/*
 * use_define.h
 *
 *  Created on: Nov 5, 2025
 *      Author: vinh
 */

#ifndef INC_USER_DEFINE_H_
#define INC_USER_DEFINE_H_

#define IN1_Pin        GPIO_PIN_1
#define IN1_GPIO_Port  GPIOD

#define IN2_Pin        GPIO_PIN_2
#define IN2_GPIO_Port  GPIOD

#define IN3_Pin        GPIO_PIN_3
#define IN3_GPIO_Port  GPIOD

#define IN4_Pin        GPIO_PIN_4
#define IN4_GPIO_Port  GPIOD


#define IN5_Pin        GPIO_PIN_5
#define IN5_GPIO_Port  GPIOD

#define IN6_Pin        GPIO_PIN_6
#define IN6_GPIO_Port  GPIOD


#include "main.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;


#define SAMPLING_TIME 0.01f // In second
#define NUMBER_OF_DEGREES_ON_A_CIRCLE 360.0f
#define THOUSAND 1000
#define ZERO 0.0f
// Timer






// motor
#define PPR 4436.0f
#define PPR_1 180000.0f
#define MAX_VELOCITY 7
#define WHEEL_RADIUS 0.15f // 3cm
#define WHEEL_CIRCUMFERENCE (2.0f * 3.1415926f * WHEEL_RADIUS)
// UART


// PID
#define PID_CONTROLLER_LIMIT_MAX (htim4.Init.Period)
#define PID_CONTROLLER_LIMIT_MIN -(float)(htim4.Init.Period)

#define CUT_OFF_FREQUENCY 10



#endif /* INC_USER_DEFINE_H_ */
