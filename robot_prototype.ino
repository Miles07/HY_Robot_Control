//Arduino Human Following Robot
// Created By DIY Builder
// You have to install the AFMotor and NewPing library Before Uploading the sketch
// You can find all the required libraris from arduino library manager.
// Contact me on instagram for any query(Insta Id : diy.builder)
// Modified 7 Mar 2022
// Version 1.1


//include the library code:         

#define TRIGGER_PIN 6         // Trigger pin connected to analog pin A1 of Arduino Uno:
#define ECHO_PIN 5            // Echo pin connected to analog pin A0 of Arduino Uno:
#define MAX_DISTANCE 200      // Maximum ping distance:

unsigned int distance = 0;    //Variable to store ultrasonic sensor distance:
unsigned int duration = 0;   

int motorPin = 3;
int speed;
int flag;

void setup() { // the setup function runs only once when power on the board or reset the board:
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(motorPin, OUTPUT); // set pin 3 as an OUTPUT
}

// the lope function runs forever
void loop() {                             
  delay(150);                                       //wait 50ms between pings:
  long distance = calculateDistance();              // send ping, get distance in cm and store it in 'distance' variable:
  Serial.print(">>> distance ");                   
  Serial.println(distance);                         // print the distance in serial monitor:                

  if((distance > 5) && (distance < 40)) {           //check wheather the ultrasonic sensor's value stays between 1 to 15.
  //                                                // if the condition is 'true' then the statement below will execute:
  //   //Move Forward:
  //   Motor1.setSpeed(130);  //define motor1 speed:
  //   Motor1.run(FORWARD);   //rotate motor1 clockwise:
    
  // }  else {
  //   //Stop
  analogWrite(motorPin, 200);
  //   Motor1.run(RELEASE);   //stop motor1:
  } else {
    analogWrite(motorPin, 0);    
  }
}

long calculateDistance() {
  // Clear the trigPin by setting it LOW:
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(5);

  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duration = pulseIn(ECHO_PIN, HIGH);
  // Calculate the distance:
  distance = duration * 0.034 / 2;

  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  // Serial.print("Distance = ");
  // Serial.print(distance);
  // Serial.println(" cm");

  return distance;
}