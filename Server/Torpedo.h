#ifndef TORPEDO_H
#define TORPEDO_H
#include <cmath>
#include <cstdlib>
#include <iostream>
class Torpedo {
    private:
        double x = 0, y = 0;
        double course_deg=0;
        double speed_ms=0;
        double temp_deg=0;
        double dt=0;
    public:
        void set_dt(double dt){
             std::cout << "DTO constructor called with Torpedo at: " << this<<std::endl;
            this->dt=dt;
        }
        double get_dt(){
            return this->dt;
        }
        double getX(){
            return x;
        }
        double getY(){
            return y;
        }
        double getCourse_deg(){
            return course_deg;
        }
        double getSpeed_ms(){
            return speed_ms;
        }
        double getTemp_Deg(){
            return temp_deg;
        }
        void setCourse(double course){
            this->course_deg=course;
        }
        void setSpeed(double speed){
            this->speed_ms = speed;
        }
        void setTemp_Deg(double temp){
            this->temp_deg=temp;
        }
public:
    void update() {
        if(course_deg<0){
            course_deg +=360;
        }
        if(course_deg>=360){
            course_deg = fmod(course_deg,360);
        }
        double difference1 = fabs(course_deg-getTemp_Deg());
        double difference2 = fabs(360-difference1);
        if(difference1 ==0 || difference1<30 || difference2<30){
            temp_deg=course_deg;
        }
        else if(difference1 <=difference2){
            if(course_deg-temp_deg<0){
                temp_deg-=30*dt;
            }
            else if(course_deg-temp_deg>0){
                temp_deg+=30*dt;
            }
        }
        else if (difference2 < difference1){
            if(course_deg - temp_deg<0){

                temp_deg+=30*dt;
            }
            else if(course_deg - temp_deg>0){
                temp_deg-=30*dt;
            }
        }
        if(temp_deg <0 || temp_deg >=360){

            temp_deg = std::fmod(temp_deg, 360);
                   if (temp_deg < 0) {
                       temp_deg += 360;
                   }
        }
        std::cout<<"sa\n";
        y = y + std::sin(getTemp_Deg() *3.14/ 180.00) * speed_ms * dt;
        x = x + std::cos(getTemp_Deg() * 3.14/ 180.00) * speed_ms * dt;
    }
};
#endif
