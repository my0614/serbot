import usb.core
import usb.util
# 오류를 위한 class
class FoundNotPixelRing(Exception): pass\

Hex2rgb = lambda n:((n >> 16) & 0xFF, (n >> 8) & 0xFF, n & 0xFF, 0)

class PixelRing:
    def __init__(self): #생성자
        self.dev = usb.core.find(idVendor=0x2886, idProduct=0x0018)
        if not self.dev:
            raise FoundNotPixelRing
    
    def __del__(self): # 소멸자
        usb.util.dispose_resources(self.dev)
    def __write(self, cmd, data=[0]):
        self.dev.ctrl_transfer(
            usb.util.CTRL_OUT | usb.util.CTRL_TYPE_VENDOR | usb.util.CTRL_RECIPIENT_DEVICE,
            0, cmd, 0x1C, data, 8000)
    def normal(self, color):
        color = color if type(color) == tuple else color = color
        self.__write(1,color)
    
    def off(self): #0x000000 - >black
        self.normal(0x000000)
        
            
