#include "include/Mesh.h"

Mesh::Mesh()
{
    sigma = sigmaM = 0;
    epsilon = 8.85418782 * 10E-12;
    mu = 4 * M_PI * 10E-7;

    rows = columns = 11;
    delta = 100.0;
    deltaT = delta/(299792458 * sqrt(2));

    E_z = new MeshElem*[rows];
    assert(E_z != 0);
    for(int i = 0; i < rows; i++){
        E_z[i] = new MeshElem[columns];
        assert(E_z[i] != 0);
    }

    H_y = new MeshElem*[rows + 1];
    assert(H_y != 0);
    for(int i = 0; i < rows + 1; i++){
        H_y[i] = new MeshElem[columns];
        assert(H_y[i] != 0);
    }

    H_x = new MeshElem*[rows];
    assert(H_x != 0);
    for(int i = 0; i < rows; i++){
        H_x[i] = new MeshElem[columns + 1];
        assert(H_x[i] != 0);
    }
}

Mesh::Mesh(int rows, int columns, double sigma, double sigmaM, double epsilon, double mu,
    double delta, double deltaT) 
        : rows(rows), columns(columns), sigma(sigma), sigmaM(sigmaM), epsilon(epsilon), 
        mu(mu), delta(delta), deltaT(deltaT)
{
    E_z = new MeshElem*[rows];
    assert(E_z != 0);
    for(int i = 0; i < rows; i++){
        E_z[i] = new MeshElem[columns];
        assert(E_z[i] != 0);
    }

    H_y = new MeshElem*[rows + 1];
    assert(H_y != 0);
    for(int i = 0; i < rows + 1; i++){
        H_y[i] = new MeshElem[columns];
        assert(H_y[i] != 0);
    }

    H_x = new MeshElem*[rows];
    assert(H_x != 0);
    for(int i = 0; i < rows; i++){
        H_x[i] = new MeshElem[columns + 1];
        assert(H_x[i] != 0);
    }
}

Mesh::~Mesh()
{

    for(int i = 0; i < rows; i++){
        delete []E_z[i];
    }
    delete []E_z;

    for(int i = 0; i < rows + 1; i++){
        delete []H_y[i];
    }
    delete []H_y;

    for(int i = 0; i < rows; i++){
        delete []H_x[i];
    }
    delete []H_x;

}

void Mesh::setSource(XYCoord *input, int len)
{
    source.clear();

    for(int i = 0; i < len; i++){
        source.push_back(input[i]);
        E_z[input[i].coordX][input[i].coordY].value = input[i].value;
    }
}

void Mesh::setInitial(XYCoord *initial, int len) const
{
    for(int i = 0; i < len; i++){
        E_z[initial[i].coordX][initial[i].coordY].value = initial[i].value;
    }
}

void Mesh::yeeAlgorithm(int steps)
{
    // defining constants for the sake of brevity in math expressions
    double C_a = (1 - sigma * deltaT / (2 * epsilon)) / (1 + sigma * deltaT / (2 * epsilon));
    double C_b = (deltaT / (epsilon * delta)) / (1 + sigma * deltaT / (2*epsilon));
    double D_a = (1 - sigmaM * deltaT / (2 * mu)) / (1 + sigmaM * deltaT / (2 * mu));
    double D_b = (deltaT / (mu*delta)) / (1 + sigmaM * deltaT / (2*mu));

    for(int n = 0; n < steps; n++){
        for(int i = 0; i < rows; i++){ // update mesh E_z
            for(int j = 0; j < columns; j++){
                E_z[i][j].value = C_a * E_z[i][j].value + 
                    C_b*(H_y[i+1][j].value - H_y[i][j].value + 
                         H_x[i][j].value - H_x[i][j+1].value);
            }
        }
        // reapplying source to E_z 
        list<XYCoord>::iterator s_pos;
        for(s_pos = source.begin(); s_pos != source.end(); s_pos++){
            E_z[s_pos->coordX][s_pos->coordY].value = s_pos->value;
        }

        for(int j = 0; j < columns; j++){ //update mesh H_y
            H_y[0][j].value = D_a * H_y[0][j].value + D_b * E_z[0][j].value;
            for(int i = 1; i < rows; i++)
                H_y[i][j].value = D_a * H_y[i][j].value + 
                    D_b * (E_z[i][j].value - E_z[i-1][j].value);
            H_y[rows][j].value = D_a * H_y[rows][j].value + D_b * (-E_z[rows-1][j].value);
        }

        for(int i = 0; i < rows; i++){ //update mesh H_x
            H_x[i][0].value = D_a * H_x[i][0].value + D_b * (-E_z[i][0].value);
            for(int j = 1; j < columns; j++){
                H_x[i][j].value = D_a * H_x[i][j].value + 
                    D_b * (E_z[i][j-1].value - E_z[i][j].value);
            }
            H_x[i][columns].value = D_a * H_x[i][columns].value + D_b * E_z[i][columns-1].value;
        }
    }
}

void Mesh::print() const
{
    //for now we'll only print E_z
    for(int i = 0; i < rows; i++){
        cout << "Line " << i << " : ";
        for(int j = 0; j < columns; j++){
            printf("%e ", E_z[i][j]);
        }
        cout << "\n";
    }
    cout << endl;
}

double** Mesh::getValues(int mesh_type) const
{

    double **values;

    assert(mesh_type < MESH_END);

    switch(mesh_type){
        case MESH_EZ:
            values = new double*[rows];
            for(int i = 0; i < rows; i++){
                values[i] = new double[columns];
                for (int j = 0; j < columns; j++){
                    values[i][j] = E_z[i][j].value;
                }
            }
        break;

        case MESH_HY:
            values = new double*[rows+1];
            for(int i = 0; i < rows+1; i++){
                values[i] = new double[columns];
                for (int j = 0; j < columns; j++){
                    values[i][j] = H_y[i][j].value;
                }
            }
        break;

        case MESH_HX:
            values = new double*[rows];
            for(int i = 0; i < rows; i++){
                values[i] = new double[columns+1];
                for (int j = 0; j < columns+1; j++){
                    values[i][j] = H_x[i][j].value;
                }
            }
        break;

        default:
            assert(true);
        break;
    }

    return values;
}

void Mesh::saveAsImage(string filename) const
{
    double **dvalues = this->getValues(MESH_EZ);
    Heatmap heatmap = Heatmap(rows, columns, dvalues);
    for(int i = 0; i < rows; i++)
        delete []dvalues[i];
    delete []dvalues;
    heatmap.saveAsImage(filename);
}

void Mesh::saveAsVideo() const
{

}

