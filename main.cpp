#include<LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo servo_9;
int pinL = 6;
int pinR = 0;
int pinC = 7;
int trigPin = 10; // Ultrasonic
int echoPin = 8;

void setup(){
    Serial.begin(9600); // Begin Serial communication at 9600 baud rate 
    servo_9.attach(9, 500, 2500);
    pinMode(pinL, INPUT);
    pinMode(pinR, INPUT);
    pinMode(pinC, INPUT);
    pinMode(1, INPUT);
    lcd.begin(16, 2); 
}

void loop(){
    //PIRState = digitalRead(1);

    lcd.clear();
    lcd.print("Seleccione modo:");
    lcd.setCursor(0, 1);
    lcd.print("<-Auto  Manual->");

    // Manual mode
    if (digitalRead(pinR == HIGH)){
        lcd.clear();
        do {
            lcd.setCursor(0,0);
            lcd.print("      Modo");
            lcd.setCursor(0,1);
            lcd.print("     Manual");
            if (digitalRead(pinC == 1)){
                for (int i = 1; i < 360*2; i++){
                    servo_9.write(i); // Servo Position
      	            delay(1);
                }
            }
        } while(digitalRead(pinL == 0));
    }

    // Auto mode
    int aux = 6; // 6 hours interval by default 
    do{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Elija intervalo");
        lcd.setCursor(1,0);
            lcd.print(("<-    " + String(aux) + " hrs   ->"));

        if (digitalRead(pinL == 1)){
            aux -= 1; // aux = 6 -> aux = 5
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Elija intervalo");
            lcd.setCursor(1,0);
            lcd.print(("<-    " + String(aux) + " hrs   ->"));
        }
        else if (digitalRead(pinR == 1)){
            aux += 1; // aux = 6  -> aux = 7
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Elija intervalo");
            lcd.setCursor(1,0);
            lcd.print(("<-    " + String(aux) + " hrs   ->"));
        }
        else{
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Elija intervalo");
            lcd.setCursor(1,0);
            lcd.print(("<-    " + String(aux) + " hrs   ->"));
        }
    } while (digitalRead(pinC == 0));

    while (true){
        delay(3600 * aux);
        if ((1+1)== true){ // Ultrasonic detection = 0
            for (int i = 1; i < 360*2; i++){
                servo_9.write(i); // Servo Position
                delay(1);
            }
        }
    }
}
