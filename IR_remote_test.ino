//use old bootloader for nano also had to install new driver 
//IR tutorial --> https://www.circuitbasics.com/arduino-ir-remote-receiver-tutorial/ 
//RBG LED tutorial --> https://create.arduino.cc/projecthub/muhammad-aqib/arduino-rgb-led-tutorial-fc003e

//fire tv remote uses SONY protocol
//elegoo remote (0x......) use NEC protocol
//power =FFA25D
//vol+ =FF629D
//func/stop = FFE21D
//rewind =FF22DD
//pause play =FF02FD
//fast foward =FFC23D
//down = FFE01F
//vol- =FFA857
//up = FF906F
//0 = FF6897
//eq = FF9867
//st/rept = FFB04F
//1 = FF30CF
//2 = FF18E7
//3 = FF7A85
//4 = FF10EF
//5 = FF38C7
//6 = FF5AA5
//7 = FF42BD
//8 = FF4AB5
//9 = FF52AD




#include <IRremote.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

int red_light_pin= 9;
int green_light_pin = 10;
int blue_light_pin = 11;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
//  irrecv.blink13(true);

  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
void loop(){
 if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
        results.value = key_value;
         switch(results.value){
          case 0xFF30CF:         //remote 1
          RGB_color(255, 0, 0); // Red
          break;
          case 0xFF18E7:        // remote 2
          RGB_color(0, 255, 0); // Green
          break;
          case 0xFF7A85:        //remote 3
          RGB_color(0, 0, 255); // Blue
          break;
          case 0xFF10EF:            //remote 4
          RGB_color(255, 255, 125); // Raspberry
          break;
          case 0xFF38C7:          //remote 5      
          RGB_color(0, 255, 255); // Cyan
          break ;  
          case 0xFF5AA5:          //remote 6
          RGB_color(255, 0, 255); // Magenta
          break ;               
          case 0xFF42BD:          //remote 7
          RGB_color(255, 255, 0); // Yellow        
          break ;  
          case 0xFF4AB5:            //remote 8
          RGB_color(255, 255, 255); // White
          break ;          
        }
        key_value = results.value;
        irrecv.resume(); 
    }
  }
