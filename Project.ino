#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define RELAY_PIN 12
#define BUZZER_PIN 13

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C LCD

const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {4, 5, 6, 7}; 
byte colPins[COLS] = {8, 9, 10};    

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String password = "1234"; // Correct password
String enteredPassword = "";

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Lock engaged

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");

  Serial.begin(9600); // Bluetooth using Hardware Serial
}

void loop() {
  char key = keypad.getKey();

  // Keypad Input Handling
  if (key) {
    if (key == '#') {
      if (enteredPassword == password) {
        unlockDoor("Keypad");
      } else {
        wrongPassword();
      }
      enteredPassword = ""; // Reset input
    } else if (key == '*') {
      enteredPassword = ""; // Clear input
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Enter Password:");
    } else {
      enteredPassword += key;
      lcd.setCursor(enteredPassword.length() - 1, 1);
      lcd.print('*'); // Hide password for security
    }
  }

  // Bluetooth Input Handling
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n'); // Read until newline
    command.trim(); // Remove extra spaces or newline characters

    Serial.print("Received: ");
    Serial.println(command); // Debugging

    if (command == "open door") {
      unlockDoor("Bluetooth");
    } else {
      unknownCommand(); // Show "Unknown Command" on LCD
    }
  }
}

// Function to Unlock Door
void unlockDoor(String method) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Access Granted!");
  lcd.setCursor(0, 1);
  lcd.print(method);
  
  digitalWrite(RELAY_PIN, LOW); // Unlock door
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
  
  delay(5000); // Keep door unlocked for 5 sec
  digitalWrite(RELAY_PIN, HIGH); // Lock again
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
}

// Function for Wrong Password
void wrongPassword() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wrong Password!");
  
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
}

// Function to Handle Unknown Commands
void unknownCommand() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Unknown Command!");
  
  digitalWrite(BUZZER_PIN, HIGH);
  delay(500);
  digitalWrite(BUZZER_PIN, LOW);
  
  delay(2000); // Show message for 2 sec
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
}
