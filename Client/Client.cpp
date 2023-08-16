#include<iostream>
#include "Torpedo.h"
#include <thread>



int main(){
    Torpedo torpedo;
    int travelTime;
    int timePeriod;
    torpedo.setCourse(37);
    torpedo.setSpeed(3.85);
    std::cout<<"Please provide travel time for torpedo !!! \n ";
    std::cin>>travelTime;

    std::cout<<"Please provide time period in which time interval you want to see  progress !!! \n ";
    std::cin>>timePeriod;


     for (int step = 1; step <= travelTime; ++step) {
        auto start = std::chrono::high_resolution_clock::now();

        torpedo.update();

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
        std::cout << duration.count() << std::endl;
        std::chrono::seconds timePeriodDuration(timePeriod);
        auto remainingSleepTime = timePeriodDuration-duration;
        std::this_thread::sleep_for(remainingSleepTime);
       // std::cout<<torpedo.getX()<<' '<< torpedo.getY()<<std::endl;
        std::cout << "Step " << step << ": x = " << torpedo.getX() << ", y = " << torpedo.getY() << std::endl;


    }

    return 0;
}
