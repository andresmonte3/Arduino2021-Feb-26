#include <DHT.h>
#include <Servo.h>

  int temp_pin  = A0;
  int mov_pin   = A1;
  int hum_pin   = A2;
  int prox_pin  = A3;
  
  int led_pin     = 2;
  int vent_pin    = 4;
  int buzz_pin    = 5;
  
  Servo servo1;
  DHT dht (hum_pin, DHT11);

void setup(){

  pinMode(temp_pin, INPUT);
  pinMode(mov_pin, INPUT);
  pinMode(hum_pin, INPUT);
  pinMode(prox_pin, INPUT);
  
  pinMode(led_pin, OUTPUT);
  pinMode(vent_pin, OUTPUT);
  pinMode(buzz_pin, OUTPUT);

  servo1.attach(3);
  dht.begin();
  
  
  Serial.begin(9600); 
}


void loop(){
  
    // Sensor temperatura
    
        int valor =  analogRead(temp_pin);
        float miliVolt= (valor/1023.0)*5000;
        float celsius = miliVolt/10;
        
        Serial.print(celsius);
        Serial.print("  G Centigrados \n");
        delay(1000);
        
        
        if (celsius>=25){
            Serial.print(" Temperatura Alta ");
            Serial.print(celsius);
            Serial.print("  G Centigrados \n");
            digitalWrite(led_pin, HIGH);
        }
        else{
            digitalWrite(led_pin, LOW);
        }           
    //Sensor movimiento
    
        if (digitalRead(mov_pin) == HIGH){
            servo1.write(90);
            Serial.println("Abrir Puerta");
            delay(5000);
            }
        else{
            servo1.write(0);
            }

    //Sendor Humedad
    
        int hum = dht.readHumidity();
        Serial.print("Humedad: ");
        Serial.print(hum);
        Serial.print("% \n");
        delay(500);
        if (hum >= 60){
          digitalWrite(vent_pin, HIGH);
          delay(100);
        }

        else{
          digitalWrite(vent_pin, LOW);
          }
}
