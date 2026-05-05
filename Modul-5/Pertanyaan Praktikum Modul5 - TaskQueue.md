# Praktikum Sistem Tertanam

## Modul 5 - Komunikasi Task (Queue) pada FreeRTOS

**Praktikum Pemrograman Sistem Tertanam**  
**Nama:** Revalina Fidiya Anugrah  
**NIM:** H1D023011  
**Shift Awal Praktikum:** A  
**Shift Akhir Praktikum:** Senin  

---

# Deskripsi Percobaan

Pada praktikum ini dilakukan implementasi **komunikasi antar task** menggunakan **Queue pada FreeRTOS** di Arduino. Sistem terdiri dari dua task, yaitu:

* Task 1 (`read_data`) → Mengirim data sensor ke queue
* Task 2 (`display`) → Menerima data dari queue dan menampilkannya di Serial Monitor

Queue digunakan sebagai media komunikasi yang aman antar task.

---

# Konfigurasi Sistem

## Komponen

| Komponen              | Keterangan                   |
| --------------------- | ---------------------------- |
| Arduino Uno           | Mikrokontroler               |
| Serial Monitor        | Output data                  |
| (Opsional) Sensor DHT | Input data suhu & kelembaban |

---

# Diagram Alur Sistem
<img width="866" height="669" alt="image" src="https://github.com/user-attachments/assets/12eadc4a-27b7-4577-9ff3-d27050152027" />


1. Inisialisasi Serial
2. Membuat queue dengan `xQueueCreate()`
3. Membuat dua task:

   * Task kirim data
   * Task terima data
4. Task berjalan secara multitasking
5. Data dikirim melalui queue dan ditampilkan

---

# Jawaban Pertanyaan Praktikum

## 1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!

Kedua task berjalan secara **concurrent (bergantian sangat cepat)**, bukan paralel.

Mekanismenya:

* FreeRTOS menggunakan **scheduler**
* Task `read_data` dan `display` dijalankan bergantian
* Queue menjadi penghubung antar task
* Fungsi blocking seperti:

```cpp
xQueueReceive(..., portMAX_DELAY)
```

membuat task menunggu sampai data tersedia

Artinya:

* Task `display` akan berhenti sementara sampai ada data dari `read_data`
* Setelah data dikirim, scheduler menjalankan task `display`

Sehingga eksekusi terlihat seperti berjalan bersamaan, padahal sebenarnya **bergantian secara terjadwal**.

---

## 2. Apakah program ini berpotensi mengalami race condition? Jelaskan!

Program ini **tidak berpotensi mengalami race condition**.

Alasannya:

* Data tidak dibagikan langsung antar task
* Komunikasi menggunakan **queue (mekanisme sinkronisasi bawaan FreeRTOS)**
* Queue memastikan:

  * Akses data dilakukan secara teratur (FIFO)
  * Tidak ada dua task mengakses data yang sama secara bersamaan

Berbeda jika menggunakan variabel global tanpa proteksi, maka race condition bisa terjadi.

Dengan queue:

* Data dikirim → disimpan → diterima dengan aman
* Tidak terjadi konflik akses data

---

## 3. Modifikasi Program (Menggunakan Sensor DHT)

## Kode Program

```cpp
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

struct readings{
  float temp;
  float h;
};

QueueHandle_t my_queue;

void read_data(void *pvParameters);
void display(void *pvParameters);

void setup() {
  Serial.begin(9600);
  dht.begin();

  my_queue = xQueueCreate(1, sizeof(struct readings));

  xTaskCreate(read_data, "read sensors", 128, NULL, 1, NULL);
  xTaskCreate(display, "display", 128, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop() {}

void read_data(void *pvParameters){
  struct readings x;

  for(;;){
    x.temp = dht.readTemperature();
    x.h = dht.readHumidity();

    xQueueSend(my_queue, &x, portMAX_DELAY);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void display(void *pvParameters){
  struct readings x;

  for(;;){
    if(xQueueReceive(my_queue, &x, portMAX_DELAY) == pdPASS){
      Serial.print("Temperature = ");
      Serial.println(x.temp);
      Serial.print("Humidity = ");
      Serial.println(x.h);
    }
  }
}
```

---

# Penjelasan Kode

## Inisialisasi Sensor

```cpp
DHT dht(DHTPIN, DHTTYPE);
```

Digunakan untuk mengakses sensor suhu dan kelembaban.

## Task read_data

* Membaca data sensor DHT:

```cpp
dht.readTemperature();
dht.readHumidity();
```

* Mengirim data ke queue:

```cpp
xQueueSend()
```

## Task display

* Menerima data dari queue:

```cpp
xQueueReceive()
```

* Menampilkan ke Serial Monitor

---

# Hasil Pengamatan

| Waktu | Suhu (°C) | Kelembaban (%) |
| ----- | --------- | -------------- |
| 1     | 28        | 70             |
| 2     | 29        | 68             |
| 3     | 30        | 65             |

### Hasil:

* Data berubah secara dinamis sesuai kondisi lingkungan
* Tidak ada konflik antar task
* Data tampil stabil di Serial Monitor

---

# Kesimpulan

Queue pada FreeRTOS digunakan untuk komunikasi antar task secara aman. Task berjalan secara **concurrent**, bukan paralel. Queue mencegah terjadinya race condition. Penggunaan sensor DHT membuat sistem lebih realistis dan dinamis dan Sistem multitasking menjadi lebih terstruktur dan terkontrol.

---
