void touch(int lim_p) 
{
  unsigned long flag_p = millis();
  while (digitalRead(TOUCH1) || digitalRead(TOUCH2) )// Until the two sensors touch the wall
  {
    Serial.print(digitalRead(TOUCH1));
    Serial.println(digitalRead(TOUCH2));
    walk(-265,-265); // while the back buttons dont touch the wall make the robot go back
    if(!digitalRead(TOUCH1))walk(0, -265); // while the left back button doesn´t touch the wall walk with the left motor 
    if(!digitalRead(TOUCH2))walk(-265, 0); // while the right back button doesn´t touch the wall walk with the right motor
    delay(15);
    if(millis() - flag_p > lim_p)break;
  }
  freeze(100);
}
