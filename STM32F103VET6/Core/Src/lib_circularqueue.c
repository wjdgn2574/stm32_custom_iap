/*******************************************************************************
 * Name        : lib_circularqueue.c
 * Author      : Jung-Hoo Moon
 * Version     : 1.0
 * Date        : 2022-07-27
 * Description : Circular Queue - Source File
 ******************************************************************************/

/**
 * @file   lib_circularqueue.c
 * @author Jung-Hoo Moon
 * @date   2022/07/27
 * @brief  원형큐 자료구조 라이브러리 소스 파일
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
// Main Header
#include "lib_circularqueue.h"

// C-Standard Library
#include <stdlib.h>

// MCU Driver

// User Library

/*******************************************************************************
 * Define
 ******************************************************************************/

/*******************************************************************************
 * Macro
 ******************************************************************************/
/**
 * @brief 원형큐의 인덱스 설ㅈ정
 */
#define INDEX_CQUEUE(x) ((x + 1) % CQUEUE_MAX_SIZE)

/*******************************************************************************
 * Typedef
 ******************************************************************************/

/*******************************************************************************
 * Enum
 ******************************************************************************/

/*******************************************************************************
 * Structure
 ******************************************************************************/

/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Private Function Prototype
 ******************************************************************************/

/*******************************************************************************
 * Public Function
 ******************************************************************************/
/**
 * @brief   Initialization
 * @details 원형큐 구조체를 초기화
 * @param   CQueue *p_CQueue \n
 *                              - 원형큐 구조체의 주소를 입력
 * @return  void             \n
 *                              - 반환값 없음
 */
void CQueue_Init(CQueue *p_CQueue)
{
	p_CQueue->front = 0;
	p_CQueue->rear  = 0;
	p_CQueue->size  = 0;
}

/**
 * @brief   Enqueue
 * @details 원형큐의 뒷부분에서 데이터를 추가합니다.
 * @param   CQueue *p_CQueue \n
 *                              - 원형큐 구조체의 주소를 입력
 * @param   element item     \n
 *                              - 추가하고자 하는 데이터
 * @return  CQUEUE_SUCCESS   \n
 *                              - 성공
 * @return  CQUEUE_FULL      \n
 *                              - 실패, 큐가 꽉 차있는 경우
 */
State_CQueue CQueue_Enqueue(CQueue *p_CQueue, element item)
{
	// 원형큐에 데이터를 넣을 공간이 없는지 확인
	if(CQueue_IsFull(p_CQueue))
	{
		return CQUEUE_FULL; 										// 넣을 공간이 없을 경우, 해당 상태를 반환
	}

	p_CQueue->rear                  = INDEX_CQUEUE(p_CQueue->rear); // 데이터를 추가할 버퍼의 인덱스 변경
	p_CQueue->queue[p_CQueue->rear] = item;                         // 버퍼에 데이터 삽입
	p_CQueue->size++;                                               // 원형큐의 현재 데이터 개수를 갱신

	return CQUEUE_SUCCESS; 											// 데이터 추가를 성공할 경우, 해당 상태를 반환
}

/**
 * @brief   Dequeue
 * @details 원형큐의 앞부분에서 데이터를 가져온 뒤, 큐에서 데이터를 삭제합니다.
 * @param   CQueue *p_CQueue \n
 *                              - 원형큐 구조체의 주소를 입력
 * @param   element *p_item  \n
 *                              - 큐에서 가져온 데이터를 저장할 데이터의 주소
 * @return  CQUEUE_SUCCESS   \n
 *                              - 성공
 * @return  CQUEUE_EMPTY     \n
 *                              - 실패, 큐가 비어져있는 경우
 */
State_CQueue CQueue_Dequeue(CQueue *p_CQueue, element *p_item)
{
	// 원형큐에서 가져올 데이터가 있는지 확인
	if(CQueue_IsEmpty(p_CQueue))
	{
		return CQUEUE_EMPTY; 										// 데이터가 없을 경우, 해당 상태를 반환
	}

	p_CQueue->front = INDEX_CQUEUE(p_CQueue->front);				// 데이터를 가져올 버퍼의 인덱스 변경
	if(p_item != NULL)                               				// 데이터를 저장할 변수의 포인터가 있는지 확인
	{
		*p_item = p_CQueue->queue[p_CQueue->front];  				// 원형큐의 데이터를 포인터에 저장
	}
	p_CQueue->size--;                                				// 원형큐의 현재 데이터 개수를 갱신

	return CQUEUE_SUCCESS; 											// 데이터 가져오기를 성공할 경우, 해당 상태를 반환
}

/**
 * @brief   Get current size
 * @details 원형큐의 저장된 현재 데이터의 개수를 가져옵니다.
 * @param   CQueue *p_CQueue \n
 *                              - 원형큐 구조체의 주소를 입력
 * @return  uint16_t         \n
 *                              - 0 ~ 65535 범위 중 값을 반환합니다.
 */
uint16_t CQueue_GetSize(CQueue *p_CQueue)
{
	return p_CQueue->size; // 원형큐의 현재 데이터 개수를 반환
}

/**
 * @brief   Check empty-state
 * @details 원형큐가 비어져 있는지 확인합니다.
 * @param   CQueue *p_CQueue \n
 *                              - 원형큐 구조체의 주소를 입력
 * @return  true             \n
 *                              - 큐의 데이터가 없는 상태
 * @return  false            \n
 *                              - 큐의 데이터가 있는 상태
 */
bool CQueue_IsEmpty(CQueue *p_CQueue)
{
	return (p_CQueue->front == p_CQueue->rear); // front 인덱스와 rear 인덱스가 같을 경우, 원형큐의 데이터가 존재 하지 않음
}

/**
 * @brief   Check full-state
 * @details 원형큐의 최대치로 데이터가 채워져 있는지 확인합니다.
 * @param   CQueue *p_CQueue \n
 *                              - 원형큐 구조체의 주소를 입력
 * @return  true             \n
 *                              - 큐의 데이터가 꽉 찬 상태
 * @return  false            \n
 *                              - 큐의 데이터가 있는 상태
 */
bool CQueue_IsFull(CQueue *p_CQueue)
{
	return (INDEX_CQUEUE(p_CQueue->rear) == p_CQueue->front); // 데이터 추가될 다음 read 인덱스가 front 인덱스와 같을 경우, 원형큐의 데이터를 추가할 공간이 없음
}

/*******************************************************************************
 * Private Function
 ******************************************************************************/

/*******************************************************************************
 * Callback Function
 ******************************************************************************/
