#include "interfaces/msg/vehicle_status.hpp"
#include <chrono>
#include <rclcpp/rclcpp.hpp>

using VehicleStatus = interfaces::msg::VehicleStatus;

class VehicleStatusPublisher : public rclcpp::Node {
private:
  rclcpp::Publisher<VehicleStatus>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;

  void publish_vehicle_status() {
    VehicleStatus vehicle_status;
    vehicle_status.speed = 10;
    vehicle_status.steering_angle = 20;

    publisher_->publish(vehicle_status);
    RCLCPP_INFO(this->get_logger(),
                "Publishing:\n\tSpeed: %d\n\tSteering Angle: %d",
                vehicle_status.speed, vehicle_status.steering_angle);
  }

public:
  VehicleStatusPublisher() : Node("vehicle_status_publisher") {
    publisher_ = this->create_publisher<VehicleStatus>("/vehicle_status", 10);
    timer_ = this->create_wall_timer(
        std::chrono::seconds(1),
        std::bind(&VehicleStatusPublisher::publish_vehicle_status, this));
  }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VehicleStatusPublisher>());
  rclcpp::shutdown();
  return 0;
}
