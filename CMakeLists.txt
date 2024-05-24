# Copyright (c) 2022，Horizon Robotics.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.5)
project(tonypi_kickball_control)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(ai_msgs REQUIRED)

include_directories(include
  /usr/include
  /usr/include/python3.8
)

add_executable(tonypi_kickball_control
  src/kick_ball_control.cpp
)

target_link_libraries(tonypi_kickball_control
  python3.8
)

ament_target_dependencies(
  tonypi_kickball_control
    rclcpp
    ai_msgs
)


install(
  TARGETS tonypi_kickball_control
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

install(
  DIRECTORY
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
${PROJECT_SOURCE_DIR}/launch/
DESTINATION share/${PROJECT_NAME}/launch)

ament_package()