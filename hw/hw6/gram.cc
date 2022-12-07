#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <time.h>

/*
  Daniel Zatko
  Homework 6
  Gram Shmidt
  I had some help with this assignment from Joey Perez for the dotProduct algorithm
  The normalization apparently works by row not column
  The outputs were also pretty strange
*/

using namespace std;

double dotProduct(double* a, double* b, int N){
  double result = 0;
  for(int i = 0; i < N; i++){
    result += a[i]*b[i];
  }
  return result;
}

void normalizeMatrix(double* matrix, int N){
  double colSum = 0;
  for(int j = 0; j < N; j++){
    colSum += matrix[j];
  }
  for(int j = 0; j < N; j++){
    matrix[j] /= sqrt(colSum);
  }
}

int main(){
  srand(time(NULL));
  int N;
  cout << "what size N would you like for your n x n matrix?" << endl;
  cin >> N;
//Initialize matrix with randoms
  double matrix[N][N];
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      matrix[i][j] = rand() % 9 + 1;
    }
  }
//Send matrix into ostream
  ofstream file("output_Gram.txt");
  file << "Original Matrix" << endl;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      file << matrix[i][j] << " ";
    }
    file << "\n";
  }
  file << endl;

//Time to normalize the matrix
//To do this you divide each column by the square root of its sum
  for(int i = 0; i < N; i++){
    normalizeMatrix(matrix[i],N);
  }

  //Lets put it into the text file now
  file << "Normalized Matrix" << endl;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < N; j++){
      file << matrix[i][j] << " ";
    }
    file << "\n";
  }
  file << endl;

//Start the Gram Shmidt Procecss
double u1;
  for(int i = 0; i < N; i++){
    for(int j = 0; j < i; j++){
      u1 = dotProduct(matrix[j], matrix[i], N) / dotProduct(matrix[j], matrix[j], N);
      for(int k = 0; k < N; k++){
        matrix[i][k] -= u1*matrix[j][k];
      }
    }
  }

//Output the grahm shmidt matrix
file << "Gram Shmidt Matrix" << endl;
for(int i = 0; i < N; i++){
  for(int j = 0; j < N; j++){
    file << matrix[i][j] << " ";
  }
  file << "\n";
}
file << endl;

//Normalize the Gram Shmidt Matrix or orthonormalize it
for(int i = 0; i < N; i++){
  normalizeMatrix(matrix[i],N);
}

//Output the final matrix
file << "Final Matrix" << endl;
for(int i = 0; i < N; i++){
  for(int j = 0; j < N; j++){
    file << matrix[i][j] << " ";
  }
  file << "\n";
}
file << endl;

}
