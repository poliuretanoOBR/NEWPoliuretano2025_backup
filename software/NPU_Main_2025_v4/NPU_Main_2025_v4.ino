 //include libraries
#include <Dynamixel2Arduino.h>
#include <Wire.h>
#include <Servo.h>
#define KF 0.7 //accelerometer constant to reduce error

//servo ports
#define SERVO1 3 //servo port
#define SERVO2 4 //servo port
#define SERVO3 6 //servo port
#define SERVO4 999 //servo port

//ultrasonic ports
#define ECHO1 35//echo ultrasonic left
#define TRIG1 33 //trig ultrasonic left
#define ECHO2 45 //echo ultrasonic right
#define TRIG2 47 //trig ultrasonic right
#define ECHO3 41 //echo ultrasonic top
#define TRIG3 43   //trig ultrasonic top
#define ECHO4 37//echo4 ultrasonic bottom 33
#define TRIG4 39 //trig ultrasonic bottom 35

//mercury port
#define MERC 40
#define MERC2 42
#define MERC3 42
#define MERC4 42

//line constants
#define BLACK 350 //value of the black line
#define MIDDLE_BLACK 350 //value of the black line for the middle sensor
#define WHITE 100 //value of the white line

//array ports
#define ERS A5 // external right sensor in the analog 2
#define RS A4 // Right sensor in the analog 3
#define MS A6 // Middle sensor in the analog 4
#define LS A3 // Left sensor in the analog 5
#define ELS A2 // external left sensor in the analog 6
#define R 48 // Red LED in the A14 port
#define G 44// Green LED in the A13 port
#define B 46// Blue LED in the A12 port
#define RCS A7 // Right color sensor analog 7
#define LCS A8 // Left color sensor analog 8

//rescue ports
#define RECS A9 // color sensor analog 7 rescue
#define RED_RESCUE 34 // Red LED in the 34 port (rescue)
#define GREEN_RESCUE 36 // Green LED in the 36 port (rescue)
#define BLUE_RESCUE 38 // Blue LED in the 38 port (rescue)



//test room3 directives

//90x90
#define R_MID_90 37.0 //middle distance
#define D_TRI_90 30.0 //triangle distance

//120x90
#define R_MID_120 54.0  //middle distance



//old green detection
#define TOL 50 //Creates the value of tolerance for the color values
#define RRCSV 1002 // Right red sensor value when in green line
#define RGCSV 960 // Right green sensor value when in green line
#define RBCSV 987 // Right blue sensor value when in green line
#define LRCSV 985 // Left red sensor value when in green line
#define LGCSV 949 // Left green sensor value when in green line
#define LBCSV 970 // Left blue sensor value when in green line
#define REFERENCE_LEFT 855 //highest value on white + 100
#define REFERENCE_RIGHT 885 //highest value on white + 100
#define REFERENCE_DELTA_LEFT 27 //value of delta on green - 10
#define REFERENCE_DELTA_RIGHT 31 //value of delta on green - 10



//Board led ports
#define LEDG 24 //define green led port
#define LEDR 22 //define red led port


//constants of proportional, integral and derivative
#define KP 0.5 //percentage of proportional band
#define KI 0.00 //inverse of integral time
#define KD 0.3 //derivative of error


//maximum and minimum values of i
#define MIN_INTEGRAL -100
#define MAX_INTEGRAL 100

//maximum and minimum values of u
#define U_MIN -530.0
#define U_MAX 530.0

#define WE 2.0 //outer sensors weight aproximation
#define WI 1.0 //inner sensors weight aproximation



//battery port
#define BAT A15

#define DIST 13.5



//dynamixel configuration
#define DEBUG_SERIAL Serial   // Serial for debug (USB)
#define DXL_SERIAL Serial3  // Serial for dynamixel



//buzzer port
#define BUZZER 8 //buzzer port



//gyroscope average error on z axis
#define GYZ_ERROR 0.0
//-261.42



//touch sensors ports
#define TOUCH1 31 //left touch sensor
#define TOUCH2 29 //right touch sensor



//debug button
#define BUTTON 23 
#define SAIDA 1



//straight walking
#define SWL 150
#define SWR 150



//opening positions for the separator
#define DEPL 160 //deposit left
#define DEPR 20 //deposit right
#define OPENL 58 //opens for left
#define OPENR 120 // opens for right


//battery value
int battery = 0;

// Test room 3 variables
float vt = 0.0 ,vb = 0.0,vl = 0.0,vr = 0.0,prev_vb = 0.0,prev_vt = 0.0, media_vb = 0.0, media_vt = 0.0, media_vl = 0.0, media_vr = 0.0, delta_vb = 0.0,delta_vt = 0.0,delta_mbt = 0.0;
int c_angle=0, entrance_angle, exit_angle=1023, tri_red, tri_green,triangles = 0,tri = 0, detec=0;
unsigned long delta_timer_balls = 0;
bool room_clear = 0;
float media_sp = 0.0;
int s=0;
float max_top = 0.1, maxlat = 0.1, t=0.0, tc=0.0;

//OLD Room 3 variables
int rooms = 0, roomL=0, roomF=0;
bool special = 0;

bool paredes[12], ent_m=0;

//room3 national variables
int position=0, cont_tri=0;
bool side[4] = {0, 0, 0, 0};
int l=0;
int l_120 = 0;


unsigned long flag = 0; //timer for pid
unsigned long flag_loop = 0;
double previous_error=0; //"previous run" timer

//Optic variables

int ers, rs, ms, ls, els, count_u = 0;   // Middle, left, right, external left and external right sensor defined
int rr, rl, gr, gl, br, bl; // Creates the color sensor variables, in RGB for each side
int red_rescue, green_rescue, blue_rescue; // Creates the color sensor variables, in RGB (rescue)
int ram = 0, ram2=0, ram3=0, ram4=0; //

const int DXL_DIR_PIN = 32; // direction PIN
 
const uint8_t DXL_ID = 1;
const uint8_t DXL_ID2 = 2;
const float DXL_PROTOCOL_VERSION = 2.0;

int ent_s = 0, avs=0, dvs = 0, balls=0;



//dynamixel objects
Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
Dynamixel2Arduino dxl2(DXL_SERIAL, DXL_DIR_PIN);



//Servo objects
Servo s1;
Servo s2;
Servo s3;
Servo s4;

//dynamixel controltable items
using namespace ControlTableItem;




//declaring functions:

//gyroscope/aceletometer functions
void CalculateErrorGyro();
void turn(int alfa);
void Simple_turn(int alfa); 

//Mercury sensor function
void DetectInclinationUP();
void DetectInclinationDOWN();


// Optic:

//LEDs control functions
void LEDcontrol (bool r, bool g, bool b);
void LEDRescue(bool r, bool g, bool b);

//Reading LEDs functions
void readLED();
void readLED_finish();
void readLEDRescue();

//Printing functions
void print_left_color();
void print_right_color();
void color_print();
void color_rescue_print();

//Array reading and printing functions
void array_read();
void array_print();
int NOSIB();

bool left_green();
bool right_green();
bool dead_end();

bool in_range(int read_value, int ref_value, int tol);
int higher(int val1, int val2, int val3);
int lower(int val1, int val2, int val3);

void finish_line();

//Board LEDs function
void Sinalize(bool gled,int blinksg,bool rled,int blinksr,int t);

// Batery alarm:
double getBatteryAlarm();
void BuzzerAlert();


// Movement functions
void PIDwalk(float a);

void walk(int left, int right);
void back(int vel);

void right(int vel);
void left(int vel);

void freeze(int del);

void back_forth(int times, int del);

//crossroad
void analyze_green();

// Obstacle and Ultrassonic
double getUltra(int u);
float getmUltra(int u, int den);
float getmnUltra(int u, int den);
float getMaxLeftRight();
void getObstacle();
void Obstacle(char c);
void Obstacle_time();

//encoder
void revolution(float revl, float revr, bool go_back);
void walk_rev(float cm, bool change);

//Servos 
void set_servo (int n, int f_pos);
void Servo_ipos();

// Room 3 and rescue
void check_exit();

void touch(int lim_p);

int detectTri();

void tri_90();
void tri_120();

// Test Room
void Troom();
void go_to_mid();
void go_to_tri();
void go_to_exit();
void scan_entrance();
void scan_edge();
void scan_exit();
void confirm_exit();
void get_vbt();
void print_vbt();
void go_to_angle(int f_angle);
void update_angle(int ang);
void deposit(bool a);

//NEW Room 3 Functions
void go_to_mid_120();
void New_Room();
//room3 new ver
void go_to_distnb(float);
int getmsharp(int i);

//rescue
void SwallowBalls();
void scan_turn(int alfa, float dist_to_ball);

// Test 2:
void go_to_dist(float);
void walk_distance(float d);
void walk_distancewb(float d);
void Nroom();

void setup() {
  //Servo communication
  s1.attach(SERVO1);
  s2.attach(SERVO2);
  s3.attach(SERVO3);
  // s4.attach(SERVO4);

  // Set initial position for the three Servos
  Servo_ipos();

  //Initialize Wire communication
  Wire.begin();
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  // Use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(1000000);

  //initialize communication with dynamixel
 
  dxl.begin(1000000);
  dxl2.begin(1000000);

  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  dxl2.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  // Get DYNAMIXEL information
  if( dxl.ping(DXL_ID) ) Serial.println("Ok (1)");
  else Serial.println("Problema (1)");

  if( dxl2.ping(DXL_ID2) ) Serial.println("Ok (2)");
  else Serial.println("Problema (2)");
  
  // Turn off torque when configuring items in EEPROM area
  dxl.torqueOff(DXL_ID);
  dxl.setOperatingMode(DXL_ID, OP_VELOCITY);
  dxl2.setOperatingMode(DXL_ID2, OP_VELOCITY);
  dxl.torqueOn(DXL_ID);
  dxl2.torqueOn(DXL_ID2);

  dxl.ledOn(DXL_ID);
  dxl.ledOn(DXL_ID2);

  //pinmodes
  pinMode(MERC, INPUT);
  // pinMode(MERC2, INPUT);
  
  //ultrasonic
  pinMode(ECHO1, INPUT);
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO3, INPUT);
  pinMode(TRIG3, OUTPUT);
  pinMode(ECHO4, INPUT);
  pinMode(TRIG4, OUTPUT);

  //rgb rescue
  pinMode(RED_RESCUE, OUTPUT);
  pinMode(GREEN_RESCUE, OUTPUT);
  pinMode(BLUE_RESCUE, OUTPUT);

  //rgb led
  pinMode(R,OUTPUT);
  pinMode(G,OUTPUT);
  pinMode(B,OUTPUT);

  //turns them off
  digitalWrite(R, 1);
  digitalWrite(G, 1);
  digitalWrite(B, 1);
  LEDRescue(0, 0, 0);

  //color sensor
  
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);

  
  //button and buzzer
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT);


  //touch sensors
  pinMode(TOUCH1, INPUT_PULLUP);
  pinMode(TOUCH2, INPUT_PULLUP);
  
  flag_loop = millis();

}
void loop() {
  
  
  while(1)
  {
    // Serial.println(getUltra(1));  
    // delay(20);
    Serial.println("C");
    Serial.println("A");
    //Obstacle_time();
    // array_read();
    // array_print();
    /*readLED();
    color_print();*/
  }
  if (millis() - flag_loop > 10) {
    //battery alert and array read
    BuzzerAlert();
    array_read();

    //detect when it goes up 
    DetectInclinationDOWN();
    DetectInclinationUP();

    // //Crossroad
    if((ms >=  MIDDLE_BLACK && NOSIB() >= 2) || NOSIB()>=3) {
      //Stop the robot when enters crossroad
      walk_distance(-1.75);
      //analyzes green
      analyze_green();
    }

    // Normal line follower
    else {

      //line follower
      PIDwalk(0.8);
      array_print();
      
      //obstacle
      getObstacle();
    
      //turns+ off all led
      LEDcontrol(0, 0, 0);
      
      //search for finish line
      finish_line();
    }
      
    // Wait 5ms for next cycle
    flag_loop = millis();
  }
  delayMicroseconds(500);
}
