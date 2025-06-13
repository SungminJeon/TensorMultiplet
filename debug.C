#include "Theory.h"
#include <iostream>
#include <vector>


int main () {

	Theory th;

	// Make test base //
	
	th.AddT(-8);
	th.AddLink(4,5); 
	th.AddT(-12);
	th.AddLink(5,5); th.AddT(-12);
	th.AddLink(5,5); th.AddT(-12);
	th.AddLink(5,5); th.AddT(-12);
	th.AddLink(5,5); th.AddT(-12);
	th.AddLink(5,5); th.AddT(-12);
	th.AddLink(5,5); 
	th.AddT(-12);
	th.AddLink(4,2);
	th.AddT(-4);
	th.AddT(-1);
	th.AddT(-4);

	// side tensors
	th.AddT(-1); th.intersect(th.GetT(),12);
	th.AddT(-1); th.intersect(th.GetT(),84);

	for (int i = 1; i < th.GetT()-2; i++) {th.intersect(i,i+1);}
	th.AddT(-1);
	th.intersect(th.GetT(),12);

	std::cout << th.GetExactDet() << std::endl;
	bool b = th.IsHirzebruch();

	if (b == 1)
	{
		std::cout << th.GetIntersectionForm() << std::endl;
		std::cout << th.GetDeterminant() << std::endl;
	}
	else 
	{
		std::cout << "NOT SUGRA" << std::endl;
		std::cout << th.GetIntersectionForm() << std::endl;
		std::cout << th.GetDeterminant() << std::endl;
	}

/*
	for (int j = 0; j < th.GetT(); j++)
	{

		if ((th.GetIntersectionForm())(j,j) == -1)
		{
			th.Blowdown(j+1);
			std::cout << "intersection form :\n" << th.GetIntersectionForm() <<std::endl;
			j = -1;
		}
	}*/
}



