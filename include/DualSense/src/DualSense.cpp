#include "../include/DualSense.hpp"
#include "sdl_2_ros/ControllerMsg.h"
#include <cmath>

#define deadzoneThreshold 5000

using namespace sdl_2_ros;
DualSense::DualSense(SDL_Joystick *joystick, ros::NodeHandle * nh){
    name = SDL_JoystickName(joystick);
    num_hats = SDL_JoystickNumHats(joystick);
    num_buttons = SDL_JoystickNumButtons(joystick);
    num_axes = SDL_JoystickNumAxes(joystick);


    joyStick_ = joystick;
    nh_ = nh;
    eventPublisher = nh_->advertise<ControllerMsg>("sdl_2_ros/DualSense_input", 10 );

    cout<<"Success, Created an EventPublisher with the following characteristics:"<<endl
        <<"Name: "<<name<<endl
        <<"Number of Hats: "<<num_hats<<endl
        <<"Number of Axes: "<<num_axes<<endl
        <<"Number of Buttons: "<<num_buttons<<endl;

}

void DualSense::publishControllerEvents(){
    ControllerMsg message;
    message.axisVals.resize(num_axes);
    message.buttonVals.resize(num_buttons);
    message.hatVals.resize(num_hats);
    message.controllerType = message.Type_DualSense;
    message.header.stamp = ros::Time::now();
    if(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
                cout<<"Exiting now"<<endl;
                std::_Exit(1);
            }
        else if(event.jdevice.type == SDL_JOYDEVICEREMOVED){
            std::_Exit(1);
        }         
        //Get Current JoystickVals
        
        //GetAxesValues here 
        //TODO:: Do preprossing and pass along %
        for(int i = 0; i < num_axes; i++){
            int joyStickRawVals = SDL_JoystickGetAxis(joyStick_,i);
            double joyStickPostProcessing = 0.0;
            if(i != 3 && i !=4){
                joyStickPostProcessing = (abs(joyStickRawVals) > deadzoneThreshold)? (float)joyStickRawVals/32000  :0.0;
            }
            else{
                int offset = 32768;
                joyStickPostProcessing = abs( (double) ((joyStickRawVals > 0)? (abs(joyStickRawVals) + offset):(abs(joyStickRawVals) - offset) ) /(32000 * 2)) ;
            }

            message.axisVals[i] = joyStickPostProcessing;
        }

        for( int b = 0; b < num_buttons; b++){
            message.buttonVals[b] = SDL_JoystickGetButton(joyStick_,b);
        }
        //get HatVals here 
        //TODO:: Resize hat section to one and probably just pass the enum value
        // I didn't do this because i don't know how mutex like hatvals are
        // also swap message.hatVals to type uint8 or int32
        message.hatVals[0] = SDL_JoystickGetHat(joyStick_,0);

    }
    eventPublisher.publish(message);

}

DualSense::~DualSense(){
   
    return;
}