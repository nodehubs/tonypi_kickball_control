#include <thread>
#include <chrono>

#include "order_interpreter.hpp"
#include "kick_ball_control.h"

KickBallControlNode::KickBallControlNode(const std::string& node_name, const rclcpp::NodeOptions& options) : rclcpp::Node(node_name, options) {
    
    this->declare_parameter<std::string>("sub_topic", sub_topic_);
    this->declare_parameter<std::string>("target_type", target_type_);

    this->get_parameter<std::string>("sub_topic", sub_topic_);
    this->get_parameter<std::string>("target_type", target_type_);
    
    target_subscriber_ =  this->create_subscription<ai_msgs::msg::PerceptionTargets>(
      sub_topic_,
      1,
      std::bind(&KickBallControlNode::subscription_callback,
      this,
      std::placeholders::_1)); 
    order_interpreter_ = std::make_shared<OrderInterpreter>();

    order_interpreter_->control_serial_servo("stand");
    order_interpreter_->control_PWM_servo(1, 1000, 200);
}
KickBallControlNode::~KickBallControlNode(){

}

void KickBallControlNode::subscription_callback(const ai_msgs::msg::PerceptionTargets::SharedPtr targets_msg){
    static int p_angle = 1000;
    static int y_angle = 1000;
    static int p_angle_change = 600;
    static int y_angle_change = 600;
    int center_x = 0;
    int center_y = 0;
    static int no_target_frame_number = 0;
    for(const auto &target : targets_msg->targets){
        if(target.type == target_type_){
            if(target.rois[0].confidence > 0.5){
                center_x = target.rois[0].rect.x_offset + target.rois[0].rect.width / 2;
                center_y = target.rois[0].rect.y_offset + target.rois[0].rect.height / 2;
                no_target = false;
            }
        }
    }
    
    if(no_target == true){
        p_angle_change = ((p_angle_change + 300) % 900); 
        p_angle = 1000 + p_angle_change;
        order_interpreter_->control_PWM_servo(1, p_angle, 500);

        if(p_angle_change == 0){
            y_angle_change = ((y_angle_change + 100) % 900); 
            y_angle = y_angle + y_angle_change;
            order_interpreter_->control_serial_servo("turn_right_fast");
        }
    } else {
        if((center_x == 0) && (center_y == 0)){
            no_target_frame_number++;
            if(no_target_frame_number >= 2){
                no_target = true;
                no_target_frame_number = 0;
                return;
            }
        } else {
            no_target_frame_number = 0;
        }

        //检测到目标后的行为
        if (p_angle >= 1100 || p_angle <= 900){
            if (center_y < 220 || center_y > 260)
            {
                p_angle += (240 - center_y)*0.5;
                p_angle = p_angle > 1500 ? 1500 : p_angle;
                p_angle = p_angle < 900 ? 900 : p_angle;
                order_interpreter_->control_PWM_servo(1, p_angle , 200);
            }
        } else {
            p_angle = 1000;
            order_interpreter_->control_PWM_servo(1, p_angle, 200);
        }

        if (center_y < 350 && p_angle > 1100){
            if(center_x < 380) {
                order_interpreter_->control_serial_servo("turn_left_fast");
            } else if(center_x > 420) {
                order_interpreter_->control_serial_servo("turn_right_fast");
            } else {
                order_interpreter_->control_serial_servo("go_forward");
            }
        } else{
            if (center_y < 260)
            {
                if(center_x < 380) {
                    order_interpreter_->control_serial_servo("turn_left_fast");
                    return;
                } else if(center_x > 420) {
                    order_interpreter_->control_serial_servo("turn_right_fast");
                    return;
                } else {
                    order_interpreter_->control_serial_servo("go_forward");
                    return;
                }
            } else if (center_y < 390)
            {
                order_interpreter_->control_serial_servo("go_forward_one_step");
                return;
            }

            if (center_x < 300)
            {
                order_interpreter_->control_serial_servo("left_move_30");
                return;
            } else if(center_x < 400){
                order_interpreter_->control_serial_servo("left_move");
                return;
            }
            if (center_x > 560)
            {
                order_interpreter_->control_serial_servo("right_move_30");
                return;
            } else if (center_x > 470){
                order_interpreter_->control_serial_servo("right_move");
                return;
            }

            if ((center_x > 390) && (center_x < 470) && (center_y > 390) && (p_angle == 1000) ){
                order_interpreter_->control_serial_servo("right_shot");
            }
        }
    }

    return;
}

int main(int argc, char* argv[]){

    rclcpp::init(argc, argv);

    rclcpp::spin(std::make_shared<KickBallControlNode>("KickBallControlNode"));

    rclcpp::shutdown();

    RCLCPP_WARN(rclcpp::get_logger("KickBallControlNode"), "Pkg exit");

    return 0;
}