#include "Theory.h"
#include <iostream>

int main()
{
	Theory th;
	int Number = 0;
	



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

	th.AddTensorMultiplet(-8);
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


	Theory test2;

	//NOW SEARCHING FOR AT LEAST CONSISTENT STRUCTURE FOR SUGRA
	for(int i : {-1} )
	{
		th.AddTensorMultiplet(i);
		th.AddT(-1);
		
		int T = th.GetT();
		th.intersect(T,T-1);
		
		for (int j = 1; j < T-1; j++)
		{
			th.intersect(j,T-1);

			test2 = th;
			
			bool b = test2.IsHirzebruch();
			std::cout << test2.GetIntersectionForm() << std::endl;
			//std::cout << th.IsSUGRA() << " \n";
			if (b == 1)
			{
				Number++;
				//std::cout << "Intersection form:\n" << th << "\n\n";
				std::cout << Number <<"  Determinant : " << test2.GetDeterminant() << " " << "( " << i << ',' << j << ")\n";
				/*	<< "\nSignature:\n";
					for (double v : th.GetSignature()) std::cout << v << '\n';
					Number++;
					std::cout <<"\n Number : " << Number << "\n" <<std::endl;
					*/
			}
			else if (b == 0)
			{	
				std::cout << "Not SUGRA : (" << i << ',' << j << ")";
				std::cout << "  Determinant : " << test2.GetDeterminant() << "\n\n";
			       	//std::cout << test2.GetIntersectionForm() << std::endl;
				std::cout << "# OF TIME DIRECTION : " << test2.TimeDirection() << std::endl; 	

			}
			th.not_intersect(j,T-1);


		}
		th.DeleteTensorMultiplet();
	}


///////////////////////////////////////////////////////////////////////////////////////////

	std::cout << "//////////////////////////////////////////////////////" << std::endl;
	std::cout << "//                     BASE 403                     //" << std::endl;
	std::cout << "//////////////////////////////////////////////////////" << std::endl;



	Theory th2;
	Number = 0;

	th2.AddTensorMultiplet(-6);
	th2.AddLink(2,2);
	th2.AddTensorMultiplet(-4);
	th2.AddTensorMultiplet(-1); th2.AddTensorMultiplet(-4);
	th2.AddTensorMultiplet(-1); th2.AddTensorMultiplet(-4);
	th2.AddTensorMultiplet(-1); th2.AddTensorMultiplet(-4);
	th2.AddTensorMultiplet(-1); th2.AddTensorMultiplet(-4);
	th2.AddTensorMultiplet(-1); th2.AddTensorMultiplet(-4);
	th2.AddTensorMultiplet(-1); th2.AddTensorMultiplet(-4);
	th2.AddTensorMultiplet(-1); th2.AddTensorMultiplet(-4);
	th2.AddTensorMultiplet(-1);
	th2.AddTensorMultiplet(-4);
	th2.AddTensorMultiplet(-1);
	th2.AddTensorMultiplet(-4);
	//side tensors
	th2.AddTensorMultiplet(-1); th2.intersect(21,th2.GetT());
	th2.AddTensorMultiplet(-4); th2.intersect(th2.GetT(),th2.GetT()-1);


	for (int i = 1; i < th2.GetT()-2; i++)
	{
		th2.intersect(i,i+1);
	}




	//NOW SEARCHING FOR AT LEAST CONSISTENT STRUCTURE FOR SUGRA
	for(int i : { -1} )
	{
		th2.AddTensorMultiplet(i);
		int T = th2.GetT();
		for (int j = 1; j < T; j++)
		{
			th2.intersect(j,T,2);

			test2 = th2;

			bool b = test2.IsHirzebruch();

		if (b == 1)
			{
				Number++;
				//std::cout << "Intersection form:\n" << th << "\n\n";
				std::cout << Number <<"  Determinant : " << test2.GetDeterminant() << " " << "( " << i << ',' << j << ")\n";
				/*	<< "\nSignature:\n";
					for (double v : th.GetSignature()) std::cout << v << '\n';
					Number++;
					std::cout <<"\n Number : " << Number << "\n" <<std::endl;
					*/
			}
			else if (b == 0)
			{
				std::cout << "Not SUGRA : (" << i << ',' << j << ")";
				std::cout << "  Determinant : " << test2.GetDeterminant() << "\n\n";
				std::cout << "# OF TIME DIRECTION : " << test2.TimeDirection() << std::endl;

			}
			th2.not_intersect(j,T);


		}
		th2.DeleteTensorMultiplet();
	}


/////////////////////////////////////////////////////////////////////////////////
	std::cout << "//////////////////////////////////////////////////////" << std::endl;
	std::cout << "//                     BASE 447                     //" << std::endl;
	std::cout << "//////////////////////////////////////////////////////" << std::endl;


	Theory th3;
	Number = 0;

	th3.AddTensorMultiplet(-12);
	th3.AddLink(5,4);
	th3.AddTensorMultiplet(-8);
	th3.AddLink(3,3); th3.AddTensorMultiplet(-8);
	th3.AddLink(3,3); th3.AddTensorMultiplet(-8);
	th3.AddLink(3,3); th3.AddTensorMultiplet(-8);
	th3.AddLink(3,3); th3.AddTensorMultiplet(-8);
	th3.AddLink(3,3); th3.AddTensorMultiplet(-8);
	th3.AddLink(3,3); th3.AddTensorMultiplet(-8);
	th3.AddLink(3,3); th3.AddTensorMultiplet(-8);
	th3.AddLink(3,3);
	th3.AddT(-8);
	th3.AddLink(3,2);
	th3.AddT(-5);
	// side tensor
	th3.AddT(-1); th3.intersect(th3.GetT(),60);





	for (int i = 1; i < th3.GetT()-1; i++)
	{
		th3.intersect(i,i+1);
	}




	//NOW SEARCHING FOR AT LEAST CONSISTENT STRUCTURE FOR SUGRA
	for(int i : { -1} )
	{
		th3.AddTensorMultiplet(i);
		int T = th3.GetT();
		for (int j = 1; j < T; j++)
		{
			th3.intersect(j,T,2);

			test2 = th3;

			bool b = test2.IsHirzebruch();

			if (b == 1)
			{
				Number++;
				//std::cout << "Intersection form:\n" << th << "\n\n";
				std::cout << Number <<"  Determinant : " << test2.GetDeterminant() << " " << "( " << i << ',' << j << ")\n";
				/*	<< "\nSignature:\n";
					for (double v : th.GetSignature()) std::cout << v << '\n';
					Number++;
					std::cout <<"\n Number : " << Number << "\n" <<std::endl;
					*/
			}
			else if (b == 0)
			{
				std::cout << "Not SUGRA : (" << i << ',' << j << ")";
				std::cout << "  Determinant : " << test2.GetDeterminant() << "\n\n";
				std::cout << "# OF TIME DIRECTION" << test2.TimeDirection() << std::endl;

			}
			th3.not_intersect(j,T);


		}
		th3.DeleteTensorMultiplet();
	}

/////////////////////////////////////////////////////////////////////////////////
	std::cout << "//////////////////////////////////////////////////////" << std::endl;
	std::cout << "//                     BASE 527                     //" << std::endl;
	std::cout << "//////////////////////////////////////////////////////" << std::endl;


	Theory th4;
	Number = 0;

	th4.AddTensorMultiplet(-12);
	th4.AddLink(5,5);
	th4.AddT(-12);
	th4.AddLink(5,5); th4.AddT(-12);
	th4.AddLink(5,5); th4.AddT(-12);
	th4.AddLink(5,5); th4.AddT(-12);
	th4.AddLink(5,5); th4.AddT(-12);
	th4.AddLink(5,5); th4.AddT(-12);
	th4.AddLink(5,5); th4.AddT(-12);
	th4.AddLink(5,5); th4.AddT(-12);
	th4.AddLink(5,5); th4.AddT(-12);
	th4.AddLink(5,3);
	th4.AddT(-4);

	// side tensor
	th4.AddT(-1); th4.intersect(th4.GetT(),13);





	for (int i = 1; i < th4.GetT()-1; i++)
	{
		th4.intersect(i,i+1);
	}




	//NOW SEARCHING FOR AT LEAST CONSISTENT STRUCTURE FOR SUGRA
	for(int i : { -1, -2} )
	{
		th4.AddTensorMultiplet(i);
		int T = th4.GetT();
		for (int j = 1; j < T; j++)
		{
			th4.intersect(j,T);

			test2 = th4;

			bool b = test2.IsHirzebruch();

			if (b == 1)
			{
				Number++;
				//std::cout << "Intersection form:\n" << th << "\n\n";
				std::cout << Number <<"  Determinant : " << test2.GetDeterminant() << " " << "( " << i << ',' << j << ")\n";
				/*	<< "\nSignature:\n";
					for (double v : th.GetSignature()) std::cout << v << '\n';
					Number++;
					std::cout <<"\n Number : " << Number << "\n" <<std::endl;
					*/
			}
			else if (b == 0)
			{
				std::cout << "Not SUGRA : (" << i << ',' << j << ")";
				std::cout << "  Determinant : " << test2.GetDeterminant() << "\n\n";
				std::cout << "# OF TIME DIRECTION : " << test2.TimeDirection() << std::endl;

			}
			th4.not_intersect(j,T);


		}
		th4.DeleteTensorMultiplet();
	}



}





		
