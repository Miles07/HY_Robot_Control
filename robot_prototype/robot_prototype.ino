#define TRIGGER_PIN 6         // Trigger pin connected to analog pin A1 of Arduino Uno:
#define ECHO_PIN 5            // Echo pin connected to analog pin A0 of Arduino Uno:
#define MAX_DISTANCE 200      // Maximum ping distance:

unsigned int distance = 0;    // Variable to store ultrasonic sensor distance:
unsigned int duration = 0;   

// motor pins
int motorPin1 = 3;
int motorPin2 = 9;

void setup() { // the setup function runs only once when power on the board or reset the board:
  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  pinMode(TRIGGER_PIN, OUTPUT);   // ultrasonic sensor input pin
  pinMode(ECHO_PIN, INPUT);       // ultrasonic sensor input pin
  pinMode(motorPin1, OUTPUT);      // set pin 3 as an OUTPUT for the motor 1
  pinMode(motorPin2, OUTPUT);      // set pin 9 as an OUTPUT for the motor 2
}

void loop() {                             
  delay(150);                                       //wait 50ms between pings:
  long distance = calculateDistance();              // send ping, get distance in cm and store it in 'distance' variable:
  Serial.print(">>> distance ");                   
  Serial.println(distance);                         // print the distance in serial monitor:                

  if((distance > 5) && (distance < 120)) {           //check wheather the ultrasonic sensor's value stays between 1 to 15.
    //Serial.print("RUN!");
    analogWrite(motorPin1, 200);
    analogWrite(motorPin2, 200);
  } else {
    analogWrite(motorPin1, 0); 
    analogWrite(motorPin2, 0);   
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
