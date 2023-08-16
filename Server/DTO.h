#ifndef DTO_H
#define DTO_H
#include "Target.h"
#include <cmath>
#include "Torpedo.h"
class DTO{
private:
    Torpedo &torpedo;
    Target &target;
    double dt;
public :
    DTO(Torpedo &torpedo, Target &target)
        : torpedo(torpedo),target(target)
    {
        std::cout << "sa";
        std::cout << "DTO constructor called with Torpedo at: " << &torpedo << " and Target at: " << &target << std::endl;

    }

    double get_dt(){
        return this->dt;
    }
    void set_dt(double dt){
        this->dt=dt;
        this->torpedo.set_dt(dt);
        this->target.set_dt(dt);
    }
    void update(){
        double difference_y= target.getY()-torpedo.getY();
        double target_speed_y = target.getSpeed_ms()*std::sin(target.getTemp_Deg()*3.1470/ 180.0000);
        double difference_x= target.getX()-torpedo.getX();
        double target_speed_X = target.getSpeed_ms()*std::cos(target.getTemp_Deg()*3.1470/ 180.0000);
        if(!target.targetActive){
            torpedo.setCourse(torpedo.getTemp_Deg());
        }

        else if(fabs(difference_x)<=5 && fabs(difference_y)<=5  ){
            target.targetActive=false;


        }
        else{
        this->torpedo.setCourse(std::atan2((difference_y+target_speed_y),(difference_x+target_speed_X))*180.0000/3.1470);
        target.update();
        std::cout<<"difference_y is  --> "<<difference_y<<std::endl;
        std::cout<<"difference_x is  --> "<<difference_x<<std::endl;
        std::cout<<"target_speed_y "<<target_speed_y<<std::endl;
        std::cout<<"torpedo course angle is --> "<<torpedo.getCourse_deg()<<std::endl;




        }
        torpedo.update();

        std::cout<<"difference_y is  --> "<<difference_y<<std::endl;
        std::cout<<"difference_x is  --> "<<difference_x<<std::endl;
        std::cout<<"target_speed_y "<<target_speed_y<<std::endl;
        std::cout<<"torpedo course angle is --> "<<torpedo.getCourse_deg()<<std::endl;
    }
};
#endif // DTO_H
