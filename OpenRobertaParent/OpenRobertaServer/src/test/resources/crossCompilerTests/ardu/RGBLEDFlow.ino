#include <math.h> 
#include <RobertaFunctions.h>   // Open Roberta library 
RobertaFunctions rob;  

    
int _led_red_R = 5;
int _led_green_R = 6;
int _led_blue_R = 3;

 
void setup() 
{
    Serial.begin(9600); 
    pinMode(_led_red_R, OUTPUT);
    pinMode(_led_green_R, OUTPUT);
    pinMode(_led_blue_R, OUTPUT);
    
}

void loop() 
{
    
    for (int i = 0; i < 255; i += 2) {
        for (int j = 0; j < 255; j += 2) {
            for (int k = 0; k < 255; k += 2) {
                analogWrite(_led_red_R, i);
                analogWrite(_led_green_R, j);
                analogWrite(_led_blue_R, k);
                
                delay(2);
                delay(1);
            }
            for (int m = -255; m < 0; m += 2) {
                analogWrite(_led_red_R, i);
                analogWrite(_led_green_R, j);
                analogWrite(_led_blue_R, - (m));
                
                delay(2);
                delay(1);
            }
            delay(1);
        }
        delay(1);
    }
}
