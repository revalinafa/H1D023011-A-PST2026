# Praktikum Sistem Tertanam

## Modul 5 - Real-Time Operating System (RTOS)

**Praktikum Pemrograman Sistem Tertanam**  
**Nama:** Revalina Fidiya Anugrah  
**NIM:** H1D023011  
**Shift Awal Praktikum:** A  
**Shift Akhir Praktikum:** Senin  

---
<img width="720" height="1280" alt="WhatsApp Image 2026-05-04 at 09 25 a59" src="https://github.com/user-attachments/assets/84c76bae-eb34-45f5-bdde-f5bbc1f372a9" />

# Deskripsi Percobaan

Pada praktikum ini dipelajari konsep **Real-Time Operating System (RTOS)** menggunakan **FreeRTOS pada Arduino**. Percobaan terdiri dari dua bagian utama, yaitu:

1. **Multitasking** → menjalankan beberapa task secara bersamaan (concurrent)
2. **Komunikasi Task (Queue)** → pertukaran data antar task secara aman

RTOS memungkinkan sistem embedded menjalankan beberapa proses secara terstruktur dan efisien sesuai kebutuhan waktu (real-time).

---

# Dasar Teori

**Real-Time Operating System (RTOS)** adalah sistem operasi yang dirancang untuk menangani proses secara langsung dengan waktu respon yang cepat dan terprediksi.
<img width="1402" height="638" alt="image" src="https://github.com/user-attachments/assets/4fb9237f-c1a4-48e2-b5eb-580755f96f4f" />


Jenis RTOS:

* **Soft RTOS** → toleransi keterlambatan masih diperbolehkan
* **Hard RTOS** → harus memenuhi deadline, jika tidak sistem gagal

FreeRTOS merupakan RTOS open-source yang banyak digunakan karena ringan dan mudah diimplementasikan pada mikrokontroler seperti Arduino.

---

# Percobaan 5A - Multitasking

## Deskripsi

Pada percobaan ini, sistem menjalankan beberapa task secara bersamaan:

* Task LED 1
* Task LED 2
* Task counter

## Konsep Utama

* `xTaskCreate()` → membuat task
* `vTaskStartScheduler()` → menjalankan scheduler
* `vTaskDelay()` → delay non-blocking

## Hasil

* LED dapat berkedip dengan interval berbeda
* Serial monitor menampilkan output dari beberapa task
* Sistem berjalan secara multitasking

---

# Percobaan 5B - Komunikasi Task (Queue)

## Deskripsi

Pada percobaan ini digunakan **queue** untuk komunikasi antar task:

* Task 1 → mengirim data
* Task 2 → menerima dan menampilkan data

## Konsep Utama

* `xQueueCreate()` → membuat queue
* `xQueueSend()` → mengirim data
* `xQueueReceive()` → menerima data

## Hasil

* Data dapat dikirim antar task dengan aman
* Tidak terjadi konflik data
* Output tampil stabil di Serial Monitor

---

# Jawaban Pertanyaan Praktikum

## 1. Perbedaan loop() Arduino biasa dengan sistem RTOS

Pada Arduino biasa:

* Semua program berjalan di dalam `loop()` secara berurutan
* Tidak ada pembagian task

Pada sistem RTOS:

* Program dibagi menjadi beberapa task
* Task dijalankan oleh scheduler
* Mendukung multitasking

---

## 2. Mengapa fungsi loop() dibiarkan kosong?

Pada sistem RTOS:

* Fungsi utama dijalankan oleh scheduler
* Semua proses sudah ditangani oleh task

Sehingga:

```cpp
void loop() {}
```

tidak digunakan karena tidak diperlukan lagi.

---

## 3. Insight utama dari praktikum

Beberapa insight yang diperoleh:

* RTOS memungkinkan multitasking pada sistem embedded
* Scheduler mengatur pembagian waktu CPU secara efisien
* Queue memungkinkan komunikasi antar task secara aman
* Sistem menjadi lebih modular dan terstruktur
* RTOS sangat penting untuk sistem kompleks seperti IoT dan otomasi

---

