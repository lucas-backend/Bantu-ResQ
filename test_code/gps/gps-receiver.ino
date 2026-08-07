// GPS Receiver
#include <SPI.h>
#include <LoRa.h>

// Definisi pin LoRa ke ESP32 (Harus sama dengan Transmitter)
#define ss 5
#define rst 14
#define dio0 2

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("=== ESP32 LoRa GPS Receiver ===");

  // Konfigurasi pin LoRa
  LoRa.setPins(ss, rst, dio0);

  // Inisialisasi LoRa pada frekuensi 433 MHz (Sesuaikan dengan Transmitter)
  if (!LoRa.begin(433E6)) {
    Serial.println("Gagal mendeteksi modul LoRa. Cek kabel!");
    while (1);
  }
  
  Serial.println("LoRa Siap Menerima Data Lokasi GPS...");
}

void loop() {
  // Mengecek apakah ada paket (sinyal) yang masuk
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) {
    // Membaca isi paket
    String receivedData = "";
    while (LoRa.available()) {
      receivedData += (char)LoRa.read();
    }

    // Mencetak data ke Serial Monitor beserta RSSI (Kekuatan Sinyal)
    Serial.print("Data Masuk: [");
    Serial.print(receivedData);
    Serial.print("] | Sinyal (RSSI): ");
    Serial.println(LoRa.packetRssi());
  }
}