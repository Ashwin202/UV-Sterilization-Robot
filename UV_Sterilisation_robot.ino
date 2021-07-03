#define in1 5 //L298n Motor Driver pins.
#define in2 6
#define in3 10
#define in4 11
#define LED 13
int command; //Int to store app command state.
int Speed = 100; // 0 - 255.
int brakeTime = 45;
int brkonoff = 1; //1 for the electronic braking system, 0 for normal.

int stripf = 2;
int stripm = 3;
int buzz = 8;

int trigPin = 4;//yellow
int echoPin = 9;//green

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(LED, OUTPUT); //Set the LED pin.
  pinMode(stripf, OUTPUT);
  pinMode(stripm, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzz, OUTPUT);
  Serial.begin(9600);  //Set the baud rate to your Bluetooth module.
  digitalWrite(stripf, LOW);
  digitalWrite(stripm,LOW);
}

void loop() { 
  if (Serial.available() > 0) {
    command = Serial.read();
    Serial.print(command);    
    Stop(); //Initialize with motors stoped.    
      switch (command) {
      case 2:
      {
        right();
        break;
      }        
      case 1:
       { 
        left();
        break;
      }        
      case 4:
        back();
        break;
      case 3:
        forward();
        break;
      case 5:         
         break;
      case 9:
         maskmode();
         break;
      case 7:
         digitalWrite(stripf, HIGH);
         break;
      case 8:
         digitalWrite(stripf, LOW);
         break;
    }
    
  }
}

void forward() {
  
  analogWrite(in1, Speed);
  analogWrite(in3, Speed);
}

void back() {
  
  analogWrite(in2, Speed);
  analogWrite(in4, Speed);
}

void left() {
  
  analogWrite(in3, Speed);
  analogWrite(in2, Speed);
}

void right() {
  
  analogWrite(in4, Speed);
  analogWrite(in1, Speed);
}

void Stop() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
}

void maskmode()
 {
  for(int i=0;i<200; i++)
   {
   Stop();
   long duration, distance;
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(1000);
   digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin,HIGH);
   distance = (duration/2)/29.1;
   Serial.println(distance);
   delay(10);
   if(distance<=11)
     {
       digitalWrite(stripm,HIGH);
       digitalWrite(LED, HIGH);
       delay(6000);
       digitalWrite(buzz,HIGH);
       delay(2000);
       digitalWrite(buzz,LOW);
       digitalWrite(stripm,LOW);
       digitalWrite(LED,LOW);
     }
 }
 }
