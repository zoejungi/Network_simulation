# Network_simulation
completed code

there are two ways to solve network::random_connect.

version 1: that's how I did: adding the number of links of poisson dis without taking already existing links ( degree of node_one ) into account. Now you only have to check that the poisson dis plus the degree of node_one isn't bigger than the values.size()

version 2: adding only the number of links missing. ->this version doesn't pass the tests.

size_t Network::random_connect(const double& mean_deg){
  links.clear();
	size_t nb(0);
	RandomNumbers rng;
	
	for(size_t node_one(0); node_one<values.size(); ++node_one){
		size_t _degree(rng.poisson(mean_deg));
		size_t _degreetoadd(_degree - degree(node_one))
    
		if(0<_degreetoadd and _degreetoadd < (values.size())){
			for(size_t link(0); link<_degreetoadd; ++link){
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
