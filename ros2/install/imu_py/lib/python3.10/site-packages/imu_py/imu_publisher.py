import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Imu

class ImuPublisher(Node): 
    def __init__(self):
        super().__init__("imu_publisher")
        self.publisher_ = self.create_publisher(Imu, "/imu", 10)
        self.timer_ = self.create_timer(1.0, self.publish_imu)

    def publish_imu(self):
        imu = Imu()
        imu.linear_acceleration.x = 20.0
        imu.linear_acceleration.y = 30.0
        imu.linear_acceleration.z = 0.0

        self.publisher_.publish(imu)

        self.get_logger().info(f"Publishing: \n\tLinear acceleration x: {imu.linear_acceleration.x}\n\tLinear acceleration y: {imu.linear_acceleration.y}\n\tLinear accleration z: {imu.linear_acceleration.z}")

def main():
    rclpy.init()
    rclpy.spin(ImuPublisher())
    rclpy.shutdown()

