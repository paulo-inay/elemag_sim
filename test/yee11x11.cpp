#include "Elemag_Sim.h"

#ifndef PNG_HEADER
#include "include/png++/png.hpp"
#define PNG_HEADER
#endif

#include <cmath>
#include <iostream>
#include <sstream>
using namespace std;

int main(){
    Mesh yee11x11 = Mesh();

    XYCoord source;
    source.coordX = source.coordY = 5;
    source.value = 1.0;

    yee11x11.setSource(&source, 1);

    for(int n = 0; n < 10; n ++){
        cout << "########### STEP " << n << " ###########" << "\n";
        cout << "MESH" << "\n";
        yee11x11.print();

        cout << "HEATMAP" << "\n";
        Heatmap heatmap = Heatmap(11, 11, yee11x11.getValues(MESH_EZ));
        heatmap.print(); // the reason why we create a local heatmap is to check the values of 
                         //a heatmap class
        cout << endl;
        stringstream filename;
        filename << "11x11-t" << n << ".png";
        yee11x11.saveAsImage(filename.str());
        yee11x11.yeeAlgorithm(1);
    }

    return 0;
}