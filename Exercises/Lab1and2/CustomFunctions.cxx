#include <iostream>
#include <fstream>
#include<sstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

// Function below takes a multiple of different arguments, and prints them, kind of resemblems the way printing works in python
template<typename... Args>
void print(Args&&... args)
{
    (std::cout << ... << args) << std::endl;
}

// function below takes the name of the file the user wants to read, and returns a vector pair of the data in the form (x, y)

std::vector<std::pair<float, float>>  ReadData(const std::string& filename) {
    std::ifstream file(filename);

    std:: string str; //str is where each line of data is stored

    std::vector<std::pair<float, float>> xy_val; //Creating vector to store x and y values

    std::getline(file, str);  //skip first line for 'x,y' 
    while(std::getline(file, str)){
      std::stringstream ss(str); // converting str to a stringstream
      std:: string x_str, y_str; // creating strings to store x and y data

        if (std::getline(ss, x_str, ',') && std::getline(ss, y_str, ',')){ //looping through data that is separated by comma
          float xfloat = std::stof(x_str);
          float yfloat = std::stof(y_str); //converting x and y strings to floats 

          xy_val.emplace_back(xfloat, yfloat); // putting x and y float data into vector pair
    }
}
return xy_val;
  }

// function below asks user prints the lines of the data, based on the value N that the user provides

void printnlines(const std::vector<std::pair<float,float>>& data){

  int N;
  // function will ask user for an input until a value N is entered that lies between 0 and the length of the vector
  do{
    print("How many lines of the data would you like printed out?");
    std::cin >> N; //User input

    if (N <= 0){
    print("Error, N cannot be less than or equal to 0, please enter a new value.");
  } else if (N>data.size()){
    print("Error, N cannot be greater than the length of the vector. Please enter a new value");
  }
} while (N<=0 || N>data.size());

//Printing the first N lines
for (int i = 0; i<N; ++i){
  print(data[i].first, ", ", data[i].second);
}
}

// function below calculates the magnitude of the data points of a vector pair with data (x, y), and prints values to the terminal

std::vector<float> magnitudevecpair(const std::vector<std::pair<float,float>>& data){
  std::vector<float> magvec;
  for (size_t i=0; i<data.size(); ++i){
      float mag = std::sqrt(data[i].first * data[i].first + data[i].second * data[i].second);
      magvec.push_back(mag); //adds the values of the magnitude calculated in the above line to the vector magvec
      print(magvec[i]);
  } 

  return magvec;
}

// function below calculates the line of best fit for a set of data points, along with the chi squared per
// degree of freedom error

std::string leastsquares(std::vector<std::pair<float, float>>& data, std::vector<std::pair<float, float>>& error){
    int N = data.size();

    if (data.size()!=error.size()){
      print("Error the length of your data is not equal to the length of your error data.");
      print("Please ensure they have the same length before running this function again.");
    return 0;} // function will stop running if data and error data don't have the same size
    //initiallising necessary sums
    float sumx = 0.0, sumy = 0.0,  sumxx = 0.0, sumxy = 0.0;

    //using a for loop to calculate the necessary sums for least squares
    for (size_t i=0; i<N; i++){
        float xvals = data[i].first;
        float yvals = data[i].second;

        sumx += xvals;
        sumy += yvals;
        sumxy += xvals*yvals;
        sumxx += xvals*xvals;
    }

    // Caluclating gradient using least squares method
    float mnum = N*sumxy - sumx*sumy; 
    float mdem = N*sumxx - sumx*sumx;
    float m = mnum/mdem;

    //Calculating y intercept using least squares method
    float cnum = sumxx*sumy - sumxy*sumx;
    float cdem = N*sumxx - sumx*sumx;
    float c =cnum/cdem;

    // Creating variables for the string
    std::ostringstream oss1;
    oss1 << std::fixed << std::setprecision(3) << c;
    std::string cstring = oss1.str();
    std::ostringstream oss2;
    oss2 << std::fixed << std::setprecision(3) << m;
    std::string mstring = oss2.str();

    // Implementing a Chi squared per degree of freedom fit
    float chichi = 0.0;

    for (size_t i=0; i<N; i++){
        float xvals = data[i].first;
        float yvals = data[i].second;
        float sigmay = error[i].second;

        float yfit = m*xvals + c;
        float residual = yvals - yfit;

        chichi += (residual * residual)/(sigmay*sigmay);
    }

    float dof = N - 2; // for straight line fit
    float chichiperdof = chichi/dof;

    // Creating variables for the string

    std::ostringstream oss4;
    oss4 << std::fixed << std::setprecision(3) << chichiperdof;
    std::string chichiperdofstring = oss4.str();

    // Printing result

    print("The line of best fit for the input data is: y = ", mstring, "x + ", cstring);
    print("The chi squared fit per degree of freedom is is χ² = ", chichiperdofstring);
    
    // Creating string variable to store line of best fit

    std::string linfitstring = "y = " + mstring + "x + " + cstring + ", χ² = " + chichiperdofstring;

    return linfitstring;
}

// recursive function that calculates x^y for integer y

float power(float xval, int yval){
  if (yval==0) return 1.0f;
  else if (yval<0) return 1.0f / power(xval, -yval);

  float halfy = power(xval, yval/2);
  if (yval%2 ==0) return halfy*halfy;
  else return xval * halfy * halfy;
}

// function below calcaultes x^y for a given vector pair of data.

void xpowery_recursion(const std::vector<std::pair<float,float>>& data, size_t index, std::vector<float>& result){
  
  if (index >= data.size()) return; //terminating condition for recursive function
  
  //rounding y data to the nearest whole number
  int y_rounded = static_cast<int>(std::round(data[index].second));
  float xpowy = power(data[index].first, y_rounded);

  result.push_back(xpowy);

  xpowery_recursion(data, index + 1, result); //recursion

}

// function below serves as a wrapper fucntion to xpowery_recursion

std::vector<float> xpowery(const std::vector<std::pair<float,float>>& data) {
  std::vector<float> result;
  xpowery_recursion(data, 0, result);
  return result;
}

// functions below will save output from a function that the user selects and upload in to a file
// My functions have 2 outputs, vector<float>, or string so I need 2 versions
// vector<float>
void savetofile(const std::vector<float>& data, const std::string& filename){
  std::ofstream file(filename);

  for (float value:data){
    file<<value<<std::endl; 
  }

  file.close();
}

//string

void savetofile(const std::string& data, const std::string& filename){
  std::ofstream file(filename);

  file<< data;

  file.close();
}

//function below creates a string to output to terminal, telling the user the name of the savefile so
//I don't have to do this 4 times.

std::string makefilename(int function_number){
  return "output_function_" + std::to_string(function_number) + ".txt";
}