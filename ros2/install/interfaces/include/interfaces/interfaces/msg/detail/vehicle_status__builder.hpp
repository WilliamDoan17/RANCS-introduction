// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:msg/VehicleStatus.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__VEHICLE_STATUS__BUILDER_HPP_
#define INTERFACES__MSG__DETAIL__VEHICLE_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/msg/detail/vehicle_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace msg
{

namespace builder
{

class Init_VehicleStatus_steering_angle
{
public:
  explicit Init_VehicleStatus_steering_angle(::interfaces::msg::VehicleStatus & msg)
  : msg_(msg)
  {}
  ::interfaces::msg::VehicleStatus steering_angle(::interfaces::msg::VehicleStatus::_steering_angle_type arg)
  {
    msg_.steering_angle = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::msg::VehicleStatus msg_;
};

class Init_VehicleStatus_speed
{
public:
  Init_VehicleStatus_speed()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleStatus_steering_angle speed(::interfaces::msg::VehicleStatus::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return Init_VehicleStatus_steering_angle(msg_);
  }

private:
  ::interfaces::msg::VehicleStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::msg::VehicleStatus>()
{
  return interfaces::msg::builder::Init_VehicleStatus_speed();
}

}  // namespace interfaces

#endif  // INTERFACES__MSG__DETAIL__VEHICLE_STATUS__BUILDER_HPP_
