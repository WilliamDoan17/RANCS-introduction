import rclpy
from interfaces.msg import VehicleStatus
from rclpy.node import Node

class VehicleStatusPublisher(Node):
    def publish_vehicle_status(self) -> None:
        vehicle_status = VehicleStatus(speed = 10, steering_angle = 20)
        self.publisher_.publish(vehicle_status)
        self.get_logger().info(f"Publishing:\n\tSpeed: {vehicle_status.speed}\n\tSteering Angle:\
            {vehicle_status.steering_angle}")

    def __init__(self):
        super().__init__('vehicle_status_publisher')
        self.publisher_ = self.create_publisher(VehicleStatus, "/vehicle_status", 10)
        self.timer_ = self.create_timer(1.0, self.publish_vehicle_status)

def main(): 
    rclpy.init()
    rclpy.spin(VehicleStatusPublisher())
    rclpy.shutdown()
