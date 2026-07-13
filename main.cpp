/*#include <Arduino.h>

const byte RGB_Pins[] = {4, 2, 15};
const byte RGB_Chns[] = {0, 1, 2};

#define Mode_Button 14
#define Buzzer 13
#define Buzzer_Chn 7
#define Dial 32
#define Alarm_Button 27

bool alarmRunning = false;
bool alarmRinging = false;
unsigned long alarmStartTime = 0;
unsigned long alarmDuration = 10000;
const unsigned long MIN_ALARM = 5UL * 1000UL;                 // 5 sec
const unsigned long MAX_ALARM = 5UL * 60UL * 60UL * 1000UL;    // 5 hours
const unsigned long Long_Press_Time = 800; // ms
unsigned long Alarm_Button_Start = 0;
bool Alarm_Button_Was_Pressed = false;

int Time_Mode = 0; // 0 = Timer, 2 = Stopwatch, 3 = Alarm clock
int Current_Mode = 0;
int Knob_Mode = 0; // 0 = brightness, 1 = alarm duration

int brightness = 255;

void updateKnob() {
  int dialValue = analogRead(Dial);

  if (Knob_Mode == 0) {
    brightness = map(dialValue, 0, 4095, 0, 255);
  }

  if (Knob_Mode == 1) {
    alarmDuration = MIN_ALARM + ((unsigned long long)dialValue * (MAX_ALARM - MIN_ALARM)) / 4095;
  }
}

void setColor(int red, int green, int blue) {
  red   = (red * brightness) / 255;
  green = (green * brightness) / 255;
  blue  = (blue * brightness) / 255;

  ledcWrite(RGB_Chns[0], 255 - red);
  ledcWrite(RGB_Chns[1], 255 - green);
  ledcWrite(RGB_Chns[2], 255 - blue);
}

void beep() {
  ledcWriteTone(Buzzer_Chn, 1000);
  delay(100);
  ledcWriteTone(Buzzer_Chn, 0);
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 3; i++) {
    ledcSetup(RGB_Chns[i], 1000, 8);
    ledcAttachPin(RGB_Pins[i], RGB_Chns[i]);
  }

  pinMode(Mode_Button, INPUT);
  pinMode(Alarm_Button, INPUT);
  pinMode(Dial, INPUT);
  pinMode(Buzzer, OUTPUT);

  ledcSetup(Buzzer_Chn, 1000, 8);
  ledcAttachPin(Buzzer, Buzzer_Chn);
}

void loop() {
  updateKnob();

bool alarmButtonState = digitalRead(Alarm_Button);

// button just got pressed
if (alarmButtonState == LOW && Alarm_Button_Was_Pressed == false) {
  Alarm_Button_Start = millis();
  Alarm_Button_Was_Pressed = true;
}

// button just got released
if (alarmButtonState == HIGH && Alarm_Button_Was_Pressed == true) {
  unsigned long pressDuration = millis() - Alarm_Button_Start;

  if (pressDuration >= Long_Press_Time) {
    // LONG PRESS = switch time mode
    Time_Mode++;

    if (Time_Mode > 2) {
      Time_Mode = 0;
    }

    Serial.println("Long press: switched time mode");
    beep();
  } 
  else {
    // SHORT PRESS = do action for current mode
    Serial.println("Short press: normal alarm action");
  }

  Alarm_Button_Was_Pressed = false;
}












  // Mode button
  if (Time_Mode == 0) {
  if (digitalRead(Mode_Button) == LOW) {
    delay(20);

    if (digitalRead(Mode_Button) == LOW) {
      Current_Mode++;

      if (Current_Mode > 2) {
        Current_Mode = 0;
      }

      beep();

      while (digitalRead(Mode_Button) == LOW);
      delay(20);
    }
  }

  // Alarm button
  if (digitalRead(Alarm_Button) == LOW) {
  delay(20);

  if (digitalRead(Alarm_Button) == LOW) {

    if (alarmRinging) {
      alarmRinging = false;
      ledcWriteTone(Buzzer_Chn, 0);
      Serial.println("Alarm stopped");
    }

    else if (alarmRunning) {
      alarmRunning = false;
      Serial.println("Timer cancelled");
      beep();
    }

    else if (Knob_Mode == 0) {
      Knob_Mode = 1;
      Serial.println("Alarm duration setting mode");
      beep();
    }

    else if (Knob_Mode == 1) {
      Knob_Mode = 0;
      alarmRunning = true;
      alarmStartTime = millis();
      Serial.println("Timer started");
      beep();
    }

    while (digitalRead(Alarm_Button) == LOW);
    delay(20);
  }
}

  // LED modes
  if (Current_Mode == 0) {
    setColor(255, 0, 0);       // red
  }

  if (Current_Mode == 1) {
    setColor(0, 255, 0);       // green
  }

  if (Current_Mode == 2) {
    setColor(0, 0, 255);       // blue
  }

  // Alarm timer
  if (alarmRunning && millis() - alarmStartTime >= alarmDuration) {
    alarmRunning = false;
    alarmRinging = true;
  }

  // Non-blocking alarm buzzer
  static unsigned long buzzerTimer = 0;
  static bool buzzerState = false;

  if (alarmRinging) {
    if (millis() - buzzerTimer >= 500) {
      buzzerTimer = millis();
      buzzerState = !buzzerState;

      if (buzzerState) {
        ledcWriteTone(Buzzer_Chn, 1000);
      } else {
        ledcWriteTone(Buzzer_Chn, 0);
      }
    }
  } else {
    ledcWriteTone(Buzzer_Chn, 0);
  }
}
 
  // Debug prints every second
static unsigned long printTimer = 0;

if (millis() - printTimer >= 1000) {
  printTimer = millis();

  Serial.print("Knob mode: ");
  Serial.print(Knob_Mode == 0 ? "Brightness" : "Alarm Duration");
  Serial.print(" | Alarm duration: ");
  Serial.print(alarmDuration / 60000UL);
  Serial.println(" min");

  if (alarmRunning) {
    unsigned long elapsed = millis() - alarmStartTime;
    unsigned long remaining = (alarmDuration - elapsed) / 1000UL;

    Serial.print("Time remaining: ");
    Serial.print(remaining);
    Serial.println(" sec");
  }
}
}
*/


#include <Arduino.h>

const byte RGB_Pins[] = {4, 2, 15};
const byte RGB_Chns[] = {0, 1, 2};

#define Mode_Button 14
#define Buzzer 13
#define Buzzer_Chn 7
#define Dial 32
#define Alarm_Button 27

const unsigned long MIN_ALARM = 5UL * 1000UL;
const unsigned long MAX_ALARM = 5UL * 60UL * 60UL * 1000UL;
const unsigned long LONG_PRESS_TIME = 800;

bool alarmRunning = false;
bool alarmRinging = false;

unsigned long alarmStartTime = 0;
unsigned long alarmDuration = 10000;

unsigned long alarmButtonStart = 0;
bool alarmButtonWasPressed = false;

int Time_Mode = 0;     // 0 = Timer, 1 = Stopwatch, 2 = Alarm clock
int Current_Mode = 0;  // 0 = red, 1 = green, 2 = blue
int Knob_Mode = 0;     // 0 = brightness, 1 = alarm duration

int brightness = 255;

void updateKnob() {
  int dialValue = analogRead(Dial);

  if (Knob_Mode == 0) {
    brightness = map(dialValue, 0, 4095, 0, 255);
  }

  if (Knob_Mode == 1) {
    alarmDuration =
      MIN_ALARM + ((unsigned long long)dialValue * (MAX_ALARM - MIN_ALARM)) / 4095;
  }
}

void setColor(int red, int green, int blue) {
  red   = (red * brightness) / 255;
  green = (green * brightness) / 255;
  blue  = (blue * brightness) / 255;

  ledcWrite(RGB_Chns[0], 255 - red);
  ledcWrite(RGB_Chns[1], 255 - green);
  ledcWrite(RGB_Chns[2], 255 - blue);
}

void beep() {
  ledcWriteTone(Buzzer_Chn, 1000);
  delay(100);
  ledcWriteTone(Buzzer_Chn, 0);
}

void handleModeButton() {
  if (digitalRead(Mode_Button) == LOW) {
    delay(20);

    if (digitalRead(Mode_Button) == LOW) {
      Current_Mode++;

      if (Current_Mode > 2) {
        Current_Mode = 0;
      }

      beep();

      while (digitalRead(Mode_Button) == LOW);
      delay(20);
    }
  }
}

void handleTimerShortPress() {
  if (alarmRinging) {
    alarmRinging = false;
    ledcWriteTone(Buzzer_Chn, 0);
    Serial.println("Alarm stopped");
  }

  else if (alarmRunning) {
    alarmRunning = false;
    Serial.println("Timer cancelled");
    beep();
  }

  else if (Knob_Mode == 0) {
    Knob_Mode = 1;
    Serial.println("Alarm duration setting mode");
    beep();
  }

  else if (Knob_Mode == 1) {
    Knob_Mode = 0;
    alarmRunning = true;
    alarmStartTime = millis();
    Serial.println("Timer started");
    beep();
  }
}

void handleAlarmButton() {
  bool buttonState = digitalRead(Alarm_Button);

  if (buttonState == LOW && alarmButtonWasPressed == false) {
    alarmButtonStart = millis();
    alarmButtonWasPressed = true;
  }

  if (buttonState == HIGH && alarmButtonWasPressed == true) {
    unsigned long pressDuration = millis() - alarmButtonStart;

    if (pressDuration >= LONG_PRESS_TIME) {
      Time_Mode++;

      if (Time_Mode > 2) {
        Time_Mode = 0;
      }

      Knob_Mode = 0;

      Serial.print("Switched Time Mode to: ");
      Serial.println(Time_Mode);
      beep();
    }

    else {
      if (Time_Mode == 0) {
        handleTimerShortPress();
      }

      if (Time_Mode == 1) {
        Serial.println("Stopwatch mode not built yet");
        beep();
      }

      if (Time_Mode == 2) {
        Serial.println("Alarm clock mode not built yet");
        beep();
      }
    }

    alarmButtonWasPressed = false;
  }
}

void updateLEDMode() {
  if (Current_Mode == 0) {
    setColor(255, 0, 0);
  }

  if (Current_Mode == 1) {
    setColor(0, 255, 0);
  }

  if (Current_Mode == 2) {
    setColor(0, 0, 255);
  }
}

void updateTimer() {
  if (alarmRunning && millis() - alarmStartTime >= alarmDuration) {
    alarmRunning = false;
    alarmRinging = true;
  }
}

void updateAlarmBuzzer() {
  static unsigned long buzzerTimer = 0;
  static bool buzzerState = false;

  if (alarmRinging) {
    if (millis() - buzzerTimer >= 500) {
      buzzerTimer = millis();
      buzzerState = !buzzerState;

      if (buzzerState) {
        ledcWriteTone(Buzzer_Chn, 1000);
      } 
      else {
        ledcWriteTone(Buzzer_Chn, 0);
      }
    }
  } 
  else {
    ledcWriteTone(Buzzer_Chn, 0);
  }
}

void printDebug() {
  static unsigned long printTimer = 0;

  if (millis() - printTimer >= 1000) {
    printTimer = millis();

    Serial.print("Time Mode: ");
    Serial.print(Time_Mode == 0 ? "Timer" : Time_Mode == 1 ? "Stopwatch" : "Alarm Clock");

    Serial.print(" | Knob Mode: ");
    Serial.print(Knob_Mode == 0 ? "Brightness" : "Timer Duration");

    Serial.print(" | Timer duration: ");
    Serial.print(alarmDuration / 60000UL);
    Serial.println(" min");

    if (alarmRunning) {
      unsigned long elapsed = millis() - alarmStartTime;
      unsigned long remaining = (alarmDuration - elapsed) / 1000UL;

      Serial.print("Time remaining: ");
      Serial.print(remaining);
      Serial.println(" sec");
    }
  }
}

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 3; i++) {
    ledcSetup(RGB_Chns[i], 1000, 8);
    ledcAttachPin(RGB_Pins[i], RGB_Chns[i]);
  }

  pinMode(Mode_Button, INPUT);
  pinMode(Alarm_Button, INPUT);
  pinMode(Dial, INPUT);
  pinMode(Buzzer, OUTPUT);

  ledcSetup(Buzzer_Chn, 1000, 8);
  ledcAttachPin(Buzzer, Buzzer_Chn);
}

void loop() {
  updateKnob();

  handleModeButton();
  handleAlarmButton();

  updateLEDMode();
  updateTimer();
  updateAlarmBuzzer();

  printDebug();
}