#include <Arduino.h>
#include <ESP32Servo.h>
#include <constants.h>

bool cereal_chosen, milk_chosen, ready;
int8_t cereal, milk, scene;
Servo servos[2];
uint8_t cereal_sensors[] = {SENSOR_CEREAL_1, SENSOR_CEREAL_2};

uint32_t toPWM(uint32_t val);
void mainFunction(void);
void pumpMilk(void);

void setup() {
    Serial.begin(115200);

    // ledcSetup(BELT, FREQ, RES);
    // ledcAttachPin(BELT_EN, BELT);
    pinMode(BELT_EN, OUTPUT);
    pinMode(PUMP_EN, OUTPUT);

    pinMode(BELT_FORWARD, OUTPUT);
    pinMode(BELT_BACK, OUTPUT);
    pinMode(PUMP_FORWARD, OUTPUT);
    pinMode(PUMP_BACK, OUTPUT);
    pinMode(SENSOR_MILK, INPUT);
    pinMode(SENSOR_CEREAL_1, INPUT);
    pinMode(SENSOR_CEREAL_2, INPUT);

    servos[0].attach(SERVO_CEREAL_1);
    servos[1].attach(SERVO_CEREAL_2);

    // ledcWrite(BELT, 0);
    // ledcWrite(PUMP, 0);
    digitalWrite(BELT_EN, HIGH);
    digitalWrite(PUMP_EN, LOW);

    digitalWrite(BELT_FORWARD, LOW);
    digitalWrite(BELT_BACK, LOW);
    digitalWrite(PUMP_FORWARD, LOW);
    digitalWrite(PUMP_BACK, LOW);

    servos[0].write(SERVO1_DEFAULT);
    servos[1].write(SERVO2_DEFAULT);

    // mainFunction();
}

void loop() {
    mainFunction();
}

void mainFunction(void) {
    while (analogRead(SENSOR_MILK) < SENSOR_SENSITIVITY) {
        Serial.println(analogRead(SENSOR_MILK));
        delay(200);
    }

    pumpMilk();

    digitalWrite(BELT_FORWARD, HIGH);
    while (analogRead(SENSOR_CEREAL_1) < SENSOR_SENSITIVITY) {
        Serial.println(analogRead(SENSOR_CEREAL_1));
        delay(200);
    }

    digitalWrite(BELT_FORWARD, LOW);
    servos[0].write(0);
    delay(10000);
    servos[0].write(SERVO1_DEFAULT);

    digitalWrite(BELT_FORWARD, HIGH);
    while (analogRead(SENSOR_CEREAL_2) < SENSOR_SENSITIVITY) {
        Serial.println(analogRead(SENSOR_CEREAL_2));
        delay(200);
    }
    digitalWrite(BELT_FORWARD, LOW);
}

void pumpMilk(void) {
    digitalWrite(PUMP_BACK, LOW);
    digitalWrite(PUMP_FORWARD, HIGH);
    digitalWrite(PUMP_EN, HIGH);
    delay(10 * 1000);
    digitalWrite(PUMP_EN, LOW);
    digitalWrite(PUMP_FORWARD, LOW);
    delay(500);

    digitalWrite(PUMP_BACK, HIGH);
    digitalWrite(PUMP_EN, HIGH);
    delay(1000);

    digitalWrite(PUMP_BACK, LOW);
    digitalWrite(PUMP_EN, LOW);
}

uint32_t toPWM(uint32_t val) {
    return map(val, 0, 100, 0, pow(2, RES));
}