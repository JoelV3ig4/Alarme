/*
    Programador....: Joel
    Data...........: 2/2/2025
    Observações....: Alarme do Joel para a Miguel Torga
*/

#include <Keypad.h>

const int BAUD_RATE = 9600;

const byte POWER_LED = 12;   
const byte POWER_BUTTON = 11; 
const byte PIR_SENSOR = 6;
const byte BUZZER = 13;       

const byte STANDBY = 0;
const byte POWER_ON = 1;
const byte PIR_DETECT = 2;

const byte DEBUG = true;

byte alarmState;
bool systemActive = false; 
bool buttonPressed = false; 

// Configuração do teclado 4x4
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const String correctCode = "1234";   // Código correto para desligar o sistema
String enteredCode = "";             // Armazena o código digitado

void setup(void) {
    Serial.begin(BAUD_RATE);
  
    pinMode(POWER_LED, OUTPUT);
    pinMode(POWER_BUTTON, INPUT_PULLUP);
    pinMode(PIR_SENSOR, INPUT);
    pinMode(BUZZER, OUTPUT);

    alarmState = STANDBY;
    digitalWrite(POWER_LED, LOW);

    if (DEBUG) Serial.println("Sistema iniciado em modo STANDBY...");
}

void loop(void) {
    if (digitalRead(POWER_BUTTON) == LOW && !buttonPressed) { // Botão pressionado
        delay(50); // Debounce
        if (digitalRead(POWER_BUTTON) == LOW) {
            toggleSystem();
            buttonPressed = true;
        }
    } else if (digitalRead(POWER_BUTTON) == HIGH) {
        buttonPressed = false;
    }

    char key = keypad.getKey();
    if (key) {
        enteredCode += key;
        if (DEBUG) Serial.println(enteredCode);

        if (enteredCode.length() == 4) {
            if (enteredCode == correctCode) {
                systemActive = false;
                alarmState = STANDBY;
                digitalWrite(POWER_LED, LOW);
                digitalWrite(BUZZER, LOW);
                if (DEBUG) Serial.println("Código correto. Sistema DESLIGADO.");
            } else {
                if (DEBUG) Serial.println("Código incorreto.");
            }
            enteredCode = ""; // Limpa o código após tentativa
        }
    }

    switch (alarmState) {
        case STANDBY: {
            digitalWrite(POWER_LED, LOW);
            break;
        }

        case POWER_ON: {
            digitalWrite(POWER_LED, HIGH);
            if (digitalRead(PIR_SENSOR) == HIGH) {
                alarmState = PIR_DETECT;
            }
            break;
        }

        case PIR_DETECT: {
            if (DEBUG) Serial.println("MOVIMENTO DETECTADO! Alarme Ativado...");

            digitalWrite(BUZZER, HIGH);

            break;
        }
    }
}

void toggleSystem() {
    systemActive = !systemActive;
    if (systemActive) {
        alarmState = POWER_ON;
        if (DEBUG) Serial.println("Sistema LIGADO.");
    } else {
        alarmState = STANDBY;
        digitalWrite(POWER_LED, LOW);
        digitalWrite(BUZZER, LOW);
        if (DEBUG) Serial.println("Sistema DESLIGADO.");
    }
}
