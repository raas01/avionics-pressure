#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// Initialize the I2C LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);  // 2004 LCD (20 characters, 4 lines)

// BMP280 sensor object
Adafruit_BMP280 bmp;

void setup() {
  // Initialize the LCD
  lcd.init();       // Initialize the LCD for I2C
  lcd.backlight();  // Turn on the backlight

  // Start the serial communication for debugging
  Serial.begin(9600);
  Serial.print("Starting Program");

  // Initialize the BMP280 sensor
  if (!bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID)) {
    lcd.clear();
    Serial.print("BMP280 not found");
    lcd.print("BMP280 not found");
    while (1)
      ;  // Freeze if sensor not connected properly
  } else {
    lcd.clear();
    Serial.print("Sensor Ready");
    lcd.print("Sensor ready");
    delay(2000);  // Display "Sensor ready" for a short time
    lcd.clear();
  }
}

void loop() {
  // Read the temperature and pressure
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0;  // Convert Pa to hPa

  // Display temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);  // Display 1 decimal place
  lcd.print(" C");

  // Display pressure
  lcd.setCursor(0, 1);
  lcd.print("Press: ");
  lcd.print(pressure, 1);  // Display 1 decimal place
  lcd.print(" hPa");

  // Delay before the next update
  delay(2000);

  // Optional: print the readings to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");
}