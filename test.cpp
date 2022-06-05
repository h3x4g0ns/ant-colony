#include <iostream>
#include "algo.h"
#include <gsl/gsl_matrix.h>

using namespace std;

// simple travelling salesman problem for testing
void tsp_small_test() {
    printf("running tsp small test\n");

    // creating distance matrix
    float distances[16] = {0, 4, 1, 3, 
                        4, 0, 2, 5,
                        1, 2, 0, 5, 
                        3, 1, 5, 0};
    gsl_matrix *map_matrix = gsl_matrix_alloc(4, 4);
    for(int i = 0; i < 16; i++) {
        gsl_matrix_set(map_matrix, i / 4, i % 4, distances[i]);
    }

    // setting hyperparameters
    int num_ants = 10;
    float evaporation_rate = 0.1;
    float intensification = 2.0;
    float alpha = 1.0;
    float beta = 1.0;
    float beta_decay = 0.0;
    float rho = 0.1;

    // creating ant colony optimizer
    AntColonyOptimizer optimizer = AntColonyOptimizer(num_ants, evaporation_rate, intensification, alpha, beta, beta_decay, rho);

    // fitting distance matrix to optimizer
    int best = optimizer.fit_tsp(map_matrix);
    printf("best score: %d\n", best);
}

int main() {
    tsp_small_test();
    return 0;
}
