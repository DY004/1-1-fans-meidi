/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
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
#include "tim.h"

/* USER CODE BEGIN 0 */

#include "gpio.h"
#include "stm32f4xx_it.h"
#include "w25qxx.h"


uint32_t time_cnt1 = 0;
uint32_t time_cnt2 = 0;
uint32_t time_cnt3 = 0;
uint32_t time_cnt4 = 0;
uint32_t time_cnt5 = 0;
uint32_t time_cnt6 = 0;
uint32_t time_cnt7 = 0;

/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

/* TIM2 init function */
void MX_TIM2_Init(void)
{

    /* USER CODE BEGIN TIM2_Init 0 */

    /* USER CODE END TIM2_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM2_Init 1 */

    /* USER CODE END TIM2_Init 1 */
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 72-1;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 5000-1;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM2_Init 2 */
    HAL_TIM_Base_Start_IT(&htim2);

    /* USER CODE END TIM2_Init 2 */

}
/* TIM3 init function */
void MX_TIM3_Init(void)//MX_TIM3_Init是挂在APB1上，时钟是APB2的一半，请切记。
{

    /* USER CODE BEGIN TIM3_Init 0 */

    /* USER CODE END TIM3_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM3_Init 1 */

    /* USER CODE END TIM3_Init 1 */
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 36-1;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 5000-1;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM3_Init 2 */
    HAL_TIM_Base_Start_IT(&htim3);

    /* USER CODE END TIM3_Init 2 */

}
/* TIM4 init function */
void MX_TIM4_Init(void)
{

    /* USER CODE BEGIN TIM4_Init 0 */

    /* USER CODE END TIM4_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};
    TIM_OC_InitTypeDef sConfigOC = {0};

    /* USER CODE BEGIN TIM4_Init 1 */

    /* USER CODE END TIM4_Init 1 */
    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 72-1;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 20000-1;
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM4_Init 2 */
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);


    /* USER CODE END TIM4_Init 2 */
    HAL_TIM_MspPostInit(&htim4);

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

    if(tim_baseHandle->Instance==TIM2)
    {
        /* USER CODE BEGIN TIM2_MspInit 0 */

        /* USER CODE END TIM2_MspInit 0 */
        /* TIM2 clock enable */
        __HAL_RCC_TIM2_CLK_ENABLE();
        /* USER CODE BEGIN TIM2_MspInit 1 */

        /* USER CODE END TIM2_MspInit 1 */
    }
    else if(tim_baseHandle->Instance==TIM3)
    {
        /* USER CODE BEGIN TIM3_MspInit 0 */

        /* USER CODE END TIM3_MspInit 0 */
        /* TIM3 clock enable */
        __HAL_RCC_TIM3_CLK_ENABLE();
        /* USER CODE BEGIN TIM3_MspInit 1 */

        /* USER CODE END TIM3_MspInit 1 */
    }
    else if(tim_baseHandle->Instance==TIM4)
    {
        /* USER CODE BEGIN TIM4_MspInit 0 */

        /* USER CODE END TIM4_MspInit 0 */
        /* TIM4 clock enable */
        __HAL_RCC_TIM4_CLK_ENABLE();
        /* USER CODE BEGIN TIM4_MspInit 1 */

        /* USER CODE END TIM4_MspInit 1 */
    }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(timHandle->Instance==TIM4)
    {
        /* USER CODE BEGIN TIM4_MspPostInit 0 */

        /* USER CODE END TIM4_MspPostInit 0 */

        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**TIM4 GPIO Configuration
        PB6     ------> TIM4_CH1
        */
        GPIO_InitStruct.Pin = FAN1_Pin;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
        HAL_GPIO_Init(FAN1_GPIO_Port, &GPIO_InitStruct);

        /* USER CODE BEGIN TIM4_MspPostInit 1 */

        /* USER CODE END TIM4_MspPostInit 1 */
    }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

    if(tim_baseHandle->Instance==TIM2)
    {
        /* USER CODE BEGIN TIM2_MspDeInit 0 */

        /* USER CODE END TIM2_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_TIM2_CLK_DISABLE();

        /* TIM2 interrupt Deinit */
        HAL_NVIC_DisableIRQ(TIM2_IRQn);
        /* USER CODE BEGIN TIM2_MspDeInit 1 */

        /* USER CODE END TIM2_MspDeInit 1 */
    }
    else if(tim_baseHandle->Instance==TIM3)
    {
        /* USER CODE BEGIN TIM3_MspDeInit 0 */

        /* USER CODE END TIM3_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_TIM3_CLK_DISABLE();

        /* TIM3 interrupt Deinit */
        HAL_NVIC_DisableIRQ(TIM3_IRQn);
        /* USER CODE BEGIN TIM3_MspDeInit 1 */

        /* USER CODE END TIM3_MspDeInit 1 */
    }
    else if(tim_baseHandle->Instance==TIM4)
    {
        /* USER CODE BEGIN TIM4_MspDeInit 0 */

        /* USER CODE END TIM4_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_TIM4_CLK_DISABLE();

        /* TIM4 interrupt Deinit */
        HAL_NVIC_DisableIRQ(TIM4_IRQn);
        /* USER CODE BEGIN TIM4_MspDeInit 1 */

        /* USER CODE END TIM4_MspDeInit 1 */
    }
}

/* USER CODE BEGIN 1 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

//	if(htim->Instance == TIM2)
//	{
//

//		if(++time_cnt1 >= 2)
//		{
//			time_cnt1 = 0;
//			if(HAL_GPIO_ReadPin(GPIOC,POWER_ON_OFF_Pin) == GPIO_PIN_RESET)
//			{
//
//				if(HAL_GPIO_ReadPin(GPIOC,POWER_ON_OFF_Pin) == GPIO_PIN_RESET)
//				{
//					HAL_GPIO_WritePin(GPIOC,POWER_CTR_Pin,GPIO_PIN_RESET);
//
//				}
//
//			}
//
//		}
//

//	}

    if(htim->Instance == TIM3)//5ms一次定时器中断
    {
		
	
        if(d == 1)//定时10s
        {
            HAL_GPIO_WritePin(GPIOG,LED0_Pin,GPIO_PIN_RESET);//LED0灯状态
			

			
            ++time_cnt1;
            if(time_cnt1 >= 2000)
            {
                time_cnt1 = 0;		
				HAL_GPIO_WritePin(GPIOC,POWER_CTR_Pin, GPIO_PIN_RESET);				
              
            }
        }

        else if(d == 2)//定时20s
        {
            HAL_GPIO_WritePin(GPIOG,LED1_Pin,GPIO_PIN_RESET);//LED1灯状态
            ++time_cnt2;
            if(time_cnt2 >= 4000)
            {
                time_cnt2 = 0;
                HAL_GPIO_WritePin(GPIOC,POWER_CTR_Pin, GPIO_PIN_RESET);
            }
        }

        else if(d == 3)//定时30s
        {

            HAL_GPIO_WritePin(GPIOG,LED0_Pin,GPIO_PIN_SET);//LED0灯状态
            ++time_cnt3;
            if(++time_cnt3 >= 6000)
            {
                time_cnt3 = 0;
                HAL_GPIO_WritePin(GPIOC,POWER_CTR_Pin, GPIO_PIN_RESET);
            }
        }

        else if(d == 4)//定时40s
        {
            HAL_GPIO_WritePin(GPIOG,LED1_Pin,GPIO_PIN_SET);//LED1灯状态
            ++time_cnt4;
            if(time_cnt4 >= 8000)
            {
                time_cnt4 = 0;
                HAL_GPIO_WritePin(GPIOC,POWER_CTR_Pin, GPIO_PIN_RESET);
            }
        }

        else if(d == 5)//定时50s
        {

            HAL_GPIO_WritePin(GPIOG,LED1_Pin,GPIO_PIN_RESET);//LED1灯状态
            ++time_cnt5;
            if(time_cnt5 >= 10000)
            {
                time_cnt5 = 0;
                HAL_GPIO_WritePin(GPIOC,POWER_CTR_Pin, GPIO_PIN_RESET);
            }
        }

        else if(d == 6)//定时60s
        {
            HAL_GPIO_WritePin(GPIOG,LED0_Pin,GPIO_PIN_RESET);//LED0灯状态
            ++time_cnt6;
            if(time_cnt6 >= 12000)
            {
                time_cnt6 = 0;
                HAL_GPIO_WritePin(GPIOC,POWER_CTR_Pin, GPIO_PIN_RESET);
            }
        }

        else if(d == 7)//定时70s
        {
            HAL_GPIO_WritePin(GPIOG,LED0_Pin|LED1_Pin,GPIO_PIN_SET);//LED1灯状态
            ++time_cnt7;
            if(time_cnt7 >= 14000)
            {
                time_cnt7 = 0;
                HAL_GPIO_WritePin(GPIOC,POWER_CTR_Pin, GPIO_PIN_RESET);
            }
        }
		
		
		
		
		




    }


}

//设置TIM4通道1的占空比
//compare:比较值
void TIM_SetTIM4Compare1(uint32_t compare)
{
    TIM4->CCR1=compare;
}

/* USER CODE END 1 */
