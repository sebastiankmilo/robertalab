#include <math.h> 
#include <RobertaFunctions.h>   // Open Roberta library 
RobertaFunctions rob;  

    
double item;
int _led_red_R = 6;
int _led_green_R = 5;
int _led_blue_R = 3;
int _taster_B = 2;
int _led_L = 13;

 
void setup() 
{
    Serial.begin(9600); 
    pinMode(_led_red_R, OUTPUT);
    pinMode(_led_green_R, OUTPUT);
    pinMode(_led_blue_R, OUTPUT);
    pinMode(_taster_B, INPUT);
    pinMode(_led_L, OUTPUT);
    
    item = 0;
}

void loop() 
{
    
    if ( digitalRead(_taster_B) == HIGH ) {
        if ( item == 0 ) {
            analogWrite(_led_red_R, 0);
            analogWrite(_led_green_R, 255);
            analogWrite(_led_blue_R, 0);
            
            item = 1;
            while (true) {
                if ( digitalRead(_taster_B) == HIGH == false ) {
                    break;
                }
                delay(1);
            }
        } else if ( item == 1 ) {
            analogWrite(_led_red_R, 0);
            analogWrite(_led_green_R, 0);
            analogWrite(_led_blue_R, 255);
            
            item = 2;
            while (true) {
                if ( digitalRead(_taster_B) == HIGH == false ) {
                    break;
                }
                delay(1);
            }
        } else if ( item == 2 ) {
            analogWrite(_led_red_R, 255);
            analogWrite(_led_green_R, 0);
            analogWrite(_led_blue_R, 0);
            
            item = 0;
            while (true) {
                if ( digitalRead(_taster_B) == HIGH == false ) {
                    break;
                }
                delay(1);
            }
        }
        digitalWrite(_led_L, HIGH);
    }
}
