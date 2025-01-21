/*
	Programador....:Joel
    Data...........:21/1/2025
    Observações....:Alarme da Miguel Torga.
*/
const int BAUD_RATE = 9600;

const byte POWER_LED = 2;
const byte POWER_BUTTON = 3;
const byte PIR_SENSOR = 6;
const byte BUZZER = 4;


const byte STANDBY = 0;
const byte POWER_ON = 1:
const byte ALARM_ON = 2:
const byte PIR_DETECT = 3;

const byte DEBUG = true;

byte alarmState

  
void setup(){
  Serial.begin(BAUD_RATE);
  
 pinMode(POWER_LED, OUTPUT);
 pinMode(POWER_BUTTON, INPUT);
 pinMode(PIR_SENSOR, INPUT);
 pinMode(BUZZER, OUTPUT);
 
 alarmState = STANDBY;

 digitalWrite(POWER_LED, LOW)
   
 if(DEBUG) Serial.println("...")
  	
}

void loop(){
  switch(alarmState){
    case STANDBY: {
      if(DEBUG) Serial.println("Standby...")
      
      if(digitalRead(POWER_BUTTON) == false) alarmState = POWER_ON;
        break;
    }
    case POWER_ON: {
      if(DEBUG) Serial.println("Power ON...")
        
      digitalWrite(POWER_lED, LOW);
      delay(3000);
      alamState = ALARM_ON 
      break;
    }
    case ALARM_ON: {
      if(DEBUG) Serial.println("Alarme ON...")
      
        digitalRead(PIR_SENSOR) == true){
        alarnState = PIR_DETECT;
      }
      break;
    } 
 	case PIR_DETECT: {
      if(DEBUG) Serial.println("PIR DETECT...")
      for(int i = 700; i <=800; i++){
        tone(Buzzer);
        delay(15);
      }
        
        
       break;
      }
  }
}