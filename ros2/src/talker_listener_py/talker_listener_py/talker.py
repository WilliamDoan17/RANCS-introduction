import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class Talker(Node):
    def __init__(self): 
        super.__init__('talker')
        self.publisher_ = self.create_publisher(String, '/chatter', 10)
        self.timer_ = self.create_timer(1.0, self.publish_message)

    def publish_message(self) -> None:
        msg = String()
        msg.data = "Hello World"
        self.publisher_.publish(msg)
        self.get_logger().info(f"Publishing: {msg.data}")

if __name__ == "__main__":
    rclpy.init(args = args)
    rclpy.spin(Talker())
    rclpy.shutdown()



