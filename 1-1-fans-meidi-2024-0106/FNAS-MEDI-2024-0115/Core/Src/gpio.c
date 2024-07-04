/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "key.h"
#include "tim.h"
#include "w25qxx.h"
#include "main.h"
#include <stdio.h>// 包含标准输入输出头文件

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

uint16_t a = 5;
uint16_t b = 4;
uint16_t b1 = 4;
uint16_t b2 = 4;
uint8_t c[2]= {'1'};//这是是关机前存储风扇模式的值
uint16_t d = 0;//这是风扇定时的的初始值
//static uint16_t key_lock;

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, BEEP_Pin|POWER_CTR_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOG, LED0_Pin|LED1_Pin, GPIO_PIN_SET);

    /*Configure GPIO pins : PAPin PAPin */
    GPIO_InitStruct.Pin = YAOTOU_Pin|DINGSHI_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin = SPI1_CS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(SPI1_CS_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : PCPin PCPin */
    GPIO_InitStruct.Pin = BEEP_Pin|POWER_CTR_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : PEPin PEPin */
    GPIO_InitStruct.Pin = KEY1_Pin|KEY2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin = POWER_ON_OFF_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(POWER_ON_OFF_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : PGPin PGPin */
    GPIO_InitStruct.Pin = LED0_Pin|LED1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(KEY2 == GPIO_PIN_RESET)//风类
    {

//        HAL_GPIO_TogglePin(GPIOG,LED0_Pin);
        a--;

        if(a == 4)
        {
            TIM_SetTIM4Compare1(8000);//风类-清凉
        }
        else if(a == 3)
        {
            TIM_SetTIM4Compare1(13000);//风类-送风
        }
        else if(a == 2)
        {
            TIM_SetTIM4Compare1(18000);//风类-睡眠
        }

        if(a == 1)
        {
            TIM_SetTIM4Compare1(4000);//风类-静音
            a = 5;
        }

    }

    else if(KEY1 == GPIO_PIN_RESET)//风速
    {

//        HAL_GPIO_TogglePin(GPIOG,LED1_Pin);

        if(a == 4)//风类-清凉
        {
            b--;
            if(a == 4 && b == 3)
            {
                TIM_SetTIM4Compare1(10000);//风类-清凉-2级
			

            }
            else if(a == 4 && b == 2)//风类-清凉-3级
            {
                TIM_SetTIM4Compare1(12000);//风类-清凉-3级
				
            }
            else if(a == 4 && b == 1)//风类-清凉-1级
            {
                TIM_SetTIM4Compare1(8000);//风类-清凉-1级
			
            }


            if(b == 1)
            {
                b = 4;
            }
        }

        else if(a == 3)//风类-送风
        {
            b1--;
            if(a == 3 && b1 == 3)
            {
                TIM_SetTIM4Compare1(15000);//风类-送风-2级
			

            }
            else if(a == 3 && b1 == 2)//风类-送风
            {
                TIM_SetTIM4Compare1(17000);//送风-送风-3级
			
            }
            else if(a == 3 && b1 == 1)//风类-送风
            {
                TIM_SetTIM4Compare1(13000);//风类-送风-1级
			
            }

            if(b1 == 1)
            {
                b1 = 4;
            }
        }

        else if(a == 2)//风类-睡眠
        {
            b2--;
            if(a == 2 && b2 == 3)
            {
                TIM_SetTIM4Compare1(20000);//风类-睡眠-2级
		

            }
            else if(a == 2 && b2 == 2)//风类-睡眠
            {
                TIM_SetTIM4Compare1(18000);//送风-睡眠-1级
		
            }

            if(b2 == 2)
            {
                b2 = 4;
            }
        }

    }






    else if(KEY0 == GPIO_PIN_RESET)
    {
        //把关机前的风扇的风类和风速保存到flash中，以便在正常开机的时候，可以右记忆功能。
        if(a == 4 )
        {
            if(b == 3)
            {   c[0] = 'a';
                W25QXX_Write(c,FLASH_SIZE-300,300);

            }
            else if(a == 4 && b == 2)
            {
                c[0] = 'b';
                W25QXX_Write(c,FLASH_SIZE-300,300);
            }
            else if(a == 4 && b == 4)
            {
                c[0] = 'c';
                W25QXX_Write(c,FLASH_SIZE-300,300);
            }

        }

        else if(a == 3 )
        {
            if(b1 == 3)
            {   c[0] = 'd';
                W25QXX_Write(c,FLASH_SIZE-300,300);

            }
            else if(b1 == 2)
            {
                c[0] = 'e';
                W25QXX_Write(c,FLASH_SIZE-300,300);
            }
            else if( b1 == 4)
            {
                c[0] = 'f';
                W25QXX_Write(c,FLASH_SIZE-300,300);
            }

        }

        else if(a == 2 )
        {
            if(b2 == 3)
            {   c[0] = 'g';
                W25QXX_Write(c,FLASH_SIZE-300,300);

            }
            else if(b2 == 4)
            {
                c[0] = 'h';
                W25QXX_Write(c,FLASH_SIZE-300,300);
            }

        }

        else if(a == 1 ||a == 5)
        {
            c[0] = 'j';
            W25QXX_Write(c,FLASH_SIZE-300,300);

        }

        HAL_GPIO_WritePin(GPIOC,POWER_CTR_Pin, GPIO_PIN_RESET);

    }

    /***风扇的摇头，按键外部中断***/
    else if(YAOT == GPIO_PIN_RESET)
    {
        HAL_GPIO_TogglePin(GPIOC, BEEP_Pin);
    }

    /***风扇的定时，按键外部中断***/
    if(DINGS == GPIO_PIN_RESET)
    {
        if(DINGS ==GPIO_PIN_RESET)
        {
            ++d;
            if(d == 8)
            {
                d = 0;
            }
        }
    }



}


/* USER CODE END 2 */
