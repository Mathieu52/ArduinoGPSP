#ifndef GPSP_h
#define GPSP_h
#include "Arduino.h"
#include <QList.h>

typedef void (*Pointer)(const char args[][50], int size);
struct Command {
    Pointer pointer;
    char* name;
    char* description;
};

class GPSP {
    public:
        GPSP(Stream &serial);
        void defineCommand(Command command);
        String update();

    private:
        //Command *command;
        //String *description;
        char args_temp[10][50];
        //arx::map<char*, Command> command_map {};
        //arx::map<char*, char*> description_map {};
        
        int index = 0;
        char buffer[500];
    
        void processBuffer();
        void helpCommand(const char args[][50], int size);
        void printCommand(Command command);

        Stream *serial;
        QList<Command> commandList = QList<Command>();
};

#endif