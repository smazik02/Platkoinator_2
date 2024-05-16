#include <Arduino.h>
#include <ESP32Servo.h>
#include <constants.h>

bool cereal_chosen, milk_chosen, ready;
int8_t cereal, milk, scene;
Servo servos[2];
uint8_t cereal_sensors[] = {SENSOR_CEREAL_1, SENSOR_CEREAL_2};

uint32_t toPWM(uint32_t val);
void readSensors(void);
void testSensors(void);
void testEngines(void);
void testServos(void);
void runServos(void);
void testLEDs(void);
void testEverything(void);

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
    digitalWrite(BELT_EN, LOW);
    digitalWrite(PUMP_EN, LOW);

    digitalWrite(BELT_FORWARD, HIGH);
    digitalWrite(BELT_BACK, LOW);
    digitalWrite(PUMP_FORWARD, LOW);
    digitalWrite(PUMP_BACK, LOW);

    servos[0].write(SERVO1_DEFAULT);
    servos[1].write(SERVO2_DEFAULT);
}

void loop() {
    Serial.println("DEBUG PROGRAM BEGINS");
    // readSensors();
    // testSensors();
    // testLEDs();
    // testEngines();
    // testServos();
    // runServos();
    testEverything();
}

void readSensors(void) {
    Serial.println("READING SENSORS");

    Serial.printf("Milk sensor: %d\n", analogRead(SENSOR_MILK));
    Serial.printf("Cereal sensor 1: %d\n", analogRead(SENSOR_CEREAL_1));
    Serial.printf("Cereal sensor 2: %d\n\n", analogRead(SENSOR_CEREAL_2));
    delay(500);
}

void testSensors(void) {
    Serial.println("TESTING SENSORS");

    Serial.println("Milk sensor, waiting until laser works");
    delay(1000);
    while (analogRead(SENSOR_MILK) < SENSOR_SENSITIVITY) {
        Serial.println(analogRead(SENSOR_MILK));
        delay(200);
    }
    Serial.println("Cover the milk sensor");
    delay(1000);
    while (analogRead(SENSOR_MILK) > SENSOR_SENSITIVITY) {
        Serial.println(analogRead(SENSOR_MILK));
        delay(200);
    }
    Serial.println("Milk sensor end");
    delay(1000);

    Serial.println("Cereal sensor 1, waiting until laser works");
    delay(1000);
    while (analogRead(SENSOR_CEREAL_1) < SENSOR_SENSITIVITY) {
        Serial.println(analogRead(SENSOR_CEREAL_1));
        delay(200);
    }
    Serial.println("Cover the cereal sensor 1");
    delay(1000);
    while (analogRead(SENSOR_CEREAL_1) > SENSOR_SENSITIVITY) {
        Serial.println(analogRead(SENSOR_CEREAL_1));
        delay(200);
    }
    Serial.println("Cereal sensor 1 end");
    delay(1000);

    Serial.println("Cereal sensor 2, waiting until laser works");
    delay(1000);
    while (analogRead(SENSOR_CEREAL_2) < SENSOR_SENSITIVITY) {
        Serial.println(analogRead(SENSOR_CEREAL_2));
        delay(200);
    }
    Serial.println("Cover the cereal sensor 2");
    delay(1000);
    while (analogRead(SENSOR_CEREAL_2) > SENSOR_SENSITIVITY) {
        Serial.println(analogRead(SENSOR_CEREAL_2));
        delay(200);
    }
    Serial.println("SENSOR END");
    delay(1000);
}

void testEngines(void) {
    Serial.println("TESTING TRANSPORTER ENGINE");
    Serial.println("WHATEVER IS ON THE TRANSPORTER, TAKE IT AWAY");
    delay(5000);
    Serial.println("Transporter forward");
    int time = millis();
    while (millis() - time < 5000) {
        digitalWrite(BELT_EN, HIGH);
        delay(7);
        digitalWrite(BELT_EN, LOW);
        delay(1);
    }
    // digitalWrite(BELT_EN, HIGH);
    // delay(5000);
    Serial.println("Transporter stop");
    digitalWrite(BELT_EN, LOW);

    Serial.println("TESTING PUMP");
    Serial.println("PUT SOMETHING TO TAKE THE FLUID");
    delay(5000);
    Serial.println("Milk => bowl");
    digitalWrite(PUMP_BACK, LOW);
    digitalWrite(PUMP_FORWARD, HIGH);
    digitalWrite(PUMP_EN, HIGH);
    delay(5000);
    digitalWrite(PUMP_FORWARD, LOW);
    digitalWrite(PUMP_EN, LOW);
    delay(500);
    Serial.println("Reverse");
    digitalWrite(PUMP_BACK, HIGH);
    digitalWrite(PUMP_EN, HIGH);
    delay(5000);
    Serial.println("Pump stop");
    digitalWrite(PUMP_BACK, LOW);
    digitalWrite(PUMP_EN, LOW);

    Serial.println("ENGINE END");
    delay(1000);
}

void testServos(void) {
    Serial.println("TESTING SERVOS");
    Serial.println("Both servos at default position");
    delay(1000);
    Serial.println("Spinning servo 1 (put a bowl underneath)");
    delay(1000);
    Serial.println("Servo 1");
    servos[0].write(0);
    delay(5000);
    Serial.println("Servo 1 stop");
    servos[0].write(SERVO1_DEFAULT);

    delay(1000);
    Serial.println("Spinning servo 2 (put a bowl underneath)");
    delay(1000);
    Serial.println("Servo 2");
    servos[1].write(0);
    delay(5000);
    Serial.println("Servo 2 stop");
    servos[1].write(SERVO2_DEFAULT);

    Serial.println("SERVO END");
    delay(1000);
}

void runServos(void) {
    Serial.println("RUNNING SERVOS");
    servos[0].write(0);
    servos[1].write(0);
    while (true);
}

void testLEDs(void) {
    Serial.println("TESTING LEDS");
}

void testEverything(void) {
    Serial.println("Waiting for milk");
    delay(1000);
    while (analogRead(SENSOR_MILK) < SENSOR_SENSITIVITY) {
        // Serial.println(analogRead(SENSOR_MILK));
    }

    Serial.println("Pouring milk");
    delay(1000);
    digitalWrite(PUMP_BACK, 0);
    digitalWrite(PUMP_FORWARD, 1);
    digitalWrite(PUMP_EN, HIGH);
    delay(5000);  // TODO - specify delay based on chosen milk amount

    digitalWrite(PUMP_EN, 0);
    delay(500);

    digitalWrite(PUMP_FORWARD, 0);
    digitalWrite(PUMP_BACK, 1);
    digitalWrite(PUMP_EN, HIGH);
    delay(1000);
    digitalWrite(PUMP_EN, 0);

    digitalWrite(PUMP_BACK, 0);

    Serial.printf("Waiting for cereal 1, sensor: %d\n", analogRead(SENSOR_CEREAL_1));
    delay(2000);
    digitalWrite(BELT_EN, HIGH);
    while (analogRead(SENSOR_CEREAL_1) < SENSOR_SENSITIVITY) {
    }
    digitalWrite(BELT_EN, LOW);

    Serial.println("Cereal 1");
    delay(1000);
    servos[0].write(0);
    delay(10000);
    servos[0].write(SERVO1_DEFAULT);

    Serial.printf("Waiting for cereal 2, sensor: %d\n", analogRead(SENSOR_CEREAL_2));
    delay(2000);
    digitalWrite(BELT_EN, HIGH);
    while (analogRead(SENSOR_CEREAL_2) < SENSOR_SENSITIVITY) {
    }
    digitalWrite(BELT_EN, LOW);

    Serial.println("Cereal 2");
    delay(1000);
    servos[1].write(0);
    delay(5000);
    servos[1].write(SERVO2_DEFAULT);

    delay(1000);
    int time = millis();
    digitalWrite(BELT_EN, HIGH);
    while (millis() - time < 300);
    digitalWrite(BELT_EN, LOW);
}

uint32_t toPWM(uint32_t val) {
    return map(val, 0, 100, 0, pow(2, RES));
}