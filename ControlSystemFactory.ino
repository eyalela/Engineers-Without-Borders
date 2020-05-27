#include <IRremote.h>

int RECV_PIN = 11;
int red =13;
int green = 9;
int  boxes [9] ;
int maturitylevelONE[9];
int maturitylevelTWO[9];
int maturitylevelThree[9];
int counterOne = 0;
int counterTwo = 0;
int counterThree = 0;
const int temperaturePin = 0;
float voltage;
float degreesC;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    startday();
    play();
    ExitFacotyBlink();
    
  }
  delay(100);
  }
void startday(){
    
  if(results.value==0xFD00FF){
      digitalWrite(red, HIGH);
        digitalWrite(green, LOW);
        
    }
  tempetureFunction();
}
void play(){
 
  if(results.value==0xFDA05F){
    Serial.println("please enter button ");
    while(!irrecv.decode(&results)){
      
    }
  numofboxes();
    boxessortbylevel();
     Serial.println(counterOne);
     Serial.println(counterTwo);
     Serial.println(counterThree); 
   }//while2
}
void numofboxes(){
  switch(results.value){
    case 0xFD08F7:
    for(int i=0;i<1;i++){
      boxes[i]=random(1,4);
        digitalWrite(green, HIGH);
        delay(500);
      digitalWrite(green, LOW);
        delay(500);
    }
      
      
    break;
    case 0xFD8877:
      for(int i=0;i<2;i++){
      boxes[i]=random(1,4);
        digitalWrite(green, HIGH);
        delay(500);
      digitalWrite(green, LOW);
        delay(500);
    }
    break;
    case 0xFD48B7:
        for(int i=0;i<3;i++){
      boxes[i]=random(1,4);
        digitalWrite(green, HIGH);
        delay(500);
      digitalWrite(green, LOW);
        delay(500);
    }
    break;
    case 0xFD28D7:
        for(int i=0;i<4;i++){
      boxes[i]=random(1,4);
        digitalWrite(green, HIGH);
        delay(500);
      digitalWrite(green, LOW);
        delay(500);
    }
    break;
    case 0xFDA857:
        for(int i=0;i<5;i++){
      boxes[i]=random(1,4);
        digitalWrite(green, HIGH);
        delay(500);
      digitalWrite(green, LOW);
        delay(500);
    }
    break;
    case 0xFD6897:
        for(int i=0;i<6;i++){
      boxes[i]=random(1,4);
        digitalWrite(green, HIGH);
        delay(500);
      digitalWrite(green, LOW);
        delay(500);
    }
    break;
    case 0xFD18E7:
        for(int i=0;i<7;i++){
      boxes[i]=random(1,4); 
        digitalWrite(green, HIGH);
        delay(500);
      digitalWrite(green, LOW);
        delay(500);
    }
    break;
    case 0xFD9867:
        for(int i=0;i<8;i++){
      boxes[i]=random(1,4);
        digitalWrite(green, HIGH);
        delay(500);
      digitalWrite(green, LOW);
        delay(500);
    }
    break;
    case 0xFD58A7:
         for(int i=0;i<9;i++){
      boxes[i]=random(1,4);
        digitalWrite(green, HIGH);
        delay(500);
      digitalWrite(green, LOW);
        delay(500);
    }

    break;
  }
}
void boxessortbylevel(){

  for(int i=0; i<9;i++){
    if(boxes[i]==1){
          counterOne++;
        
    }
    else if(boxes[i]==2){
            counterTwo++;
    }
    else if(boxes[i]==3){
        
      counterThree++;
    }
    
  }
}
void ExitFacotyBlink(){//הבהוב ארגזים יוצאים מהמפעל
  for(int i=0; i<counterThree;i++){
        digitalWrite(red, HIGH);
        delay(500);
      digitalWrite(red, LOW);
        delay(500);
    counterThree--;
    
  }
}
void tempetureFunction(){
 voltage = getVoltage(temperaturePin);
  degreesC = (voltage - 0.5) * 100.0;
  Serial.println("  deg C: ");
  Serial.println(degreesC);
  delay(1000);
}
float getVoltage(int pin){
   return (analogRead(A1) * 0.004882814);
}
