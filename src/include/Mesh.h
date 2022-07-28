#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>
#include <iostream>

#ifndef HEATMAP_HEADER
#include "Heatmap.h"
#define HEATMAP_HEADER
#endif

using namespace std;

struct XYCoord {
    int coordX;
    int coordY;
    double value;
};

struct MeshElem {
    bool isSource = 0;
    double value = 0;
};

class Mesh {
public:
    Mesh(); 
    Mesh(int size, int total_time, double sigma, double sigmaM, double epsilon, double mu,
        double delta, double deltaT);
    ~Mesh();
    // TODO add setters for sigma, sigmaM, epsilon, mu, delta and deltaT
        //dont do it for size and total_time
    void setSource(XYCoord *source, int len) const;
    void setInitial(XYCoord *initial, int len) const; 
    void yeeAlgorithm();
    void print() const;
    double **getValues(int time) const;
    void saveAsImage() const; // TODO implement image saving directly from this class
    void saveAsVideo() const; // TODO research an appropriate api for this

private:
    double sigma;
    double sigmaM;
    double epsilon;
    double mu;

    int size;
    int total_time;

    double delta;
    double deltaT;

    MeshElem ***E_z, ***H_y, ***H_x;
};