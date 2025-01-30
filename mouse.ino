// Joystick pins
const int VRx = A0; // Joystick X-axis
const int VRy = A1; // Joystick Y-axis
const int joystickButton = 2; // Joystick push button

// Button pins
const int leftClickButton = 3; // Left-click button
const int rightClickButton = 4; // Right-click button

void setup() {
    // Configure joystick and button pins
    pinMode(joystickButton, INPUT_PULLUP); // Enable internal pull-up for joystick button
    pinMode(leftClickButton, INPUT_PULLUP); // Enable internal pull-up for left-click button
    pinMode(rightClickButton, INPUT_PULLUP); // Enable internal pull-up for right-click button

    // Start serial communication
    Serial.begin(9600);
}

void loop() {
    // Read joystick X and Y values
    int xValue = analogRead(VRx);
    int yValue = analogRead(VRy);

    // Map joystick values to -10 to 10 for cursor speed
    int mappedX = map(xValue, 0, 1023, -10, 10);
    int mappedY = map(yValue, 0, 1023, 10, -10); // Inverted Y-axis for natural movement

    // Read button states (debounced)
    bool leftClick = debounce(leftClickButton);
    bool rightClick = debounce(rightClickButton);

    // Print joystick and button states to Serial
    Serial.print(mappedX);
    Serial.print(",");
    Serial.print(mappedY);
    Serial.print(",");
    Serial.print(leftClick);
    Serial.print(",");
    Serial.println(rightClick);

    delay(10); // Small delay to reduce data flooding
}

// Debounce function to prevent false button presses
bool debounce(int pin) {
    static unsigned long lastPress[5] = {0, 0, 0, 0, 0}; // Array for multiple pins
    const unsigned long debounceDelay = 50; // 50 ms debounce delay

    int pinIndex = pin - 2; // Adjust index for your pin numbers (e.g., pin 3 -> index 1)
    if (digitalRead(pin) == LOW) {
        unsigned long currentTime = millis();
        if (currentTime - lastPress[pinIndex] > debounceDelay) {
            lastPress[pinIndex] = currentTime;
            return true; // Button press detected
        }
    }
    return false; // No button press
}
