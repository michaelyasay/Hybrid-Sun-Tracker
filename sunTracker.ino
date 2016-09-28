#include <Servo.h>
//defining Servos
Servo servohori;
int servoh = 0;
int servohLimitHigh = 160;
int servohLimitLow = 20;

Servo servoverti; 
int servov = 0; 
int servovLimitHigh = 160;
int servovLimitLow = 20;
//Assigning LDRs
int ldrtopl = 2; //top left LDR green
int ldrtopr = 1; //top right LDR yellow
int ldrbotl = 3; // bottom left LDR blue
int ldrbotr = 0; // bottom right LDR orange

 void setup () 
 {
  servohori.attach(10);
  servohori.write(0);
  servoverti.attach(9);
  servoverti.write(0);
  delay(500);
 }

void loop()
{
  servoh = servohori.read();
  servov = servoverti.read();

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
    servoverti.write(servov +1);   	// move to look down
    if (servov > servovLimitHigh) 	// check for limit switch either replace this with limit switch with debounce
     { 
      servov = servovLimitHigh;		// flag to indicate already in the limit
     }
    delay(10);
  }
  else if (avgbot < avgtop)		// top sensor is higher that bottom
  {
    servoverti.write(servov -1);	// move to look up
    if (servov < servovLimitLow)	// check for limit switch either replace this with limit switch with debounce
  {
    servov = servovLimitLow;		// flag to indicate already in the limit
  }
    delay(10);
  }
  else 
  {
    servoverti.write(servov);		// this stops the vertical motor
  }
  
  if (avgleft > avgright)		// left sensor is higher than right
  {
    servohori.write(servoh +1);		// move to face right
    if (servoh > servohLimitHigh)	// check for limit switch either replace this with limit switch with debounce
    {
    servoh = servohLimitHigh;		// flag to indicate already in the limit
    }
    delay(10);
  }
  else if (avgright > avgleft)		// right sensor is higher than left
  {
    servohori.write(servoh -1);		// move to face left
    if (servoh < servohLimitLow)	// check for limit switch either replace this with limit switch with debounce
     {
     servoh = servohLimitLow;		// flag to indicate already in the limit
     }
    delay(10);
  }
  else 
  {
    servohori.write(servoh);		// this stops the horizontal motor
  }
  delay(50);
}