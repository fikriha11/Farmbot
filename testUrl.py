# from inspect import Parameter
# import cv2
# from cv2 import resize
# import requests

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


def size():
    img = cv2.imread('picture.png',cv2.IMREAD_UNCHANGED)
    print('Original Dimension: ', img.shape)    
    dim = (400,150)
    resized = resize(img,dim,interpolation=cv2.INTER_AREA)
    print('Resized Dimensions : ',resized.shape)

    cv2.imshow("Resized image", resized)
    cv2.imwrite("post.jpg", resized)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


def query():
   url = 'http://farmbot.belajarobot.com/farm/bot/1'
   req = requests.get(url,headers=headers)
   print(req.json())

# query()
# InsertSensor()
# size()


def json():
  json = {
    'data':[
      [
        {
          "id" : "9"
        },
        {
          "nama": "10"
        }
      ]
    ]
  }

  data = json['data']
  print(data[0][1]['nama'])

def coba():
  path = '/home/pi/Documents/Farmbot/'
  print(path + 'Gui/agribot/nano.txt')
  print("mpg123 {}GUI/agribot.hg".format(path))


coba()