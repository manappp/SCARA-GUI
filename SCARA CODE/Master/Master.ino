#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6); // RX, TX

String inputString = "";
bool newData = false;

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);

  Serial.println("MASTER READY");
  Serial.println("Input dua angka: contoh 120,90");
}

void loop() {
  serialEventHandler();

  if (newData) {
    newData = false;

    int comma = inputString.indexOf(',');
    if (comma == -1) {
      Serial.println("Format salah! Gunakan: 120,90");
      inputString = "";
      return;
    }

    float s1 = inputString.substring(0, comma).toFloat();
    float s2 = inputString.substring(comma + 1).toFloat();

    String kirim = String(s1) + "," + String(s2) + "\n";

    // kirim ke semua slave
    mySerial.print(kirim);

    Serial.print("Mengirim: ");
    Serial.println(kirim);

    inputString = "";
  }
}

void serialEventHandler() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c=='\n' || c=='\r') newData = true;
    else inputString += c;
  }
}
