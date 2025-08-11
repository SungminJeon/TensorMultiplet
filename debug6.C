#include <iostream>
#include "Theory.h"



int main() {


	int base;

	Theory* TEST = new Theory();

	base = 4;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-6);
	TEST->AL(2,2);
	TEST->AT(-4);
	
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);

	TEST->AL(2,2);
	TEST->AT(-6);
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	std::cout << TEST->TimeDirection() << std::endl;
	std::cout << TEST->SpaceDirection() << std::endl;
	std::cout << TEST->NullDirection() << std::endl;
	

	//TEST->ATE(-1,21);
	TEST->Setb0Q();

	std::cout << TEST->GetIFb0Q() << std::endl;

	Theory B(*TEST);

	bool c = B.IsSUGRA();
	std::cout << B.GetExactDet() << std::endl;
	std::cout << B.GetEigenvalues() << std::endl;

	int bn = 0;
	bool k;
	
	//TEST->LSTBlowdown(2);


	for (int i = 1; i <= TEST->GetT(); i++)
	{
		if ( TEST->GetIntersectionForm()(i-1,i-1) == -1 && TEST->GetIntersectionForm()(i-1,0) ==0)
		{
			k = TEST->Blowdown5(i);
			std::cout << TEST->GetIFb0Q() << std::endl;
			bn++;
			i = 0;
		}
	}

	std::cout << TEST->GetIFb0Q() << std::endl;
	std::cout << bn << std::endl;



/*
	TEST->Initialize();
	TEST->AT(-1);
	TEST->AT(-6);
	TEST->AT(0);
	TEST->AT(4);

	TEST->Setb0Q();
*/
	std::cout << TEST->GetIFb0Q() << std::endl;

	std::cout << TEST->GetDeterminant() << std::endl;

	std::cout << TEST->GetEigenvalues() << std::endl;


	TEST->Initialize();

	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-6);

	TEST->Setb0Q();

	std::cout << TEST->GetIFb0Q() << std::endl;
	TEST->Blowdown5(2);

	std::cout << TEST->GetIFb0Q() << std::endl;


	delete TEST;


}
