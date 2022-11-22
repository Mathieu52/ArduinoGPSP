#include "Arduino.h"

class GPSP {
    public :

        GPSP(HardwareSerial &serial)
        void defineInstruction(String key, void (*procedure)(String args, ...));
        void defineDefinition(String key, String definition);
        String[] getInstructionList();
        String update();

    private :
        HardwareSerial *serial;
        arx::map<String, void (*procedure)(String args, ...)> mp {};
}