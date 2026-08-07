## Skema Rangkaian GPS ke ESP32

Koneksi komunikasi serial (UART) harus **disilangkan**: TX pada GPS masuk ke RX pada ESP32, dan sebaliknya.

| Modul GPS NEO-M8N | ESP32 WROOM (Transmitter) | Keterangan |
| --- | --- | --- |
| **VCC** | 3.3V | Catu daya modul GPS |
| **GND** | GND | Ground |
| **TX / TXD** | RX2 (GPIO 16) | Mengirim data dari GPS ke ESP32 |
| **RX / RXD** | TX2 (GPIO 17) | Menerima data dari ESP32 (Opsional, tapi baiknya dipasang) |

*(Catatan: Biarkan pin LoRa tetap terpasang sama seperti skema sebelumnya di GPIO 5, 14, 2, 23, 19, 18).*

---

## 2. Persiapan Library GPS

Anda memerlukan library tambahan untuk menerjemahkan data mentah (NMEA) dari satelit menjadi data lokasi yang mudah dibaca (Latitude & Longitude).

1. Di Arduino IDE, buka **Sketch > Include Library > Manage Libraries...**
2. Cari **"TinyGPSPlus"** oleh **Mikal Hart**.
3. Klik **Install**.

> **Tips Penting untuk Modul GPS NEO-M8N:**
> * Modul GPS membutuhkan ruang terbuka (*clear view of the sky*) untuk mengunci satelit pertama kali (proses *cold start*).
> * Tes alat ini di teras rumah atau di luar ruangan. Di dalam kamar, modul ini sangat sulit mendapatkan koordinat, sehingga tulisan yang muncul akan selalu "Mencari sinyal satelit GPS...".
> * Modul ini biasanya memiliki LED yang akan berkedip jika sudah berhasil mengunci sinyal satelit (GPS *Fix*).
