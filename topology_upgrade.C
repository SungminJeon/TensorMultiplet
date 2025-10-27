#include <iostream>
#include <fstream>
#include <string>
#include "Theory.h"
#include "Tensor.h"




// 1. what I want is to store the data of basic structure of the base
// 2. and from that data, we could attach new links or nodes to it then check whether it is scft or lst or sugra..


enum LKind {g,L,S,I}

struct Block { LKind kind, int param }

struct topology { // want to make data set!
	std::string name;
	std::vector<node> nodes;
	std::vector<link> link;
	std::vector<slink> slink;
	std::vector<instanton> instanton;
	std::vector<std::pair<int,int>> base; // here, define the node-interior link structure
	std::vector<std::pair<int,int>> decoration; //decoration at last..


}


static inline void topology_sweeper(topology top) {

	// 1. for node bank. 4,6,7,8,12  choose maximal value for entire base structure. 
	// 2. for this descr ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffsdsfdfdfsdfsdfsdfsdfsdfsssssssdfssdfssssdfsdfsdfsdfssdfsdfsdfsdfffffsdfffffddfdfd	
