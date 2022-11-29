#include "Arduino.h"
#include "GPSP.h"
#include <QList.h>

/**
 * @brief Construct a new GPSP object, associating a Stream (Generally a Serial) to it.
 * 
 * @param serial
 */
GPSP::GPSP(Stream &serial) {
    this->serial = &serial;

};

/**
 * @brief Adds a new command to the List of Commands
 * 
 * @param command The new command
 */
void GPSP::defineCommand(Command command) {
    commandList.push_front(command);
}

/**
 * @brief Separate the buffer (see {@link #update() Update}) into it's Name & Arguments constituant, If this structure isn't followed (ex : Name doesn't match any command) prints "Invalid syntax" and recommands the use of the HELP command. It then calls the approproiate command passing it the Arguments and their number (How many arguments were retreived).
 *
 */
void GPSP::processBuffer() {
    char* d = strtok(buffer, "=");
    int index = 0;
    while (d != NULL) {
        d = strtok(NULL, ",");
        strcpy(args_temp[index++], d);
    }
    
    for (int i = 0; i < commandList.size(); i++) {
        if (strcmp(buffer, commandList[i].name) == 0) {
            commandList[i].callback(args_temp, index - 1);
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

/**
 * @brief Reads available data from Stream and stores it in a buffer until a NewLine or Semicolon is encountered. When this case is encountered call {@link #processBuffer() ProcessBuffer}, then clears the buffer.
 * 
 */
void GPSP::update() {
    while(serial->available() > 0) {
        char c = serial->read();
        if (c == '\n' || c == ';') {
            buffer[index] = '\0';
            processBuffer();
            index = 0;
        } else {
            buffer[index] = c;
            index++;
        }
    }
}

/**
 * @brief Prints to Stream commands specified by arguments. If none specified prints all available commands excluding itself.
 * 
 * @param args Arguments
 * @param size Number of retrieved arguments
 */
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

/**
 * @brief Prints a command
 * 
 * @param command The command to print
 */
void GPSP::printCommand(Command command) {
    serial->print(command.name);
    serial->println(": ");
    serial->print("\t- ");
    serial->println(command.description);
}
