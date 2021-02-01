#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/core.hpp>

#include "tracker/deepsort.h"

#define PUBLISH_TOPIC "/image_from_tracker"
#define SUBSCRIBE_TOPIC "/usb_cam/image_raw"

ros::Publisher cam_image;

cv::Scalar COLOR_RED = (255, 0, 0);

// void cv_rectangle(cv::Mat img, cv::Point2d pt1, cv::Point2d pt2, cv::Scalar color){
//     cv::rectangle(img, pt1, pt2, color);
// }

void callback(const sensor_msgs::ImageConstPtr& msg){
    cv_bridge::CvImagePtr cv_image;
    cv_image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    cv::Mat image_mat = cv_image->image;

    cv_bridge::CvImage ros_image;
    sensor_msgs::Image img_msg;

    int height, width;

    // Edit image
    cv::Point2d pt1(100, 100);
    cv::Point2d pt2(200, 300);
    // pass the cv::Mat image to deepsort class
    deep_sort(image_mat, pt1, pt2, COLOR_RED);

    width = image_mat.cols;
    height = image_mat.rows;

    // Construct the image message
    std_msgs::Header header;
    header.seq = 0;
    header.stamp = ros::Time::now();
    ros_image = cv_bridge::CvImage(header, sensor_msgs::image_encodings::BGR8, image_mat);
    ros_image.toImageMsg(img_msg);

    cam_image.publish(img_msg);
}

int main(int argc, char** argv){

    ros::init(argc, argv, "Tracker");
    ros::NodeHandle n;

    // Publish topic
    cam_image = n.advertise<sensor_msgs::Image>(PUBLISH_TOPIC, 1);
    
    // Subscribe topic
    ros::Subscriber camera_sub = n.subscribe<sensor_msgs::Image>(SUBSCRIBE_TOPIC, 1, callback);
    ros::spin();    

}
