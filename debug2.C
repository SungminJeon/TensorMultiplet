#include <iostream>
#include "Theory.h"
#include <vector>



int main() {


	Theory th;

	for(int i : {-4,-1,-4,-1,-4,-1,-4,-1,-4,-1})
		th.AddTensorMultiplet(i);


	for(int i=1;i<10;++i) th.intersect(i,i+1);

	th.intersect(3,10);

	Theory test = th;
	bool b = test.IsHirzebruch();
	std::cout << test.GetIntersectionForm() << std::endl;
	//test.Blowdown(6);
	//std::cout << test.GetIntersectionForm() << std::endl;
	
	
/*	for ( int i = 0 ; i < test.GetT(); i++)
	{
		std::cout << i << std::endl;
		if ( test.GetIntersectionForm()(i,i) == -1 )
		{
			test.Blowdown(i+1);
			bool b  = test.IsSUGRA();
			if ( b == 1)
			{
				i = -1;
			}
			else if ( b == 0)
			{
				std::cout << " NOT SUGRA " << std::endl;
				std::cout << " Determinant : " << test.GetDeterminant() << std::endl;
			}
		}
	}*/
/*
	bool b = test.IsHirzebruch();

	if ( b==1 )
	{
		std::cout << "SUGRA" << std::endl;
		std::cout << "Intersection form : \n" << test.GetIntersectionForm() << std::endl;

	}
	else
	{
		std::cout << "NOT SUGRA" << std::endl;
	}
*/

	std::cout << test.GetIntersectionForm() <<std::endl;
}


