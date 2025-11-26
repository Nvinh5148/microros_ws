/*
 * motor.c
 *
 *  Created on: Nov 5, 2025
 *      Author: vinh
 */

#include "motor.h"


void motor_init(Motor_t *tmotor, uint32_t ipulse)
{
    if (tmotor == NULL)
    {
        // Handle null pointer error
        return;
    }

    motor_reset(tmotor);
    tmotor->ipulse_per_round = ipulse;
    HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
}
void motor_reset(Motor_t *tmotor)
{
    if (tmotor == NULL)
    {
        // Handle null pointer error
        return;
    }
    tmotor->icounter = 0;
    tmotor->dvelocity = 0.0f;
    tmotor->dposition = 0.0f;
    tmotor->dreference_velocity = 0.0f;
    tmotor->dreference_position = 0.0f;
    tmotor->last_count = 0;
}

void motor_read_encoder(Motor_t *tmotor, TIM_HandleTypeDef *htim)
{
	if (tmotor == NULL || htim == NULL)
	    {
	        // Handle null pointer error
	        return;
	    }
    int32_t count = __HAL_TIM_GET_COUNTER(htim);
    int32_t diff = count - tmotor->last_count;
    if (diff > 32768)
        diff -= 65536;
    else if (diff < -32768)
        diff += 65536;
    tmotor->icounter = count;
    tmotor->last_count = count;
    // diff/PPR = số vòng quay trong một chu kỳ
    float rev = (float)diff / (float)tmotor->ipulse_per_round;
    // Vận tốc tuyến tính (m/s)
    tmotor->dvelocity = rev / SAMPLING_TIME * WHEEL_CIRCUMFERENCE;
    tmotor->dposition += rev * NUMBER_OF_DEGREES_ON_A_CIRCLE * DEG_TO_RAD;
}

void MotorSetDuty1(int nDuty)
{
	if (nDuty > 4200) nDuty = 4200;
	if (nDuty < -4200) nDuty = -4200;

	if (nDuty >= 0)
	{
    HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, nDuty);
	}
	else
	{
    HAL_GPIO_WritePin(IN1_GPIO_Port, IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN2_GPIO_Port, IN2_Pin, GPIO_PIN_SET);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, abs(nDuty));
	}
}
void MotorSetDuty2(int nDuty)
{
	if (nDuty > 4200) nDuty = 4200;
	if (nDuty < -4200) nDuty = -4200;

	if (nDuty >= 0)
	{
    HAL_GPIO_WritePin(IN3_GPIO_Port, IN5_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(IN4_GPIO_Port, IN6_Pin, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, nDuty);
	}
	else
	{
    HAL_GPIO_WritePin(IN3_GPIO_Port, IN5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN4_GPIO_Port, IN6_Pin, GPIO_PIN_SET);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, abs(nDuty));
	}
}


void MotorSetDuty3(int nDuty)
{
	if (nDuty > 4200) nDuty = 4200;
	if (nDuty < -4200) nDuty = -4200;

	if (nDuty >= 0)
	{
    HAL_GPIO_WritePin(IN5_GPIO_Port, IN3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(IN6_GPIO_Port, IN4_Pin, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, nDuty);
	}
	else
	{
    HAL_GPIO_WritePin(IN5_GPIO_Port, IN3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(IN6_GPIO_Port, IN4_Pin, GPIO_PIN_SET);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, abs(nDuty));
	}
}



float MotorPIDVelocity(Motor_t *tmotor, PID_CONTROL_t *tpid_ctrl, float dvelocity)
{
	tmotor->dreference_velocity = dvelocity;
	float duty = pid_compute(tpid_ctrl, tmotor->dreference_velocity, tmotor->dvelocity);
	return duty;
}

float MotorPIDPosition(Motor_t *tmotor, PID_CONTROL_t *tpid_ctrl, float dposition)
{
	tmotor->dreference_position = dposition;
	float duty = pid_compute(tpid_ctrl, tmotor->dreference_position, tmotor->dposition);
	return duty;
}






