int sharp_left, sharp_right;
int ini_angle=0;

void scan_entrance_RCJ()
{
   freeze(50);//stops the robot for 50 milliseconds

  media_vl = getmUltra(2,15);//get the media for top us
  delay(25);//default delay for getting information

  media_vr = getmUltra(4,15);//get the media for right us
  delay(25);//default delay for getting information

  if(media_vl < 15.0)//if the robot is closer to the left wall
  {
    ent_s = -1;//used for turns, when the entrance is in left ent_s = -1 
    LEDcontrol(0,0,1);
    delay(500);
    LEDcontrol(0,0,0);
  } 

  else if(media_vr < 15.0)//if the robot is closer to the right wall
  {
    ent_s = 1;//used for turns, when the entrance is in right ent_s = 1
    LEDcontrol(0,1,0);
    delay(500);
    LEDcontrol(0,0,0);
  }

  else
  {
    ent_s = 1;
    ent_m = 1;
    LEDcontrol(1,0,0);
    delay(500);
    LEDcontrol(0,0,0);
  }
  
  if (ent_m==0)
  {
    turn(90*ent_s);
    touch(2000);
    walk_distance(45.0);
    turn(-90*ent_s);
  }
  walk_distance(45.0);
}


void update_angle_RCJ(int ang)
{
  ini_angle+=ang;
}

void scan_turn_RCJ(int alfa) 
{
  int ang_to_balls=0; //the angle 'to turn for the victim

  //union to read the float values in bytes
  union 
  {
    byte bytes[4]; //array of bytes
    float dist_to_balls; //name os the float
  }floatUnion; //name of the union

  while (ini_angle < 360) //turning 360 degrees
  {
    turn(alfa); //turns alfa degrees before checking the camera

    freeze(100); //waits

    //if there are 6 or more bytes that the camera sent
    if (DEBUG_SERIAL.available() >= 6){
      ang_to_balls = DEBUG_SERIAL.read() | (DEBUG_SERIAL.read() << 8); //reads the first two bytes, set as int
      
      //Reads the last 4 bytes, sets as the union float
      for (int i = 0; i < 4; i++){
        floatUnion.bytes[i] = DEBUG_SERIAL.read();
      }
    }
    //turns to the victim
    turn(ang_to_balls);
    
    //if there is a change in the integer
    if (ang_to_balls != 0) {
      walk_distance(floatUnion.dist_to_balls); //walks to the victim
      SwallowBalls(); //catches the victim
      walk_distance((floatUnion.dist_to_balls*-1)); //walks back
    }

    update_angle_RCJ(alfa);//updates angle

    //back for a new loop
    ang_to_balls=0;
    for (int i = 0; i < 4; i++) {
      floatUnion.bytes[i] = 0;
    }

    delay(200);//waits a little
  }

  ini_angle = 0;//the initial angle goes back to 0 after a 360 turn
}

void Evacuation_Zone()
{
    scan_entrance_RCJ();
    //look for the victims
    
    //medir sharps
    sharp_left = getmsharp(10);
    sharp_right = getmsharp(10);
    

    // ir pra diagonal do lado da parede oposta
    //  andar um pouco enquanto procura
    // girar 360 enquanto procura, pegar bolas se achar
    // se faltar alguma bola, girar 90 no mesmo sentido andar mais um poucoo praoutra diagonal
    // gira 360, e provavelmennte pegar as 3 bolas
    // procurar triangulo dos mesmos lugares
    // depositar
    // procurar saida e sair 
}