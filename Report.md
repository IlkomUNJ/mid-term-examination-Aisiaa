[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/ZCO_vauY)
Repository for final lesson before mid term of computer graphic course
Computer Graphhics Midterm Exam Report

Ukuran Window yang Saya Pakai yaitu W=50x50 piksel.
Langkah Geser (Step Size): S=5 piksel.

Kenapa Saya Memilih Parameter Ini:
Setelah mencoba beberapa ukuran, saya putuskan 50X50  adalah yang paling pas. Ukuran ini cukup besar untuk mencakup segmen garis, tapi tidak terlalu besar sampai menangkap noise berlebihan. Saya pakai langkah geser S=5 karena saya ingin window ini bergeser sedikit-sedikit (tumpang tindih yang tinggi). Tujuannya jelas, supaya tidak ada sedikit pun bagian garis yang terlewat saat proses scanning deteksi.

lalu Temuan dari Console Dump 

Ini adalah bagian paling penting. Setelah saya suruh kode untuk mencatat semua window non-kosong ke konsol, saya menemukan pola yang jelas: Segmen garis lurus yang saya gambar (lebar 4 piksel) selalu menghasilkan sekitar 6 piksel berwarna di dalam window 50x50 ini.

Contoh data di konsol yang jadi acuan:
WINDOW_DUMP: ( 285 , 130 ) | Piksel Berwarna: 6

untuk Tujuan ke 3

Berdasarkan temuan angka 6 di atas, saya merancang dua kriteria filter di fungsi checkSegmentPattern untuk memastikan hanya segmen yang valid yang terdeteksi, bukan sekadar noise acak.

kemudian Hasil Akhir dan Verifikasi
lhasil, algoritma ini berhasil mendeteksi segmen garis dengan sangat akurat. Setelah melakukan penyesuaian pada objek di kanvas (mengganti atau menambah segmen), log konsol mengonfirmasi hasil terbaru:

[INFO] Analisis selesai. Total kandidat terdeteksi: 200

Jumlah 200 kandidat ini makes sense. Dibandingkan dengan hasil sebelumnya (96 kandidat untuk 2 segmen), ini menunjukkan bahwa saat ini program berhasil mendeteksi sekitar empat segmen garis yang berbeda (karena 4x50=200, dengan asumsi setiap segmen menghasilkan window tumpang tindih) atau ada objek lain yang terdeteksi. Verifikasi visual pada kanvas menunjukkan bahwa seluruh area segmen garis yang terdeteksi ditutup dengan rapi oleh kotak-kotak magenta, yang membuktikan semua tujuan proyek sudah tercapai.
