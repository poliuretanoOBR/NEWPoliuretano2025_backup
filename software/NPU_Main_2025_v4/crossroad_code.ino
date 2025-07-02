//function to look for green
void analyze_green() {

  //bool for detecting green on crossroad
  int leftgreen=0, rightgreen=0;


  //starts walking while looking for green
  walk(SWL, SWR);

  //if it detects green once, keeps the information
  for (int i = 0; i < 11; i++) {
    readLED();
    if (i == 7){
      walk(0, 0);
      delay(10);
      readLED();
    }
    else walk(80, 80);

    //condition for green: green is the lowest value on the color read and red value is higher than blue
    if(rl > gl && bl > gl && rl > (gl + 50)){
      leftgreen=1;
    }
     
    if(rr > gr && br > gr && rr > (gr + 50)){
      rightgreen=1;
    }
    
    delay(10);
  }
  freeze(2);
  //if there's green on both sides
  if (leftgreen == 1 && rightgreen == 1) {

    //ledcontrol for debug "there are 2 greens"
    LEDcontrol(1,0,0);

    //turn on the green led and turns until it's on a black line
    digitalWrite(LEDG, 1);
    walk(SWL, SWR);
    delay(60);
    turn(-150);
    
    while (ls < BLACK){
      right(150);
      array_read();
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
    walk(SWL, SWR);
    delay(60);

    //turn on the green led and turns until it's on a black line
    digitalWrite(LEDG, 1);
    walk(SWL, SWR);
    delay(60); 
    turn(60);
    
    while (rs < BLACK){
      left(150);
      array_read();
    }
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
    walk(SWL, SWR);
    delay(60);
    //turn on the green led and turns until it's on a black line
    digitalWrite(LEDG, 1);
    walk(50, 50);
    delay(200);
    turn(-60);
    
    while (ls < BLACK){
      right(150);
      array_read();
    }

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

    walk_distance(-1.5);
    
    //does pid for a while
    unsigned long f = millis();
    while (millis() - f < 400) {
      array_read();
      PIDwalk(0.6);
      delay(5);
    }

    //turns off ledcontrol for debug "there's NOT a green"
    LEDcontrol(0,0,1);
  }
  
}
