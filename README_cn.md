# 功能介绍

该功能包通过接收物体识别节点的消息，控制机器人自动踢球

# 使用方法

## 准备工作

1. 具备TonyPi机器人，包含机器人本体、相机及RDK套件，并且能够正常运行。
2. 具备小球等相关道具

## 安装功能包

**1.安装功能包**

启动机器人后，通过终端SSH或者VNC连接机器人，点击本页面右上方的“一键部署”按钮，复制如下命令在RDK的系统上运行，完成相关Node的安装。

```bash
sudo apt update
sudo apt install -y tros-tonypi-kickball-control
```

**2.运行自动踢球功能**

```shell
source /opt/tros/local_setup.bash

ros2 launch tonypi_kickball_control kick_ball_control.launch.py

```


# 接口说明

## 话题

### Sub话题
| 名称                          | 消息类型                                                     | 说明                                                   |
| ----------------------------- | ------------------------------------------------------------ | ------------------------------------------------------ |
| robot_target_detection      | ai_msgs::msg::PerceptionTargets        | 目标物体的位置消息                  |

## 参数

| 参数名                | 类型        | 说明   |
| --------------------- | ----------- | ----------------------------------------------------- |
| sub_topic    | string |    接收的目标物体的消息名称，请根据实际发布的话题名称配置，默认值为/robot_target_detection |
| target_type    | string |    识别目标的类型，默认值为red_ball |