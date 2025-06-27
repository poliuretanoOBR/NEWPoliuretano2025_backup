double getUltra(int u) {
   long duration;
   double distance;

   //ultrasonic "1"
   if (u==1){
      digitalWrite(TRIG1, LOW);
      delayMicroseconds(2);

      //emits the ultrasonic sensor sonor wave
      digitalWrite(TRIG1, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG1, LOW);

      duration = pulseIn(ECHO1, HIGH, 25000); // captures the sonor wave emitted by the ultrasonic sensor. the last parameter is the max distance the sensor will get (_duration = _distance * 2 / 0,0343)
      distance = duration * 0.0343 / 2; // converts the distance in centimeters

      return distance;
   } 

   //ultrasonic "2"
   else if (u==2){
      digitalWrite(TRIG2, LOW);
      delayMicroseconds(2);

      //emits the ultrasonic sensor sonor wave
      digitalWrite(TRIG2, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG2, LOW);

      duration = pulseIn(ECHO2, HIGH, 25000); // captures the sonor wave emitted by the ultrasonic sensor. the last parameter is the max distance the sensor will get (_duration = _distance * 2 / 0,0343)
      distance = duration * 0.0343 / 2; // converts the distance in centimeters

      return distance;
   } 

   //ultrasonic "3"
   else if (u==3){
      digitalWrite(TRIG3, LOW);
      delayMicroseconds(2);

      //emits the ultrasonic sensor sonor wave
      digitalWrite(TRIG3, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG3, LOW);

      duration = pulseIn(ECHO3, HIGH, 25000); // captures the sonor wave emitted by the ultrasonic sensor. the last parameter is the max distance the sensor will get (_duration = _distance * 2 / 0,0343)
      distance = duration * 0.0343 / 2; // converts the distance in centimeters
      
      return distance;
   } 

   //ultrasonic "4"
   else{
      digitalWrite(TRIG4, LOW);
      delayMicroseconds(2);

      //emits the ultrasonic sensor sonor wave
      digitalWrite(TRIG4, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG4, LOW);

      duration = pulseIn(ECHO4, HIGH, 25000); // captures the sonor wave emitted by the ultrasonic sensor. the last parameter is the max distance the sensor will get (_duration = _distance * 2 / 0,0343)
      distance = duration * 0.0343 / 2; // converts the distance in centimeters  
      
      return distance;
   }
}


float getMaxLeftRight() {
   float val_left = 0.0;
   float val_right = 0.0;

   for (int i = 0; i < 20; i++) {
      float aux=getUltra(1);
      if(val_left<aux)val_left=aux;

      aux=getUltra(2);
      if(val_right<aux)val_right=aux;
   }
}

float getmUltra(int u, int den)//function used to get the media of an us sensor
{
   float m_ultra = 0.0;
   for(int i = 0; i < den; i++)
   {
      float aux = getUltra(u);
      if(aux != 0.0) m_ultra += aux;
      else m_ultra += 200;
      delay(3);
   }
   return m_ultra/den; 
}

//negative media
float getmnUltra(int u, int den)//function used to get the media of an us sensor
{
   float m_ultra = 0.0;
   for(int i = 0; i < den; i++)
   {
      float aux = getUltra(u);
      if(aux != 0.0) m_ultra += aux;
      else m_ultra = -1;
      delay(3);
   }
   return m_ultra/den; 
}

//if  detects obstacle with top sensor 5 times in a row, starts obstacle function
void getObstacle() {
   int dist = getUltra(4);
   if (dist < 9.0 && dist != 0.0)count_u++;
   else count_u = 0;
   if (els > BLACK || ers > BLACK)count_u=0;

   if (count_u > 7) {
      walk_distance(-2.0);
      Obstacle('r');
   }
}

void Obstacle(char c) {

   //timer for ultrasonic
   unsigned long flag_obs;
   int obs_side = 0, counter_black = 0; //1 is for right and -1 for left in obs_side
   bool obs_finish = 0;
   int counter_ref = 0;
   while(!obs_finish)
   {
      //if the right side is greater, it turns right
      /*vl = getmnUltra(1, 15);
      vr = getmnUltra(2, 15);
      if (vr >= vl)obs_side=1;
      else obs_side = -1;*/
      //side 
      float lat_dist;//variable used to get the distance of the lateral ultra
      turn(-90*obs_side);//turns 90 deegres to stay parrallel to the obstacle
      walk_distance(2.0);//walk to adjust on line going back

      array_read();
      flag_obs = millis();
      while(els <= BLACK && ers <= BLACK && millis()-flag_obs < 800){
         array_read();
         walk(-SWL, -SWR);
      }
      if(ers<=BLACK && millis()-flag_obs < 400){while(ers<=BLACK && millis()-flag_obs <400){array_read();walk(0, -SWR);}}
      if(els<=BLACK && millis()-flag_obs<400){while(els<=BLACK && millis()-flag_obs<400){array_read();walk(-SWL, 0);}}
      //this while is used for the robot toa adjust on the black line

      lat_dist = getUltra(obs_side==1 ? 1 : 2);//gets the lateral ultra distance

      //walks until it doesn't detects obstacle or for 5 seconds
      flag_obs = millis();
      walk(SWL, SWR);
      while(lat_dist < 25.0 && lat_dist != 0){
         delay(5);
         lat_dist = getUltra(obs_side==1 ? 1 : 2);
         if (millis() - flag_obs > 5000)break; 
      }
      //walks until the robot passes the obstacle
      walk_distance(3.0);//walks a little more to ensure that the robot passed the obstacle
      turn(85*obs_side);//turns left and reads the value of left ultra
      lat_dist = getUltra(obs_side==1 ? 1 : 2);//gets the lateral ultra distance
      
      //walks until the robot detects the obstacle
      walk(SWL, SWR);
      flag_obs = millis();
      while(lat_dist > 20.0 || lat_dist== 0.0) {
         array_read();
         delay(5);
         lat_dist = getUltra(obs_side==1 ? 1 : 2);
         if (millis() - flag_obs> 5000)break;
      }
      //while the robot walks until detects black line or for 2.5 seconds
      while(millis()-flag_obs < 2500 && counter_black <= 2)
      {
         array_read();
         walk(SWL,SWR);
         if(NOSIB() > 1)
         {
            counter_black++;
         }
      }
      if(counter_black > 2) //if the robot detected the black line more than 2 times
      {
         obs_finish = 1; //the robot already finished the obstacle
      }
      if(obs_finish == 1)//if the robot finished the obstacle
      {
         walk_distance(3.0);  
         flag_obs = millis();
         while(els<=BLACK && ers<=BLACK && millis()-flag_obs<800){
            array_read();
            walk(-SWL, -SWR);
         }
         if(ers<=BLACK && millis()-flag_obs<400){while(ers<=BLACK && millis()-flag_obs<400){array_read();walk(0, -SWR);}}
         if(els<=BLACK && millis()-flag_obs<400){while(els<=BLACK && millis()-flag_obs<400){array_read();walk(-SWL, 0);}}
         //this while is used for the robot toa adjust on the black line
         turn(-90*obs_side);
         walk_distance(-4.0);
         flag_obs = millis();
         while(millis - flag_obs < 1000)
         {
            array_read();
            PIDwalk(0.6);    
         }
         break;
      }

      lat_dist = getUltra(obs_side==1 ? 1 : 2);//gets the lateral ultra distance

      //walks until it doesn't detects obs_sidetacle or for 5 seconds
      flag_obs = millis();
      walk(SWL, SWR);
      while(lat_dist < 25.0 && lat_dist != 0){
         delay(5);
         lat_dist = getUltra(obs_side==1 ? 1 : 2);
         if (millis() - flag_obs > 5000)break; 
      }

      turn(85*obs_side);//turns to continue its path (ultimo giro do caminho normal)
      
      //walks until the robot detects the obstacle
      walk(SWL, SWR);
      flag_obs = millis();
      while(lat_dist > 20.0 || lat_dist== 0.0) {
         array_read();
         delay(5);
         lat_dist = getUltra(obs_side==1 ? 1 : 2);
         if (millis() - flag_obs> 5000)break;
      }

      //while the robot walks until detects black line
      while(millis()-flag_obs < 2500 && counter_black <= 2)
      {
         array_read();
         walk(SWL,SWR);
         if(NOSIB() > 1)
         {
            counter_black++;
         }
      }
      if(counter_black > 2) //the robot already finished the obstacle
      {
         obs_finish = 1;
      }
      if(obs_finish == 1)//if the robot finished the obstacle
      {
         walk_distance(3.0);  
         flag_obs = millis();
         while(els<=BLACK && ers<=BLACK && millis()-flag_obs<800){
            array_read();
            walk(-SWL, -SWR);
         }
         if(ers<=BLACK && millis()-flag_obs<400){while(ers<=BLACK && millis()-flag_obs<400){array_read();walk(0, -SWR);}}
         if(els<=BLACK && millis()-flag_obs<400){while(els<=BLACK && millis()-flag_obs<400){array_read();walk(-SWL, 0);}}
         turn(-90*obs_side);
         walk_distance(-4.0);
         flag_obs = millis();
         while(millis - flag_obs < 1000)
         {
            array_read();
            PIDwalk(0.6);    
         }
         break;
      }
      
       //walks until it doesn't detects obs_sidetacle or for 5 seconds
      flag_obs = millis();
      walk(SWL, SWR);
      while(lat_dist < 25.0 && lat_dist != 0){
         delay(5);
         lat_dist = getUltra(obs_side==1 ? 1 : 2);
         if (millis() - flag_obs > 5000)break; 
      }

      //fim do caminho normal
      walk_distance(3.0);
      turn(85*obs_side);
      walk(SWL, SWR);
      
      flag_obs = millis();
      while(lat_dist > 20.0 || lat_dist== 0.0) {
         array_read();
         delay(5);
         lat_dist = getUltra(obs_side==1 ? 1 : 2);
         if (millis() - flag_obs> 5000)break;
      }
      walk_distance(15.0);
      flag_obs = millis();
      while(els<=BLACK && ers<=BLACK && millis()-flag_obs<800){
         array_read();
         walk(-SWL, -SWR);
      }
      if(ers<=BLACK && millis()-flag_obs<400){while(ers<=BLACK && millis()-flag_obs<400){array_read();walk(0, -SWR);}}
      if(els<=BLACK && millis()-flag_obs<400){while(els<=BLACK && millis()-flag_obs<400){array_read();walk(-SWL, 0);}}
      turn(-90*obs_side);
      walk_distance(-4.0);
      flag_obs = millis();
      while(millis - flag_obs < 1000)
      {
         array_read();
         PIDwalk(0.6);    
      }
      break;
   }
}
