#ifndef FUNCTIONS_H
#define FUNCTIONS_H

    //Every 100 milliseconds sends report to Serial monitor
    void monitorDistanceToGo() {
        static uint32_t oldtime = millis();
        //Every 100 milliseconds report distanceToGo over Serial
        if ((millis()-oldtime)>100){
            String output1, output2, output3;
            oldtime = millis();
            output1 = "   [" + String(ptrSteppers[0]->distanceToGo());
            output2 = " {" + String(s.isArrivedAxis[0]);
            output3 = " {" + String(s.isArrived) + "}";
            for (int i=1; i<6; i++) {
                output1 += "," + String(ptrSteppers[i]->distanceToGo());
                output2 += "," + String(s.isArrivedAxis[i]);
            }
            output1 += "]";
            output2 += "}";
            Serial.println(output1 + output2 + output3); 
        }
    }



#endif