#include <iostream>
#include <string>

#include "Logger.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
    while(true)
    {
        Logger::log("Dog", Logger::System::NETWORKING, Logger::Level::SEVERE);
    }
}
