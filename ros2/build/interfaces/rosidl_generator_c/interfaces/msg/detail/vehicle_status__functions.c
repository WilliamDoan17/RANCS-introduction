// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from interfaces:msg/VehicleStatus.idl
// generated code does not contain a copyright notice
#include "interfaces/msg/detail/vehicle_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
interfaces__msg__VehicleStatus__init(interfaces__msg__VehicleStatus * msg)
{
  if (!msg) {
    return false;
  }
  // speed
  // steering_angle
  return true;
}

void
interfaces__msg__VehicleStatus__fini(interfaces__msg__VehicleStatus * msg)
{
  if (!msg) {
    return;
  }
  // speed
  // steering_angle
}

bool
interfaces__msg__VehicleStatus__are_equal(const interfaces__msg__VehicleStatus * lhs, const interfaces__msg__VehicleStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // speed
  if (lhs->speed != rhs->speed) {
    return false;
  }
  // steering_angle
  if (lhs->steering_angle != rhs->steering_angle) {
    return false;
  }
  return true;
}

bool
interfaces__msg__VehicleStatus__copy(
  const interfaces__msg__VehicleStatus * input,
  interfaces__msg__VehicleStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // speed
  output->speed = input->speed;
  // steering_angle
  output->steering_angle = input->steering_angle;
  return true;
}

interfaces__msg__VehicleStatus *
interfaces__msg__VehicleStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  interfaces__msg__VehicleStatus * msg = (interfaces__msg__VehicleStatus *)allocator.allocate(sizeof(interfaces__msg__VehicleStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(interfaces__msg__VehicleStatus));
  bool success = interfaces__msg__VehicleStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
interfaces__msg__VehicleStatus__destroy(interfaces__msg__VehicleStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    interfaces__msg__VehicleStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
interfaces__msg__VehicleStatus__Sequence__init(interfaces__msg__VehicleStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  interfaces__msg__VehicleStatus * data = NULL;

  if (size) {
    data = (interfaces__msg__VehicleStatus *)allocator.zero_allocate(size, sizeof(interfaces__msg__VehicleStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = interfaces__msg__VehicleStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        interfaces__msg__VehicleStatus__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
interfaces__msg__VehicleStatus__Sequence__fini(interfaces__msg__VehicleStatus__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      interfaces__msg__VehicleStatus__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

interfaces__msg__VehicleStatus__Sequence *
interfaces__msg__VehicleStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  interfaces__msg__VehicleStatus__Sequence * array = (interfaces__msg__VehicleStatus__Sequence *)allocator.allocate(sizeof(interfaces__msg__VehicleStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = interfaces__msg__VehicleStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
interfaces__msg__VehicleStatus__Sequence__destroy(interfaces__msg__VehicleStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    interfaces__msg__VehicleStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
interfaces__msg__VehicleStatus__Sequence__are_equal(const interfaces__msg__VehicleStatus__Sequence * lhs, const interfaces__msg__VehicleStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!interfaces__msg__VehicleStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
interfaces__msg__VehicleStatus__Sequence__copy(
  const interfaces__msg__VehicleStatus__Sequence * input,
  interfaces__msg__VehicleStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(interfaces__msg__VehicleStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    interfaces__msg__VehicleStatus * data =
      (interfaces__msg__VehicleStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!interfaces__msg__VehicleStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          interfaces__msg__VehicleStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!interfaces__msg__VehicleStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
