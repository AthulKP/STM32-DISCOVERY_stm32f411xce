/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mcp_hal.h"
#include "task.h"
#include "CAN_Handler.h"

SemaphoreHandle_t xSyncSemaphore;
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim11;

osThreadId HandleMCPConfigStats;
osThreadId HandleCANRx;
osThreadId HandleCANTx;
osThreadId HandleLEDIndicators;
SemaphoreHandle_t spiMutex;

TaskStatus_t xTaskDetails;
/* USER CODE BEGIN PV */
// SPI_HandleTypeDef* spi_handler;
volatile CAN_FRAME g_can_tx_frame ;

osThreadId CANTxHandle;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM11_Init(void);

// RTOS tasks
void TaskMCPConfigStatsTask(void const *argument);
void TaskCANRx(void const *argument);
void TaskCANTx(void const *argument);
void TaskLEDIndicators(void const *argument);

/* USER CODE BEGIN PFP */
// Helper functions
void revolving_led_pattern(void);
void transmit_can_message(CAN_FRAME *tx_frame);
void CAN_Pool_Init(void);


QueueHandle_t can_tx_queue;


/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_SPI2_Init();
	MX_TIM11_Init();
	/* USER CODE BEGIN 2 */
	MX_USB_DEVICE_Init();
	spi_handler = &hspi2;
	mcp_initialize();

	/* USER CODE END 2 */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of defaultTask */
	//  osThreadDef(defaultTask, StartDefaultTask, osPriorityHigh, 0, 128);
	//  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
	/* definition and creation of myTask01 */
	//  osThreadDef(myTask01, StartTask01, osPriorityHigh, 0, 128);
	//  myTask01Handle = osThreadCreate(osThread(myTask01), NULL);
	//
	//  /* USER CODE BEGIN RTOS_THREADS */
	//  osThreadDef(myTask02, StartTask02, osPriorityHigh, 0, 128);
	//  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);
	//
	osThreadDef(mcp_config_stats, TaskMCPConfigStatsTask, osPriorityNormal, 0,128);
	HandleMCPConfigStats = osThreadCreate(osThread(mcp_config_stats), NULL);

	osThreadDef(can_rx, TaskCANRx, osPriorityHigh, 0, 256);
	HandleCANRx = osThreadCreate(osThread(can_rx), NULL);
	osThreadSuspend(HandleCANRx);

	osThreadDef(can_tx, TaskCANTx, osPriorityHigh, 0, 256);
	HandleCANTx = osThreadCreate(osThread(can_tx), NULL);
	osThreadSuspend(HandleCANTx);

	osThreadDef(led_indications, TaskLEDIndicators, osPriorityNormal, 0,128);
	HandleLEDIndicators = osThreadCreate(osThread(led_indications), NULL);

	//  UBaseType_t highWaterMark = uxTaskGetStackHighWaterMark(myTask04Handle);
	/* USER CODE END RTOS_THREADS */

	/* Start scheduler */
	osKernelStart();

	/* We should never get here as control is now taken by the scheduler */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 72;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 3;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief SPI2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI2_Init(void) {

	/* USER CODE BEGIN SPI2_Init 0 */

	/* USER CODE END SPI2_Init 0 */

	/* USER CODE BEGIN SPI2_Init 1 */

	/* USER CODE END SPI2_Init 1 */
	/* SPI2 parameter configuration*/
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_SOFT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi2.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI2_Init 2 */

	/* USER CODE END SPI2_Init 2 */
}

/**
 * @brief TIM11 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM11_Init(void) {

	/* USER CODE BEGIN TIM11_Init 0 */

	/* USER CODE END TIM11_Init 0 */

	/* USER CODE BEGIN TIM11_Init 1 */

	/* USER CODE END TIM11_Init 1 */
	htim11.Instance = TIM11;
	htim11.Init.Prescaler = 0;
	htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim11.Init.Period = 65535;
	htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim11) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM11_Init 2 */

	/* USER CODE END TIM11_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */

	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin,
			GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD,
			led_cantx_Pin | led_mcp_error_Pin | led_poweron_Pin | led_canrx_Pin,
			GPIO_PIN_RESET);

	/*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
	GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : mcp_cs_Pin */
	GPIO_InitStruct.Pin = mcp_cs_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(mcp_cs_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : mcp_int_Pin */
	GPIO_InitStruct.Pin = mcp_int_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(mcp_int_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : led_cantx_Pin led_mcp_error_Pin led_poweron_Pin led_canrx_Pin */
	GPIO_InitStruct.Pin = led_cantx_Pin | led_mcp_error_Pin | led_poweron_Pin
			| led_canrx_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */

	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void TaskMCPConfigStatsTask(void const *argument) {
	/* USER CODE BEGIN StartTask01 */
	/* Infinite loop */
	spiMutex = xSemaphoreCreateMutex();
	CAN_Pool_Init();
	configASSERT(spiMutex != NULL);
	for (;;) {
		if (hUsbDeviceFS.dev_state != USBD_STATE_CONFIGURED) {
			revolving_led_pattern();
			vTaskGetInfo(HandleCANTx, &xTaskDetails, pdTRUE, eInvalid);
			if (xTaskDetails.eCurrentState != eSuspended) {
				vTaskSuspend(HandleCANTx);
				vTaskSuspend(HandleCANRx);
			}
		} else {
			vTaskGetInfo(HandleCANTx, &xTaskDetails, pdTRUE, eInvalid);
			if (xTaskDetails.eCurrentState == eSuspended) {
				vTaskResume(HandleCANTx);
				vTaskResume(HandleCANRx);
			}
		}
	}
}

void TaskCANRx(void const *argument) {

	for (;;) {
		if (!HAL_GPIO_ReadPin(mcp_int_GPIO_Port, mcp_int_Pin)) {
			if (xSemaphoreTake(spiMutex, portMAX_DELAY) == pdTRUE) {
				mcp_recieve_can(&g_can_tx_frame);
				xSemaphoreGive(spiMutex);
				CDC_Transmit_FS(&g_can_tx_frame, 13U);
			}
		}
	}
}

void TaskCANTx(void const *argument) {
	CAN_FRAME *frame;
	for (;;) {
		if (xQueueReceive(can_tx_queue, &frame, portMAX_DELAY) == pdTRUE) {
			if (xSemaphoreTake(spiMutex, portMAX_DELAY) == pdTRUE) {
				transmit_can_message(frame); // Send over CAN
				xSemaphoreGive(spiMutex);
				CAN_FramePool_Free(frame);   // Return to pool
			}
		}
	}
}

void TaskLEDIndicators(void const *arguments){

	for(;;){
	vTaskGetInfo(HandleCANTx, &xTaskDetails, pdTRUE, eInvalid);
	HAL_GPIO_WritePin(led_cantx_GPIO_Port, led_cantx_Pin, (int) xTaskDetails.eCurrentState < eBlocked);
	vTaskGetInfo(HandleCANRx, &xTaskDetails, pdTRUE, eInvalid);
	HAL_GPIO_WritePin(led_canrx_GPIO_Port, led_canrx_Pin, (int) xTaskDetails.eCurrentState < eBlocked);
	osDelay(500);
	HAL_GPIO_WritePin(led_cantx_GPIO_Port, led_cantx_Pin, 0x0);
	HAL_GPIO_WritePin(led_canrx_GPIO_Port, led_canrx_Pin, 0x0);
	}
}

void CAN_Pool_Init(void) {
	CAN_FramePool_Init(); // Call during system init

	can_tx_queue = xQueueCreate(8, sizeof(CAN_FRAME));
	if (can_tx_queue == NULL) {
		HAL_GPIO_WritePin(led_cantx_GPIO_Port, led_cantx_Pin, 0x1);
	}
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
	printf("Stack overflow in task: %s\n", pcTaskName);
	while (1)
		; // Break here in debugger
}

/* USER CODE END 4 */

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM1 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	/* USER CODE BEGIN Callback 0 */

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM1) {
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}
void revolving_led_pattern(void) {
	HAL_GPIO_WritePin(led_mcp_error_GPIO_Port, led_poweron_Pin, 0x0);
	HAL_GPIO_WritePin(led_mcp_error_GPIO_Port, led_cantx_Pin, 0x1);
	osDelay(140);
	HAL_GPIO_WritePin(led_mcp_error_GPIO_Port, led_cantx_Pin, 0x0);
	HAL_GPIO_WritePin(led_mcp_error_GPIO_Port, led_mcp_error_Pin, 0x1);
	osDelay(140);
	HAL_GPIO_WritePin(led_mcp_error_GPIO_Port, led_mcp_error_Pin, 0x0);
	HAL_GPIO_WritePin(led_mcp_error_GPIO_Port, led_canrx_Pin, 0x1);
	osDelay(140);
	HAL_GPIO_WritePin(led_mcp_error_GPIO_Port, led_canrx_Pin, 0x0);
	HAL_GPIO_WritePin(led_mcp_error_GPIO_Port, led_poweron_Pin, 0x1);
	osDelay(140);
}
void transmit_can_message(CAN_FRAME *tx_frame) {
	volatile uint8_t txdata[14];
	volatile uint8_t buffer_id = 0, buffer_ctrl_reg = 0;

	mcp_rx_reg(&buffer_id, &buffer_ctrl_reg);

	txdata[0] = (uint8_t) (MCP_INSTRUCTION_LOAD_TX_BUFFER | buffer_id);

	load_array(&txdata, tx_frame);

	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_Transmit(spi_handler, txdata, 14U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);

	mcp_reg_write(buffer_ctrl_reg, MCP_TXREQ_EN);

	txdata[0] = MCP_INSTRUCTION_REQUEST_TO_SEND | buffer_id;
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x0);
	HAL_SPI_Transmit(spi_handler, txdata, 1U, 100);
	HAL_GPIO_WritePin(mcp_cs_GPIO_Port, mcp_cs_Pin, 0x1);
}
#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
