// File:          my_controller_DRONE-27.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/LED.hpp>
#include <webots/Keyboard.hpp>
#include <iostream>


#define TIME_STEP 32
// All the webots classes are defined in the "webots" namespace
using namespace webots;
using namespace std;

class HYBRIDE_DRONE {
  
  private:
    Robot *DRONE;
    Keyboard *keyboard;
    LED *led[2];
    Motor *Hinge_BODY[4]; 
    Motor *Slider_BODY[4]; 
    Motor *Wheel_BODY[4];
    Motor *Prop_BODY[4];
    const string Hinge_body[4] = {"MOTOR_FL1","MOTOR_RL1","MOTOR_FR1","MOTOR_RR1"};
    const string Slider_body[4] = {"MOTOR_SFL","MOTOR_SRL","MOTOR_SFR","MOTOR_SRR"};
    const string Wheel_body[4] = {"WHEEL_1","WHEEL_2","WHEEL_3","WHEEL_4"};
    const string Prop_body[4] = {"PROP_1","PROP_2","PROP_3","PROP_4"};
    int key;
    inline static bool L_ONE = false;
    
  public:
    HYBRIDE_DRONE(){
      DRONE = new Robot();
      keyboard = DRONE->getKeyboard();
      keyboard->enable(TIME_STEP);
      led[0] = DRONE->getLED("LED_0");
      led[1] = DRONE->getLED("LED_1");
      for (int m1=0;m1<4;m1++){
        Hinge_BODY[m1] = DRONE->getMotor(Hinge_body[m1]);
        Hinge_BODY[m1]->setVelocity(1);
        Hinge_BODY[m1]->setPosition(0);
        Slider_BODY[m1] = DRONE->getMotor(Slider_body[m1]);
        Slider_BODY[m1]->setVelocity(1);
        Slider_BODY[m1]->setPosition(0);
        Wheel_BODY[m1] = DRONE->getMotor(Wheel_body[m1]);
        Wheel_BODY[m1]->setVelocity(0);
        Wheel_BODY[m1]->setPosition(INFINITY);
        Prop_BODY[m1] = DRONE->getMotor(Prop_body[m1]);
        Prop_BODY[m1]->setVelocity(4.4);
        Prop_BODY[m1]->setPosition(INFINITY);
      };
    }
    Robot* getRobot(){
      return DRONE;
    }
    void DELAY(int TIME){
      int STEP = (TIME/TIME_STEP);
         for (int i = STEP; i>0; i--){
           if (DRONE->step(TIME_STEP) == -1){
           break;
           }
         };
    }
    void LED_start(){
      led[0]->set(1);
      led[1]->set(1);
    }
    void LED_stop(){
      led[1]->set(0);
      led[0]->set(0);
    }
    void Key(){
      key = keyboard->getKey();
      DELAY(80);
      if (key == -1) return;
    }
    void Key_RESET(){
      key = -1;
      DELAY(50);
    }
    void press(){
      if (key != -1){
          cout << "Pressed KEY : " << (char)key << endl;
      };
    }
    void LED_CONTROL(){
      while (DRONE->step(TIME_STEP) != -1){
        Key();
        if (key == '0'){
          LED_stop();
          Key_RESET();
          break;
        }
        else if (key == '1'){
          LED_start();
          Key_RESET();
          break;
        }
      };
    }
    void HINGE_CONTROLS(){
      while (DRONE->step(TIME_STEP) != -1){
       Key();
        if(!L_ONE){
                cout <<" - Press : 0 to return - \n"
                << endl;
                L_ONE = true;
          }
        switch(key){
          case '1':
            cout << " ~~~ Controls ~~~ \n"
                      <<" - Press : 1 to set Position UP - \n"
                      <<" - Press : 2 to set Position DOWN - \n"
                      <<" - Press : 3 to to set Position DEFAULT - \n"
                      << endl;
                      L_ONE = false;
             DELAY(50);
            Key_RESET();
            HINGE_MOVE_ALL();
          break;
          case '2':
            cout << " ~~~ Controls ~~~ \n"
                      <<" - Press : 1 to set Position UP - \n"
                      <<" - Press : 2 to set Position DOWN - \n"
                      <<" - Press : 3 to to set Position DEFAULT - \n"
                      << endl;
                      L_ONE = false;
             DELAY(50);
            Key_RESET();
            HINGE_MOVE_BOTH_LEFT();
          break;
          case '3':
              cout << " ~~~ Controls ~~~ \n"
                      <<" - Press : 1 to set Position UP - \n"
                      <<" - Press : 2 to set Position DOWN - \n"
                      <<" - Press : 3 to to set Position DEFAULT - \n"
                      << endl;
                      L_ONE = false;
             DELAY(50);
            Key_RESET();
            HINGE_MOVE_BOTH_RIGHT();
          break;
          case '4':
              cout << " ~~~ Controls ~~~ \n"
                      <<" - Press : 1 to set Position UP - \n"
                      <<" - Press : 2 to set Position DOWN - \n"
                      <<" - Press : 3 to to set Position DEFAULT - \n"
                      << endl;
                      L_ONE = false;
             DELAY(50);
            Key_RESET();
            HINGE_MOVE_BOTH_BACK();
          break;
          case '5':
           cout << " ~~~ Controls ~~~ \n"
                      <<" - Press : 1 to set Position UP - \n"
                      <<" - Press : 2 to set Position DOWN - \n"
                      <<" - Press : 3 to to set Position DEFAULT - \n"
                      << endl;
                      L_ONE = false;
             DELAY(50);
            Key_RESET();
            HINGE_MOVE_BOTH_FRONT();
          break;
          case '6':
          break;
          case '0':
              L_ONE = false;
              return;
          break;
        };
      };
    }
    void HINGE_MOVE_ALL(){
       while (DRONE->step(TIME_STEP) != -1){
       Key();
       if(!L_ONE){
       cout <<" - Press : 0 to return - \n"
                 << endl;
       DELAY(5);
         L_ONE = true;
         }
           if(key == '1'){
            for(int i = 0; i<4; i++){
              Key_RESET();
               Hinge_BODY[i]->setVelocity(4);
               Hinge_BODY[i]->setControlPID(2,0,0.5);
               Hinge_BODY[i]->setAvailableTorque(200);
              if(i == 0 || i == 1)
               Hinge_BODY[i]->setPosition(0.5);
              else
               Hinge_BODY[i]->setPosition(-0.5);
             };
             L_ONE = false;
             break;
           }
           else if(key == '2'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Hinge_BODY[i]->setVelocity(4);
               Hinge_BODY[i]->setControlPID(2,0,0.5);
               Hinge_BODY[i]->setAvailableTorque(200);
              if(i == 0 || i == 1)
               Hinge_BODY[i]->setPosition(-1.07);
              else
               Hinge_BODY[i]->setPosition(1.07);
             };
             L_ONE = false;
             break;
           }
           else if(key == '3'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Hinge_BODY[i]->setVelocity(4);
               Hinge_BODY[i]->setControlPID(2,0,0.25);
               Hinge_BODY[i]->setAvailableTorque(100);
               Hinge_BODY[i]->setPosition(0);
             };
             L_ONE = false;
             break;
           }
           else if(key == '0'){
             Key_RESET();
             L_ONE = false;
             break;
           }
       };
    }
        void HINGE_MOVE_BOTH_LEFT(){
       while (DRONE->step(TIME_STEP) != -1){
       Key();
       if(!L_ONE){
       cout <<" - Press : 0 to return - \n"
                 << endl;
       DELAY(5);
         L_ONE = true;
         }
           if(key == '1'){
            for(int i = 0; i<4; i++){
              Key_RESET();
               Hinge_BODY[i]->setVelocity(4);
               Hinge_BODY[i]->setControlPID(2,0,0.5);
               Hinge_BODY[i]->setAvailableTorque(200);
              if(i == 0 || i == 1){
               Hinge_BODY[i]->setPosition(0.5);
               }
             };
             L_ONE = false;
             break;
           }
           else if(key == '2'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Hinge_BODY[i]->setVelocity(4);
               Hinge_BODY[i]->setControlPID(2,0,0.5);
               Hinge_BODY[i]->setAvailableTorque(200);
              if(i == 0 || i == 1)
               Hinge_BODY[i]->setPosition(-1.07);
             };
             L_ONE = false;
             break;
           }
           else if(key == '3'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Hinge_BODY[i]->setVelocity(4);
               Hinge_BODY[i]->setControlPID(2,0,0.25);
               Hinge_BODY[i]->setAvailableTorque(100);
              if(i == 0 || i == 1)
               Hinge_BODY[i]->setPosition(0);
             };
             L_ONE = false;
             break;
           }
           else if(key == '0'){
             Key_RESET();
             L_ONE = false;
             break;
           }
       };
    }
    void HINGE_MOVE_BOTH_RIGHT(){
       while (DRONE->step(TIME_STEP) != -1){
       Key();
       if(!L_ONE){
       cout <<" - Press : 0 to return - \n"
                 << endl;
       DELAY(5);
         L_ONE = true;
         }
           if(key == '1'){
            for(int i = 0; i<4; i++){
              Key_RESET();
               Hinge_BODY[i]->setVelocity(4);
               Hinge_BODY[i]->setControlPID(2,0,0.5);
               Hinge_BODY[i]->setAvailableTorque(200);
              if(i == 3 || i == 2){
               Hinge_BODY[i]->setPosition(-0.5);
               }
             };
             L_ONE = false;
             break;
           }
           else if(key == '2'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Hinge_BODY[i]->setVelocity(4);
               Hinge_BODY[i]->setControlPID(2,0,0.5);
               Hinge_BODY[i]->setAvailableTorque(200);
              if(i == 3 || i == 2)
               Hinge_BODY[i]->setPosition(1.07);
             };
             L_ONE = false;
             break;
           }
           else if(key == '3'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Hinge_BODY[i]->setVelocity(4);
               Hinge_BODY[i]->setControlPID(2,0,0.25);
               Hinge_BODY[i]->setAvailableTorque(100);
              if(i == 2 || i == 3)
               Hinge_BODY[i]->setPosition(0);
             };
             L_ONE = false;
             break;
           }
           else if(key == '0'){
             Key_RESET();
             L_ONE = false;
             break;
           }
       };
    }
       void HINGE_MOVE_BOTH_BACK(){
       while (DRONE->step(TIME_STEP) != -1){
       Key();
       if(!L_ONE){
       cout <<" - Press : 0 to return - \n"
                 << endl;
       DELAY(5);
         L_ONE = true;
         }
           if(key == '1'){
            for(int i = 0; i<4; i++){
              Key_RESET();
               Hinge_BODY[i]->setVelocity(4);
               Hinge_BODY[i]->setControlPID(2,0,0.5);
               Hinge_BODY[i]->setAvailableTorque(200);
              if(i == 1)
               Hinge_BODY[i]->setPosition(0.5);
              else if (i == 3)
               Hinge_BODY[i]->setPosition(-0.5);
             };
             L_ONE = false;
             break;
           }
           else if(key == '2'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Hinge_BODY[i]->setVelocity(4);
               Hinge_BODY[i]->setControlPID(2,0,0.5);
               Hinge_BODY[i]->setAvailableTorque(200);
              if( i == 1)
               Hinge_BODY[i]->setPosition(-1.07);
              else if (i == 3)
               Hinge_BODY[i]->setPosition(1.07);
             };
             L_ONE = false;
             break;
           }
           else if(key == '3'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Hinge_BODY[i]->setVelocity(4);
               Hinge_BODY[i]->setControlPID(2,0,0.25);
               Hinge_BODY[i]->setAvailableTorque(100);
               if(i==1 || i==3)
               Hinge_BODY[i]->setPosition(0);
             };
             L_ONE = false;
             break;
           }
           else if(key == '0'){
             Key_RESET();
             L_ONE = false;
             break;
           }
       };
    }
    void HINGE_MOVE_BOTH_FRONT(){
       while (DRONE->step(TIME_STEP) != -1){
       Key();
       if(!L_ONE){
       cout <<" - Press : 0 to return - \n"
                 << endl;
       DELAY(5);
         L_ONE = true;
         }
           if(key == '1'){
            for(int i = 0; i<4; i++){
              Key_RESET();
               Hinge_BODY[i]->setVelocity(4);
               Hinge_BODY[i]->setControlPID(2,0,0.5);
               Hinge_BODY[i]->setAvailableTorque(200);
              if(i == 0)
               Hinge_BODY[i]->setPosition(0.5);
              else if (i == 2)
               Hinge_BODY[i]->setPosition(-0.5);
             };
             L_ONE = false;
             break;
           }
           else if(key == '2'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Hinge_BODY[i]->setVelocity(4);
               Hinge_BODY[i]->setControlPID(2,0,0.5);
               Hinge_BODY[i]->setAvailableTorque(200);
              if( i == 0)
               Hinge_BODY[i]->setPosition(-1.07);
              else if (i == 2)
               Hinge_BODY[i]->setPosition(1.07);
             };
             L_ONE = false;
             break;
           }
           else if(key == '3'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Hinge_BODY[i]->setVelocity(4);
               Hinge_BODY[i]->setControlPID(2,0,0.25);
               Hinge_BODY[i]->setAvailableTorque(100);
               if(i==0 || i==2)
               Hinge_BODY[i]->setPosition(0);
             };
             L_ONE = false;
             break;
           }
           else if(key == '0'){
             Key_RESET();
             L_ONE = false;
             break;
           }
       };
    }
    void SLIDER_MOVE_ALL(){
       while (DRONE->step(TIME_STEP) != -1){
       Key();
       if(!L_ONE){
       cout <<" - Press : 0 to return - \n"
                 << endl;
       DELAY(5);
         L_ONE = true;
         }
           if(key == '1'){
            for(int i = 0; i<4; i++){
              Key_RESET();
               Slider_BODY[i]->setVelocity(4);
               Slider_BODY[i]->setControlPID(2,0,0.5);
               Slider_BODY[i]->setAvailableForce(200);
              if(i == 0 || i == 1)
               Slider_BODY[i]->setPosition(-1);
              else
               Slider_BODY[i]->setPosition(-1);
             };
             L_ONE = false;
             break;
           }
           else if(key == '2'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Slider_BODY[i]->setVelocity(4);
               Slider_BODY[i]->setControlPID(2,0,0.5);
               Slider_BODY[i]->setAvailableForce(200);
              if(i == 0 || i == 1)
               Slider_BODY[i]->setPosition(1);
              else
              Slider_BODY[i]->setPosition(1);
             };
             L_ONE = false;
             break;
           }
           else if(key == '3'){
             for(int i = 0; i<4; i++){
              Key_RESET();
              Slider_BODY[i]->setVelocity(4);
               Slider_BODY[i]->setControlPID(2,0,0.25);
               Slider_BODY[i]->setAvailableForce(100);
               Slider_BODY[i]->setPosition(0);
             };
             L_ONE = false;
             break;
           }
           else if(key == '0'){
             Key_RESET();
             L_ONE = false;
             break;
           }
       };
    }
    void SLIDER_MOVE_BOTH_LEFT(){
       while (DRONE->step(TIME_STEP) != -1){
       Key();
       if(!L_ONE){
       cout <<" - Press : 0 to return - \n"
                 << endl;
       DELAY(5);
         L_ONE = true;
         }
           if(key == '1'){
            for(int i = 0; i<4; i++){
              Key_RESET();
               Slider_BODY[i]->setVelocity(4);
               Slider_BODY[i]->setControlPID(2,0,0.5);
               Slider_BODY[i]->setAvailableForce(200);
              if(i == 0 || i == 1){
               Slider_BODY[i]->setPosition(1);
               }
             };
             L_ONE = false;
             break;
           }
           else if(key == '2'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Slider_BODY[i]->setVelocity(4);
               Slider_BODY[i]->setControlPID(2,0,0.5);
               Slider_BODY[i]->setAvailableForce(200);
              if(i == 0 || i == 1)
               Slider_BODY[i]->setPosition(-1);
             };
             L_ONE = false;
             break;
           }
           else if(key == '3'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Slider_BODY[i]->setVelocity(4);
               Slider_BODY[i]->setControlPID(2,0,0.25);
               Slider_BODY[i]->setAvailableForce(100);
              if(i == 0 || i == 1)
               Slider_BODY[i]->setPosition(0);
             };
             L_ONE = false;
             break;
           }
           else if(key == '0'){
             Key_RESET();
             L_ONE = false;
             break;
           }
       };
    }
    void SLIDER_MOVE_BOTH_RIGHT(){
       while (DRONE->step(TIME_STEP) != -1){
       Key();
       if(!L_ONE){
       cout <<" - Press : 0 to return - \n"
                 << endl;
       DELAY(5);
         L_ONE = true;
         }
           if(key == '1'){
            for(int i = 0; i<4; i++){
              Key_RESET();
               Slider_BODY[i]->setVelocity(4);
               Slider_BODY[i]->setControlPID(2,0,0.5);
               Slider_BODY[i]->setAvailableForce(200);
              if(i == 3 || i == 2){
               Slider_BODY[i]->setPosition(-1);
               }
             };
             L_ONE = false;
             break;
           }
           else if(key == '2'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Slider_BODY[i]->setVelocity(4);
               Slider_BODY[i]->setControlPID(2,0,0.5);
               Slider_BODY[i]->setAvailableForce(200);
              if(i == 3 || i == 2)
               Slider_BODY[i]->setPosition(1);
             };
             L_ONE = false;
             break;
           }
           else if(key == '3'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Slider_BODY[i]->setVelocity(4);
               Slider_BODY[i]->setControlPID(2,0,0.25);
               Slider_BODY[i]->setAvailableForce(100);
              if(i == 2 || i == 3)
               Slider_BODY[i]->setPosition(0);
             };
             L_ONE = false;
             break;
           }
           else if(key == '0'){
             Key_RESET();
             L_ONE = false;
             break;
           }
       };
    }
       void SLIDER_MOVE_BOTH_BACK(){
       while (DRONE->step(TIME_STEP) != -1){
       Key();
       if(!L_ONE){
       cout <<" - Press : 0 to return - \n"
                 << endl;
       DELAY(5);
         L_ONE = true;
         }
           if(key == '1'){
            for(int i = 0; i<4; i++){
              Key_RESET();
               Slider_BODY[i]->setVelocity(4);
               Slider_BODY[i]->setControlPID(2,0,0.5);
               Slider_BODY[i]->setAvailableForce(200);
              if(i == 1)
               Slider_BODY[i]->setPosition(1);
              else if (i == 3)
               Slider_BODY[i]->setPosition(1);
             };
             L_ONE = false;
             break;
           }
           else if(key == '2'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Slider_BODY[i]->setVelocity(4);
               Slider_BODY[i]->setControlPID(2,0,0.5);
               Slider_BODY[i]->setAvailableForce(200);
              if( i == 1)
               Slider_BODY[i]->setPosition(-1);
              else if (i == 3)
               Slider_BODY[i]->setPosition(-1);
             };
             L_ONE = false;
             break;
           }
           else if(key == '3'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Slider_BODY[i]->setVelocity(4);
               Slider_BODY[i]->setControlPID(2,0,0.25);
               Slider_BODY[i]->setAvailableForce(100);
               if(i==1 || i==3)
               Slider_BODY[i]->setPosition(0);
             };
             L_ONE = false;
             break;
           }
           else if(key == '0'){
             Key_RESET();
             L_ONE = false;
             break;
           }
       };
    }
    void SLIDER_MOVE_BOTH_FRONT(){
       while (DRONE->step(TIME_STEP) != -1){
       Key();
       if(!L_ONE){
       cout <<" - Press : 0 to return - \n"
                 << endl;
       DELAY(5);
         L_ONE = true;
         }
           if(key == '1'){
            for(int i = 0; i<4; i++){
              Key_RESET();
               Slider_BODY[i]->setVelocity(4);
               Slider_BODY[i]->setControlPID(2,0,0.5);
               Slider_BODY[i]->setAvailableForce(200);
              if(i == 0)
               Slider_BODY[i]->setPosition(1);
              else if (i == 2)
               Slider_BODY[i]->setPosition(1);
             };
             L_ONE = false;
             break;
           }
           else if(key == '2'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Slider_BODY[i]->setVelocity(4);
               Slider_BODY[i]->setControlPID(2,0,0.5);
               Slider_BODY[i]->setAvailableForce(200);
              if( i == 0)
               Slider_BODY[i]->setPosition(-1);
              else if (i == 2)
               Slider_BODY[i]->setPosition(-1);
             };
             L_ONE = false;
             break;
           }
           else if(key == '3'){
             for(int i = 0; i<4; i++){
              Key_RESET();
               Slider_BODY[i]->setVelocity(4);
               Slider_BODY[i]->setControlPID(2,0,0.25);
               Slider_BODY[i]->setAvailableForce(100);
               if(i==0 || i==2)
               Slider_BODY[i]->setPosition(0);
             };
             L_ONE = false;
             break;
           }
           else if(key == '0'){
             Key_RESET();
             L_ONE = false;
             break;
           }
       };
    }
    void SLIDER_CONTROLS(){
      while (DRONE->step(TIME_STEP) != -1){
       Key();
        if(!L_ONE){
                cout <<" - Press : 0 to return - \n"
                << endl;
                L_ONE = true;
          }
        switch(key){
          case '1':
            cout << " ~~~ Controls ~~~ \n"
                      <<" - Press : 1 to set Position UP - \n"
                      <<" - Press : 2 to set Position DOWN - \n"
                      <<" - Press : 3 to to set Position DEFAULT - \n"
                      << endl;
                      L_ONE = false;
             DELAY(50);
            Key_RESET();
            SLIDER_MOVE_ALL();
          break;
          case '2':
            cout << " ~~~ Controls ~~~ \n"
                      <<" - Press : 1 to set Position UP - \n"
                      <<" - Press : 2 to set Position DOWN - \n"
                      <<" - Press : 3 to to set Position DEFAULT - \n"
                      << endl;
                      L_ONE = false;
             DELAY(50);
            Key_RESET();
            SLIDER_MOVE_BOTH_LEFT();
          break;
          case '3':
              cout << " ~~~ Controls ~~~ \n"
                      <<" - Press : 1 to set Position UP - \n"
                      <<" - Press : 2 to set Position DOWN - \n"
                      <<" - Press : 3 to to set Position DEFAULT - \n"
                      << endl;
                      L_ONE = false;
             DELAY(50);
            Key_RESET();
            SLIDER_MOVE_BOTH_RIGHT();
          break;
          case '4':
              cout << " ~~~ Controls ~~~ \n"
                      <<" - Press : 1 to set Position UP - \n"
                      <<" - Press : 2 to set Position DOWN - \n"
                      <<" - Press : 3 to to set Position DEFAULT - \n"
                      << endl;
                      L_ONE = false;
             DELAY(50);
            Key_RESET();
            SLIDER_MOVE_BOTH_BACK();
          break;
          case '5':
           cout << " ~~~ Controls ~~~ \n"
                      <<" - Press : 1 to set Position UP - \n"
                      <<" - Press : 2 to set Position DOWN - \n"
                      <<" - Press : 3 to to set Position DEFAULT - \n"
                      << endl;
                      L_ONE = false;
             DELAY(50);
            Key_RESET();
            SLIDER_MOVE_BOTH_FRONT();
          break;
          case '6':
          break;
          case '0':
              L_ONE = false;
              return;
          break;
        };
      };
    }
    void CONTROLS(){
     if (!L_ONE){
      cout <<" ~~~ Controls ~~~ \n"
             <<" - Press : 1 for LED Control - \n"
             <<" - Press : 2 for Hinge Control - \n"
             <<" - Press : 3 for Slider Control - \n"
             << endl; 
      L_ONE = true;
     }
      switch(key){
        case '1':
        cout <<" ~~~ Controls ~~~ \n"
               <<" - Press : 1 to turn ON LED - \n"
               <<" - Press : 0 to turn off LED - \n"
               << endl;
             L_ONE = false;
          Key_RESET();
          LED_CONTROL();
        break;
        case '2':
         cout <<" ~~~ Controls ~~~ \n"
                <<" - Press : 1 to move all Hinges - \n"
                <<" - Press : 2 to move both left Hinges - \n"
                <<" - Press : 3 to move both right Hinges - \n"
                <<" - Press : 4 to move both back Hinges - \n"
                <<" - Press : 5 to move both front Hinges - \n"
                <<" - Press : 6 to move both single Hinge - \n"
                << endl;
             L_ONE = false;
          Key_RESET();
          HINGE_CONTROLS();
        break;
        case '3':
            cout <<" ~~~ Controls ~~~ \n"
                <<" - Press : 1 to move all Slider - \n"
                <<" - Press : 2 to move both left Slider - \n"
                <<" - Press : 3 to move both right Slider - \n"
                <<" - Press : 4 to move both back Slider - \n"
                <<" - Press : 5 to move both front Slider - \n"
                <<" - Press : 6 to move both single Slider - \n"
                << endl;
             L_ONE = false;
          Key_RESET();
          SLIDER_CONTROLS();
        break;
      };
    }
};

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
  HYBRIDE_DRONE drone;
  Robot *robot = drone.getRobot();
  
  // create the Robot instance.

  // get the time step of the current world.
  int timeStep = (int)robot->getBasicTimeStep();
  

  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  //  Motor *motor = robot->getMotor("motorname");
  //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
  //  ds->enable(timeStep);

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  while (robot->step(timeStep) != -1) {
    // Read the sensors:
    // Enter here functions to read sensor data, like:
    //  double val = ds->getValue();
    
    drone.Key();
    drone.CONTROLS();

    // Process sensor data here.

    // Enter here functions to send actuator commands, like:
    //  motor->setPosition(10.0);
  };

  // Enter here exit cleanup code.

  delete robot;
  return 0;
}
