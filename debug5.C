
#include <iostream>
#include "Theory.h"
#include <vector>


int main() {


        Theory th;
/*	th.AddTensorMultiplet(-8);
	th.AddLink(4,5);
	th.AddTensorMultiplet(-12);
	th.AddLink(5,5); th.AddTensorMultiplet(-12);
	th.AddLink(5,5); th.AddTensorMultiplet(-12);
	th.AddLink(5,5); th.AddTensorMultiplet(-12);
	th.AddLink(5,5); th.AddTensorMultiplet(-12);
	th.AddLink(5,5); th.AddTensorMultiplet(-12);
	th.AddLink(5,5); th.AddTensorMultiplet(-12);
	th.AddLink(4,2);
	th.AddTensorMultiplet(-4);
	th.AddTensorMultiplet(-1);
	th.AddTensorMultiplet(-4);
	// side tensors
	th.AddTensorMultiplet(-1); th.intersect(12,th.GetT());
	th.AddTensorMultiplet(-1); th.intersect(84,th.GetT());


	for(int i=1;i<th.GetT()-2;++i) th.intersect(i,i+1);

	th.AddTensorMultiplet(-1); th.intersect(10,th.GetT());

*/
	//std::cout << th.GetIntersectionForm() <<std::endl;

       	th.AddT(-1);
	th.AddT(-1);
	th.AddT(-1);
	th.AddT(-1);

	for (int i = 2; i < 5; i++)
	{
		th.intersect(1,i);
	}

	std::cout << "evs " << std::endl;
	std::cout << th.GetEigenvalues() << std::endl;
	
	std::cout << " TIME DIR : \n" << th.GetSignature() << std::endl;


	std::cout << " ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// " << std::endl;
	std::cout << " ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// " << std::endl;
	std::cout << " ////////////////////////////////////////////////// T E S T    FOR     B L O W D O W N            ///////////////////////////////////////////////// " << std::endl;
	std::cout << " ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// " << std::endl;
	std::cout << " ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// " << std::endl;

	std::cout << th.GetIntersectionForm() << std::endl;

	std::cout << " after blowdown " << std::endl;
	th.Blowdown2(1);

	std::cout << th.GetIntersectionForm() << std::endl;

	
	std::cout << "////////////////////// SIGNATURE METHOD TEST //////////////////////////// " << std::endl;


	Theory th2;

	th2.AddT(-12);
	th2.AddLink(5,5);
	th2.AddT(-12);
	th2.AddT(-1); th2.intersect(14,1);
	for (int i = 1 ; i < 13 ;i++)
	{
		th2.intersect(i,i+1);
	}


	std::cout << th2.GetIntersectionForm() <<std::endl;

	std::cout << " EIGENVALUES " << std::endl;
	std::cout << th2.GetEigenvalues() << std::endl; 
	std::cout << " Eigenvalues2 " << std::endl;
	std::cout << th2.GetEigenvalues2() << std::endl;
	std::cout << th2.GetSignature() << std::endl;

	for (int j = 0; j < th2.GetT() ; j++)
	{
		if( th2.GetIntersectionForm()(j,j) == -1 )
		{
			th2.Blowdown2(j+1);
			std::cout << th2.GetIntersectionForm() <<std::endl;
			j = -1;
		}
	}


	

	//th.Blowdown(th.GetT());


      //  std::cout << " ForcedBLOWDOWNED : " <<std::endl;
       // std::cout << th.GetIntersectionForm() << std::endl;

       // th.IsHirzebruch();
       //   std::cout << th.GetIntersectionForm() <<std::endl;

  //      th.LSTBlowdown();

    //    std::cout << " LSTBLOWDOWNED : " <<std::endl;
      //  std::cout << th.GetIntersectionForm() << std::endl;
      //
      //
      //



	std::cout << "/////////////////////////////TEST FOR LST 360 BASE ////////////////////////// " << std::endl;



	Theory th3;

	th3.AddT(-8);
	th3.AddLink(4,5);
	th3.AddT(-12);
	th3.AddLink(5,5); th3.AddT(-12);
	th3.AddLink(5,5); th3.AddT(-12);
	th3.AddLink(5,5); th3.AddT(-12);
	th3.AddLink(5,5); th3.AddT(-12);
	th3.AddLink(5,5); th3.AddT(-12);
	th3.AddLink(5,5); 
	th3.AddT(-12);
	th3.AddLink(4,2);
	th3.AddT(-4);
	th3.AddT(-1);
	th3.AddT(-4);

	th3.AddT(-1); th3.intersect(th3.GetT(),12);
	th3.AddT(-1); th3.intersect(th3.GetT(),84);

	for (int k = 1; k < th3.GetT()-2; k++)
	{
		th3.intersect(k,k+1);
	
	}

//	th3.AddT(-1);
//	th3.AddT(-1);
//	th3.intersect(th3.GetT(),th3.GetT()-1);
//	th3.intersect(th3.GetT()-1,2);

	for (int j = 0; j < th3.GetT() ; j++)
	{
		if( th3.GetIntersectionForm()(j,j) == -1 )
		{
			bool b = th3.Blowdown2(j+1);
			std::cout << "Intersection form" <<std::endl;
			std::cout << th3.GetIntersectionForm() <<std::endl;
			std::cout << "DET " << std::endl;

			std::cout << th3.GetDeterminant() <<std::endl;
			std::cout << "time dir " << std::endl;
			std::cout << th3.TimeDirection() << std::endl;
			if ( b == 1)
			{
				j = -1;
			}


			if( th3.GetT() < 4)
			{
				break;
			}
		}
	}



}
