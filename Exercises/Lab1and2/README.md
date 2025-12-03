How my code works:

Once compiled, code will ask user to select one of 4 functions, by typing a number into the terminal. 

The 4 functions are: 1) Print n lines of code 2) Calculate the magnitude of a set of data.
3) Calculate the line of best fit and reduced chi squared for a set of data, 4) Calculate x^y for
a given set of data, recursively.

To compile: I use: "g++ -std=c+20 -w -o Lab1 AnalyseDataWW.cxx CustomFunctions.cxx"

The user should be promoted to select one of the 4 functions when the code is ran with ./Lab1 .

If a number is chosen outside this range of numbers, the user will be asked to select a valid number.

Once a function has been selected, its output will be automatically saved to a separate txt file called ("output_function" + function_number + ".txt"). This doesn't happen for the print N lines function.

Once the function has finished running, the user will either be asked to select a new function, or to exit the program selection.

I have tried to add helpful comments throughout the code. I hope it's not difficult to understand!