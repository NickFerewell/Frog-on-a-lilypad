#include "PIDController.hpp"
// #include <math.h>
#include "utilities.hpp"

PIDController::PIDController(float Kp, float Ki, float Kd, float dt){
        dt_ = dt;
        Kp_ = Kp;
        Ki_ = Ki;
        Kd_ = Kd;
}

PIDController::~PIDController(){}

float PIDController::calculate(float value, float target, float dt = 1){
    if (dt == 1)
    {
        dt = dt_;
    }
    
    float error = target - value;

    float P = Kp_ * error;

    integral += error * dt;
    float I = Ki_ * integral;

    float derivative = (error - prevError)/dt;
    float D = Kd_ * derivative;
    
    float output = P + I + D;

    prevError = error;

    return output;
};

RController::RController(float speed = 1.0f){
    speed_ = speed;
}

RController::~RController(){}

float RController::calculate(float value, float target, int deltaTime){
    return value + utils::signum(target - value) * utils::min(speed_, abs(target-value)) * deltaTime;
}

float RController::getIncrement(float value, float target){
    return utils::signum(target - value)* utils::min(speed_, (float)abs(target-value));
}