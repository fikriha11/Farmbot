from datetime import datetime as dt
from gtts import gTTS


def TextToSpeech(cTemp, lux, humidity, moisture):
    try:
        if dt.now().hour > 5 and dt.now().hour <= 10:
            waktu = "Pagi"
        elif dt.now().hour > 10 and dt.now().hour <= 14:
            waktu = "Siang"
        elif dt.now().hour > 14 and dt.now().hour < 17:
            waktu = "Soree"
        else:
            waktu = "Datang"

        phrase = "Selamat {}, Kondisi Suhu saat ini adalah {} derajat Celcius, Dan kelembapan Udara sebesar {} Persen, Kelembapan Tanah sebesar {} persen.".format(waktu, int(cTemp), int(humidity), int(moisture))     
        phrase1 = "Untuk Keterangan Cahaya Sebesar {} Lumen, Terima Kasih".format(int(lux))
        language = 'id'
    
        output = gTTS(text=phrase + phrase1, lang=language, slow=False)
        output.save("GUI/temp.mp3")
        print("GTTS Sukses")

        return True
    except Exception as error:
        print("SoundOutput Error")
