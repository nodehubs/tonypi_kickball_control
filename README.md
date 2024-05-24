# tonypi_kickball_control
# Function Introduction

This package controls the robot to automatically kick the ball by receiving messages from the object recognition node.

# Usage

## Preparations

1. Have the TonyPi robot, including the robot body, camera, and RDK suite, and ensure it runs normally.
2. Have related props such as small balls.

## Install the Package

**1. Install the package**

After starting the robot, connect to the robot through terminal SSH or VNC, click the "One-click Deployment" button at the top right of this page, copy the following command to run on the RDK system to complete the installation of the relevant Node.

```bash
sudo apt update
sudo apt install -y tros-tonypi-kickball-control
```
**2. Run the Task Decomposition Function**

```shell
source /opt/tros/local_setup.bash

ros2 launch tonypi_kickball_control kick_ball_control.launch.py
```

# Interface Description

## Topics

### Subscribed Topics

|Name  | Type                                  |  Description           |
|------| --------------------------------------| --------------------------------|
|robot_target_detection |ai_msgs::msg::PerceptionTargets | Position messages of the target object|

## Parameters
| Parameter Name             | Type       | Description  |
| --------------------- | ----------- | ----------------------------------------------------- |
| sub_topic    | string |   Name of the subscribed topic for receiving messages about target objects. Configure according to the actual published topic name. Default value is /robot_target_detection |
| target_type    | string |    Type of the recognized target. Default value is red_ball. |