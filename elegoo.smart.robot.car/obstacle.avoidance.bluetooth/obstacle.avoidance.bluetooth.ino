//
// Elegoo Smart Robot Car
//
// Four direction moving with remote control by bluetooth.
//
// @author Peter Perger <perger1984@gmail.com>
// @since 2016
//

//-----------------------------------------------------------------------------
// Libraries
//-----------------------------------------------------------------------------

#include <Servo.h>

//-----------------------------------------------------------------------------
// Variable Declarations
//-----------------------------------------------------------------------------

// Create servo object to control servo
Servo myservo;
int Echo = A4;
int Trig = A5;
int rightDistance = 0;
int leftDistance = 0;
int middleDistance = 0;

// Pins of motor connection port (MCP) 1 - Tyres on right side of car
int in1 = 9;
int in2 = 8;
// Pins of motor connection port (MCP) 2 - Tyres on left side of car
int in3 = 7;
int in4 = 6;
// Pin for control of speed of motors on right
int ENA = 10;
// Pin for control of speed of motors on left
int ENB = 5;
// Turning speed (0-255)
int ABS = 130;
// Input byte from communication channel (bluetooth)
char inputByte;

//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

// Move
//
// @param String  direction Direction of car
// @param Boolean scwt      Speed control write type
// @param Integer scv       Speed control value
// @param String  mcp1      Motor connection port 1
// @param String  mcp2      Motor connection port 2
// @param Integrr wait      Runtime of car
void move(String direction, boolean scwt, int scv, String mcp1, String mcp2, int wait)
{
  // Print to serial output (show up on remote device)
  Serial.println(direction);

  // Code for DC motor status (MCP1)
  if (scwt) {
    analogWrite(ENA, scv);
  } else {
    digitalWrite(ENA, scv == 1 ? HIGH : LOW);
  }
  digitalWrite(in1, mcp1.charAt(0) == '1' ? HIGH : LOW);
  digitalWrite(in2, mcp1.charAt(1) == '1' ? HIGH : LOW);

  // Code for DC motor status (MCP2)
  if (scwt) {
    analogWrite(ENB, scv);
  } else {
    digitalWrite(ENB, scv == 1 ? HIGH : LOW);
  }
  digitalWrite(in3, mcp2.charAt(0) == '1' ? HIGH : LOW);
  digitalWrite(in4, mcp2.charAt(1) == '1' ? HIGH : LOW);

  // Wait 1 secound
  delay(wait);

  // Stop the car
  stop();
}

void forward()
{
  // Code: 01 - DC motor status: Forward (MCP1, MCP2)
  move("forward", false, 1, "01", "01", 1000);
}

void backward()
{
  // Code: 10 - DC motor status: Backward (MCP1, MCP2)
  move("backward", false, 1, "10", "10", 1000);
}

void left()
{
  // Code: 01, 10 - DC motor status: Forward (MCP1), Backward (MCP2)
  move("left", true, ABS, "01", "10", 1000);
}
void right()
{
  // Code: 10, 01 - DC motor status: Backward (MCP1), Forward (MCP2)
  move("right", true, ABS, "10", "01", 1000);
}

void stop()
{
  Serial.println("stop");
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}

// Ultrasonic distance measurement
int distanceMeasurement()
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);

  float distance = pulseIn(Echo, HIGH);
  distance = distance / 58;
  return (int) distance;
}

int distanceTest()
{
  delay(500);
  Serial.println("Distance test (0-180) starting ...");
  myservo.write(0);
  Serial.println("distance 5: ");
  delay(1000);
  Serial.println(distanceMeasurement());
  myservo.write(90);
  Serial.println("distance 90: ");
  delay(1000);
  Serial.println(distanceMeasurement());
  myservo.write(180);
  Serial.println("distance 175: ");
  delay(1000);
  Serial.println(distanceMeasurement());
  delay(5000);
  Serial.println("Distance test finished");
}

//-----------------------------------------------------------------------------
// Setup - Run only once, when power up the car
//-----------------------------------------------------------------------------

void setup()
{
  // Attach servo on pin 3 to servo object
  myservo.attach(3);

  // Set the defined pins to the output
  pinMode(Echo, INPUT);
  pinMode(Trig, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Open the serial port and set the baud rate to 9600
  Serial.begin(9600);

  // Stop the car
  stop();
}

//-----------------------------------------------------------------------------
// Loop for main code - Countinously running...
//-----------------------------------------------------------------------------

void loop()
{
  // Wait for connection
  while (!Serial.available());

  // Set servo position according to scaled value
  myservo.write(90);
  delay(500);

  // Print to serial output (show up on remote device)
  Serial.println("Press W,S,A,D + ENTER to control robot car");
  Serial.println("Press O + ENTER to measurement the distance");

  // Read char (byte) from serial port
  inputByte = Serial.read();

  // Move car into the selected direction by given input
  switch (inputByte) {
    case 'w':
      forward();
      break;
    case 's':
      backward();
      break;
    case 'a':
      left();
      break;
    case 'd':
      right();
      break;
    case 'o':
      distanceTest();
      break;
  }

  // Wait half a secound
  delay(500);
}
