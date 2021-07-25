#include<LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo servo_9;
int pinL = 6; // Left button
int pinR = 0; // Right button
int pinC = 7; // Center button to confirm
int trigPin = 10; // Ultrasonic sensor trigger pin
int echoPin = 8; // Ultrasonic sensor echo pin

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
    lcd.clear();
    lcd.print("Seleccione modo:");
    lcd.setCursor(0, 1);
    lcd.print("<-Auto  Manual->");

    // Manual mode
    if (digitalRead(pinR == HIGH)){ // If right button is pressed
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
        } while(digitalRead(pinL == 0)); // Do until left button is pressed
    }

    // Auto mode
    int aux = 6; // 6 hours interval by default 
    do{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Elija intervalo");
        lcd.setCursor(1,0);
        lcd.print(("<-    " + String(aux) + " hrs   ->"));
        // "<-    6 hrs   ->"

        if (digitalRead(pinL == 1)){ // If left button is pressed
            aux -= 1; // aux = 6 -> aux = 5
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Elija intervalo");
            lcd.setCursor(1,0);
            lcd.print(("<-    " + String(aux) + " hrs   ->"));
            // "<-    5 hrs   ->"

        }
        else if (digitalRead(pinR == 1)){ // If right button is pressed
            aux += 1; // aux = 6  -> aux = 7
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Elija intervalo");
            lcd.setCursor(1,0);
            lcd.print(("<-    " + String(aux) + " hrs   ->"));
            // "<-    7 hrs   ->"

        }
        else{
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Elija intervalo");
            lcd.setCursor(1,0);
            lcd.print(("<-    " + String(aux) + " hrs   ->"));
            // "<-    6 hrs   ->"

        }
    } while (digitalRead(pinC == 0)); // Do until center button is pressed

    while (true){
        delay(3600 * aux); // Delay for the selected interval
        if ((1+1)== true){ // It should be Ultrasonic detection = 0
            for (int i = 1; i < 360*2; i++){
                servo_9.write(i); // Move servo
                delay(1); 
            }
        }
    }
}
