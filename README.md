# Ant Colony Optimization in C++

naive, but mostly efficient, implementation of the Ant Colony optimization algo in C++

## Main Idea

Ants traverse paths and return pheremones to indicate the strength of the traversal. Stronger pheremones indicate the presence of a more optimal solution.

**Input:** A grid map, a motion model, current cell $m_u$, next cell $m_t$, an ant colony divided into different sub-cohorts ${A_1,A_2,··· ,A_c,··· ,A_C}$, each sub-cohort $A_c$ with velocity $c$.

**Output:** An optimal path that covers the whole free space.

1. for sub-cohort $A_c$ ∈ $A$ do
2. &nbsp;&nbsp;&nbsp;&nbsp;for ant $a_{l_c}$ ∈ $A_c$ do
3. &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Choose next cell mt according to equations (4) to
(6).
4. &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Update local and global pheromone trail according
to equations (7) and (8).
5. &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Repeat the above two steps until converge.
6. &nbsp;&nbsp;&nbsp;&nbsp;end for
7. end for
8. Choose and return the optimal path found.


## Running tests

A couple included tests are running instances of the Travelling Salesman Problem. While the ACO algo is best known for NP-Hard problems, the versatility of this algo is quite broad. Problems for the TSP are inputted as distance matrices, although it wouldn't require too many changes in order to reduce the problem into something else altogether.

Run `make test` to run all included tests in `test.cpp`.

### Adding tests

The included tests all run variations of TSP. Here's an example of the input.

```cpp
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
```

## Further Study

- [ ] look into FaSCO for seeing how velocities of the ants can possibly shorten computations required for NP-Hard problems

## Links

- [original paper for implementation](https://arxiv.org/pdf/2205.15691.pdf)
- [similar python implentation](https://github.com/johnberroa/Ant-Colony-Optimization/blob/master/AntColonyOptimizer.py)
- [gsl: c/c++'s numpy](https://www.gnu.org/software/gsl/doc/html/vectors.html)
- [discrete distributions](http://candcplusplus.com/c11-discrete-distribution-random-number-generator)
