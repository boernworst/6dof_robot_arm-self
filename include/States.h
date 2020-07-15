#ifndef STATES_H
#define STATES_H

/*
    States for serial communication and state tests
        ::isArrivedAxis[6]: is used to test if each individual axis has reached the setpoint
        ::isArrived: is used to store the state in which all axis have reached the setpoint
        ::isEmpty: is used to store the state in which the buffer is empty
        ::firstPositionReached: is used to skip the first serial communication loop for setting the setpoint
*/
struct States{
    bool isArrivedAxis[6] = {false};
    bool isArrived = true;
    bool isEmptyBuffer = false;
    bool firstPositionReached = false;
}s;

#endif