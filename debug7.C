#include <iostream>
#include "Theory.h"


int main () {


	int bn = 0;
	Theory* TEST = new Theory();

	int base = 175;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS3(-2,-2,-1,-12);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	
		




	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	TEST->ATE(-1,81);


	TEST->Setb0Q();

	for (int i = 0; i < TEST->GetT(); i++)
	{

		if (TEST->GetIntersectionForm()(i,TEST->GetT()-1) == 0 && TEST->GetIntersectionForm()(i,i) == -1 && TEST->IsSUGRA() == 1 )
		{
			TEST->Blowdown5(i+1);
			i = -1;

			bn++;
			std::cout << " Blowdowned : "<< bn << "      det : " << TEST->GetExactDet() << " timedir : " << TEST->TimeDirection() << std::endl;	
			std::cout << TEST->GetIntersectionForm() << std::endl;
			std::cout << "                             " << std::endl;
			std::cout << "  " << std::endl;

		}
	}

	std::cout << "FINAL RESULT " << std::endl;
	std::cout << TEST->GetIFb0Q() << std::endl;


	std::cout << "  " << std::endl;

	std::cout << "FORCED BLOWDOWN" << std::endl;


	for (int i = 0; i < TEST->GetT(); i++)
	{

		if ( TEST->GetIntersectionForm()(i,TEST->GetT()-1) == 0 && TEST->GetIntersectionForm()(i,i) == -1 )
		{
			TEST->Blowdown5(i+1);
			i = -1;

			bn++;
			std::cout << " Blowdowned : "<< bn << "      det : " << TEST->GetExactDet() << " timedir : " << TEST->TimeDirection() << std::endl;	
			std::cout << TEST->GetIntersectionForm() << std::endl;
			std::cout << "                             " << std::endl;
			std::cout << "  " << std::endl;

		}
	}






}
