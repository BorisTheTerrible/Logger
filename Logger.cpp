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

Logger::Level Logger::control[SYSTEM_COUNT];

std::queue<std::string> Logger::activeMessageQueue;

std::thread * Logger::printLoopThread;

std::mutex Logger::messageQueueMutex;

std::mutex Logger::printLoopMutex;

bool Logger::isInitialized = intialize();

bool Logger::intialize()
{
    /*
     Intializes the control array values to INFO.
     */
    for(int index = 0; index < SYSTEM_COUNT; index++)
    {
        control[index] = Logger::Level::INFO;
    }
    
    printLoopThread = new std::thread(printLoop);
    
    return true;
}

void Logger::printLoop()
{
    std::unique_lock<std::mutex> uniqueLock(printLoopMutex);
    
    /*
     Sets up the intial lock, so the lock inside the while loop will block until log() unlocks it.
     */
    printLoopMutex.lock();
    
    while(true)
    {
        /*
         Blocks until log() unlocks the mutex.
         
         Once it loops back around, it will block on this again until log() unlocks the mutex.
         */
        std::cout << "TH:prelock" << std::endl;
        
        try
        {
            printLoopMutex.lock();
        }
        catch (std::exception ex)
        {
            std::cout << ex.what() << std::endl;
        }
        
        messageQueueMutex.lock();
        std::cout << "TH:lock" << std::endl;
        
        /*
         Prints out the messages until the message queue is empty.
         */
        while(!activeMessageQueue.empty())
        {
            std::string message = activeMessageQueue.front();
            activeMessageQueue.pop();
            
            /*
             Logger is meant to be low priority.
             So the message queue is unlocked incase something is trying to log a message.
             */
            messageQueueMutex.unlock();
            std::cout << "TH:unlock" << std::endl;
            //std::cout << message;
            
            messageQueueMutex.lock();
            std::cout << "TH:lock1" << std::endl;
        }

        messageQueueMutex.unlock();
        std::cout << "HT:unlock1" << std::endl;
        
        //std::this_thread::sleep_for (std::chrono::milliseconds(10));
    }
}

bool Logger::log(std::string message, Logger::System system, Logger::Level level)
{
    if((level >= control[system]) && (control[system] != Logger::Level::OFF))
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
        //std::cout << "lock" << std::endl;
        activeMessageQueue.push(stringStream.str());
        messageQueueMutex.unlock();
        //std::cout << "unlock" << std::endl;
        
        /*
         Unlocks the print loop so it can print out the pushed message.
         */
        printLoopLock.try_lock();
        printLoopLock.unlock();
        
        return true;
    }
    
    return false;
}

void Logger::setLevel(Logger::System system, Logger::Level level)
{
    control[system] = level;
    
    std::stringstream messageStream;
    messageStream << getSystemName(system) << " has been set to " << getLevelName(level);
    
    Logger::log(messageStream.str(), Logger::System::LOGGER, Logger::Level::INFO);
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
