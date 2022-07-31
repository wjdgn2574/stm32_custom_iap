/*******************************************************************************
 * Name        : lib_printf.c
 * Author      : Jung-Hoo Moon
 * Version     : 1.0
 * Date        : 2022-07-27
 * Description : Printf Library - Source File
 ******************************************************************************/

/**
 * @file   lib_printf.c
 * @author Jung-Hoo Moon
 * @date   2022/07/27
 * @brief  printf 함수 내용 설정 소스 파일
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
// Main Header
#include "lib_printf.h"

// C-Standard Library
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// MCU Driver

// User Library
#if defined(DBG_SWO)
#include "stm32f1xx_hal.h"
#endif

#if defined(DBG_RTT)

#endif

#if defined(DBG_UART1) | defined(DBG_UART2) | defined(DBG_UART3) | defined(DBG_UART4) | defined(DBG_UART5)
#include "usart.h"
#endif

/*******************************************************************************
 * Defines
 ******************************************************************************/
#if defined(DBG_SWO)

#endif

#if defined(DBG_RTT)

#endif

#if defined(DBG_UART1)

#endif

#if defined(DBG_UART2)

#endif

#if defined(DBG_UART3)

#endif

#if defined(DBG_UART4)

#endif

#if defined(DBG_UART5)

#endif

/*******************************************************************************
 * Macros
 ******************************************************************************/
#if defined(DBG_SWO)

#endif

#if defined(DBG_RTT)

#endif

#if defined(DBG_UART1)

#endif

#if defined(DBG_UART2)

#endif

#if defined(DBG_UART3)

#endif

#if defined(DBG_UART4)

#endif

#if defined(DBG_UART5)

#endif

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
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Constants
 ******************************************************************************/

/*******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Public Function
 ******************************************************************************/

/*******************************************************************************
 * Private Function
 ******************************************************************************/

/*******************************************************************************
 * Abstract Function
 ******************************************************************************/
#ifdef __cplusplus
extern "C" int _write(int32_t file, uint8_t *ptr, int32_t len) {
#else
int _write(int32_t file, uint8_t *ptr, int32_t len) {
#endif

#if defined(DBG_SWO)
	for(int32_t i=0; i<len; ++i) {
		ITM_SendChar(*ptr++);
	}
#endif

#if defined(DBG_RTT)

#endif

#if defined(DBG_UART1)
	if(HAL_UART_Transmit(&huart1, ptr, len, 1000) != HAL_OK) {
		return 0;
	}
#endif

#if defined(DBG_UART2)
	if(HAL_UART_Transmit(&huart2, ptr, len, 1000) != HAL_OK) {
		return 0;
	}
#endif

#if defined(DBG_UART3)
	if(HAL_UART_Transmit(&huart3, ptr, len, 1000) != HAL_OK) {
		return 0;
	}
#endif

#if defined(DBG_UART4)
	if(HAL_UART_Transmit(&huart4, ptr, len, 1000) != HAL_OK) {
		return 0;
	}
#endif

#if defined(DBG_UART5)
	if(HAL_UART_Transmit(&huart5, ptr, len, 1000) != HAL_OK) {
		return 0;
	}
#endif

	return len;
}
