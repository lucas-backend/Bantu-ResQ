## Skema Rangkaian (Wiring)

Hubungkan pin modul LoRa-02 ke masing-masing ESP32 dengan skema berikut. Gunakan pin 3.3V, **jangan gunakan 5V** karena akan merusak modul LoRa.

| LoRa-02 (AI-Thinker) | ESP32 (32D & 32U) | Keterangan                   |
| -------------------- | ----------------- | ---------------------------- |
| **VCC**              | 3.3V              | Daya (Hati-hati, wajib 3.3V) |
| **GND**              | GND               | Ground                       |
| **NSS / CS**         | D5 (GPIO 5)       | SPI Chip Select              |
| **MOSI**             | D23 (GPIO 23)     | SPI MOSI                     |
| **MISO**             | D19 (GPIO 19)     | SPI MISO                     |
| **SCK / SCL**        | D18 (GPIO 18)     | SPI Clock                    |
| **RST**              | D14 (GPIO 14)     | Reset LoRa                   |
| **DIO0**             | D2 (GPIO 2)       | Interrupt (Wajib dipasang)   |

## Persiapan Library

Di Arduino IDE, Anda perlu menginstal library LoRa:

1. Buka **Sketch > Include Library > Manage Libraries...**
2. Cari **"LoRa"** oleh **Sandeep Mistry**.
3. Klik **Install**.
