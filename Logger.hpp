//
//  Logger.hpp
//  Logger
//
//  Created by games on 8/7/17.
//  Copyright © 2017 games. All rights reserved.
//

#ifndef Logger_hpp
#define Logger_hpp

#include <stdio.h>
#include <string>
#include <queue>
#include <thread>

class Logger
{
public:
    
    /*
     Details what specific system inside a program is logging a specific message.
     Each system defaults to Level::INFO, their level can be set uniquely through the setLevel method.
     
     NOTE, SYSTEM_COUNT should be updated everytime an enum is added or removed from System.
     NOTE, the getSystemName() method should be updated if an enum is added or removed from System.
     */
    enum System
    {
        NETWORKING, LOGGER
    };
    
    /*
     Used to specify what level of messages a current system inside a program will be outputted to the console.
     log() will only output messages to the console that are of higher or equal value of the specified system's level.
     
     Example, NETWORKING is set to Fine, that means all messages that are logged with Fine or higher (INFO through SEVERE) to NETWORKING will be outputted to the console.
     However, OFF is a special case that will ignore all attempts to log for the specific System.
     
     Note, OFF should not be used to log messages.
     
     NOTE, the getLevelName() method should be updated if an enum is added or removed from Level.
     */
    enum Level
    {
        OFF, DEBUGGING, FINE, INFO, CONFIG, WARNING, SEVERE
    };
    
    /*
     Used to set what level a specific system will log at.
     
     Such as, NETWORKING is set to Fine, that means all messages that are logged with Fine or higher (INFO through SEVERE) to NETWORKING will be outputted to the console.
     */
    static void setLevel(System system, Level level);
    
    /*
     Used to log a message to the console.
     For consistency, all messages should be outputted to the console used this method.
     
     Will only output the message to the console if the specified system's level is of equal or higher value.
     However, OFF is a special case that will ignore all attempts to log for the specific System.
     
     This method returns true if the message will be outputted to console, it returns false if it won't.
     
     Note, OFF should not be used to log messages.
     */
    static bool log(std::string message, System system, Level level);
    
//public
    
private:
    
/*
This is a count of how many values are contained in the enum System.
 
This should be updated everytime an enum is added or removed from System.
*/
#define SYSTEM_COUNT 2
    
    /*
     This defines a level for each system used.
     All System's Levels will be default intialized to INFO.
     
     The array values corresponde to the Level enum values.
     Such as, control[0] corresponds to the first enum value in System(in this case OFF).
     */
    static Level systemLevels[SYSTEM_COUNT];
    
    /*
     This holds the messages that are to be printed out.
     */
    static std::queue<std::string> messageQueue;
    
    /*
     This locks messageQueue from being accessed simultaneously.
     */
    static std::mutex messageQueueMutex;
    
    /*
     This thread runs the printLoop() method that prints messages in the messageQueue to the console.
     */
    static std::thread * printLoopThread;
    
    /*
     This is used for the printLoopConditionVariable.
     */
    static std::mutex printLoopMutex;
    
    /*
     The printLoop() method uses this to wait until messages are available to be printed out.
     
     The log() method uses this to notify the printLoopThread that messages are available in the messageQueue.
     */
    static std::condition_variable printLoopConditionVariable;
    
    /*
     This defines whether or not intialize() has been called or not.
     
     It is primarily used just to call the intialize() before the logger class is used.
     */
    static bool isInitialized;
    
    /*
     This intializes the control array before the logger class is used.
     */
    static bool intialize();
    
    /*
     This method is called by the printLoopThread and continously prints message from the messageQueue to the console.
     */
    static void printLoop();
    
    /*
     Returns the string representation of a System enum value.
     */
    static std::string getSystemName(System system);
    
    /*
     Returns the string representation of a Level enum value.
     */
    static std::string getLevelName(Level level);
};

//private

#endif /* Logger_hpp */
