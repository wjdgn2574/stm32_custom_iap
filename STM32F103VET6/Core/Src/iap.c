/*******************************************************************************
 * Name        : iap.c
 * Author      : Moon Jung-Hoo
 * Version     : 1.0
 * Description : IAP(In Application Program) - Source File
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "iap.h"

// C Standard

// MCU Driver

// User

/*******************************************************************************
 * Defines
 ******************************************************************************/
// Switch On/Off
#define IAP_SWITCH_OFF          GPIO_PIN_SET
#define IAP_SWITCH_ON           GPIO_PIN_RESET

// Mode Select
#define IAP_HW_MODE_APPLICATION	0x00
#define IAP_HW_MODE_BOOTLOADER  0x01
#define IAP_HW_MODE_USER1       0x02
#define IAP_HW_MODE_USER2       0x03

// Download State
#define IAP_DOWNLOAD_INIT       0x00
#define IAP_DOWNLOAD_READY      0x01
#define IAP_DOWNLOAD_DOWNLOAD   0x02
#define IAP_DOWNLOAD_FLASH      0x03
#define IAP_DOWNLOAD_FINISH     0x04

/*******************************************************************************
 * Macros
 ******************************************************************************/

/*******************************************************************************
 * Enums
 ******************************************************************************/

/*******************************************************************************
 * Structures
 ******************************************************************************/

/*******************************************************************************
 * Typedefs
 ******************************************************************************/

/*******************************************************************************
 * Constants - Extern Variables
 ******************************************************************************/

/*******************************************************************************
 * Constants - Local Variables
 ******************************************************************************/
uint8_t   iap_select;

// Serial Network
//Network   iap_network;
uint8_t   iap_network_byte;
uint8_t   iap_network_length;

// File Download
uint16_t  iap_partition_index                 = 0;
uint8_t   iap_partition_size                  = 0;
uint32_t  iap_manufacture_id                  = 0;
uint32_t  iap_file_size                       = 0;
uint8_t   iap_partition_unit                  = 0;
uint8_t   iap_file_select                     = 0;
uint16_t  iap_file_crc                        = 0;
uint16_t  iap_file_checkCRC                   = 0;
uint16_t  iap_check_index_count               = 0;
uint16_t  iap_check_page_count                = 0;
uint16_t  iap_flash_page_count                = 0;
uint16_t  iap_state                           = IAP_DOWNLOAD_INIT;

// GUI
uint8_t   iap_content[256]                    = {0x00, };
uint8_t   iap_contentLength                   = 0x00;
uint8_t   iap_payload[256]                    = {0x00, };
uint8_t   iap_payloadLength                   = 0x00;
uint8_t   iap_packet[256]                     = {0x00, };
uint8_t   iap_packetLength                    = 0x00;
//uint8_t   iap_buffer[DRV_NETWORK_BUFFER_SIZE] = {0x00, };
uint16_t  iap_size                            = 0;

// System Flag
uint16_t  iap_system_flag                     = 0;
uint16_t  iap_fw_checksum                     = 0;
uint32_t  iap_fw_size                         = 0;

/*******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/
void    IAP_Info(void);
void    IAP_DeInit(void);
uint8_t IAP_Select(void);
bool    IAP_CheckApp(void);
void    IAP_ExecApp(void);
void    IAP_Update(void);
void    IAP_GetSystemOption(void);
void    IAP_CheckSystemOption(void);
bool    IAP_DetectFalsificationFW(void);
void    IAP_DownloadFW(void);

void    IAP_AckForReady_GUI(void);
void    IAP_AckForSend_GUI(void);

/*******************************************************************************
 * Public Functions
 ******************************************************************************/
void IAP_Init(void)
{
	// Init LED
	HAL_GPIO_WritePin(LED_SYSTEM_GPIO_Port, LED_SYSTEM_Pin, LED_OFF);

	// Init BSP UART
	BspUartInterrupt_Init();

	// Enable Interrupt
	BspUartInterrupt_Enable(BSP_UART_INTERRUPT_UART_PORT_5);

	// Init Serial Network
	//Network_Init(&iap_network);

	// Start Bootloader
	IAP_Info();

	// Check System-Flag
	//IAP_CheckSystemOption();

	// Check HW-Switch
	iap_select = IAP_Select();
}

void IAP_Proc(void)
{
	switch(iap_select)
	{
		case IAP_HW_MODE_APPLICATION : // Application
			/*
			// Check flag for update
			if((iap_system_flag & 0x8000) == 0x8000)
			{
				printf("Install Application \r\n");

				printf("- Check to download file : ");

				if(IAP_DetectFalsificationFW())
				{
					uint32_t word = 0;

					printf("Success \r\n");

					// Download Area -> Application Area Copy
					printf("- Format : Application Area \r\n");
					if(FLASH_Erase(ADDR_FLASH_PAGE_9, ADDR_FLASH_PAGE_59) == HAL_OK)
					{
						FLASH_CopyPage(ADDR_FLASH_PAGE_59, ADDR_FLASH_PAGE_9, (ADDR_FLASH_PAGE_59 - ADDR_FLASH_PAGE_9));
					}

					// Clear System Flag
					printf("- Clear system flag : ");
					if(FLASH_Erase(ADDR_FLASH_PAGE_109, ADDR_FLASH_PAGE_110) == HAL_OK)
					{
						iap_system_flag -= 0x8000;
						word                        = ( ((uint32_t)iap_system_flag << 16) | (uint32_t)iap_fw_checksum );
						if(FLASH_WriteWord(ADDR_FLASH_PAGE_109, word))
						{
							printf("O, ");
						}
						else
						{
							printf("X, ");
						}

						if(FLASH_WriteWord((ADDR_FLASH_PAGE_109 + 4), iap_fw_size))
						{
							printf("O \r\n");
						}
						else
						{
							printf("X \r\n");
						}

						IAP_GetSystemOption();
						IAP_CheckSystemOption();
					}
				}
				else
				{
					printf("Fail \r\n");
				}
			}

			if(IAP_CheckApp())
			{
				printf("Run application \r\n\r\n");

				IAP_ExecApp();
			}
			else
			{
				printf("Wait for install application \r\n\r\n");

				IAP_Update();
			}
			*/

			break;
		case IAP_HW_MODE_BOOTLOADER : // Boot Loader
			/*
			if(IAP_CheckApp())
			{
				printf("Installed application \r\n\r\n");
			}
			else
			{
				printf("Not installed application \r\n\r\n");
			}

			IAP_Update();
			*/
			break;
		case IAP_HW_MODE_USER1 : // Not Use
			break;
		case IAP_HW_MODE_USER2 : // Not Use
			break;
		default :
			break;
	}
}

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
void IAP_Info(void)
{
	printf("******************************\r\n");
	printf("%s \r\n"  , IAP_NAME);
	printf("- Target : %s \r\n", IAP_TARGET);
	printf("- Version : %s \r\n", IAP_VERSION);
	printf("- Release : %s \r\n", IAP_RELEASE_DATE);
	printf("******************************\r\n");
	printf("\r\n");
}

void IAP_DeInit(void)
{
	// LED Off
	HAL_GPIO_DeInit(LED_SYSTEM_GPIO_Port, LED_SYSTEM_Pin);

	// Disable UART
	BspUartInterrupt_Disable(BSP_UART_INTERRUPT_UART_PORT_5);
}

uint8_t IAP_Select(void)
{
	uint8_t retval = IAP_HW_MODE_APPLICATION;

	if( 	 (HAL_GPIO_ReadPin(CUSTOM_BOOT_1_GPIO_Port, CUSTOM_BOOT_1_Pin) == IAP_SWITCH_OFF) &&
			 (HAL_GPIO_ReadPin(CUSTOM_BOOT_2_GPIO_Port, CUSTOM_BOOT_2_Pin) == IAP_SWITCH_OFF) )
	{
		retval = IAP_HW_MODE_APPLICATION;
	}
	else if( (HAL_GPIO_ReadPin(CUSTOM_BOOT_1_GPIO_Port, CUSTOM_BOOT_1_Pin) == IAP_SWITCH_ON) &&
			 (HAL_GPIO_ReadPin(CUSTOM_BOOT_2_GPIO_Port, CUSTOM_BOOT_2_Pin) == IAP_SWITCH_OFF) )
	{
		retval = IAP_HW_MODE_BOOTLOADER;
	}
	else if( (HAL_GPIO_ReadPin(CUSTOM_BOOT_1_GPIO_Port, CUSTOM_BOOT_1_Pin) == IAP_SWITCH_OFF) &&
			 (HAL_GPIO_ReadPin(CUSTOM_BOOT_2_GPIO_Port, CUSTOM_BOOT_2_Pin) == IAP_SWITCH_ON) )
	{
		retval = IAP_HW_MODE_USER1;
	}
	else
	{
		retval = IAP_HW_MODE_USER2;
	}

	return retval;
}

bool IAP_CheckApp(void)
{
	/*
	if(((*(__IO uint32_t*)UPDATE_APPLICATION_ADDR_START) & 0x2FFE0000) == 0x20000000)
	{
		return true;
	}
	*/

	return false;
}

void IAP_ExecApp(void)
{
	/*
	typedef void (*pFunction)(void);

	pFunction JumpToApplication;
	uint32_t  JumpAddress;

	IAP_DeInit();

	// Jump to user application
	JumpAddress       = *(__IO uint32_t*)(UPDATE_APPLICATION_ADDR_START + 4);
	JumpToApplication = (pFunction)JumpAddress;

	// Initialize user application's Stack Pointer
	__set_MSP(*(__IO uint32_t*) UPDATE_APPLICATION_ADDR_START);
	JumpToApplication();
	*/
}

void IAP_Update(void)
{
	/*
	while(iap_state != IAP_DOWNLOAD_FINISH)
	{
		// Process Network
		iap_network_length = CQueue_GetSize(BspUartInterrupt_GetQueue(BSP_UART_INTERRUPT_UART_PORT_5));
		if(iap_network_length > 0)
		{
			for(uint16_t i=0; i<iap_network_length; i++)
			{
				if(CQueue_Dequeue(BspUartInterrupt_GetQueue(BSP_UART_INTERRUPT_UART_PORT_5), &iap_network_byte) == CQUEUE_SUCCESS)
				{
					Network_Parse(&iap_network, iap_network_byte);
				}
			}
		}

		// Process - CUI
		if(iap_network.indexCUI > 0)
		{
			for(uint16_t i=0; i<iap_network.indexCUI; i++)
			{
				printf("%c", iap_network.bufferCUI[i]);
			}

			iap_network.indexCUI = 0;
		}

		// Process - GUI
		if(iap_network.indexGUI > 0)
		{
			for(uint16_t i=0; i<iap_network.indexGUI; i++)
			{
				GUI_parsePacket(GUI_PACKET_TARGET_GUI, iap_network.bufferGUI[i]);
			}

			iap_network.indexGUI = 0;
		}
	}
	*/

	iap_state = IAP_DOWNLOAD_INIT;
}

void IAP_GetSystemOption(void)
{
	/*
	uint32_t word;

	word            = FLASH_ReadWord(ADDR_FLASH_PAGE_109);
	iap_system_flag = (uint16_t)(word >> 16);
	iap_fw_checksum	= (uint16_t)(word      );
	iap_fw_size     = FLASH_ReadWord((ADDR_FLASH_PAGE_109 + 4));
	*/
}

void IAP_CheckSystemOption(void)
{
	printf("Check System-Option \r\n");
	/*
	IAP_GetSystemOption();
	if(iap_system_flag == 0xFFFF)
	{
		if(FLASH_Erase(ADDR_FLASH_PAGE_109, ADDR_FLASH_PAGE_110) == HAL_OK) // System Flag ÃÊ±âÈ­ µÇ¾î ÀÖÁö ¾ÊÀ» °æ¿ì
		{
			if(FLASH_WriteWord(ADDR_FLASH_PAGE_109, 0x00000000))            // System Flag ¿µ¿ª ÃÊ±âÈ­
			{
				printf("- Init \r\n");

				IAP_GetSystemOption();
			}
		}
	}
	*/
	printf("\r\n");

	printf("Infomation System-Option \r\n");
	printf("- System Flag\t: %04X \r\n", iap_system_flag);
	printf("- Checksum\t: %04X \r\n", iap_fw_checksum);
	printf("- FW Size\t: %d \r\n", (int)iap_fw_size);
	printf("\r\n");
}

bool IAP_DetectFalsificationFW(void)
{
	/*
	uint16_t checksum  = 0;
	uint32_t addr      = UPDATE_DOWNLOAD_ADDR_START;
	uint32_t word      = 0;

	for(uint16_t i=0; i<(iap_fw_size / 4); i++)
	{
		word = FLASH_ReadWord(addr);

		for(uint8_t j=0; j<4; j++)
		{
			checksum = GUI_stepCRC16(checksum, (uint8_t)(word >> (8 * j)));
		}

		addr += 4;
	}

	if(checksum == iap_fw_checksum)
	{
		return true;
	}
	*/

	return false;
}

void IAP_DownloadFW(void)
{
	/*
	iap_flash_page_count++;

	UPDATE_Download();
	*/

	printf("- Flash to download area\t:  [%d/%d] \r\n", iap_flash_page_count, iap_check_page_count);
}

void IAP_AckForReady_GUI(void)
{
	/*
	iap_content[0]    = 0x11;
	iap_contentLength = 1;

	iap_payloadLength = GUI_generatePayload(iap_payload, GUI_PAYLOAD_TYPE_UPDATE, iap_content, iap_contentLength);
	iap_packetLength  = GUI_generatePacket(iap_packet, GUI_PACKET_TARGET_AN_EMD_TA100L, iap_payload, iap_payloadLength);

	iap_size = Network_Generate(true, iap_buffer, iap_packet, iap_packetLength);

	HAL_UART_Transmit(&huart5, iap_buffer, iap_size, 1000);
	*/
}

void IAP_AckForSend_GUI(void)
{
	/*
	uint8_t idx = 0;

	iap_content[idx++]    = 0x12;
	iap_content[idx++]    = (uint8_t)(iap_partition_index >> 8);
	iap_content[idx++]    = (uint8_t)(iap_partition_index     );
	iap_content[idx++]    = iap_partition_size;
	iap_contentLength     = idx;

	iap_payloadLength = GUI_generatePayload(iap_payload, GUI_PAYLOAD_TYPE_UPDATE, iap_content, iap_contentLength);
	iap_packetLength  = GUI_generatePacket(iap_packet, GUI_PACKET_TARGET_AN_EMD_TA100L, iap_payload, iap_payloadLength);

	iap_size = Network_Generate(true, iap_buffer, iap_packet, iap_packetLength);

	HAL_UART_Transmit(&huart5, iap_buffer, iap_size, 1000);
	*/
}

/*******************************************************************************
 * Callback Functions
 ******************************************************************************/
void GUI_processUpdate(uint8_t *data, uint8_t data_size)
{
	/*
	printf("Content - Update \r\n");

	switch(data[0])
	{
		case 0x01 : // Ready
			printf(">> Ready \r\n");

			iap_state          = TASK_BL_DOWNLOAD_READY;
			iap_manufacture_id = ((uint32_t)data[1] << 24) | ((uint32_t)data[2] << 16) | ((uint32_t)data[3] << 8) | ((uint32_t)data[4]);
			iap_file_size      = ((uint32_t)data[5] << 24) | ((uint32_t)data[6] << 16) | ((uint32_t)data[7] << 8) | ((uint32_t)data[8]);
			iap_partition_unit = data[9];
			iap_file_select    = data[10];
			iap_file_crc       = ((uint16_t)data[11] << 8) | ((uint16_t)data[12]);
			iap_file_checkCRC  = ((uint16_t)data[13] << 8) | ((uint16_t)data[14]);

			iap_check_index_count = (iap_file_size / iap_partition_unit);
			if((iap_file_size % iap_partition_unit) > 0)
			{
				iap_check_index_count = iap_check_index_count + 1;
			}

			iap_check_page_count = (iap_file_size / UPDATE_MAX_BUFFER_SIZE);
			if((iap_file_size % UPDATE_MAX_BUFFER_SIZE) > 0)
			{
				iap_check_page_count = iap_check_page_count + 1;
			}

			printf("- Manufacture ID\t\t: 0x%08X \r\n"  , iap_manufacture_id);
			printf("- File Size\t\t\t: %d byte \r\n"    , iap_file_size);
			printf("- Partition Unit\t\t: %d byte \r\n" , iap_partition_unit);
			printf("- File Select\t\t\t: %d \r\n"       , iap_file_select);
			printf("- File CRC\t\t\t: 0x%04X \r\n"      , iap_file_crc);
			printf("- Index Count\t\t\t: %d \r\n"       , iap_check_index_count);
			printf("- Page Count\t\t\t: %d \r\n"        , iap_check_page_count);
			printf("\r\n");

			UPDATE_Open();

			printf(">> Download... \r\n");
			printf("\r\n");

			iap_flash_page_count = 0;

			iap_AckForReady_GUI();
			break;
		case 0x02 : // Send
			printf(">> Send \r\n");

			if(iap_state == TASK_BL_DOWNLOAD_READY)
			{
				iap_state = TASK_BL_DOWNLOAD_DOWNLOAD;
			}

			iap_partition_index  = ((uint16_t)data[1] << 8);
			iap_partition_index |= ((uint16_t)data[2]     );
			iap_partition_size   = data[3];

			printf("- Partition Index\t\t: %d \r\n"    , iap_partition_index);
			printf("- Partition Size\t\t: %d byte \r\n", iap_partition_size);

			if(UPDATE_Ready(&data[4], iap_partition_size))
			{
				iap_DownloadFW();
			}

			iap_AckForSend_GUI();

			if( ((iap_check_index_count - 1) == iap_partition_index) && ((iap_check_page_count - 1) == iap_flash_page_count))
			{
				iap_DownloadFW();



				uint32_t addr = UPDATE_DOWNLOAD_ADDR_START;
				uint32_t word = 0;
				uint16_t crc  = 0;
				uint8_t  cnt  = 0;

				for(uint32_t i=0; i<iap_file_size; i++)
				{
					if(cnt == 4)
					{
						cnt = 0;
					}

					if(cnt == 0)
					{
						word = FLASH_ReadWord(addr);

						addr += 4;
					}

					crc = GUI_stepCRC16(crc, (uint8_t)(word >> (8 * cnt)));

					cnt++;
				}
#if (TASK_BOOTLOADER_PRINT_CHECKSUM != 0)
				printf("- GUI CRC[0x%04X], FW CRC[0x%04X], Check CRC[0x%04X] \r\n", iap_file_crc, crc, iap_file_checkCRC);
#endif
				printf(">> Download Complete \r\n");

				if((crc == iap_file_crc) && (crc == iap_file_checkCRC))
				{
					printf(">> Flash to Firmware \r\n");

					iap_state = TASK_BL_DOWNLOAD_FLASH;

					switch(iap_file_select)
					{
						case 0 : // Application
							printf("- Application \r\n");

							UPDATE_UpdateApplication(iap_file_size);

							printf(">> Finish \r\n");

							iap_state = TASK_BL_DOWNLOAD_FINISH;

							break;
						default :
							printf(">> This firmware file is not application \r\n");
							break;
					}
				}
				else
				{
					if(iap_file_checkCRC != crc)
					{
						printf("\r\n");
						printf(">> Wrong Firmware Binary \r\n");
						printf("\r\n");
					}
				}
			}
			break;
		default :
			break;
	}
	*/
}

/**** EOF *********************************************************************/
