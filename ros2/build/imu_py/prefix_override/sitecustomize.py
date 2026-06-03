import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/will/Will/RANCS/RANCS-introduction/ros2/install/imu_py'
