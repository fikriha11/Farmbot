import requests
import serial
from datetime  import datetime
from time import sleep

headers = {
  'user-agent': 'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.54 Mobile Safari/537.36'
}

class GetData():

    def __init__(self,kolom,baris):
        self.url = 'http://farmbot.belajarobot.com/farm/bot/1'
        self.baris = int(baris)
        self.kolom = int(kolom)

        self.plant_id = "0"
        self.Umur = "0"
        self.umur_panen = "0"   

    @property
    def get_database(self):
        self.req = requests.get(self.url,headers=headers)   
        self.req = self.req.json()
        return self.req

    @property
    def get_data(self):
        self.data = self.get_database['data'][self.kolom-1][self.baris - 1]
        return self.data

    @property
    def get_umur(self):
        self.tanggal = datetime.now()
        self.hari_now = self.tanggal.day
        self.bulan_now = self.tanggal.month
        self.tahun_now = self.tanggal.year

        self.tanggal_tanam = self.get_data['plant_time']
        self.tanggal_tanam = self.tanggal_tanam.split('-')        
        self.tahun_tanam = int(self.tanggal_tanam[0])
        self.bulan_tanam = int(self.tanggal_tanam[1])
        self.hari_tanam = int(self.tanggal_tanam[2].split('T')[0])  

        self.Tanam = self.hari_tanam + self.bulan_tanam * 30 + self.tahun_tanam * 365
        self.Sekarang = self.hari_now + self.bulan_now * 30 + self.tahun_now * 365

        self.Umurtahun = (self.Sekarang - self.Tanam) / 365
        self.UmurBulan = self.Umurtahun * 12
        self.UmurMinggu = self.UmurBulan * 4
        self.UmurHari = self.UmurMinggu * 7

        return round(self.UmurHari)

                
    def save(self):
        if self.get_data != None:
            self.plant_name = self.get_data['plant_name']
            self.plant_id = self.get_data['plant_id']
            self.Umur = self.get_umur
            self.umur_panen = self.get_data['period']     

    @property
    def data_send(self):
        self.save()
        return "{},{},{}".format(
            self.plant_id,
            self.Umur,
            self.umur_panen,
        )  
 
def DataArduino():
    # Kolom  x Baris
    Tanaman1 = GetData(1,1)
    Tanaman2 = GetData(2,1)
    Tanaman3 = GetData(3,1)
    Tanaman4 = GetData(4,1)

    Tanaman5 = GetData(4,2)
    Tanaman6 = GetData(3,2)
    Tanaman7 = GetData(2,2)
    Tanaman8 = GetData(1,2)

    Tanaman9  = GetData(1,3)
    Tanaman10 = GetData(2,3)
    Tanaman11 = GetData(3,3)
    Tanaman12 = GetData(4,3)

    Tanaman13 = GetData(4,4)
    Tanaman14 = GetData(3,4)
    Tanaman15 = GetData(2,4)
    Tanaman16 = GetData(1,4)

    Tanaman17 = GetData(1,5)
    Tanaman18 = GetData(2,5)
    Tanaman19 = GetData(3,5)
    Tanaman20 = GetData(4,5)

    return "A{}B{}C{}D{}E{}F{}G{}H{}I{}J{}K{}L{}M{}N{}O{}P{}Q{}R{}S{}T{}".format(
        Tanaman1.data_send,Tanaman2.data_send,Tanaman3.data_send,Tanaman4.data_send,
        Tanaman5.data_send,Tanaman6.data_send,Tanaman7.data_send,Tanaman8.data_send,
        Tanaman9.data_send,Tanaman10.data_send,Tanaman11.data_send,Tanaman12.data_send,
        Tanaman13.data_send,Tanaman14.data_send,Tanaman15.data_send,Tanaman16.data_send,
        Tanaman17.data_send,Tanaman18.data_send,Tanaman19.data_send,Tanaman20.data_send,
    )

def TestSerial():
    arduino = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=.1)
    arduino.write(bytes(DataArduino(), 'utf-8'))

