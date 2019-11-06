#include <Servo.h>
#define FLAME 2 //Verbindet DO pin vom Feuer-Sensor mit dem Pin 2
#define ALARM 9 //Verbindet DO pin vom Alarm-Sensor mit dem Pin 9
#define LEDR 5 //Verbindet DO pin vom LEDF=Rot-Sensor mit dem Pin 5
#define LEDF 6 //Verbindet DO pin vom LEDF=Grün-Sensor mit dem Pin 6
#define LEDRED 11 //Verbindet DO pin vom LED-Rot-Sensor mit dem Pin 11
#define LEDREDTWO 12 //Verbindet DO pin vom LED-Rot2-Sensor mit dem Pin 12
Servo servo;
int angle = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Nicolas und Anthony Feuer Tester");
  pinMode(FLAME, INPUT);//definiert Feuer input pin
  pinMode(ALARM, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDF, OUTPUT);
  pinMode(LEDRED, OUTPUT);
  pinMode(LEDREDTWO , OUTPUT);
  servo.attach(8);
  servo.write(angle);
}


void loop()
{
   digitalWrite(LEDF, HIGH); //Wenn kein Feuer leuchtet es Grün
  int feuer = digitalRead(FLAME); //LiestFeuer Sensor
  if ( feuer == HIGH ) {        //Wenn Feuer dann
    digitalWrite(ALARM, HIGH);  //Alarm geht los
    tone(9, 200);
    Serial.println("Feuer"); //Meldung
    //led gehen an und aus
    digitalWrite(LEDR, HIGH); 
    digitalWrite(LEDF, LOW); 
    digitalWrite(LEDRED, HIGH); 
     digitalWrite(LEDREDTWO, HIGH);
    for (angle = 0; angle < 200; angle++) //Rad dreht sich --> Scanne von 0 zu 200 Grad
    {
      servo.write(angle);
      delay(1);
    }
    for (angle = 200; angle > 0; angle--)    //Scanne zurück von 200 zu 0 Grad
    {
      servo.write(angle);

      delay(1);
    }


  }
  //Kein Feuer mehr
  else {
    digitalWrite(ALARM, LOW);  //Alarm geht aus
    noTone(9);
    digitalWrite(LEDR, LOW); //Led-Rot geht aus
    digitalWrite(LEDRED, LOW); //Rad-Led1 gehen aus
    digitalWrite(LEDREDTWO, LOW); //Rad-Led2 gehen aus
    Serial.println("Kein Feuer"); //Meldung das kein Feuer vorhanden ist
  }

  delay(200);
}
