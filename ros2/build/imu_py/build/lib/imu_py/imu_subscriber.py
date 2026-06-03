import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu

class ImuSubsriber(Node):
    def __init__(self):
        super().__init__("imu_subscriber")
        self.subscription_ = self.create_subscription(Imu, "/imu", self.imu_callback, 10)
    
    def imu_callback(self, imu: Imu) -> None:
        self.get_logger().info(f"Received: \n\tLinear acceleration x: {imu.linear_acceleration.x}\n\tLinear acceleration y: {imu.linear_acceleration.y}\n\tLinear accleration z: {imu.linear_acceleration.z}")


def main(): 
    rclpy.init()
    rclpy.spin(ImuSubsriber())
    rclpy.shutdown()
