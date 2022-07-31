/*******************************************************************************
 * Name        : bsp_uart_interrupt.h
 * Author      : Jung-Hoo Moon
 * Version     : 1.0
 * Date        : 2022-07-27
 * Description : STM32F103 BSP(Board Support Package) UART Interrupt - Header File
 ******************************************************************************/

/**
 * @file   bsp_uart_interrupt.h
 * @author Jung-Hoo Moon
 * @date   2022/07/27
 * @brief  BSP(Board Support Package) - UART Interrupt Handling Header File
 */

#ifndef __BSP_UART_INTERRUPT_H__
#define __BSP_UART_INTERRUPT_H__

/*******************************************************************************
 * Includes
 ******************************************************************************/
// C-Standard Library
#include <stdint.h>
#include <stdbool.h>

// MCU Driver
#include "usart.h"

// User Library
#include "lib_circularqueue.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/
/**
 * @brief UART 버퍼 최대 크기
 */
#define BSP_UART_INTERRUPT_MAX_BUFFER_SIZE    2048

// UART Ports
/**
 * @brief UART Port 1
 */
#define BSP_UART_INTERRUPT_UART_PORT_1        0x01
/**
 * @brief UART Port 2
 */
#define BSP_UART_INTERRUPT_UART_PORT_2        0x02
/**
 * @brief UART Port 3
 */
#define BSP_UART_INTERRUPT_UART_PORT_3        0x04
/**
 * @brief UART Port 4
 */
#define BSP_UART_INTERRUPT_UART_PORT_4        0x08
/**
 * @brief UART Port 5
 */
#define BSP_UART_INTERRUPT_UART_PORT_5        0x10

// UART Config
/**
 * @brief 사용할 UART Port 선택
 */
#define BSP_UART_INTERRUPT_UART_PORT_SELECT   (BSP_UART_INTERRUPT_UART_PORT_5)

/*******************************************************************************
 * Macros
 ******************************************************************************/

/*******************************************************************************
 * Enums
 ******************************************************************************/

/*******************************************************************************
 * Structure
 ******************************************************************************/

/*******************************************************************************
 * External Variables
 ******************************************************************************/

/*******************************************************************************
 * External Constants
 ******************************************************************************/

/*******************************************************************************
 * Public Function Prototypes
 ******************************************************************************/
void    BspUartInterrupt_Init(void);
void    BspUartInterrupt_Enable(uint8_t select_uart);
void    BspUartInterrupt_Disable(uint8_t select_uart);
void    BspUartInterrupt_Process(uint8_t select_uart, uint8_t byte);
CQueue* BspUartInterrupt_GetQueue(uint8_t select_uart);

/*******************************************************************************
 * Abstract Function Prototypes
 ******************************************************************************/

#endif /* __BSP_UART_INTERRUPT_H__ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
