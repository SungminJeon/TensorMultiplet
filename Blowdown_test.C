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
	int base = 527;
	// for file
	fs::path out_dir = std::string("./LST_Blowdown_") + std::to_string(base);




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


	th.AddT(-12);
	th.AddLink(5,5);
	th.AddT(-12);
	th.AddLink(5,5); th.AddT(-12);
	th.AddLink(5,5); th.AddT(-12);
	th.AddLink(5,5); th.AddT(-12);
	th.AddLink(5,5); th.AddT(-12);
	th.AddLink(5,5); th.AddT(-12);
	th.AddLink(5,5); th.AddT(-12);
	th.AddLink(5,5); th.AddT(-12);
	th.AddLink(5,5); th.AddT(-12);
	th.AddLink(5,3);
	th.AddT(-4);

	//side tensor
	th.AddT(-1); th.intersect(th.GetT(),13);
	
	for (int i=1; i<th.GetT()-1; i++)
	{
		th.intersect(i,i+1);
	}


	//NOW SEARCHING FOR AT LEAST CONSISTENT STRUCTURE FOR SUGRA
	for(int i : {-1} )
	{
		th.AddTensorMultiplet(i);
		int T = th.GetT();
		
		for (int j = 1; j < T; j++)
		{
			th.intersect(j,T);
			Theory test = th;
			bool b = test.IsHirzebruch();
			//int T = test.GetT();
			//std::cout << th.IsSUGRA() << " \n";
			if (b == 1)
			{
				


				
				//test.CompleteBlowdown();
				
				std::cout << "Intersection form after full blowdown  :\n" << test.GetIntersectionForm() << "\n\n";



				Number++;
				//std::cout << "Intersection form:\n" << test.GetIntersectionForm() << "\n\n";
				std::cout << Number <<"  Determinant : " << th.GetDeterminant() << " " << "( " << i << ',' << j << ")     :" << test.GetDeterminant() << "\n";
				/*	<< "\nSignature:\n";
					for (double v : th.GetSignature()) std::cout << v << '\n';
					Number++;
					std::cout <<"\n Number : " << Number << "\n" <<std::endl;
					*/
			}
			else if (b == 0)
			{	
				std::cout << "Not SUGRA : (" << i << ',' << j << ")";
				std::cout << "  Determinant : " << test.GetDeterminant() << "\n\n";
				std::cout << " # OF TIME DIRECTION : " << test.TimeDirection() << std::endl;	
				//std::cout << "  Signature : " << test.GetSignature() << "\n\n"; 
			}

			// file open
			//
			std::ostringstream oss;
			oss << "LST_Blowdown_" << base << "_(" << i << "," << j << ").txt";
			fs::path filepath = out_dir / oss.str();
			std::ofstream out(filepath);
			if(!out) { std::cerr << "Fail to open a file\n";
				return 1;
			}

			out << test.GetIntersectionForm() << '\n';
			out.close();
			//std::cout << "intersection_form saved\n";




			th.not_intersect(j,T);


		}
		th.DeleteTensorMultiplet();
	}

}
