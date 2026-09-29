#include <Arduino.h>

// ===============================
// PINLAR
// ===============================

#define RED_LED     26
#define GREEN_LED   27
#define BLUE_LED    14
#define YELLOW_LED  12

#define BUTTON      25
#define LIGHT       33

#define SERVO       5
#define BUZZER      32


// ===============================
// O'ZGARUVCHILAR
// ===============================

bool greenState = false;

bool lastButtonState = LOW;

bool redState = false;

unsigned long lastRedTime = 0;
unsigned long lastLightTime = 0;


// ===============================
// SETUP
// ===============================

void setup()
{
    Serial.begin(115200);

    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);

    pinMode(BUTTON, INPUT);

    // LEDlarni boshlang'ich holatda o'chirish
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);

    Serial.println("LAB 1 START");
}


// ===============================
// LOOP
// ===============================

void loop()
{

    // =================================================
    // 1) RED LED BLINK
    // =================================================

    if (millis() - lastRedTime >= 500)
    {
        lastRedTime = millis();

        redState = !redState;

        digitalWrite(RED_LED, redState);

        if (redState)
        {
            Serial.println("RED ON");
        }
        else
        {
            Serial.println("RED OFF");
        }
    }


    // =================================================
    // 2) BUTTON -> GREEN TOGGLE
    // =================================================

    bool buttonState = digitalRead(BUTTON);

    if (buttonState == HIGH && lastButtonState == LOW)
    {
        greenState = !greenState;

        digitalWrite(GREEN_LED, greenState);

        if (greenState)
        {
            Serial.println("GREEN=1");
        }
        else
        {
            Serial.println("GREEN=0");
        }


        // =============================================
        // 5) SNAPSHOT
        // =============================================

        int snapshot = analogRead(LIGHT);

        Serial.print("snapshot=");
        Serial.println(snapshot);

        // Yellow LED 100 ms
        digitalWrite(YELLOW_LED, HIGH);

        delay(100);

        digitalWrite(YELLOW_LED, LOW);
    }

    lastButtonState = buttonState;


    // =================================================
    // 3) LIGHT SENSOR
    // =================================================

    if (millis() - lastLightTime >= 500)
    {
        lastLightTime = millis();

        int raw = analogRead(LIGHT);

        Serial.print("raw=");
        Serial.println(raw);


        // =============================================
        // 4) LIGHT -> LED BAND
        // =============================================

        if (raw >= 0 && raw <= 1023)
        {
            digitalWrite(BLUE_LED, HIGH);
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(YELLOW_LED, LOW);

            Serial.println("band=BLUE");
        }
        else if (raw >= 1024 && raw <= 2047)
        {
            digitalWrite(BLUE_LED, LOW);
            digitalWrite(GREEN_LED, HIGH);
            digitalWrite(YELLOW_LED, LOW);

            Serial.println("band=GREEN");
        }
        else if (raw >= 2048 && raw <= 3071)
        {
            digitalWrite(BLUE_LED, LOW);
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(YELLOW_LED, HIGH);

            Serial.println("band=YELLOW");
        }
        else
        {
            digitalWrite(BLUE_LED, LOW);
            digitalWrite(GREEN_LED, LOW);
            digitalWrite(YELLOW_LED, LOW);

            digitalWrite(RED_LED, HIGH);

            Serial.println("band=RED");
        }
    }


    // =================================================
    // 6) SERIAL CONTROL
    // =================================================

    if (Serial.available() > 0)
    {
        char command = Serial.read();

        if (command == 'B')
        {
            digitalWrite(BLUE_LED, HIGH);

            Serial.println("BLUE=1");
        }

        else if (command == 'b')
        {
            digitalWrite(BLUE_LED, LOW);

            Serial.println("BLUE=0");
        }
    }
}