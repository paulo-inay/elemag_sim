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
    Mesh yee101x101 = Mesh(rows, columns, sigma, sigmaM, epsilon, mu, delta, deltaT);

    XYCoord source;
    source.coordX = source.coordY = 50;
    source.value = 1.0;

    for(int n = 0; n <= total_time; n++){
        source.value = sin(n/100.0) + 1;
        yee101x101.setSource(&source, 1);

        if(n % 60 == 0) {stringstream filename;
            fs::create_directory("image");
            filename << "image/" << "sinewave-t" << n << ".png";
            yee101x101.saveAsImage(filename.str());
        }
        yee101x101.yeeAlgorithm(1);
    }

    return 0;
}