//Project Name:  Fire Fighting Robot
//Year/Semester: Third Year Second Semester
//Section: A | Lab Group: A1  | Group: 03


#include<Servo.h>    
Servo project;       
int pos = 0;
boolean fire = false;


//defining inputs
#define Forward_S 8 //Forward sensor
#define Left_S 9    //Left sensor
#define Right_S 10  //Right sensor


//defining outputs
#define LM1 2  //left motor
#define LM2 3  //left motor
#define RM1 4  //right motor
#define RM2 5  //right motor
#define pump 7

void setup()
{
  Serial.begin(9600);
  pinMode (Left_S, INPUT);
  pinMode (Right_S, INPUT);
  pinMode (Forward_S, INPUT);
  pinMode (LM1, OUTPUT);
  pinMode (LM2, OUTPUT);
  pinMode (RM1, OUTPUT);
  pinMode (RM2, OUTPUT);
  pinMode (pump, OUTPUT);
  pinMode (6, OUTPUT);
  project.attach(11);
  project.write(50);
}


void put_off_fire()
{
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);
  digitalWrite(pump, HIGH);
  delay(500);
  for (pos = 50; pos <= 130; pos += 1)
  {
    project.write(pos);
    Serial.println("Servo running");
    delay(10);
  }
  for (pos = 130; pos >= 50; pos -= 1) {
    project.write(pos);
    delay(10);
  }
  digitalWrite(pump, LOW);
  project.write(50);
  fire = false;
}
void loop() {
  project.write(90);


  
  if (digitalRead(Left_S) == 1 && digitalRead(Right_S) == 1 && digitalRead(Forward_S) == 1)  //if fire not detected all sensors are zero
  {
    //Do not move the robot
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    Serial.println("Stopped");

  }

  else if (digitalRead(Forward_S) == 0) //Fire ahead
  {
    digitalWrite(6, 65);
    
    //For Moving Forward
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    Serial.println("Going forward");
    fire = true;

  }
  else if (digitalRead(Left_S) == 0)    //Fire Left
  {
    digitalWrite (6, 130);
    
    //For Moving Left
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    Serial.println("Going left");
  }
  else if (digitalRead(Right_S) == 0)   //Fire Right
  {
    digitalWrite(6, 1300);
    
    //For Moving Right
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    Serial.println("Going right");
  }
  delay(250); 
  
  while (fire == true)
  {
    put_off_fire();
  }

}
