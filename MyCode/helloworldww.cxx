// Wiktor Witkowski 12/11/2025
#include <iostream>
#include <cmath>

int main()
{
    // print 'Hello World' to the terminal
std::cout << "Hello World :)" << std::endl;

// Computing magnitude of vector z = x + y
float x = 7.5;
float y = 3.4;
float z2 = x*x + y*y;
float mag_z = std::sqrt(z2);

std::cout << mag_z << std::endl;
return 0;
}