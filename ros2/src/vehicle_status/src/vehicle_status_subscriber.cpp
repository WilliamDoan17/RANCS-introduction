#include "interfaces/msg/vehicle_status.hpp"
#include <rclcpp/rclcpp.hpp>

using VehicleStatus = interfaces::msg::VehicleStatus;

class VehicleStatusSubscriber : public rclcpp::Node {
private:
  rclcpp::Subscription<VehicleStatus>::SharedPtr subscription_;

  void log_vehicle_status(const VehicleStatus::SharedPtr vehicle_status) {
    RCLCPP_INFO(this->get_logger(),
                "Received:\n\tSpeed: %d\n\tSteering Angle: %d",
                vehicle_status->speed, vehicle_status->steering_angle);
  }

public:
  VehicleStatusSubscriber() : Node("vehicle_status_subscriber") {
    subscription_ = this->create_subscription<VehicleStatus>(
        "/vehicle_status", 10,
        std::bind(&VehicleStatusSubscriber::log_vehicle_status, this,
                  std::placeholders::_1));
  }
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VehicleStatusSubscriber>());
  rclcpp::shutdown();
  return 0;
}
