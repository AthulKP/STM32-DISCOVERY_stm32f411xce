/*
 * CMSIS.h
 *
 *  Created on: Jan 31, 2025
 *      Author: athul
 */

#ifndef CMSIS_H_
#define CMSIS_H_

#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile

#endif /* CMSIS_H_ */
