#include <Wire.h> 
#include <LiquidCrystal_I2C.h>//biblioteca display
LiquidCrystal_I2C lcd(0x27,20,4); 
#include <Adafruit_NeoPixel.h>  //biblioteca leduri
#define S0 2 //pini senzor culoare
#define S1 3 //pini senzor culoare
#define S2 4 //pini senzor culoare
#define S3 5 //pini senzor culoare
#define sensorOut 6  //pini senzor culoare
#define PIN            9 //pin leduri
#define NUMPIXELS      10 // numarul de leduri
int frequency = 0;
int color=0;
int x=0;
const int buton = 11;
int lastpozbuton=1;   
int i=-1,a=0,b=0,c=0;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// definire banda led neopixel 
void setup() {
  lcd.begin(16,2); 
  lcd.backlight();
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(buton, INPUT_PULLUP);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  pixels.begin();
  Serial.begin(9600);
   for(int i=0;i<NUMPIXELS;i++)// animatia de la inceput va rula o singura data (ledul alb)
   { 
   pixels.setPixelColor(i, pixels.Color(250,250,250)); //se aprinde ledul i
   pixels.show();
   pixels.setPixelColor(i-1, pixels.Color(0,0,0));//ledul anterior se stinge astfel se creaza efectul de miscare
   pixels.show();
   delay(50);
    }
  for(int i=NUMPIXELS;i>=-1;i--)// dupa ce ajunge ledul in capat adica la ultimul(10) miscarea se va face de la capat spre inceput(
   { 
   pixels.setPixelColor(i, pixels.Color(250,250,250)); // se aprinde ledul i in acest caz ledul 10, 
   pixels.show();
   pixels.setPixelColor(i+1, pixels.Color(0,0,0));//se stinge ledul 10 si se va aprinde ledul 9, 
   pixels.show();
   delay(50);
   
   }
   
}
void loop() 
  {
     lcd.init();
    int pozbuton = digitalRead(buton);//citire buton verde
    lcd.setCursor(0,0);//setare pozitia de unde va incepe scrisul in acest caz prima linie primul rand
    lcd.print("WELCOME!");//mesajul ce il va afisa  
 if(pozbuton==0)//daca se apasa pe buton vor citi culorile
    for(int j=0;j<8;j++)
  {               lcd.init();
    lcd.init();                      
    lcd.setCursor(0,0);
    lcd.print("Apropie culoarea!");
    delay(200);
    citireculoare();//se apeleaza functia de citire a culorii
    switch (color) {
    case 1:     // cazul in care culoarea este rosie
  {
     Serial.println(" ROSU ");
     lcd.setCursor(0,0);
     lcd.print(" culoarea este: ");
     delay(1000);
     lcd.setCursor(0,1); 
     lcd.print("......Rosu......");
     delay(2000);
     lcd.clear();
          i++; //i va creste pentru a se aprinde urmatorul led
          a=255;// valorile corespunzatoare culorii rosu la leduri( adica rosu va avea 255,0,0)
          b=0;// a se vedea coduri culori html
          c=0;
          j=0;
    
  }
   break;
    case 2:
 {
     Serial.println(" ALBASTRU ");
     lcd.setCursor(0,0);
     lcd.print(" culoarea este: ");
     delay(1000);
     lcd.setCursor(0,1); 
     lcd.print("....Albastru....");
     delay(2000);
     lcd.clear();
          i++;
          a=0;
          b=0;
          c=250; 
          j=0; 
  }
    break;
    case 3:
     {
       Serial.println(" VERDE");
       lcd.setCursor(0,0);
       lcd.print(" culoarea este: ");
       delay(1000);
       lcd.setCursor(0,1); 
       lcd.print("....VERDE....");
       delay(2000);
       lcd.clear();
       i++;
       a=0;
       b=250;
       c=0;  
       j=0; 
  }
   break;
    case 4:
    {
       Serial.println(" GALBEN ");
       lcd.setCursor(0,0);
       lcd.print(" culoarea este: ");
       delay(1000);
       lcd.setCursor(0,1); 
       lcd.print("....Galben....");
       delay(2000);
       lcd.clear();
       i++;
       a=255;
       b=255;
       c=0; 
       j=0; 
     }
    break;
     case 5:
    {
       Serial.println(" VIOLET ");
       lcd.setCursor(0,0);
       lcd.print(" culoarea este: ");
       delay(1000);
       lcd.setCursor(0,1); 
       lcd.print("....VIOLET....");
       delay(2000);
       lcd.clear();
       i++;
       a=75;
       b=0;
       c=130; 
       j=0; 
     }
    break;
   }
    delay(300);
    color=0;
      pixels.setPixelColor( i, pixels.Color(a,b,c));
      pixels.show();
    if(i==10)
    {  i=0;
      for(int j=0;j<10;j++)
      {
      pixels.setPixelColor( j, pixels.Color(0,0,0));
    pixels.show();
      }
    }
}
 
lastpozbuton=pozbuton;
}
int citireculoare()
 {
  digitalWrite(S2, LOW); 
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);//citeste valoarea senzorului pentru rosu
  int R = frequency;
  Serial.print(frequency);//afiseaza in serial valoarea pentru rosu
  Serial.print("  ");
  delay(50);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);//citeste valoarea pentru verde 
  int G = frequency;
  Serial.print(frequency);//afiseaza in serial valoarea pentru veerde
  Serial.print("  ");
  delay(50);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);////citeste valoarea pentru albastru
  int B = frequency;
  Serial.print(frequency);//afiseaza in serial valoarea corespunzatoare pentru albastru
  Serial.println("  ");
  delay(50);
  if(R<35 & R>18 & G<85 & G>65 & B<65 & B>40)//in cazul  in care valorile citite de la senzor sunt in acest interval culoarea va fi rosu
  {
    color = 1;
  }
  if(R<75 &R>58 & B<40 &B>20)////in cazul  in care valorile citite de la senzor sunt in acest interval culoarea va fi albastru
  {
    color = 2; 
  }
  if(R<70 & R>50 & G<55 & G>40)
  {
    color = 3; 
  }
  if(R<25 & R>13 & G<45 & G>20 & B<55 & B>20)
  {
    color = 4; 
  }
  
    if(R<60 & R>50 & B<45 & B>35)
  {
    color = 5; 
  }
  return color;  
}



