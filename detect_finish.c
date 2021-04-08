from pop import LiDAR
import math

serbot_width = 500 # mm
degrees = [0, 45, 90, 135, 180, 225, 270, 315]

#모터 라이더 실행하기

lidar = LiDAR.Rplidar()
ldar.connect()
lidar.startMotor()

def calAngle(length):
    tan = (serbot_width / 2 ) / length
    angle = math.atan(tan) * (180 / math.pi)
    return angle
def collisonDetect(length):

    #global degress
    detect = [False] * len(degrees)
    ret = lidar.getVectors()
    angle = calAngle(length) #각도 체크

    for degree, distance, _ in ret:
        for i, detect_direction in enumerate(degrees):
            minDegree = detect_direction - angle
            maxDegree = detect_direction + angle
            isOut = minDegree < 0 and ((360 + minDegree) < degree and degree < maxDegree)
            if (minDegree < degree and degree < maxDegree) or isOut:
                if distance < length:
                    detect[i] = True
                    break
    return detect

lidar = LiDAR.Rplidar()
lidar.connect()
lidar.startMotor()
bot = Pilot.SerBot()
#degrees = [0, 45, 90, 135, 180, 225, 270, 315] # 초기화 해줄때
degrees = [i * 45 for i in range(8)]
