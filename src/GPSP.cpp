#include "Arduino.h"
#include "GPSP.h"
#include <QList.h>

GPSP::GPSP(Stream &serial) {
    this->serial = &serial;
    //name = new String[size];
    //command = new Command[size];
    //description = new String[size];
};

void GPSP::defineCommand(Command command) {
    commandList.push_front(command);
}

void GPSP::processBuffer() {
    char* d = strtok(buffer, "=");
    int index = 0;
    while (d != NULL) {
        d = strtok(NULL, ",");
        strcpy(args_temp[index++], d);
    }
    
    for (int i = 0; i < commandList.size(); i++) {
        if (strcmp(buffer, commandList[i].name) == 0) {
            commandList[i].pointer(args_temp, index - 1);
            return;
        }
    }

    if (strcmp(buffer, "HELP") == 0) {
        helpCommand(args_temp, index - 1);
        return;
    }

    serial->print("Invalid syntax: ");
    serial->println(buffer);
    serial->println("use HELP for list of valid commands");
}

String GPSP::update() {
    while(serial->available() > 0) {
        char c = serial->read();
        if (c == '\n') {
            buffer[index] = '\0';
            processBuffer();
            index = 0;
        } else {
            buffer[index] = c;
            index++;
        }
    }
}

void GPSP::helpCommand(const char args[][50], int size) {
    serial->println("");
    for (int i = 0; i < commandList.size(); i++) {
        if (size > 0) {
            for (int j = 0; j < size; j++) {
                if (strcmp(args[j], commandList[i].name) == 0) {
                    printCommand(commandList[i]);
                }
            }
        } else {
            printCommand(commandList[i]);
        }
    }
}

void GPSP::printCommand(Command command) {
    serial->print(command.name);
    serial->println(": ");
    serial->print("\t- ");
    serial->println(command.description);
}
