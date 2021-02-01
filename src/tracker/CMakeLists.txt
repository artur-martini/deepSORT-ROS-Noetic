cmake_minimum_required(VERSION 3.0.2)
project(tracker)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  cv_bridge
  sensor_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
)

# BUILD

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${avcodec_INCLUDE_DIRS}
  ${swscale_INCLUDE_DIRS}  
)

add_library(${PROJECT_NAME} src/deepsort.cpp)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})


# CPP EXECUTABLE

add_executable(${PROJECT_NAME}_node src/${PROJECT_NAME}_node.cpp)
target_link_libraries(${PROJECT_NAME}_node
  ${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

# INSTALL 


