#include "include/Mesh.h"

Mesh::Mesh()
{
    sigma = sigmaM = 0;
    epsilon = 8.85418782 * 10E-12;
    mu = 4 * M_PI * 10E-7;

    size = 11;
    total_time = 10;

    delta = 100.0;
    deltaT = delta/(299792458 * sqrt(2));

    E_z = new MeshElem**[total_time];
    assert(E_z != 0);
    for(int i = 0; i < total_time; i++){
        E_z[i] = new MeshElem*[size];
        assert(E_z[i] != 0);
        for(int j = 0; j < size; j++){
            E_z[i][j] = new MeshElem[size];
            assert(E_z[i][j] != 0);
        }
    }

    H_y = new MeshElem**[total_time];
    assert(H_y != 0);
    for(int i = 0; i < total_time; i++){
        H_y[i] = new MeshElem*[size + 1];
        assert(H_y[i] != 0);
        for(int j = 0; j < size + 1; j++){
            H_y[i][j] = new MeshElem[size];
            assert(H_y[i][j] != 0);
        }
    }

    H_x = new MeshElem**[total_time];
    assert(H_x != 0);
    for(int i = 0; i < total_time; i++){
        H_x[i] = new MeshElem*[size + 1];
        assert(H_x[i] != 0);
        for(int j = 0; j < size; j++){
            H_x[i][j] = new MeshElem[size + 1];
            assert(H_x[i][j] != 0);
        }
    }
}

Mesh::Mesh(int size, int total_time, double sigma, double sigmaM, double epsilon, double mu,
    double delta, double deltaT) 
        : size(size), total_time(total_time), sigma(sigma), sigmaM(sigmaM), epsilon(epsilon), 
        mu(mu), delta(delta), deltaT(deltaT)
{
    E_z = new MeshElem**[total_time];
    assert(E_z != 0);
    for(int i = 0; i < total_time; i++){
        E_z[i] = new MeshElem*[size];
        assert(E_z[i] != 0);
        for(int j = 0; j < size; j++){
            E_z[i][j] = new MeshElem[size];
            assert(E_z[i][j] != 0);
        }
    }

    H_y = new MeshElem**[total_time];
    assert(H_y != 0);
    for(int i = 0; i < total_time; i++){
        H_y[i] = new MeshElem*[size + 1];
        assert(H_y[i] != 0);
        for(int j = 0; j < size + 1; j++){
            H_y[i][j] = new MeshElem[size];
            assert(H_y[i][j] != 0);
        }
    }

    H_x = new MeshElem**[total_time];
    assert(H_x != 0);
    for(int i = 0; i < total_time; i++){
        H_x[i] = new MeshElem*[size + 1];
        assert(H_x[i] != 0);
        for(int j = 0; j < size; j++){
            H_x[i][j] = new MeshElem[size + 1];
            assert(H_x[i][j] != 0);
        }
    }
}

Mesh::~Mesh()
{
    for(int i = 0; i < total_time; i++){
        for(int j = 0; j < size; j++)
            delete []E_z[i][j];
        delete []E_z[i];
    }
    delete []E_z;

    for(int i = 0; i < total_time; i++){
        for(int j = 0; j < size + 1; j++)
            delete []H_y[i][j];
        delete []H_y[i];
    }
    delete []H_y;

    for(int i = 0; i < total_time; i++){
        for(int j = 0; j < size; j++)
            delete []H_x[i][j];
        delete []H_x[i];
    }
    delete []H_x;
}

void Mesh::setSource(XYCoord *source, int len) const
{
    for(int i = 0; i < len; i++){
        E_z[0][source[i].coordX][source[i].coordY].value = source[i].value;
        E_z[0][source[i].coordX][source[i].coordY].isSource = true;
    }
}

void Mesh::setInitial(XYCoord *initial, int len) const
{
    for(int i = 0; i < len; i++){
        E_z[0][initial[i].coordX][initial[i].coordY].value = initial[i].value;
        E_z[0][initial[i].coordX][initial[i].coordY].isSource = true;
    }
}

void Mesh::yeeAlgorithm()
{
    // defining constants for the sake of brevity in math expressions
    double C_a = (1 - sigma * deltaT / (2 * epsilon)) / (1 + sigma * deltaT / (2 * epsilon));
    double C_b = (deltaT / (epsilon * delta)) / (1 + sigma * deltaT / (2*epsilon));
    double D_a = (1 - sigmaM * deltaT / (2 * mu)) / (1 + sigmaM * deltaT / (2 * mu));
    double D_b = (deltaT / (mu*delta)) / (1 + sigmaM * deltaT / (2*mu));

    for(int n = 1; n < total_time; n++){
        for(int i = 0; i < size; i++){ // update mesh E_z
            for(int j = 0; j < size; j++){
                E_z[n][i][j].value = C_a * E_z[n-1][i][j].value + 
                    C_b*(H_y[n-1][i+1][j].value - H_y[n-1][i][j].value + 
                         H_x[n-1][i][j].value - H_x[n-1][i][j+1].value);
            }
        }
        // reapplying source to E_z 
        // TODO save source in the class to make this more efficient, use a linked list?
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(E_z[0][i][j].isSource)
                    E_z[n][i][j].value = E_z[0][i][j].value;
            }
        }

        for(int j = 0; j < size; j++){ //update mesh H_x
            H_y[n][0][j].value = D_a * H_y[n-1][0][j].value + D_b * E_z[n][0][j].value;
            for(int i = 1; i < size; i++)
                H_y[n][i][j].value = D_a * H_y[n-1][i][j].value + 
                    D_b * (E_z[n][i][j].value - E_z[n][i-1][j].value);
            H_y[n][size][j].value = D_a * H_y[n-1][size][j].value + D_b * (-E_z[n][size-1][j].value);
        }

        for(int i = 0; i < size; i++){
            H_x[n][i][0].value = D_a * H_x[n-1][i][0].value + D_b * (-E_z[n][i][0].value);
            for(int j = 1; j < size; j++){
                H_x[n][i][j].value = D_a * H_x[n-1][i][j].value + 
                    D_b * (E_z[n][i][j-1].value - E_z[n][i][j].value);
            }
            H_x[n][i][size].value = D_a * H_x[n-1][i][size].value + D_b * E_z[n][i][size-1].value;
        }
    }
}

void Mesh::print() const
{
    //for now we'll only print E_z
    cout << "Result E_z:\n";
    for(int n = 0; n < total_time; n++){
        cout << "Time " << n << " : \n";
        for(int i = 0; i < size; i++){
            cout << "Line " << i << " : ";
            for(int j = 0; j < size; j++){
                printf("%e ", E_z[n][i][j]);
            }
            cout << "\n";
        }
        cout << endl;
    }
}

double** Mesh::getValues(int time) const
{
    assert(time < total_time);
    double **values = new double*[size];
    for(int i = 0; i < size; i++){
        values[i] = new double[size];
        for (int j = 0; j < size; j++){
            values[i][j] = E_z[time][i][j].value;
        }
    }
    return values;
}

void Mesh::saveAsImage() const
{

}

void Mesh::saveAsVideo() const
{

}

