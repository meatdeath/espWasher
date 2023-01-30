#include "motor_pid.h"

long previousTime = 0, currentTime = 0, elapsedTime = 0;
double error = 0, cumError = 0, rateError = 0, lastError = 0;
double kp = 0, ki = 0, kd = 0;
void pidReset(){
    error = 0;
    cumError = 0;
    rateError = 0;
    lastError = 0;
    previousTime = millis();
}
void pidInit( double p, double i, double d ){
    kp = p;
    ki = i;
    kd = d;
    pidReset();
}
double pidCompute( double Setpoint, double input ){
    currentTime = millis();
    elapsedTime = (double)(currentTime - previousTime);

    error = Setpoint - input;
    cumError += error * elapsedTime;
    rateError = (error - lastError)/elapsedTime;

    double out = kp*error + ki*cumError + kd*rateError;

    lastError = error;
    previousTime = currentTime;

    return out;
}