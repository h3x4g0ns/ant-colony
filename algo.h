#include <iostream>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <vector>
#include <numeric>
#include <random>
#include <ctime>
#include <cmath>
#include <algorithm>

template <typename T, typename A>
int arg_max(std::vector<T, A> const& vec) {
  	return static_cast<int>(std::distance(vec.begin(), max_element(vec.begin(), vec.end())));
}

template <typename T, typename A>
int arg_min(std::vector<T, A> const& vec) {
  	return static_cast<int>(std::distance(vec.begin(), min_element(vec.begin(), vec.end())));
}

template <typename T, typename A>
int sum(std::vector<T, A> const& vec) {
	return std::accumulate(vec.begin(), vec.end(), 0);
}

	
class AntColonyOptimizer {
	public:
		int num_ants; 					// number of ants
		float evaporation_rate; 		// evaporation rate
		float intensification; 			// intensification constant	
		float alpha;					// weighing factor for pheromone
		float beta;						// weighing factor for heuristic
		float beta_decay;				// decay rate for beta
		float rho;						// probability of random choice

		gsl_matrix *pheromone; 			// pheromone matrix
		gsl_matrix *heuristic; 			// heuristic matrix
		gsl_matrix *probability; 		// probability matrix
		gsl_matrix *visited; 			// visited matrix
		std::vector<int> available_nodes;	// available nodes

		std::vector<int> best_series; 		// best series
		float best; 				// best score
		int fitted; 					// fitted or not
		std::vector<int> best_path; 			// best path
		float fit_time; 				// time to fit

	AntColonyOptimizer(int num_ants, float evaporation_rate, float intensification, float alpha, float beta, float beta_decay, float rho)  {
		this -> num_ants = num_ants;
		this -> evaporation_rate = evaporation_rate;
		this -> intensification = intensification;
		this -> alpha = alpha;
		this -> beta = beta;
		this -> beta_decay = beta_decay;
		this -> rho = rho;
	}

	void init() {
		// checking to make sure dimensions are same
		if(visited -> size1 != visited -> size2) {
			std::cout << "visited matrix is not square" << std::endl;
			return;
		}


		// initializing pheromone matrix
		int num_nodes = visited -> size1;
		pheromone = gsl_matrix_calloc(num_nodes, num_nodes);
		gsl_matrix_set_all(pheromone, 1.0);
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
			for(int j = 0; j < num_nodes; j++) {
				gsl_matrix_set(probability, i, j, pow(gsl_matrix_get(pheromone, i, j), alpha) * 
					pow(gsl_matrix_get(heuristic, i, j), beta));
			}
		}

		// initializing available_nodes
		for(int i = 0; i < num_nodes; i++) {
			available_nodes.push_back(i);
		}
	}

	void reinstate_nodes() {
		// reinstating available nodes
		available_nodes.clear();
		for(int i = 0; i < visited -> size1; i++) {
			available_nodes.push_back(i);
		}
	}

	void update_probabilities() {
		// updating probability matrix
		for(int i = 0; i < probability -> size1; i++) {
			for(int j = 0; j < probability -> size2; j++) {
				gsl_matrix_set(probability, i, j, pow(gsl_matrix_get(pheromone, i, j), alpha) * 
					pow(gsl_matrix_get(heuristic, i, j), beta));
			}
		}
	}

	int chose_next_node(int from_node) {
		// finding probabilities of all the next nodes
		std::vector<float> numerator;
		for(int i = 0; i < available_nodes.size(); i++) {
			numerator.push_back(gsl_matrix_get(probability, from_node, available_nodes[i]));
		}

		// if p < rho, then best path is chosen
		// otherwise use pheremone to choose next node
		if(rand() % 1 < rho) {
			return arg_max(available_nodes);
		} else {
			int denominator = sum(available_nodes);
			std::vector<int> probabilities;
			for(int i = 0; i < numerator.size(); i++) {
				probabilities.push_back(numerator[i] / denominator);
			}
			
			// randomly choosing integer from 0 to size of probabilities
			// based on given probabilities
			std::discrete_distribution<> distribution(probabilities.begin(), probabilities.end());
			std::default_random_engine dre;
			int next_node = distribution(dre);
			return available_nodes[next_node];
		}
	}

	void remove_node(int node) {
		// removing node from available_nodes
		for(int i = 0; i < available_nodes.size(); i++) {
			if(available_nodes[i] == node) {
				available_nodes.erase(available_nodes.begin() + i);
				break;
			}
		}
	}

	std::vector<std::vector<int> > evaluate(std::vector<std::vector<int> > paths, int mode) {
		// evaluating paths
		std::vector<int> scores(paths.size(), 0);
		std::vector<std::vector<int> > coordinates_i;
		std::vector<std::vector<int> > coordinates_j;
		
		// iterating through every path and evaluating it
		for(int i = 0; i < paths.size(); i++) {
			int score = 0;
			std::vector<int> cord_i;
			std::vector<int> cord_j;
			for(int j = 0; j < paths[i].size(); j++) {
				cord_i.push_back(paths[i][j]);
				cord_j.push_back(paths[i][j+1]);
				score += gsl_matrix_get(visited, paths[i][j], paths[i][j+1]);
			}

			scores[i] = score;
			coordinates_i.push_back(cord_i);
			coordinates_j.push_back(cord_j);
		}			

		// returning best path based on mode
		int best;
		if(mode == 0) {
			best = arg_min(scores);
		} else {
			best = arg_max(scores);
		}
		std::vector<std::vector<int> > return_value;
		return_value.push_back(coordinates_i[best]);
		return_value.push_back(coordinates_j[best]);
		return_value.push_back(paths[best]);
		std::vector<int> vect;
		vect.push_back(scores[best]);
		return_value.push_back(vect);
		return return_value;
	}

	void evaporation() {
		// evaporating pheromone matrix
		for(int i = 0; i < pheromone -> size1; i++) {
			for(int j = 0; j < pheromone -> size2; j++) {
				gsl_matrix_set(pheromone, i, j, gsl_matrix_get(pheromone, i, j) * (1-beta));
				gsl_matrix_set(heuristic, i, j, gsl_matrix_get(heuristic, i, j) * (1-beta_decay));
			}
		}
	}

	void intensify(int coord_i, int coord_j) {
		// intensifying pheromone matrix for given coordinate
		int prev = gsl_matrix_get(pheromone, coord_i, coord_j);
		gsl_matrix_set(pheromone, coord_i, coord_j, prev * intensification);
	}

	int fit_tsp(gsl_matrix *map_matrix, int iterations=100, int mode = 0, int early_stopping = 20) {
		// fitting given distance travelling salesman problem to optimizer
		printf("beginning aco optimization fit with %d iterations\n", iterations);
		visited = map_matrix;
		time_t start = time(0);
		init();
		int num_equal = 0;

		for(int i = 0; i < iterations; i++) {
			time_t start_iter = time(0);
			std::vector<std::vector<int> > paths;
			std::vector<int> path;

			for(int j = 0; j < num_ants; j++) {
				int current_node = rand() % available_nodes.size();
				int start_node = current_node;
				while(1) {
					path.push_back(current_node);
					remove_node(current_node);
					if(!available_nodes.empty()) {
						int idx = chose_next_node(current_node);
						current_node = available_nodes[idx];
					} else {
						break;
					}
				}

				// adding path to paths
				path.push_back(start_node);
				reinstate_nodes();
				paths.push_back(path);
				path.clear();
			}

			// evaluating paths and unpacking			
			std::vector<std::vector<int> > results = evaluate(paths, mode);
			int best_path_coord_i = results[0][0];
			int best_path_coord_j = results[1][0];
			std::vector<int> best_path = results[2];
			float best_score = results[3][0];

			float best_current_score = 0;
			if(i == 0) {
				best_current_score = best_score;
			} else {
				if(mode == 0) {
					if(best_score < best_current_score) {
						best_current_score = best_score;
						this -> best_path = best_path;
					}
				} else if(mode == 1) {
					if(best_score > best_current_score) {
						best_current_score = best_score;
						this -> best_path = best_path;
					}
				} 

				if(best_score == best_current_score) {
					num_equal += 1;
				} else {
					num_equal = 0;
				}

				best_series.push_back(best_score);
				evaporation();
				intensify(best_path_coord_i, best_path_coord_j);

				printf("best score at iteration %d: %.3f; overall: %.3f (%.2fs)", i, best_score, best_current_score, difftime(time(0), start_iter));

				if(best_score == best_current_score && num_equal == early_stopping) {
					printf("\nstopping early with %d iterations completed\n", early_stopping);
					break;
				}
			}
		}

		fit_time = difftime(time(0), start);
		fitted = 1;

		if(mode == 0) {
			best = best_series[arg_min(best_series)];
			printf("aco fit completed with best score: %.3f (%.2fs)", best, fit_time);
			return best;
		} else if(mode == 1) {
			best = best_series[arg_max(best_series)];
			printf("aco fit completed with best score: %.3f (%.2fs)", best, fit_time);
			return best;
		} else {
			printf("invalid mode: select 0 for min or 1 for max");
			return -1;
		}
	}
};
