//קישור למודל : https://www.tinkercad.com/things/jNpHslCdpAE
#include <IRremote.h>

int RECV_PIN = 11;
int red = 13;
int green = 9;
int  boxes [9] ;
int maturitylevelONE[9];
int maturitylevelTWO[9];
int maturitylevelThree[9];
int counterOne = 0;
int counterTwo = 0;
int counterThree = 0;
int sensePin = A1;  //This is the Arduino Pin that will read the sensor output
int sensorInput;    //The variable we will use to store the sensor input
double temp;        //The variable we will use to store temperature in degrees.
int chacktemptime = 0;
const int trigPin = 7;//ultrasonic trig pin
const int echoPin = 4;//ultrasonoc echo pin
long duration;//paramter for puslse from ultrasonic
long distance;//parameter for distance of ultrasonic
int buzzpin = 10;
int Thief = 0;//בכל לילה מתבצעת מקסימום גניבה אחת וזה ישמש אותנו לדעת זאת

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  Serial.begin(9600);

  irrecv.enableIRIn(); // Start the receiver
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    irrecv.resume(); // Receive the next value
    startday();
    delay(500);
  }

  ultrasonictodistance();
  delay(500);
}

void startday() {//תחילת יום
  if (results.value == 0xFD00FF) {//אם נלחץ כפתור תחילת יום
    Thief = 0;
    play();
    irrecv.resume();

    while (results.value != 0xFD00FF) {// כל עוד לא נלחץ על כפתור סיום יום נמשיך לבדוק טמפרטורה
      irrecv.resume();
      play();
      tempeturetest();
    }

    counterThree = counterTwo;//לאחר סיום יום כולם עולים בדרגת בשלות
    counterTwo = 0;
    counterTwo = counterOne;
    counterOne = 0;
  

    Serial.print("TYPE ONE: " );//ארגזים בסיום יום
    Serial.println(counterOne);
    delay(200);

    Serial.print("TYPE TWO: ");
    Serial.println(counterTwo);
    delay(200);
    Serial.print("TYPE THREE: ");
    Serial.println(counterThree);
    delay(200);
  }
}

void play() {//בודק לחיצה על כפתור הפליי
  while (!irrecv.decode(&results)) {//כל עוד לא לחצנו אל אף כפתור בודק בינתיים טמפרטורה
    tempetureFunction();
    tempeturetest();
  }
  if (irrecv.decode(&results)) {
    irrecv.resume();
    if (results.value == 0xFDA05F) {//כפתור פליי נלחץ
      Serial.println("Please enter button between 1-9:");
      while (!irrecv.decode(&results)) {//עד שלא לוחצים על מספר לא קורה כלום
delay(500);
      }
      irrecv.resume();
      numofboxes();
      ExitFacotyBlink();
    }//while
  }
}

void numofboxes() {// מכניס ארגזים באופן רנדומלי וממיין אותם
  switch (results.value) {
    case 0xFD08F7:
      for (int i = 0; i < 1; i++) {
        boxes[i] = random(1, 4);
        digitalWrite(green, HIGH);
        delay(200);
        digitalWrite(green, LOW);
        delay(200);
      }

      boxessortbylevel();
      break;
    case 0xFD8877:
      for (int i = 0; i < 2; i++) {
        boxes[i] = random(1, 4);
        digitalWrite(green, HIGH);
        delay(200);
        digitalWrite(green, LOW);
        delay(200);
      }
      boxessortbylevel();
      break;
    case 0xFD48B7:
      for (int i = 0; i < 3; i++) {
        boxes[i] = random(1, 4);
        digitalWrite(green, HIGH);
        delay(200);
        digitalWrite(green, LOW);
        delay(200);
      }
      boxessortbylevel();
      break;
    case 0xFD28D7:
      for (int i = 0; i < 4; i++) {
        boxes[i] = random(1, 4);
        digitalWrite(green, HIGH);
        delay(200);
        digitalWrite(green, LOW);
        delay(200);
      }
      boxessortbylevel();
      break;
    case 0xFDA857:
      for (int i = 0; i < 5; i++) {
        boxes[i] = random(1, 4);
        digitalWrite(green, HIGH);
        delay(200);
        digitalWrite(green, LOW);
        delay(200);
      }
      boxessortbylevel();
      break;
    case 0xFD6897:
      for (int i = 0; i < 6; i++) {
        boxes[i] = random(1, 4);
        digitalWrite(green, HIGH);
        delay(200);
        digitalWrite(green, LOW);
        delay(200);
      }
      boxessortbylevel();
      break;
    case 0xFD18E7:
      for (int i = 0; i < 7; i++) {
        boxes[i] = random(1, 4);
        digitalWrite(green, HIGH);
        delay(200);
        digitalWrite(green, LOW);
        delay(200);
      }
      boxessortbylevel();
      break;
    case 0xFD9867:
      for (int i = 0; i < 8; i++) {
        boxes[i] = random(1, 4);
        digitalWrite(green, HIGH);
        delay(200);
        digitalWrite(green, LOW);
        delay(200);
      }
      boxessortbylevel();
      break;
    case 0xFD58A7:
      for (int i = 0; i < 9; i++) {
        boxes[i] = random(1, 4);
        digitalWrite(green, HIGH);
        delay(200);
        digitalWrite(green, LOW);
        delay(200);
      }
      boxessortbylevel();
      break;
  }
  irrecv.resume();
  memset(boxes, 0, sizeof(boxes));//איפוס המערך להכנסה הבאה
}

void boxessortbylevel() {//מיון המערך לארגזים
  for (int i = 0; i < 9; i++) {
    if (boxes[i] == 1) {
      counterOne++;

    }
    else if (boxes[i] == 2) {
      counterTwo++;
    }
    else if (boxes[i] == 3) {

      counterThree++;
    }

  }
  delay(200);
}

void ExitFacotyBlink() { //הבהוב ארגזים יוצאים מהמפעל
  for (int i = 1; i <= counterThree; i++) {

    digitalWrite(red, HIGH);
    delay(200);
    digitalWrite(red, LOW);
    delay(200);
  }
  counterThree = 0;
}

void tempetureFunction() { //חידשוב הטמפרטורה מהחיישן
  sensorInput = analogRead(A1); //read the analog sensor and store it
  temp = (double)sensorInput / 1024;   //find percentage of input reading
  temp = temp * 5;                     //multiply by 5V to get voltage
  temp = temp - 0.5;                   //Subtract the offset
  temp = temp * 100;     //Convert to degrees
  //  Serial.println("Current Temperature: ");
  // Serial.println(temp);
  delay(300);
}

void tempeturetest() {//בדיקת הטמפרטורה
  tempetureFunction();
  delay(200);
  if (temp > 23 && chacktemptime == 0) {//אם הטמפרטורה גדולה מ-23 מתבצע עלייה בדרגת בשלות

    counterThree = counterTwo;
    counterTwo = 0;
    counterTwo = counterOne;
    counterOne = 0;
    ExitFacotyBlink();
    chacktemptime = 1;
  }
  if (temp <= 23 && chacktemptime == 1) {
    chacktemptime = 0;
  }
   delay(200);
}

void ultrasonictodistance() {//קריאה מחיישן מרחק
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = (pulseIn(echoPin, HIGH));
  distance = duration * ( 0.0454 / 2); // Calculating the distance
  // Prints the distance on the Serial Monitor
  //  Serial.print("Distance:");
  //  Serial.println(distance);
  if (distance < 100 && Thief == 0) {//אם הגנב מתקרב למרחק של עד 110 מטר מתבצעת גניבה
    myTone(buzzpin, 1000, 3000);
    steelboxs();
    Thief = 1;

  }
   delay(200);
}

void myTone(byte pin, uint16_t frequency, uint16_t duration) {//פונקציה מהמצגת להוצאת צליל מהחיישן
  unsigned long startTime = millis();
  unsigned long halfPeriod = 1000000L / frequency / 2;
  pinMode(pin, OUTPUT);
  while (millis() - startTime < duration) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(pin, LOW);
    delayMicroseconds(halfPeriod);
  }
  pinMode(pin, INPUT);
}

void steelboxs() {//גניבת ארגז
  Serial.println("The stolen crates:");
  int  Sboxes = 0;

  for   (int i = 1; i <= 3; i++) {
    Sboxes = random(1, 4);
    if (Sboxes == 1 && counterOne > 0) {
      counterOne--;
      Serial.print("1,");
    }
    else if  (Sboxes == 2 && counterTwo > 0) {
      counterTwo--;
      Serial.print("2,");
    }
    else if (Sboxes == 3 && counterThree > 0) {
      counterThree--;
      Serial.print("3,");
    }
  }
   delay(200);
}

//הנחות יסוד
//בתחילת העבודה יש למקום את העצם במרחק מעל 100 מהחיישן כדי שלא יזמזם  בתחילת הריצה
//לגנב אין מספיק זמן אם נכנס לאיזור בו מאוחסנים אחרזים מסוג מסוים ואיזור זה ריק הוא לא גונב כלום במקום
//לאחר לחיצה על פליי המשתמש יודע כי עליו ללחוץ על אחד המספרים, לחיצה אחרת תמשיך את התכנית והוא יצטרך ללחוץ על פליי שוב כדי להכניס
//מקרה קיצון
//עלייה של טמפרטורה למעל של 23 ולאחר מכן עלייה נוספת למעל לא תיתן עלייה בדרגת בשלות טיפלנו על ידי אינדיקטור
