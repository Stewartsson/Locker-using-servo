#include <Keypad.h>
#include <Servo.h>

const String password = "1234";       // Set your desired password
String input = "";

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};    // Connect to keypad rows
byte colPins[COLS] = {5, 4, 3, 2};    // Connect to keypad columns

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Servo lockServo;

void setup() {
  Serial.begin(9600);
  lockServo.attach(10);   // Connect servo signal to D10
  lockServo.write(0);     // Locked position at startup
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Pressed: ");
    Serial.println(key);

    if (key == '*') {
      input = "";                      // Clear input
      Serial.println("Input cleared");
    } else if (key == '#') {
      if (input == password) {
        Serial.println("Access Granted");
        lockServo.write(90);           // Unlock
        delay(10000);                  // Stay unlocked for 10 seconds
        lockServo.write(0);            // Lock again
        Serial.println("Locker re-locked");
      } else {
        Serial.println("Access Denied");
      }
      input = "";                      // Reset input after submission
    } else {
      input += key;                    // Build the input string
    }
  }
}
