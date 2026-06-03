#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>

using Node = rclcpp::Node;
using Imu = sensor_msgs::msg::Imu;

class ImuPublisher : public Node {
private:
  rclcpp::Publisher<Imu>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;

  void publish_imu() {
    Imu imu;
    imu.header.frame_id = "base_link";
    imu.header.stamp = this->now();
    imu.linear_acceleration.x = 20;
    imu.linear_acceleration.y = 30;
    imu.linear_acceleration.z = 0;
    publisher_->publish(imu);
    RCLCPP_INFO(this->get_logger(),
                "Publishing:\n\tLinear acceleration x: %f\n\t Linear "
                "acceleration y: %f\n\tLinear acceleration z: %f",
                imu.linear_acceleration.x, imu.linear_acceleration.y,
                imu.linear_acceleration.z);
  }

public:
  ImuPublisher() : Node("imu_publisher") {
    publisher_ = this->create_publisher<Imu>("/imu", 10);
    timer_ = this->create_wall_timer(
        std::chrono::seconds(1), std::bind(&ImuPublisher::publish_imu, this));
  }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ImuPublisher>());
  rclcpp::shutdown();
  return 0;
}
