// C++ code
//
/* */
#include <Servo.h>

// Define the pins for the LEDs and ultrasonic sensor
const int leds[] = {2, 3, 4}; // LED pins
const int trigPin = 10; // trig pin for ultrasonic sensor
const int echoPin = 9; // echo pin for ultrasonic sensor
long duration;
int distance;

int potpin = A5;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

Servo myservo; // Create servo object

void setup() {
  // Initialize the LED pins as outputs
  for (int led : leds) {
    pinMode(led, OUTPUT);
  }

  // Initialize the serial communication
  Serial.begin(9600);

  // Attach the servo to a pin
  myservo.attach(8);  // Attaches the servo on pin 8 to the servo object

  // Initialize the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
}

void loop()
{
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 25, 100);	   // scale it to get a percentage value
 
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(20);                           // waits for the servo to get there
  
  digitalWrite(trigPin, LOW);		   // Clears the trigPin
  delayMicroseconds(5);
  
  digitalWrite(trigPin, HIGH);		   // Sets the trigPin on HIGH state for 20 micro seconds
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);   // Reads the echoPin, returns the sound wave travel time in microseconds
  
  distance = duration * 0.034 / 2;	   // Calculating the distance
  
  Serial.print("Distance: ");          // Prints the distance on the Serial Monitor
  Serial.println(distance);
  Serial.println(val);
  
  if (distance >= 25 && distance <= 100) {
    for (int led : leds) {
      digitalWrite(led, HIGH); // Turn on all LEDs
    }
  } else {
    for (int led : leds) {
      digitalWrite(led, LOW);  // Turn off all LEDs
    }
  }
  delay(10); // Delay 
}