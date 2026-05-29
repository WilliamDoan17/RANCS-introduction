#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class Listener : public rclcpp::Node {
private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;

  void subscribe_message(const std_msgs::msg::String::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "Received: %s", msg->data.c_str());
  }

public:
  Listener() : Node("listener") {
    subscriber_ = this->create_subscription<std_msgs::msg::String>(
        "/chatter", 10,
        std::bind(&Listener::subscribe_message, this, std::placeholders::_1));
  };
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Listener>());
  rclcpp::shutdown();
  return 0;
}
