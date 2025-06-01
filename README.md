# Smart-Pin-Lock-System 

A smart IoT-based door locking system developed using Arduino, allowing users to unlock doors using either a PIN or voice commands via Google Assistant (Bluetooth-controlled).

##  Features
- Dual authentication: Keypad-based PIN + Voice control (via Bluetooth).
- Auto-relocking after a delay for enhanced security.
- Real-time feedback through LCD and buzzer alerts.
- Compact and easy-to-build prototype suitable for homes and offices.

## Components Used
- Arduino UNO
- 4x4 Keypad
- 16x2 LCD Display (I2C or standard)
- HC-05 Bluetooth Module
- Buzzer
- Relay Module
- Solenoid Lock
- Voltage Regulator
- 12V Power Supply
- Jumper Wires

##  Working Principle
- User enters a PIN via keypad or speaks a voice command using a mobile app connected over Bluetooth.
- Arduino checks the input; if valid, the relay triggers the solenoid lock to unlock.
- LCD shows success/failure messages and buzzer gives feedback.
- System auto-relocks after a short timeout.

## Future Enhancements
- Cloud-based access logs and monitoring.
- AI-powered voice recognition.
- Biometric authentication (fingerprint/face).
- Wi-Fi support for remote unlocking.

## Files
- `ArduinoCode/Project.ino` - Main Arduino sketch.
- `Presentation/Smart_Pin_Lock_PPT.pdf` - Project presentation.
- `CircuitDiagram/Smart_Lock_Circuit.png` - Optional, upload if available.



