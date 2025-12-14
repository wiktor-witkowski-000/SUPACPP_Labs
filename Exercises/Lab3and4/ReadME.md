My code for Lab3and4 works in the following way:

I have FiniteFunctions.h and FiniteFunctions.cxx defining the parent class that the normal, cauchy-lorentz
and crystal ball classes inherit from. I have these children classes defined in a separate script, CustomFunctions.h and CustomFunctions.cxx. I analyse the code, creating all the necessary plots and print statements, in TestFiniteFunctions.cxx.

To run my file:
I have modified the given makefile to work with CustomFunctions.h and CustomFunctions.cxx.

So to run the code, "make" should compile the necessary code, and then "./TestFiniteFunctions" should give the required outputs.