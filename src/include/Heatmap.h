#ifndef PNG_HEADER
#include "include/png++/png.hpp"
#define PNG_HEADER
#endif

#include <cmath>
#include <cassert>
#include <iostream>
#include <string>
using namespace std;

static int** normalize(double **dvalues, int sizeX, int sizeY);

class Heatmap {
public:
    Heatmap(int sizeX, int sizeY, int **values) : sizeX(sizeX), sizeY(sizeY), values(values){};
    Heatmap(int sizeX, int sizeY, double **dvalues);
    ~Heatmap();
    void print();
    int **values;
    void saveAsImage(string filename);
private:
    int sizeX;
    int sizeY;
};