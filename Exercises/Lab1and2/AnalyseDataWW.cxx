#include <iostream>
#include <fstream>
#include<sstream>
#include <string>
#include <vector>
#include <cmath>
#include "CustomFunctions.h"

  int main(){

    //reading in the data we wish to analyse
    std::vector<std::pair<float, float>> xy_data = ReadData("input2D_float.txt");

    std::vector<std::pair<float, float>> xy_error = ReadData("error2D_float.txt");

    int function_number;  
  
  while (true){
    print("Which function would you like to use today?"); 

      while(true){
         print("Enter '1' to print N lines of your data"); 
         print("Enter '2' to calculate the magnitude of a set of data points"); 
         print("Enter '3' to calculate the line of best fit");
         print("Enter '4' to calculate the x data to the power of rounded y");
    std::cin>>function_number;
      if (function_number==1){
        printnlines(xy_data);
        // saving N printed lines to a new file feels pointless beacsue we already have a text file
        // with all the data
        break;
      } else if (function_number==2){
          std::vector<float> magnitudexydata = magnitudevecpair(xy_data);
          std::string File = makefilename(2);
          savetofile(magnitudexydata, File);
          print("Saved magnitude data to: " + File);
          break;
      } else if(function_number==3){
          std::string lineofbestfit = leastsquares(xy_data, xy_error);
          std::string File = makefilename(3);
          savetofile(lineofbestfit, File);
          print("Saved line of best fit data to: " + File);
          break;
      } else if(function_number==4){
        std::vector<float> results = xpowery(xy_data);
        for(float o: results){
          print(o);
        }
        std::string File = makefilename(4);
        savetofile(results, File);
        print("Saved x^rounded(y) data to: " + File);
        break;
      } else {
          print("Invalid input, please enter either: '1', '2', '3', or '4'.");
      }
    }


print("Would you like to select another function or exit?");
print("Press '1' for another function.");
print("Press '2' to exit.");
std::cin>>function_number;

if (function_number==2){
  print("Have a nice day!");
  break;
}

  }
return 0;
}