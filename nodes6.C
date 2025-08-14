#include <iostream>
#include <fstream>
#include <vector>
#include "Theory.h"

int main() {


	Theory* TEST = new Theory();



	int base = 1;

	/*
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
//	TEST->AL(1,1); TEST->AT(-4);
//	TEST->AL(1,1); TEST->AT(-4);
	
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
*/


	base = 355;

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
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	TEST->AL(5,5);
	TEST->ATS2(-2,-1,-12);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	





	std::cout << TEST->GetIntersectionForm() << std::endl;



	TEST->ATE(-1,91);
	TEST->Setb0Q();

	Theory B(*TEST);

	bool c = B.IsSUGRA();

	std::cout << "DET : " << B.GetDeterminant() << std::endl;
	std::cout << "Signature : " << B.GetSignature() << std::endl;


	for (int i = 0; i < TEST->GetT(); i++)
	{
		if ( B.GetIntersectionForm()(i,i) == -1 && B.GetIntersectionForm()(i,0) == 0 )
		{
			B.Blowdown5(i+1);

			std::cout << B.GetIFb0Q() << std::endl;
			std::cout << "processing... " << i << std::endl;
			i = -1;

			c = B.IsSUGRA();




			if( c == 0 )
			{

				std::cout << " det : " << B.GetDeterminant() << std::endl;
				std::cout << " signature : " << B.TimeDirection() << std::endl;
				std::cout << B.GetIFb0Q() << std::endl;
			}
		}
	
	}

	if ( c == 1)
	{
	//	std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
	

		std::cout << B.GetIFb0Q() << std::endl;
	}


	TEST->Initialize();


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



//	TEST->ATE(-1,91);
	TEST->Setb0Q();

	Theory C(*TEST);

	c = C.IsSUGRA();

	std::cout << "DET : " << C.GetDeterminant() << std::endl;
	std::cout << "Signature : " << C.GetSignature() << std::endl;

	if ( c == 1)
	{
	//	std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
		C.LSTBlowdown(2);

		std::cout << C.GetIFb0Q() << std::endl;
	}


}







