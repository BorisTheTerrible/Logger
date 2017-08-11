//
//  Logger.cpp
//  Logger
//
//  Created by games on 8/7/17.
//  Copyright © 2017 games. All rights reserved.
//

#include "Logger.hpp"

#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

Logger::Level Logger::systemLevels[SYSTEM_COUNT];

std::mutex Logger::systemLevelsMutex;

std::queue<std::string> Logger::messageQueue;

std::mutex Logger::messageQueueMutex;

std::thread * Logger::printLoopThread;

std::mutex Logger::printLoopMutex;

std::condition_variable Logger::printLoopConditionVariable;

bool Logger::isInitialized = intialize();

bool Logger::intialize()
{
    /*
     Intializes the control array values to INFO.
     */
    for(int index = 0; index < SYSTEM_COUNT; index++)
    {
        systemLevels[index] = Logger::Level::INFO;
    }
    
    printLoopThread = new std::thread(printLoop);
    
    return true;
}

void Logger::printLoop()
{
    std::unique_lock<std::mutex> printLoopLock(printLoopMutex);
    
    while(true)
    {
        messageQueueMutex.lock();
        
        /*
         Prints out the messages until the message queue is empty.
         */
        while(!messageQueue.empty())
        {
            std::string message = messageQueue.front();
            messageQueue.pop();
            
            /*
             Logger is meant to be low priority.
             So the message queue is unlocked incase something is trying to log a message.
             */
            messageQueueMutex.unlock();
            std::cout << message;
            
            messageQueueMutex.lock();
        }

        messageQueueMutex.unlock();
        
        /*
         Waits until log() is called and notifies that their are messages available.
         */
        printLoopConditionVariable.wait(printLoopLock);
    }
}

bool Logger::log(std::string message, Logger::System system, Logger::Level level)
{
    if((level >= systemLevels[system]) && (systemLevels[system] != Logger::Level::OFF))
    {
        using namespace std::chrono;
        
        /*
         Gets the current time.
         */
        time_point<system_clock> nowTimePoint = system_clock::now();
        time_t nowTime = system_clock::to_time_t(nowTimePoint);
        
        using namespace std;
        
        /*
         Formats the message with system, level, and time stamp.
         */
        stringstream  stringStream;
        stringStream << "[" << getSystemName(system) << "] ";
        stringStream << "[" << getLevelName(level) << "] ";
        stringStream << put_time(localtime(& nowTime), "[%Y-%m-%d] [%X] ");
        stringStream << message << endl;
        
        /*
         Pushes the message to the message queue.
         */
        messageQueueMutex.lock();
        messageQueue.push(stringStream.str());
        messageQueueMutex.unlock();
        
        /*
         Notifies the printLoopThread that there are messages available to be printed to console.
         */
        printLoopConditionVariable.notify_one();
        
        return true;
    }
    
    return false;
}

void Logger::setLevel(Logger::System system, Logger::Level level)
{
    systemLevelsMutex.lock();
    systemLevels[system] = level;
    systemLevelsMutex.unlock();
    
    std::stringstream messageStream;
    messageStream << getSystemName(system) << " has been set to " << getLevelName(level);
    
    Logger::log(messageStream.str(), Logger::System::LOGGER, Logger::Level::INFO);
}

Logger::Level Logger::checkLevel(Logger::System system)
{
    Level level;
    
    systemLevelsMutex.lock();
    level = systemLevels[system];
    systemLevelsMutex.unlock();
    
    return level;
}

std::string Logger::getSystemName(Logger::System system)
{
    if(system == Logger::System::LOGGER)
    {
        return "LOGGER";
    }
    else if(system == Logger::System::NETWORKING)
    {
        return "NETWORKING";
    }
    else
    {
        return "NOT_VALID_SYSTEM";
    }
}

std::string Logger::getLevelName(Level level)
{
    if(level == Logger::Level::OFF)
    {
        return "OFF";
    }
    else if(level == Logger::Level::DEBUGGING)
    {
        return "DEBUGGING";
    }
    else if(level == Logger::Level::FINE)
    {
        return "FINE";
    }
    else if(level == Logger::Level::INFO)
    {
        return "INFO";
    }
    else if(level == Logger::Level::CONFIG)
    {
        return "CONFIG";
    }
    else if(level == Logger::Level::WARNING)
    {
        return "WARNING";
    }
    else if(level == Logger::Level::SEVERE)
    {
        return "SEVERE";
    }
    else
    {
        return "NOT_VALID_LEVEL";
    }
}
