#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//////////////////////////////////////////////////////
///////////////////    CONSTANTS    ///////////////////
///////////////////////////////////////////////////////

const int SERVOMIN = 140;       // this value depends on the adjustment of the servos
                                //const ut your setup code here, to run once:

int SERVOMAX = 400;       // this value depends on the adjustment of the servos


const int SCHRITTWEITE = 10;    // setting up the step size of the servos
const double SCHRITTWEITE_alpha = 70;
const double SCHRITTWEITE_beta = 110;
const double SCHRITTWEITE_gamma = 100;

const int SERVOMIN_1 = 140; //corresponds to the DIP, PIP and MCP joints 
const int SERVOMAX_1 = 400; //corresponds to the DIP, PIP and MCP joints 

const int SERVOMIN_2 = 140; //corresponds to the DIP joint (fingertip) as well as to x_current_2
const int SERVOMAX_2 = 400; //corresponds to the DIP joint (fingertip) as well as to x_current_2

const int SERVOMIN_3 = 140;  //corresponds to the PIP joint as well as to x_current_3
const int SERVOMAX_3 = 400;  //corresponds to the PIP joint as well as to x_current_3

const int SERVOMIN_4 = 140; //corresponds to the MCP joint as well as to x_current_4
const int SERVOMAX_4 = 400; //corresponds to the MCP joint as well as to x_current_4

const int wrist_fe_start = 380;       // movement of the wrist from flexion to extension
const int wrist_ef_start = 140;       // movement of the wrist from extension to flexion
const int wrist_ru_start = 380;       // movement of the wrist from radial to ulnar
const int wrist_ur_start = 140;       // movement of the wrist from ulnar to radial
const int neutral_position = 270; 
int x_current_5 = 270;

//These values are obtained through calculations and experimental measurements.
const double r_c = 0.83;
const double r_b = 0.9;
const double r_a = 1.43;

// These values were obtained by experiments. These values represents the highest stretched position of the servo motor.
int x_start_4 = 400;                  // x_4 corresponts to gamma / MCP joint 270
int x_start_3 = 340;                  // x_3 corresponts to beta / PIP joint 280
int x_start_2 = 240;                  // x_2 corresponts to alpha / DIP joint 350
int x_start_1 = 140;

int alpha_min = 0; 
int alpha_max = 70; 

int beta_min = 0; 
int beta_max = 110; 

int gamma_min = -30; 
int gamma_max = 70; 

// There are two different adresses for the two Adafruit motor boards: pwm & pwm2
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40); // motor board 1 mit Servos von 11 - 35
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41); // motor board 1 mit Servos von 41 - 55

  /*
Assignement of the servo motors (left arm) --> Number Servo motor (corresponding Pin)

pwm1: 11(0), 12(1), 13(2), 14(3)
      21(4), 22(12), 23(6), 24(13)
      31(8), 32(9), 33(10), 34(11)

pwm2: 41(0), 42(1), 43(2), 44(3)
      51(4), 52(5), 53(6), 54(7)
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("movement of the roboy hand");
  pwm1.begin();
  pwm2.begin();

  // Servos run at ~50 Hz updates
  pwm1.setPWMFreq(50);  
  pwm2.setPWMFreq(50); 
  yield();
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement All FINGERS           /////////////
//////////////////    from flexion to stretch        /////////////
//////////////////////////////////////////////////////////////////
// von gebeugten Zustand in den gestreckten Zustand

void flexion_stretch_all_fingers_same_time(){ 
    int delta_alpha = 0;                // corresponds to the DIP joint (fingertip).
    int delta_beta = 0;                // corresponds to the PIP joint.
    int delta_gamma = 0;               // corresponds to the MCP joint.

    double delta_x4=0;
    double delta_x3=0;
    double delta_x2=0;
    double delta_x1=0;
    
    int x_start_4 = 400;                  // x_4 corresponts to gamma / MCP joint 
    int x_start_3 = 340;                  // x_3 corresponts to beta / PIP joint 
    int x_start_2 = 240;                  // x_2 corresponts to alpha / DIP joint 
    int x_start_1 = 140;

 while ((delta_alpha <= alpha_max && delta_alpha >= alpha_min)&&(delta_beta <= beta_max && delta_beta >= beta_min)&&(delta_gamma <= gamma_max && delta_gamma >= gamma_min)){
    void neutral_position_wrist();
    double delta_x4 = - delta_gamma * r_c ;
    double delta_x3 = (-delta_beta * r_b) + (delta_gamma * r_c); 
    double delta_x2 = (-delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);
    double delta_x1 = (delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);

    double x_current_4 = x_start_4 - delta_x4; 
    double x_current_3 = x_start_3 - delta_x3;
    double x_current_2 = x_start_2 - delta_x2;
    double x_current_1 = x_start_1 - delta_x1;

    Serial.println("stretch indexfinger: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("stretch indexfinger: delta_beta");
    Serial.println(delta_beta);
    Serial.println("stretch indexfinger: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("stretch indexfinger: x_current_4");
    Serial.println(x_current_4);
    Serial.println("stretch indexfinger: x_current_3");
    Serial.println(x_current_3);
    Serial.println("stretch indexfinger: x_current_2");
    Serial.println(x_current_2);
    Serial.println("flexion indexfinger: x_current_1");
    Serial.println(x_current_1);
    pwm1.setPWM(10, 0, x_current_3);              // 33 servo motor / Pin 10 --> stretch PIP 
    pwm1.setPWM(6, 0, x_current_1);               // 23 servo motor / Pin 6 --> flexion  
    pwm1.setPWM(2, 0, 270);                       // 13 servo motor / Pin 2 --> left/right
    pwm2.setPWM(2, 0, x_current_4);               // 43 servo motor / Pin 2 --> stretch MCP

    Serial.println("stretch middlefinger: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("stretch middlefinger: delta_beta");
    Serial.println(delta_beta);
    Serial.println("stretch middlefinger: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("stretch middlefinger: x_current_4");
    Serial.println(x_current_4);
    Serial.println("stretch middlefinger: x_current_3");
    Serial.println(x_current_3);
    Serial.println("stretch middlefinger: x_current_2");
    Serial.println(x_current_2);
    Serial.println("flexion middlefinger: x_current_1");
    Serial.println(x_current_1);
    pwm1.setPWM(11, 0, x_current_3);              // 34 servo motor / Pin 11 --> stretch PIP 
    pwm1.setPWM(13, 0, x_current_1);               // 24 servo motor / Pin 13 --> flexion  
    pwm1.setPWM(3, 0, 270);                       // 14 servo motor / Pin 3 --> left/right
    pwm2.setPWM(3, 0, x_current_4);               // 44 servo motor / Pin 3 --> stretch MCP 

    Serial.println("stretch RING/LITTLE FINGER: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("stretch RING/LITTLE FINGER: delta_beta");
    Serial.println(delta_beta);
    Serial.println("stretch RING/LITTLE FINGER: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("stretch RING/LITTLE FINGER: x_current_4");
    Serial.println(x_current_4);
    Serial.println("stretch RING/LITTLE FINGER: x_current_3");
    Serial.println(x_current_3);
    Serial.println("stretch RING/LITTLE FINGER: x_current_2");
    Serial.println(x_current_2);
    Serial.println("flexion RING/LITTLE FINGER: x_current_1");
    Serial.println(x_current_1);
    pwm1.setPWM(8, 0, x_current_3);                 // 31 servo motor / Pin 8 --> stretch PIP 
    pwm1.setPWM(4, 0, x_current_1);                 // 21 servo motor / Pin 4 --> flexion  
    pwm1.setPWM(0, 0, 270);                         // 11 servo motor / Pin 0 --> left/right
    pwm2.setPWM(0, 0, x_current_4);                 // 41 servo motor / Pin 0 --> stretch MCP
    
    /*Serial.println("stretch thumb: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("stretch thumb: delta_beta");
    Serial.println(delta_beta);
    Serial.println("stretch thumb: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("stretch thumb: x_current_4");
    Serial.println(x_current_4);
    Serial.println("stretch thumb: x_current_3");
    Serial.println(x_current_3);
    Serial.println("stretch thumb: x_current_2");
    Serial.println(x_current_2);
    Serial.println("stretch thumb: x_current_1");
    Serial.println(x_current_1);
    pwm1.setPWM(9, 0, x_current_3);              // 32 servo motor / Pin 9 --> stretch PIP 
    pwm1.setPWM(12, 0, x_current_1);              // 22 servo motor / Pin 12 --> flexion  
    pwm1.setPWM(1, 0, 300);                      // 12 servo motor / Pin 1 --> left/right 
    delay(40);
    pwm2.setPWM(1, 0, x_current_4);              // 42 servo motor / Pin 1 --> stretch MCP*/

    delta_alpha+=SCHRITTWEITE_alpha;
    delay(200);
    delta_beta+=SCHRITTWEITE_beta;
    delay(800);
    delta_gamma+=SCHRITTWEITE_gamma;
    delay(200); 
    if((x_current_1 > SERVOMAX_1 && x_current_1 < SERVOMIN_1) && (x_current_2 > SERVOMAX_2 && x_current_2 < SERVOMIN_2) && (x_current_3 > SERVOMAX_3 && x_current_3 < SERVOMIN_3) && (x_current_4 > SERVOMAX_4 && x_current_4 < SERVOMIN_4)){
    break;
    }
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement All FINGERS           /////////////
//////////////////    from stretch to flexion        /////////////
//////////////////////////////////////////////////////////////////
// von gebeugten Zustand in den gestreckten Zustand

void stretch_flexion_all_fingers_same_time(){ 
   int delta_alpha = 70;                // corresponds to the DIP joint (fingertip). 
    int delta_beta = 110;                // corresponds to the PIP joint. 
    int delta_gamma= 70;                 // corresponds to the MCP joint. 

    double delta_x4=0;
    double delta_x3=0;
    double delta_x2=0;
    double delta_x1=0;
    
    int x_start_4 = 300;                  // x_4 corresponts to gamma / MCP joint 
    int x_start_3 = 300;                  // x_3 corresponts to beta / PIP joint 
    int x_start_2 = 300;                  // x_2 corresponts to alpha / DIP joint 
    int x_start_1 = 400;
    
 while ((delta_alpha <= alpha_max && delta_alpha >= alpha_min)&&(delta_beta <= beta_max && delta_beta >= beta_min)&&(delta_gamma <= gamma_max && delta_gamma >= gamma_min)){
    void neutral_position_wrist();
    double delta_x4 = - delta_gamma * r_c ;
    double delta_x3 = (-delta_beta * r_b) + (delta_gamma * r_c); 
    double delta_x2 = (-delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);
    double delta_x1 = (delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);

    double x_current_4 = x_start_4 - delta_x4; 
    double x_current_3 = x_start_3 - delta_x3;
    double x_current_2 = x_start_2 - delta_x2;
    double x_current_1 = x_start_1 - delta_x1;
/*
    Serial.println("stretch thumb: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("stretch thumb: delta_beta");
    Serial.println(delta_beta);
    Serial.println("stretch thumb: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("stretch thumb: x_current_4");
    Serial.println(x_current_4);
    Serial.println("stretch thumb: x_current_3");
    Serial.println(x_current_3);
    Serial.println("stretch thumb: x_current_2");
    Serial.println(x_current_2);
    Serial.println("stretch thumb: x_current_1");
    Serial.println(x_current_1);
    /*pwm1.setPWM(9, 0, x_current_3);              // 32 servo motor / Pin 9 --> stretch PIP 
    pwm1.setPWM(12, 0, x_current_1);              // 22 servo motor / Pin 12 --> flexion  
    pwm1.setPWM(1, 0, 300);                      // 12 servo motor / Pin 1 --> left/right 
    pwm2.setPWM(1, 0, x_current_4);              // 42 servo motor / Pin 1 --> stretch MCP*/
    delay(500);
    Serial.println("stretch indexfinger: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("stretch indexfinger: delta_beta");
    Serial.println(delta_beta);
    Serial.println("stretch indexfinger: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("stretch indexfinger: x_current_4");
    Serial.println(x_current_4);
    Serial.println("stretch indexfinger: x_current_3");
    Serial.println(x_current_3);
    Serial.println("stretch indexfinger: x_current_2");
    Serial.println(x_current_2);
    Serial.println("flexion indexfinger: x_current_1");
    Serial.println(x_current_1);
    pwm1.setPWM(10, 0, x_current_3);              // 33 servo motor / Pin 10 --> stretch PIP 
    pwm1.setPWM(6, 0, x_current_1);               // 23 servo motor / Pin 6 --> flexion  
    pwm1.setPWM(2, 0, 270);                       // 13 servo motor / Pin 2 --> left/right
    pwm2.setPWM(2, 0, x_current_4);               // 43 servo motor / Pin 2 --> stretch MCP

    Serial.println("stretch middlefinger: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("stretch middlefinger: delta_beta");
    Serial.println(delta_beta);
    Serial.println("stretch middlefinger: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("stretch middlefinger: x_current_4");
    Serial.println(x_current_4);
    Serial.println("stretch middlefinger: x_current_3");
    Serial.println(x_current_3);
    Serial.println("stretch middlefinger: x_current_2");
    Serial.println(x_current_2);
    Serial.println("flexion middlefinger: x_current_1");
    Serial.println(x_current_1);
    pwm1.setPWM(11, 0, x_current_3);              // 34 servo motor / Pin 11 --> stretch PIP 
    pwm1.setPWM(13, 0, x_current_1);               // 24 servo motor / Pin 13 --> flexion  
    pwm1.setPWM(3, 0, 270);                       // 14 servo motor / Pin 3 --> left/right
    pwm2.setPWM(3, 0, x_current_4);               // 44 servo motor / Pin 3 --> stretch MCP 

    Serial.println("stretch RING/LITTLE FINGER: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("stretch RING/LITTLE FINGER: delta_beta");
    Serial.println(delta_beta);
    Serial.println("stretch RING/LITTLE FINGER: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("stretch RING/LITTLE FINGER: x_current_4");
    Serial.println(x_current_4);
    Serial.println("stretch RING/LITTLE FINGER: x_current_3");
    Serial.println(x_current_3);
    Serial.println("stretch RING/LITTLE FINGER: x_current_2");
    Serial.println(x_current_2);
    Serial.println("flexion RING/LITTLE FINGER: x_current_1");
    Serial.println(x_current_1);
    pwm1.setPWM(8, 0, x_current_3);                 // 31 servo motor / Pin 8 --> stretch PIP 
    pwm1.setPWM(4, 0, x_current_1);                 // 21 servo motor / Pin 4 --> flexion  
    pwm1.setPWM(0, 0, 270);                         // 11 servo motor / Pin 0 --> left/right
    pwm2.setPWM(0, 0, x_current_4);                 // 41 servo motor / Pin 0 --> stretch MCP

    delta_alpha-=SCHRITTWEITE_alpha;
    delay(200);
    delta_beta-=SCHRITTWEITE_beta;
    delay(200);
    delta_gamma-=SCHRITTWEITE_gamma;
    delay(200);
    if((x_current_1 > SERVOMAX_1 && x_current_1 < SERVOMIN_1) && (x_current_2 > SERVOMAX_2 && x_current_2 < SERVOMIN_2) && (x_current_3 > SERVOMAX_3 && x_current_3 < SERVOMIN_3) && (x_current_4 > SERVOMAX_4 && x_current_4 < SERVOMIN_4)){
    break;
    }
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement INDEX FINGER          /////////////
//////////////////    from flexion to stretch        /////////////
//////////////////////////////////////////////////////////////////
// von gebeugten Zustand in den gestreckten Zustand

void flexion_stretch_indexfinger(){ 
    int delta_alpha = 0;                // corresponds to the DIP joint (fingertip).
    int delta_beta = 0;                // corresponds to the PIP joint.
    int delta_gamma = 0;               // corresponds to the MCP joint.

    double delta_x4=0;
    double delta_x3=0;
    double delta_x2=0;
    double delta_x1=0;
    
    int x_start_4 = 400;                  // x_4 corresponts to gamma / MCP joint 
    int x_start_3 = 340;                  // x_3 corresponts to beta / PIP joint 
    int x_start_2 = 240;                  // x_2 corresponts to alpha / DIP joint 
    int x_start_1 = 140;

 while ((delta_alpha <= alpha_max && delta_alpha >= alpha_min)&&(delta_beta <= beta_max && delta_beta >= beta_min)&&(delta_gamma <= gamma_max && delta_gamma >= gamma_min)){
    void neutral_position_wrist();
    double delta_x4 = - delta_gamma * r_c ;
    double delta_x3 = (-delta_beta * r_b) + (delta_gamma * r_c); 
    double delta_x2 = (-delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);
    double delta_x1 = (delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);

    double x_current_4 = x_start_4 - delta_x4; 
    double x_current_3 = x_start_3 - delta_x3;
    double x_current_2 = x_start_2 - delta_x2;
    double x_current_1 = x_start_1 - delta_x1;

    Serial.println("stretch indexfinger: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("stretch indexfinger: delta_beta");
    Serial.println(delta_beta);
    Serial.println("stretch indexfinger: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("stretch indexfinger: x_current_4");
    Serial.println(x_current_4);
    Serial.println("stretch indexfinger: x_current_3");
    Serial.println(x_current_3);
    Serial.println("stretch indexfinger: x_current_2");
    Serial.println(x_current_2);
    Serial.println("flexion indexfinger: x_current_1");
    Serial.println(x_current_1);
    pwm1.setPWM(10, 0, x_current_3);              // 33 servo motor / Pin 10 --> stretch PIP 
    pwm1.setPWM(6, 0, x_current_1);               // 23 servo motor / Pin 6 --> flexion  
    pwm1.setPWM(2, 0, 270);                        // 13 servo motor / Pin 2 --> left/right
    pwm2.setPWM(2, 0, x_current_4);               // 43 servo motor / Pin 2 --> stretch MCP
    delta_alpha+=SCHRITTWEITE_alpha;
    delay(200);
    delta_beta+=SCHRITTWEITE_beta;
    delay(200);
    delta_gamma+=SCHRITTWEITE_gamma;
    delay(800); 
    if((x_current_1 > SERVOMAX_1 && x_current_1 < SERVOMIN_1) && (x_current_2 > SERVOMAX_2 && x_current_2 < SERVOMIN_2) && (x_current_3 > SERVOMAX_3 && x_current_3 < SERVOMIN_3) && (x_current_4 > SERVOMAX_4 && x_current_4 < SERVOMIN_4)){
    break;
    }
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement INDEX FINGER          /////////////
//////////////////    from stretch to flexion        /////////////
//////////////////////////////////////////////////////////////////
// von gestreckten in den gebeugten Zustand

void stretch_flexion_indexfinger(){

    int delta_alpha = 70;                // corresponds to the DIP joint (fingertip). 
    int delta_beta = 110;                // corresponds to the PIP joint. 
    int delta_gamma= 70;                 // corresponds to the MCP joint. 

    double delta_x4=0;
    double delta_x3=0;
    double delta_x2=0;
    double delta_x1=0;
    
    int x_start_4 = 300;                  // x_4 corresponts to gamma / MCP joint 
    int x_start_3 = 300;                  // x_3 corresponts to beta / PIP joint 
    int x_start_2 = 300;                  // x_2 corresponts to alpha / DIP joint 
    int x_start_1 = 400;
    
 while ((delta_alpha <= alpha_max && delta_alpha >= alpha_min)&&(delta_beta <= beta_max && delta_beta >= beta_min)&&(delta_gamma <= gamma_max && delta_gamma >= gamma_min)){
    void neutral_position_wrist();
    double delta_x4 = - delta_gamma * r_c ;
    double delta_x3 = (-delta_beta * r_b) + (delta_gamma * r_c); 
    double delta_x2 = (-delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);
    double delta_x1 = (delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);

    double x_current_4 = x_start_4 - delta_x4; 
    double x_current_3 = x_start_3 - delta_x3;
    double x_current_2 = x_start_2 - delta_x2;
    double x_current_1 = x_start_1 - delta_x1;

    Serial.println("flexion indexfinger: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("flexion indexfinger: delta_beta");
    Serial.println(delta_beta);
    Serial.println("flexion indexfinger: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("flexion indexfinger: x_current_4");
    Serial.println(x_current_4);
    Serial.println("flexion indexfinger: x_current_3");
    Serial.println(x_current_3);
    Serial.println("flexion indexfinger: x_current_2");
    Serial.println(x_current_2);
    Serial.println("flexion indexfinger: x_current_1");
    Serial.println(x_current_1);
    pwm1.setPWM(10, 0, x_current_3);              // 33 servo motor / Pin 10 --> stretch PIP 
    pwm1.setPWM(6, 0, x_current_1);               // 23 servo motor / Pin 6 --> flexion  
    pwm1.setPWM(2, 0, 270);                       // 13 servo motor / Pin 2 --> left/right
    pwm2.setPWM(2, 0, x_current_4);               // 43 servo motor / Pin 2 --> stretch MCP
    delta_alpha-=SCHRITTWEITE_alpha;
    delay(200);
    delta_beta-=SCHRITTWEITE_beta;
    delay(200);
    delta_gamma-=SCHRITTWEITE_gamma;
    delay(200);
    if((x_current_1 > SERVOMAX_1 && x_current_1 < SERVOMIN_1) && (x_current_2 > SERVOMAX_2 && x_current_2 < SERVOMIN_2) && (x_current_3 > SERVOMAX_3 && x_current_3 < SERVOMIN_3) && (x_current_4 > SERVOMAX_4 && x_current_4 < SERVOMIN_4)){
    break;
    }
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement THUMB                 /////////////
//////////////////    from flexion to stretch        /////////////
//////////////////////////////////////////////////////////////////
// von gebeugten Zustand in den gestreckten Zustand

void flexion_stretch_thumb(){ 
    int delta_alpha = 0;                // corresponds to the DIP joint (fingertip).
    int delta_beta = 0;                // corresponds to the PIP joint.
    int delta_gamma = 0;               // corresponds to the MCP joint.

    double delta_x4=0;
    double delta_x3=0;
    double delta_x2=0;
    double delta_x1=0;

    int x_start_4 = 200;                  // x_4 corresponts to gamma / MCP joint 
    int x_start_3 = 340;                  // x_3 corresponts to beta / PIP joint 
    int x_start_2 = 240;                  // x_2 corresponts to alpha / DIP joint 
    int x_start_1 = 140;

 while ((delta_alpha <= alpha_max && delta_alpha >= alpha_min)&&(delta_beta <= beta_max && delta_beta >= beta_min)&&(delta_gamma <= gamma_max && delta_gamma >= gamma_min)){
    void neutral_position_wrist();
    double delta_x4 = - delta_gamma * r_c ;
    double delta_x3 = (-delta_beta * r_b) + (delta_gamma * r_c); 
    double delta_x2 = (-delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);
    double delta_x1 = (delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);

    double x_current_4 = x_start_4 - delta_x4; 
    double x_current_3 = x_start_3 - delta_x3;
    double x_current_2 = x_start_2 - delta_x2;
    double x_current_1 = x_start_1 - delta_x1;

    Serial.println("stretch thumb: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("stretch thumb: delta_beta");
    Serial.println(delta_beta);
    Serial.println("stretch thumb: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("stretch thumb: x_current_4");
    Serial.println(x_current_4);
    Serial.println("stretch thumb: x_current_3");
    Serial.println(x_current_3);
    Serial.println("stretch thumb: x_current_2");
    Serial.println(x_current_2);
    Serial.println("stretch thumb: x_current_1");
    Serial.println(x_current_1);
    pwm1.setPWM(9, 0, x_current_3);              // 32 servo motor / Pin 9 --> stretch PIP 
    pwm1.setPWM(12, 0, x_current_1);              // 22 servo motor / Pin 12 --> flexion  
    pwm1.setPWM(1, 0, 300);                      // 12 servo motor / Pin 1 --> left/right 
    pwm2.setPWM(1, 0, x_current_4);              // 42 servo motor / Pin 1 --> stretch MCP
    delta_alpha+=SCHRITTWEITE_alpha;
    delay(200);
    delta_beta+=SCHRITTWEITE_beta;
    delay(200);
    delta_gamma+=SCHRITTWEITE_gamma;
    delay(200); 
    if((x_current_1 > SERVOMAX_1 && x_current_1 < SERVOMIN_1) && (x_current_2 > SERVOMAX_2 && x_current_2 < SERVOMIN_2) && (x_current_3 > SERVOMAX_3 && x_current_3 < SERVOMIN_3) && (x_current_4 > SERVOMAX_4 && x_current_4 < SERVOMIN_4)){
    break;
    }
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement THUMB                 /////////////
//////////////////    from stretch to flexion        /////////////
//////////////////////////////////////////////////////////////////
// von gestreckten in den gebeugten Zustand

void stretch_flexion_thumb(){

    int delta_alpha = 70;                // corresponds to the DIP joint (fingertip). 
    int delta_beta = 110;                // corresponds to the PIP joint. 
    int delta_gamma= 70;               // corresponds to the MCP joint. 

    double delta_x4=0;
    double delta_x3=0;
    double delta_x2=0;
    double delta_x1=0;
    
    int x_start_4 = 200;                  // x_4 corresponts to gamma / MCP joint 
    int x_start_3 = 300;                  // x_3 corresponts to beta / PIP joint 
    int x_start_2 = 300;                  // x_2 corresponts to alpha / DIP joint 
    int x_start_1 = 400;
    
 while ((delta_alpha <= alpha_max && delta_alpha >= alpha_min)&&(delta_beta <= beta_max && delta_beta >= beta_min)&&(delta_gamma <= gamma_max && delta_gamma >= gamma_min)){
    void neutral_position_wrist();
    double delta_x4 = - delta_gamma * r_c ;
    double delta_x3 = (-delta_beta * r_b) + (delta_gamma * r_c); 
    double delta_x2 = (-delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);
    double delta_x1 = (delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);

    double x_current_4 = x_start_4 - delta_x4; 
    double x_current_3 = x_start_3 - delta_x3;
    double x_current_2 = x_start_2 - delta_x2;
    double x_current_1 = x_start_1 - delta_x1;

    Serial.println("flexion thumb: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("flexion thumb: delta_beta");
    Serial.println(delta_beta);
    Serial.println("flexion thumb: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("flexion thumb: x_current_4");
    Serial.println(x_current_4);
    Serial.println("flexion thumb: x_current_3");
    Serial.println(x_current_3);
    Serial.println("flexion thumb: x_current_2");
    Serial.println(x_current_2);
    Serial.println("flexion thumb: x_current_1");
    Serial.println(x_current_1);
    pwm1.setPWM(9, 0, x_current_3);              // 32 servo motor / Pin 9 --> stretch PIP 
    pwm1.setPWM(12, 0, x_current_1);              // 22 servo motor / Pin 12 --> flexion  
    pwm1.setPWM(1, 0, 300);                      // 12 servo motor / Pin 1 --> left/right                     
    pwm2.setPWM(1, 0, x_current_4);              // 42 servo motor / Pin 1 --> stretch MCP
    delta_alpha-=SCHRITTWEITE_alpha;
    delay(200);
    delta_beta-=SCHRITTWEITE_beta;
    delay(200);
    delta_gamma-=SCHRITTWEITE_gamma;
    delay(200);
    if((x_current_1 > SERVOMAX_1 && x_current_1 < SERVOMIN_1) && (x_current_2 > SERVOMAX_2 && x_current_2 < SERVOMIN_2) && (x_current_3 > SERVOMAX_3 && x_current_3 < SERVOMIN_3) && (x_current_4 > SERVOMAX_4 && x_current_4 < SERVOMIN_4)){
    break;
    }
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement MIDDLE FINGER         /////////////
//////////////////    from flexion to stretch        /////////////
//////////////////////////////////////////////////////////////////
// von gebeugten Zustand in den gestreckten Zustand

void flexion_stretch_middlefinger(){ 
    int delta_alpha = 0;                // corresponds to the DIP joint (fingertip).
    int delta_beta = 0;                // corresponds to the PIP joint.
    int delta_gamma = 0;               // corresponds to the MCP joint.

    double delta_x4=0;
    double delta_x3=0;
    double delta_x2=0;
    double delta_x1=0;

    int x_start_4 = 400;                  // x_4 corresponts to gamma / MCP joint 
    int x_start_3 = 340;                  // x_3 corresponts to beta / PIP joint 
    int x_start_2 = 240;                  // x_2 corresponts to alpha / DIP joint 
    int x_start_1 = 140;

 while ((delta_alpha <= alpha_max && delta_alpha >= alpha_min)&&(delta_beta <= beta_max && delta_beta >= beta_min)&&(delta_gamma <= gamma_max && delta_gamma >= gamma_min)){
    void neutral_position_wrist();
    double delta_x4 = - delta_gamma * r_c ;
    double delta_x3 = (-delta_beta * r_b) + (delta_gamma * r_c); 
    double delta_x2 = (-delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);
    double delta_x1 = (delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);

    double x_current_4 = x_start_4 - delta_x4; 
    double x_current_3 = x_start_3 - delta_x3;
    double x_current_2 = x_start_2 - delta_x2;
    double x_current_1 = x_start_1 - delta_x1;

    Serial.println("stretch middlefinger: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("stretch middlefinger: delta_beta");
    Serial.println(delta_beta);
    Serial.println("stretch middlefinger: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("stretch middlefinger: x_current_4");
    Serial.println(x_current_4);
    Serial.println("stretch middlefinger: x_current_3");
    Serial.println(x_current_3);
    Serial.println("stretch middlefinger: x_current_2");
    Serial.println(x_current_2);
    Serial.println("flexion middlefinger: x_current_1");
    Serial.println(x_current_1);
    pwm1.setPWM(11, 0, x_current_3);              // 34 servo motor / Pin 11 --> stretch PIP 
    pwm1.setPWM(13, 0, x_current_1);               // 24 servo motor / Pin 13 --> flexion  
    pwm1.setPWM(3, 0, 270);                       // 14 servo motor / Pin 3 --> left/right
    pwm2.setPWM(3, 0, x_current_4);               // 44 servo motor / Pin 3 --> stretch MCP
    delta_alpha+=SCHRITTWEITE_alpha;
    delay(200);
    delta_beta+=SCHRITTWEITE_beta;
    delay(200);
    delta_gamma+=SCHRITTWEITE_gamma;
    delay(200);  
    if((x_current_1 > SERVOMAX_1 && x_current_1 < SERVOMIN_1) && (x_current_2 > SERVOMAX_2 && x_current_2 < SERVOMIN_2) && (x_current_3 > SERVOMAX_3 && x_current_3 < SERVOMIN_3) && (x_current_4 > SERVOMAX_4 && x_current_4 < SERVOMIN_4)){
    break;
    }
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement MIDDLE FINGER         /////////////
//////////////////    from stretch to flexion        /////////////
//////////////////////////////////////////////////////////////////
// von gestreckten in den gebeugten Zustand

void stretch_flexion_middlefinger(){

    int delta_alpha = 70;                // corresponds to the DIP joint (fingertip). 
    int delta_beta = 110;                // corresponds to the PIP joint. 
    int delta_gamma= 70;               // corresponds to the MCP joint. The value was set to 70 because the servo was not able to perform 90

    double delta_x4=0;
    double delta_x3=0;
    double delta_x2=0;
    double delta_x1=0;

    int x_start_4 = 300;                  // x_4 corresponts to gamma / MCP joint 
    int x_start_3 = 300;                  // x_3 corresponts to beta / PIP joint 
    int x_start_2 = 300;                  // x_2 corresponts to alpha / DIP joint 
    int x_start_1 = 400;
    
 while ((delta_alpha <= alpha_max && delta_alpha >= alpha_min)&&(delta_beta <= beta_max && delta_beta >= beta_min)&&(delta_gamma <= gamma_max && delta_gamma >= gamma_min)){
    void neutral_position_wrist();
    double delta_x4 = - delta_gamma * r_c ;
    double delta_x3 = (-delta_beta * r_b) + (delta_gamma * r_c); 
    double delta_x2 = (-delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);
    double delta_x1 = (delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);

    double x_current_4 = x_start_4 - delta_x4; 
    double x_current_3 = x_start_3 - delta_x3;
    double x_current_2 = x_start_2 - delta_x2;
    double x_current_1 = x_start_1 - delta_x1;

    Serial.println("flexion middlefinger: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("flexion middlefinger: delta_beta");
    Serial.println(delta_beta);
    Serial.println("flexion middlefinger: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("flexion middlefinger: x_current_4");
    Serial.println(x_current_4);
    Serial.println("flexion middlefinger: x_current_3");
    Serial.println(x_current_3);
    Serial.println("flexion middlefinger: x_current_2");
    Serial.println(x_current_2);
    Serial.println("flexion middlefinger: x_current_1");
    Serial.println(x_current_1);
    pwm1.setPWM(11, 0, x_current_3);              // 34 servo motor / Pin 11 --> stretch PIP 
    pwm1.setPWM(13, 0, x_current_1);               // 24 servo motor / Pin 13 --> flexion  
    pwm1.setPWM(3, 0, 270);                       // 14 servo motor / Pin 3 --> left/right
    pwm2.setPWM(3, 0, x_current_4);               // 44 servo motor / Pin 3 --> stretch MCP
    delta_alpha-=SCHRITTWEITE_alpha;
    delay(200);
    delta_beta-=SCHRITTWEITE_beta;
    delay(200);
    delta_gamma-=SCHRITTWEITE_gamma;
    delay(200);
    if((x_current_1 > SERVOMAX_1 && x_current_1 < SERVOMIN_1) && (x_current_2 > SERVOMAX_2 && x_current_2 < SERVOMIN_2) && (x_current_3 > SERVOMAX_3 && x_current_3 < SERVOMIN_3) && (x_current_4 > SERVOMAX_4 && x_current_4 < SERVOMIN_4)){
    break;
    }
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement RING & LITLLE FINGER  /////////////
//////////////////    from flexion to stretch        /////////////
//////////////////////////////////////////////////////////////////
// von gebeugten Zustand in den gestreckten Zustand

void flexion_stretch_ring_little_finger(){ 
    int delta_alpha = 0;                // corresponds to the DIP joint (fingertip).
    int delta_beta = 0;                // corresponds to the PIP joint.
    int delta_gamma = 0;               // corresponds to the MCP joint.

    double delta_x4=0;
    double delta_x3=0;
    double delta_x2=0;
    double delta_x1=0;

    int x_start_4 = 400;                  // x_4 corresponts to gamma / MCP joint 
    int x_start_3 = 340;                  // x_3 corresponts to beta / PIP joint 
    int x_start_2 = 240;                  // x_2 corresponts to alpha / DIP joint 
    int x_start_1 = 140;

 while ((delta_alpha <= alpha_max && delta_alpha >= alpha_min)&&(delta_beta <= beta_max && delta_beta >= beta_min)&&(delta_gamma <= gamma_max && delta_gamma >= gamma_min)){
    void neutral_position_wrist();
    double delta_x4 = - delta_gamma * r_c ;
    double delta_x3 = (-delta_beta * r_b) + (delta_gamma * r_c); 
    double delta_x2 = (-delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);
    double delta_x1 = (delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);

    double x_current_4 = x_start_4 - delta_x4; 
    double x_current_3 = x_start_3 - delta_x3;
    double x_current_2 = x_start_2 - delta_x2;
    double x_current_1 = x_start_1 - delta_x1;

    Serial.println("stretch RING/LITTLE FINGER: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("stretch RING/LITTLE FINGER: delta_beta");
    Serial.println(delta_beta);
    Serial.println("stretch RING/LITTLE FINGER: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("stretch RING/LITTLE FINGER: x_current_4");
    Serial.println(x_current_4);
    Serial.println("stretch RING/LITTLE FINGER: x_current_3");
    Serial.println(x_current_3);
    Serial.println("stretch RING/LITTLE FINGER: x_current_2");
    Serial.println(x_current_2);
    Serial.println("flexion RING/LITTLE FINGER: x_current_1");
    Serial.println(x_current_1);
    pwm1.setPWM(8, 0, x_current_3);                 // 31 servo motor / Pin 8 --> stretch PIP 
    pwm1.setPWM(4, 0, x_current_1);                 // 21 servo motor / Pin 4 --> flexion  
    pwm1.setPWM(0, 0, 270);                         // 11 servo motor / Pin 0 --> left/right
    pwm2.setPWM(0, 0, x_current_4);                 // 41 servo motor / Pin 0 --> stretch MCP
    delta_alpha+=SCHRITTWEITE_alpha;
    delay(200);
    delta_beta+=SCHRITTWEITE_beta;
    delay(200);
    delta_gamma+=SCHRITTWEITE_gamma;
    delay(200);  
    if((x_current_1 > SERVOMAX_1 && x_current_1 < SERVOMIN_1) && (x_current_2 > SERVOMAX_2 && x_current_2 < SERVOMIN_2) && (x_current_3 > SERVOMAX_3 && x_current_3 < SERVOMIN_3) && (x_current_4 > SERVOMAX_4 && x_current_4 < SERVOMIN_4)){
    break;
    }
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement RING & LITLLE FINGER  /////////////
//////////////////    from stretch to flexion        /////////////
//////////////////////////////////////////////////////////////////
// von gestreckten in den gebeugten Zustand

void stretch_flexion_ring_little_finger(){

    int delta_alpha = 70;                // corresponds to the DIP joint (fingertip). 
    int delta_beta = 110;                // corresponds to the PIP joint. 
    int delta_gamma= 70;                 // corresponds to the MCP joint. The value was set to 70 because the servo was not able to perform 90

    double delta_x4=0;
    double delta_x3=0;
    double delta_x2=0;
    double delta_x1=0;

    int x_start_4 = 300;                  // x_4 corresponts to gamma / MCP joint 
    int x_start_3 = 300;                  // x_3 corresponts to beta / PIP joint 
    int x_start_2 = 300;                  // x_2 corresponts to alpha / DIP joint 
    int x_start_1 = 400;
    
 while ((delta_alpha <= alpha_max && delta_alpha >= alpha_min)&&(delta_beta <= beta_max && delta_beta >= beta_min)&&(delta_gamma <= gamma_max && delta_gamma >= gamma_min)){
    void neutral_position_wrist();
    double delta_x4 = - delta_gamma * r_c ;
    double delta_x3 = (-delta_beta * r_b) + (delta_gamma * r_c); 
    double delta_x2 = (-delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);
    double delta_x1 = (delta_alpha * r_a) + (delta_beta * r_b) + (delta_gamma * r_c);

    double x_current_4 = x_start_4 - delta_x4; 
    double x_current_3 = x_start_3 - delta_x3;
    double x_current_2 = x_start_2 - delta_x2;
    double x_current_1 = x_start_1 - delta_x1;

    Serial.println("flexion RING/LITTLE FINGER: delta_alpha");
    Serial.println(delta_alpha);
    Serial.println("flexion RING/LITTLE FINGER: delta_beta");
    Serial.println(delta_beta);
    Serial.println("flexion RING/LITTLE FINGER: delta_gamma");
    Serial.println(delta_gamma);
    Serial.println("flexion RING/LITTLE FINGER: x_current_4");
    Serial.println(x_current_4);
    Serial.println("flexion RING/LITTLE FINGER: x_current_3");
    Serial.println(x_current_3);
    Serial.println("flexion RING/LITTLE FINGER: x_current_2");
    Serial.println(x_current_2);
    Serial.println("flexion RING/LITTLE FINGER: x_current_1");
    Serial.println(x_current_1);
    pwm1.setPWM(8, 0, x_current_3);                 // 31 servo motor / Pin 8 --> stretch PIP 
    pwm1.setPWM(4, 0, x_current_1);                 // 21 servo motor / Pin 4 --> flexion  
    pwm1.setPWM(0, 0, 270);                         // 11 servo motor / Pin 0 --> left/right
    pwm2.setPWM(0, 0, x_current_4);                 // 41 servo motor / Pin 0 --> stretch MCP
    delta_alpha-=SCHRITTWEITE_alpha;
    delay(200);
    delta_beta-=SCHRITTWEITE_beta;
    delay(200);
    delta_gamma-=SCHRITTWEITE_gamma;
    delay(200);
    if((x_current_1 > SERVOMAX_1 && x_current_1 < SERVOMIN_1) && (x_current_2 > SERVOMAX_2 && x_current_2 < SERVOMIN_2) && (x_current_3 > SERVOMAX_3 && x_current_3 < SERVOMIN_3) && (x_current_4 > SERVOMAX_4 && x_current_4 < SERVOMIN_4)){
    break;
    }
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement INDEX FINGER           ////////////
//////////////////    from left to right              ////////////
//////////////////////////////////////////////////////////////////
// von links nach rechts (nach innen)

void left_right_indexfinger(){ 
int x_current_5 = 200;
 while (x_current_5 <= 400 && x_current_5 >= 150){
    void neutral_position_wrist();
    Serial.println("right indexfinger: x_current_5");
    Serial.println(x_current_5);
    pwm2.setPWM(2, 0, 410);               // 43 servo motor / Pin 2 --> stretch MCP
    pwm1.setPWM(10, 0, 278);              // 33 servo motor / Pin 10 --> stretch PIP 
    pwm1.setPWM(5, 0, 137);               // 22 servo motor / Pin 1 --> stretch DIP (fingertip) 
    pwm1.setPWM(2, 0, x_current_5);       // 13 servo motor / Pin 2 --> left/right
    //delay(10);   
    x_current_5+=5;
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement INDEX FINGER           ////////////
//////////////////    from right to left              ////////////
//////////////////////////////////////////////////////////////////
// von rechts nach links (nach innen)

void right_left_indexfinger(){ 
int x_current_5 = 400;
 while (x_current_5 <= 400 && x_current_5 >= 150){
    void neutral_position_wrist();
    Serial.println("right index finger: x_current_5");
    Serial.println(x_current_5);
    pwm2.setPWM(2, 0, 410);               // 43 servo motor / Pin 2 --> stretch MCP
    pwm1.setPWM(10, 0, 278);              // 33 servo motor / Pin 10 --> stretch PIP 
    pwm1.setPWM(5, 0, 137);               // 22 servo motor / Pin 1 --> stretch DIP (fingertip) 
    pwm1.setPWM(2, 0, x_current_5);       // 13 servo motor / Pin 2 --> left/right
    delay(10);   
    x_current_5-=5;
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement THUMB                  ////////////
//////////////////    from left to right              ////////////
//////////////////////////////////////////////////////////////////
// von rechts nach links (nach außen)

void left_right_thumb(){ 
int x_current_5 = 200;
 while (x_current_5 <= 400 && x_current_5 >= 150){
    void neutral_position_wrist();
    Serial.println("left thumb: x_current_5");
    Serial.println(x_current_5);
    pwm2.setPWM(1, 0, 300);               // 42 servo motor / Pin 1 --> stretch MCP
    pwm1.setPWM(9, 0, 278);               // 32 servo motor / Pin 9 --> stretch PIP 
    pwm1.setPWM(12, 0, 137);              // 22 servo motor / Pin 12 --> stretch DIP   (fingertip) 
    pwm1.setPWM(1, 0, x_current_5);       // 12 servo motor / Pin 1 --> left/right
    delay(10);   
    x_current_5+=5;
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement THUMB                  ////////////
//////////////////    from right to left              ////////////
//////////////////////////////////////////////////////////////////
// von rechts nach links (nach außen)

void right_left_thumb(){ 
int x_current_5 = 400;
 while (x_current_5 <= 400 && x_current_5 >= 150){
    void neutral_position_wrist();
    Serial.println("left thumb: x_current_5");
    Serial.println(x_current_5);
    pwm2.setPWM(1, 0, 300);              // 42 servo motor / Pin 1 --> stretch MCP
    pwm1.setPWM(9, 0, 278);              // 32 servo motor / Pin 9 --> stretch PIP 
    pwm1.setPWM(12, 0, 137);             // 22 servo motor / Pin 12 --> stretch DIP (fingertip) 
    pwm1.setPWM(2, 0, x_current_5);      // 12 servo motor / Pin 2 --> left/right
    delay(10);   
    x_current_5-=5;
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement MIDDLE FINGER          ////////////
//////////////////    from left to right              ////////////
//////////////////////////////////////////////////////////////////
// von links nach rechts (nach innen)

void right_left_middlefinger(){ 
int x_current_5 = 200;
 while (x_current_5 <= 400 && x_current_5 >= 150){
    void neutral_position_wrist();
    Serial.println("right middle finger: x_current_5");
    Serial.println(x_current_5);
    pwm2.setPWM(3, 0, 410);                 // 44 servo motor / Pin 3 --> stretch MCP
    pwm1.setPWM(11, 0, 278);                // 34 servo motor / Pin 11 --> stretch PIP 
    pwm1.setPWM(13, 0, 137);                // 24 servo motor / Pin 13 --> stretch DIP (fingertip) 
    pwm1.setPWM(3, 0, x_current_5);         // 14 servo motor / Pin 3 --> left/right
    //delay(10);   
    x_current_5+=5;
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement MIDDLE FINGER          ////////////
//////////////////    from right to left              ////////////
//////////////////////////////////////////////////////////////////
// von rechts nach links (nach innen)

void left_right_middlefinger(){ 
int x_current_5 = 400;
 while (x_current_5 <= 400 && x_current_5 >= 150){
    void neutral_position_wrist();
    Serial.println("right middlefinger: x_current_5");
    Serial.println(x_current_5);
    pwm2.setPWM(3, 0, 410);                 // 44 servo motor / Pin 3 --> stretch MCP
    pwm1.setPWM(11, 0, 278);                // 34 servo motor / Pin 11 --> stretch PIP 
    pwm1.setPWM(13, 0, 137);                // 24 servo motor / Pin 13 --> stretch DIP (fingertip) 
    pwm1.setPWM(3, 0, x_current_5);         // 14 servo motor / Pin 3 --> left/right
    delay(10);   
    x_current_5-=5;
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement RING & LITTLE FINGER   ////////////
//////////////////    from left to right              ////////////
//////////////////////////////////////////////////////////////////
// von links nach rechts (nach innen)

void left_right_ring_little_finger(){ 
int x_current_5 = 200;
 while (x_current_5 <= 400 && x_current_5 >= 150){
    void neutral_position_wrist();
    Serial.println("right RING/LITTLE FINGER: x_current_5");
    Serial.println(x_current_5);
    pwm2.setPWM(0, 0, 410);               // 41 servo motor / Pin 0 --> stretch MCP
    pwm1.setPWM(8, 0, 278);               // 31 servo motor / Pin 8 --> stretch PIP 
    pwm1.setPWM(4, 0, 137);               // 21 servo motor / Pin 4 --> stretch DIP (fingertip) 
    pwm1.setPWM(0, 0, x_current_5);       // 11 servo motor / Pin 0 --> left/right
    //delay(10);   
    x_current_5+=5;
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement RING & LITTLE FINGER   ////////////
//////////////////    from right to left              ////////////
//////////////////////////////////////////////////////////////////
// von rechts nach links (nach innen)

void right_left_ring_little_finger(){ 
int x_current_5 = 400;
 while (x_current_5 <= 400 && x_current_5 >= 150){
    void neutral_position_wrist();
    Serial.println("right RING/LITTLE FINGER: x_current_5");
    Serial.println(x_current_5);
    pwm2.setPWM(0, 0, 410);               // 41 servo motor / Pin 0 --> stretch MCP
    pwm1.setPWM(8, 0, 278);               // 31 servo motor / Pin 8 --> stretch PIP 
    pwm1.setPWM(4, 0, 137);               // 21 servo motor / Pin 4 --> stretch DIP (fingertip) 
    pwm1.setPWM(0, 0, x_current_5);       // 11 servo motor / Pin 0 --> left/right
    delay(10);   
    x_current_5-=5;
}
}
//////////////////////////////////////////////////////////////////
//////////////////    Neutral position of the wrist     //////////
//////////////////    all tendons are streched         ///////////
//////////////////////////////////////////////////////////////////

void neutral_position_wrist(){
// Nullstelle wrist, 270 --> This is the position where the wrist is in a neutral position
    int neutral_position = 270; 
    delay(60);
    pwm2.setPWM(4, 0, neutral_position);               //51 servo motor / Pin 4
    pwm2.setPWM(5, 0, neutral_position);               //52 servo motor / Pin 5
    pwm2.setPWM(6, 0, neutral_position);               //53 servo motor / Pin 6
    pwm2.setPWM(7, 0, neutral_position);               //54 servo motor / Pin 7
    Serial.println("neutral position");
    Serial.println(neutral_position); 
  }
//////////////////////////////////////////////////////////////////
//////////////////    Movement for the wrist     /////////////////
//////////////////    flexion_extension_wrist   //////////////////
//////////////////////////////////////////////////////////////////
// Movement from flexion to extension = 70°

void flexion_extension_wrist(){
  int wrist_fe = wrist_fe_start;
  int wrist_ef = wrist_ef_start;
  do
  {
    pwm2.setPWM(5, 0, wrist_fe);         //52 servo motor / Pin 5
    pwm2.setPWM(7, 0, wrist_ef);         //54 servo motor / Pin 7

    // blaue Tendons, for movement radial - ulnar
    pwm2.setPWM(4, 0, 270);              //51 servo motor / Pin 4
    pwm2.setPWM(6, 0, 270);              //53 servo motor / Pin 6

    Serial.println("flexion_extension_wrist: SERVO 52");
    Serial.println(wrist_fe);
    Serial.println("flexion_extension_wrist: SERVO 54");
    Serial.println(wrist_ef);
       wrist_fe-=SCHRITTWEITE;
       delay(30);
       wrist_ef+=SCHRITTWEITE;
  } while (wrist_ef<= SERVOMAX && wrist_ef>= SERVOMIN && wrist_fe<= SERVOMAX && wrist_fe>= SERVOMIN);
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement for the wrist     /////////////////
//////////////////    extension_flexion_wrist   //////////////////
//////////////////////////////////////////////////////////////////
// Movement from extension to flexion = 80°

void extension_flexion_wrist(){
   int wrist_ef = wrist_ef_start;
   int wrist_fe = wrist_fe_start;
   do 
  {
    pwm2.setPWM(5, 0, wrist_ef);         //52 servo motor / Pin 5
    pwm2.setPWM(7, 0, wrist_fe);         //54 servo motor / Pin 7
    
    // grüne Tendons, for movement radial - ulnar
    pwm2.setPWM(4, 0, 270);              //51 servo motor / Pin 4
    pwm2.setPWM(6, 0, 270);              //53 servo motor / Pin 6
    
    Serial.println("extension_flexion_wrist: SERVO 52");
    Serial.println(wrist_ef);
    Serial.println("extension_flexion_wrist: SERVO 54");
    Serial.println(wrist_fe);
    wrist_ef+=SCHRITTWEITE;
    delay(30);
    wrist_fe-=SCHRITTWEITE;
  } while (wrist_ef<= SERVOMAX && wrist_ef>= SERVOMIN && wrist_fe<= SERVOMAX && wrist_fe>= SERVOMIN);  
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement for the wrist     /////////////////
//////////////////    ulnar_radial_wrist         /////////////////
//////////////////////////////////////////////////////////////////
// Movement from radial to ulnar = 20°

void ulnar_radial_wrist(){
  int wrist_ur = wrist_ur_start;         
  int wrist_ru = wrist_ru_start;         
  do
  {
    //Servo 51 und Servo 53 haben entgegengesetzte Werte!!!
    pwm2.setPWM(4, 0, wrist_ur);              //51 servo motor / Pin 4
    pwm2.setPWM(6, 0, wrist_ru);              //53 servo motor / Pin 6
    // orange tendons, for movement flexion - extension
    pwm2.setPWM(5, 0, 270);                   //52 servo motor / Pin 5
    pwm2.setPWM(7, 0, 270);                   //54 servo motor / Pin 7
    Serial.println("ulnar_radial_wrist Servo 51");
    Serial.println(wrist_ur);
    Serial.println("ulnar_radial_wrist Servo 53");
    Serial.println(wrist_ru);
       wrist_ur-=SCHRITTWEITE;
       delay(30); 
       wrist_ru+=SCHRITTWEITE;
  } while (wrist_ur >= SERVOMIN && wrist_ur<=SERVOMAX && wrist_ru >= SERVOMIN && wrist_ru <= SERVOMAX); 
}

//////////////////////////////////////////////////////////////////
//////////////////    Movement for the wrist     /////////////////
//////////////////    radial_ulnar_wrist        //////////////////
//////////////////////////////////////////////////////////////////
// Movement from radial to ulnar = 30°

void radial_ulnar_wrist(){
     int wrist_ru = wrist_ru_start;      
     int wrist_ur = wrist_ur_start;       
   do 
  {
    //Servo 51 und Servo 53 haben entgegengesetzte Werte!!!
    pwm2.setPWM(4, 0, wrist_ru);              //51 servo motor / Pin 4
    pwm2.setPWM(6, 0, wrist_ur);              //53 servo motor / Pin 6
    // orange tendons, for movement flexion - extension
    pwm2.setPWM(5, 0, 270);                   //52 servo motor / Pin 5
    pwm2.setPWM(7, 0, 270);                   //54 servo motor / Pin 7
    Serial.println("radial_ulnar_wrist Servo 51");
    Serial.println(wrist_ru);
    Serial.println("radial_ulnar_wrist Servo 53");
    Serial.println(wrist_ru);
       wrist_ru+=SCHRITTWEITE;
       wrist_ur-=SCHRITTWEITE;
       delay(30); 
  } while (wrist_ru>= SERVOMIN && wrist_ru<=SERVOMAX && wrist_ur >= SERVOMIN && wrist_ur <= SERVOMAX); 
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement all fingers           /////////////
//////////////////    from flexion to stretch        /////////////
//////////////////////////////////////////////////////////////////
// von gebeugten Zustand in den gestreckten Zustand

void flexion_stretch_all_fingers(){ 
    neutral_position_wrist();                
    flexion_stretch_indexfinger();                 
    flexion_stretch_middlefinger();
    flexion_stretch_ring_little_finger(); 
    //flexion_stretch_thumb(); 
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement all fingers           /////////////
//////////////////    from stretch to flexion        /////////////
//////////////////////////////////////////////////////////////////
// von gestreckten in den gebeugten Zustand

void stretch_flexion_all_fingers(){
    neutral_position_wrist();
    //stretch_flexion_thumb();
    stretch_flexion_indexfinger();
    stretch_flexion_middlefinger();
    stretch_flexion_ring_little_finger();
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement all fingers           /////////////
//////////////////    from left to right             /////////////
//////////////////////////////////////////////////////////////////
// von gebeugten Zustand in den gestreckten Zustand

void left_right_all_fingers(){ 
    neutral_position_wrist(); 
    //left_right_thumb();                
    left_right_indexfinger();                 
    left_right_middlefinger();
    left_right_ring_little_finger(); 
}
//////////////////////////////////////////////////////////////////
//////////////////    Movement all fingers           /////////////
//////////////////    from right to left             /////////////
//////////////////////////////////////////////////////////////////
// von gestreckten in den gebeugten Zustand

void right_left_all_fingers(){
    neutral_position_wrist();
    right_left_indexfinger();
    right_left_middlefinger();
    right_left_ring_little_finger();
    //right_left_thumb();
}
//////////////////////////////////////////////////////////////////
//////////////////   void loop        ////////////////////////////
//////////////////   function call    ////////////////////////////
//////////////////////////////////////////////////////////////////

void loop() {
 /*
//test for adjust the servo
    neutral_position_wrist();
    pwm1.setPWM(0, 0, 400);               // 52 servo motor / Pin 6 --> stretch MCP
    pwm1.setPWM(1, 0, 400);               // 44 servo motor / Pin 3 --> stretch MCP
    pwm1.setPWM(2, 0, 400);              // 33 servo motor / Pin 10 --> stretch PIP 
    pwm1.setPWM(3, 0, 400);               // 13 servo motor / Pin 6 --> stretch DIP (fingertip)
    
    pwm1.setPWM(4, 0, 400);               // 52 servo motor / Pin 6 --> stretch MCP
    pwm1.setPWM(5, 0, 400);               // 44 servo motor / Pin 3 --> stretch MCP
    pwm1.setPWM(6, 0, 400);              // 33 servo motor / Pin 10 --> stretch PIP 
    pwm1.setPWM(7, 0, 140);               // 13 servo motor / Pin 6 --> stretch DIP (fingertip)
    
    pwm1.setPWM(8, 0, 400);               // 52 servo motor / Pin 6 --> stretch MCP
    pwm1.setPWM(9, 0, 140);               // 44 servo motor / Pin 3 --> stretch MCP
    pwm1.setPWM(10, 0, 400);              // 33 servo motor / Pin 10 --> stretch PIP 
    pwm1.setPWM(11, 0, 400);               // 13 servo motor / Pin 6 --> stretch DIP (fingertip) 
      
    pwm2.setPWM(0, 0, 400);               // 52 servo motor / Pin 6 --> stretch MCP
    pwm2.setPWM(1, 0, 240);               // 44 servo motor / Pin 3 --> stretch MCP
    pwm2.setPWM(2, 0, 400);              // 33 servo motor / Pin 10 --> stretch PIP 
    pwm2.setPWM(3, 0, 400);               // 13 servo motor / Pin 6 --> stretch DIP (fingertip) 
  */

//////////////////////////////////////////////////////////////////
//////////////////   movement fingers      ///////////////////////
/////////////////////////////////////////////////////////////////
    /*
    pwm1.setPWM(4, 0, 300);              // 43 servo motor / Pin 2 --> stretch MCP
    delay(2000);
    pwm1.setPWM(4, 0, 400);              // 43 servo motor / Pin 2 --> stretch MCP
    delay(2000);
    /*
    pwm1.setPWM(10, 0, 300);              // 33 servo motor / Pin 10 --> stretch PIP 
    //pwm1.setPWM(12, 0, 400);              //  servo motor / Pin 5 --> stretch DIP (fingertip) 
    pwm1.setPWM(6, 0, 400);              // 23 servo motor / Pin 6 --> flexion 
    pwm1.setPWM(4, 0, 300);              // 21 servo motor / Pin 4 --> flexion  
    pwm1.setPWM(2, 0, 270);                      // 13 servo motor / Pin 2 --> left/right 
    delay(2000);

flexion_stretch_fingers();             
delay(2000);
stretch_flexion_fingers();              
delay(2000);
flexion_stretch_fingers();             
delay(2000);
*/
/*
neutral_position_wrist(); 
delay(1000);



pwm1.setPWM(2, 0, 270);       // 13 servo motor / Pin 2 --> left/right
pwm1.setPWM(3, 0, 270);       // 13 servo motor / Pin 2 --> left/right
pwm1.setPWM(0, 0, 270);       // 13 servo motor / Pin 2 --> left/right
pwm1.setPWM(1, 0, 300);       // 13 servo motor / Pin 2 --> left/right
*/
/* 
flexion_stretch_all_fingers();         
delay(2000);
stretch_flexion_all_fingers();
delay(2000);
/*
left_right_all_fingers();          
delay(2000);
right_left_all_fingers();          
delay(2000);
*/
stretch_flexion_all_fingers_same_time();
delay(2000);
flexion_stretch_all_fingers_same_time();
delay(2000);
 /*

delay(2000);
flexion_stretch_indexfinger();
delay(2000);
 
flexion_stretch_middlefinger();           
delay(2000);

flexion_stretch_ring_little_finger();
delay(2000);
 
flexion_stretch_thumb();
delay(2000);




delay(2000);
delay(2000);
delay(2000);

stretch_flexion_thumb();
delay(2000);

stretch_flexion_ring_little_finger();
delay(2000);

stretch_flexion_middlefinger(); 
delay(2000);

stretch_flexion_indexfinger();
delay(2000);

delay(2000);
flexion_stretch_indexfinger();
delay(2000);
 
flexion_stretch_middlefinger();           
delay(2000);

flexion_stretch_ring_little_finger();
delay(2000);
 
flexion_stretch_thumb();
delay(2000);

stretch_flexion_thumb();
delay(2000);

stretch_flexion_ring_little_finger();
delay(2000);

stretch_flexion_middlefinger(); 
delay(2000);

left_right_indexfinger();
delay(1000);
right_left_indexfinger();
delay(200);
left_right_indexfinger();
delay(200);
right_left_indexfinger();
delay(200);
left_right_indexfinger();
delay(200);
right_left_indexfinger();
delay(200);
left_right_indexfinger();
delay(200);
right_left_indexfinger();
delay(200);
 
delay(2000);

stretch_flexion_indexfinger();
delay(2000);

pwm1.setPWM(2, 0, 270);       // 13 servo motor / Pin 2 --> left/right
pwm1.setPWM(3, 0, 270);       // 13 servo motor / Pin 2 --> left/right
pwm1.setPWM(0, 0, 270);       // 13 servo motor / Pin 2 --> left/right
pwm1.setPWM(1, 0, 300);       // 13 servo motor / Pin 2 --> left/right
*/
//////////////////////////////////////////////////////////////////
//////////////////   movement wrist        ///////////////////////
//////////////////////////////////////////////////////////////////
/*
flexion_extension_wrist();               // movement of the wrist from flexion to extension
delay(2000);
neutral_position_wrist();                // middle position
delay(2000);
extension_flexion_wrist();               // movement of the wrist from extension to flexion
delay(2000);
neutral_position_wrist();                // middle position
delay(2000);
radial_ulnar_wrist();                    // movement of the wrist from ulnar to radial
delay(2000);
neutral_position_wrist();              // middle position
delay(2000);
ulnar_radial_wrist();                    // movement of the wrist from radial to ulnar
delay(2000); 
neutral_position_wrist();              // middle position
delay(2000);
*/
}


