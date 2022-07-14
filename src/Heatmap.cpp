#include "include/Heatmap.h"

static int** normalize(double **dvalues, int sizeX, int sizeY){

    double max = 0.0, min = 0.0;
    for (int i = 0; i < sizeX; i++){
        for (int j = 0; j < sizeY; j++){
            if(dvalues[i][j] > max) max = dvalues[i][j];
            if(dvalues[i][j] < min) min = dvalues[i][j];
        }
    }

    double logmax = log(max - min + 1.0);
    int **ivalues = new int*[sizeX];
    assert(ivalues != 0);
    for(int i = 0; i < sizeX; i++){
        ivalues[i] = new int[sizeY];
        assert(ivalues[i] != 0);
    }

    for(int i = 0; i < sizeX; i++){
        for(int j = 0; j < sizeY; j++){
            ivalues[i][j] = lrint(255*(log(dvalues[i][j] - min + 1.0)/logmax));
        }
    }

    return ivalues;

}

Heatmap::Heatmap(int sizeX, int sizeY, double **dvalues) : sizeX(sizeX), sizeY(sizeY)
{
    values = normalize(dvalues, sizeX, sizeY);
}

Heatmap::~Heatmap()
{
    for(int i = 0; i < sizeX; i++)
        delete []values[i];
    delete values;
}

void Heatmap::print()
{
    for(int i = 0; i < sizeX; i++){
        for(int j = 0; j < sizeY; j++){
            cout << values[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << endl;
}

void Heatmap::saveAsImage(string filename)
{
    png::image< png::rgb_pixel > image(sizeY,sizeX);
    for(size_t y = 0; y < image.get_height(); y++){
        for(size_t x = 0; x < image.get_width(); x++){
            image[y][x] = png::rgb_pixel(values[x][y], values[x][y], values[x][y]);
        }
    }
    image.write(filename);
}