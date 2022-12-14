#define TRIGGER_PIN 3         // Trigger pin connected to analog pin A1 of Arduino Uno:
#define ECHO_PIN 2            // Echo pin connected to analog pin A0 of Arduino Uno:
#define MAX_DISTANCE 200      // Maximum ping distance:

unsigned int distance = 0;    // ultrasonic sensor distance
unsigned int duration = 0;    // length of ultrasonic sensor pulse

// ultra sonic sensor distance (in cm)
int minDist = 25;
int maxDist = 140;
int slowDist = 60;

// motor speed
int fullSpeed = 400;
int turnSpeed = 380;          
int slowSpeed = 320;

// motor pins
int motorPinFL = 10;          // front left
int motorPinFR = 6;           // front right
int motorPinBL = 9;           // back left
int motorPinBR = 5;           // back right

// proximity sensor pins
int proximityPinLeft = A1;
int proximityPinRight = A0;
int COLLISION_PROXIMITY = 850; // sensor value below limit -> object detected

// control variables
boolean targetDetected = false;
boolean leftObstacle = false;
boolean rightObstacle = false;

void setup() { // the setup function runs only once when power on the board or reset the board:
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  pinMode(TRIGGER_PIN, OUTPUT);     // ultrasonic sensor output pin
  pinMode(ECHO_PIN, INPUT);         // ultrasonic sensor input pin
  
  pinMode(motorPinFL, OUTPUT);      // front left motor
  pinMode(motorPinFR, OUTPUT);      // front right motor
  pinMode(motorPinBL, OUTPUT);      // back left motor
  pinMode(motorPinBR, OUTPUT);      // back right motor
  pinMode(proximityPinLeft, INPUT);
  pinMode(proximityPinRight, INPUT);
}

void loop() {                             
  delay(150); // 150
  long distance = calculateDistance();              // send ping, get distance in cm and store it in 'distance' variable:
  long distLeft = analogRead(proximityPinLeft);
  long distRight = analogRead(proximityPinRight);
  
  Serial.print(">>> distance ");       
  Serial.println(distance);    
          
  Serial.print(">>> distance left: ");   
  Serial.println(distLeft);
  
  Serial.print(">>> distance right: ");  
  Serial.println(distRight);   
  Serial.println(); 

  // get target & obstacle conditions
  targetDetected = (distance > minDist) && (distance < maxDist);
  leftObstacle = false; // distLeft < COLLISION_PROXIMITY; // if left sensor's distance is below distance --> True
  rightObstacle = false; // distRight < COLLISION_PROXIMITY;


  // Serial.print(">>> TARGET: ");  
  // Serial.println(targetDetected);   
  
  // Serial.print(">>> LEFT COLLISION: ");  
  // Serial.println(leftObstacle);   
  
  // Serial.print(">>> RIGHT: ");  
  // Serial.println(rightObstacle);   
  // Serial.println(); 

  if (targetDetected && !leftObstacle && !rightObstacle) {
    // no collision --> run all motors
    if (distance < slowDist) {
      analogWrite(motorPinFL, slowSpeed);
      analogWrite(motorPinBL, slowSpeed);
      analogWrite(motorPinFR, slowSpeed);
      analogWrite(motorPinBR, slowSpeed);
    } else {
      analogWrite(motorPinFL, fullSpeed);
      analogWrite(motorPinBL, fullSpeed);
      analogWrite(motorPinFR, fullSpeed);
      analogWrite(motorPinBR, fullSpeed);
    }
  } else if (targetDetected && leftObstacle && !rightObstacle) {
    // left collision --> run only left motors
    analogWrite(motorPinFL, turnSpeed);
    analogWrite(motorPinBL, turnSpeed);
    analogWrite(motorPinFR, 0);  
    analogWrite(motorPinBR, 0);   
  } else if (targetDetected && !leftObstacle && rightObstacle) {
    // right collision --> run only right motors
    analogWrite(motorPinFL, 0); 
    analogWrite(motorPinBL, 0);  
    analogWrite(motorPinFR, turnSpeed);
    analogWrite(motorPinBR, turnSpeed);
  } else {
    // stop motors
    analogWrite(motorPinFL, 0); 
    analogWrite(motorPinBL, 0);  
    analogWrite(motorPinFR, 0);  
    analogWrite(motorPinBR, 0);   
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
