tanggalTanam = input("Masukan Tanggal Tanam: ")
bulanTanam = input("Masukan Bulan Tanam: ")
tahunTanam = input("Masukan Tahun Tanam: ")
Tanam = int(tanggalTanam) + (int(bulanTanam)*30) + (int(tahunTanam)*365)

tanggalNow = input("Tanggal Sekarang: ")
bulanNow = input("Bulan Sekarang: ")
tahunNow = input("Tahun Sekarang: ")
Now = int(tanggalNow) + (int(bulanNow) * 30) + (int(tahunNow) * 365)


Umurtahun = (Now - Tanam) / 365
UmurBulan = Umurtahun * 12
UmurMinggu = UmurBulan * 4
UmurHari = UmurMinggu * 7

print("{} Bulan Atau {} Minggu Atau {} Hari Atau {} Tahun".format(
    int(UmurBulan), int(UmurMinggu), int(UmurHari), Umurtahun))
