#include "../../controller.hpp"


/** @brief specific prototype include file for sony specific
 *  information. likely unnecessary other than for support of special
 *  technology present on sony-devices. 
 * 
 * 
 */
class DualSense :controller
{
protected:
    string name;
    int num_hats;
    int num_buttons;
    int num_axes;
    SDL_Joystick * joyStick_;
    SDL_Event event;
    ros::NodeHandle * nh_;
    
public:
    ros::Publisher eventPublisher;
    DualSense(SDL_Joystick *, ros::NodeHandle *);
    void publishControllerEvents();
    ~DualSense();
};

