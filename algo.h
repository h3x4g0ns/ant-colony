#include <iostream>
#include <gsl/gsl_matrix.h>
#include <vector>

class AntColonyOptimizer {
	public:
		int num_ants; 							// number of ants
		float evaporation_rate; 		// evaporation rate
		float intensification; 			// intensification constant	
		float alpha;								// weighing factor for pheromone
		float beta;									// weighing factor for heuristic
		float beta_decay;						// decay rate for beta
		float rho;									// probability of random choice

		gsl_matrix *pheromone; 			// pheromone matrix
		gsl_matrix *heuristic; 			// heuristic matrix
		gsl_matrix *probability; 		// probability matrix
		gsl_matrix *visited; 				// visited matrix
		vector<int> available_nodes;// available nodes

		int* best_series 						// best series
		int best_score; 						// best score
		int fitted; 								// fitted or not
		int* best_path; 						// best path
		float fit_time; 						// time to fit

		AntColonyOptimizer(int num_ants, float evaporation_rate, float intensification, float alpha, float beta, float beta_decay, float rho)  {
			num_ants = num_ants;
			evaporation_rate = evaporation_rate;
			intensification = intensification;
			alpha = alpha;
			beta = beta;
			beta_decay = beta_decay;
			rho = rho;
		}

		void init() {
			// checking to make sure dimensions are same
			if visited -> size1 != visited -> size2 {
				std::cout << "visited matrix is not square" << std::endl;
				return;
			}


			// initializing pheromone matrix
			int num_nodes = visited -> size1;
			pheromone = gsl_matrix_calloc(num_nodes, num_nodes);
			gsl_matrix_set(pheromone, 1.0);
			for(int i = 0; i < num_nodes; i++) {
				gsl_matrix_set(pheromone, i, i, 0.0);
			}

			// initializing heuristic matrix
			heuristic = gsl_matrix_calloc(num_nodes, num_nodes);
			for(int i = 0; i < num_nodes; i++) {
				for(int j = 0; j < num_nodes; j++) {
					gsl_matrix_set(heuristic, i, j, 1.0/gsl_matrix_get(visited, i, j));
				}
			}

			// initializing probability matrix
			probability = gsl_matrix_calloc(num_nodes, num_nodes);
			for(int i = 0; i < num_nodes; i++) {
				for(int j = 0; j < num_nodes; i++) {
					gsl_matrix_set(probability, i, j, gsl_matrix_get(pheromone, i, j) ** alpha * gsl_matrix_get(heuristic, i, j) ** beta);
				}
			}

			// initializing available_nodes
			for(int i = 0; i < num_nodes; i++) {
				available_nodes.insert(i);
			}
}
