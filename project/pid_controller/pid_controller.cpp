/**********************************************
 * Self-Driving Car Nano-degree - Udacity
 *  Created on: December 11, 2020
 *      Author: Mathilde Badoual
 **********************************************/

#include "pid_controller.h"
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kpi, double Kii, double Kdi, double output_lim_maxi, double output_lim_mini) {
   /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   **/
   Kp = Kpi;
   Ki = Kii;
   Kd = Kdi;
   output_lim_max = output_lim_maxi;
   output_lim_min = output_lim_mini;
   cte_ = 0.0;
   diff_cte = 0.0;
   int_cte = 0.0;
   iteration = 0;
   
}


void PID::UpdateError(double cte) {
   /**
   * TODO: Update PID errors based on cte.
   **/
  if (!iteration)
    diff_cte = 0.0;
  else {
    diff_cte = cte - prev_cte;
    int_cte += cte;
  }
  prev_cte = cte;
  cte_ = cte;
  iteration++;
}

double PID::TotalError() {
   /**
   * TODO: Calculate and return the total error
    * The code should return a value in the interval [output_lim_mini, output_lim_maxi]
   */
    double control = Kp * cte_ + Kd * diff_cte / delta_time + Ki * int_cte * delta_time;
    control = min(control, output_lim_max);
    control = max(control, output_lim_min);
    return control;
}

double PID::UpdateDeltaTime(double new_delta_time) {
   /**
   * TODO: Update the delta time with new value
   */
   delta_time = new_delta_time;
   return delta_time;
}
