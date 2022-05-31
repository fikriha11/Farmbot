import requests

headers = {
  'user-agent': 'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.54 Mobile Safari/537.36'
}

class GetData():

    def __init__(self,kolom,baris):
        self.url = 'http://farmbot.belajarobot.com/farm/bot/1'
        self.baris = int(baris)
        self.kolom = int(kolom)

        self.plant_id = None
        self.umur_panen = None       
        self.tanggal_tanam = None
        self.tahun_tanam = None
        self.bulan_tanam = None
        self.hari_tanam = None

    @property
    def get_database(self):
        self.req = requests.get(self.url,headers=headers)   
        self.req = self.req.json()
        return self.req

    @property
    def get_data(self):
        self.data = self.get_database['data'][self.kolom-1][self.baris - 1]
        return self.data   

    def save(self):
        if self.get_data != None:
            self.plant_id = self.get_data['plant_id']
            self.umur_panen = int(self.get_data['period'] / 7)
            
            self.tanggal_tanam = self.get_data['plant_time']
            self.tanggal_tanam = self.tanggal_tanam.split('-')
            
            self.tahun_tanam = self.tanggal_tanam[0]
            self.bulan_tanam = self.tanggal_tanam[1]
            self.hari_tanam = self.tanggal_tanam[2].split('T')[0]
                

    @property
    def data_send(self):
        self.save()
        return "{},{},{},{},{}".format(
            self.plant_id,
            self.umur_panen,
            self.tahun_tanam,
            self.bulan_tanam,
            self.hari_tanam
        )  
           
def DataArduino():
    Tanaman1 = GetData(1,1)
    Tanaman2 = GetData(1,2)
    Tanaman3 = GetData(1,3)
    Tanaman4 = GetData(1,4)
    Tanaman5 = GetData(1,5)
    Tanaman6 = GetData(2,1)
    Tanaman7 = GetData(2,2)
    Tanaman8 = GetData(2,3)

    return "A{}B{}C{}D{}E{}F{}G{}H{}I".format(
        Tanaman1.data_send,Tanaman2.data_send,Tanaman3.data_send,
        Tanaman4.data_send,Tanaman5.data_send,Tanaman6.data_send,
        Tanaman7.data_send,Tanaman8.data_send,
    )

print(DataArduino())
