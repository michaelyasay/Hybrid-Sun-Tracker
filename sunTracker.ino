//Hybrid Sun Tracker System 1.0
//09282016 - Created draft code based on Servo motor
//         - added motor pins


int hMotCounter = 0; 
int hLimitHigh = 160;
int hLimitLow = 20;

int vMotCounter = 0; 
int vLimitHigh = 160;
int vLimitLow = 20;

//Motor Pin Map
int ENA=2, IN1=3, IN2=4, ENB=5, IN3=6, IN4=7

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
    if (servov > servovLimitHigh) 	// check for limit switch either replace this with limit switch with debounce
     { 
      servov = servovLimitHigh;		// flag to indicate already in the limit
     }
    delay(10);
  }
 
  else if (avgbot < avgtop)		// top sensor is higher that bottom
  {
    // move vertical motor backward
    vMotorDown();
    if (servov < servovLimitLow)	// check for limit switch either replace this with limit switch with debounce
  {
    servov = servovLimitLow;		// flag to indicate already in the limit
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
    if (servoh > servohLimitHigh)	// check for limit switch either replace this with limit switch with debounce
    {
    servoh = servohLimitHigh;		// flag to indicate already in the limit
    }
    delay(10);
  }
 
  else if (avgright > avgleft)		// right sensor is higher than left
  {
    // move horizontal motor to the left
    hMotorleft();
    if (servoh < servohLimitLow)	// check for limit switch either replace this with limit switch with debounce
     {
     servoh = servohLimitLow;		// flag to indicate already in the limit
     }
    delay(10);
  }
 
  else 
  {
    hMotorStop(); // this stops the horizontal motor
  }
  delay(50);
}
