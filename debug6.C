#include <iostream>
#include "Theory.h"



int main() {


	int base;

	Theory* TEST = new Theory();

	TEST->Initialize();
	base = 4;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);

	TEST->AL(2,3);
	TEST->AT(-8);


	

	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	
		TEST->Setb0Q();

		Theory B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND // INTERSECTIONF FORM " << std::endl;
			std::cout << B.GetIFb0Q() << std::endl;
			
			B.FBlowdown();

			std::cout << B.GetIFb0Q() << std::endl;

			int d = B.GetExactDet();
			int sig = B.TimeDirection();
			

			B.ForcedBlowdown();
			std::cout << B.GetIFb0Q() << std::endl;

		
		}
		else if(c==0)
		{
			std::cout << " NOT SUGRA" << std::endl;

			B.ForcedBlowdown();
			std::cout << B.GetIFb0Q() << std::endl;
		}
		
		

	

	delete TEST;


}
