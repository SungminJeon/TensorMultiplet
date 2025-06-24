#include "Theory.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;


int main()
{
	Theory th;
	int Number = 0;
	//int base = 11;
	// for file
	//fs::path out_dir = std::string("./LST_Blowdown_") + std::to_string(base);




	///////////////////////////////////////////////////////////////////////////////////
	// Table for nodes and links 
	// Nodes (curve, gauge algebra)
	// 	 (-12, e_8)
	// 	 (-11, e_8')
	// 	 (-10, e_8'')
	// 	 ( -9, e_8''')
	// 	 ( -8, e_7)
	// 	 ( -7, e_7')
	// 	 ( -6, e_6)
	// 	 ( -5, f_4)
	// 	 ( -4, so_8)
	// 	 ( -3, su_2)	
	//
	// Links (n,m) {tensormultiplets}
	// 	 (1,1) {-1}
	// 	 (2,2) {-1,-3,-1}
	// 	 (3,3) {-1,-2,-3,-2,-1}
	// 	 (3,2) {-1,-2,-3,-1}
	// 	 (4,2) {-1,-2,-2,-3,-1}
	// 	 (3,3) {-1,-3,-1,-5,-1,-3,-1} void
	// 	 (3,4) {-1,-3,-1,-5,-1,-3,-2,-1} 
	// 	 (3,5) {-1,-3,-1,-5,-1,-3,-2,-2,-1}
	// 	 (4,4) {-1,-2,-3,-1,-5,-1,-3,-2,-1}
	// 	 (4,5) {-1,-2,-3,-1,-5,-1,-3,-2,-2,-1}
	// 	 (5,5) {-1,-2,-2,-3,-1,-5,-1,-3,-2,-2,-1}
	//
	//
	////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////
	///
	///
	///
	///
	///           LST PART -> LST # FROM HAMADA YUTA'S TABLE
	///
	///
	///          
	////////////////////////////////////////////////////////////////////////////////////
	/// LST:360 no gauge, add only one tensor multiplet -> -1, -2 curve
	/// ////////////////////////////////////////////////////////////////////////////////           



	th.AddT(-4);
	th.AddT(-1);
	th.AddT(-4);
	th.AddT(-1);
	th.AddT(-4);
	th.AddT(-1);
	th.AddT(-4);
	th.AddT(-1);
	th.AddT(-4);
	th.AddT(-1);

	for ( int i = 1; i < 9 ; i++)
	{
		th.intersect(i,i+1);
	}
	th.intersect(10,3);


	std::cout << th.GetIntersectionForm() << std::endl;

	
		
	
	Theory test = th;				


	for( int l= 0; l < test.GetT(); l++)
	{

		//std::cout << l << std::endl;
		if ( test.GetIntersectionForm()(l,l) == -1 )
		{

			bool b = test.Blowdown2(l+1);
			bool c = test.IsSUGRA();
		//	std::cout << l << std::endl;
			if (b == 1 && c ==1 )
			{
				std::cout << test.GetIntersectionForm() << std::endl;
				l = -1;
			}
			else if ( c == 0)
			{
				std::cout << "NOT SUGRA " << std::endl;
				break;
			}

		}
		
	}

	std::cout << "after full blowdown " << std::endl;
	std::cout << test.GetIntersectionForm() <<std::endl;




//	bool b = test.IsHirzebruch();
	//test.CompleteBlowdown();
	//bool b  = test.IsSUGRA();

/*	if ( b == 1)
	{



	std::cout << "Intersection form:\n" << test.GetIntersectionForm() << "\n\n";
	std::cout << b <<"  Determinant : " << th.GetDeterminant() << " after blowdown    :" << test.GetDeterminant() << "\n";
		<< "\nSignature:\n";
		for (double v : th.GetSignature()) std::cout << v << '\n';
		Number++;
		std::cout <<"\n Number : " << Number << "\n" <<std::endl;
		
	} */

//	th.CompleteBlowdown();
//	std::cout << "Intersection form:\n" << th.GetIntersectionForm() << "\n\n";
	
			

			

}
