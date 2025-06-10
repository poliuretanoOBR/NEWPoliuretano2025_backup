//value for dead victim
#define BLACK_BALL 930

void SwallowBalls() {
  
  int ball = 1023; //analogRead
  bool aux=0, alive=0, dead=0; //aux to do a single "swoosh2", alive or dead is the victim conditio
  Servo_ipos();
  
  //goes to the right position with both servo and catches the victim
  set_servo(1,180);
  set_servo(2,100);
  delay(10);
  
  set_servo(1, 150);
  set_servo(2, 120);
  delay(500);
  set_servo(1,120);
  int claw_TCRT = 1023, auxclaw = 0,lock = 0;
  for (int i = 0; i < 50; i++) 
  {
    if(i % 2 == 0 && i <= 30)
    {
      set_servo(1, 150);
      set_servo(1, 120);
    }
    auxclaw = analogRead(A10);
    if(auxclaw < claw_TCRT)
    {
      claw_TCRT = auxclaw;
    }
  }
  //starts to lift te ball and stops t the middle
  set_servo(1,100);
  set_servo(2, 60);
  set_servo(1, 40);

  set_servo(2, 10);
    
  // makes the ball go a little further from the reflectance sensor to read the victim color more pecisely
//  for (int i=0; i < 100; i++) {
//      int auxb=analogRead(A1);      
//      //reads the lowest value of the victim color
//      if (auxb < BLACK_BALL)ball=auxb;
  Serial.println(claw_TCRT);
      //reads the victim color
  if (claw_TCRT < BLACK_BALL) {
    set_servo(3,OPENR); //separator
    alive=true;
    avs++; ////another alive victim secured
  } 
    else 
   {
     set_servo(3,OPENL); //separator
     dead=true;
     dvs++;//another dead victim secured
   }

  
  //finishes going up
  set_servo(1, 0);
  delay(50);
  //pushes the ball inside the separator
  for (int a=0; a<5; a++) {
    for(int i = 10; i >= 140; i++){s2.write(i); delay(10);}
    delay(100);
    for(int i = 140; i >= 10; i--) {s2.write(i); delay(1);}
  }
  delay(50);
  //everything goes back to its original position
  Servo_ipos();
  balls++;//another victim secured
}
