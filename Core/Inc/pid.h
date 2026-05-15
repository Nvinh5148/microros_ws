/*
 * pid.h
 *
 *  Created on: Nov 5, 2025
 *      Author: vinh
 */

#ifndef INC_PID_H_
#define INC_PID_H_

#include "user_define.h"
#include "stdint.h"
#include "stdlib.h"


typedef struct
{
  float dkp;
  float dki;
  float dkd;

  float dlim_min;
  float dlim_max;

  float dlim_max_int;
  float dlim_min_int;

  float dts;

  float derror;
  float dpre_error;
  float dfiltered_error;
  float dpre_filtered_error;

  float dproportional;
  float dintergral;
  float dderivative;

  float dresult;

} PID_CONTROL_t;

void pid_reset(PID_CONTROL_t *tpid_ctrl);
void pid_init(PID_CONTROL_t *tpid_ctrl, float dkp, float dki, float dkd, float dlimit_max, float dlimit_min, float dts);
void pid_tunning_set(PID_CONTROL_t *tpid_ctrl, float dkp, float dki, float dkd);
float lpf_trap(float draw_signal_value, float dpre_raw_signal_value, float dpre_filtered_value, float dfc, float dts);
float pid_compute(PID_CONTROL_t *tpid_ctrl, float dcmd_value, float dact_value);

#endif /* INC_PID_H_ */
