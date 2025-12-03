// Wiktor Witkowski 12/11/2025
#include <iostream>
#include <cmath>
#include <vector>

float mag_vector(float a, float b){
    // Function that takes as an input 2 components of a 2D vector
    // and outputs the magnitude of the vector
    float c2 = a*a + b*b;
    float c = std::sqrt(c2);
    std::cout << "Using function, magnitude of x = " << c << std::endl;
return c;
}

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

float x_function;
x_function = mag_vector(x, y);


return 0;
}