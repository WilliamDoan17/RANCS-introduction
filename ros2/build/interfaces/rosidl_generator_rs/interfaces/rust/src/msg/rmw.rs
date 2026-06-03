#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "interfaces__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__interfaces__msg__VehicleStatus() -> *const std::ffi::c_void;
}

#[link(name = "interfaces__rosidl_generator_c")]
extern "C" {
    fn interfaces__msg__VehicleStatus__init(msg: *mut VehicleStatus) -> bool;
    fn interfaces__msg__VehicleStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<VehicleStatus>, size: usize) -> bool;
    fn interfaces__msg__VehicleStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<VehicleStatus>);
    fn interfaces__msg__VehicleStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<VehicleStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<VehicleStatus>) -> bool;
}

// Corresponds to interfaces__msg__VehicleStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct VehicleStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub speed: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub steering_angle: i8,

}



impl Default for VehicleStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !interfaces__msg__VehicleStatus__init(&mut msg as *mut _) {
        panic!("Call to interfaces__msg__VehicleStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for VehicleStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { interfaces__msg__VehicleStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { interfaces__msg__VehicleStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { interfaces__msg__VehicleStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for VehicleStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for VehicleStatus where Self: Sized {
  const TYPE_NAME: &'static str = "interfaces/msg/VehicleStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__interfaces__msg__VehicleStatus() }
  }
}


