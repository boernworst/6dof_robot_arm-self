#ifndef KINEMATIC_DEFINITIONS_H
#define KINEMATIC_DEFINITIONS_H

    //robot geometry in [mm]
    const int d1 = 133; 
    const int r1 = 47; 
    const int r2 = 110; 
    const int r3 = 26; 
    const int d3 = 0;
    const int d4 = 117.5;
    const int d6 = 28;

    //Gear ratios Axis 1-6
    //  gear ratio 1 = 96/20 = 4.8
    //  gear ratio 2 = 4
    //  gear ratio 3 = 5
    //  gear ratio 4 = 56/20 = 2.8
    //  gear ratio 5 = 42/20 = 2.1
    //  gear ratio 6 = 1
    const double gr[6] = {4.8, 4, 5, 2.8, 2.1, 1.0};
    const int stepsPerRevolution = 200*16; //1/16 microstepping with 200 steps/revolution
    //Required steps from stepper for a full revolution of joint
    const double steps[6] =    {stepsPerRevolution*gr[0],
                                stepsPerRevolution*gr[1],
                                stepsPerRevolution*gr[2],
                                stepsPerRevolution*gr[3],
                                stepsPerRevolution*gr[4],
                                stepsPerRevolution*gr[5]};

    //Set positive direction of rotation, CW is positive
    const bool AXIS_DIR[6] = {LOW, LOW, HIGH, HIGH, HIGH, LOW};

    //Store stepper profile settings: {vmax, a}
    const double set_A4988[2] = {1000, 500}; 
    const double set_TB6600[2] = {1000, 500}; 

    //AccelStepper(motorInterfaceType, stepPin, dirPin)
    // AccelStepper stepper1, stepper2, stepper3, stepper4, stepper5, stepper6;
    AccelStepper stepper1(AccelStepper::DRIVER, STEP_PIN[0], DIR_PIN[0]);
    AccelStepper stepper2(AccelStepper::DRIVER, STEP_PIN[1], DIR_PIN[1]);
    AccelStepper stepper3(AccelStepper::DRIVER, STEP_PIN[2], DIR_PIN[2]);
    AccelStepper stepper4(AccelStepper::DRIVER, STEP_PIN[3], DIR_PIN[3]);
    AccelStepper stepper5(AccelStepper::DRIVER, STEP_PIN[4], DIR_PIN[4]);
    AccelStepper stepper6(AccelStepper::DRIVER, STEP_PIN[5], DIR_PIN[5]);
    AccelStepper *ptrSteppers[6] = {&stepper1, &stepper2, &stepper3, &stepper4, &stepper5, &stepper6};

    /* Initialize steppers by: 
        - storing stepper settings for TB6600 to steppers 1-3
        - storing stepper settings for A4988 to steppers 4-6
    */
    void initSteppers(){
        String output;
        for (int i=0; i<3; i++){
            ptrSteppers[i]->setMaxSpeed(set_TB6600[0]);
            ptrSteppers[i]->setAcceleration(set_TB6600[1]);
            ptrSteppers[i]->setCurrentPosition(0);

            ptrSteppers[i+3]->setMaxSpeed(set_A4988[0]);
            ptrSteppers[i+3]->setAcceleration(set_A4988[1]);
            ptrSteppers[i+3]->setCurrentPosition(0);
        }
        output = "Steppers initialized:\n";
        output += "   TB6600: v_max = " + String(set_TB6600[0]) + " [steps/second]\n";
        output += "   TB6600:     a = " + String(set_TB6600[1]) + "  [steps/second^2]\n";
        output += "   AT4988: v_max = " + String(set_A4988[0])  + " [steps/second]\n";
        output += "   AT4988:     a = " + String(set_A4988[1])  + "  [steps/second^2]";
        Serial.println(output);
    }
    
#endif