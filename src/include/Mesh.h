#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>
#include <iostream>
#include <list>
#include <iterator>

#ifndef HEATMAP_HEADER
#include "Heatmap.h"
#define HEATMAP_HEADER
#endif

using namespace std;

enum MESH_TYPE {MESH_EZ, MESH_HY, MESH_HX, MESH_END};

struct XYCoord {
    int coordX;
    int coordY;
    double value;
};

struct MeshElem {
    //bool isSource = false;
    double value = 0;
};

class Mesh {
public:
    Mesh(); 
    Mesh(int rows, int columns, double sigma, double sigmaM, double epsilon, double mu,
        double delta, double deltaT);
    ~Mesh();
    // TODO add setters for sigma, sigmaM, epsilon, mu, delta and deltaT
        //dont do it for size and total_time
    void setSource(XYCoord *source_input, int len);
    void setInitial(XYCoord *initial, int len) const; 
    void yeeAlgorithm(int steps);
    void print() const;
    double **getValues(int mesh_type) const;
    void saveAsImage(string filename) const; // TODO implement image saving directly from this class
    void saveAsVideo() const; // TODO research an appropriate api for this

private:
    double sigma;
    double sigmaM;
    double epsilon;
    double mu;

    int rows, columns;

    double delta;
    double deltaT;

    MeshElem **E_z, **H_y, **H_x;
    list<XYCoord> source;
};