#include "network.h"
#include <iostream>
#include "random.h"


Network::Network(){}

void Network::resize(const size_t& new_size){
	values.clear();
	values.resize(new_size);
	
	RandomNumbers rng;
	for (auto& node : values){
		node = rng.normal();
	}
}

bool Network::add_link(const size_t& a, const size_t& b){
	bool inserted(false);
	bool _neighbors(false);
	
	for (auto n : neighbors(a)){
		if (n == b){ 
			_neighbors = true;
			return inserted;
		}
	}
	
	if(a < values.size() and b < values.size() and a!=b and !_neighbors){
		links.insert(std::pair<size_t, size_t> (a, b));
		links.insert(std::pair<size_t, size_t> (b, a));
		inserted = true;
	}
	
	return inserted;
}

size_t Network::random_connect(const double& mean_deg){
	links.clear();
	size_t nb(0);
	RandomNumbers rng;
	
	for(size_t node_one(0); node_one<values.size(); ++node_one){
		size_t _degree(rng.poisson(mean_deg));
		
		if(0<_degree and _degree < (values.size()-degree(node_one))){
			for(size_t link(0); link<_degree; ++link){
				size_t node_two;
				do{
					node_two = rng.uniform_int(0, values.size());	
				}while (!add_link(node_one, node_two));
				++nb;
			}
		}
	}
	
	return nb;
}

size_t Network::set_values(const std::vector<double>& new_values){
	size_t nb_set(0);
	
	if (new_values.size() < values.size()){
		for (size_t i(0); i < new_values.size(); ++i){
			values[i] = new_values[i];
			++nb_set;
		}
	}else{
		for (size_t i(0); i < values.size(); ++i){
			values[i] = new_values[i];
			++nb_set;
		}	
	}

	return nb_set;
}

size_t Network::size() const{
	return values.size();
}

size_t Network::degree(const size_t& _n) const{
	return links.count(_n);
}

double Network::value(const size_t& _n) const{
	return values[_n];
}

std::vector<double> Network::sorted_values() const{
	std::vector<double> sorted_val (values);
	std::sort(sorted_val.begin(), sorted_val.end(), std::greater<double>());
	
	return sorted_val;
}

std::vector<size_t> Network::neighbors(const size_t& _n) const{
	std::vector<size_t> _neighbors;
	
	if (!links.empty() and degree(_n) != 0){
		auto range = links.equal_range(_n);
		for (auto it (range.first); it != range.second; ++it){
			_neighbors.push_back(it->second);
		}
	}

	return _neighbors;
}
