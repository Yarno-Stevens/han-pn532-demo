# RFID Arduino Project

Dit project maakt gebruik van een **PN532 RFID/NFC-module** met een **Arduino** om gegevens te lezen en te schrijven op RFID-tags.

## Benodigdheden
- Arduino (bijv. Uno, Mega, etc.)
- PN532 RFID/NFC-module
- RFID-kaarten of -tags (MIFARE Classic 1K)
- Arduino IDE
- Adafruit PN532-bibliotheek

## Installatie
1. **Arduino IDE installeren**: Zorg ervoor dat je de Arduino IDE hebt geïnstalleerd.
2. **Bibliotheken toevoegen**:
   - Open de Arduino IDE
   - Ga naar `Sketch` > `Bibliotheek gebruiken` > `Bibliotheken beheren`
   - Zoek naar **Adafruit PN532** en installeer deze
3. **Sluit de hardware aan**:
   - SDA van de PN532 naar A4 (Arduino Uno)
   - SCL van de PN532 naar A5 (Arduino Uno)
   - Voeding (VCC) en GND correct aansluiten

## Functionaliteiten
Het project ondersteunt de volgende commando's via de seriële monitor:
- `W + tekst` : Schrijft een tekst (max. 16 tekens) naar de RFID-tag.
- `R` : Leest de opgeslagen tekst van de RFID-tag.
- `I` : Leest en toont de UID (unieke identificatie) van de RFID-tag.

## Gebruik
1. **Upload de code** naar je Arduino met de Arduino IDE.
2. **Open de seriële monitor** (`Baudrate: 115200`).
3. **Geef een commando**:
   - Voer `W jouwtekst` in om een tekst op de tag te schrijven.
   - Voer `R` in om de opgeslagen tekst uit te lezen.
   - Voer `I` in om de UID van de tag te bekijken.
4. **Houd een RFID-kaart of -tag voor de lezer** om de actie uit te voeren.

## Probleemoplossing
- **Geen PN532 gevonden?** Controleer de bekabeling.
- **Geen kaart gedetecteerd?** Zorg ervoor dat de kaart dichtbij genoeg is.
- **Schrijven/lezen mislukt?** Probeer een andere RFID-tag.

## Auteur
Dit project is ontwikkeld door **[Thijs](https://github.com/thijsdewitt) en [Yarno](https://github.com/Yarno-Stevens)**.

Veel succes met je RFID-project! 🚀
