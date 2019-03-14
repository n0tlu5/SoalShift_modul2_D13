# Laporan Penjelasan Soal Shift Modul 1

## Contents :
- [soal 1](#soal_1)
- [soal 2](#soal_2)
- [soal 3](#soal_3)
- [soal 4](#soal_4)
- [soal 5](#soal_5)

## soal 1 <a name="soal_1"></a>
Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama berkas yang memiliki ekstensi .png menjadi “[namaberkas]_grey.png”. Karena jumlah berkas yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.

Catatan : Tidak boleh menggunakan crontab.

### Jawab :
Buat program daemon dengan bahasa C yang memindahkan sekaligus me-rename berkas gambar milik kusuma (asumsi gambar berasal dari _folder_ /home/[user]/Downloads/) ke /home/[user]/modul2/gambar/.

[Source Code](/soal1/soal1.c)

### Langkah :

- Tentukan _full path_ berkas untuk _source_ dan _destination_ sesuai ketentuan soal.
- Gunakan `fork` dan `exec` untuk mengeksekusi command `mv` dengan argumen _source_ dan _destination_ dari poin 1.

## soal 2 <a name="soal_2"></a>
Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada berkas bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus berkas “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada berkas “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.

Catatan: Tidak boleh menggunakan crontab

### Jawab :
Buat program daemon dengan bahasa C yang mengecek keberadan berkas /home/[user]/hatiku/elen.ku, ubah permission berkas menjadi 777 jika user dan groupnya 'www-data', lalu hapus berkas. Atur daemon untuk berjalan setiap 3 detik.

[Source Code](/soal2/soal2.c)

### Langkah :

- Cek keberadaan berkas /home/[user]/hatiku/elen.ku.
- Cek user dan group dari berkas tersebut.
- Ubah permission dari berkas tersebut menjadi 777 jika user dan groupnya 'www-data'.
- Hapus berkas tersebut menjadi 777 jika user dan groupnya 'www-data'.

catatan : jalankan daemon dengan `sudo` agar memiliki _privilege_ untuk melakukan `chmod`.

## soal 3 <a name="soal_3"></a>
Diberikan berkas campur2.zip. Di dalam berkas tersebut terdapat _folder_ “campur2”. 
Buatlah program C yang dapat :
i)  mengekstrak berkas zip tersebut.
ii) menyimpan daftar berkas dari _folder_ “campur2” yang memiliki ekstensi .txt ke dalam berkas daftar.txt. 
Catatan:  
- Gunakan fork dan exec.
- Gunakan minimal 3 proses yang diakhiri dengan exec.
- Gunakan pipe
- Pastikan berkas daftar.txt dapat diakses dari text editor

### Jawab :
[Source Code](/soal3/soal3.c)

### Langkah :
- _Extract_ "campur2.zip" menggunakan `fork` dan `exec` command `unzip`.
- Pindah ke _directory_ yang baru saja dibuat dari proses `unzip`.
- Lakukan perintah `ls | grep .txt$ | cat > daftar.txt` menggunakan `pipe`, `fork`, dan `exec`.

## soal 4 <a name="soal_4"></a>
Dalam direktori /home/[user]/Documents/makanan terdapat berkas makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah berkas makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika berkas itu pernah dibuka, program Anda akan membuat 1 berkas makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

Contoh:
- berkas makan_enak.txt terakhir dibuka pada detik ke-1
- Pada detik ke-10 terdapat berkas makan_sehat1.txt dan makan_sehat2.txt

Catatan: 
- dilarang menggunakan crontab
- Contoh nama berkas : makan_sehat1.txt, makan_sehat2.txt, dst

### Jawab :
Buat program daemon dengan bahasa C yang mengecek waktu akses terakhir dari berkas /home/[user]/Documents/makanan/makan_enak.txt. Buat berkas makanan_sehat#.txt jika berkas tersebut diakses dalam waktu 30 detik ke belakang. Atur daemon untuk berjalan setiap 5 detik.

[Source Code](/soal4/soal4.c)

### Langkah :
- Dapatkan informasi waktu akses terakhir dari berkas /home/[user]/Documents/makanan/makan_enak.txt.
- Buat berkas makanan_sehat#.txt jika `waktu_sekarang - waktu_akses_terakhir <= 30`.
- Buka berkas /home/[user]/Documents/makanan/makan_enak.txt menggunakan `fopen` dengan _attribute_ "w" agar waktu akses terakhir tetap _up to date_.

## soal 5 <a name="soal_5"></a>
Kerjakan poin 1 dan 2 di bawah:

1. Buatlah program c untuk mencatat log setiap menit dari berkas log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log

    Ket:
    - Per 30 menit membuat _folder_ /[dd:MM:yyyy-hh:mm]
    - Per menit memasukkan log#.log ke dalam _folder_ tersebut
    - ‘#’ : increment per menit. Mulai dari 1
2. Buatlah program c untuk menghentikan program di atas.

NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

### Jawab :
Buat program daemon dengan bahasa C yang menyalin isi berkas /var/log/syslog ke /home/[user]/log/[dd:MM:yyy-hh:mm]/log#.log setiap 1 menit. Dengan ketentuan _folder_ bekerja akan berpindah setiap 30 menit.

[Source Code (1)](/soal5/soal5.c)

[Source Code (2)](/soal5/soal5_kill.c)

### Langkah :
- Jika [count]=30, buat _folder_ dengan format sesuai soal dan set nilai [count] menjadi 1.
- Salin isi berkas /var/log/syslog ke /home/[user]/log/[dd:MM:yyy-hh:mm]/log[count].log.
- _increment_ [count].

catatan : nilai _intial_ count adalah 30.