/*
An Arduino-based prototype game controller, inspired by physical boxing simulator arcade installations.
A physical slotted metal sheet will slide past an LED light, allowing a sliver of light to pass a photoresistor.
The duration of time in which the photoresistor notices the light will be passed onto the PC via USB connection.
*/

#define DEBUG false // false is Debug off, true is Debug on

#if DEBUG == true
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

const int pResistor = A0; // Photoresistor at Arduino analog pin A0
const int buttonPin = 8;  // non PWM pin
const int ledPin = 2;     // the PWM pin the LED is attached to

int value;       // Store value from photoresistor (0-1023)
float threshold; // Value has to be above this to trigger millis()
int buttonState = LOW;
bool isThresholdTriggered = false;

unsigned long startTime;
unsigned long duration;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);   // led , 8 pin as output
  pinMode(pResistor, INPUT); // Set pResistor - A0 pin as an input
  pinMode(buttonPin, INPUT); // Set button, non PWM pin 8 as input
  threshold = 600;           // arbitrary threshold for now.
}

void loop()
{

  buttonState = digitalRead(buttonPin);
  // buttonState = HIGH;

  // get button state
  if (buttonState == HIGH)
  {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }

  // capture the photoresistor reading
  value = analogRead(pResistor);
  debugln(value);

  if (value > threshold && !isThresholdTriggered)
  {
    startTime = millis();
    isThresholdTriggered = true;
  }

  if (value <= threshold && isThresholdTriggered)
  {
    duration = millis() - startTime;
    isThresholdTriggered = false;
    DoSendMessage(duration); // Serial.println goes to PC
  }
}

void DoSendMessage(unsigned long time)
{
  Serial.println(time); // updates duration and outputs it to PC
  debugln("Updating count to PC");
}
