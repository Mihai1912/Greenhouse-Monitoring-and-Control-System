#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Define the pins for the RGB LED
const int pinRed = 11;
const int pinGreen = 10;
const int pinBlue = 9;

const int relayPin = 12;

// Define the pins for the temperature sensor
const int sensorPin = A0;

// Define servo objects
Servo servo_L;
Servo servo_R;

// Define the pins for servos
const int servo_L_pin = 5;
const int servo_R_pin = 6;

// Define the pind for buttons
const int button_L_servo = 7;
const int button_change_mode = 4;
const int button_R_servo = 2;

// Adafruit_LiquidCrystal lcd(0);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int window_L_position = 0; // 0 is closed, 1 is open
int window_R_position = 0; // 0 is closed, 1 is open

int previous_window_L_position = 0;
int previous_window_R_position = 0;

int mode = 1; // 0 is manual, 1 is automatic

int servo_L_position = 0;
int servo_R_position = 0;

char Wopen[] = {
    0x1F,
    0x11,
    0x11,
    0x11,
    0x11,
    0x11,
    0x11,
    0x1F
};
char Wclose[] = {
    0x1F,
    0x1F,
    0x1F,
    0x1F,
    0x1F,
    0x1F,
    0x1F,
    0x1F
};
char hot[] = {
    0x02,
    0x06,
    0x04,
    0x0D,
    0x0E,
    0x1F,
    0x1F,
    0x0E
};
char cold[] = {
  0x1F,
  0x1F,
  0x0E,
  0x0E,
  0x0E,
  0x04,
  0x04,
  0x04
};
char O[] = {
  0x1F,
  0x1B,
  0x1B,
  0x1B,
  0x1B,
  0x1B,
  0x1B,
  0x1F
};
char K[] = {
  0x19,
  0x1B,
  0x1A,
  0x1E,
  0x1E,
  0x1B,
  0x19,
  0x19
};

void setup (void)
{
    Serial.begin(9600);

    // Initialize the LCD
    lcd.init();
    lcd.backlight();
    lcd.begin(16, 2);
    lcd.print("Hello farmers!");

    lcd.createChar(0, Wopen);
    lcd.createChar(1, Wclose);
    lcd.createChar(2, hot);
    lcd.createChar(3, cold);
    lcd.createChar(4, O);
    lcd.createChar(5, K);

    // Set the pins for the RGB LED as output
    pinMode(pinRed, OUTPUT);
    pinMode(pinGreen, OUTPUT);
    pinMode(pinBlue, OUTPUT);

    pinMode(relayPin, OUTPUT);

    // Set the pins for buttons as input
    pinMode(button_L_servo, INPUT_PULLUP);
    pinMode(button_change_mode, INPUT_PULLUP);
    pinMode(button_R_servo, INPUT_PULLUP);

    // Attach the servos to the pins
    servo_L.attach(servo_L_pin);
    servo_R.attach(servo_R_pin);

    // Set the initial position of the servos
    servo_L.write(servo_L_position);
    servo_R.write(servo_R_position);

    delay(2000);

    lcd.clear();

    digitalWrite(relayPin, HIGH);
}

void loop (void)
{
    int sensorValue = analogRead(sensorPin);

    int red = 255;
    int green = 255;
    int blue = 255;
  
    float voltage = sensorValue * (5.0 / 1023.0);
    float temperatureC = voltage * 100;

    Serial.print("Temperature: ");
    Serial.print(temperatureC);
    Serial.println(" C");

    printToLCD(temperatureC, window_L_position, window_R_position);

    Serial.print("Mode: ");
    Serial.println(mode);

    Serial.print("Window L: ");
    Serial.println(window_L_position);

    Serial.print("Window R: ");
    Serial.println(window_R_position);


    if (digitalRead(button_change_mode) == HIGH)
    {
        if (mode == 0)
        {
            mode = 1;
            lcd.clear();
            lcd.print("Automatic mode");
            delay(1000);
            lcd.clear();
        }
        else
        {
            mode = 0;
            lcd.clear();
            lcd.print("Manual mode");
            delay(1000);
            lcd.clear();
        }
    }

    servo_L.write(servo_L_position);
    servo_R.write(servo_R_position);

    delay(1000);
    
    if (mode == 1){
        if (temperatureC > 30)
        {
            Serial.println("Temperature is higher than 30 degrees");
            previous_window_L_position = window_L_position;
            previous_window_R_position = window_R_position;
            window_L_position = 1;
            window_R_position = 1;
        }
        else
        {
            Serial.println("Temperature is lower than 30 degrees");
            previous_window_L_position = window_L_position;
            previous_window_R_position = window_R_position;
            window_L_position = 0;
            window_R_position = 0;
        }

        if (window_L_position != previous_window_L_position)
        {
            Serial.println("Window L position changed");
            if (window_L_position == 1)
            {
                Serial.println("Window L is open");
                servo_L_position = 90;
            }
            else
            {
                Serial.println("Window L is closed");
                servo_L_position = 0;
            }
        }

        if (window_R_position != previous_window_R_position)
        {
            Serial.println("Window R position changed");
            if (window_R_position == 1)
            {
                Serial.println("Window R is open");
                servo_R_position = 90;
            }
            else
            {
                Serial.println("Window R is closed");
                servo_R_position = 0;
            }
        }
    } else {
        if (digitalRead(button_L_servo) == HIGH)
        {
            if (window_L_position == 0)
            {
                previous_window_L_position = window_L_position;
                window_L_position = 1;
                servo_L_position = 90;
            }
            else
            {
                previous_window_L_position = window_L_position;
                window_L_position = 0;
                servo_L_position = 0;
            }
        }

        if (digitalRead(button_R_servo) == HIGH)
        {
            if (window_R_position == 0)
            {
                previous_window_R_position = window_R_position;
                window_R_position = 1;
                servo_R_position = 90;
            }
            else
            {
                previous_window_R_position = window_R_position;
                window_R_position = 0;
                servo_R_position = 0;
            }
        }
    }

    if (temperatureC > 40)
    {
        red = 0;
        green = 255;
        blue = 255;
    }
    else if (temperatureC > 25 && temperatureC <= 40)
    {
        red = 255;
        green = 0;
        blue = 255;
    }
    else if (temperatureC < 25)
    {
        red = 255;
        green = 255;
        blue = 0;

        digitalWrite(relayPin, LOW);
  
        // Așteptăm 3 secunde (3000 milisecunde)
        delay(3000);
        
        digitalWrite(relayPin, HIGH);

    }

    analogWrite(pinRed, red);
    analogWrite(pinGreen, green);
    analogWrite(pinBlue, blue);
    
}

void printToLCD(float temperatureC, int window_L_position, int window_R_position)
{
    lcd.setCursor(0, 0);
    lcd.print("Temperature: ");

    if (temperatureC > 40) {
        lcd.write(2);
    } else if (temperatureC > 25 && temperatureC <= 40) {
        lcd.write(4);
        lcd.write(5);
    } else {
        lcd.write(3);
    }

    lcd.setCursor(0, 1);
    lcd.print("L:");
    if (window_L_position == 0)
    {
        lcd.write(1);
    }
    else
    {
        lcd.write(0);
    }
    lcd.print("  ");
    lcd.print(temperatureC);
    lcd.print("C");
    lcd.print("  R:");
    if (window_R_position == 0)
    {
        lcd.write(1);
    }
    else
    {
        lcd.write(0);
    }
}