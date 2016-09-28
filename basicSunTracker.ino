//--------------------------Sun-Seeker---------------------------//
// 9/28/20165 - create basic sun tracking code for DC motor controller//
//---------------------------------------------------------------//

//assigning analog input pin to the sensors
int pinin1=A0, pinin2=A1, pinin3=A2, pinin4=A3;

//store analog values of LDR sensors
int sensorValue1=0, sensorValue2=0, sensorValue3=0, sensorValue4=0;

//digital out comparing sensor values 
int stpin1, stpin2, stpin3, stpin4; 

//these digital output for driving two motors 
const int m1=2, m2=3, m3=4, m4=5, m5=6, m6=7;

//counter parameters
int interval_to_read_sensor_value=0,loop_count=0;


//robot's basic functions
void stop_right_there();
void move_forward_searching_light();
void rotate_in_dir_of_light();


void setup()
{
  //horizontal motor
  pinMode(m1,OUTPUT); //ENA
  pinMode(m2,OUTPUT); //IN1
  pinMode(m3,OUTPUT); //IN2
  //vertical motor
  pinMode(m4,OUTPUT); //ENB
  pinMode(m5,OUTPUT); //IN3
  pinMode(m6,OUTPUT); //IN4
}

void loop()
{
  //horizontral motor
  sensorValue1 = analogRead(pinin1);    
  if(sensorValue1<=150)
    stpin1=HIGH;
  else
    stpin1=LOW;
  sensorValue2 = analogRead(pinin2);    
  if(sensorValue2<=150)
    stpin2=HIGH; 
  else
    stpin2=LOW;
  
  //vertical motor
  sensorValue3 = analogRead(pinin3);    
  if(sensorValue3<=150)
    stpin3=HIGH;
  else
    stpin3=LOW;
  sensorValue4 = analogRead(pinin4);    
  if(sensorValue4<=150)
    stpin4=HIGH; 
  else
    stpin4=LOW;
  
  // horizontal motor
  // 1st condition both sensor detect light
  if (stpin1==HIGH && stpin2==HIGH) 
  {
    stop_right_there_h();
  }
  //2nd condition both sensor doesnot detect light
  else if(stpin1==LOW && stpin2== LOW)
  {
    move_forward_searching_light_h();
  }
  //3rd condition one of the sensor detect light
  else
  {
    rotate_in_dir_of_light_h();
  }
  
  // vertical motor
  // 1st condition both sensor detect light
  if (stpin3==HIGH && stpin4==HIGH) 
  {
    stop_right_there_v();
  }
  //2nd condition both sensor doesnot detect light
  else if(stpin3==LOW && stpin4== LOW)
  {
    move_forward_searching_light_v();
  }
  //3rd condition one of the sensor detect light
  else
  {
    rotate_in_dir_of_light_v();
  }
  
  // check interval readings
  if(interval_to_read_sensor_value==500)
  {
    digitalWrite(m2,LOW);
    digitalWrite(m3,LOW);
    digitalWrite(m5,LOW);
    digitalWrite(m6,LOW);
    delay(5000);
    interval_to_read_sensor_value=0;
    loop_count++;
    stop_right_there();
  }
  if(loop_count==4)
    exit(0);
}

void stop_right_there_h()
{
  digitalWrite(m1,LOW);
  // delay(50);
  return;
}

void stop_right_there_v()
{
  digitalWrite(m4,LOW);
  // delay(50);
  return;

}

void move_forward_searching_light_h() 
{
  //double check which one controls motor
  digitalWrite(m1,HIGH);
  digitalWrite(m2,HIGH);
  digitalWrite(m3,LOW);
  delay(20);
  interval_to_read_sensor_value++;
  stop_right_there();
  return;
}
void move_forward_searching_light_v()
{
  //double check which one controls motor
  digitalWrite(m4,HIGH);
  digitalWrite(m5,HIGH);
  digitalWrite(m6,LOW);
  delay(20);
  interval_to_read_sensor_value++;
  stop_right_there();
  return;
}

void rotate_in_dir_of_light_h()
{
  if(stpin1==HIGH && stpin2==LOW)
  {
    digitalWrite(m1,HIGH);
    digitalWrite(m2,HIGH);
    digitalWrite(m3,LOW);  
    delay(50);
    stop_right_there();
    return;
  }
  else
  {
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    digitalWrite(m3,HIGH);
    delay(50);
    stop_right_there();
    return;
  } 
}

void rotate_in_dir_of_light_v()
{
  if(stpin3==HIGH && stpin4==LOW)
  {
    digitalWrite(m4,HIGH);
    digitalWrite(m5,HIGH);
    digitalWrite(m6,LOW);  
    delay(50);
    stop_right_there();
    return;
  }
  else
  {
    digitalWrite(m4,HIGH);
    digitalWrite(m5,LOW);
    digitalWrite(m6,HIGH);
    delay(50);
    stop_right_there();
    return;
  } 
}

