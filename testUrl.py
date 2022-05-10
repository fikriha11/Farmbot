import urllib.request
import urllib.parse
import base64

url = "http://farmbot.belajarobot.com/sensor/1"
# url = "https://aklimatisasidisperta.belajarobot.com/sensor/insert"

headers = {
    'Content-Type' : 'multipart/form-data'
}

# with open("GUI/images.jpg", "rb") as img_file:
#     Image = base64.b64encode(img_file.read())

files = urllib.parse.urlencode({
    'moist':100,
    'lumen': 100,
    'temp': 100,
    'humid': 100,
    # 'image' : Image,
    'image':('images.jpg',open('GUI/images.jpg', 'rb'),'image/jpg'),
}).encode('ascii')
try:
    send_image = urllib.request.urlopen(url, data=files)
    print(send_image.read())
except Exception as error:
    print(error)
    print("post image bermasalah!")