// Control the LED part of array
void LEDcontrol (bool r, bool g, bool b) {
  digitalWrite(R,!r);
  digitalWrite(G,!g);
  digitalWrite(B,!b);
}

// Control the LED part of rescue color sensor
void LEDRescue(bool r, bool g, bool b) {
  digitalWrite(RED_RESCUE,!r);
  digitalWrite(GREEN_RESCUE,!g);
  digitalWrite(BLUE_RESCUE,!b);
}


//Read what the LED is detecting
void readLED() {

  //turns on and read the RED
  LEDcontrol(1,0,0); 
  delay(5);
  rr = analogRead(RCS);
  rl = analogRead(LCS);
  delay(5); 
  
  //turns on and read the GREEN
  LEDcontrol(0,1,0);
  delay(5);
  gr = analogRead(RCS);  
  gl = analogRead(LCS);
  delay(5);
  
  //turns on and read the BLUE
  LEDcontrol(0,0,1);
  delay(5);    
  br = analogRead(RCS);   
  bl = analogRead(LCS);  
  delay(5);  

  //turns everything off
  LEDcontrol(0, 0, 0);
}

//Read what the LED is detecting
void readLED_finish() {

  //turns on and read the RED
  LEDcontrol(1,0,0); 
  delay(1);
  rr = analogRead(RCS);
  rl = analogRead(LCS);
  delay(1); 
  
  //turns on and read the GREEN
  LEDcontrol(0,1,0);
  delay(1);
  gr = analogRead(RCS);  
  gl = analogRead(LCS);
  delay(1);
  
  //turns on and read the BLUE
  LEDcontrol(0,0,1);
  delay(1);    
  br = analogRead(RCS);   
  bl = analogRead(LCS);  
  delay(1);  

  //turns everything off
  LEDcontrol(0, 0, 0);
}

//Read what the rescue LED is detecting
void readLEDRescue() {

  //turns on and read the RED
  LEDRescue(1,0,0); 
  delay(5);
  red_rescue = analogRead(RECS);
  delay(5); 
  
  //turns on and read the GREEN
  LEDRescue(0,1,0);
  delay(5);
  green_rescue = analogRead(RECS);
  delay(5);
  
  //turns on and read the BLUE
  LEDRescue(0,0,1);
  delay(5);    
  blue_rescue = analogRead(RECS);
  delay(5);  

  //turns everything off
  LEDRescue(0, 0, 0);
}


// Print what the left sensor color is reading
void print_left_color() {
  Serial.print(rl);
  Serial.print(" ");  
  Serial.print(gl);
  Serial.print(" ") ; 
  Serial.print(bl);
  Serial.println(" ");
}
// Print what the right sensor color is reading
void print_right_color() {
  Serial.print(rr);
  Serial.print(" ");  
  Serial.print(gr);
  Serial.print(" ") ; 
  Serial.print(br);
  Serial.println(" ");
}

// Print and read the RGB's LED
void color_print() {
  Serial.println("LEFT: ");
  print_left_color();
  Serial.println();

  Serial.println("RIGHT: ");
  print_right_color();
  Serial.println();
}

// Print what the left sensor color is reading
void color_rescue_print() {
  Serial.print(red_rescue);
  Serial.print(" ");  
  Serial.print(green_rescue);
  Serial.print(" ") ; 
  Serial.print(blue_rescue);
  Serial.println(" ");
}

// Read the reflection sensors in the array
void array_read() {
  ers = analogRead(ERS);
  rs = analogRead(RS);
  ms = analogRead(MS);
  ls = analogRead(LS);
  els = analogRead(ELS);
}

// Print the reflection sensors in the array from left to right
void array_print() {
  Serial.print(els);
  Serial.print(" ");
  Serial.print(ls);
  Serial.print(" ");
  Serial.print(ms);
  Serial.print(" ");
  Serial.print(rs);
  Serial.print(" ");
  Serial.println(ers);
}


//detects green on the left side
bool left_green() {
  //variation of the values at the same position
  int delta = higher(rl, gl, bl) - lower(rl, gl, bl);


  //if everything is in the reference value, green is the lowest value and the variation is in the reference value
  if(gl < rl && gl < bl) return true; 
  else return false;
}

//detects green on the right side
bool right_green() {
  //variation of the values at the same position
  int delta = higher(rr, gr, br) - lower(rr, gr, br);


  //if everything is in the range of being green, return true
  if(gr < rr && gr < br) return true; 
  else return false;
}

bool dead_end() {
  // If left_green and right_green are true, there are 2 greens
  if(left_green() == true && right_green() == true) return true;
  else return false;
}


// Define in_range as bool
bool in_range(int read_value, int ref_value,int tol) {
  
  // If the read value is inside the range (reference + tolerance or reference - tolerance)
  if(read_value <= ref_value + tol && read_value >= ref_value - tol) return true;

  else return false;
}

//highest value and lowest between 3, used in old detection
int higher(int val1, int val2, int val3) {
  if (val1 > val2) {
    if (val1 > val3) return val1;
    else return val3;
  } else {
    if (val2 > val3) return val2;
    else return val3;
  }
}
int lower(int val1, int val2, int val3) {
  if (val1 < val2) {
    if (val1 < val3) return val1;
    else return val3;
  } else {
    if (val2 < val3) return val2;
    else return val3;
  }
}


//if the red is the lowest value by far, then it's the finish line 

//counter for line
int finish_counter=0;

// function used to detect finish line (similar for the dectecion of room 3 and green)
void finish_line(){
  bool finish_l=0, finish_r=0, reflexive_l=0, reflexive_r=0;
  for (int i = 0; i < 1; i++){
    readLED_finish();

    if (rl < 600 && gl < 800 && bl < 600)reflexive_l=1;
    if (rr < 600 && gr < 800 && br < 600)reflexive_r=1;

    // int deltal = higher(rl, gl, bl) - lower(rl, gl, bl); //if necessary, the variation can be used
    if((rl+60) < gl && rl < bl && bl > 850) finish_l=1;

    // int deltar = higher(rr, gr, br) - lower(rr, gr, br); //if necessary, the variation can be used
    if((rr+60) < gr && rr < br && br > 850) finish_r=1;
  }

  if(finish_r == 1 && finish_l == 1 && ms < BLACK) 
  {
    finish_counter++;
  }
  else 
  {
    finish_counter=0;
  }
  if (finish_counter > 0)
  {
    while(1) 
    {
      LEDcontrol(0,0,0);
      walk(0,0);
    }
  }

  if (reflexive_l && reflexive_r && NOSIB()==0)
  {
    
    freeze(200);
    readLED_finish(); 
    reflexive_l=0;reflexive_r=0;

    if (rl < 600 && gl < 800 && bl < 600)reflexive_l=1;
    if (rr < 600 && gr < 800 && br < 600)reflexive_r=1;

    if (reflexive_l && reflexive_r && NOSIB()==0)
    {
      tone(BUZZER, 155, 5);
      LEDcontrol(1,1,1);

      Evacuation_Zone();
    }
  }
  

}

// function used to control the board LEDs in most times used to sinalize something
void Sinalize(bool gled,int blinksg,bool rled,int blinksr,int t)
{
  for(int i = 0; i < blinksg; i++)
  {
    digitalWrite(LEDG,gled);
    delay(t);
    digitalWrite(LEDG,0);
    delay(t);
  }
  for(int i = 0; i < blinksr; i++)
  {
    digitalWrite(LEDR,rled);
    delay(t);
    digitalWrite(LEDR,0);
    delay(t);
  }
}
