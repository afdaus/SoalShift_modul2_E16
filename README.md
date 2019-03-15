# SoalShift_modul2_E16
# SOAL 1
# SOAL 2
Untuk menyelesaikan soal nomor 2, langkahnya sebagai berikut:
1. Membuat variabel char yang akan menyimpan path dari file elen.ku dan variabel char yang menyimpan string owner dan grup yang diinginkan.
2. Mengganti permission file elen.ku menjadi 777 menggunakan `chmod(pathtofile,0777)`.
3. Untuk mengetahui owner dan group file elen.ku, membutuhkan struct stat, struct psswd dan struct group. Pertama dilakukan `stat(dir,&namavariabelstruct)` untuk mengetahui file yang akan dicari owner dan grupnya. Selanjutnya untuk mengetahui owner filenya menggunakan struct passwd dengan cara `getpwuid(variabelstructstat.st_uid)` kemudian disimpan dalam suatu variabel, variabel ini nantinya dapat mengakses nama owner filenya. Begitu juga untuk mendapatkan grupnya tinggal mengganti `getpwuid` dengan `getgrgid`.
4. Setelah mendapatkan nama owner dan grup file elen.ku, kita dapat membandingkan owner dan grupnya dengan `www-data`, jika sesuai maka file elen.ku akan dihapus.
5. Kemudian main program ini tinggal dipindahkan ke template daemon modul 2 dengan mengganti waktu `sleep(3)` agar berjalan setiap 3 detil=k.
# SOAL 3
# SOAL 4
# SOAL 5
