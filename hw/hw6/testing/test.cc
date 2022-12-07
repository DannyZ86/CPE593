#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

double dot_prod(double a[], double b[], int n){
    double prod = 0;
    for(int i = 0; i < n; i++){
        prod = prod + a[i]*b[i];
    }
    return prod;
}

void normalize(double *a, int n){
    int sum = 0;
    double magnitude;
    for(int i = 0; i < n; i++){
        sum += a[i];
    }
    magnitude = sqrt(sum);

    for(int i = 0; i < n; i++)
        a[i] /= magnitude;
}

int main(){
    int n = 3;
    // cin >> n;
    srand(0);

    ofstream output("gram_schmidt_output.txt");
    char out_string;

    //create and normalize matrix

    output << "Original Matrix" << endl;
    double matrix[n][n] = {0};

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = rand();
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            output << matrix[i][j] << " ";
        }
        output << endl;
    }

    output << endl;

    output << "Normalized Matrix" << endl;

    for(int i = 0; i < n; i++){
        normalize(matrix[i],n);
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            output << matrix[i][j] << " ";
        }
        output << endl;
    }

    output << endl;

    //gram schmidt
    double s_factor;
    double new_matrix[n][n];

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            new_matrix[i][j] = matrix[i][j];
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++){
            s_factor = dot_prod(matrix[j],matrix[i],n) / dot_prod(matrix[j],matrix[j],n);
            for(int k = 0; k < n; k++){
                new_matrix[i][k] -= s_factor*new_matrix[j][k];
            }
        }
    }

    output << "Orthogonal Matrix" << endl;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            output << new_matrix[i][j] << " ";
        }
        output << endl;
    }

    output << endl;

    output << "Normalized Orthogonal Matrix" << endl;

    for(int i = 0; i < n; i++){
        normalize(new_matrix[i],n);
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            output << new_matrix[i][j] << " ";
        }
        output << endl;
    }

    output.close();
    return 0;
}
