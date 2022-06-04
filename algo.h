#include <iostream>
#include <gsl/gsl_matrix.h>
#include <vector>
#include <numeric>
#include <random>

template <typename T, typename A>
int arg_max(vector<T, A> const& vec) {
  	return static_cast<int>(distance(vec.begin(), max_element(vec.begin(), vec.end())));
}

template <typename T, typename A>
int arg_min(vector<T, A> const& vec) {
  	return static_cast<int>(distance(vec.begin(), min_element(vec.begin(), vec.end())));
}

template <typename T, typename A>
int sum(vector<T, A> const& vec) {
	return std::accumulate(available_node.segin(), available_nodes.end(), decltype(vector)::value_type(0));
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
	vector<int> available_nodes;	// available nodes

	int* best_series 				// best series
	int best_score; 				// best score
	int fitted; 					// fitted or not
	int* best_path; 				// best path
	float fit_time; 				// time to fit

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
				gsl_matrix_set(probability, i, j, gsl_matrix_get(pheromone, i, j) ** alpha * gsl_matrix_get(heuristic, i, j) ** beta);
			}
		}
	}

	int chose_next_node(int from_node) {
		// finding probabilities of all the next nodes
		vector<float> numerator;
		for(int i = 0; i < available_nodes.size(); i++) {
			numerator.push_back(gsl_matrix_get(probability, from_node, available_nodes[i]));
		}

		// if p < rho, then best path is chosen
		// otherwise use pheremone to choose next node
		if rand() % 1 < rho {
			return arg_max(available_nodes);
		} else {
			int denominator = sum(available_nodes);
			vector<int> probabilities;
			for(int i = 0; i < numerator.size(); i++) {
				probabilities.push_back(numerator[i] / denominator);
			}
			
			// randomly choosing integer from 0 to size of probabilities
			// based on given probabilities
			discrete_distribution<float> distribution(probabilities.begin(), probabilities.end());
			default_random_engine dre;
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

	vector<int> evaluate()
}
