#ifndef TARGET_H
#define TARGET_H
#include <cmath>
#include <cstdlib>
#include <iostream>



class Target {

    private:
        double x = 0, y = 0;
        double course_deg=0;
        double temp_deg=0;
        double speed_ms=0;
        double dt=0;
    public:
        bool targetActive = true;
        void set_dt(double dt){
            std::cout<<" i am in target set_dt \n";
             std::cout << "DTO constructor called with Target at: " << this<<this<<std::endl;
            this->dt=dt;
            std::cout<<" dt is in target "<<get_dt()<<std::endl;
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
        double getTemp_Deg(){
            return temp_deg;
        }
        void setTemp_Deg(double temp){
            this->temp_deg=temp;
        }
        void setX(double x ){
            this->x=x;
        }
        void setY(double y){
            this->y=y;
        }
        double getCourse_deg(){
            if(course_deg>=360){
                course_deg = fmod(course_deg,360);
            }
            return course_deg;
        }
        double getSpeed_ms(){
            return speed_ms;
        }

        void setCourse(double course){
            this->course_deg=course;
        }
        void setSpeed(double speed){
            this->speed_ms = speed;
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
                       }}
            std::cout<< " i am in target.update()\n";
            y = y + std::sin(getTemp_Deg() *3.14/ 180.00) * speed_ms * dt;
            x = x + std::cos(getTemp_Deg() * 3.14/ 180.00) * speed_ms * dt;


        }


};

#endif // TARGET_H
