#include <ros/ros.h>


int main(int argc, char** argv){

    ros::init(argc, argv, "Tracker");
    ros::NodeHandle n;
    ros::spin();

    while(1){
        printf("okidoki\n");
    }

    return 0;

}