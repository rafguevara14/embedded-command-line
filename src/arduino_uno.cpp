
#include "arduino_uno.h"

PortPin dev_to_pin(char port, int pin){

    PortPin ret;
    
    if (port == D_CODE){
        if (0 <= pin && pin <= 7){
            ret.pin = pin;
            ret.port = ePort::D;
        }
        if (8 <= pin && pin <= 13){
            ret.pin = pin-8;
            ret.port = ePort::B;
        }
    }
    else if (port == A_CODE){
        if (0 <= pin && pin <= 5){
            ret.pin = pin;
            ret.port = ePort::C;
        }

    }
    return ret;
}