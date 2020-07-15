#ifndef POSITION_H
#define POSITION_H

    struct Position{

            double cartPos[3] = {0};
            double thetaPos[6] ={0};
        
        void setCartPos(double _x, 
                        double _y,
                        double _z){
            double _cartPos[3] = {_x, _y, _z};
            for (int i=0; i<3; i++)
                cartPos[i] = _cartPos[i];
        }

        void setThetaPos(   double _th1,
                            double _th2,
                            double _th3,
                            double _th4,
                            double _th5,
                            double _th6){
            double _thetaPos[6] = {_th1, _th2, _th3, _th4, _th5, _th6};
            for (int i=0; i<6; i++)
                thetaPos[i] = _thetaPos[i];
        }
    };

#endif