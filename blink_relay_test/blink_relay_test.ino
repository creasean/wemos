#define LED_BUILTINN D4
const int ledPin = 14;
  
  void setup() {
    pinMode(LED_BUILTINN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    pinMode(ledPin, OUTPUT);
  }
  
  // the loop function runs over and over again forever
  void loop() {
    digitalWrite(LED_BUILTINN, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
    digitalWrite(ledPin, HIGH);
    delay(5000);                      // Wait for a second
    digitalWrite(LED_BUILTINN, LOW);  // Turn the LED off by making the voltage HIGH
    digitalWrite(ledPin, LOW);    
    delay(500);                      // Wait for two seconds (to demonstrate the active low LED)
  }
