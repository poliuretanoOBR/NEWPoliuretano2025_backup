//positive values = turn left. Inclination turn (slower)
void inc_turn(int alfa) {
    //sensor addres and value of Z axis of gyroscope
    int16_t GyZ=0;
  
    double total_alfa = 0.0, dimensional_error = 1.08; //error calculated by the difference in degree 
  
    //timer variables
    unsigned long previoustimer = millis();
    double elapsedtime;
    
    //while it didn't walk to the said angle "alfa"
    while(abs(total_alfa) <= abs(alfa)){
  
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
        
      total_alfa += (double)GyZ * dimensional_error * elapsedtime / 131.0; //scale in degrees/seconds. For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
  
      //debug
      //Serial.println(GyZ);
      
      //turns to left when positive, right when negative. Slowered from 150 to 80
      if (alfa < 0)walk(80, -80);
      if (alfa > 0)walk(-80, 80);
  
      //debug
      //   Serial.println(total_alfa);
    }
    //stops
    freeze(50);
}



//function to look for green at inclination (slowered and with higher delays considering the "drift")
void inc_analyze_green() {

    //bool for detecting green on crossroad
    int leftgreen=0, rightgreen=0;
  
  
    //starts walking while looking for green
    walk(150, 150);
  
    //if it detects green once, keeps the information
    for (int i = 0; i < 10; i++) {
      readLED();
      if (i == 7){
        walk(0, 0);
        delay(10);
        readLED();
      }
      
      else walk(80, 80);
  
      //condition for green: green is the lowest value on the color read and red value is higher than blue
      if(gl < rl && gl < bl && rl > bl && higher(rl, gl, bl)-lower(rl, gl, bl)>=20){
        leftgreen=1;
      }
       
      if(gr < rr && gr < br && rr > br && higher(rr, gr, br)-lower(rr, gr, br)>=20){
        rightgreen=1;
      }
      
      delay(10);
    }
    
  
    //if there's green on both sides
    if (leftgreen == 1 && rightgreen == 1) {
  
      //ledcontrol for debug "there are 2 greens"
      LEDcontrol(1,0,0);
  
      //turn on the green led and turns 170 degrees (safer than to search the black line at inclination)
      digitalWrite(LEDG, 1);
      walk(-150, -150);
      delay(500);
      inc_turn(-150);

      walk(200, 200);
      delay(200);
      unsigned long f = millis();
      while (millis() - f < 1000) {
        array_read();
        PIDwalk(0.5);
        delay(5);
      }
      //stops
      walk(0, 0);
      digitalWrite(LEDG, 0);
  
      //turns off ledcontrol for debug "there are 2 greens"
      LEDcontrol(0,0,0);
    }
  
    //if there's green on left side
    else if (leftgreen == 1) {
  
      //ledcontrol for debug "there's a green" 
      LEDcontrol(0,1,0);


      //turn on the green led and turns 60 degrees (safer than to search the black line at inclination)
      digitalWrite(LEDG, 1);
      walk(-150, -150);
      delay(400); 
      inc_turn(80);

      
      walk(265, 265);
      delay(100);
  
      //stops
      walk(0, 0);
      digitalWrite(LEDG, 0);
  
      //turns off ledcontrol for debug "there's a green"
      LEDcontrol(0,0,0);
    }
  
    //if there's green on right side
    else if (rightgreen == 1) {
      //ledcontrol for debug "there's a green"
      LEDcontrol(0,1,0);
      walk(-150, -150);
      delay(400);

      //turn on the green led and turns 60 degrees (safer than to search the black line at inclination)
      digitalWrite(LEDG, 1);
      inc_turn(-70);
  
      walk(265, 265);
      delay(100);
  
      //stops
      walk(0, 0);
      digitalWrite(LEDG, 0);
  
      //turns off ledcontrol for debug "there's a green"
      LEDcontrol(0,1,0);
    }
    
    //if there's no green
    else {
      //ledcontrol for debug "there's NOT a green"
      LEDcontrol(0,0,1);
  
      walk(-150, -150);
      delay(200);
      
      //does pid for a while
      unsigned long f = millis();
      while (millis() - f < 1500) {
        array_read();
        PIDwalk(0.5);
        delay(5);
      }
  
      //turns off ledcontrol for debug "there's NOT a green"
      LEDcontrol(0,0,1);
    }
    
}
  

//uses mercury sensor to detect inclination
void DetectInclinationDOWN() {
    bool getup=0;
    int ninety_countl = 0, ninety_countr = 0;
    if (digitalRead(MERC))ram++;
    else ram = 0;
    if (ram >= 3){
      freeze(50);
      set_servo(1, 180);
      ram=5;
      Serial.println("i got down");
    }
    while (ram >= 3)  {
        Serial.println(ram);

        if (millis() - flag_loop > 10) {
            //battery alert and array read
            // BuzzerAlert();
            array_read();
            //Crossroad
            if((ms >=  MIDDLE_BLACK && NOSIB() >= 2) || NOSIB()>=3) {
                //Stop the robot when enters crossroad
                back(205);
                delay(100);
                back(100);
                delay(100);

                //analyzes green
                inc_analyze_green();
            }

            // Normal line follower
            else {
                
                if (ers > BLACK + 100 && ms < 300 && els < 300)ninety_countr++;//if an extreme sensor is on black and the middle sensor us on while alongside th opposite extreme sensor
                else ninety_countr = 0;//making the counter go to zero
                if (els > BLACK + 100 && ms < 300 && ers < 300)ninety_countl++;//if an extreme sensor is on black and the middle sensor us on while alongside th opposite extreme sensor
                else ninety_countl = 0;  //making the counter go to zero
                if(ninety_countr >= 5)//if the counter of ninety curve is higher than 2 do a 90 deegre curve
                {
                  walk(-150, -150);
                  delay(300);
                  turn(-40);
                }
                else if(ninety_countl >= 5)//if the counter of ninety curve is higher than 2 do a 90 deegre curve
                {
                  walk(-150, -150);
                  delay(300);
                  turn(40);
                }
                //line follower
                PIDwalk(0.5);
                //   array_print();
                
                //obstacle
                getObstacle();
            
                //turns off all led
                LEDcontrol(0, 0, 0);
                
                //search for finish line
                finish_line();
            }
            flag_loop = millis();
            getup=1;
            if (digitalRead(MERC) && ram < 10)ram++;
            else if (!digitalRead(MERC))ram--;
        }
    }
  
    if (getup){freeze(50);set_servo(1, 10);getup=0;}
}


//uses mercury sensor to detect inclination
void DetectInclinationUP() {
    bool getup=0;
    int ninety_countl = 0, ninety_countr = 0;
    if (digitalRead(MERC2))ram2++;
    else ram2 = 0;
    if (ram2 >= 10){
      freeze(50);
      set_servo(1, 180);
      ram2=5;
      Serial.println("i got down");
    }
    while (ram2 >= 10)  {
        Serial.println(ram2);
        if (millis() - flag_loop > 10) {
            //battery alert and array read
            // BuzzerAlert();
            array_read();
            //Crossroad
            if((ms >=  MIDDLE_BLACK && NOSIB() >= 2) || NOSIB()>=3) {
                //Stop the robot when enters crossroad
                back(205);
                delay(100);
                back(100);
                delay(100);

                //analyzes green
                inc_analyze_green();
            }

            // Normal line follower
            else {
              if (ers > BLACK + 100 && ms < 300 && els < 300)ninety_countr++;//if an extreme sensor is on black and the middle sensor us on while alongside th opposite extreme sensor
              else ninety_countr = 0;//making the counter go to zero
              if (els > BLACK + 100 && ms < 300 && ers < 300)ninety_countl++;//if an extreme sensor is on black and the middle sensor us on while alongside th opposite extreme sensor
              else ninety_countl = 0;  //making the counter go to zero
              if(ninety_countr >= 5)//if the counter of ninety curve is higher than 2 do a 90 deegre curve
              {
                walk(-150, -150);
                delay(300);
                turn(-40);
              }
              else if(ninety_countl >= 5)//if the counter of ninety curve is higher than 2 do a 90 deegre curve
              {
                walk(-150, -150);
                delay(300);
                turn(40);
              }

                //line follower
                PIDwalk(0.5);
                //   array_print();
                
                //obstacle
                getObstacle();
            
                //turns off all led
                LEDcontrol(0, 0, 0);
                
                //search for finish line
                finish_line();
            }
            flag_loop = millis();
            getup=1;
            if (digitalRead(MERC2) && ram2 < 10)ram2++;
            else if (!digitalRead(MERC2))ram2--;
        }
    }
  
    if (getup){freeze(50);set_servo(1, 10);getup=0;}
}
