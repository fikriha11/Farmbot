import requests
import serial
from datetime  import datetime
from time import sleep

headers = {
  'user-agent': 'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.54 Mobile Safari/537.36'
}

class GetData():

    def __init__(self,kolom,baris,data):
        self.url = 'http://farmbot.belajarobot.com/farm/bot/1'

        self.plant_id = "0"
        self.Umur = "0"
        self.umur_panen = "0" 
        self.get_database = data
        self.kolom = kolom
        self.baris = baris
         

    # @property
    # def get_database(self):
    #     self.req = requests.get(self.url,headers=headers)   
    #     self.req = self.req.json()
    #     return self.req

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
def query():
  headers = {
  'user-agent': 'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.54 Mobile Safari/537.36'
  }
  url = 'http://farmbot.belajarobot.com/farm/bot/1'
  query = requests.get(url, headers=headers)
  query = query.json()
  return query        
 
def DataArduino():
    # Kolom  x Baris
    data = query()
    Tanaman1 = GetData(1,1,data)
    Tanaman2 = GetData(2,1,data)
    Tanaman3 = GetData(3,1,data)
    Tanaman4 = GetData(4,1,data)

    Tanaman5 = GetData(4,2,data)
    Tanaman6 = GetData(3,2,data)
    Tanaman7 = GetData(2,2,data)
    Tanaman8 = GetData(1,2,data)

    Tanaman9  = GetData(1,3,data)
    Tanaman10 = GetData(2,3,data)
    Tanaman11 = GetData(3,3,data)
    Tanaman12 = GetData(4,3,data)

    Tanaman13 = GetData(4,4,data)
    Tanaman14 = GetData(3,4,data)
    Tanaman15 = GetData(2,4,data)
    Tanaman16 = GetData(1,4,data)

    Tanaman17 = GetData(1,5,data)
    Tanaman18 = GetData(2,5,data)
    Tanaman19 = GetData(3,5,data)
    Tanaman20 = GetData(4,5,data)

    return "A{}B{}C{}D{}E{}F{}G{}H{}I{}J{}K{}L{}M{}N{}O{}P{}Q{}R{}S{}T{}U".format(
        Tanaman1.data_send,Tanaman2.data_send,Tanaman3.data_send,Tanaman4.data_send,
        Tanaman5.data_send,Tanaman6.data_send,Tanaman7.data_send,Tanaman8.data_send,
        Tanaman9.data_send,Tanaman10.data_send,Tanaman11.data_send,Tanaman12.data_send,
        Tanaman13.data_send,Tanaman14.data_send,Tanaman15.data_send,Tanaman16.data_send,
        Tanaman17.data_send,Tanaman18.data_send,Tanaman19.data_send,Tanaman20.data_send,
    )

def TestSerial():
    arduino = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=.1)
    arduino.write(bytes(DataArduino(), 'utf-8'))
