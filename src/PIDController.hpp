#pragma once

class PIDController{
public:
    float dt_;
    float Kp_;
    float Ki_;
    float Kd_;
    float prevError = 0.0f;
    float integral = 0.0f; //Интеграл от 0 до контроллируемой переменной


    PIDController(float Kp, float Ki, float Kd, float dt);

    ~PIDController();

    float calculate(float value, float target, float dt);
};

class RController{//Релейный контроллер, улучшенный
public:
    float speed_;


    RController(float speed);
    ~RController();

    float calculate(float value, float target, int deltaTime);

    float getIncrement(float value, float target);
};