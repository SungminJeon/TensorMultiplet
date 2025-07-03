
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

/*	th3.AddT(-8);
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
*/


/*	th3.AddT(-6);
	th3.AddLink(3,3); 
	th3.AddT(-6);
	th3.AddLink(2,2); th3.AddT(-6);
	th3.AddLink(2,2); th3.AddT(-6);
	th3.AddLink(2,2); th3.AddT(-6);
	th3.AddLink(2,2); th3.AddT(-6);
	th3.AddLink(2,2); th3.AddT(-6);
	th3.AddLink(2,2); th3.AddT(-6);
	th3.AddLink(3,3,1); 
	th3.AddT(-6);

	for (int k = 1; k < th3.GetT(); k++)
	{
		th3.intersect(k,k+1);
	}

*/

	th3.AddT(-12);
	th3.AddLink(5,5);
	th3.AddT(-12);
	th3.AddLink(5,5); th3.AddT(-12);
	th3.AddLink(5,5); th3.AddT(-12);
	th3.AddLink(5,5); th3.AddT(-12);
	th3.AddLink(5,5); th3.AddT(-12);
	th3.AddLink(5,5); th3.AddT(-12);
	th3.AddLink(5,5); th3.AddT(-12);
	th3.AddLink(5,5); th3.AddT(-12);
	th3.AddLink(5,5); th3.AddT(-12);
	th3.AddLink(5,3);
	th3.AddT(-4);

	th3.AddT(-1); th3.intersect(th3.GetT(),13);

	for(int k = 1; k < th3.GetT()-1;k++)
	{
		th3.intersect(k,k+1);
	}







	std::cout << "Intersection form............ " << std::endl;
	std::cout << th3.GetIntersectionForm() <<std::endl;
//	th3.AddT(-1);
//	th3.AddT(-1);
//	th3.intersect(th3.GetT(),th3.GetT()-1);
//	th3.intersect(th3.GetT(),60);

	std::cout << " the number of time direction " << th3.TimeDirection() << std::endl;
	std::cout << " Signatures : " << std::endl;
	std::cout << "DET without 0 evs : " << th3.IsUnimodular() <<  std::endl;		
	std::cout << "DET with 0 evs    : " << th3.GetExactDet() << std::endl;
	std::cout << "time dir : " << th3.TimeDirection() << std::endl;
	std::cout << "null dir : " << th3.NullDirection() <<std::endl;
	std::cout << "space dir : " << th3.SpaceDirection() <<std::endl;




//	std::cout << th3.GetEigenvalues() <<std::endl;

	for (int j = 0; j < th3.GetT() ; j++)
	{
		if( th3.GetIntersectionForm()(j,j) == -1 )
		{
			bool b = th3.Blowdown2(j+1);
		//	std::cout << "Intersection form" <<std::endl;
		//	std::cout << th3.GetIntersectionForm() <<std::endl;
			std::cout << "DET without 0 evs : " << th3.IsUnimodular() <<  std::endl;
			std::cout << "DET with 0 evs    : " << th3.GetExactDet() << std::endl;

			//std::cout << th3.GetDeterminant() <<std::endl;
			std::cout << "time dir : " << th3.TimeDirection() << std::endl;
			std::cout << "null dir : " << th3.NullDirection() <<std::endl;
			std::cout << "space dir : " << th3.SpaceDirection() <<std::endl;

		/*	for ( int k =0; k <th3.GetT() ; k++)
			{
				if ( th3.GetIntersectionForm()(k,k) == 0 )
				{
					std::cout << " non-negative cureve occurs " << std::endl;
					std::cout << th3.GetIntersectionForm() << std::endl;
				}
			}*/


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

	th3.GetIntersectionForm()(0,0) = 12;
	std::cout << th3.GetIntersectionForm() <<std::endl;


/*
	std::cout << " Test for the signature method " << std::endl;
	Theory th4;


	th4.AddT(-4);
	th4.AddT(-1);
	th4.AddT(-4);
	th4.AddLink(1,1); th4.AddT(-4);
	th4.AddLink(1,1); th4.AddT(-4);
	th4.AddLink(1,1); th4.AddT(-4);
	th4.AddLink(1,1); th4.AddT(-4);
	th4.AddLink(1,1); th4.AddT(-4);
	th4.AddLink(1,1); th4.AddT(-4);
	th4.AddT(-1);
	th4.AddT(-2);
	for (int i = 1; i < th4.GetT() ;i++)
	{
		th4.intersect(i,i+1);
	}
	th4.AddT(-1); th4.intersect(th4.GetT(),2);
	th4.AddT(-4); th4.intersect(th4.GetT(),16);
	th4.AddT(-4); th4.intersect(th4.GetT(),th4.GetT()-2);


	std::cout << th4.GetIntersectionForm() <<std::endl;


	std::cout << "evs 1 " <<std::endl;
	std::cout << th4.GetEigenvalues() << std::endl;
	std::cout << "evs 2 " << std::endl;
	std::cout << th4.GetEigenvalues2() << std::endl;



*/
	std::cout << "......................................................................." << std::endl;
	std::cout << "......................................................................." << std::endl;
	std::cout << "......................................................................." << std::endl;
	std::cout << ".............               TEST FOR B0Q          ....................." << std::endl;
	std::cout << "......................................................................." << std::endl;
	std::cout << "......................................................................." << std::endl;
	std::cout << "......................................................................." << std::endl;



	Theory th5;
	
	th5.AddT(-12);
	th5.AddLink(5,5);
	th5.AddT(-12);
	for(int i =1; i < th5.GetT(); i++)
	{
		th5.intersect(i,i+1);
	}

	th5.Setb0Q();

	std::cout << " Intersection Form " << std::endl;
	std::cout << th5.GetIntersectionForm() << std::endl;
	std::cout << " b0Q's " << std::endl;
//	std::cout << th5.Getb0Q() << std::endl;

	std::cout << " intersection matrix with b0Q " << std::endl;
	std::cout << th5.GetIFb0Q() << std::endl;





	std::cout << "......................................................................." << std::endl;
	std::cout << "......................................................................." << std::endl;
	std::cout << "......................................................................." << std::endl;
	std::cout << ".............         TEST FOR BLOWDOWN4          ....................." << std::endl;
	std::cout << "......................................................................." << std::endl;
	std::cout << "......................................................................." << std::endl;
	std::cout << "......................................................................." << std::endl;



//	th5.Initialize();

	Theory th6;	
	th6.AddT(-12);
	th6.AddT(-12);
	th6.AddT(-1);
	th6.AddT(-12);
	
	th6.intersect(1,3,2);
	th6.intersect(2,3,3);
	

	std::cout << " for debug " << std::endl;

	th6.Blowdown4(3);
	th6.Setb0Q();
	std::cout << " for debug " << std::endl;


	std::cout << " Intersection Form " << std::endl;
	std::cout << th6.GetIntersectionForm() << std::endl;
	std::cout << " b0Q's " << std::endl;
//	std::cout << th5.Getb0Q() << std::endl;

	std::cout << " intersection matrix with b0Q " << std::endl;
	std::cout << th6.GetIFb0Q() << std::endl;


}
