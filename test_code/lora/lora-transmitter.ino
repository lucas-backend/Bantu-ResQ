// TRANSMITTER
#include <SPI.h>
#include <LoRa.h>

// Definisi pin LoRa ke ESP32
#define ss 5
#define rst 14
#define dio0 2

int counter = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("ESP32 LoRa Transmitter");

  // Konfigurasi pin LoRa
  LoRa.setPins(ss, rst, dio0);

  // Inisialisasi LoRa pada frekuensi 433 MHz (Sesuai modul AI-Thinker LoRa-02)
  if (!LoRa.begin(433E6)) {
    Serial.println("Gagal mendeteksi modul LoRa. Cek kabel!");
    while (1); // Berhenti di sini jika gagal
  }
  
  Serial.println("LoRa Berhasil Diinisialisasi!");
}

void loop() {
  Serial.print("Mengirim paket ke-");
  Serial.println(counter);

  // Mulai mengirim paket
  LoRa.beginPacket();
  LoRa.print("Halo dari ESP32! Paket #");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  delay(2000); // Jeda 2 detik sebelum mengirim lagi
}