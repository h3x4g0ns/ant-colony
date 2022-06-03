# Ant Colony Optimization in C++

naive, but mostly efficient, implementation of the Ant Colony optimization algo in C++

## Main Idea

Ants traverse paths and return pheremones to indicate the strength of the traversal. Stronger pheremones indicate the presence of a more optimal solution.

**Input:** A grid map, a motion model, current cell $m_u$, next cell $m_t$, an ant colony divided into different sub-cohorts ${A_1,A_2,··· ,A_c,··· ,A_C}$, each sub-cohort $A_c$ with velocity $c$.

**Output:** An optimal path that covers the whole free space.

1. for sub-cohort Ac ∈ A do
2. &nbsp;&nbsp;&nbsp;&nbsp;for ant alc ∈ Ac do
3. &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Choose next cell mt according to equations (4) to
(6).
4. &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Update local and global pheromone trail according
to equations (7) and (8).
5. &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Repeat the above two steps until converge.
6. &nbsp;&nbsp;&nbsp;&nbsp;end for
7. end for
8. Choose and return the optimal path found.

## Running Tests


## Links

- [original paper for implementation](https://arxiv.org/pdf/2205.15691.pdf)
- [similar python implentation](https://github.com/johnberroa/Ant-Colony-Optimization/blob/master/AntColonyOptimizer.py)
- [gsl library for complex math](https://www.gnu.org/software/gsl/doc/html/vectors.html)
