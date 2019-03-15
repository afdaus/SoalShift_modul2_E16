# SoalShift_modul2_E16
# SOAL 1
# SOAL 2
Untuk menyelesaikan soal nomor 2, langkahnya sebagai berikut:
1. Membuat variabel char yang akan menyimpan path dari file elen.ku dan variabel char yang menyimpan string owner dan grup yang diinginkan.
2. Untuk mengetahui owner dan group file elen.ku, membutuhkan struct stat, struct psswd dan struct group. Pertama dilakukan `stat(dir,&namavariabelstruct)` untuk mengetahui file yang akan dicari owner dan grupnya. Selanjutnya untuk mengetahui owner filenya menggunakan struct passwd dengan cara `getpwuid(variabelstructstat.st_uid)` kemudian disimpan dalam suatu variabel, variabel ini nantinya dapat mengakses nama owner filenya. Begitu juga untuk mendapatkan grupnya tinggal mengganti `getpwuid` dengan `getgrgid`..
3. Setelah mendapatkan nama owner dan grup file elen.ku, kita dapat membandingkan owner dan grupnya dengan `www-data`, jika sesuai maka file elen.ku akan dihapus. Sebelum itu kita perlu mengganti permission file elen.ku menjadi 777 agar dapat dihapus dengan cara `chmod(pathtofile,0777)`.
4. Kemudian main program ini tinggal dipindahkan ke template daemon modul 2 dengan mengganti waktu `sleep(3)` agar berjalan setiap 3 detik.
# SOAL 3
 untuk menyelesaikan soal nomor 3, maka langkah-langkahnya sebagai berikut:
1. secara garis besar, nomor 3 dapat diselesaikan dengan: membuat file "daftar.txt" dengan fungsi touch, mengekstrak file zip "campur2.zip" dengan perintah unzip, lalu menggunakan fungsi ls untuk mengambil daftar nama file yang ada di folder campur2 (folder dari hasil mengekstrak campur2.zip) kemudian menggunakan fungsi grep untuk mensortir nama filenya bedasarkan ekstensi (fungsi ls dan grep dijalankan dengan piping, yang hanya diambil ialah file berekstensi .txt). Setelah itu, untuk mencetak hasil dari fungsi grep dan ls ke dalam file "daftar.txt", maka digunakan fungsi dup2 untuk menulisnya.
2. untuk melakukan fungsi-fungsi diatas, maka dapat menggunakan fungsi fork serta exec, dengan urutan sebagai berikut:
	-di main, fork pertama dijalankan, sehingga menghasilkan child pertama dan parent pertama.
	-pada child pertama dijalankan fungsi touch dengan fungsi exec `execvp("touch",&pointer_yang_menyimpan_fungsi_touch);`.
	-Pada parent pertama, parent pertama menjalankan fungsi fork kedua yang menghasilkan 2 proses baru, yaitu child kedua dan parent kedua.
	-Pada child kedua, dijalankan fungsi unzip dengan exec untuk mengekstrak file dari campur2.zip `execvp("unzip",&pointer_yang_menyimpan_fungsi_unzip);`. 
	-Parent kedua melakukan wait dengan cara `while((wait(&var_int))>0);` untuk menunggu child kedua menyelesaikan proses unzip. hal ini penting dilakukan karena jika parent tidak menunggu child pertama, fungsi yang memerlukan file dari campur2.zip dapat dijalankan terlebih dahulu. selanjutnya dijalankan fungsi fork ketiga, sehingga menghasilkan child ketiga dan parent ketiga.
	-Pada child ketiga, dijalankan wait dengan cara `while((wait(&var_int))>0);` untuk memastikan bahwa proses sebelumnya telah selesai dijalankan. setelah itu, maka pada child ketiga dijalankan fungsi ls yang dipipe bersama dengan fungsi grep, menggunakan fungsi exec. Fungsi grep dijalankan pada proses lain.
	-Pada parent ketiga, dijalankan fungsi wait dengan cara `while((wait(&var_int))>0);` untuk menunggu proses ls telah selesai dijalankan.  Setelah itu, dijalankan fungsi grep untuk mensortir hasil dari fungsi ls, yang kemudian dimasukkan ke dalam file daftar.txt dengan fungsi dup2. Perintah yang digunakan ialah `dup2(&variabel_yang_membuka_file,1);`, `execvp("grep",&pointer_yang_menyimpan_fungsi_grep);`
# SOAL 4
# SOAL 5
Untuk menyelesaikan soal nomor 5, maka langkah-langkahnya sebagai berikut:
A. Program C untuk mencatat log tiap menitnya
	-untuk menjalankan setiap menitnya, maka menggunakan daemon.
	-untuk membuat nama folder dengan waktu, maka dapat menggunakan fungsi untuk mengambil waktu pada c, yaitu `time_t &array_char = time(NULL);`
	-untuk merubah waktu menjadi format tertentu, maka dapat menggunakan `strftime(&array_char_lain, besar_array, "%d:%m:%Y-%H:%M", localtime(&array_char));`
	-setelah itu, untuk membuatnya kedalam sebuah alamat direktori, maka dapat menggunakan strcat  dan strcpy, kemudian dimasukkan ke dalam variabel.
	-untuk membuat direktori, maka dapat menggunakan fungsi mkdir.
	-untuk mengedit sebuah string dengan format nama tertentu, dapat menggunakan fungsi sprintf.
	-untuk membuka atau membuat file, maka dapat menggunakan pointer FILE.
Secara garis besar, untuk menyelesaikan soal nomor 5 ialah menggunakan fungsi time untuk mengambil waktu, kemudian waktu tersebut dirubah formatnya dengan fungsi strftime, kemudian waktu tersebut dibuat menjadi alamat sebuah direktori dengan fungsi strcat dan strcpy. Selanjutnya, membuat direktori dengan alamat yang sudah dibuat dengan mkdir, membuat loop sebanyak 30 kali, dimana di dalamnya digunakan sprintf untuk memformat sebuah string, lalu membuat file dengan nama string tersebut, membuka dan membaca log, mengcopy isi log tersebut ke file log yang baru. setelah itu, program berhenti selama 1 menit menggunakan fungsi sleep.
B. untuk menghentikan program, maka dapat menggunakan fungsi `pkill [nama_program]` dijalankan dengan fungsi exec di dalam c.
