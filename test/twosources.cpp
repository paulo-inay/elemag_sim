#include "Elemag_Sim.h"

#ifndef PNG_HEADER
#include "include/png++/png.hpp"
#define PNG_HEADER
#endif

#include <cmath>
#include <iostream>
#include <sstream>
#include <experimental/filesystem>
using namespace std;
namespace fs = std::experimental::filesystem;

int main(){
    int rows = 101, columns = 101;
    int total_time = 6000;
    double sigma = 0.0;
    double sigmaM = 0.0;
    double epsilon = 8.85418782 * 10E-12;
    double mu = 4 * M_PI * 10E-7;
    double delta = 100.0;
    double deltaT = delta/(299792458 * sqrt(2));
    Mesh twosources = Mesh(rows, columns, sigma, sigmaM, epsilon, mu, delta, deltaT);

    XYCoord source[2];
    source[0].coordY = source[1].coordY = 50;
    source[0].coordX = 25;
    source[1].coordX = 75;
    source[0].value = source[1].value = 1.0;

    twosources.setSource(source, 2);
    //yee11x11.print();

    for(int n = 0; n < total_time / 60; n++){
        stringstream filename;
        fs::create_directory("image");
        filename << "image/" << "twosources-t" << n * 60 << ".png";
        twosources.saveAsImage(filename.str());

        twosources.yeeAlgorithm(60);
    }

    return 0;
}