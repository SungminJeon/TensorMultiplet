#include "Theory.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;



int main() {


	int base = 447;
	// for file
	fs::path out_dir = std::string("./LST_") + std::to_string(base);
	int Number = 0;

	Theory th;
	//Theory th2;
	//Theory th3;

	//////////////// Base //////////////////
	// LST BASE 447
	
	std::cout << "/////////////////////////////////////////////////////////" <<std::endl;
	std::cout << "//                     LST" << 447 << "     	                   //" << std::endl;
	std::cout << "/////////////////////////////////////////////////////////" << std::endl;

	th.AddTensorMultiplet(-12);
	th.AddLink(5,4);
	th.AddTensorMultiplet(-8);
	th.AddLink(3,3); th.AddTensorMultiplet(-8);
	th.AddLink(3,3); th.AddTensorMultiplet(-8);
	th.AddLink(3,3); th.AddTensorMultiplet(-8);
	th.AddLink(3,3); th.AddTensorMultiplet(-8);
	th.AddLink(3,3); th.AddTensorMultiplet(-8);
	th.AddLink(3,3); th.AddTensorMultiplet(-8);
	th.AddLink(3,3); th.AddTensorMultiplet(-8);
	th.AddLink(3,3);
	th.AddT(-8);
	th.AddLink(3,2);
	th.AddT(-5);
	// side tensor
	th.AddT(-1); th.intersect(th.GetT(),60);





	for (int i = 1; i < th.GetT()-1; i++)
	{
		th.intersect(i,i+1);
	}
		
	
	
	//NOW SEARCHING FOR AT LEAST CONSISTENT STRUCTURE FOR SUGRA
	for(int i : { -1, -2} )
	{
		th.AddTensorMultiplet(i);
		int T = th.GetT();

		for (int j = 1; j < T; j++)
		{
			th.intersect(j,T);
			bool b = th.IsSUGRA();
			//std::cout << th.IsSUGRA() << " \n";
			if (b == 1)
			{
				Number++;
				//std::cout << "Intersection form:\n" << th << "\n\n";
				std::cout << Number <<"  Determinant : " << th.GetDeterminant() << " " << "( " << i << ',' << j << ")\n";
				/*	<< "\nSignature:\n";
					for (double v : th.GetSignature()) std::cout << v << '\n';
					Number++;
					std::cout <<"\n Number : " << Number << "\n" <<std::endl;
					*/
			}
			else if (b == 0)
			{	
				std::cout << "Not SUGRA : (" << i << ',' << j << ")";
				std::cout << "  Determinant : " << th.GetDeterminant() << "\n";
			       	//std::cout << " Intersection form : " << th.GetIntersectionForm() << std::endl;	

			}

			// file open
			//
			std::ostringstream oss;
			oss << "LST_" << base << "_(" << i << "," << j << ").txt";
			fs::path filepath = out_dir / oss.str();
			std::ofstream out(filepath);
			if(!out) { std::cerr << "Fail to open a file\n";
				return 1;
			}

			out << th.GetIntersectionForm() << '\n';
			out.close();
			//std::cout << "intersection_form saved\n";

			
			th.not_intersect(j,T);


		}
		th.DeleteTensorMultiplet();
	}

	std::cout << "total number of SUGRA : " << Number << std::endl;

}
