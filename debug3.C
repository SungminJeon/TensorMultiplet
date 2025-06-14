#include <iostream>
#include "Theory.h"
#include <vector>



int main() {


	Theory th;
	
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

	th.AddT(-1); th.intersect(th.GetT(),33);

	std::cout << th.GetIntersectionForm() <<std::endl;

	th.LSTBlowdown();

	std::cout << " LSTBLOWDOWNED : " <<std::endl;
	std::cout << th.GetIntersectionForm() << std::endl;

	th.IsHirzebruch();

	





//	std::cout << test.GetIntersectionForm() << std::endl;
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


	*/

}

