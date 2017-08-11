#include <iostream>
#include <string>

#include "Logger.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
    //Test
    while(true)
    {
        Logger::log("Dog", Logger::System::NETWORKING, Logger::Level::SEVERE);
        
        //std::this_thread::sleep_for (std::chrono::milliseconds(100));
    }
}
