#include <iostream>
#include <fstream>
#include<sstream>
#include <string>
#include <vector>
#include <cmath>
#include "FiniteFunctions.h"
#include "CustomFunctions.h"

int main(){
//reading the data we wish to analyse
std::ifstream file("Outputs/data/MysteryData22022.txt");

// check if file opened successfully

if(!file.is_open()){
  std::cerr<<"ERROR:could not open file"<<std::endl;
  return 1;
}

std:: string str; //str is where each line of data is stored

std::vector<double>  datapoints; //Creating vector to store x values

    while(std::getline(file, str)){
      if (str.empty()) continue;

      try{
      datapoints.emplace_back(std::stod(str));
      } // putting x data into vector
      catch (const std::exception& e){
      std::cerr << "Parse error in line: '" << str << "' (" << e.what() << ")\n";
        }
      }
    

// checking if data points are empty

if (datapoints.empty()) {
    std::cerr << "ERROR: No data read — file empty or parse failed"<<std::endl;
    return 1;
}

//std::string xvalstoi = std::to_string(xval);
// std::cout<<datapoints[99999]<<std::endl;

// Using default constructor with default range and name
FiniteFunction defaultres;

// Increase the range before plotting the data

defaultres.setRangeMin(-10);
defaultres.setRangeMax(10);
// Scanning and plotting function

defaultres.plotData(datapoints, 100, true);
defaultres.plotFunction();

// Trying function for normal distribution

NormalDist gauss(0.0, 1.0, -10.0, 10.0, "Gaussian_Output");

double gaussintegral = gauss.integral();

gauss.printInfo();
gauss.plotData(datapoints, 100, true);
gauss.plotFunction();

// Trying function for cauchy lorentz distribution

CauchyLorentz calo(0.0, 1.0, -10.0, 10.0, "CauchyLorentz_Output");

double calointegral = calo.integral();

calo.printInfo();
calo.plotData(datapoints, 100, true);
calo.plotFunction();

// Trying function for Crystal ball distribution

CrystalBall cball(0.0, 1.0, 1.9, 50.0, -10.0, 10.0, "CrystalBall_Output");

double cballintegral = cball.integral();

cball.printInfo();


// Creating vector to store sampled data from metropolis algorithm:

std::vector<double> samples;

int Nsteps = 200000;
int burnin = 5000; //burnin is the amount of initial samples that are discarded, so data isn't sampled from tail of distribution

// Sampling data from CrystalBall function

double xi_rand = cball.sampleUniformX(); // Xi data

// Proposed standard deviation 

double sigma_prop = 2.0;

for (int i=0; i< Nsteps; i+=1){
  double y_nor_rand = cball.sampleGaussianrand(xi_rand, sigma_prop); //Y data

  // Compute Acceptance ratio A

  double A = cball.acceptance(xi_rand, y_nor_rand);

  // Generate random number T

  double T = cball.sampleUniform01();
  
  // Accept y if T<A

  if (T<A){
    xi_rand = y_nor_rand;
  }

  // else, x_i+1 = x_i

  if (i>burnin){
    samples.push_back(xi_rand);
  }
}

// plotting sampled data
cball.plotData(samples, 100, false);

//plotting real data and function

cball.plotData(datapoints, 100, true);
cball.plotFunction();

//SampleUnifromX, acceptance, sampleGaussianrand and sampleUniform01 will work for Normal, CauchyLorentz, and Inverse Squared distribtions also

// I think that the Crystal Ball distribution is where the mystery data is sampled from, as this is the only asymmetric
// distribution out of the 4, however I think that for the crystal ball to fit the mystery data exactly, a crystal
// ball distribution that has 2 modifiable tails, rather than 1, needs to be implemented. Metropolis algorithm seems
// to work well to reproduce the function data.

return 0;
}