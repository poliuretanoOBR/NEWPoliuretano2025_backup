void revolution(float revl, float revr, bool go_back) {
    dxl.torqueOff(DXL_ID);//turn off torque to change operation mode
    dxl2.torqueOff(DXL_ID2);//turn off torque to change operation mode
    dxl.setOperatingMode(DXL_ID, OP_EXTENDED_POSITION);//sets operation mode to extended position
    dxl2.setOperatingMode(DXL_ID2, OP_EXTENDED_POSITION);//sets operation mode to extended position
    dxl.torqueOn(DXL_ID);//turn torque on
    dxl2.torqueOn(DXL_ID2); //turn torque on
    
    int32_t current_posl, current_posr;//creates two variables for the current position of the motors

    current_posr = dxl.getPresentPosition(DXL_ID);//gets current position of the right motor
    current_posl = dxl2.getPresentPosition(DXL_ID2);//gets current position of the right motor

    //the goal position is the actual position + 4096 * the amount of revolution *-1 at one side because the motors are mirrored
    const int32_t goal_posr = current_posr + (int32_t)(4096 * revr) * (int32_t)-1, goal_posl = current_posl + (int32_t)(4096 * revl);//sets the goal position based on the number of revolutions


    //debug
    // Serial.print("posr: ");
    // Serial.println(current_posr);  
    // Serial.print("posl: ");
    // Serial.println(current_posl);
    // Serial.print("4096*revr: ");
    // Serial.println((long)4096*revr);
    // Serial.print("4096*revl: ");
    // Serial.println((long)4096*revl);

    // Serial.print("SUM1: ");
    // Serial.println((long)(current_posr + (long)4096*revr));
    // Serial.print("SUM2: ");
    // Serial.println((long)(current_posl + (long)4096*revr));


    //debug
    // Serial.print("delta r: ");
    // Serial.println(goal_posr - current_posr);  
    // Serial.print("delta l: ");
    // Serial.println(goal_posl - current_posl);

    dxl.setGoalPosition(DXL_ID, goal_posr);//sets the REAL goal position adding it current position
    dxl2.setGoalPosition(DXL_ID2, goal_posl);//sets the REAL goal position adding it current position


    //while there's a big difference on the actual reading and the goal position, it's not allowed to do anything else
    while(abs(dxl.getPresentPosition(DXL_ID) - goal_posr) > 10 || abs(dxl2.getPresentPosition(DXL_ID2) - goal_posl) > 10) {
        delay(5);
    }

    //debug of led
    digitalWrite(22, 1);
    delay(50);
    digitalWrite(22, 0);

    //debug
    // Serial.print("real pos 1: ");
    // Serial.println(dxl.getPresentPosition(DXL_ID));  
    // Serial.print("real pos 2: ");
    // Serial.println(dxl2.getPresentPosition(DXL_ID2));


    //turn off both motors
    dxl.torqueOff(DXL_ID);//turn off torque to stop the motors
    dxl2.torqueOff(DXL_ID2);//turn off torque to stop the motors

    //goes back to velocity mode
    if (go_back) {
        dxl.torqueOff(DXL_ID);//turn off torque to change operation mode
        dxl2.torqueOff(DXL_ID2);//turn off torque to change operation mode
        dxl.setOperatingMode(DXL_ID, OP_VELOCITY);//sets operation mode to velocity
        dxl2.setOperatingMode(DXL_ID2, OP_VELOCITY);//sets operation mode to velocity
        dxl.torqueOn(DXL_ID);//turn torque on
        dxl2.torqueOn(DXL_ID2); //turn torque on    
    }

}


//empirically we discovered that 1 revolution each motor goes 16.5 centimeters forward
void walk_rev(float cm, bool change) {
    float rev = cm/16.5; //after discovering the proportion, we do the math
    revolution(rev, rev, change); //turns the amount of time
}