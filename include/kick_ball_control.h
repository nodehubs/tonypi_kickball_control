#ifndef KICK_BALL_H_
#define KICK_BALL_H_

#include "rclcpp/rclcpp.hpp"
#include "ai_msgs/msg/perception_targets.hpp"

class KickBallControlNode : public rclcpp::Node{
public:
    KickBallControlNode(const std::string &node_name, const rclcpp::NodeOptions &options = rclcpp::NodeOptions());
    ~KickBallControlNode() override;

private:
    rclcpp::Subscription<ai_msgs::msg::PerceptionTargets>::SharedPtr target_subscriber_;
    void subscription_callback(const ai_msgs::msg::PerceptionTargets::SharedPtr targets_msg);
    std::shared_ptr<OrderInterpreter> order_interpreter_;

    std::string sub_topic_ = "robot_target_detection";
    std::string target_type_ = "red_ball";
    bool no_target = true;
};



#endif //KICK_BALL_H_