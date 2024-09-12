#define GREEN_LED 5
#define YELLOW_LED 4
#define RED_LED 3
#define BLUE_LED 2

#define LEVEL_SENSOR A7
#define HUMIDITY_SENSOR A6
#define BYPASS_BT A5

unsigned long blueLedTime = 0;
unsigned long bypassLedTime = 0;
unsigned long serialTime = 0;
bool blueLedOn = false;
bool bypassLedOn = false;

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  handleLeds();
  handleSensors();
  controlPower();
  updateSerial();
}

void controlPower() {
  analogWrite(GREEN_LED, 50);
}

void handleSensors() {
  if (analogRead(LEVEL_SENSOR) > 100 && !blueLedOn) {
    blueLedOn = true;
    blueLedTime = millis();
    digitalWrite(BLUE_LED, HIGH);
  }

  if (blueLedOn && (millis() - blueLedTime >= 5000)) {
    blueLedOn = false;
    digitalWrite(BLUE_LED, LOW);
  }
}

void handleLeds() {
  if (analogRead(LEVEL_SENSOR) > 100) {
    digitalWrite(YELLOW_LED, HIGH);
  } else {
    digitalWrite(YELLOW_LED, LOW);
  }

  if (analogRead(HUMIDITY_SENSOR) < 300) {
    digitalWrite(RED_LED, HIGH);
  } else {
    digitalWrite(RED_LED, LOW);
  }

  if (analogRead(BYPASS_BT) > 500 && !bypassLedOn) {
    bypassLedOn = true;
    bypassLedTime = millis();
    digitalWrite(BLUE_LED, HIGH);
  }

  if (bypassLedOn && (millis() - bypassLedTime >= 5000)) {
    bypassLedOn = false;
    digitalWrite(BLUE_LED, LOW);
  }
}

void updateSerial() {
  if (millis() - serialTime >= 1000) {
    serialTime = millis();

    int humidityLevel = map(analogRead(HUMIDITY_SENSOR), 0, 860, 0, 100);
    int levelState = (analogRead(LEVEL_SENSOR) > 100) ? 1 : 0;
    int valveState = (blueLedOn) ? 1 : 0;

    for (int i = 0; i < 5; i++) {
      Serial.println();
    }

    Serial.print("Power: ");
    Serial.println("on");

    Serial.print("Humidity: ");
    Serial.println(humidityLevel);

    Serial.print("Level: ");
    Serial.println(levelState);

    Serial.print("Valve: ");
    Serial.println(valveState);
  }
}

// © 2024 Christian Campolo. All rights reserved