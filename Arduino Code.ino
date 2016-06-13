int pin1=A0; // MQ-6 LPG GAS SENSOR OUTPUT PIN
int pin2=A1; // MQ-2 AIR QUALITY SENSOR OUTPUT PIN 

int trigger1=400; //AT WHAT SENSOR OUTPUT VOLTAGE VALUE LPG ALARM WILL BE TRIGGERED
int trigger2=400; //AT WHAT SENSOR OUTPUT VOLTAGE VALUE SMOKE ALARM WILL BE TRIGGERED

void setup() 
{
 pinMode(pin1,INPUT);
 pinMode(pin2,INPUT);
 Serial.begin(9600);
 delay(5000); 
 pinMode(2,OUTPUT);
 pinMode(3,OUTPUT);
}

void send_sms(char ch[]) // TO SEND SMS VIA GSM MODULE
{
 Serial.println("AT");
  delay(1000);
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+91**********\""); //CHANGE TO THE DESTINATION PHONE NUMBER
  delay(1000);
  Serial.print(ch);
  Serial.write(26);
  delay(300000);  
}

void beep(int pin) // TO WARN ABOUT GAS LEAK IF SOMEONE IS PRESENT AT HOME, BUZZER MUST          {                 //BE CONNECTED AT PIN 2 AND 3 OR CHANGE THEM AT YOUR WILL
  while(analogRead(pin)>=200)
  {
   for(int i=0;i<100;i++)
   { 
    digitalWrite(2,HIGH);   
    digitalWrite(3,LOW);
    delay(1);
    digitalWrite(3,HIGH);
    digitalWrite(2,LOW);
    delay(1);
   }
   delay(100);
   digitalWrite(2,LOW);
   digitalWrite(3,LOW);
   delay(100);
 }
}

void loop() 
{
char ch1[]="Attention! Gas leakage at Home! Attention!";   //DIFFERENT MESSAGE IN DIFFERENT CASES
char ch2[]="Attention! Thick smoke detected at Home! Attention!";
int sensor1 = analogRead(pin1);
int sensor2 = analogRead(pin2);
 if(sensor1>=trigger1)     //IN CASE LPG/COOKING GAS LEAKAGE IS DETECTED
 {
  beep(pin1);
  send_sms(ch1);
 }
 else if(sensor2>=trigger2) // IN CASE SMOKE IS DETECTED
 {
  beep(pin2);
  send_sms(ch2); 
 }
}