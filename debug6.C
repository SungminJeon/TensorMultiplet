#include <iostream>
#include "Tensor.h"



int main() {


	int base;

	Tensor* TEST = new Tensor();

	base = 4;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-3);
	TEST->ATS(-2,-2);
	TEST->AT(-1);
	TEST->AT(-8);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	std::cout << TEST->TimeDirection() << std::endl;
	std::cout << TEST->SpaceDirection() << std::endl;
	std::cout << TEST->NullDirection() << std::endl;
	

	//TEST->ATE(-1,21);
	TEST->Setb0Q();

	std::cout << TEST->GetIFb0Q() << std::endl;

	Tensor B(*TEST);
	//std::cout << B.GetExactDet() << std::endl;
	//std::cout << B.GetEigenvalues() << std::endl;

	int bn = 0;
	bool k;
	
	//TEST->LSTBlowdown(2);


	for (int i = 1; i <= TEST->GetT(); i++)
	{
		if ( TEST->GetIntersectionForm()(i-1,i-1) == -1 )
		{
			k = TEST->Blowdown5(i);
			std::cout << TEST->GetIFb0Q() << std::endl;
			bn++;
			i = 0;

			if ( TEST->GetT() == 1 ) {break;}
		}
	}

	std::cout << TEST->GetIFb0Q() << std::endl;
	std::cout << bn << std::endl;


	B.ForcedBlowdown();
	std::cout << B.GetIntersectionForm() << std::endl;




	delete TEST;


}
