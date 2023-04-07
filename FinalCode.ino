#include <PS2X_lib.h>  //for v1.6

PS2X ps2x; // create PS2 Controller Class
int error = 0; 
byte type = 0;
byte vibrate = 0;

//all capital letters for inputs
//all small letters for outputs

int compound_valve =50; //compound coil o/p

int MID_JOINT_F =44;
int mid_joint_f =43;
int toggleState1;
int lastmidfState = 0;

int MID_JOINT_B =45;
int mid_joint_b =42;
int toggleState2;
int lastmidbState = 0;

int FORWARD =26;
int forward =28;
int toggleState3;
int lastforwardState = 0;

int BACKWARD =27;
int backward =29;
int toggleState4;
int lastbackwardState = 0;

int LIFT_UP =40;
int Lift_up =39;
int toggleState5;
int lastliftupState = 0;

int LIFT_DOWN =41;
int Lift_down =38;
int toggleState6;
int lastliftdownState = 0;

int MOTOR =46;
int motor =48;
int toggleState7;
int lastmotorState = 0;

int STR_LEFT = 22;
int str_left = 23;
int toggleState8;
int laststrleftState=0;

int STR_RIGHT =24;
int str_right = 25;
int toggleState9;
int laststrrightState=0;

int TILT_UP =36;
int tilt_up = 35;
int toggleState10;
int lasttiltupState=0;

int TILT_DOWN =37;
int tilt_down = 34;
int toggleState11;
int lasttiltdownState=0;

int MAST_F =32;
int mast_f = 31;
int toggleState12;
int lastmastfState=0;

int MAST_B =33;
int mast_b = 30;
int toggleState13;
int lastmastbState=0;

int SELECT = 22;
int lastselectState ; 
int toggleStateSelect;

void setup(){
  
pinMode(MID_JOINT_F, INPUT);
pinMode(MID_JOINT_B, INPUT);
pinMode(MOTOR, INPUT);
pinMode(FORWARD, INPUT);
pinMode(BACKWARD, INPUT);
pinMode(LIFT_UP, INPUT);
pinMode(LIFT_DOWN, INPUT);
pinMode(STR_LEFT, INPUT);
pinMode(STR_RIGHT, INPUT);
pinMode(TILT_UP, INPUT);
pinMode(TILT_DOWN, INPUT);
pinMode(MAST_F, INPUT);
pinMode(MAST_B, INPUT);
   
pinMode(compound_valve, OUTPUT);
pinMode(mid_joint_f, OUTPUT);
pinMode(mid_joint_b, OUTPUT);
pinMode(forward, OUTPUT);
pinMode(backward, OUTPUT);
pinMode(Lift_up, OUTPUT);
pinMode(Lift_down, OUTPUT);
pinMode(motor, OUTPUT);
pinMode(str_left, OUTPUT);
pinMode(str_right, OUTPUT);
pinMode(tilt_up, OUTPUT);
pinMode(tilt_down, OUTPUT);
pinMode(mast_f, OUTPUT);
pinMode(mast_b, OUTPUT);
  
 Serial.begin(57600);

 //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
 error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
 if(error == 0){
   Serial.println("Found Controller, configured successful");
 }
   
  else if(error == 1)
   Serial.println("No controller found, check wiring");
   
  else if(error == 2)
   Serial.println("Controller found but not accepting commands");
   
  else if(error == 3)
   Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);
   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
     }
  
}

void loop(){
  if(error == 1) //skip loop if no controller found
  return; 
  
 if(type == 1){ 
  //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
    
  int motorState = ps2x.Button(PSB_START);
  
  if(motorState == 1 && lastmotorState == 0)    //if button is pressed and was released last change
    {
      toggleState7 =! toggleState7;                 //toggle the LED state
      digitalWrite(motor, toggleState7);
      lastmotorState = 1;    //record the lastButtonState
    }  
    if(motorState == 0 && lastmotorState == 1)    //if button is not pressed, and was pressed last change
    {
      lastmotorState = 0;    //record the lastButtonState
    }
 
   int select = ps2x.Button(PSB_SELECT) ; 
  if( select == 1 && lastselectState == 0)    //if button is pressed and was released last change
    {
      toggleStateSelect =! toggleStateSelect;                 //toggle the LED state
      digitalWrite(SELECT, toggleStateSelect);
      lastselectState = 1;    //record the lastButtonState   
      
    }  
    if(select == 0 && lastselectState == 1)    //if button is not pressed, and was pressed last change
    {
      lastselectState = 0;    //record the lastButtonState
    } 
    
  int MODE = digitalRead(SELECT);  
 if ( MODE == HIGH ){
  TOGGLE();
  }else {
  SWITCH();
  } 
  
 delay(50);
     
}
}

void TOGGLE(){
   
  int midfState = ps2x.Button(PSB_R1);
  int midbState = ps2x.Button(PSB_L1);
  int forwardState = ps2x.Button(PSB_PAD_UP);
  int backwardState = ps2x.Button(PSB_PAD_DOWN);
  int liftupState = ps2x.Button(PSB_GREEN);
  int liftdownState = ps2x.Button(PSB_BLUE);
  int strleftState = ps2x.Button(PSB_PAD_LEFT);
  int strrightState = ps2x.Button(PSB_PAD_RIGHT);
  int tiltupState = ps2x.Button(PSB_PINK);
  int tiltdownState = ps2x.Button(PSB_RED);
  int mastfState = ps2x.Button(PSB_R2);
  int mastbState = ps2x.Button(PSB_L2);
  
  switch (forwardState){   
  case 1 :
    digitalWrite(compound_valve,HIGH);              
    digitalWrite(backward,LOW);    
     safety2();   
     break;
  case 0:
     Lift_Up ();
     Lift_Down ();            
     Backward ();
     SteeringLeft ();
     SteeringRight ();
     Mid_F (); 
     Mid_B ();  
     Tilt_Up(); 
     Tilt_Down(); 
     Mast_F(); 
     Mast_B();            
     break;
     }
switch (backwardState){
  case 1:
    digitalWrite(compound_valve,HIGH);          
    digitalWrite(forward,LOW);   
     safety2();    
    break;
  case 0:
    Lift_Up ();
    Lift_Down ();
    Forward ();
    SteeringLeft ();
    SteeringRight ();
    Mid_F (); 
    Mid_B ();
    Tilt_Up(); 
    Tilt_Down(); 
    Mast_F(); 
    Mast_B();
    break;
    } 
switch (strleftState){
  case 1:
    digitalWrite(compound_valve,HIGH);          
    digitalWrite(str_right,LOW);
    safety2();    
    break;
  case 0:
    Lift_Up ();
    Lift_Down ();
    Forward ();
    Backward ();
    Mid_F (); 
    Mid_B ();
    Tilt_Up(); 
    Tilt_Down(); 
    Mast_F(); 
    Mast_B();
    SteeringRight ();
    break;
    }
switch (strrightState){
  case 1:
    digitalWrite(compound_valve,HIGH);          
    digitalWrite(str_left,LOW);
    safety2();    
    break;
  case 0:
    Lift_Up ();
    Lift_Down ();
    Forward ();
    Backward ();
    Mid_F (); 
    Mid_B ();
    Tilt_Up(); 
    Tilt_Down(); 
    Mast_F(); 
    Mast_B();
    SteeringLeft ();
    break;
    }    
switch (liftupState){
  case 1:
    digitalWrite(compound_valve,HIGH);          
    digitalWrite(Lift_down,LOW);
    digitalWrite(mid_joint_f,LOW);
    digitalWrite(mid_joint_b,LOW);    
    digitalWrite(mast_f,LOW);
    digitalWrite(mast_b,LOW);
    digitalWrite(tilt_up,LOW);
    digitalWrite(tilt_down,LOW);    
    safety1();
    break;
  case 0:
    Lift_Down ();
    Tilt_Up(); 
    Tilt_Down(); 
    Mast_F(); 
    Mast_B();
    Forward ();
    Backward ();
    SteeringLeft ();
    SteeringRight ();
    Mid_F (); 
    Mid_B ();    
    break ;
    }    
switch (liftdownState){
  case 1:
    digitalWrite(compound_valve,HIGH);          
    digitalWrite(Lift_up,LOW);
    digitalWrite(mid_joint_f,LOW);
    digitalWrite(mid_joint_b,LOW);    
    digitalWrite(mast_f,LOW);
    digitalWrite(mast_b,LOW);
    digitalWrite(tilt_up,LOW);
    digitalWrite(tilt_down,LOW);  
    safety1();
    break;
  case 0:    
    Lift_Up ();
    Tilt_Up(); 
    Tilt_Down(); 
    Mast_F(); 
    Mast_B();
    Forward ();
    Backward ();
    SteeringLeft ();
    SteeringRight ();
    Mid_F (); 
    Mid_B ();    
    break ;
    }    
switch (midfState){
  case 1:
    digitalWrite(compound_valve,HIGH);          
    digitalWrite(Lift_up,LOW);
    digitalWrite(Lift_down,LOW);
    digitalWrite(mid_joint_b,LOW);
    digitalWrite(tilt_up,LOW);
    digitalWrite(tilt_down,LOW);
    digitalWrite(mast_f,LOW);
    digitalWrite(mast_b,LOW);
    safety1();
    break;
  case 0:    
    Lift_Up ();
    Lift_Down ();
    Tilt_Up(); 
    Tilt_Down(); 
    Mast_F(); 
    Mast_B();
    Forward ();
    Backward ();
    SteeringLeft ();
    SteeringRight (); 
    Mid_F ();   
    break;
    }
    
switch (midbState){
  case 1:
    digitalWrite(compound_valve,HIGH);          
    digitalWrite(Lift_up,LOW);
    digitalWrite(Lift_down,LOW);
    digitalWrite(mid_joint_f,LOW);
    digitalWrite(tilt_up,LOW);
    digitalWrite(tilt_down,LOW);
    digitalWrite(mast_f,LOW);
    digitalWrite(mast_b,LOW);
    safety1();
    break;
  case 0:    
    Lift_Up ();
    Lift_Down ();
    Tilt_Up(); 
    Tilt_Down(); 
    Mast_F(); 
    Mast_B();
    Forward ();
    Backward ();
    SteeringLeft ();
    SteeringRight ();
    Mid_F ();     
    break;
    }
    
switch (tiltupState){
  case 1:
    digitalWrite(compound_valve,HIGH);          
    digitalWrite(Lift_up,LOW);
    digitalWrite(Lift_down,LOW);
    digitalWrite(tilt_down,LOW);
    digitalWrite(mid_joint_f,LOW);
    digitalWrite(mid_joint_b,LOW);    
    digitalWrite(mast_f,LOW);
    digitalWrite(mast_b,LOW);    
    safety1();
    break;
  case 0:    
    Lift_Up ();
    Lift_Down ();
    Tilt_Down(); 
    Mast_F(); 
    Mast_B();
    Forward ();
    Backward ();
    SteeringLeft ();
    SteeringRight ();
    Mid_F (); 
    Mid_B ();
    break;
    }
    
switch (tiltdownState){
  case 1:
    digitalWrite(compound_valve,HIGH);          
    digitalWrite(Lift_up,LOW);
    digitalWrite(Lift_down,LOW);
    digitalWrite(tilt_up,LOW);
    digitalWrite(mid_joint_f,LOW);
    digitalWrite(mid_joint_b,LOW);    
    digitalWrite(mast_f,LOW);
    digitalWrite(mast_b,LOW);    
    safety1();
    break;
  case 0:    
    Lift_Up ();
    Lift_Down ();
    Tilt_Up(); 
    Mast_F(); 
    Mast_B();
    Forward ();
    Backward ();
    SteeringLeft ();
    SteeringRight ();
    Mid_F (); 
    Mid_B ();
    break;
    }
    
switch (mastfState){
  case 1:
    digitalWrite(compound_valve,HIGH);          
    digitalWrite(Lift_up,LOW);
    digitalWrite(Lift_down,LOW);
    digitalWrite(mid_joint_f,LOW);
    digitalWrite(mid_joint_b,LOW);
    digitalWrite(tilt_up,LOW);
    digitalWrite(tilt_down,LOW);
    digitalWrite(mast_b,LOW);
    safety1();
    break;
  case 0:    
    Lift_Up ();
    Lift_Down ();
    Tilt_Up(); 
    Tilt_Down();  
    Mast_B();
    Forward ();
    Backward ();
    SteeringLeft ();
    SteeringRight ();
    Mid_F (); 
    Mid_B ();   
    break;
    }
    
switch (mastbState){
  case 1:
    digitalWrite(compound_valve,HIGH);          
    digitalWrite(Lift_up,LOW);
    digitalWrite(Lift_down,LOW);
    digitalWrite(mid_joint_f,LOW);
    digitalWrite(mid_joint_b,LOW);
    digitalWrite(tilt_up,LOW);
    digitalWrite(tilt_down,LOW);
    digitalWrite(mast_f,LOW);
    safety1();
    break;
  case 0:    
    Lift_Up ();
    Lift_Down ();
    Tilt_Up(); 
    Tilt_Down();  
    Mast_F();
    Forward ();
    Backward ();
    SteeringLeft ();
    SteeringRight ();
    Mid_F (); 
    Mid_B ();   
    break;
    }    
    safety3(); 
}

void SWITCH(){
  
int SL = 33;//stearing left output
int SR = 35;// stearing right output
int BF = 53; //forward output
int BB = 31;//backward output
int MF=5;// mast forward output
int MB=2;//backward output
int TF=15;//tillting forward output
int TB=16;//tillting backward output
int LF=14;// lift up output
int LB=17;// lift down output
int CF=6;//mid joint cylinder forward output
int CB=7;//mid joint cylinder backward output
int Help_Button = 49;
int Sensor_Action=51;
int Sensor_Input=52;
int x=50;//valve for all


int left = ps2x.Button(PSB_PAD_LEFT);        //reading of stearing left input
int right = ps2x.Button(PSB_PAD_RIGHT);      //reading of stearing right input
int up = ps2x.Button(PSB_PAD_UP);            //reading of forward input
int down = ps2x.Button(PSB_PAD_DOWN);        //reading of backward input 
int mastf = ps2x.Button(PSB_R2);             //reading of mast forward input
int mastb = ps2x.Button(PSB_L2);             //reading of mast backward input
int tiltf = ps2x.Button(PSB_PINK);           //reading of  tillting forward input
int tiltb = ps2x.Button(PSB_RED);           //reading of tillting backward input
int liftf = ps2x.Button(PSB_GREEN);          //reading of lift up input
int liftb = ps2x.Button(PSB_BLUE);           //reading of lift down input
int cylif = ps2x.Button(PSB_R1);             //reading of mid joint cylinder forward input
int cylib = ps2x.Button(PSB_L1);             //reading of mid joint cylinder backward
int M_H = ps2x.Button(PSB_START);            //reading of motor on 
int M_L = ps2x.Button(PSB_SELECT);   //reading of motor off
int Help_Read =  ps2x.Button(PSB_L3);        //reading of help button
int Sensor_Read = digitalRead(Sensor_Input);




   //////////////////////////////////////////////////////up+right+left+safty
   if(up==HIGH&&down==LOW&&mastf==LOW&&mastb==LOW&&liftb==LOW&&liftf==LOW&&tiltf==LOW&&tiltb==LOW&&cylif==LOW&&cylib==LOW){
    if(left==HIGH&&right==LOW){//check stearing left button & other buttons states
      digitalWrite( BF, HIGH);
      digitalWrite( SL, HIGH);
      digitalWrite( x, HIGH);
     }
    else{
      digitalWrite( SL, LOW);
      if(right==HIGH&&left==LOW){//check stearing right button & other buttons states
      digitalWrite( BF, HIGH);
      digitalWrite( SR, HIGH);
      digitalWrite( x, HIGH);  
      }
      else{
        digitalWrite( SR, LOW);
        digitalWrite( BF, HIGH);
        digitalWrite( x, HIGH);
    }
    }
   }
   

else {
  digitalWrite( BF,LOW);
  
  if(down==HIGH&&up==LOW&&mastf==LOW&&mastb==LOW&&liftb==LOW&&liftf==LOW&&tiltf==LOW&&tiltb==LOW&&cylif==LOW&&cylib==LOW){////////////////////////////////////////////////////down+right+left+safty
    
    if(left==HIGH&&right==LOW){//check stearing left button & other buttons states
      digitalWrite( BB,HIGH);
      digitalWrite( SL,HIGH);
      digitalWrite( x, HIGH);
    }
    else{
      digitalWrite( SL,LOW);
      
      if(right==HIGH&&left==LOW){//check stearing right button & other buttons states
      digitalWrite( BB,HIGH);
      digitalWrite( SR,HIGH);
      digitalWrite( x, HIGH);
      }
      else{
         digitalWrite( SR,LOW);
         digitalWrite( BB,HIGH);
         digitalWrite( x, HIGH);
       }
      }
    }
  
  else {
    digitalWrite( BB,LOW);
    
     //////////////////////check stearing right button & other buttons states
      
    if(right==HIGH&&up==LOW&&down==LOW&&mastf==LOW&&mastb==LOW&&liftb==LOW&&liftf==LOW&&tiltf==LOW&&tiltb==LOW&&cylif==LOW&&cylib==LOW&&left==LOW){       
      digitalWrite( SR,HIGH); 
      digitalWrite( x, HIGH);
    }
    else{
        digitalWrite( SR,LOW); 

//////////////////////check stearing left button & other buttons states
        if(left==HIGH&&up==LOW&&down==LOW&&mastf==LOW&&mastb==LOW&&liftb==LOW&&liftf==LOW&&tiltf==LOW&&tiltb==LOW&&cylif==LOW&&cylib==LOW&&right==LOW){
      digitalWrite( x, HIGH);
      digitalWrite( SL,HIGH);
        }
        else{
          digitalWrite( SL,LOW);
    
      ////////////////////check mast forward button & other buttons states
if(mastf==HIGH&&up==LOW&&down==LOW&&left==LOW&&mastb==LOW&&liftb==LOW&&liftf==LOW&&tiltf==LOW&&tiltb==LOW&&cylif==LOW&&cylib==LOW&&right==LOW){
  digitalWrite(MF,HIGH);
  digitalWrite( x, HIGH);
 }
else{
  digitalWrite(MF,LOW);
  ////////////////////check mast backward button & other buttons states
  if(mastb==HIGH&&up==LOW&&down==LOW&&left==LOW&&mastf==LOW&&liftb==LOW&&liftf==LOW&&tiltf==LOW&&tiltb==LOW&&cylif==LOW&&cylib==LOW&&right==LOW){
      digitalWrite(MB,HIGH);
      digitalWrite( x, HIGH);
    }
     else  {
   digitalWrite(MB,LOW);
if(tiltb==HIGH&&up==LOW&&down==LOW&&left==LOW&&mastb==LOW&&liftb==LOW&&liftf==LOW&&tiltf==LOW&&mastf==LOW&&cylif==LOW&&cylib==LOW&&right==LOW){//check tillting backward button & other buttons states
       if (Sensor_Read==LOW){
         digitalWrite( Sensor_Action,HIGH);
       if(Help_Read==1){
         digitalWrite(Help_Button,HIGH);
         digitalWrite(x,HIGH);
         }
        else{  
    digitalWrite(Help_Button, 0);
     digitalWrite(x,0);
        }
  }
else{
     digitalWrite( Sensor_Action,0);
     digitalWrite(x,HIGH);
     digitalWrite(TB,HIGH); 
        }
    }
    else{
      digitalWrite(TB,LOW);

////////////////////check tillting forward button & other buttons states
  if(tiltf==HIGH&&up==LOW&&down==LOW&&left==LOW&&mastb==LOW&&liftb==LOW&&liftf==LOW&&tiltb==LOW&&mastf==LOW&&cylif==LOW&&cylib==LOW&&right==LOW){
      digitalWrite( TF,HIGH);
      digitalWrite( x, HIGH);  
  }
  else{
    digitalWrite(TF,LOW); 
  
    if(liftb==HIGH&&up==LOW&&down==LOW&&left==LOW&&mastb==LOW&&tiltf==LOW&&liftf==LOW&&tiltb==LOW&&mastf==LOW&&cylif==LOW&&cylib==LOW&&right==LOW){/////////////check lift down button & other buttons states
     digitalWrite( x, HIGH);
     digitalWrite(LB,HIGH);
    }
   else{
    digitalWrite(LB,LOW);

    ///////////////////////////////////////////////check lift up button & other buttons states
  if(liftf==HIGH&&up==LOW&&down==LOW&&left==LOW&&mastb==LOW&&tiltf==LOW&&liftb==LOW&&tiltb==LOW&&mastf==LOW&&cylif==LOW&&cylib==LOW&&right==LOW){
      digitalWrite( x, HIGH); 
      digitalWrite(LF,HIGH);
    }
  else  {
      digitalWrite(LF,LOW);
     
   if(cylif==HIGH&&up==LOW&&down==LOW&&left==LOW&&mastb==LOW&&tiltf==LOW&&liftf==LOW&&tiltb==LOW&&mastf==LOW&&liftb==LOW&&cylib==LOW&&right==LOW){//////////////////////////////////check cylinder forward button & other buttons states
         digitalWrite(CF,HIGH);
         digitalWrite( x, HIGH);
        }
  else{

digitalWrite(CF,LOW);

  if(cylib==HIGH&&up==LOW&&down==LOW&&left==LOW&&mastb==LOW&&tiltf==LOW&&liftf==LOW&&tiltb==LOW&&mastf==LOW&&liftb==LOW&&cylif==LOW&&right==LOW){//////////////////////////////////check cylinder backward button & other buttons states
      digitalWrite(CB,HIGH);
      digitalWrite( x, HIGH);
  }
else  {
  digitalWrite(CB,LOW);
  digitalWrite( x, LOW);
}        
}   
    }
  }
  }
} 
}          
    }
  }
}          }        }
delay(50); 
}

void Mid_F (){  
  
  int midfState = digitalRead(MID_JOINT_F);
  if(midfState == 1 && lastmidfState == 0)    //if button is pressed and was released last change
    {
      toggleState1 =! toggleState1;                 //toggle the LED state
      digitalWrite(mid_joint_f, toggleState1);
      lastmidfState = 1;    //record the lastButtonState
    }  
    if(midfState == 0 && lastmidfState == 1)    //if button is not pressed, and was pressed last change
    {
      lastmidfState = 0;    //record the lastButtonState
    } 
  }
  
void Mid_B (){ 
  
  int midbState = digitalRead(MID_JOINT_B);
  if(midbState == 1 && lastmidbState == 0)    //if button is pressed and was released last change
    {
      toggleState2 =! toggleState2;                 //toggle the LED state
      digitalWrite(mid_joint_b, toggleState2);
      lastmidbState = 1;    //record the lastButtonState
    }  
    if(midbState == 0 && lastmidbState == 1)    //if button is not pressed, and was pressed last change
    {
      lastmidbState = 0;    //record the lastButtonState
    }  
  }
  
   
  
void Forward (){ 
  
  int forwardState = digitalRead(FORWARD);
  if(forwardState == 1 && lastforwardState == 0)    //if button is pressed and was released last change
    {
      toggleState3 =! toggleState3;                 //toggle the LED state
      digitalWrite(forward, toggleState3);
      lastforwardState = 1;    //record the lastButtonState
    }  
    if(forwardState == 0 && lastforwardState == 1)    //if button is not pressed, and was pressed last change
    {
      lastforwardState = 0;    //record the lastButtonState
    }  
  } 
  
void Backward (){
  
  int backwardState = digitalRead(BACKWARD);
  if(backwardState == 1 && lastbackwardState == 0)    //if button is pressed and was released last change
    {
      toggleState4 =! toggleState4;                 //toggle the LED state
      digitalWrite(backward, toggleState4);
      lastbackwardState = 1;    //record the lastButtonState
    }  
    if(backwardState == 0 && lastbackwardState == 1)    //if button is not pressed, and was pressed last change
    {
      lastbackwardState = 0;    //record the lastButtonState
    }  
  } 
  
void SteeringLeft (){
    
  int strleftState = digitalRead(STR_LEFT);
  if(strleftState == 1 && laststrleftState == 0)    //if button is pressed and was released last change
    {
      toggleState8 =! toggleState8;                 //toggle the LED state
      digitalWrite(str_left, toggleState8);
      laststrleftState = 1;    //record the lastButtonState
    }  
    if(strleftState == 0 && laststrleftState == 1)    //if button is not pressed, and was pressed last change
    {
      laststrleftState = 0;    //record the lastButtonState
    }        
  }
  
void SteeringRight (){
    
  int strrightState = digitalRead(STR_RIGHT);
  if(strrightState == 1 && laststrrightState == 0)    //if button is pressed and was released last change
    {
      toggleState9 =! toggleState9;                 //toggle the LED state
      digitalWrite(str_right, toggleState9);
      laststrrightState = 1;    //record the lastButtonState
    }  
    if(strrightState == 0 && laststrrightState == 1)    //if button is not pressed, and was pressed last change
    {
      laststrrightState = 0;    //record the lastButtonState
    }        
  }  

void Lift_Up (){ 
  
  int liftupState = digitalRead(LIFT_UP);
  if(liftupState == 1 && lastliftupState == 0)    //if button is pressed and was released last change
    {
      toggleState5 =! toggleState5;                 //toggle the LED state
      digitalWrite(Lift_up, toggleState5);
      lastliftupState = 1;    //record the lastButtonState
    }  
    if(liftupState == 0 && lastliftupState == 1)    //if button is not pressed, and was pressed last change
    {
      lastliftupState = 0;    //record the lastButtonState
    }  
  } 
  
void Lift_Down (){  
  int liftdownState = digitalRead(LIFT_DOWN);
  if(liftdownState == 1 && lastliftdownState == 0)    //if button is pressed and was released last change
    {
      toggleState6 =! toggleState6;                 //toggle the LED state
      digitalWrite(Lift_down, toggleState6);
      lastliftdownState = 1;    //record the lastButtonState
    }  
    if(liftdownState == 0 && lastliftdownState == 1)    //if button is not pressed, and was pressed last change
    {
      lastliftdownState = 0;    //record the lastButtonState
    }  
  }  
  
void Tilt_Up (){  
  int tiltupState  = digitalRead(TILT_UP);
  if(tiltupState == 1 && lasttiltupState == 0)    //if button is pressed and was released last change
    {
      toggleState10 =! toggleState10;                 //toggle the LED state
      digitalWrite(tilt_up, toggleState10);
      lasttiltupState = 1;    //record the lastButtonState
    }  
    if(tiltupState == 0 && lasttiltupState == 1)    //if button is not pressed, and was pressed last change
    {
      lasttiltupState = 0;    //record the lastButtonState
    }  
  }
  
void Tilt_Down (){  
  int tiltdownState = digitalRead(TILT_DOWN);
  if(tiltdownState == 1 && lasttiltdownState == 0)    //if button is pressed and was released last change
    {
      toggleState11 =! toggleState11;                 //toggle the LED state
      digitalWrite(tilt_down, toggleState11);
      lasttiltdownState = 1;    //record the lastButtonState
    }  
    if(tiltdownState == 0 && lasttiltdownState == 1)    //if button is not pressed, and was pressed last change
    {
      lasttiltdownState = 0;    //record the lastButtonState
    }  
  }
  
void Mast_F (){  
  int mastfState = digitalRead(MAST_F);
  if(mastfState == 1 && lastmastfState == 0)    //if button is pressed and was released last change
    {
      toggleState12 =! toggleState12;                 //toggle the LED state
      digitalWrite(mast_f, toggleState12);
      lastmastfState = 1;    //record the lastButtonState
    }  
    if(mastfState == 0 && lastmastfState == 1)    //if button is not pressed, and was pressed last change
    {
      lastmastfState = 0;    //record the lastButtonState
    }  
  }
  
void Mast_B (){  
  int mastbState = digitalRead(MAST_B);
  if(mastbState == 1 && lastmastbState == 0)    //if button is pressed and was released last change
    {
      toggleState13 =! toggleState13;                 //toggle the LED state
      digitalWrite(mast_b, toggleState13);
      lastmastbState = 1;    //record the lastButtonState
    }  
    if(mastbState == 0 && lastmastbState == 1)    //if button is not pressed, and was pressed last change
    {
      lastmastbState = 0;    //record the lastButtonState
    }  
  }

//Safety_Sector 

void safety1(){  
       digitalWrite(forward,LOW);
       digitalWrite(backward,LOW);
       digitalWrite(str_right,LOW);
       digitalWrite(str_left,LOW);       
  }
  
void safety2(){
       digitalWrite(mid_joint_f,LOW);
       digitalWrite(mid_joint_b,LOW);
       digitalWrite(Lift_up,LOW);
       digitalWrite(Lift_down,LOW);
       digitalWrite(tilt_up,LOW);
       digitalWrite(tilt_down,LOW);
       digitalWrite(mast_f,LOW);
       digitalWrite(mast_b,LOW);       
  }
  
void safety3(){  
  int b = digitalRead(mid_joint_f);
  int c = digitalRead(mid_joint_b);
  int d = digitalRead(forward);
  int e = digitalRead(backward);
  int f = digitalRead(Lift_up);
  int g = digitalRead(Lift_down);
  int h = digitalRead(motor);
  int k = digitalRead(str_left);
  int l = digitalRead(str_right);
  int m = digitalRead(tilt_up);
  int n = digitalRead(tilt_down);
  int o = digitalRead(mast_f);
  int p = digitalRead(mast_b);
   
if( b == LOW && c == LOW && d == LOW && e == LOW && f == LOW && g == LOW && h == LOW && k == LOW && l == LOW && m == LOW && n == LOW && o == LOW && p == LOW ){
digitalWrite(compound_valve , LOW);
}

if ( o == HIGH && p == HIGH ){
    digitalWrite(mast_f,LOW);
    digitalWrite(mast_b,LOW);
}

if ( b == HIGH && c == HIGH ){
    digitalWrite(mid_joint_f,LOW);
    digitalWrite(mid_joint_b,LOW);
}

}  
 
