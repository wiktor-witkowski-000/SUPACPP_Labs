#include "FiniteFunctions.h"
#include <cmath>

#pragma once //Replacement for IFNDEF

class NormalDist : public FiniteFunction{
    public:
        NormalDist(double mu, double sigma, double range_min, double range_max, std::string outfile);

        // overide callfunction and printInfo

        double callFunction(double x) override;
        void printInfo() override;

    private:
        double m_mu;
        double m_sigma;
        double m_normFactor;
};

class CauchyLorentz : public FiniteFunction{
    public: 
        CauchyLorentz(double x0, double gamma, double range_min, double range_max, std::string outfile);

        // override callFunction and printInfo

        double callFunction(double x) override;
        void printInfo() override;

    private:
        double m_x0;
        double m_gamma;
        double m_clfactor;
};

class CrystalBall : public FiniteFunction{
    public: 
        CrystalBall(double xbar, double sigma, double alpha, double n, double range_min, double range_max, std::string outfile);

        //override callFunction and printInfo

        double callFunction(double x) override;
        void printInfo() override;

    private:
        double m_xbar;
        double m_sigma;
        double m_alpha;
        double m_n;
    
    // Crystal Ball constants
        double m_A;
        double m_B;
        double m_N;
};