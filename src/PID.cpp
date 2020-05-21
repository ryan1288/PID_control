#include "PID.h"

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  // PID Coefficients 
  this->Kp = Kp_;
  this->Ki = Ki_;
  this->Kd = Kd_;
  
  // Initialize error integral/sum to 0
  this->cte_sum = 0;
  
  // For the first time step, the previous cross track error is set to 0
  this->prev_cte = 0;
}

void PID::UpdateError(double cte) {
  // Update PID errors using the appropriate equations
  double diff_cte = cte - this->prev_cte;
  this->prev_cte = cte;
  this->p_error = -this->Kp * cte;
  this->i_error = -this->Ki * this->cte_sum;
  this->d_error = -this->Kd * diff_cte;
}

double PID::TotalError() {
  // Return the total error
  return p_error + i_error + d_error;
}