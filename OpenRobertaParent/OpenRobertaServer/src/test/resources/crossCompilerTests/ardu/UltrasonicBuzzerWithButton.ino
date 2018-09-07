#include <math.h> 
#include <RobertaFunctions.h>   // Open Roberta library 
RobertaFunctions rob;  

    
int _trigger_U = 7;
int _echo_U = 6;
double _signalToDistance = 0.03432/2;
int _taster_B = 2;
int _led_L = 13;
int _spiele_B2 = 11;

double _getUltrasonicDistance()
{
digitalWrite(_trigger_U, LOW);
delay(5);
digitalWrite(_trigger_U, HIGH);
delay(10);
digitalWrite(_trigger_U, LOW);
return pulseIn(_echo_U, HIGH)*_signalToDistance;
}
 
void setup() 
{
    Serial.begin(9600); 
    pinMode(_trigger_U, OUTPUT);
    pinMode(_echo_U, INPUT);
    pinMode(_taster_B, INPUT);
    pinMode(_led_L, OUTPUT);
    
}

void loop() 
{
    
    while (true) {
        if ( digitalRead(_taster_B) == HIGH == true ) {
            break;
        }
        delay(1);
    }
    for (int k0 = 0; k0 < 10; k0 += 1) {
        digitalWrite(_led_L, HIGH);
        delay(1000);
        digitalWrite(_led_L, LOW);
        if ( _getUltrasonicDistance() < 20 ) {
            tone(_spiele_B2,300, 100);
        }
        delay(1000);
        delay(1);
    }
}
