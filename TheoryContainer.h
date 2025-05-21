#include <iostream>
#include <math>
#include <Eigen/Dense>
#include <Tensor.h>
#include <Theory.h>


class TheoryContainer {

	private:

		//Matrix for strings
		//Matrix for tensor multiplet
		//anomally contribution Delta = H-V+29T <= this should be zero for 6d supergravity 
		//# of tensor multiplets
		//gauge algebras <- how?
		//# of theories included in this container 


	public:

		void AddTensorMultiplet(int charge, //index for tensormult matrix? );
		void AddLink(//gauge alg, link type, blowups, index for string matrix);
		void AddNode(int charge, //index for string matrix);
		void GetTheory(int theory_number);
