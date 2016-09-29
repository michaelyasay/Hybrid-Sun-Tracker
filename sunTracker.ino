//Hybrid Sun Tracker System 1.0
//09282016 - Created draft code based on Servo motor
//         - added motor pins
//09292016 - added motor control signals

//horizontal motor fixed values
int hMotCounter = 0; 
int hLimitHigh = 160;
int hLimitLow = 20;

//vertical motor fixed values
int vMotCounter = 0; 
int vLimitHigh = 100;
int vLimitLow = 20;

//sensor gap/difference limit
int sensorDiff = 50; 


// Motor Pin Map 
// Upward movement condition ENA = High, IN1 = High, IN2 = Low
// Downward movement condition ENA = High, IN1 = Low, IN2 = High
// pan Right movement condition ENB = High, IN3 = High, IN4 = Low
// Pan Left movement condition ENB = High, IN3 = Low, IN4 = High
// Vertical/Horizontal Motor Stop condition ENX = Low or IN1=IN2/IN3=IN4 

int ENA=2, IN1=3, IN2=4, ENB=5, IN3=6, IN4=7;

//Assigning LDRs
int ldrtopl = 2; //top left LDR green
int ldrtopr = 1; //top right LDR yellow
int ldrbotl = 3; // bottom left LDR blue
int ldrbotr = 0; // bottom right LDR orange

 void setup () 
 {
  Serial.begin(9600);
 }

void loop()
{
  //capturing analog values of each LDR
  int topl = analogRead(ldrtopl);	
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);

  // calculating average
  int avgtop = (topl + topr) / 2; 	// average of top LDRs
  int avgbot = (botl + botr) / 2; 	// average of bottom LDRs
  int avgleft = (topl + botl) / 2; 	// average of left LDRs
  int avgright = (topr + botr) / 2; 	// average of right LDRs

  if (avgtop < avgbot)			// bottom sensor is higher the top
  {
    //move vertical motor forward
    vMotorUp(); 
    if (vMotCounter > vLimitHigh) 	// check for limit switch either replace this with limit switch with debounce
     { 
      vMorCounter = vLimitHigh;		// flag to indicate already in the limit
     }
    delay(10);
  }
 
  else if (avgbot < avgtop)		// top sensor is higher that bottom
  {
    // move vertical motor backward
    vMotorDown();
    if (vMotCounter < vLimitLow)	// check for limit switch either replace this with limit switch with debounce
  {
    vMotCounter = vLimitLow;		// flag to indicate already in the limit
  }
    delay(10);
  }
 
  else 
  {
    vMotorStop();     // this stops the vertical motor
  }
  
  if (avgleft > avgright)		// left sensor is higher than right
  {
    // move horizontal motor to the right
    hMotorRight();
    if (hMotCounter > hLimitHigh)	// check for limit switch either replace this with limit switch with debounce
    {
     hMotCounter = hLimitHigh;		// flag to indicate already in the limit
    }
    delay(10);
  }
 
  else if (avgright > avgleft)		// right sensor is higher than left
  {
    // move horizontal motor to the left
    hMotorleft();
    if (hMotCounter < hLimitLow)	// check for limit switch either replace this with limit switch with debounce
     {
      hMotCounter = hLimitLow;		// flag to indicate already in the limit
     }
    delay(10);
  }
 
  else 
  {
    hMotorStop(); // this stops the horizontal motor
  }
  delay(50);
}

vMotorUp(){
 //code to tilt upwards
 digitalWrite(ENA,HIGH);
 digitalWrite(IN1,HIGH);
 digitalWrite(IN2,LOW); 
 
 // increment the counters
 vMotCounter = vMotCounter + 1;
}

vMotorDown(){
 //code to tilt downwards
 digitalWrite(ENA,HIGH);
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,HIGH); 
 
 // decrement the counters
 vMotCounter = vMotCounter - 1;
}

vMotorStop(){
 //code to stop vertical motor
 digitalWrite (ENA, LOW);
}

hMotorRight(){
 //code to pan to the right
 digitalWrite(ENB,HIGH);
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW); 
 //increment the counters
 hMotCounter = hMotCounter + 1;
}

hMotorLeft(){
 //code to pan to the left
 digitalWrite(ENB,HIGH);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH); 
 // decrement the counters
 hMotCounter = hMotCounter - 1;
}

hMotorStop(){
 //code to stop horizontal motor
 digitalWrite (ENB, LOW);
}

 
