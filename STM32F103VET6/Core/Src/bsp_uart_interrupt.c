/*******************************************************************************
 * Name        : bsp_uart_interrupt.c
 * Author      : Jung-Hoo Moon
 * Version     : 1.0
 * Date        : 2022-07-27
 * Description : STM32F103 BSP(Board Support Package) UART Interrupt - Source File
 ******************************************************************************/

/**
 * @file   bsp_uart_interrupt.c
 * @author Jung-Hoo Moon
 * @date   2022/07/27
 * @brief  BSP(Board Support Package) - UART Interrupt Handling Source File
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
// Main Header
#include "bsp_uart_interrupt.h"

// C-Standard Library
#include <stdio.h>
#include <string.h>

// MCU Driver

// User Library

/*******************************************************************************
 * Defines
 ******************************************************************************/

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
 * Variables
 ******************************************************************************/
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_1) == BSP_UART_INTERRUPT_UART_PORT_1)
CQueue   cQueue_UART1;
#endif

#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_2) == BSP_UART_INTERRUPT_UART_PORT_2)
CQueue   cQueue_UART2;
#endif

#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_3) == BSP_UART_INTERRUPT_UART_PORT_3)
CQueue   cQueue_UART3;
#endif

#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_4) == BSP_UART_INTERRUPT_UART_PORT_4)
CQueue   cQueue_UART4;
#endif

#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_5) == BSP_UART_INTERRUPT_UART_PORT_5)
CQueue   cQueue_UART5;
#endif

/*******************************************************************************
 * Constants
 ******************************************************************************/

/*******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Public Function
 ******************************************************************************/
/**
 * @brief   Initialization
 * @details UART Interrupt Handle에 사용되는 것들을 초기화 합니다.
 * @param   void             \n
 *                              - 매개변수 없음
 * @return  void             \n
 *                              - 반환값 없음
 */
void BspUartInterrupt_Init(void)
{
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_1) == BSP_UART_INTERRUPT_UART_PORT_1)
	CQueue_Init(&cQueue_UART1); // UART1에 사용될 원형큐 초기화
#endif

#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_2) == BSP_UART_INTERRUPT_UART_PORT_2)
	CQueue_Init(&cQueue_UART2); // UART2에 사용될 원형큐 초기화
#endif

#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_3) == BSP_UART_INTERRUPT_UART_PORT_3)
	CQueue_Init(&cQueue_UART3); // UART3에 사용될 원형큐 초기화
#endif

#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_4) == BSP_UART_INTERRUPT_UART_PORT_4)
	CQueue_Init(&cQueue_UART4); // UART4에 사용될 원형큐 초기화
#endif

#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_5) == BSP_UART_INTERRUPT_UART_PORT_5)
	CQueue_Init(&cQueue_UART5); // UART5에 사용될 원형큐 초기화
#endif
}

/**
 * @brief   UART Interrupt Enable
 * @details UART Interrupt 활성화 시킵니다.
 * @param   uint8_t select_uart \n
 *                                 - 활성화 시킬 UART Port define 값을 입력합니다.
 * @return  void                \n
 *                                 - 반환값 없음
 */
void BspUartInterrupt_Enable(uint8_t select_uart)
{
	UART_HandleTypeDef *p_uart = NULL;

	switch(select_uart)
	{
		case BSP_UART_INTERRUPT_UART_PORT_1 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_1) == BSP_UART_INTERRUPT_UART_PORT_1)
			p_uart = &huart1; // UART1 Handle을 포인터에 연결
#endif
			break;
		case BSP_UART_INTERRUPT_UART_PORT_2 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_2) == BSP_UART_INTERRUPT_UART_PORT_2)
			p_uart = &huart2; // UART2 Handle을 포인터에 연결
#endif
			break;
		case BSP_UART_INTERRUPT_UART_PORT_3 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_3) == BSP_UART_INTERRUPT_UART_PORT_3)
			p_uart = &huart3; // UART3 Handle을 포인터에 연결
#endif
			break;
		case BSP_UART_INTERRUPT_UART_PORT_4 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_4) == BSP_UART_INTERRUPT_UART_PORT_4)
			p_uart = &huart4; // UART4 Handle을 포인터에 연결
#endif
			break;
		case BSP_UART_INTERRUPT_UART_PORT_5 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_5) == BSP_UART_INTERRUPT_UART_PORT_5)
			p_uart = &huart5; // UART5 Handle을 포인터에 연결
#endif
			break;
		default :
			break;
	}

	if(p_uart != NULL)
	{
		__HAL_UART_ENABLE_IT(p_uart, UART_IT_RXNE); // 선택한 UART의 Interrupt를 활성화
	}
}

/**
 * @brief   UART Interrupt Disable
 * @details UART Interrupt 비활성화 시킵니다.
 * @param   uint8_t select_uart \n
 *                                 - 비활성화 시킬 UART Port define 값을 입력합니다.
 * @return  void                \n
 *                                 - 반환값 없음
 */
void BspUartInterrupt_Disable(uint8_t select_uart)
{
	UART_HandleTypeDef *p_uart = NULL;

	switch(select_uart)
	{
		case BSP_UART_INTERRUPT_UART_PORT_1 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_1) == BSP_UART_INTERRUPT_UART_PORT_1)
			p_uart = &huart1;
#endif
			break;
		case BSP_UART_INTERRUPT_UART_PORT_2 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_2) == BSP_UART_INTERRUPT_UART_PORT_2)
			p_uart = &huart2;
#endif
			break;
		case BSP_UART_INTERRUPT_UART_PORT_3 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_3) == BSP_UART_INTERRUPT_UART_PORT_3)
			p_uart = &huart3;
#endif
			break;
		case BSP_UART_INTERRUPT_UART_PORT_4 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_4) == BSP_UART_INTERRUPT_UART_PORT_4)
			p_uart = &huart4;
#endif
			break;
		case BSP_UART_INTERRUPT_UART_PORT_5 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_5) == BSP_UART_INTERRUPT_UART_PORT_5)
			p_uart = &huart5;
#endif
			break;
		default :
			break;
	}

	if(p_uart != NULL)
	{
		__HAL_UART_DISABLE_IT(p_uart, UART_IT_RXNE); // 선택한 UART의 Interrupt를 비활성화
		__HAL_UART_CLEAR_PEFLAG(p_uart);             // 선택한 UART의 Interrupt 관련 Flag 초기화
	}
}

/**
 * @brief   UART Interrupt Process
 * @details UART Interrupt를 통해 데이터를 받아 원형큐에 저장하는 함수(stm32f1xx_it.c의 UART Handle 함수에 해당 내용을 넣어서 사용 추천)
 * @param   uint8_t select_uart \n
 *                                 - 사용할 UART Port define 값을 입력합니다.
 * @param   uint8_t byte        \n
 *                                 - 처리할 데이터를 입력(Byte 단위로 처리 가능)
 * @return  void                \n
 *                                 - 반환값 없음
 */
void BspUartInterrupt_Process(uint8_t select_uart, uint8_t byte)
{
	UART_HandleTypeDef *p_uart   = NULL;
	CQueue             *p_cqueue = NULL;
	uint8_t             dummy    = 0x00;

	switch(select_uart)
	{
		case BSP_UART_INTERRUPT_UART_PORT_1 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_1) == BSP_UART_INTERRUPT_UART_PORT_1)
			p_uart   = &huart1;
			p_cqueue = &cQueue_UART1;
#endif
			break;
		case BSP_UART_INTERRUPT_UART_PORT_2 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_2) == BSP_UART_INTERRUPT_UART_PORT_2)
			p_uart   = &huart2;
			p_cqueue = &cQueue_UART2;
#endif
			break;
		case BSP_UART_INTERRUPT_UART_PORT_3 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_3) == BSP_UART_INTERRUPT_UART_PORT_3)
			p_uart   = &huart3;
			p_cqueue = &cQueue_UART3;
#endif
			break;
		case BSP_UART_INTERRUPT_UART_PORT_4 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_4) == BSP_UART_INTERRUPT_UART_PORT_4)
			p_uart   = &huart4;
			p_cqueue = &cQueue_UART4;
#endif
			break;
		case BSP_UART_INTERRUPT_UART_PORT_5 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_5) == BSP_UART_INTERRUPT_UART_PORT_5)
			p_uart   = &huart5;
			p_cqueue = &cQueue_UART5;
#endif
			break;
		default :
			break;
	}

	if((p_uart != NULL) && (p_cqueue != NULL))
	{
		if(CQueue_Enqueue(p_cqueue, byte) == CQUEUE_FULL) // UART에 사용되는 원형큐의 데이터를 삽입
		{
			CQueue_Dequeue(p_cqueue, &dummy);             // UART에 사용되는 원형큐가 가득 찼을 경우, 제일 오래된 데이터 하나를 삭제
		}
	}
}

/**
 * @brief   Get Circular Queue
 * @details UART Interrupt를 통해 저장된 원형큐의 주소를 반환합니다.
 * @param   uint8_t select_uart \n
 *                                 - 사용할 UART Port define 값을 입력합니다.
 * @return  CQueue*             \n
 *                                 - 원형큐의 주소
 */
CQueue* BspUartInterrupt_GetQueue(uint8_t select_uart)
{
		switch(select_uart)
	{
		case BSP_UART_INTERRUPT_UART_PORT_1 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_1) == BSP_UART_INTERRUPT_UART_PORT_1)
			return (&cQueue_UART1);
#else
			break;
#endif
		case BSP_UART_INTERRUPT_UART_PORT_2 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_2) == BSP_UART_INTERRUPT_UART_PORT_2)
			return (&cQueue_UART2);
#else
			break;
#endif
		case BSP_UART_INTERRUPT_UART_PORT_3 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_3) == BSP_UART_INTERRUPT_UART_PORT_3)
			return (&cQueue_UART3);
#else
			break;
#endif
		case BSP_UART_INTERRUPT_UART_PORT_4 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_4) == BSP_UART_INTERRUPT_UART_PORT_4)
			return (&cQueue_UART4);
#else
			break;
#endif
		case BSP_UART_INTERRUPT_UART_PORT_5 :
#if((BSP_UART_INTERRUPT_UART_PORT_SELECT & BSP_UART_INTERRUPT_UART_PORT_5) == BSP_UART_INTERRUPT_UART_PORT_5)
			return (&cQueue_UART5);
#else
			break;
#endif
		default :
			break;
	}

	return NULL;
}

/*******************************************************************************
 * Private Function
 ******************************************************************************/

/*******************************************************************************
 * Abstract Function
 ******************************************************************************/

/*******************************************************************************
 * EOF
 ******************************************************************************/
