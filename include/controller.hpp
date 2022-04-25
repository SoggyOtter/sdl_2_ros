#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_config.h>
#include <iostream>
#include <ros/ros.h>


using namespace std;

class controller
{
protected:
    string name;
    int num_hats;
    int num_buttons;
    int num_axes;
    SDL_Joystick * stick;
    SDL_Event event;
    
public:
    ros::Publisher eventPublisher;
    void publishControllerEvents();
};
