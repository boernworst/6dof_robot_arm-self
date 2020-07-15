#ifndef PINOUT_DEFINITIONS_H
#define PINOUT_DEFINITIONS_H

    extern const bool AXIS_DIR[6];

    //Order of axis[6] = {1, 2, 3, 4, 5, 6}
    const int EN_PIN[6] =   {32, 32, 32, 38, 24, 30};
    const int DIR_PIN[6] =  {39, 43, 47, A1, 28, 34}; //A1 is pre-defined as integer
    const int STEP_PIN[6] = {37, 41, 45, A0, 26, 36}; //A0 is pre-defined as integer

    /* Initalize GPIO by:
        - setting pinmodes to OUTPUT
        - writing LOW on STEP signals
        - writing AXIS_DIR on DIR signals
    */
    void initGPIO(){
        for (int i = 0;  i < 6; i++){
            //Define pinmodes
            pinMode(EN_PIN[i], OUTPUT);
            pinMode(DIR_PIN[i], OUTPUT);

            //Define directions
            digitalWrite(STEP_PIN[i], LOW);
            digitalWrite(DIR_PIN[i], AXIS_DIR[i]);
        }
        Serial.println("GPIO initialized...");
    }

#endif