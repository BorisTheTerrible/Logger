#include <iostream>
#include <string>

#include "Logger.hpp"

using namespace std;

void logTest();

int main(int argc, const char * argv[])
{
    logTest();
}

void logTest()
{
    Logger::log("Dog", Logger::System::NETWORKING, Logger::Level::SEVERE);
    Logger::log("Dog", Logger::System::NETWORKING, Logger::Level::WARNING);
    Logger::log("Dog", Logger::System::NETWORKING, Logger::Level::CONFIG);
    Logger::log("Dog", Logger::System::NETWORKING, Logger::Level::INFO);
    Logger::log("Dog", Logger::System::NETWORKING, Logger::Level::FINE);
    Logger::log("Dog", Logger::System::NETWORKING, Logger::Level::DEBUGGING);
    
    Logger::log("Dog", Logger::System::LOGGER, Logger::Level::SEVERE);
    Logger::log("Dog", Logger::System::LOGGER, Logger::Level::WARNING);
    Logger::log("Dog", Logger::System::LOGGER, Logger::Level::CONFIG);
    Logger::log("Dog", Logger::System::LOGGER, Logger::Level::INFO);
    Logger::log("Dog", Logger::System::LOGGER, Logger::Level::FINE);
    Logger::log("Dog", Logger::System::LOGGER, Logger::Level::DEBUGGING);
    
    Logger::setLevel(Logger::System::NETWORKING, Logger::Level::FINE);
    Logger::log("Dog1", Logger::System::NETWORKING, Logger::Level::SEVERE);
    Logger::log("Dog1", Logger::System::NETWORKING, Logger::Level::WARNING);
    Logger::log("Dog1", Logger::System::NETWORKING, Logger::Level::CONFIG);
    Logger::log("Dog1", Logger::System::NETWORKING, Logger::Level::INFO);
    Logger::log("Dog1", Logger::System::NETWORKING, Logger::Level::FINE);
    Logger::log("Dog1", Logger::System::NETWORKING, Logger::Level::DEBUGGING);
    
    Logger::log("Dog1", Logger::System::LOGGER, Logger::Level::SEVERE);
    Logger::log("Dog1", Logger::System::LOGGER, Logger::Level::WARNING);
    Logger::log("Dog1", Logger::System::LOGGER, Logger::Level::CONFIG);
    Logger::log("Dog1", Logger::System::LOGGER, Logger::Level::INFO);
    Logger::log("Dog1", Logger::System::LOGGER, Logger::Level::FINE);
    Logger::log("Dog1", Logger::System::LOGGER, Logger::Level::DEBUGGING);
    
    Logger::setLevel(Logger::System::NETWORKING, Logger::Level::OFF);
    Logger::log("Dog2", Logger::System::NETWORKING, Logger::Level::SEVERE);
    Logger::log("Dog2", Logger::System::NETWORKING, Logger::Level::WARNING);
    Logger::log("Dog2", Logger::System::NETWORKING, Logger::Level::CONFIG);
    Logger::log("Dog2", Logger::System::NETWORKING, Logger::Level::INFO);
    Logger::log("Dog2", Logger::System::NETWORKING, Logger::Level::FINE);
    Logger::log("Dog2", Logger::System::NETWORKING, Logger::Level::DEBUGGING);
    
    Logger::log("Dog2", Logger::System::LOGGER, Logger::Level::SEVERE);
    Logger::log("Dog2", Logger::System::LOGGER, Logger::Level::WARNING);
    Logger::log("Dog2", Logger::System::LOGGER, Logger::Level::CONFIG);
    Logger::log("Dog2", Logger::System::LOGGER, Logger::Level::INFO);
    Logger::log("Dog2", Logger::System::LOGGER, Logger::Level::FINE);
    Logger::log("Dog2", Logger::System::LOGGER, Logger::Level::DEBUGGING);
    
    Logger::setLevel(Logger::System::LOGGER, Logger::Level::OFF);
    Logger::setLevel(Logger::System::LOGGER, Logger::Level::SEVERE);
    Logger::setLevel(Logger::System::NETWORKING, Logger::Level::SEVERE);
    Logger::setLevel(Logger::System::NETWORKING, Logger::Level::WARNING);
    Logger::setLevel(Logger::System::LOGGER, Logger::Level::DEBUGGING);
    Logger::log("Dog3", Logger::System::NETWORKING, Logger::Level::SEVERE);
    Logger::log("Dog3", Logger::System::NETWORKING, Logger::Level::WARNING);
    Logger::log("Dog3", Logger::System::NETWORKING, Logger::Level::CONFIG);
    Logger::log("Dog3", Logger::System::NETWORKING, Logger::Level::INFO);
    Logger::log("Dog3", Logger::System::NETWORKING, Logger::Level::FINE);
    Logger::log("Dog3", Logger::System::NETWORKING, Logger::Level::DEBUGGING);
    
    Logger::log("Dog3", Logger::System::LOGGER, Logger::Level::SEVERE);
    Logger::log("Dog3", Logger::System::LOGGER, Logger::Level::WARNING);
    Logger::log("Dog3", Logger::System::LOGGER, Logger::Level::CONFIG);
    Logger::log("Dog3", Logger::System::LOGGER, Logger::Level::INFO);
    Logger::log("Dog3", Logger::System::LOGGER, Logger::Level::FINE);
    Logger::log("Dog3", Logger::System::LOGGER, Logger::Level::DEBUGGING);
    
    Logger::setLevel(Logger::System::LOGGER, Logger::Level::OFF);
    Logger::log(Logger::getLevelName(Logger::checkLevel(Logger::System::LOGGER)), Logger::System::NETWORKING, Logger::SEVERE);
    Logger::setLevel(Logger::System::LOGGER, Logger::Level::SEVERE);
    Logger::log(Logger::getLevelName(Logger::checkLevel(Logger::System::LOGGER)), Logger::System::NETWORKING, Logger::SEVERE);
    Logger::setLevel(Logger::System::NETWORKING, Logger::Level::SEVERE);
    Logger::log(Logger::getLevelName(Logger::checkLevel(Logger::System::NETWORKING)), Logger::System::NETWORKING, Logger::SEVERE);
    Logger::setLevel(Logger::System::NETWORKING, Logger::Level::WARNING);
    Logger::log(Logger::getLevelName(Logger::checkLevel(Logger::System::NETWORKING)), Logger::System::NETWORKING, Logger::SEVERE);
    Logger::setLevel(Logger::System::LOGGER, Logger::Level::DEBUGGING);
    Logger::log(Logger::getLevelName(Logger::checkLevel(Logger::System::LOGGER)), Logger::System::NETWORKING, Logger::SEVERE);
    
    std::this_thread::sleep_for(std::chrono::seconds(10));
}
