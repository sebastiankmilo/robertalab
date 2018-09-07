#include <math.h> 
#include <LiquidCrystal_I2C.h> 
#include <Stepper.h> 
#include <RobertaFunctions.h>   // Open Roberta library 
RobertaFunctions rob;  

    
LiquidCrystal_I2C _lcd_L(0x27, 16, 2);
int _SPU_S = 2048;
Stepper Motor_S(_SPU_S, 6, 5, 4, 3);

 
void setup() 
{
    Serial.begin(9600); 
    _lcd_L.begin();
    
}

void loop() 
{
    
    _lcd_L.setCursor(0,1);
    _lcd_L.print("Hallo");
    Motor_S.setSpeed(10);
    Motor_S.step(_SPU_S*5);
}
