/*
 * motor.h
 *
 *  Created on: Nov 5, 2025
 *      Author: vinh
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "pid.h"
#include "user_define.h"


typedef struct
{
  uint32_t ipulse_per_round;
  int16_t icounter;
  float dvelocity;
  float dposition;
  float dreference_velocity;
  float dreference_position;
  int32_t last_count;
} Motor_t;

void motor_init(Motor_t *tmotor, uint32_t ipulse);
void motor_reset(Motor_t *tmotor);
void motor_read_encoder(Motor_t *tmotor, TIM_HandleTypeDef *htim);
void ReadEncoder(Motor_t *tmotor, TIM_HandleTypeDef *htim);
void MotorSetDuty1( int duty);
void MotorSetDuty2( int duty);
void MotorSetDuty3( int duty);
void motor_set_duty(int32_t iduty);


float MotorPIDVelocity(Motor_t *tmotor, PID_CONTROL_t *tpid_ctrl, float dvelocity);
float MotorPIDPosition(Motor_t *tmotor, PID_CONTROL_t *tpid_ctrl, float dposition);

#endif /* INC_MOTOR_H_ */
