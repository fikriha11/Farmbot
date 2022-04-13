tTanam = input("Masukan Tanggal Tanam: ")
bTanam = input("Masukan Bulan Tanam: ")
Tanam = int(tTanam) + int(bTanam) * 30

tNow = input("Tanggal Sekarang: ")
bNow = input("Bulan Sekarang: ")
Now = int(tNow) + int(bNow) * 30


UmurBulan = (Now-Tanam) / 30
UmurMinggu = UmurBulan * 4
UmurHari = UmurMinggu * 7

print("{} Bulan Atau {} Minggu Atau {} Hari".format(
    int(UmurBulan), int(UmurMinggu), int(UmurHari)))
