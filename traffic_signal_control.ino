const int redPin = 13; // the number of the red LED pin
const int yellowPin = 12; // the number of the yellow LED pin
const int greenPin = 11; // the number of the green LED pin
const int ambulance=9;
const int raspberry=8;
const int buz=10;
int ambulancestate,raspberrystate;
// Variables will change:
int redState = LOW; // redState used to set the red LED
int yellowState = LOW; // yellowState used to set the yellow LED
int greenState = LOW; // greenState used to set the green LED
long StartTime = 0; // will store last time the traffic sequence was started
// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 30000; // sequence interval is the time in miliseconds from
the start of the green // light to the end of the
red (milliseconds)
void setup() {
// set the digital pin as output:
Serial.begin(9600);
delay(3000);
pinMode(redPin, OUTPUT);
pinMode(yellowPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(ambulance,INPUT);
pinMode(raspberry,INPUT);
pinMode(buz,OUTPUT);
digitalWrite(ambulance,HIGH);
digitalWrite(raspberry,LOW);
digitalWrite(buz,LOW);
}
void loop()
{
unsigned long CheckTime = millis();
unsigned long elapsedTime = CheckTime - StartTime;
if(elapsedTime > interval) {
StartTime = CheckTime;
}
if (elapsedTime < 10000){
redState = LOW;
yellowState = LOW;
greenState = HIGH;
}
if (elapsedTime > 10000 &&elapsedTime < 15000 ){
redState = LOW;
yellowState = HIGH;
greenState = LOW ;
}
if (elapsedTime > 15000 ){
redState = HIGH;
yellowState = LOW;
greenState = LOW ;
}
digitalWrite(redPin,redState);
digitalWrite(greenPin,greenState);
digitalWrite(yellowPin,yellowState);
//Serial.println("Working");
ambulancestate=digitalRead(ambulance);
raspberrystate=digitalRead(raspberry);
if(ambulancestate==LOW || raspberrystate==HIGH){
digitalWrite(buz,HIGH);
digitalWrite(redPin,LOW);
digitalWrite(greenPin,LOW);
digitalWrite(yellowPin,HIGH);
delay(3000);
digitalWrite(redPin,LOW);
digitalWrite(greenPin,HIGH);
digitalWrite(yellowPin,LOW);
delay(10000);
digitalWrite(buz,LOW);
}
else{
delay(100);
}
}