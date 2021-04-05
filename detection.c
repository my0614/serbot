from pop import Pilot
from pop import LiDAR
import time
import math, random

serbot_width = 500 # 초기 serbot값 설정
detect = []

#각도 거리 탐지
def calcAngle(length):
    radian = math.atan((serbot_width /2) / length) #atan함수 사용하여 
    angle = math.degrees(radian) # 라디안을 각도형식으로 변환
    return angle

def collisionDetect(length):
    angle = calcAngle(length)
    
    detect = [False] * 8
    degrees = [0, 45, 90, 135, 180, 225, 270, 315]
    
    vectors = lidar.getVectors()
    
    for d in degrees:    
        for v in vectors:
            if d-angle >= 0:
                if v[0] >= d - angle and v[0] <= d + angle:
                    detect[d // 45] = True
                    break
            else:
                if v[0] >= 360- angle + d  or v[0] <= d + angle:
                    detect[d // 45] = True
                    break
    return detect

value = 0
bot = Pilot.SerBot()
lidar = LiDAR.Rplidar()
lidar.connect()
lidar.startMotor()

cont = True
degrees = [0, 45, 90, 135, 180, 225, 270, 315]

bot.move(degrees[value], 20)

while cont:
    try:
        detect = collisionDetect(300)
        if detect[value]:
            print('stop')
            bot.stop()
            continue
            
        print('detect',detect)
        detect = collisionDetect(800)
        
        if sum(detect) == 8:
            print('detect')
            bot.stop()
            continue
            
        if detect[value]:
            while True:
                value_test = random.randint(0,7)
                if value != value_test and detect[value_test] is False:
                    value = value_test
                    break
            print('value', value)
        
        bot.move(degrees[value], 20)        
    except KeyboardInterrupt:
        cont = False
