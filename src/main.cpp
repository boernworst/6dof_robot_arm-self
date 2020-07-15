//Import libraries
#include <Arduino.h>
#include <AccelStepper.h>
#include <CircularBuffer.h>

//Include project specific headers
#include <States.h>
#include <PinDef.h>
#include <KinematicDef.h>
#include <KinematicFunctions.h>
#include <Position.h>
#include <Functions.h> //dependency: KinematicDef, struct state

Position homePos, demoPos1, demoPos2;
long timerStart;

//Declare a buffer with pointers to Position instances
CircularBuffer<Position*, 10> buffer;

void setup() {
  Serial.begin(115200);
  while(!Serial){
    //wait for Serial to connect
  }
  String output = "";

  initGPIO();
  initSteppers();
  enableJoints();
  
  //Declare home position
  homePos.setThetaPos(  0,
                        steps[1]*0.01,
                        steps[2]*0.01,
                        0,
                        0,
                        0);

  //Declare demo positions
  demoPos1.setThetaPos( 0,
                        steps[1]*1/2*0.9,
                        steps[2]*2/4*0.9,
                        0,
                        0,
                        steps[5]/4);

  demoPos2.setThetaPos( 0,
                        steps[1]*1/4,
                        steps[2]*1/4,
                        0,
                        0,
                        0);

  //Load address of positions into buffer
  buffer.push(&homePos);
  buffer.push(&demoPos1);
  buffer.push(&demoPos2);
  buffer.push(&homePos);

  //Print input into buffer to serial
  output = "Buffer loaded with theta positions:\n";
  for (int i=0; i<buffer.size(); i++){
    Position _pos = *buffer[i];

    output += "   " + String(i) + ":   {" + String(_pos.thetaPos[0]);
    for (int j=1; j<6; j++)
      output += "," + String(_pos.thetaPos[j]);
    output += "}\n";
  }
  Serial.println(output);

  timerStart = millis();
}



void loop() {
  String output;
  Position curPos;

  //Check if all steppers have reached target position and buffer is not empty
  s.isArrived = true; //assume true, unless condition not satisfied
  for (int i=0; i<6; i++){
    s.isArrivedAxis[i] = false; //set as false unless stepper arrived
    //Switch state if individual stepper has reached target position
    if(ptrSteppers[i]->distanceToGo() == 0)
      s.isArrivedAxis[i] = true;

    //If any stepper is not yet arrived, flag collective arrival as false
    if(!s.isArrivedAxis[i])
      s.isArrived = false;
  }

  //Sent result of movement over Serial
  //Check if buffer is not empty, if yes perform final message and disable joints
  //If buffer is not empty, get and set next position
  if (s.isArrived && !s.isEmptyBuffer){

    //Sent serial communication when target position is reached.
    //Skip first iteration, since this is loading the first position.
    if (s.firstPositionReached) {
      long time = millis() - timerStart;
      timerStart = millis(); //start timer for next movement
      output = "Reached target position in " + String(time) + " milliseconds.\n";
      Serial.println(output);
    }
    s.firstPositionReached = true; //skip first cycle

    //If buffer is empty, print final message and disable joints
    if(buffer.isEmpty()){
      s.isEmptyBuffer = true;
      output = "Buffer is empty.";
      Serial.println(output);
      disableJoints();
    }

    //If buffer is not empty, get and set next position
    if(!buffer.isEmpty()){
      //Get next position
      curPos = *buffer.shift(); //Return, dereference and remove address from buffer
      
      //Set next position for steppers
      output = "Setting theta position target to: \n   {" + String(curPos.thetaPos[0]);
      for (int i=0; i<6 ; i++) {
        ptrSteppers[i]->moveTo(curPos.thetaPos[i]);

        if (i<5)
          output += "," + String(curPos.thetaPos[i]);
        
      }
      output += "} [steps]";
      Serial.println(output);
    }
  }


  //Execute stepper rotations
  for (int i=0; i<6 ; i++)
    ptrSteppers[i]->run();
}

