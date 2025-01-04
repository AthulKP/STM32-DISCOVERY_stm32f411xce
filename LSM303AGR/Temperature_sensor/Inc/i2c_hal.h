/*
 * I2c_hal.h
 *
 *  Created on: Dec 29, 2024
 *      Author: athul
 */

#ifndef I2C_HAL_H_
#define I2C_HAL_H_

#include <stdint.h>
#include "CMSIS.h"


#define I2C_Reset_value        ((uint32_t)0x00000000)

#define I2C1_Base_Address      ((uint32_t)0x40005400)

#define I2C_CR1_PE    ((uint32_t) 0x1<<0)
#define I2C_CR1_START ((uint32_t) 0x1<<8)
#define I2C_CR1_STOP  ((uint32_t) 0x1<<9)
#define I2C_CR1_ACK   ((uint32_t) 0x1<<10)
#define I2C_CR1_SWRST ((uint32_t) 0x1<<15)

#define I2C_SR1_SB    ((uint32_t) 0x1<<0)
#define I2C_SR1_ADDR  ((uint32_t) 0x1<<1)
#define I2C_SR1_BTF   ((uint32_t) 0x1<<2)
#define I2C_SR1_STOPF ((uint32_t) 0x1<<4)
#define I2C_SR1_RXNE  ((uint32_t) 0x1<<6)
#define I2C_SR1_TXE   ((uint32_t) 0x1<<7)

typedef struct
{
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t OAR1;
    __IO uint32_t OAR2;
    __IO uint32_t DR;
    __IO uint32_t SR1;
    __IO uint32_t SR2;
    __IO uint32_t CCR;
    __IO uint32_t TRISE;
    __IO uint32_t FLTR;
}I2Cx;

void I2C_Initialize(I2Cx*);
void I2C_Terminate(I2Cx*);
uint8_t i2c_read_single_reg(I2Cx* ,uint8_t ,uint8_t);
void i2c_read_multiple_reg(I2Cx* ,uint8_t , uint8_t ,uint8_t* , int8_t );
void i2c_write_single_reg(I2Cx* ,uint8_t ,uint8_t ,uint8_t);
void i2c_augment_single_reg(I2Cx* ,uint8_t , uint8_t , uint8_t );
void __I2C1_Start(I2Cx*);
void __I2C1_Write_Register(I2Cx* ,uint8_t);
void __I2C1_Write_Address(I2Cx* ,uint8_t);
uint8_t __I2C1_Read_ACK(I2Cx*);
uint8_t __I2C1_Read_NACK(I2Cx*);
void __I2C1_Stop(I2Cx*);


void I2C_Initialize(I2Cx* i2c){
    i2c->CR1   &= ~(I2C_CR1_PE);  // Disable I2C Peripheral
    i2c->CR1   |= 1<<15;          // I2C SWRest
    i2c->CR1    = 0x0;            // I2C toggle SWRest

    i2c->CR2   |= 0x10;           // Setting I2C clock to 16MHz
    i2c->CCR   |= 0x50;           // Scl_up/peripheral_clk_up
    i2c->TRISE  = 0x11;           // Max rise time setting
    i2c->CR1   |= I2C_CR1_PE;     // Enable I2C Peripheral
    i2c->CR1   |= I2C_CR1_ACK;    // Enable ACK
}

void I2C_Terminate(I2Cx* i2c){
    i2c->CR1   |= 1<<15;          // I2C SWRest clears all regs i,e; Config
    i2c->CR1   &= ~(I2C_CR1_PE);  // Disable I2C Peripheral
}

uint8_t i2c_read_single_reg(I2Cx* i2c,uint8_t i2c_address, uint8_t reg_address){
    __I2C1_Start(i2c);
    __I2C1_Write_Address(i2c,i2c_address<<1);
    __I2C1_Write_Register(i2c,reg_address);
    __I2C1_Start(i2c);
    __I2C1_Write_Address(i2c,(i2c_address<<1)|0x1);
    uint8_t data =  __I2C1_Read_NACK(i2c);
    __I2C1_Stop(i2c);
    return data;
}

void i2c_read_multiple_reg(I2Cx* i2c,uint8_t i2c_address, uint8_t reg_address,uint8_t* p_data, int8_t count){
    __I2C1_Start(i2c);
    __I2C1_Write_Address(i2c,i2c_address<<1);
    __I2C1_Write_Register(i2c,reg_address |(1<<7)); // MSB = 1 for auto increment register in multiple read
    __I2C1_Start(i2c);
    __I2C1_Write_Address(i2c,(i2c_address<<1)|0x1);
    for(;count >= 2; p_data++,count--){
    	*p_data =  __I2C1_Read_ACK(i2c);
    }
    *p_data =  __I2C1_Read_NACK(i2c);
    __I2C1_Stop(i2c);

}

void i2c_write_single_reg(I2Cx* i2c,uint8_t i2c_address, uint8_t reg_address, uint8_t data){
    __I2C1_Start(i2c);
    __I2C1_Write_Address(i2c,i2c_address<<1);
    __I2C1_Write_Register(i2c,reg_address);
    __I2C1_Write_Register(i2c,data);
    __I2C1_Stop(i2c);
}

void i2c_augment_single_reg(I2Cx* i2c,uint8_t i2c_address, uint8_t reg_address, uint8_t data){
	data |= i2c_read_single_reg(i2c,i2c_address,reg_address);
    i2c_write_single_reg(i2c,i2c_address, reg_address,data);
}

void __I2C1_Start(I2Cx* i2c) {
    i2c->CR1 |= I2C_CR1_START;            // Generate START condition
    while (!(i2c->SR1 & I2C_SR1_SB));     // Wait for START condition
}

void __I2C1_Write_Register(I2Cx* i2c,uint8_t reg_address) {
    i2c->DR = reg_address;                // Send data
    while (!(i2c->SR1 & I2C_SR1_TXE));    // Wait for transmission complete
    (void)i2c->SR2;
    while (!(i2c->SR1 & I2C_SR1_TXE));
}

void __I2C1_Write_Address(I2Cx* i2c,uint8_t i2c_address) {
    i2c->DR = i2c_address;                 // Send data
    while (!(i2c->SR1 & I2C_SR1_ADDR));    // Wait for transmission complete
    (void)i2c->SR2;
}

uint8_t __I2C1_Read_ACK(I2Cx* i2c) {
    i2c->CR1 |= I2C_CR1_ACK;              // Enable ACK
    while (!(i2c->SR1 & I2C_SR1_RXNE));   // Wait for data
    return i2c->DR;                       // Return received data
}

uint8_t __I2C1_Read_NACK(I2Cx* i2c) {
    i2c->CR1 &= ~I2C_CR1_ACK;             // Disable ACK
    while (!(i2c->SR1 & I2C_SR1_RXNE));   // Wait for data
    return i2c->DR;                       // Return received data
}

void __I2C1_Stop(I2Cx* i2c) {
    i2c->CR1 |= I2C_CR1_STOP;             // Generate STOP condition
}

#endif /* I2C_HAL_H_ */
