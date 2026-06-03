#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>

using Node = rclcpp::Node;
using Imu = sensor_msgs::msg::Imu;

class ImuSubscriber : public Node {
private:
  rclcpp::Subscription<Imu>::SharedPtr subscription_;

  void imu_callback(const Imu &imu) {
    RCLCPP_INFO(this->get_logger(),
                "Received:\n\tLinear acceleration x: %f\n\t Linear "
                "acceleration y: % f\n\tLinear acceleration z: % f ",
                imu.linear_acceleration.x, imu.linear_acceleration.y,
                imu.linear_acceleration.z);
  }

public:
  ImuSubscriber() : Node("imu_subscriber") {
    subscription_ = this->create_subscription<Imu>(
        "/imu", 10,
        std::bind(&ImuSubscriber::imu_callback, this, std::placeholders::_1));
  }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ImuSubscriber>());
  rclcpp::shutdown();
  return 0;
}
