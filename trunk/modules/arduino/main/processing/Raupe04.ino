// IR remote control code
#include <IRremote.h>
#include <IRremoteInt.h>
#include <Servo.h> 
#include <SerialCommand.h>

SerialCommand SCmd;   // The demo SerialCommand object

Servo myservo;  // create servo object to control a servo 

int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key = 0;

const unsigned long UP = 16677509;
const unsigned long DOWN = 16673429;
const unsigned long LEFT = 16701989;
const unsigned long RIGHT = 16653029;
const unsigned long ENTER = 16669349;
const unsigned long POWER = 16666799;
const unsigned long BACKLIGHT = 16704029;
const unsigned long FRONTLIGHT = 16687709;

//Standard PWM DC control

const int E1 = 5;     //M1 Speed Control
const int E2 = 6;     //M2 Speed Control
const int M1 = 4;    //M1 Direction Control
const int M2 = 7;    //M1 Direction Control

int vLinks = 0;
int vRechts = 0;
const int V_STEP = 10;
const int V_MAX = 90;
const int V_THRESH = 40;

const int REDPIN = 9;                 // LED connected to digital pin
const int YELLOWPIN = 10;                 // LED connected to digital pin

int redPinStatus = LOW;
int yellowPinStatus = LOW;

const int LR_PIN = 3;

int serialData = 0;
unsigned long serialdata;
int inbyte;

void setup(void)
{
  int i;
  for(i=4;i<=7;i++)
    pinMode(i, OUTPUT); 

  pinMode(REDPIN, OUTPUT);      // sets the digital pin as output
  digitalWrite(REDPIN, redPinStatus);   // sets the LED on

  pinMode(YELLOWPIN, OUTPUT);      // sets the digital pin as output
  digitalWrite(YELLOWPIN, yellowPinStatus);   // sets the LED on

  myservo.attach(LR_PIN);  // attaches the servo on pin 3 to the servo object 

  //    Serial.begin(19200);      //Set Baud Rate
  Serial.begin(115200);      //Set Baud Rate

  // Setup callbacks for SerialCommand commands 
  SCmd.addCommand("lr",setLR);  
  SCmd.addCommand("key",setKey);  
  SCmd.addDefaultHandler(unrecognized);  // Handler for command that isn't matched  (says "What?") 

  irrecv.enableIRIn(); // Start the receiver
}

void loop(void)
{
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
    key = results.value;
    Serial.println(key, DEC);
  }

//  if (Serial.available() > 0) {
//    getSerial();
//  }

  SCmd.readSerial();     // We don't do much, just process serial commands

  if(key != 0 && key != 4294967295)
  {
    switch(key)
    {
    case LEFT://Turn Left
      setLinksRechts(vLinks-V_STEP,vRechts+V_STEP);             
      break;      
    case RIGHT://Turn Right
      setLinksRechts(vLinks+V_STEP,vRechts-V_STEP);             
      break;         
    case ENTER://Stop Motor
      setLinksRechts(0,0);             
      break;         
    case UP://schneller werden
      if (vLinks != vRechts)
      {
        int vNeu = max(vLinks,vRechts);
        setLinksRechts(vNeu,vNeu); 
      } 
      else
      {
        setLinksRechts(vLinks+V_STEP,vRechts+V_STEP);             
      }
      break;         
    case DOWN://langsamer werden
      if (vLinks != vRechts)
      {
        int vNeu = min(vLinks,vRechts);
        setLinksRechts(vNeu,vNeu); 
      } 
      else
      {
        setLinksRechts(vLinks-V_STEP,vRechts-V_STEP);             
      }
      break;         
    case BACKLIGHT:
      redPinStatus = toggle(redPinStatus);
      digitalWrite(REDPIN,redPinStatus);
      break;         
    case FRONTLIGHT:
      yellowPinStatus = toggle(yellowPinStatus);
      digitalWrite(YELLOWPIN,yellowPinStatus);
      break;    
      //             case SERVO_LINKS:
      //                     val = map(val, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 

    }
//    Serial.print("vLinks=");  
//    Serial.print(vLinks, DEC);  
//    Serial.print(" vRechts=");  
//    Serial.println(vRechts, DEC);  
    key = 0;
  }

  delay(50);

}

void setKey()
{
  char *arg; 

  arg = SCmd.next(); 
  if (arg != NULL) 
  {
    if (!strcmp("UP", arg))
      key = UP;
    else if (!strcmp("LEFT", arg))
      key = LEFT;
    else if (!strcmp("STOP", arg))
      key = ENTER;
    else if (!strcmp("RIGHT", arg))
      key = RIGHT;
    else if (!strcmp("DOWN", arg))
      key = DOWN;

    Serial.print("setKey, first argument: "); 
    Serial.println(arg); 
  } 
  else {
    Serial.println("No argument"); 
  }
}
  
void setLR()
{
  int firstNumber;  
  int secondNumber;  
  char *arg; 

  Serial.println("We're in setLR"); 
  arg = SCmd.next(); 
  if (arg != NULL) 
  {
    firstNumber=atoi(arg);    // Converts a char string to an integer
    Serial.print("First argument was: "); 
    Serial.println(firstNumber); 
  } 
  else {
    Serial.println("No arguments"); 
  }

  arg = SCmd.next(); 
  if (arg != NULL) 
  {
    secondNumber=atol(arg); 
    Serial.print("Second argument was: "); 
    Serial.println(secondNumber); 
  } 
  else {
    Serial.println("No second argument"); 
  }

  setLinksRechts(firstNumber, secondNumber);
}

void setLinksRechts(int links, int rechts)
{
  vLinks = links;
  vRechts = rechts;

  if (abs(vLinks) > V_MAX)
    vLinks = V_MAX * sign(vLinks);
  if (abs(vRechts) > V_MAX)
    vRechts = V_MAX * sign(vRechts);

  setLinks(vLinks);
  setRechts(vRechts);
} 

int sign(int wert)
{
  if(wert >= 0)
    return +1;
  else
    return -1;
}

void setLinks(int links)
{
  if (abs(links) > 0)
    links += V_THRESH * sign(links);

//  Serial.print("links=");  
//  Serial.print(links, DEC);  

  analogWrite (E1,abs(links));      //PWM Speed Control
  digitalWrite(M1,links>0?HIGH:LOW);   
}  

void setRechts(int rechts)
{
  if (abs(rechts) > 0)
    rechts += V_THRESH * sign(rechts);

//  Serial.print(" rechts=");  
//  Serial.println(rechts, DEC);  

  analogWrite (E2,abs(rechts));   
  digitalWrite(M2,rechts>0?HIGH:LOW);
}

int toggle(int status)
{
  int retStatus = 0;

  if (status == HIGH)
    retStatus = LOW;
  else if (status == LOW)
    retStatus = HIGH;

  Serial.print(" retStatus=");  
  Serial.println(retStatus, DEC);  

  return retStatus;
}    

long getSerial()
{
  serialdata = 0;
//  while (inbyte != '/')
  while (Serial.available() > 0)
  {
    inbyte = Serial.read(); 
//    Serial.println("serialData available: ");
//    Serial.println(inbyte);
  }
  return serialdata;
}

// This gets set as the default handler, and gets called when no other command matches. 
void unrecognized()
{
  Serial.println("What?"); 
}

