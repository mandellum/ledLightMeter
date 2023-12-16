const int pResistor = A0;  // Photoresistor at Arduino analog pin A0
const int buttonPin = 8;   // non PWM pin
const int led = 2;         // the PWM pin the LED is attached to

int value;  // Store value from photoresistor (0-1023)

int buttonState = LOW;


void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);       // led , 8 pin as output
  pinMode(pResistor, INPUT);  // Set pResistor - A0 pin as an input
  pinMode(buttonPin, INPUT);  // Set button, non PWM pin 8 as input
}

void loop() {

  buttonState = digitalRead(buttonPin);
  // buttonState = HIGH;

  // get button state
  if (buttonState == HIGH) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }

  // capture the photoresistor reading
  value = analogRead(pResistor);
  Serial.println(value);

}
