#include <LiquidCrystal.h>
#include <Keypad.h>
LiquidCrystal lcd(37,38,39,40,41,42);
const int lm35=A0;
int buzzer=22; 
int pirled=51;   
const int flamepin=A5;
const int pirpin=A4;
int flamecntrol=0;
int pircntrol;
int olcdrc;
int sicaklik;
int i=0;
int gled=32;
int rled=36;
const byte satir = 4;
const byte sutun = 3;
char password[4]={'1','2','3','4'};
char girilen[4];
char keys[satir][sutun] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[satir] = {26,27,28,29};
byte colPins[sutun] = {25,24,23};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins,satir, sutun);

  
void setup() {
pinMode(flamepin,INPUT);
pinMode(pirpin,INPUT);
pinMode(pirled,OUTPUT);
pinMode(buzzer,OUTPUT);
lcd.begin(16,2);
analogReference("INTERNAL1V1");
pinMode(gled,OUTPUT);
pinMode(rled,OUTPUT);


}
void loop(){
   olcdrc=analogRead(lm35);
   sicaklik = map (olcdrc, 0, 1023, 0, 255);
   lcd.clear();
   lcd.print("sicaklik = ");
   lcd.print(sicaklik);
   lcd.print("C");
   delay(10);
   
   if(sicaklik<20){
    lcd.setCursor(0,1);
    lcd.print("Sicaklik dustu");
    delay(10);
   }
   else if(sicaklik>30){
    lcd.setCursor(0,1);
    lcd.print("Sicaklik yukseldi");
    delay(10);
   }
   
   flamecntrol=digitalRead(flamepin);
   if(flamecntrol==HIGH){
      tone(buzzer,450);
    }
    else{
      noTone(buzzer);
    }
   pircntrol=digitalRead(pirpin);
   if(pircntrol==HIGH){
    digitalWrite(pirled,HIGH);
   }
   else{
    digitalWrite(pirled,LOW);
   }
      char key = keypad.getKey();
    if (key != NO_KEY){
     girilen[i]=key;
     i++;
     if(i==4){
      if(girilen[0]==password[0]) {
        if(girilen[1]==password[1]){
          if(girilen[2]==password[2]){
            if(girilen[3]==password[3]){
              digitalWrite(gled,HIGH);
              digitalWrite(rled,LOW);
              delay(1000);
              digitalWrite(gled,LOW);
              girilen[4]={};
            }
          }
        }
      }
      else{
        digitalWrite(rled,HIGH);
        digitalWrite(gled,LOW);
        delay(1000);
        digitalWrite(rled,LOW);
        girilen[4]={};
      }
      }
    }
}
