#include <iostream>
#include <fstream>
#include <vector>
#include "Theory.h"

int main() {


	Theory* TEST = new Theory();



	int base = 1;

	std::cout << base << std::endl;

	//LST links and base should be added.. estimated by ~300??
	//
	//
	
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	//TEST->AL(1,1); TEST->AT(-4);
	
	TEST->AT(-1);
	TEST->AT(-2);


	std::cout << TEST->GetDeterminant() << std::endl;
	std::cout << TEST->GetSignature() << std::endl;



	TEST->Initialize(); 


	base = 2;

	std::cout << base << std::endl;

	//LST links and base should be added.. estimated by ~300??
	//
	//
	
	
	TEST->AT(-1);
	TEST->ATS(-1,-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	//TEST->AL(1,1); TEST->AT(-4);
	
	TEST->AL(1,1);
	TEST->ATS(-1,-4);
	TEST->AT(-1);



	std::cout << TEST->GetDeterminant() << std::endl;
	std::cout << TEST->GetSignature() << std::endl;



	TEST->Initialize(); 

	base = 3;

	std::cout << base << std::endl;

	//LST links and base should be added.. estimated by ~300??
	//
	//
	
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	//TEST->AL(1,1); TEST->AT(-4);
	
	TEST->AT(-1);
	TEST->AT(-2);


	std::cout << TEST->GetDeterminant() << std::endl;
	std::cout << TEST->GetSignature() << std::endl;



	TEST->Initialize(); 

	TEST->AT(-2);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-2);

	std::cout << TEST->GetDeterminant() << std::endl;
	std::cout << TEST->GetSignature() << std::endl;

}







