void go_to_mid_120()
{
  if(roomL == 120)
  {
    if(ent_m == 0)// left/right entrance
    {
      turn(ent_s*90);//turn 90 deegres right / left
      touch(3000);//touch function

      walk_distance(32.0);//goes to next tile that is garanted to not be an exit 
      turn(ent_s*-90);//turns
      touch(3000);//adjusts on wall
      media_vt = getmUltra(3,15);//gets the media of the top US
      if(media_vt > 3000.0)//exit
      {
        turn(ent_s*90);//turns back
        walk_distance(R_MID_90);//goes to mid on the x axis
        turn(ent_s*-90);//turns to face the y axis
        touch(2000);//adjusts on wall
        go_to_dist(R_MID_90);//goes to mid on y axis
      }
      else//theres no exit so its safe to continue the default path
      {
        walk_distance(R_MID_90);//goes to mid on the y axis
        turn(ent_s*90);//turns to face the x axis
        freeze(25);
        media_vt = getmUltra(3,15);//gets the media of top US
        if(media_vt > 3000.0)//exit
        {
          turn(ent_s*-90);//goes back to the previous position
          touch(8000);//goes back to the previous position
          turn(ent_s*90);//makes the robot face the x axis
          go_to_dist(R_MID_120);//goes to mid on the y axis
        }
        else//theres no exit so its safe to continue the default path 
        {
          walk_distance(18.0);//goes to mid on the y axis
        }
      }
      
    }


    else //mid entrance
    {
      media_vl = getmUltra(1,15);//gets the media of the left US
      delay(25);//delay for getting the information
      media_vr = getmUltra(2,15);//gets the media of the right US
      //set ent_s based on the closest wall to the robot
      if(media_vl > 90.0 && media_vl < 100.0) ent_s = 1;// if the left media is between 90 and 100, entrance side is right
      else if(media_vr > 90.0 && media_vr < 100.0) ent_s = -1;//if the right media is between 90 and 100, entrance side is left
      else ent_s = -1; //else, entrance side is left

      media_vt = getmUltra(3,15);//gets the media of the top US
      if(media_vt > 3000.0)
      {
        turn(ent_s*90);//makes the robot face the x axis
        walk_distance(R_MID_120);//goes to mid on the y axis
        turn(ent_s*-90);//turn -90
        touch(2000);//adjusts on wall
        go_to_dist(R_MID_90);//goes to mid on the y axis
      }
      else
      {
        walk_distance(R_MID_90);//goes to mid on the y axis
        turn(ent_s*90);//makes the robot face the x axis
        media_vt = getmUltra(3,15);//gets the media of the top US
        if(media_vt > 3000.0)//if the top media is more than 120
        {
          turn(ent_s*-90);//turn -90
          walk_distance(-(R_MID_90));//goes back on the y axis
          turn(ent_s*90);//makes the robot face the x axis
          touch(2000);//ajusts on wall
          walk_distance(R_MID_120);//goes to mid on the y axis
          turn(ent_s*-90);//go to -90
          go_to_dist(R_MID_90);//goes to mid on the y axis
        }
        else
        {
          walk_distancewb(16.0);//goes to mid on the y axis
        }
      }
    }
    
  }


  else
  {
    
    if(ent_m == 0)
    {
      turn(ent_s*90);
      touch(5000);//adjusts on wall
      walk_distancewb(R_MID_90);//goes to mid x axis
      turn(ent_s*-90);//turns to face the y axis
      touch(5000);
      walk_distancewb(R_MID_120);//goes to mid on the y axis
    }

    else //mid entrance
    {
      walk_distancewb(R_MID_120 - 10.0);//goes to mid in y axis 
    }
  }
}



void New_Room()
{
  
  scan_entrance();// scan the entrance
  
  if (roomF == 120)
  {
    LEDcontrol(0,1,0);
    delay(3000);
    LEDcontrol(0, 0, 0);
    delay(50);
  }
  else 
  {
    LEDcontrol(1, 0, 0);
    delay(3000);
    LEDcontrol(0, 0, 0);
    delay(50);
  }

  if (roomL == 120)
  {
    LEDcontrol(0,1,0);
    delay(3000);
    LEDcontrol(0, 0, 0);
    delay(50);
  }
  else 
  {
    LEDcontrol(1, 0, 0);
    delay(3000);
    LEDcontrol(0, 0, 0);
    delay(50);
  }

  // if(roomF == 120 && roomL == 90 &&  ent_s == -1)while(1);
  bool z = 0;
  if(roomL == 90 && roomF == 90) {
    if(special == 0)go_to_mid();// goes to mid on the 90x90 room

    //rescue the victims 
    scan_turn(360,26.0);
    if(balls == 0)
    {
      turn(3);
    }
    else if(balls == 2)
    {
      turn(-3);
    }
    else
    {
      turn(-7);
    }

    //starts triangle
    t = getmUltra(3, 15);// gets a media of top US
    if (t < 80.0) { // if there´s a wall 
      walk_distance(30.0);//walks until you almost touched id
      turn(180);//turns to align
      touch(2000);// aligns
      walk_distance(5.0);//walks a little just to get out of the wall
    } 
    
    else { //if there´s an exit on the top US the robot scans starting on the left wall
      turn(-90);
      walk_distance(30.0);
      touch(2000);
      walk_distance(5.0);
    }
  
    turn(-90);//turns 90 deegres counterclock wise 
    tri_90();
    media_sp=getmsharp(10);//gets the media of sharp sensor
    Serial.print("SHARP: ");
    Serial.println(media_sp);
    if(media_sp >= 200.0) //if there´s a wall adjusts
    {
      turn(90);//turns to adjust on wall
      touch(2000);//adjusts on wall
      walk_distance(8.0);//walks to get out of the wall
      turn(-90);//turns to stay parallel to the wall    
      
    }
    else //if there's no wall on the right
    {
      turn(-90);//turn 90 
      check_exit();//check to see if that was an exit
      //if that was the entrance
      if(room_clear==0){
        freeze(100);//the robot is now in its initial position
        walk_distance(3.0);//walks to restart the cycle
        turn(-90);//turns 90  
        
        if (side[l] == 0) {//if the robot isn´t in the same side as a triangle 
          walk_distance(R_MID_90-10.0);//walks to adjust on both walls
          turn(90);//turns do adjust on wall
          touch(3000);//adjusts on wall
          walk_distance(3.0);//walks to get out of the wall
          media_sp=getmsharp(5);
          Serial.print("SHARP: ");
          Serial.println(media_sp);
          if(media_sp <= 200){
            walk_distance(7.0);
            turn(-90);
            check_exit();
            room_clear=1;
          }
          
        } 
        else {
          go_to_distnb(30.0);
          turn(45);//turns 45 degrees to stay parallel to the triangle
          walk_distance(30.0);//the triangle
          turn(45);//turns to stay parallel to the wall
          walk_distance(10.0);//walks to restart the cycle
          l = l < 3 ? ++l : l=0;
        }
      
      }
      if (room_clear == 0) { //if the robot didn´t detect exit
        media_sp=getmsharp(10);//gets the media of the sharp sensor
        Serial.print("SHARP: ");
        Serial.println(media_sp);
        if(media_sp <= 230.0)//if there´s an exit
        {
          walk_distance(7.0);//walks a little
          turn(-90);//turns to face the exit
          check_exit();//checs exit
          room_clear=1;
        }
        else//that isn´t the exit so we can adjust on that wall
        {
          turn(90);//turns to make the back of the robot face the wall
          touch(3000);//adjusts on the wall
          walk_distance(7.0);//walks a little
          turn(-90);//turns back
        }
      }  
    }
    //scan for exit
    Serial.println(l);
    for(int i=0;i<=3;i++){
      Serial.println(side[i]);
    } 
    //after the triangle search: array_read();
    // #endif

    //AFTER the triangle search
    //walk and look for wall at both sides to adjust
    // bool z =0;
    //cycle searching for exit
    while(room_clear == 0)
    {
      //gets the side media and looks for an exit. If there's none, keep going and don't consider it (z = 1) 
      walk_distance(5.0);//walks just a little to start the cycle
      media_sp=getmsharp(10);//gets the media of the sharp sensor
      Serial.print("SHARP: ");
      Serial.println(media_sp);
      if (media_sp < 230) {//if that is an "exit"
        
        walk_distance(-2.0);//walks back to check the exit
        turn(-90);//turns to face the "exit"
        //walks with a limit of time to see the exit
        
        check_exit();
        if(room_clear==0){
          turn(-90);//turns 90
          walk_distance(7.0);
        } else {
          break;
        }
      }
      //search exit with bottom sensor. If there's one, checks.
      walk_distance(7.0);//walks a little to get the media of top US

      if(side[l])//if the side of the robot is a triangle  side
      {
        go_to_distnb(30.0);//go to the start of the triangle
        turn(45);//turns 45 degrees to stay parallel to the triangle
        walk_distance(20.0);//the triangle
        turn(45);//turns to stay parallel to the wall
        walk_distance(10.0);//walks to restart the cycle
      }

      else//if there´s an "exit" on the top US
      {
        walk_distance(10.0);//walks a little to see the wall in front of the robot
        media_vt = getmUltra(3,10);//gets the media of top US
        Serial.print("TOP: ");
        Serial.println(media_vt);
        if(media_vt >= 50.0)//if that is an "exit"
        {
          walk_distance(10.0);//walks a little
          walk(0,0);
          tone(BUZZER, 155, 5);//debug
          turn(90);//turns to adjust on the adjacent wall of the exit
          touch(5000);//adjusts the robot
          walk_distance(7.0);//walks just so it can get out of the wall
          turn(-90);//turns to face the "exit"
          check_exit();//checks the exit
          if(room_clear==0){//if that isn´t an exit
            walk_distance(3.0);//walks to restart the cycle
            turn(-90);//turns 90  
            walk_distance(R_MID_90 - 10.0);//go to the next wall
            turn(90);//turns do adjust on wall
            touch(3000);//adjusts on wall
            walk_distance(3.0);//walks to get out of the wall
            turn(-90);//turns to continue to follow the wall
          } else {
            break;
          }
        }

        else //no exit/on the right
        {
          go_to_distnb(7.0);//the robot get close to the guaranted wall
          media_sp=getmsharp(10);//gets the right US media
          Serial.print("SHARP: ");
          Serial.println(media_sp);
          if (media_sp <= 230.0)//confirms that there´s an "exit" on the right side
          {
            turn(-180);//turns back
            touch(3000);// adjust on wall
            walk_distance(7.0);//walks to the exit
            turn(90);//turs to face the exit
            check_exit();//checks the "exit"
            freeze(500);
            if(room_clear==0){
              turn(90);//turns do adjust on wall
              touch(3000);//adjusts on wall
              walk_distance(3.0);//walks to get out of the wall
              turn(-90);//turns to continue to follow the wall
              walk_distance(R_MID_90 - 5.0);//walks to start a new cycle
            } else {
              break;
            }
          }
          else//else there´s no "exit" on the right
          {
            turn(90);//turns to continue the cycle
            touch(5000);
            walk_distance(R_MID_90 - 5.0);//walks to restart the cycle
          }
        }
        freeze(25);
      }
      if(l < 3)l++;
      else l=0;
    }
  }
  else
  { // 120*90
    // #ifndef SAIDA
    if(special == 0)go_to_mid_120();
    tone(BUZZER,440,1000);
    scan_turn(360,25.0);
    if(balls == 0)
    {
      turn(3);
    }
    else if(balls == 2)
    {
      turn(-1);
    }
    else
    {
      turn(-5);
    }
    bool sigma=true;
    while(sigma)
    {
      //media_vr = getmUltra(3, 30);
      media_vt = getmUltra(3, 30);
      Serial.println(media_vt);
      if(media_vt < 37.0)//the robot is facing the 120 room dimension with top us // troca por media_vr junto com o valor
      {
        //indo para de 120 *** 129 no sensor da direita
        //turn(-90);
        walk_distance(R_MID_90-10);
        turn(90);
        //turn(90);
        walk_distance(9.0);
        media_sp = getmsharp(10);
        if(media_sp <= 200.0)//exit on the right
        {
          walk_distance(-14.0);
          turn(90);
          touch(1500);
          walk_distance(7.0);
          turn(-90);
          walk_distance(10.0);
        }
        else//wall on the right
        {
          turn(90);
          touch(1500);
          walk_distance(7.0);
          turn(-90);
          walk_distance(-6.0);
        }
        sigma=false;
        l_120=2;
        break;
      }
      else if(media_vt  >= 37.0 && media_vt <= 70.0)//the robot is facing the 90 room dimension with top us trocar mpor media_vr
      {
        //(indo pra de 90) *** direita acusando sala de 90
        //turn(-90);
        walk_distance(20.0);
        tone(BUZZER,440,1000);
        float aux_1 = 0.0 ,max_1 = 0.1,aux_2 = 0.0,max_2=0.1, aux_3 = 0.0, max_3 = 0.0;
        for(int i = 0; i < 5; i++)
        {
          aux_1 = getUltra(3);
          if (aux_1 != 0.0 && max_1 != -1.0){if (aux_1 > max_1)max_1 = aux_1;}
          else max_1 = -1.0;
        }
        turn(-3);
        for(int i = 0; i < 5; i++)
        {
          aux_2 = getUltra(3);
          if (aux_2 != 0.0 && max_2 != -1.0){if (aux_2 > max_2)max_2 = aux_2;}
          else max_2 = -1.0;
        }
        turn(6);
        for(int i = 0; i < 5; i++)
        {
          aux_3 = getUltra(3);
          if (aux_3 != 0.0 && max_3 != -1.0){if (aux_3 > max_3)max_3 = aux_3;}
          else max_3 = -1.0;
        }
        turn(-3);
        float max_f = 0.0;
        max_f = higher(max_1, max_2, max_3);
        if(max_f <=50.0 ){
          walk_distance(R_MID_90 - 10.0);
          turn(180);
          touch(6000);
          walk_distance(7.0);
          turn(-90);
          l_120=1;
          sigma=false;
          break;
        }
        else{
          walk_distance(-15.0);
        }
      }
      turn(-90);
    }
    //triangle search
    tri_120();
    if(l_120 % 2 == 0) walk_distance(-15.0);
    media_sp=getmsharp(10);//gets the media of sharp sensor
    if(media_sp <= 230)//exit
    {
      turn(-90);
      check_exit();
      turn(-90);
      if(room_clear == 0)//no exit
      {
        if(l_120 % 2 == 0)
        {
          walk_distance(30.0);
          turn(90);
          touch(4000);
          walk_distance(7.0);
          turn(-90);
        }
        else
        {
          walk_distance(2.0);
          if(side[l])//if the side of the robot is a triangle  side
          {
            go_to_distnb(30.0);//go to the start of the triangle
            turn(45);//turns 45 degrees to stay parallel to the triangle
            walk_distance(20.0);//the triangle
            turn(45);//turns to stay parallel to the wall
            walk_distance(15.0);//exit the triangle
            walk_distance(30.0);//go to the starting tile
            l = l < 3 ? ++l : l=0;
          }
          else
          {
            walk_distance(25.0);//walks a little to see the wall in front of the robot
            turn(90);
            touch(3000);
            walk_distance(7.0);
            turn(-90);
            media_vt = getmUltra(3,10);//gets the media of top US
            Serial.print("TOP: ");
            Serial.println(media_vt);
            if(media_vt >= 50.0)//if that is an "exit"
            {
              check_exit();//checks the exit
              if(room_clear==0){//if that isn´t an exit
                turn(-90);//turns 90  
                walk_distance(R_MID_90 - 10.0);//go to the next wall
                l = l < 3 ? ++l : l=0;
                turn(90);//turns do adjust on wall
                touch(3000);//adjusts on wall
                walk_distance(7.0);//walks to get out of the wall
                turn(-90);//turns to continue to follow the wall
                walk_distance(30.0);//go to the starting tile
              } 
            } 
            else
            {
              turn(90);  
              walk_distance(R_MID_90 - 10.0);//go to the next wall
              walk_distance(30.0);//go to the starting tile
              l = l < 3 ? ++l : l=0;
            }
          }
          l_120 ++;
        }
      }
    }

    else 
    {
      if(l_120 % 2 == 0)
      {
        walk_distance(30.0);
      }
    }

    while(room_clear == 0)
    {
      if(l_120 % 2 == 0)//if the robot is on 120 side
      {
        LEDcontrol(0,1,0);
        delay(1000);
        LEDcontrol(0,0,0);
        media_sp = getmsharp(10);//gets the media of sharp sensor
        if(media_sp <= 230)//if there´s an exit on the right
        {
          turn(-90);//turns to face the exit
          check_exit();//check exit
          if(room_clear == 0)
          {
            turn(-90);//turns to stay parallel to the waçç
          }
          else break;//just break out of while
        }

        if(side[l] == 1)//if the robot is on the same side of the triangle
        {
          go_to_distnb(25.0);//go to the start of the triangle
          turn(45);//turns 45 degrees to stay parallel to the triangle
          walk_distance(20.0);//the triangle
          turn(45);//turns to stay parallel to the wall
          walk_distance(10.0);//walks to restart the cycle
        }
        else//if the robot isn´t on the same side of the triangle
        {
          walk_distance(10.0);
          media_vt = getmUltra(3,15);
          if(media_vt >= 50.0)//exit on the front
          {
            walk_distance(10.0);//walks a little
            walk(0,0);
            tone(BUZZER, 155, 5);//debug
            turn(90);//turns to adjust on the adjacent wall of the exit
            touch(5000);//adjusts the robot
            walk_distance(7.0);//walks just so it can get out of the wall
            turn(-90);//turns to face the "exit"
            check_exit();//checks the exitis
            if(room_clear==0){//if that isn´t an exit
              walk_distance(3.0);//walks to restart the cycle
              turn(-90);//turns 90  
              walk_distance(R_MID_90 - 10.0);//go to the next wall
              turn(90);//turns do adjust on wall
              touch(3000);//adjusts on wall
              walk_distance(7.0);//walks to get out of the wall
              turn(-90);//turns to continue to follow the wall
	          }
            else
            {
              break;
            }
          }
          else//no exit on the front
          {
            go_to_distnb(7.0);//the robot get close to the guaranted wall
            media_sp=getmsharp(10);//gets the right US media
            Serial.print("SHARP: ");
            Serial.println(media_sp);
            if (media_sp <= 230.0)//confirms that there´s an "exit" on the right side
            {
              turn(-180);//turns back
              touch(3000);// adjust on wall
              walk_distance(7.0);//walks to the exit
              turn(90);//turs to face the exit
              check_exit();//checks the "exit"
              freeze(500);
              if(room_clear==0){
                turn(90);//turns do adjust on wall
                touch(3000);//adjusts on wall
                walk_distance(7.0);//walks to get out of the wall
                turn(-90);//turns to continue to follow the wall
                walk_distance(R_MID_90 - 10.0);//walks to start a new cycle
              } 
              else
              {
                break;
              }  
            }
            else//else there´s no "exit" on the right
            {
              turn(90);//turns to continue the cycle
              touch(5000);
              walk_distance(R_MID_90 - 5.0);//walks to restart the cycle
            }
          }
        }
      }

      else //the robot is on 90 side
      {
        LEDcontrol(1,1,1);
        delay(1000);
        LEDcontrol(0,0,0);
        media_sp = getmsharp(10);//gets the media of sharp sensor
        if(media_sp <= 230)//if there´s an exit on the right side
        {
          turn(-90);//turns to face the exit
          check_exit();//checks exit     
          if(room_clear == 0)//if no exit
          {
            turn(-90);//turns to stay parallel to the wall
          }       
          else break;//breaks to get out of the loop
        }
        if(side[l] == 1)//triangle
        {
          go_to_distnb(30.0);//go to the start of the triangle
          turn(45);//turns 45 degrees to stay parallel to the triangle
          walk_distance(20.0);//the triangle
          turn(45);//turns to stay parallel to the wall
          walk_distance(10.0);//walks to restart the cycle 
          media_sp = getmsharp(10);//gets the media of sharp sensor
          if(media_sp >= 230)//wall on the right
          {
            turn(90);//turns 
            touch(3000);//adjusts on wall
            walk_distance(7.0);//walks to get out of the wall
            turn(-90);//turns to stay parallel to the wall
            walk_distance(30.0);//walks to next tile
          }
          else //exit on the right
          {
            turn(-90);//turns to face the exit
            check_exit();//checks exit
            if(room_clear == 0)//if that was an entrance
            {
              walk_distance(2.0);//walks a little
              turn(-90.0);//turns to stay parallel to the wall
              walk_distance(20.0);//walks to next tile
              turn(90);//turns to adjust on the wall
              touch(3000);//adjusts on wall
              walk_distance(7.0);//get out of the wall
              turn(-90);//turns to stay parallel to the wall
            }
            else break;
          }
        }
        else // no triangle
        {
          walk_distance(10.0);
          media_vt = getmUltra(3,15);
          if(media_vt >= 50.0)//front exit
          {
            walk_distance(20.0);//walks to face the exit
            turn(90);//turns to adjust on wall
            touch(3000);//adjusts on wall
            walk_distance(7.0);//gets out of the wall
            turn(-90);//turns to stay parallel to the wall
            check_exit();//checks exit
            if(room_clear == 0)//if that was an entrance
            {
              walk_distance(2.0); //walks a little
              turn(-90); //turns
              walk_distance(20.0); //walks to the next tile
              turn(90); //turns
              touch(3000); //touches the wall
              walk_distance(7.0); //walks to get off the wall
              turn(-90); //turns to stay parallel to the wall
              walk_distance(30.0); //walks to the next tile
            }
          }
          else //there's no front exit
          {
            go_to_distnb(7.0); //gets close to the wall
            media_sp = getmsharp(10); //gets the sharp value
            if(media_sp >= 230) //if there's no exit
            {
              turn(90); //turns
              touch(3000); //touches the wall
              walk_distance(7.0); //get off the wall
              walk_distance(R_MID_90 - 5.0); //walks to the next tile
              media_sp = getmsharp(10); //gets the sharp value

              if(media_sp >= 230) //if there's no exit
              {
                turn(90); //turns
                touch(3000); //touches the wall
                walk_distance(7.0); //walks to get off the wall
                turn(-90); //turns
                walk_distance(30.0); //walks to the next tile
              }

              else //there's an exit
              {
                turn(-90); //turns to face the exit
                check_exit(); //checks the exit
                if(room_clear == 0) //if that was an entrance
                {
                  turn(-90); //turns
                  walk_distance(30.0); //walks to the next tile
                  turn(90); //turns
                  touch(3000); //touches the wall
                  walk_distance(7.0); //walks to get off the wall
                  turn(-90); //turns
                }
                else //ther's an exit 
                {
                  break;
                }
              }
            }
            else //there's an exit on the side
            {
              turn(180); //turns to face the exit
              touch(3000); //touches the wall
              walk_distance(7.0); //walks to get off the wall
              turn(90); //turns
              check_exit(); //checks the exit
              if (room_clear == 0) //if there's no exit
              {
                walk_distance(30.0); //goes to the next tile
                media_sp = getmsharp(10); //gets the sharp value
                if (media_sp <= 230) //if there's an exit
                {
                  //as it just got an entrance, this is definitely an exit
                  turn(-90); //faces the exit
                  walk_distance(10.0); //walks to the exit
                  room_clear = 1; //end of room3
                  break; //break
                }
                else 
                {
                  turn(90); //turns
                  touch(3000); //touches the wall
                  walk_distance(7.0); //gets off the wall
                  turn(-90); //turns
                  walk_distance(30.0); //goes to the next tile
                }
              }
            }
          }
        }
      }
      l_120++; //goes to the next side, not a 120
      l = l < 3 ? ++l : l=0;
    }

    tone(BUZZER, 155, 10000);
  }
}

  /*walk_distance(3.0);
  array_read();
  if(NOSIB()==0){
    turn(30);
    walk_distance(5.0);
    turn(-30);
    array_read();
    if(NOSIB()==0){
      turn(30);
      walk_distance(-5.0);
      turn(-30);
      turn(-30);
      walk_distance(5.0);
      turn(30);
    }
  }*/


void check_exit()
{
  int cont_bl = 0;//counter for black line
  float walking_back = 0.0;
  unsigned long timer = millis();//gets a timer
  while(cont_bl < 5 && (millis() - timer <= 2000))//while the black line counter is lower than five and the robot is scanning for less than 3 seconds
  {
    walk(SWL,SWR);//walks
    array_read();//reads the array
    if(NOSIB() >= 3) cont_bl++;//if the robot is in a black line 
    else cont_bl = 0; //resets the black line counter
  } 
  
  walking_back = (float)(millis() - timer);
  if(cont_bl > 3) {     //if the robot has seen the black line 4 times
    tone(BUZZER, 440, 1000);
    room_clear = 1;
    //fazer o robo sair na linha talvez
  }
  else 
  {
    turn(180);
    walk(SWL, SWR);
    delay(walking_back);
    freeze(25);
  }
  walk(0,0);
  freeze(25);
}

void go_to_distnb (float final_d)// Function used to make the robot go to a distance
{
  int n_top = 0;
  do
  {
    walk(SWL,SWR);
    get_vbt();//Read top and bot ultrassonics
    //    Serial.print("nbot: ");
    //    Serial.print(n_bot);
    //    Serial.print(" n_top: ");
    //    Serial.println(n_top);
    Serial.println(vt);
    if(vt < final_d && vt  != 0) n_top++;//if the top us value is lower than the distance wanted adds to the top counter
    else n_top = 0; // else resets the top count    
    delay(25);//default delay for reading values
  } while(n_top < 2);//do the above while the top counter is lower than 2
  freeze(100);//stop for 100 millisecons  
  Sinalize(1,3,1,3,20);
}

void tri_90()
{
  while(triangles < 2) { // search for triangles until you have deposited the victms
    walk_distance(2.0);
    walk_distance(7.0);//walks until it gets close to the triangle

    turn(45);//turns to stay parallel to the triangle 
    walk_distance(15.0);//walks and scan the edge for a triangle
    int isTri = 0;

    for (int i = 0; i < 10; i++) {
      isTri += analogRead(0);
    }
    isTri = (int)(isTri/10);
    // Serial.println(isTri);
    //media of 10 values of the sharp sensor

    if (isTri > 350) {//if it is a triangle
      side[l]=true;
      
      turn(-90);//turns to face the triangle
      walk_distance(10.0);//walks to touch the triangle

      if(tc != 0) //if we know the color of one triangle
      {
        if (tc == 1) //if the  other triangle is green, this is red
        {
          deposit(0);
        }
        else //if the  other triangle is red, this is green
        { 
          deposit(1);
        }   
      }
      else {
        tc = detectTri(); //detects the color of the triangle |1 = green| / |2 =  red|
        if (tc == 1) {// if the triangle is green
          LEDcontrol(0, 1, 0);//green led
          delay(1000);
          LEDcontrol(0, 0, 0);
          deposit(1);//deposit the alives victims
        } else {//if the triangle is red
          LEDcontrol(1, 0, 0);//red led
          delay(1000);
          LEDcontrol(0, 0, 0);
          deposit(0);//deposit the dead victims
        }
      }

      triangles++;// it already detected a triangle
      walk_distance(10.0); //walk
      turn(45); //turn
      walk_distance(10.0);
    } 
    
    else 
    {// if there´s not a triangle
      walk_distance(10.0);
      turn(45);//turns to continue the scan
      delay(5);
      walk_distance(10.0);
    }
    t = getmUltra(3,15); //last media
    if(l >= 3)l = 0;
    else l++;
  } 
}

void tri_120() {
 while(triangles < 2) { // search for triangles until you have deposited the victms
    if(l_120 % 2 == 1){ //parede 90
      LEDcontrol(1,1,1);
      walk_distance(2.0);
      walk_distance(7.0);//walks until it gets close to the triangle
      LEDcontrol(0,0,0);
    }
    else{ // parede 120
      LEDcontrol(0,1,0);
      walk_distance(2.0);
      walk_distance(30.0);//walks until it gets close to the triangle
      LEDcontrol(0,0,0);

    }

    turn(50);//turns to stay parallel to the triangle 
    walk_distance(12.0);//walks and scan the edge for a triangle
    int isTri = 0;

    for (int i = 0; i < 10; i++) {  
      isTri += analogRead(0);
    }
    isTri = (int)(isTri/10);
    // Serial.println(isTri);
    //media of 10 values of the sharp sensor

    if (isTri > 370 && !side[l]) {//if it is a triangle
 
      side[l]=true;
      
      turn(-90);//turns to face the triangle
      walk_distance(10.0);//walks to touch the triangle

      if(tc != 0) //if we know the color of one triangle
      {
        if (tc == 1) //if the  other triangle is green, this is red
        {
          deposit(0);
        }
        else //if the  other triangle is red, this is green
        {
          deposit(1);
        }   
      }
      else {
        tc = detectTri(); //detects the color of the triangle |1 = green| / |2 =  red|
        if (tc == 1) {// if the triangle is green
          LEDcontrol(0, 1, 0);//green led
          delay(1000);
          LEDcontrol(0, 0, 0);
          deposit(1);//deposit the alives victims
        } else {//if the triangle is red
          LEDcontrol(1, 0, 0);//red led
          delay(1000);
          LEDcontrol(0, 0, 0);
          deposit(0);//deposit the dead victims
        }
      }

      triangles++;// it already detected a triangle
      walk_distance(15.0); //walk
      turn(50); //turn
      freeze(25);
      walk_distance(11.0);
    } 
    
    else 
    {// if there´s not a triangle
      walk_distance(11.0);
      turn(45);//turns to continue the scan
      freeze(25);
      if(l_120%2==0)walk_distance(17.0);
      else walk_distance(16.0);
    }
    t = getmUltra(3,15); //last media
    if(l >= 3)l = 0;
    else l++;
    l_120++;
    freeze(10);
    media_sp=getmsharp(10);
    if(media_sp>=230 && triangles < 2){
      turn(90);
      touch(3000);
      walk_distance(9.0);
      turn(-90);
    } 
  }
}

void walk_distancewb(float d)
{
	int vitima = 0;
  int sign = abs(d) / d; //if sign is negative makes the robot walk back
  unsigned long start_wdb = millis();
	unsigned long tempo_i = 0;
	while ( millis() - start_wdb < 125*abs(d) + tempo_i )
	{
		walk(SWR*sign,SWL*sign);
		get_vbt();
		if(vb <= 5.0 && vb != 0.0)vitima++;
		else vitima = 0;
		if (vitima > 1)
		{	
      delay(50);
			unsigned long d_interno = millis();
      freeze(50);   
			SwallowBalls();
			d_interno = millis() - d_interno;
			tempo_i += d_interno;
			vitima = 0;
		}
	}
	
 	freeze(100);
}

void front_scan()
{
  walk_distancewb(40.0);
  freeze(100);
  float auxt = 0.0;
  for(int i = 0; i < 15; i++)
  {
    auxt = getUltra(3);
    if (auxt != 0.0 && max_top != -1.0){if (auxt > max_top)max_top = auxt;}  
    else max_top = -1.0;
    delay(10);
  }
  max_top += 40.0;
  walk_distance(-40.0);
}

void front_scan_2()
{
  walk_distancewb(30.0);
  freeze(100);
  float auxlat = 0.0;
  turn(-3*ent_s);
  for(int i = 0; i < 15; i++)
  {
    auxlat = getUltra(3);
    if (auxlat != 0.0 && maxlat != -1.0){if (auxlat > maxlat)maxlat = auxlat;}  
    else maxlat = -1.0;
    delay(10);
  }
  maxlat += 30.0;
  turn(3*ent_s);
  Serial.println(maxlat);
  delay(3000);
  walk_distance(-30.0);
}


void go_to_dist (float final_d)// Function used to make the robot go to a distance
{
  int n_top = 0,n_bot = 0;
  do
  {
    walk(SWL,SWR);
    get_vbt();//Read top and bot ultrassonics
    //    Serial.print("nbot: ");
    //    Serial.print(n_bot);
    //    Serial.print(" n_top: ");
    //    Serial.println(n_top);
    Serial.println(vt);
    if(vt < final_d && vt  != 0) n_top++;//if the top us value is lower than the distance wanted adds to the top counter
    else n_top = 0; // else resets the top count
    
    if(vb < 6.0 && vb > 0) n_bot++;//if the bot value is lower than 8.0cm adds to the bot counter
    else n_bot = 0;// else resets the top count
    
    if(n_bot >= 2) // if the bot counter gets higher or equals 2 it is a victim
    {
      freeze(500);//makes the robot stop for 500 milliseconds
      SwallowBalls();
    }
    
    delay(25);//default delay for reading values
  } while(n_top < 2);//do the above while the top counter is lower than 2
  freeze(100);//stop for 100 millisecons  
  Sinalize(1,3,1,3,20);
}

void go_to_angle(int f_angle)//function used to make the robot go to an specific angle starting on its current angle
{
  int delta_angle = f_angle - c_angle;//get angle variation (delta_angle)
  
  if(delta_angle < -180)//if angle variation if lower than -180
  { 
    walk(-SWL, SWR);
    Simple_turn(delta_angle + 360);//adds 360 to the angle
    freeze(50);
  }

  else if(delta_angle > 180)//if angle variation if higher than 180
  {
    walk(SWL, -SWR);
    Simple_turn(360 - delta_angle);//subtracts 360 to the angle
  }

  else turn(delta_angle);//just turn the angle variation
  
  c_angle = f_angle;//updates final angle
  freeze(25);
}


void update_angle(int ang)
{
  c_angle+=ang;
  if(c_angle < 0)//if angle is negative 
  {
    c_angle += 360;//adds 360 
  }
  else if(c_angle > 360)//else if angle is higher than 360
  {
    c_angle -= 360;//subtracts 360
  }
}

void scan_turn(int alfa, float dist_to_ball) 
{
  //sensor addres and value of Z axis of gyroscope
  int16_t GyZ=0;

  float total_alfa = 0.0, dimensional_error = 1.0357; //error calculated by the difference in degree 

  //timer variables
  unsigned long previoustimer = millis();
  float elapsedtime;
  int cont_b = 0; //ball counter

  //while it didn't walk to the said angle "alfa"
  if (alfa < 0)walk(SWL, -SWR);
  if (alfa > 0)walk(-SWL, SWR);
  
  while(abs(total_alfa) <= abs(alfa))
  {
    //the elapsed time
    elapsedtime = (float)(millis() - previoustimer) / 1000.0; //as the scale is degrees/seconds, we divided the time in millis by 1000
    previoustimer = millis(); 
    //transmission on wire library
    Wire.beginTransmission(0x68);
    Wire.write(0x47); //0x47 (GYRO_ZOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 2, true); //each axis value is stored in 2 registers
    total_alfa += (float)GyZ * dimensional_error * elapsedtime / 131.0; //scale in degrees/seconds. For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
    //put the value received on the variable
    GyZ = (Wire.read()<<8|Wire.read()); //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
    GyZ -=  GYZ_ERROR; //small correction

    vb = getUltra(4); // Read the bottom US

    // Serial.print("bottom distance: ");
    // Serial.println(vb);
    
    if ( vb < dist_to_ball && vb > 0.0) cont_b++;//if the bot us value is lower than 25.0cm adds to the ball counter
    else cont_b = 0;//else it resets the ball counter

    // Serial.print("count: ");
    // Serial.println(cont_b);

    if( cont_b >= 12 ) //if the ball counter gets higher or equal 2 it is a victim
    {
      float b_dist = vb; //go to balls
      freeze(100);//stop for 100 millisecons  
      LEDcontrol(0,0,1);//uses array LED for debug
      Serial.println("VB:");
      Serial.println(vb);
      if(b_dist <= 4.0)
      {
        SwallowBalls();
      }
      else if(b_dist <= 7.0 && b_dist >= 4.0)//first detection radius
      {
        LEDcontrol(0,0,1);
        delay(500);
        LEDcontrol(0,0,0);
        turn(1);
        freeze(100);
        total_alfa += 1.0*total_alfa/abs(total_alfa);
        walk_distance(b_dist*0.95 - 1.0);
        freeze(500);
        SwallowBalls();//catches the victim
        freeze(10);
        walk_distance(-(b_dist*0.95 - 1.0));
        LEDcontrol(0,0,0);//turns off LED
      }
      else if(b_dist >= 7.0 && b_dist <= 14.0)
      {
        LEDcontrol(0,1,0);
        delay(500);
        LEDcontrol(0,0,0);
        turn(3);
        freeze(100);
        total_alfa += 3.0*total_alfa/abs(total_alfa);
        walk_distance(b_dist*0.95 - 3.0);
        freeze(500);
        SwallowBalls();//catches the victim
        freeze(10);
        walk_distance(-(b_dist*0.95 - 3.0));
        LEDcontrol(0,0,0);//turns off LED
      }
      else if(b_dist >= 14.0 && b_dist <= 21.0)
      {
        
        LEDcontrol(1,0,0);
        delay(500);
        LEDcontrol(0,0,0);
        turn(5);
        freeze(100);
        total_alfa += 5.0*total_alfa/abs(total_alfa);
        walk_distance(b_dist*0.95 - 3.0);
        freeze(500);
        SwallowBalls();//catches the victim
        freeze(10);
        walk_distance(-(b_dist*0.95 - 3.0));
        LEDcontrol(0,0,0);//turns off LED
      }
      else
      {
        LEDcontrol(1,1,1);
        delay(500);
        LEDcontrol(0,0,0);
        turn(8);
        freeze(100);
        total_alfa += 8.0*total_alfa/abs(total_alfa);
        walk_distance(b_dist*0.95 - 4.0);
        freeze(500);
        SwallowBalls();//catches the victim
        freeze(10);
        walk_distance(-(b_dist*0.95 - 4.0));
        LEDcontrol(0,0,0);//turns off LED
      }

      // precaution=1;
      freeze(10);
      previoustimer = millis();
      cont_b=0;
    }
    
    if (alfa < 0)walk(SWL, -SWR);
    if (alfa > 0)walk(-SWL, SWR);
    delayMicroseconds(800);   
  }

  //stops
  freeze(25);
  update_angle(alfa);
}

void Nroom()
{
  delay(100);
  c_angle = 90;
  Serial.println(c_angle);
  scan_entrance();
  go_to_mid();
  freeze(500);
  scan_turn(360,26.0);


  go_to_angle(90);
  c_angle = 90;
  touch(10000);
  walk_distance(R_MID_90);

  
  go_to_angle(45);
  scan_edge();
  go_to_angle(130);
  c_angle = 135;
  scan_edge();
  go_to_angle(225);
  c_angle = 225;
  if(triangles <= 1 && entrance_angle != 225)scan_edge();
  go_to_angle(310);
  c_angle = 315;
  if(triangles <= 1 && entrance_angle != 315)scan_edge();
  go_to_angle(90);
  c_angle = 90;
  
  if(balls == 0)
  {
    Sinalize(0,0,1,5,20);
  }
  else
  {
    if (avs > 0){
      deposit(1);
    }
    if (dvs > 0){
      deposit(0);
    }
  }
  
  if(exit_angle == 1023)
  {
    Sinalize(1,5,0,0,20);
    scan_exit();
    go_to_exit();
    if(room_clear == 0)confirm_exit();
  }
  else {
    go_to_exit();
    confirm_exit();
  }

}


void Troom()
{
  delay(100);
  c_angle = 90;
  Serial.println(c_angle);
  scan_entrance();
  go_to_mid();
  freeze(1000);



  scan_turn(90,26.0);
  c_angle = 90;
  go_to_angle(45);
  c_angle = 45;
  scan_edge();
  freeze(100);
  

  scan_turn(25,26.0);
  scan_turn(30,26.0);
  scan_turn(60,26.0);
  scan_turn(15,26.0);
  go_to_angle(135);
  c_angle = 135;
  scan_edge();
  freeze(100);
  
  scan_turn(25,26.0);
  scan_turn(30,26.0);
  scan_turn(60,26.0);
  scan_turn(15,26.0);
  go_to_angle(225);
  c_angle = 225;
  if(triangles <= 1 && entrance_angle != 225)scan_edge();
  freeze(100);
   

  scan_turn(25,26.0);
  scan_turn(30,26.0);
  scan_turn(60,26.0);
  scan_turn(15,26.0);
  go_to_angle(300);
  c_angle = 315;
  if(triangles <= 1 && entrance_angle != 315)scan_edge();
  
  go_to_angle(90);
  c_angle = 90;
  
  if(balls == 0)
  {
    Sinalize(0,0,1,5,20);
  }
  else
  {
    if (avs > 0){
      deposit(1);
    }
    if (dvs > 0){
      deposit(0);
    }
  }
  
  if(exit_angle == 1023)
  {
    Sinalize(1,5,0,0,20);
    scan_exit();
    go_to_exit();
    if(room_clear == 0)confirm_exit();
  }
  else {
    go_to_exit();
    confirm_exit();
  }
}



void deposit(bool a)  { //rescue "a" (alive) or dead victims
  int prevc_angle = c_angle; //save the previous angle

  //if the victim is alive
  if (a==1) {
    //go to the green triangle
    
    //turns to  and touches the triangle
    walk(-SWL, -SWR);
    delay(500);
    turn(180);
    touch(5000);

    //deposit the ball
    set_servo(3, DEPR);
    back_forth(15,100);
    delay(300);
    Servo_ipos();

    walk_distance(10.0);
    turn(-90);
    avs=0;
  } 
  
  else {
    //turns and touches the triangle
    walk(-SWL, -SWR);
    delay(500);
    turn(180);
    touch(5000);

    //deposit the ball
    set_servo(3, DEPL);
    back_forth(15,100);
    delay(1500);
    Servo_ipos();//gets the media of the bot us
    
    walk_distance(10.0);
    turn(-90);
  }
}



void scan_edge()//function used to scan edges
{
  media_vb = getmUltra(4,20);
  Serial.println("MEDIA_VB:");
  Serial.println(media_vb);
  if(media_vb <=40.0 && media_vb > 0.0)//triangle condition
  {
    Sinalize(1,10,1,10,10);

    go_to_tri();//go to the triangle
    tri = 1;

    if (tri_green == 0 && tri_red == 0) {
    
      if (tri != 0) {
        triangles++;
        int tc = detectTri(); //detects the color of the triangle |1 = green| / |2 =  red|
        if (tc == 1) //if the triangle is green
        {
          LEDcontrol(0,1,0);
          delay(300);
          LEDcontrol(0,0,0);
          tri_green = c_angle; //the angle of the green triangle is the current angle of the robot
          if(avs > 0)//if the robot has an alive victim in the separator
          {
            turn(180);
            update_angle(180);
            touch(1000);
            set_servo(3,DEPR);
            back_forth(15,100);
            freeze(500);
            walk_distance(vb*0.92);
            go_to_angle(tri_green);
            avs = 0;
            //deposit and return to the previous angle
          }
          else walk_distance(-vb*0.92);//else the robot goes back to its initial position
        } 
        else if (tc == 2)//else if the triangle is red
        {
          LEDcontrol(1,0,0);
          delay(300);
          LEDcontrol(0,0,0);
          tri_red = c_angle; //the angle of the green triangle is the current angle of the robot
          if(dvs > 0)
          {
            turn(180);
            update_angle(180);
            touch(1000);
            set_servo(3,DEPL);
            back_forth(15,100);
            freeze(500);
            walk_distance(vb*0.92);
            go_to_angle(tri_red);
            dvs = 0;
          }
          else walk_distance(-vb*0.92);
        }

        else walk_distance(-vb*0.92);
      }
      else walk_distance(-vb*0.92);

      Servo_ipos();
    
      freeze(50);//stops for 250 milliseconds

      //walks back to the centre
    } 
    
    else {
      tri = 1;
      if (tri != 0) {
        if (tri_green != 0)tri_red = c_angle;
        else tri_green = c_angle;
        triangles++;

        walk_distance(-vb*0.95);
      } 
      
      else walk_distance(-vb*0.92);      
    }

    // delay(1000);
    // Serial.println("c_angle :");
    // Serial.println(c_angle);
    // delay(1000);
    // Serial.println("tri_green :");
    // Serial.println(tri_green);
    // delay(1000);
    // Serial.println("tri_green :");
    // Serial.println(tri_green);
   
    
  } 
  
  /*else if (media_vb > 0.0 && media_vb < 26.0) {
    turn(10);
    update_angle(10);
    walk_distance(media_vb*0.95- 3.0);
    SwallowBalls();
    walk_distance(-(media_vb*0.9 - 3.0));
  }*/
  
  else LEDcontrol(1,1,1);//no triangle edge uses LEDs for debug
}


void go_to_tri()
{
  float med;
  get_vbt();
  med = vb;
  walk_distance(vb*0.95);
}


//uses the color sensor for rescue. 1 for green, 2 for red and 0 is wall
int detectTri() {
  LEDRescue(0, 0, 0);

  int green=0, red=0;
  
  //sets the initial value of red green and blue as values impossible to be obtained as a read
  int minr = 10000;
  int ming = 10000;
  int minb = 10000;
  int maxr = 1;
  int maxg = 1;
  int maxb = 1;

  //read 100 times
  for (int i = 0; i < 100; i++) {
    readLEDRescue(); 

    //the lowest and the highest values are kept
    if(minr > red_rescue && red_rescue>0)minr=red_rescue;
    if(ming > green_rescue && green_rescue>0)ming=green_rescue;
    if(minb > blue_rescue && blue_rescue>0)minb=blue_rescue;
    if(maxr < red_rescue)maxr=red_rescue;
    if(maxg < green_rescue)maxg=green_rescue;
    if(maxb < blue_rescue)maxb=blue_rescue;

    //if red is the lowest value it's red
    if (red_rescue < green_rescue && red_rescue < blue_rescue && red_rescue < 900) {
      red++;
    }
    //if the maximum and minimum value are really close to each other it's green
    else {
      green++;
    }
  }
  cont_tri=0;
  //if there are more green than red 
  if (green > red)return 1;
  else if (red>green) return 2;
  else return 0;
}

// Function to print all variables of variaton of ultrassonic values
void print_all ()
{
  get_vbt();
  
  prev_vb = vb;
  prev_vt = vt;
  
  get_vbt();
  
  delta_vb = prev_vb - vb; 
  delta_vt = prev_vt - vt;
  
  Serial.print("vb: ");
  Serial.print(vb);
  Serial.print(" prev_vb: ");
  Serial.print(prev_vb);
  
  Serial.print(" vt: ");
  Serial.print(vt);
  Serial.print(" prev_vt: ");
  Serial.print(prev_vt);
  
  Serial.print(" delta_vb: ");
  Serial.print(delta_vb);
  Serial.print(" delta_vt:");
  Serial.print(delta_vt);
  
  Serial.print(" delta_mbt: ");
  Serial.println(delta_mbt);
  
  delay(750);
}



void print_vbt()
{
  get_vbt();
  
  prev_vb = vb;
  prev_vt = vt;
  
  get_vbt();
  
  delta_vb = prev_vb - vb; 
  delta_vt = prev_vt - vt;
  
  Serial.print("vb: ");
  Serial.print(vb);
  Serial.print(" prev_vb: ");
  Serial.print(prev_vb);
  Serial.print(" delta_vb: ");
  Serial.print(delta_vb);
  
  Serial.print(" vt: ");
  Serial.print(vt);
  Serial.print(" prev_vt: ");
  Serial.print(prev_vt);
  Serial.print(" delta_vt:");
  Serial.println(delta_vt);
  
  delay(500);
}



void get_vbt()//function used to get bot and top us
{
  vb = getUltra(4);
  vt = getUltra(3);
}



void scan_exit()
{

  //reads the distance of the ultrasonic sensors
  delay(15);
  media_vl = getmUltra(1,10);
  delay(100);
  media_vr = getmUltra(2,10);
  delay(100);
  media_vt = getmUltra(3,10); 
  delay(100);
  Serial.println("media_vl");
  Serial.println(media_vl);
  delay(100);
  Serial.println("media_vr");
  Serial.println(media_vr);
  delay(100);
  Serial.println("media_vt");
  Serial.println(media_vt);
  
  //if the media is too high it detects exit
  if (media_vr > 150.0)
  {
    exit_angle = 0;
    Sinalize(0,0,1,3,30);
  }
  else if(media_vl > 150.0)
  {
    exit_angle = 180;
    Sinalize(1,3,1,3,30);
  }
  else if(media_vt > 150.0)
  {
    exit_angle = 90;
    Sinalize(1,3,0,0,30);
  }
  else { 
    //45 and 135
    if( (tri_green == 45 && tri_red == 135) || (tri_green == 135 && tri_red == 45) )//if the two triangles are in 45 and 135 deegres
    {
      if(ent_m == 0)//if the entrance is in the corners
      {
        if(ent_s == -1)exit_angle = 315;//if the entrance is in the left corner the exit_angle is 315 deegres
        else exit_angle = 225; //if the entrance is in the right corner the exit_angle is 225 deegres
      }
      else //mid entrance
      {
        walk_distance(-R_MID_90);
        turn(90);
        media_vt == getmUltra(3,10);
        //*********
        if(media_vt >= 100.0)
        {
          do
          {
            array_read();
            walk(SWL,SWR);
          }
          while(NOSIB() >= 2);
          walk(0, 0);
          room_clear = 1;
        }
        else
        {
          turn(-180);
          do
          {
            array_read();
            walk(SWL,SWR);
          }
          while(NOSIB() >= 2);
          walk(0, 0);
          room_clear = 1;
        }
    }
   }
    //45 and 225 && 45 and 315 and entrance from corner
    else if( ent_m == 0 && ( (tri_green == 45 && tri_red == 225) || (tri_green == 225 && tri_red == 45) || (tri_green == 45 && tri_red == 315) || (tri_green == 315 && tri_red == 45) ) )
    {
      exit_angle = 135; 
    }
    
    //45 and 225 mid variation
    else if( ent_m == 1 && (tri_green == 45 && tri_red == 225) || (tri_green == 225 && tri_red == 45) )//*********
    {
      walk_distance(-R_MID_90);
      turn(-90);
      media_vt = getmUltra(3,10);
      if(media_vt >= 100.0)
      {
        do
        {
          array_read();
          walk(SWL,SWR);
        }
        while(NOSIB() >= 2);
        walk(0, 0);
        room_clear = 1;
      }
      else
      {
        turn(90);
        walk_distance(R_MID_90);
        exit_angle = 135;
      }
    }
    
    //45 and 315 mid variation
    else if( ent_m == 1 && (tri_green == 45 && tri_red == 315) || (tri_green == 315 && tri_red == 45) )//*********
    {
      walk_distance(-R_MID_90);
      turn(90);
      media_vt = getmUltra(3,10);
      if(media_vt >= 100.0)
      {
        do
        {
          array_read();
          walk(SWL,SWR);
        }
        while(NOSIB() >= 2);
        walk(0, 0);
        room_clear = 1;
      }
      else
      {
        turn(-90);
        walk_distance(R_MID_90);
        exit_angle = 135;
      }
    }

    //135 and 225 
    else if( ent_m == 0 && (tri_green == 135 && tri_red == 225) || (tri_green == 225 && tri_red == 135) )exit_angle = 45;
    //135 and 225 mid variation
    else if(ent_m == 1 && (tri_green == 135 && tri_red == 225) || (tri_green == 225 && tri_red == 135) )//*********
    {
      walk_distance(-R_MID_90);
      turn(90);
      media_vt = getmUltra(3,10);
      if(media_vt >= 100.0)
      {
        do
        {
          array_read();
          walk(SWL,SWR);
        }
        while(NOSIB() >= 2);
        walk(0, 0);
        room_clear = 1;
      }
      else
      {
        turn(90);
        walk_distance(R_MID_90);
        exit_angle = 45;
      }
    }
    //135 and 315
    else if( ent_m == 0 && (tri_green == 135 && tri_red == 315) || (tri_green == 315 && tri_red == 135) ) exit_angle = 45;
    //135 and 315 mid variation
    else if( ent_m == 1 && (tri_green == 135 && tri_red == 315) || (tri_green == 315 && tri_red == 135) ) //**********
    {
      walk_distance(-R_MID_90);
      turn(90);
      media_vt = getmUltra(3,10);
      if(media_vt >= 100.0)
      {
        do
        {
          array_read();
          walk(SWL,SWR);
        }
        while(NOSIB() >= 2);
        walk(0, 0);
        room_clear = 1;
      }
      else
      {
        turn(-90);
        walk_distance(R_MID_90);
        exit_angle = 45;
      }
    }
    //225 and 315
    else
    {
      walk_distance(R_MID_90);
      turn(90);
      media_vt = getmUltra(3,10);
      if(media_vt >= 100.0)
      {
        do
        {
          array_read();
          walk(SWL,SWR);
        }
        while(NOSIB() >= 2);
        walk(0, 0);
        room_clear = 1;
      }
      else 
      {
        turn(-180);
        do
        {
          array_read();
          walk(SWL,SWR);
        }
        while(NOSIB() >= 2);
        walk(0, 0);
        room_clear = 1;
      }
    }
  }
}


void confirm_exit()
{

  if(exit_angle == 45 || exit_angle == 225)
  {
    if(exit_angle == 45) go_to_angle(90);
    else go_to_angle(270);
    media_vt = getmUltra(3,10); // Top US
    delay(25);
    if(media_vt <= 20.0)
    {
      turn(-90);

      freeze(10);
      walk_distance(5.0);
      do
      {
        array_read();
        walk(SWL,SWR);
      }while(NOSIB() < 2);
      freeze(100);
      walk(0, 0);
    }
    else
    {
      freeze(10);
      walk_distance(5.0);
      do
      { 
        array_read();
        walk(SWL,SWR);
      }while(NOSIB() < 2);
      walk(0, 0);
    }
  }
  else
  {
    if(exit_angle == 135)go_to_angle(90);
    else go_to_angle(270);
    media_vt = getmUltra(3,10);
    delay(25);
    if(media_vt <= 20.0)
    {
      turn(90);
      
      freeze(10);
      walk_distance(10.0);
      do
      {
        array_read();
        walk(SWL,SWR);
      }while(NOSIB() < 2);
      walk(0, 0);
    }
    else
    {
      freeze(10);
      walk_distance(10.0);
      do
      {
        array_read();
        walk(SWL,SWR);
      }while(NOSIB() < 2);
      walk(0, 0);
    }
  }
}


void scan_entrance() //function used to scan entrance
{  


  media_vl = getmUltra(1,15);//get the media for top us
  delay(25);//default delay for getting information

  //previous code
  // media_vr = getmUltra(2,15);//get the media for right us
  // delay(25);//default delay for getting information
  // media_vt = getmUltra(3,15);//get the media for left us
  // delay(25);//default delay for getting information

  media_sp = getmsharp(10);

  float mL=0.1, mT=0.1, mR=0.1; //minimum values


  // if(media_vl < 28.0)//if the robot is closer to the left wall
  // {
  //   ent_s = -1;//used for turns, when the entrance is in left ent_s = -1 
  //   Sinalize(1,5,0,0,20);
  // } 
  

  // else if(media_vr < 28.0)//if the robot is closer to the right wall
  // {
  //   ent_s = 1;//used for turns, when the entrance is in right ent_s = 1 
  //   Sinalize(0,0,1,5,20);
  // }
  // else //mid entrance
  // {
  //   ent_s=1;
  //   ent_m=1;
  //   Sinalize(1,5,1,5,20);
  // }

  if (media_sp > 300)
  {
    ent_s = 1;//used for turns, when the entrance is in right ent_s = 1 
    Sinalize(0,0,1,5,20);
  }

  else
  {
    turn(185);
    media_sp=getmsharp(10);
    if (media_sp > 350)
    {
      ent_s = -1;//used for turns, when the entrance is in left ent_s = -1 
      Sinalize(1,5,0,0,20);
      turn(180);
    }
    else //mid entrance
    {
      ent_s=1;
      ent_m=1;
      turn(185);
      //Sinalize(1,5,1,5,20);
    }
  }

  
  //scan fot possible victims:
  if(ent_m == 0)
  {
    turn(ent_s*90);
    touch(8000);
    walk_distance(15.0);
    turn(ent_s*-90);
    media_vb = getmUltra(4,15);
    Serial.println("M inicial");
    Serial.println(media_vb);
    if(media_vb < 40.0)
    {
      walk_distancewb(media_vb - 1.0);
      SwallowBalls();
      walk_distance(-media_vb + 1.0);
    }
    // if(ent_s == 1)//right
    // {
    //   media_vl = getmUltra(1,15);
    //   if(media_vl <= 40.0)
    //   {
    //     turn(90);
    //     walk_distancewb(media_vl);
    //     SwallowBalls();
    //     walk_distance(-media_vl);
    //     turn(-90);
    //   }
    // }
    // else//left
    // {
    //   media_vr = getmUltra(1,15);
    //   if(media_vr <= 40.0)
    //   {
    //     turn(-90);
    //     walk_distancewb(media_vr);
    //     SwallowBalls();
    //     walk_distance(-media_vr);
    //     turn(90);
    //   }
    // }
  }
  else
  {
    media_vb = getmUltra(4,15);
    Serial.println("M inicial");
    Serial.println(media_vt);
    if(media_vb < 40.0)
    {
      walk_distancewb(media_vb - 1.0);
      SwallowBalls();
      freeze(50);
      delay(50);
      walk_distance(-media_vb + 1.0);
    }
  }

  freeze(100);  
  for (int i = 0; i < 15; i++) {
    //auxiliar values
    float auxr, auxl;
  
    auxl=getUltra(1);
    // Serial.print("1: ");Serial.println(auxl);
    delay(25);
  
    auxr=getUltra(2);
    // Serial.print("2: ");Serial.println(auxr);
    delay(25);
  
    //if the minimum value is lower than the recent, replaces
    if (auxl != 0.0 && mL != -1.0){if (auxl > mL)mL = auxl;}
    else mL = -1.0;
    if (auxr != 0.0 && mR != -1.0){if (auxr > mR)mR = auxr;}
    else mR = -1.0;
  
  //   //debug
  //   // Serial.println();
  //   // Serial.print("1: ");Serial.println(mL);
  //   // Serial.print("2: ");Serial.println(mR);
  //   // Serial.print("3: ");Serial.println(mT);
  //   // Serial.println();
  //   // Serial.println();
  }
  freeze(50);//stops the robot for 50 milliseconds  
  // Serial.println();
  // Serial.print("mL: ");Serial.print(mL);
  // Serial.print(" mR: ");Serial.println(mR);
  // Serial.println();
  
  
  front_scan();
  if(ent_m == 0)
  {
    turn(90*ent_s);
    front_scan_2();
    turn(-90*ent_s);
  }
  //if entrance is in the middle
  if (ent_m == 1) {
    tone(BUZZER,440,1000);
    LEDcontrol(1,0,0);
    delay(500);
    LEDcontrol(0,0,0);
    //"exit" of the room of 120 by the middle on left
    if (mL > 70.0 || mL == -1.0) {
      //search fot exit in the middle. If the value is still too high it's a 120cm room on the side.
      walk_distance(30.0);
      float mL2=0.1;
      float auxl2 = getUltra(1);
      for (int i = 0; i < 15; i++) {
        auxl2 = getUltra(1);
        if (auxl2 != 0.0 && mL2 != -1.0){if (auxl2 > mL2)mL2 = auxl2;}
        else mL2 = -1.0;
        
      }
      if (mL2 > 70.0 || mL2 == -1.0)
      {
        roomL = 120;roomF=90;
        walk_distance(-30.0);
        return;
      }
      else roomL = 90;
      walk_distance(-30.0);
    }
    else {
      roomL = 90; //side is 90cm
    }

    //"exit" of the room of 120 by the middle on right
    if (mR > 70.0 || mR == -1.0) {
      //search fot exit in the middle. If the value is still too high it's a 120cm room on the side.
      walk_distance(30.0);
      float mR2=0.1;
      float auxr2 = getUltra(2);
      for (int i = 0; i < 15; i++) {
        auxr2 = getUltra(2);
        if (auxr2 != 0.0 && mR2 != -1.0){if (auxr2 > mR2)mR2 = auxr2;}
        else mR2 = -1.0;
      }
      if (mR2 > 70.0 || mR2 == -1.0)
      {
        roomL = 120;roomF=90;
        walk_distance(-30.0);
        return;
      }
      else roomL = 90;
      walk_distance(-30.0);
    }
    else {
      roomL = 90; //side is 90cm
    }

    //"exit" of the room of 120 by the middle on top sensor
    if ((max_top > 70.0 || max_top == -1.0) && roomF == 0) {
      //search fot exit in the middle. If the value is still too high it's a 120cm room on the side.
      LEDcontrol(0,0,1);
      delay(2000);
      LEDcontrol(0,0,0);
      walk_distancewb(30.0);//walks to tte next tile
      turn(-90*ent_s);//turns to face the adjacent tile
      walk_distancewb(15.0);//goes to the adjacent tile
      media_vt = getmUltra(3,15);
      if(media_vt <= 25.0)
      {
        walk_distance(10.0);
        turn(180);
        touch(5000);
        walk_distance(20.0);
        turn(-90*ent_s);
      }
      else
      {
        turn(90*ent_s);//turns to face the front wall
      }
      float mT2=0.1;
      float auxt2 = getUltra(3);
      for (int i = 0; i < 15; i++) {//for used to get the maximum value of the top US
        auxt2 = getUltra(3);
        if (auxt2 != 0.0 && mT2 != -1.0)
        {
          if (auxt2 > mT2)mT2 = auxt2;
        }
        else mT2 = -1.0;
      }
      if (mT2 > 40.0 || mT2 == -1.0)//if the max valueof top US is a 120 or exit
      {
        roomF = 120;
        roomL = 90;
        tone(BUZZER, 440, 1000);
        LEDcontrol(0,0,1);
        delay(1000);
        LEDcontrol(0,0,0);

        turn(-90*ent_s);
        walk_distance(-15.0);
        turn(90*ent_s);
        walk_distance(-30.0);
        return;
      }
      else roomF = 90;
      //goes back
      turn(-90*ent_s);
      walk_distance(-15.0);
      turn(90*ent_s);
      walk_distance(-30.0);
    }
    else {
      roomF = 90; //front is 90cm
    }
  }

  //if entrance is on the right
  else if (ent_s == 1 && ent_m == 0) {
    //"exit" of the room of 120 by the middle on left
    if (maxlat == -1.0) {
      freeze(20);
      walk_distance(30.0);
      turn(90);
      front_scan();
      if (max_top > 70.0 || max_top == -1.0)
      {
        roomL = 120;
        roomF=90;
        turn(-90);
        walk_distance(-30.0);
        return;
      }
      else roomL = 90;
      turn(-90);
      walk_distance(-30.0);
    }

    else if (maxlat > 70.0) 
    {
      roomL = 120;
      roomF=90;
      return;
    }
    else {
      roomL = 90; //side is 90cm
    }

  }
  
  //if entrance is on the left
  else {
    //"exit" of the room of 120 by the middle on left
    if (maxlat == -1.0) {
      freeze(20);
      walk_distance(30.0);
      turn(-90);
      front_scan();
      if (max_top > 70.0 || max_top == -1.0)
      {
        roomL = 120;roomF=90;
        turn(90);
        walk_distance(-30.0);
        return;
      }
      else roomL = 90;
      turn(90);
      walk_distance(-30.0);
    }

    else if (maxlat > 70.0) 
    {
      roomL = 120;
      roomF=90;
      return;
    }
    else {
      roomL = 90; //side is 90cm
    }
  }
  
  //if entrance is on either side
  if ((max_top == -1.0) && roomF == 0 && ent_m == 0) {
    //"exit" of the room of 120 by the middle on top
    turn(ent_s*90);
    touch(5000);
    walk_distance(7.0);
    walk_distancewb(R_MID_90 - 10.0);
    freeze(50);
    turn(ent_s*-90);
    touch(5000);
    freeze(50);
    walk_distance(7.0);
    freeze(50);
    float mT2=0.1;
    float auxt2 = getUltra(3);
    for (int i = 0; i < 15; i++) 
    {
      auxt2 = getUltra(3);
      if (auxt2 != 0.0 && mT2 != -1.0){if (auxt2 > mT2)mT2 = auxt2;}
      else mT2 = -1.0;
      delay(10);
    }
    Serial.println("MT2:");
    Serial.println(mT2);
    if (mT2 > 70.0 || mT2 == -1.0)
    {
      walk_distancewb(R_MID_120 - 10.0);
      roomF = 120;
      roomL = 90;
      special = 1;
      LEDcontrol(1, 1, 1);
      delay(25);
      return;
    }
    else 
    {
      walk_distancewb(R_MID_90 - 3.0);
      roomF = 90;
      special = 1;
      LEDcontrol(0, 0, 1);
      delay(25);
    }
  }

  else if (max_top > 70.0) 
  {
    roomF = 120;
    roomL = 90;
    return;
  }
  else {
    roomF = 90; //front is 90cm
  }   

}


void go_to_mid() {
  
  if(ent_m == 0)// left/right entrance
  {
    turn(ent_s*90);//turn 90 deegres right / left
    Serial.println(c_angle);
    touch(5000);//touch function
  
    media_vt = getmUltra(3,15);//gets a media of the top US just for confirmation purposes 
  
    if(media_vt >= 100.0) //if the media is higher than 100.0 cm the robot is facing an exit
    {
      turn(ent_s*-90);

      //make the robot go to inital and updtades its angle    
      walk_distancewb(R_MID_90 - 1.0);
      turn(ent_s*90);//turns left/right
      
      touch(5000);//touch function
    
      walk_distancewb(R_MID_90 - 5.0);
      
    }
    
    else
    {
      // go_to_dist(R_MID_90);//go to the middle of the room
      walk_distancewb(R_MID_90 - 5.0);
      turn(ent_s*-90);//turn left / right
      touch(5000);
      
      // Serial.println(c_angle);

      // walk_distance(15.0);
      freeze(500);

      media_vt = getmUltra(3,15);
      if(media_vt >= 100.0)
      {
        walk_distance(-10.0);
        turn(ent_s*90);//turn left / right
        walk_distance(-(R_MID_90 - 1.0)); //walks to get in the begin of the room
        turn(ent_s*-90);
        // go_to_dist(R_MID_90);
        walk_distance(R_MID_90 - 1.0);
        turn(ent_s*90);
        touch(5000);
        // go_to_dist(R_MID_90);
        walk_distance(R_MID_90 - 1.0);
        
      }
      else  walk_distancewb(R_MID_90 - 1.0); //go_to_dist(R_MID_90);      
    }
  }
  
  else //entrance in the middle
  {
    media_vt = getmUltra(3, 25);
    if (media_vt >= 100.0)
    {
      //walk_distance
      walk_distancewb(R_MID_90);
    }
    else  
    {
      walk_distance(30.0);
      go_to_dist(R_MID_90);//if the exit isnt in the middle just go to the middle
    }
  }
  
}


void go_to_exit()
{

  LEDcontrol(0, 0, 0);
  go_to_angle(exit_angle);
  walk_distance(38.0);
  
  if(exit_angle == 90) //if exit angle == 90
  {
    do
    {
      array_read();
      walk(SWL,SWR);
    } while (NOSIB() < 3);
    room_clear = 1;
    walk(0, 0);
  }
}
