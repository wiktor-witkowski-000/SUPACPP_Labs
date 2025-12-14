#include "CustomFunctions.h"
#include <cmath>

NormalDist::NormalDist(double mu, double sigma, double range_min, double range_max, std::string outfile)
: FiniteFunction(range_min, range_max, outfile),
m_mu(mu),
m_sigma(sigma)
{
    //Calculating normalisation constant
    m_normFactor = 1.0/(sigma*std::sqrt(2.0*M_PI));
}

double NormalDist::callFunction(double x){
    double factor = (x - m_mu)/m_sigma;
    double fx = m_normFactor*std::exp(-1.0/2.0*factor*factor);
    return fx;
}

void NormalDist::printInfo() {
    std::cout << "Normal Distribution"<< std::endl;
    FiniteFunction::printInfo();
    std::cout << "mu =" << m_mu << std::endl;
    std::cout << "sigma = " << m_sigma << std::endl;
}

CauchyLorentz::CauchyLorentz(double x0, double gamma, double range_min, double range_max, std::string outfile)
: FiniteFunction(range_min, range_max, outfile),
m_x0(x0),
m_gamma(gamma)
{
    // calculating factor
    m_clfactor = 1.0/(M_PI*gamma);
}

double CauchyLorentz::callFunction(double x){
    double bracket = (x - m_x0)/(m_gamma);
    double fx = m_clfactor*(1.0/(1.0 + (bracket*bracket)));
    return fx;
}

void CauchyLorentz::printInfo() {
    std::cout << "Cauchy–Lorentz Distribution" << std::endl;
    FiniteFunction::printInfo();
    std::cout << "x0 =" << m_x0 << std::endl;
    std::cout << "gamma =" << m_gamma << std::endl;
}

CrystalBall::CrystalBall(double xbar, double sigma, double alpha, double n, double range_min, double range_max, std::string outfile)
: FiniteFunction(range_min, range_max, outfile),
m_xbar(xbar),
m_sigma(sigma),
m_alpha(alpha),
m_n(n)
{
    // Calculating A,B,C,D,N
    double A_xfactor = n/std::abs(alpha);
    double A_factor = std::pow(A_xfactor, n);
    double exp_factor = -(alpha*alpha)/2.0;
    double C_factor = 1.0/(n - 1.0);
    double D_factor = std::sqrt(M_PI/2);

    m_A = A_factor*std::exp(exp_factor);
    m_B = A_xfactor - std::abs(alpha);
    double C = A_xfactor*C_factor*std::exp(exp_factor);
    double D = D_factor*(1.0 + std::erf(std::abs(alpha)/std::sqrt(2)));
    m_N = 1.0/sigma*1.0/(C + D);
}

double CrystalBall::callFunction(double x){
    double ball_factor = (x - m_xbar)/m_sigma;

    // Using if statments to calculate 2 separate cases
    if (ball_factor > -m_alpha){
        return m_N*exp(-1.0/2.0*ball_factor*ball_factor);
    } else {
        return m_N*m_A*pow(m_B - ball_factor, -m_n);
    }
}

    void CrystalBall::printInfo() {
    std::cout << "Crystal Ball Distribution" << std::endl;
    FiniteFunction::printInfo();
    std::cout << "xbar =" << m_xbar << std::endl;
    std::cout << "sigma =" << m_sigma << std::endl;
    std::cout << "alpha =" << m_alpha << std::endl;
    std::cout << "n =" << m_n << std::endl;
}