#ifndef KINEMATIC_FUNCTIONS_H
#define KINEMATIC_FUNCTIONS_H

    //extern const int EN_PIN[6];4
    extern AccelStepper* ptrSteppers[6];

    //Disable all joints, by setting ENABLE to HIGH
    void disableJoints(){
        for (int i = 0;  i < 6; i++){
            //digitalWrite(EN_PIN[i], HIGH);
            ptrSteppers[i]->disableOutputs();
        }
    Serial.println("Disabling joints...");
    }

    //Enable all joints, by setting ENABLE to LOW
    void enableJoints(){
        for (int i = 0;  i < 6; i++){
            //digitalWrite(EN_PIN[i], LOW);
            ptrSteppers[i]->enableOutputs();
        }
    Serial.println("Enabling joints...");
    }

#endif