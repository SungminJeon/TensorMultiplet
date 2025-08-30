#include <iostream>
#include "Tensor.h"


int main() {

	Tensor* TEST = new Tensor();


	TEST->AT(-12);
	TEST->AT(-1);
	TEST->AT(-13);
	TEST->AT(-14);
	TEST->AT(-15);

	TEST->intersect(2,1);
	TEST->intersect(2,3,3);
	TEST->intersect(2,4,2);
	TEST->intersect(4,3,17);


	TEST->Setb0Q();


	std::cout << " BLOWDOWN TEST " << std::endl;
	std::cout << TEST->GetIntersectionForm() << std::endl;

	std::cout << " after BLOWDOWN " << std::endl;
	TEST->Blowdown5(2); 
	std::cout << TEST->GetIntersectionForm() << std::endl;



	TEST->Initialize();

	TEST->AL(2,2);

	std::cout << TEST->GetIntersectionForm() << std::endl;
	delete TEST;



}
