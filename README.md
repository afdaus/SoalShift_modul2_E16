# SoalShift_modul2_E16
# Commit terbaru dilakukan atas permintaan asisten penguji, untuk menyelesaikan soal nomor 4 dengan cara yang berbeda
# SOAL 1
Pertama-tama, kita menggunakan function directory pada c untuk menangkap file-file yang satu folder dengan file kodingan ini. 

Struct dirent *dir berarti sebagai pointer untuk directory entry. 

d = opendir("."); digunakan untuk menangkap file, jika ditemukan, maka akan masuk ke loop.

Selanjutnya, jika sebuah file ditemukan, saya memasukkan file tersebut ke dalam array bernama fsumber menggunakan fungsi strcpy. Lalu saya cari panjang array dari fsumber dengan menggunakan fungsi strlen. Hasil tersebut saya masukkan ke dalam variabel len. Lalu len saya kurangi 4 agar dapat mengetahui indeks ke berapakah untuk menangkap 4 string terakhir dalam sebuah char. Setelah itu saya membuat loop untuk memasukkan array indeks ke len-4 sampai dengan len ke dalam char bernama temp1. Jadi isi dari temp1 adalah 4 karakter terakhir dari nama file fsumber. Selanjutnya saya akan cek apakah isi dari temp1 adalah ‘.png’ atau bukan. Jika iya, maka akan masuk ke dalam fungsi dalam if, sedangkan jika bukan ‘.png’ tidak akan me return apa-apa dan mengulang loop dari awal.

Dalam fungsi if tersebut, saya membuat loop untuk mengambil nama file depan yang tidak diikuti ‘.png’ nya. Jadi misal jika ada file bernama lalala.png maka loop tersebut hanya mengambil lalala nya saja dan dimasukkan ke char bernama temp. Selanjutnya saya sudah memiliki char bernama grey yang berisi ‘_grey’. Lalu saya hanya tinggal menggabungkan char temp, grey, dan temp1 dan saya masukkan hasil itu ke dalam char bernama temp2. Maka file lalala.png akan menjadi lalala_grey.png. Setelah itu saya membuat char bernama alamat yang berisi ‘/home/samuel/modul2/gambar/’. Lalu saya akan menambahkan temp2 ke belakang char alamat dengan menggunakan funsgi strcat dan memasukkan hasilnya ke dalam char bernama temp3. Terakhir, saya hanya membuat fungsi rename dari fsumber ke temp3. Fungsi rename mirip dengan fungsi mv. Karena dalam temp3 sudah ada direktori tujuannya, otomatis file .png yang berada 1 folder dengan file kodingannya akan otomatis pindah ke /home/samuel/modul2/gambar/temp3. 

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
- di main, fork pertama dijalankan, sehingga menghasilkan child pertama dan parent pertama.
- pada child pertama dijalankan fungsi touch dengan fungsi exec `execvp("touch",&pointer_yang_menyimpan_fungsi_touch);`
- Pada parent pertama, parent pertama menjalankan fungsi fork kedua yang menghasilkan 2 proses baru, yaitu child kedua dan parent kedua.
- Pada child kedua, dijalankan fungsi unzip dengan exec untuk mengekstrak file dari campur2.zip `execvp("unzip",&pointer_yang_menyimpan_fungsi_unzip);`. 
- Parent kedua melakukan wait dengan cara `while((wait(&var_int))>0);` untuk menunggu child kedua menyelesaikan proses unzip. hal ini penting dilakukan karena jika parent tidak menunggu child pertama, fungsi yang memerlukan file dari campur2.zip dapat dijalankan terlebih dahulu. selanjutnya dijalankan fungsi fork ketiga, sehingga menghasilkan child ketiga dan parent ketiga.
- Pada child ketiga, dijalankan wait dengan cara `while((wait(&var_int))>0);` untuk memastikan bahwa proses sebelumnya telah selesai dijalankan. setelah itu, maka pada child ketiga dijalankan fungsi ls yang dipipe bersama dengan fungsi grep, menggunakan fungsi exec. Fungsi grep dijalankan pada proses lain.
- Pada parent ketiga, dijalankan fungsi wait dengan cara `while((wait(&var_int))>0);` untuk menunggu proses ls telah selesai dijalankan.  Setelah itu, dijalankan fungsi grep untuk mensortir hasil dari fungsi ls, yang kemudian dimasukkan ke dalam file daftar.txt dengan fungsi dup2. Perintah yang digunakan ialah `dup2(&variabel_yang_membuka_file,1);`, `execvp("grep",&pointer_yang_menyimpan_fungsi_grep);`
# SOAL 4
Di soal ini kita diharapkan agar membuat file makan_sehat#.txt, dengan ketentuan jika kita membuka file makan_enak.txt di 30 detik terakhir, dan program ini berjalan setiap 5 detik.
1. Membuat variabel yang akan menyimpan path dari makan_enak.txt.
    ```char dir[]="/home/panda/Documents/makanan/makan_enak.txt";```
2. Memakai struct stat untuk kemudian dipakai untuk mengetahui waktu(seconds).
`struct stat sb;`
`stat(dir, &sb);`
3a. Salah satu cara untuk mengetahui perbedaan waktu pada saat makan_enak.txt dibuka dan program ini berjalan kita tinggal memakai struct stat yang sebelumnya dideklarasikan ditambah 30 detik, jika waktunya masih lebih lama dari waktu program berjalan, maka file makan_sehat#.txt akan dibuat. 
3b. Cara yang satu lagi yaitu kita memakai fungsi yang disediakan oleh library time, fungsi yang kita pakai bernama difftime. Di fungsi ini terdapat 2 variabel, nanti akan dikurang variabel kiri dikurang variabel kanan, apabila perbedaannya masih kurang dari 30 detik, maka file makan sehat akan dibuat

# SOAL 5
Untuk menyelesaikan soal nomor 5, maka langkah-langkahnya sebagai berikut:
1. Program C untuk mencatat log tiap menitnya
- untuk menjalankan setiap menitnya, maka menggunakan daemon.
- untuk membuat nama folder dengan waktu, maka dapat menggunakan fungsi untuk mengambil waktu pada c, yaitu `time_t &array_char = time(NULL);`
- untuk merubah waktu menjadi format tertentu, maka dapat menggunakan `strftime(&array_char_lain, besar_array, "%d:%m:%Y-%H:%M", localtime(&array_char));`
- setelah itu, untuk membuatnya kedalam sebuah alamat direktori, maka dapat menggunakan strcat  dan strcpy, kemudian dimasukkan ke dalam variabel.
- untuk membuat direktori, maka dapat menggunakan fungsi mkdir.
- untuk mengedit sebuah string dengan format nama tertentu, dapat menggunakan fungsi sprintf.
- untuk membuka atau membuat file, maka dapat menggunakan pointer FILE.
Secara garis besar, untuk menyelesaikan soal nomor 5 ialah menggunakan fungsi time untuk mengambil waktu, kemudian waktu tersebut dirubah formatnya dengan fungsi strftime, kemudian waktu tersebut dibuat menjadi alamat sebuah direktori dengan fungsi strcat dan strcpy. Selanjutnya, membuat direktori dengan alamat yang sudah dibuat dengan mkdir, membuat loop sebanyak 30 kali, dimana di dalamnya digunakan sprintf untuk memformat sebuah string, lalu membuat file dengan nama string tersebut, membuka dan membaca log, mengcopy isi log tersebut ke file log yang baru. setelah itu, program berhenti selama 1 menit menggunakan fungsi sleep.
2. untuk menghentikan program, maka dapat menggunakan fungsi `pkill [nama_program]` dijalankan dengan fungsi exec di dalam c.
