#ifndef GPSP_h
#define GPSP_h
#include "Arduino.h"
#include <ArxContainer.h>

class GPSP {
    public:
        GPSP(HardwareSerial &serial);
        void defineCommand(String key, void (*procedure)(String args, ...), String description = "No description");
        void defineDescription(String key, String description);
        String update();

    private:
        typedef void (*Command)(String args, ...);
        HardwareSerial *serial;
        arx::map<String, Command> command_map {};
        arx::map<String, String> description_map {};

        void HELP(String args, ...);
};
#endif