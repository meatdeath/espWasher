#ifndef __PID_H__
#define __PID_H__

#include <Arduino.h>

void pidInit( double p, double i, double d );
void pidReset();
double pidCompute( double Setpoint, double input );

#endif // __PID_H__
