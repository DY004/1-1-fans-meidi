/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "key.h"
#include "w25qxx.h"
#include <stdio.h>// 包含标准输入输出头文件
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

/* USER CODE BEGIN PV */

//SPI_HandleTypeDef hspi1;

//UART_HandleTypeDef huart1;


uint16_t device_id;
uint8_t write_buf[]= {"duwiewei"};
#define SIZE sizeof(write_buf)
uint8_t read_buf[SIZE];
int i;
uint32_t FLASH_SIZE;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int key =0;



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* USER CODE BEGIN 1 */
    FLASH_SIZE=16*1024*1024;



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
    MX_TIM2_Init();
    MX_TIM3_Init();
    MX_TIM4_Init();
    MX_SPI1_Init();
    MX_USART1_UART_Init();

    /* Initialize interrupts */
    MX_NVIC_Init();
    /* USER CODE BEGIN 2 */
    W25QXX_Init();

    HAL_GPIO_WritePin(GPIOC, POWER_CTR_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, BEEP_Pin, GPIO_PIN_SET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(GPIOC, BEEP_Pin, GPIO_PIN_RESET);

//    device_id = W25QXX_ReadID();
//    printf("W25Q16 Device ID is 0x%04x\r\n", device_id);

    /* 为了验证，首先读取要写入地址处的数据 */
//    printf("-------- read data before write -----------\r\n");
//    W25QXX_Read(read_buf, 0, 10);

//    for(i = 0; i < 10; i++)
//    {
//        printf("[0x%08x]:0x%02x\r\n", i, *(read_buf+i));
//    }

//    /* 擦除该扇区 */
//    printf("-------- erase sector 0 -----------\r\n");
//    W25QXX_Erase_Sector(0);

//    /* 再次读数据 */
//    printf("-------- read data after erase -----------\r\n");
//    W25QXX_Read(read_buf, 0, 10);
//    for(i = 0; i < 10; i++)
//    {
//        printf("[0x%08x]:0x%02x\r\n", i, *(read_buf+i));
//    }

//    /* 擦除该扇区 */
//    printf("-------- erase sector 0 -----------\r\n");
//    W25QXX_Erase_Sector(0);

//    /* 再次读数据 */
//    printf("-------- read data after erase -----------\r\n");
//    W25QXX_Read(read_buf, 0, 10);
//    for(i = 0; i < 10; i++)
//    {
//        printf("[0x%08x]:0x%02x\r\n", i, *(read_buf+i));
//    }

    /* 写数据 */
//    printf("-------- write data -----------\r\n");
//	for(i = 0; i < 10; i++)
//    {
//        printf("%d\r\n", *(write_buf+i));
//
//	}
//
//    for(i = 0; i < 10; i++)
//    {
//        write_buf[i] = i;
//    }
//	W25QXX_Write((u8*)write_buf,FLASH_SIZE-100,SIZE) ;
//	HAL_UART_Transmit(&huart1,(uint8_t*)write_buf,SIZE,1000);
//	printf("\r\n");
//	printf("%d\n", *write_buf);

    /* 再次读数据 */
    printf("-------- read data after write -----------\r\n");
//	W25QXX_Read((u8*)read_buf,100,100) ;
    W25QXX_Read(read_buf, FLASH_SIZE-300, SIZE);

//    for(i = 0; i < 10; i++)
//    {
//        printf("%d", *(read_buf+i));
//
//	}

    HAL_UART_Transmit(&huart1,(uint8_t*)read_buf,SIZE,1000);

    if(read_buf[0] == 'a')
    {
        a = 4, b =3;
//        HAL_GPIO_WritePin(GPIOG, LED0_Pin|LED1_Pin, GPIO_PIN_RESET);
        TIM_SetTIM4Compare1(10000);//风类-清凉-2级
    }

    else if(read_buf[0] == 'b')
    {
        a = 4, b =2;
//        HAL_GPIO_WritePin(GPIOG, LED0_Pin|LED1_Pin, GPIO_PIN_RESET);
        TIM_SetTIM4Compare1(12000);//风类-清凉-3级
    }

    else if(read_buf[0] == 'c')
    {
        a = 4, b =4;
//        HAL_GPIO_WritePin(GPIOG, LED0_Pin|LED1_Pin, GPIO_PIN_RESET);
        TIM_SetTIM4Compare1(8000);//风类-清凉-1级
    }

    if(read_buf[0] == 'd')
    {
        a = 3, b1 =3;
//        HAL_GPIO_WritePin(GPIOG, LED0_Pin|LED1_Pin, GPIO_PIN_RESET);
        TIM_SetTIM4Compare1(15000);//风类-清凉-2级
    }

    else if(read_buf[0] == 'e')
    {
        a = 3, b1 =2;
//        HAL_GPIO_WritePin(GPIOG, LED0_Pin|LED1_Pin, GPIO_PIN_RESET);
        TIM_SetTIM4Compare1(17000);//风类-清凉-3级
    }

    else if(read_buf[0] == 'f')
    {
        a = 3, b1 =4;
//        HAL_GPIO_WritePin(GPIOG, LED0_Pin|LED1_Pin, GPIO_PIN_RESET);
        TIM_SetTIM4Compare1(13000);//风类-清凉-1级
    }

    if(read_buf[0] == 'g')
    {
        a = 2, b2 =3;
//        HAL_GPIO_WritePin(GPIOG, LED0_Pin|LED1_Pin, GPIO_PIN_RESET);
        TIM_SetTIM4Compare1(20000);//风类-清凉-2级
    }

    else if(read_buf[0] == 'h')
    {
        a = 2, b2 =4;
//        HAL_GPIO_WritePin(GPIOG, LED0_Pin|LED1_Pin, GPIO_PIN_RESET);
        TIM_SetTIM4Compare1(18000);//风类-清凉-3级
    }

    else if(read_buf[0] == 'j')
    {
        a = 5;
//        HAL_GPIO_WritePin(GPIOG, LED0_Pin|LED1_Pin, GPIO_PIN_RESET);
        TIM_SetTIM4Compare1(4000);//风类-清凉-3级
    }



    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */

    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

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
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
    /* TIM2_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
    /* TIM3_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
    /* TIM4_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM4_IRQn);
    /* EXTI15_10_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
    /* EXTI1_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(EXTI1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI1_IRQn);
    /* EXTI0_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
