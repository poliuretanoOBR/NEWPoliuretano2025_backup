int sharp_left, sharp_right;
int cur_angle=0;

void scan_entrance_RCJ()
{
  freeze(50);//stops the robot for 50 milliseconds

  sharp_left = getmsharp(10);
  sharp_right = getmsharp(10);

  if(sharp_left < 200)//if the robot is closer to the left wall (this value isn't real)
  {
    ent_s = -1;//used for turns, when the entrance is in left ent_s = -1 
    LEDcontrol(0,0,1);
    delay(500);
    LEDcontrol(0,0,0);
  } 

  else if(sharp_right < 200)//if the robot is closer to the right wall (this value isn't real)
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

  Serial.println('C');
  delay(500);
}


void update_angle_RCJ(int ang)
{

  cur_angle+=ang;
  if(cur_angle < 0)//if angle is negative 
  {
    cur_angle += 360;//adds 360 
  }
  else if(cur_angle > 360)//else if angle is higher than 360
  {
    cur_angle -= 360;//subtracts 360
  }
}

void scan_turn_RCJ(int alfa) 
{
  Serial.println("A");
  delay(100);
  bool analyze=0;
  int ang_alive, dist_alive, ang_dead, dist_dead, ang_tri_g, dist_tri_g, ang_tri_r, dist_tri_r;
  while (cur_angle < 360) //turning 360 degrees
  { 
    if (analyze == 1)
    {
      Serial.println("A");
      analyze=0;
      delay(100);
    }
    matrix_read();
    int objects = detection_i + 1;
    for(int i = 0; i < objects; i++)
    {
      if (detection_matrix[i][0] == 0) 
      {
        dist_alive = detection_matrix[i][1];
        ang_alive = detection_matrix[i][2];
        break;
      }
      // else if (detection_matrix[i][0] == 1) 
      // {
      //   ang_dead = detection_matrix[i][1];
      //   dist_dead = detection_matrix[i][2];
      // }
      // else if (detection_matrix[i][0] == 2) 
      // {
      //   ang_tri_g = detection_matrix[i][1];
      //   dist_tri_g = detection_matrix[i][2];
      // }
      // else if (detection_matrix[i][0] == 3) 
      // {
      //   ang_tri_r = detection_matrix[i][1];
      //   dist_tri_r = detection_matrix[i][2];
      // }
    }
    turn(ang_alive);
    walk_distance(dist_alive);
    SwallowBalls();
    turn(alfa);
    cur_angle += alfa + ang_alive;
    analyze=1;
  }

  cur_angle = 0;//the initial angle goes back to 0 after a 360 turn
}


void matrix_read() {
  detection_i=0;
  detection_j=0;
  if (Serial.available()) 
  {
    String message = Serial.readStringUntil('\n');  // read the string
    //Serial.println(message);// print the string
    
    while (message.length() > 0)
    {
      int separator = message.indexOf(',');
      int num = 0;
      if(separator != -1)
      {
        num = message.substring(0, separator).toInt();
        message = message.substring(separator+1);
      }
      else 
      {
        num = message.toInt();
        message = ""; 
      }
      
      detection_matrix[detection_i][detection_j] = num;
      detection_j++;
      if(detection_j == 3)
      {
        detection_j=0;
        detection_i++;
      }
    }
    // int objects = detection_i + 1;
    // for(int i = 0; i < objects; i++)
    // {
    //   for(int j = 0; j < 3; j++)
    //   {
    //     Serial.print(detection_matrix[i][j]);
    //     Serial.print(" ");
    //   }
    // }
  }
}

void Evacuation_Zone()
{
  scan_entrance_RCJ();

  //look for the victims
  scan_turn_RCJ(30);
  
  // procurar triangulo dos mesmos lugares
  // depositar
  // procurar saida e sair 
}