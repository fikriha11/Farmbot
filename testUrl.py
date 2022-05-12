import requests


def InsertSensor():
  headers = {
  'user-agent': 'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.54 Mobile Safari/537.36'
}
  url = 'http://farmbot.belajarobot.com/sensor/1'
  name_img = 'images.png'
  img = open(name_img, 'rb')
  data = {
    'moist': 199,
    'lumen': 199,
    'temp': 199,
    'humid': 103
  }
  files = {'image' : img}
  # files = {'image': (name_img,img,'images/png')}
  try:
    res = requests.post(url, data=data, files=files, headers=headers)
    print(res.text)
  except Exception as error:
    print(error)

InsertSensor()


