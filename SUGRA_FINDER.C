#include <iostream>
#include "Theory.h"
#include <vector>
#include <fstream>

int main()
{

	int base;



	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  
	
	base = 1;

	Theory* TEST = new Theory();


	TEST->AT(-1);
	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-3);

	std::cout << TEST->GetIntersectionForm() << std::endl;


	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		std::cout << TEST->GetIntersectionForm() << std::endl;
		TEST->Setb0Q();

		Theory B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND" << std::endl;
			B.FBlowdown();

			std::cout << B.GetIFb0Q() << std::endl;

		}
		else 
		{
			std::cout << "NOT SUGRA" << std::endl;
			break;
		}

		TEST->DeleteTensorMultiplet();
	}





	delete TEST;
}





