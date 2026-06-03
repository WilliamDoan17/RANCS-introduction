import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class Listener(Node):
    def __init__(self):
        super().__init__('listener')
        self.subscriber_ = self.create_subscription(String, "/chatter", self.subscribe_message, 10)

    def subscribe_message(self, msg: String) -> None:
        self.get_logger().info(f"Received: {msg.data}")

def main() -> None: 
    rclpy.init()
    rclpy.spin(Listener())
    rclpy.shutdown()

if __name__ == "__main__":
    main()
