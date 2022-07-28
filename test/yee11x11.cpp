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

    cout << "############### YEE ALGORITHM ###############" << endl;
    yee11x11.setSource(&source, 1);
    yee11x11.yeeAlgorithm();
    yee11x11.print();


    cout << "############### HEATMAP  ###############" << endl;
    for(int n = 0; n < 10; n ++){
        double **dvalues = yee11x11.getValues(n);
        Heatmap heatmap = Heatmap(11, 11, dvalues);
        for(int i = 0; i < 11; i++)
            delete []dvalues[i];
        delete dvalues;

        cout << "Heatmap " << n << ":" << "\n";
        heatmap.print();
        cout << endl;
        stringstream filename;
        filename << "11x11-t" << n << ".png";
        heatmap.saveAsImage(filename.str());
    }

    return 0;
}