#include <dht.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //Setzt die Verbinder für das LCD Display

dht DHT; 

#define DHT11_PIN 2 //Definiert den Pin 2 als DHT11_PIN
#define R_Pin 13 // Definiert den Pin 13 als R_Pin, ist Rot für die RGB LED
#define B_Pin 12 // Definiert den Pin 12 als B_Pin, ist Blau für die RGB LED
#define G_Pin 11 // Definiert den Pin 11 als G_Pin, ist Grün für die RGB LED

void setup() {
  lcd.begin(16, 2); //Definiert den Beginn des LCD-Display
  pinMode(R_Pin, OUTPUT); //Macht, dass das LED heller leuchtet
  pinMode(G_Pin, OUTPUT); //Macht, dass das LED heller leuchtet
  pinMode(B_Pin, OUTPUT); //Macht, dass das LED heller leuchtet
}

void loop()
{
  digitalWrite(R_Pin, LOW); //Setzt die Stärke des Roten-Lämpchen auf aus/schwach
  digitalWrite(G_Pin, LOW); //Setzt die Stärke des Grünen-Lämpchen auf aus/schwach
  digitalWrite(B_Pin, LOW); //Setzt die Stärke des Blauen-Lämpchen auf aus/schwach

  lcd.clear(); //Gibt ein leeres LCD-Display aus
  lcd.setCursor(0, 0); //Setzt den Deginn des LCD-Display
if (DHT.temperature == -999  DHT.humidity == -999) { //Wenn der Sensor am Kalbirieren ist
    digitalWrite(B_Pin, HIGH); //Mache das Blaue Licht des RGB-LED auf stark
    lcd.print("Calibrate"); //Gib auf dem LCD-Display "Calibrate" aus
    delay(500); //Macht einen Delay, damit das Blau schön gesehen werden kann
  } else { //Sonst

    lcd.print("Temp: "); //Gib auf dem LCD-Display "Temp: " aus
    lcd.print(DHT.temperature); //Gib auf dem LCD-Display die Temperatur aus
    lcd.print((char)223); //Macht einen Abstand auf dem Display
    lcd.print("C"); //Gib auf dem LCD-Display "C" aus, für Celsius


    lcd.setCursor(0, 1); //Geht auf dem Display eine Zeile nach unten
    lcd.print("Humidity: "); //Gib auf dem LCD-Display "Humidity" aus
    lcd.print(DHT.humidity); //Gib auf dem LCD-Display die Luftfeuchtigkeit aus
    lcd.print("%"); //Gib auf dem LCD-Display "%" aus, für die '%' der Luftfeuchtigkeit

    //Falls die Temperatur oder die Luftfeuchtigkeit in einem "kritischen" Zustand ist
    if (DHT.temperature > 50  DHT.temperature < -50  DHT.humidity > 50  DHT.humidity < 0) {
      digitalWrite(R_Pin, HIGH); //Mache das LED Rot
      delay(1000); //Mache einen Delay, um das Rot wirken zu lassen
    } else { //Sonst ist alles OK
      digitalWrite(G_Pin, HIGH); //Setzt das LED auf Grün
      delay(1000); //Macht einen Delay, um das Grün wirken zu lassen
    }
  }
}
