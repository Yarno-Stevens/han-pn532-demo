#include <Wire.h>
#include <Adafruit_PN532.h>

#define SDA_PIN A4
#define SCL_PIN A5
Adafruit_PN532 nfc(SDA_PIN, SCL_PIN);

const uint8_t blok = 4; // Bloknummer voor lezen/schrijven (aan te passen tussen 4 en 63)
uint8_t keyA[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }; // Standaard sleutel

void setup() {
  Serial.begin(115200);
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.println("Geen PN532 gevonden! Check bekabeling.");
    while (1);
  }

  nfc.SAMConfig();
  Serial.println("Wacht op commando: W + de tekst (Schrijven), R (Lezen), I (UID)");
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();

    if (command == 'W') {
      while (!Serial.available());
      String input = Serial.readStringUntil('\n');
      input.trim(); 
      Serial.print("Hou je pas of tag ervoor om dit op te slaan: ");
      Serial.println(input);

      if (input.length() > 16) {
        Serial.println("Fout: Te lange tekst! Max 16 tekens.");
      } else {
        writeRFID(input);
      }
    } 
    
    else if (command == 'R') {
      Serial.println("hou de pas of tag ertegen om hem uit te lezen");
      readRFID();
    } 
    
    else if (command == 'I') {
      Serial.println("hou de pas of tag ertegen om hem uit te lezen");
      readUID();
    }
  }
}

void writeRFID(String text) {
  uint8_t uid[7], uidLength;
  if (!nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {
    Serial.println("Geen kaart gedetecteerd!");
    return;
  }

  Serial.println("Kaart gedetecteerd! Schrijven...");

  if (nfc.mifareclassic_AuthenticateBlock(uid, uidLength, blok, 0, keyA)) {
    uint8_t data[16] = { 0 };  // Begin met een lege array van 16 bytes

    text.toCharArray((char*)data, 16);

    if (nfc.mifareclassic_WriteDataBlock(blok, data)) {
      Serial.println("Schrijven geslaagd!");
    } else {
      Serial.println("Schrijven mislukt!");
    }
  } else {
    Serial.println("Authenticatie mislukt!");
  }
}

void readRFID() {
  uint8_t uid[7], uidLength;
  if (!nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {
    Serial.println("Geen kaart gedetecteerd!");
    return;
  }

  Serial.println("Kaart gedetecteerd! Lezen...");

  if (nfc.mifareclassic_AuthenticateBlock(uid, uidLength, blok, 0, keyA)) {
    uint8_t data[16];
    if (nfc.mifareclassic_ReadDataBlock(blok, data)) {
      Serial.print("Gelezen data: ");
      for (int i = 0; i < 16; i++) {
        if (data[i] != 0) {
          Serial.print((char)data[i]);
        }
      }
      Serial.println();
    } else {
      Serial.println("Lezen mislukt!");
    }
  } else {
    Serial.println("Authenticatie mislukt!");
  }
}

void readUID() {
  uint8_t uid[7], uidLength;
  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {
    Serial.print("UID: ");
    for (uint8_t i = 0; i < uidLength; i++) {
      Serial.print(uid[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  } else {
    Serial.println("Geen kaart gedetecteerd!");
  }
}
