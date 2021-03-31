from pop import Pilot
from pop import LiDAR
import time


bot = Pilot.SerBot()
lidar = LiDAR.Rplidar()
lidar.connect()
lidar.startMotor()
direction = 0
while True:
    no_collision = True
    vectors = lidar.getVectors()
    for v in vectors:
        degree = v[0]
        distance = v[1]
        if degree <= 60 or degree >= 300:
            if distance <= 500:
                no_collision = False
        if degree <= 30:
            bot.stop()
            print('stop')
            
    if no_collision:
        bot.setSpeed(80)
        bot.forward()
    else:
        bot.setSpeed(50)
        bot.turnLeft()
