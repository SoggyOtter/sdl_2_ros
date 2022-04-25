#include <ros/ros.h>
#include "DualSense.hpp"
#include <signal.h>


void setup();
void shutdown();
int main(int, char**);

void setup(){
    SDL_Quit();
    SDL_SetHint(SDL_HINT_NO_SIGNAL_HANDLERS, "1"); //so Ctrl-C still works
	SDL_Init(SDL_INIT_JOYSTICK);
    SDL_Init(SDL_INIT_EVERYTHING);

    int numJoysticks = SDL_NumJoysticks();
    if (numJoysticks <1){
        printf("Could not find a joystick\n");
        shutdown();
    }
    else{
        printf("Found %d joysticks", numJoysticks);
    }

}

void shutdown(){
    printf("Shutting down SDL and exiting");
    SDL_Quit();
    std::_Exit(0);
}


int main(int argc, char* argv[]){
    
    //Spawn ros node-handler//
    setup();
    ros::init(argc, argv, "DualSenseInputNode", 0);
    ros::NodeHandle nh;
    ros::Rate rate(50); //50hz

    SDL_Joystick * joy = SDL_JoystickOpen(0);

    //instantiate DualSense Publisher
    DualSense ds_publisher(joy, &nh);
    
    //SDL_Event event; will need to 
    //Publish at rate
    while(true){
        ds_publisher.publishControllerEvents();
        rate.sleep();
        /*
        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                cout<<"WHAT"<<endl;
                std::_Exit(1);
            }
            else cout<<event.type<<endl;

        }
        */
    }
    
    return(0);
}