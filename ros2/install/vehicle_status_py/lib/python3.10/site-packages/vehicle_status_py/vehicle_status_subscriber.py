import rclpy
from rclpy.node import Node
from interfaces.msg import VehicleStatus

class VehicleStatusSubscriber(Node):
    def subscribe_vehicle_status(self, vehicle_status: VehicleStatus) -> None:
        self.get_logger().info(f"Received:\n\tSpeed: {vehicle_status.speed}\n\tSteering Angle:\
            {vehicle_status.steering_angle}")

    def __init__(self):
        super().__init__('vehicle_status_subscriber')
        self.subscription_ = self.create_subscription(VehicleStatus, '/vehicle_status', self.subscribe_vehicle_status,\
                                                      10)

def main():
    rclpy.init()
    rclpy.spin(VehicleStatusSubscriber())
    rclpy.shutdown()

