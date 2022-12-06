int val;
unsigned long TIME;
int charge = 7;
int led = 8;
int gas = 12;
int buzzer = 4;


unsigned long delayStart = 0; //  delay started
bool delayRunning = false; // true if still waiting for delay to end

void setup() {
 
  
  pinMode(led, OUTPUT);
  pinMode(charge, OUTPUT);   // initialize
  pinMode(gas , INPUT);
  pinMode(buzzer, OUTPUT);
  
  digitalWrite(charge, LOW); // turn all off
  digitalWrite(led, LOW);

  Serial.begin(9600); 
  
}

void loop() {

  if( Serial.available()){
    val = Serial.read();
  }
  
switch(val){
      case '0':    
        digitalWrite(led, HIGH); //LED ON
        Serial.println("LIGHT ON");
        break;
        
      case '1':  
        digitalWrite(led, LOW);  //LED OFF
        Serial.println("LIGHT OFF");
        break;

      case '2':
        
        TIME = 10000;     //10 second for demo
        delayStart = millis();   // start delay
        delayRunning = true; // not finished yet
        digitalWrite(charge, HIGH);
        Serial.println("CHARGE ON 10 seconds ");
            
        break;

      case '3': 
        TIME = 1800000;           //30 minute 
        delayStart = millis();   
        delayRunning = true; 
        digitalWrite(charge, HIGH);
        Serial.println("CHARGE ON 30 minute");
        
        break;
      
      case '4':  
        TIME = 3600000;           //1 hour
        delayStart = millis();  
        delayRunning = true;
        digitalWrite(charge, HIGH);
        Serial.println("CHARGE ON 1 hour");
        
        break;

      case '5':    
        digitalWrite(charge, HIGH); //charger ON
        Serial.println("CHARGER ON");
        break;
        
      case '6':  
        digitalWrite(charge, LOW);  //charger OFF
        Serial.println("CHARGER OFF");
        break;
      
      default:
        break;  // default code (should never run)
    }
  

if(digitalRead(gas) == HIGH)
{
digitalWrite(buzzer, HIGH);
digitalWrite(charge, LOW); 
  digitalWrite(led, LOW);
}
else if(digitalRead(gas) == LOW)
{
digitalWrite(buzzer, LOW);
}

  
  // off after the TIME
  if (delayRunning && ((millis() - delayStart) >= TIME)) {
    delayRunning = false; //prevent this code being run more then once
    digitalWrite(charge, LOW); // turn off
    Serial.println("CHARGE COMPLETE");    
  }
}
