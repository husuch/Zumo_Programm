#include <Wire.h>
#include <Zumo32U4.h>

Zumo32U4Motors motors; 
Zumo32U4ButtonA buttonA; 
Zumo32U4LineSensors lineSensors; 
Zumo32U4ProximitySensors proxSensors;
Zumo32U4LCD lcd;

const uint8_t sensorThreshold = 1;
unsigned int lineSensorValues[3];
void setup()
{

  buttonA.waitForButton(); //Wartet bis der Konopf 'a' gedrückt wurde
  lineSensors.initThreeSensors(); //initialisiert den lineSensor
  proxSensors.initFrontSensor();//initialisiert den proxSensor
  delay(5000); //Wartet 5 sek, damit die Regeln nicht vereltzt werden
}

void loop()
{
  if (millis() <= 95000) { //Falls 95 sek noch nicht vorbei sein sollten
  int randDelay = random(150, 300); //generiert eine Zufällige Zahl
  lcd.clear(); //löscht alles, was im Display war

  proxSensors.read(); //Liest den Sensor-Wert aus
  lineSensors.read(lineSensorValues); //Liest den Sensor-Wert aus, für die 3 Sensoren

  uint8_t leftValue = proxSensors.countsFrontWithLeftLeds(); //übergiebt den Wert der Variable leftValue
  uint8_t rightValue = proxSensors.countsFrontWithRightLeds(); //übergiebt den Wert der Variable rightValue

  bool objectRight = rightValue >= sensorThreshold; //Schaut, ob ein Objekt rechts davon ist
  bool objectLeft = leftValue >= sensorThreshold; //Schaut, ob ein Objekt links davon ist

  if (lineSensorValues[0] < 1000) //Falls der Robotter auf die Weisse linie trifft
  {
    lcd.print("LB_02");
    motors.setLeftSpeed(-400); //Rückwertsfahren
    motors.setRightSpeed(-400);
    delay(randDelay); //für eine zufällige Zeit
    motors.setLeftSpeed(200); //Sich drehen, für eine zufällige Zeit
    motors.setRightSpeed(-200); //Sich drehen, für eine zufällige Zeit
    delay(randDelay);
} 
 else if (lineSensorValues[2] < 1000) //Falls der Robotter auf die Weisse linie trifft
  {
    lcd.print("LB_02");
    motors.setLeftSpeed(-400); //Rückwertsfahren
    motors.setRightSpeed(-400);
    delay(randDelay); //Rückwertsfahren
    motors.setLeftSpeed(-200); //Sich drehen, für eine zufällige Zeit
    motors.setRightSpeed(200); //Sich drehen, für eine zufällige Zeit
    delay(randDelay);
  }
  else if (objectLeft == false && objectRight == false){ //Fals weder auf einer Linie, noch ein Objekt davor ist

    motors.setLeftSpeed(200); //Such geschwindigkeit
    motors.setRightSpeed(200); //Such geschwindigkeit

  }
  else if (objectLeft && objectRight){ //Falls ein Objekt gerade aus ist

    motors.setLeftSpeed(400); //Angriff
    motors.setRightSpeed(400); //Angriff

  }
    else if(objectLeft || objectRight){ //Falls ein Objekt auf der Seite ist

     if(objectLeft){ //Falls es links ist
      motors.setLeftSpeed(100); //Nach links fahren
      motors.setRightSpeed(400); //Nach links fahren
    }
    else if(objectRight){ //Falls es Rechts ist
      motors.setLeftSpeed(400); //Nach rechts fahren
      motors.setRightSpeed(100); //Nach rechts fahren
    }


  }
  }else{ //Falls 90 sek abgelaufen sein sollten
    motors.setLeftSpeed(0); //Anhalten
    motors.setRightSpeed(0); //Anhalten
    lcd.print("Stop"); //Auf LCD "Stop" ausgeben
  }

}
