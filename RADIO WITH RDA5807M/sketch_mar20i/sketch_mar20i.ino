#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RDA5807.h>

// Initialize the LCD (address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Initialize the RDA5807M radio object
RDA5807 radio;

// Pin definitions for TTP223 touch switches
#define TUNE_UP_PIN 2   // D2
#define TUNE_DOWN_PIN 3 // D3
#define VOL_UP_PIN 4    // D4
#define VOL_DOWN_PIN 5  // D5

// Preset stations (frequency in MHz * 100, e.g., 91.9 MHz = 9190)
const int presetFrequencies[] = {9190, 9270, 9350, 9830, 10020, 10180, 10480, 10700, 10780};
const char* presetNames[] = {
  "Friends FM", 
  "Big FM", 
  "Red FM", 
  "Radio Mirchi", 
  "AIR FM Gold", 
  "Vividh Bharati", 
  "Fever FM", 
  "AIR FM Rainbow", 
  "Power FM"
};
const int numPresets = 9; // Number of preset stations
int currentPresetIndex = 0; // Start at the first preset

// Variables
int frequency = 9190; // Starting frequency (91.9 MHz * 100)
int volume = 8;       // Volume range: 0-15, start at mid-level
const int MIN_FREQ = 8750;  // 87.5 MHz
const int MAX_FREQ = 10800; // 108.0 MHz

// Long press detection variables
unsigned long volUpPressTime = 0;
unsigned long volDownPressTime = 0;
const unsigned long longPressDuration = 3000; // 3 seconds
bool volUpPressed = false;
bool volDownPressed = false;

void setup() {
  // Initialize Serial for debugging (optional)
  Serial.begin(9600);

  // Initialize I2C
  Wire.begin();

  // Initialize LCD
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("FM Radio");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  // Initialize RDA5807M
  radio.setup();
  radio.setVolume(volume);
  radio.setFrequency(frequency / 100.0); // Convert to float (e.g., 91.9)

  // Set up touch switch pins as inputs
  pinMode(TUNE_UP_PIN, INPUT);
  pinMode(TUNE_DOWN_PIN, INPUT);
  pinMode(VOL_UP_PIN, INPUT);
  pinMode(VOL_DOWN_PIN, INPUT);

  // Initial display update
  updateDisplay();
  delay(2000); // Brief startup delay
}

void loop() {
  // Check tune up/down (short press)
  if (digitalRead(TUNE_UP_PIN) == HIGH) {
    tuneUp();
    currentPresetIndex = -1; // Manual tuning, no preset selected
    delay(200); // Debounce delay
  }
  if (digitalRead(TUNE_DOWN_PIN) == HIGH) {
    tuneDown();
    currentPresetIndex = -1; // Manual tuning, no preset selected
    delay(200);
  }

  // Check volume up (short press and long press)
  if (digitalRead(VOL_UP_PIN) == HIGH) {
    if (!volUpPressed) {
      volUpPressTime = millis();
      volUpPressed = true;
    }
    // Check for long press (3 seconds)
    if (millis() - volUpPressTime >= longPressDuration) {
      nextPreset();
      delay(200); // Debounce
      volUpPressed = false; // Reset to allow another press
    }
  } else if (volUpPressed) {
    // Short press detected (released before 3 seconds)
    if (millis() - volUpPressTime < longPressDuration) {
      volumeUp();
      delay(200); // Debounce
    }
    volUpPressed = false;
  }

  // Check volume down (short press and long press)
  if (digitalRead(VOL_DOWN_PIN) == HIGH) {
    if (!volDownPressed) {
      volDownPressTime = millis();
      volDownPressed = true;
    }
    // Check for long press (3 seconds)
    if (millis() - volDownPressTime >= longPressDuration) {
      previousPreset();
      delay(200); // Debounce
      volDownPressed = false; // Reset to allow another press
    }
  } else if (volDownPressed) {
    // Short press detected (released before 3 seconds)
    if (millis() - volDownPressTime < longPressDuration) {
      volumeDown();
      delay(200); // Debounce
    }
    volDownPressed = false;
  }
}

// Tune frequency up by 0.1 MHz
void tuneUp() {
  if (frequency < MAX_FREQ) {
    frequency += 10; // Increment by 0.1 MHz (10 * 0.01 MHz)
    radio.setFrequency(frequency / 100.0);
    updateDisplay();
  }
}

// Tune frequency down by 0.1 MHz
void tuneDown() {
  if (frequency > MIN_FREQ) {
    frequency -= 10; // Decrement by 0.1 MHz
    radio.setFrequency(frequency / 100.0);
    updateDisplay();
  }
}

// Increase volume
void volumeUp() {
  if (volume < 15) {
    volume++;
    radio.setVolume(volume);
    updateDisplay();
  }
}

// Decrease volume
void volumeDown() {
  if (volume > 0) {
    volume--;
    radio.setVolume(volume);
    updateDisplay();
  }
}

// Go to the next preset station
void nextPreset() {
  currentPresetIndex++;
  if (currentPresetIndex >= numPresets) {
    currentPresetIndex = 0; // Wrap around to the first preset
  }
  frequency = presetFrequencies[currentPresetIndex];
  radio.setFrequency(frequency / 100.0);
  updateDisplay();
}

// Go to the previous preset station
void previousPreset() {
  currentPresetIndex--;
  if (currentPresetIndex < 0) {
    currentPresetIndex = numPresets - 1; // Wrap around to the last preset
  }
  frequency = presetFrequencies[currentPresetIndex];
  radio.setFrequency(frequency / 100.0);
  updateDisplay();
}

// Update LCD display with frequency, station name (if preset), and volume
void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Freq: ");
  lcd.print(frequency / 100.0, 1); // Display as float (e.g., 91.9)
  lcd.print(" MHz");

  lcd.setCursor(0, 1);
  if (currentPresetIndex >= 0) {
    // Display station name if a preset is selected
    lcd.print(presetNames[currentPresetIndex]);
  } else {
    // Display volume if manually tuned
    lcd.print("Vol: ");
    lcd.print(volume);
    lcd.print("   ");
  }
}