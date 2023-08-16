#ifndef TORPEDO_H
#define TORPEDO_H
#include <cmath>
#include <cstdlib>
#include <iostream>



class Torpedo {

    private:
        double x = 0, y = 0;
        double course_deg;
        double speed_ms;
        double temp_deg=0;
    public:
        static constexpr double dt = 0.2;
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


//Setters for course and speed;

//Getters for everything;

public:
    void update() {

        double difference1 = fabs(course_deg-getTemp_Deg());
        double difference2 = fabs(360-difference1);
        if(difference1 ==0 || difference1<=5 || difference2<=5){
            temp_deg=course_deg;
        }
        else if(difference1 <=difference2){
            if(course_deg-temp_deg<0){
                temp_deg-=5;

            }
            else if(course_deg-temp_deg>0){
                temp_deg+=5;

            }
        }
        else if (difference2 <= difference1){
            if(course_deg - temp_deg<0){
                temp_deg+=5;
            }
            else if(course_deg - temp_deg>0){
                temp_deg-=5;
            }




        }
        if(temp_deg <0 && temp_deg ==360){
            temp_deg = 360- temp_deg;

        }



        y = y + std::sin(getTemp_Deg() *3.14/ 180) * speed_ms * dt*0.514444444;
        x = x + std::cos(getTemp_Deg() * 3.14/ 180) * speed_ms * dt*0.514444444;
    }

};
#endif
