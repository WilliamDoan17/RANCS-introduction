// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interfaces:msg/VehicleStatus.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__MSG__DETAIL__VEHICLE_STATUS__STRUCT_H_
#define INTERFACES__MSG__DETAIL__VEHICLE_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/VehicleStatus in the package interfaces.
typedef struct interfaces__msg__VehicleStatus
{
  int8_t speed;
  int8_t steering_angle;
} interfaces__msg__VehicleStatus;

// Struct for a sequence of interfaces__msg__VehicleStatus.
typedef struct interfaces__msg__VehicleStatus__Sequence
{
  interfaces__msg__VehicleStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__msg__VehicleStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACES__MSG__DETAIL__VEHICLE_STATUS__STRUCT_H_
