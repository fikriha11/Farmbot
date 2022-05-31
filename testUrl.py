import cv2
from cv2 import resize
import requests

headers = {
  'user-agent': 'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.54 Mobile Safari/537.36'
}

def InsertSensor():
  url = 'http://farmbot.belajarobot.com/sensor/1'
  name_img = 'image.png'
  img = open(name_img, 'rb')

  data = {
    'moist': 88,
    'lumen': 997,
    'temp': 38,
    'humid': 70
  } 
  # files = {'image':img}
  files = {'image': (name_img,img,'images/png')}

  try:
    res = requests.post(url, data=data, files=files, headers=headers)
    print(res.text)
  except Exception as error:
    print(error)

