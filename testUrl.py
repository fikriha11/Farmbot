import urllib.request
import urllib.parse

def UpdateDatabase():
    # url = "https://aklimatisasidisperta.belajarobot.com/sensor/insert"
    # url = "http://farmbot.belajarobot.com/sensor/1"

    files = urllib.parse.urlencode({
        'moist' : '100',
        'lumen': '100',
        'temp': '100',
        'humid':'100',
    }).encode('ascii')

    try:
        send_image = urllib.request.urlopen(url,data=files)
        print(send_image.read())
    except Exception as error:
        print(error)

UpdateDatabase()