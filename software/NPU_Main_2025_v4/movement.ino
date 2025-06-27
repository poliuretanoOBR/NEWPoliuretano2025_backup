//Walk function
void old_walk(int left, int right) {
  int l, r;

  //limits the input to 1023
  if (left > 1023)left=1023;
  if (left < -1023)left=-1023;
  if (right > 1023)right=1023;
  if (right < -1023)right=1023;

  //dynamixel works from 0-1023 clock wise and 1024-2047 counterclock wise. This code makes both side work as "positive to 1023" = CW and "negative to 1023" CCW.
  //note it's reversed for the other side as each motor is pointing a direction on the robot
  if (left > 0) {
    l = left;
  } else l = 1024 + abs(left);
  
  if (right > 0) {
    r = right + 1024; //right is slightly faster, so needs a small correction for the straight walk
  } else r = abs(right);

  float auxl, auxr;
  auxl = l*0.229;
  auxr = r*0.229;
  l = auxl;
  r = auxr;


  //aplies the function
  dxl.setGoalVelocity(DXL_ID, l);
  dxl2.setGoalVelocity(DXL_ID2, r);
}

void walk(int rpml, int rpmr)
{
  if(rpml > 265) rpml = 265;
  if(rpmr > 265) rpmr = 265;
  if(rpml < -265) rpml = -265;
  if(rpmr < -265) rpmr = -265;

  dxl2.setGoalVelocity(DXL_ID2, rpml);
  dxl.setGoalVelocity(DXL_ID, -rpmr);
}


void walk_distance(float d)//function used to make the robot walk to a specific distance based on experiments
{
  int sign = abs(d) / d; //if sign is negative makes the robot walk back
  walk(140*sign,130*sign);
  delay((int)(125*abs(d)));
  freeze(100);
}


//Walk back function
void back(int vel) {
  walk(-vel, -vel);
}


//turn right function
void right(int vel)  {
  walk(vel, -vel);
}


//turn left function
void left(int vel) {
  walk(-vel, vel);
}


//Stop for "del" moment
void freeze(int del) {
  walk(0,0); 
  delay(del);
}


//positive values = turn left
void turn(int alfa) {
  // sensor addres and value of Z axis of gyroscope
  int16_t GyZ=0;
  // Serial.println("entrei no turn");
  double total_alfa = 0.0, dimensional_error = 1.08; //error calculated by the difference in degree 

  //timer variables
  unsigned long previoustimer = millis();
  double elapsedtime;
  
  //while it didn't walk to the said angle "alfa"
  while(abs(total_alfa) <= abs(alfa)){
    Serial.println("entrei no while");
    //the elapsed time
    elapsedtime = (double)(millis() - previoustimer) / 1000.0; //as the scale is degrees/seconds, we divided the time in millis by 1000
    previoustimer = millis();
    
    //transmission on wire library
    Wire.beginTransmission(0x68);
    Wire.write(0x47); //0x47 (GYRO_ZOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 2, true); //each axis value is stored in 2 registers
    
    //put the value received on the variable
    GyZ = (Wire.read()<<8|Wire.read()); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    GyZ -=  GYZ_ERROR; //small correction

    // if (abs(GyZ) < 350)GyZ = 0;
    
    total_alfa += (double)GyZ * dimensional_error * elapsedtime / 131.0; //scale in degrees/seconds. For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet

    //debug
     //Serial.println(GyZ);
    
    //turns to left when positive, right when negative
    Serial.println("ALFA:");
    Serial.println(alfa);
    if (alfa < 0)
    {
      Serial.println("girando pra direita");
      walk(SWL, -SWR);
      Serial.println("andando");
    }
    if (alfa > 0)
    {
      Serial.println("girando pra esquerda");
      walk(-SWL, SWR);
      Serial.println("andando");
    }
    // debug
    Serial.println(total_alfa);
  }
  //stops
  Serial.println("fim do turn");
  freeze(50);

}


//need to send walk before
void Simple_turn(int alfa) 
{
  //sensor addres and value of Z axis of gyroscope
  int16_t GyZ=0;
  float total_alfa = 0.0, dimensional_error = 1.0357; //error calculated by the difference in degree 
  //timer variables
  unsigned long previoustimer = millis();
  float elapsedtime;
  //while it didn't walk to the said angle "alfa"
  while( abs(total_alfa) <= abs(alfa) )
  {
    //the elapsed time
    elapsedtime = (float)(millis() - previoustimer) / 1000.0; //as the scale is degrees/seconds, we divided the time in millis by 1000
    previoustimer = millis();
    //transmission on wire library
    Wire.beginTransmission(0x68);
    Wire.write(0x47); //0x47 (GYRO_ZOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 2, true); //each axis value is stored in 2 registers
    //put the value received on the variable
    GyZ = (Wire.read()<<8|Wire.read()); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    GyZ -=  GYZ_ERROR; //small correction
    total_alfa += (float)GyZ * dimensional_error * elapsedtime / 131.0; //scale in degrees/seconds. For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
    //debug
    //Serial.println(GyZ);
    //debug
    //Serial.println(total_alfa);
  }
}


//calculate error on robot resting
void CalculateErrorGyro() {
  float elapsedtime, GyroErrorZ = 0.0;
  int16_t GyroZ = 0;

  //read the value at the Z axis 200 times
  for(int i = 1 ; i <= 10000 ; i++){

    //reading the values
    Wire.beginTransmission(0x68);
    Wire.write(0x47);
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 2, true);
    GyroZ = (Wire.read() << 8 | Wire.read());

    // Sum all readings
    GyroErrorZ += ((float)GyroZ - GyroErrorZ)/(float)i;

    delay(2);
  }

  Serial.println(GyroErrorZ);
}

//function used to make the robot go back and forth. Receives the amount of times to go back and and forth and del is the delay between going foward and back
void back_forth(int times, int del)
{
  for(int i = 0; i < times; i++)//for used to count how many times the robot went back and forth
  {
    walk(SWL,SWR);//walk foward
    delay(del);//delay "del"
    walk(-SWL,-SWR);//walk back
    delay(del);//delay "del"
  }

  freeze(25);
}


//d/(v2/v1-1) = r 
// d/r + 1  = v2/v1
// d/r + 1 = 1/coeff
// 1 / (d/r + 1) = coeff
//the SWL velocity is 7.2 cm/s = 7.2 * 10^-2 m/s
//the 1023 velocity is 13.4 cm/s = 1.34 * 10^-1 m/s

void circle_path(float radius, float ang){
  
  float coeff = 1/(DIST/radius + 1);

  float ctime = (ang*radius)/(7.2*coeff);

  walk((int)(coeff*SWL), SWR);
  delay((int)(ctime*1000));
  walk(0, 0);

}
