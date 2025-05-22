#include "Theory.h"
#include <iostream>

int main()
{
	Theory th;
	static const std::array<int,25> squares =
	{1,4,9,16,25,36,49,64,81,100,121,144,169,196,225,256,289,324,361,400,441,484,529,576,625};
	int Number = 0;
	int Number2 = 0;
	int Number3 = 0;

	for(int i : {-2,-1,-4,-1,-4,-1,-4,-1,-4,-1,-4,-1,-4,-1,-4,-1,-2})
		th.AddTensorMultiplet(i);


	for(int i=1;i<17;++i) th.intersect(i,i+1);

	//th.intersect(2,16);
	//th.intersect(16,2);

	//NOW SEARCHING FOR AT LEAST CONSISTENT STRUCTURE FOR SUGRA
	for(int i : { -1, -2, -3,-4,-6,-7,-8,-9,-10,-11,-12} )
	{
		th.AddTensorMultiplet(i);
		for (int j = 1; j < 18; j++)
		{
			th.intersect(j,18);
			int detInt = static_cast<int>(std::round( std::abs( th.CheckUnimodularity() ) ));

			/* ---------- ② 정수 det 가 완전제곱인지 검사 ---------- */
			bool isSquare = std::find(squares.begin(), squares.end(), detInt)
				!= squares.end();

			if (isSquare)
			{
				std::cout << "Intersection form:\n" << th << "\n\n";
				std::cout << "Determinant : " << th.GetDeterminant()
					<< "\nSignature:\n";
				for (double v : th.GetSignature()) std::cout << v << '\n';
				Number++;
				std::cout <<"\n Number : " << Number << "\n" <<std::endl;
			}
			else if (detInt > 625)
			{
				std::cout << "Too big one : (" << i << ',' << j << ")\n";
			}
			th.not_intersect(j,18);

			
		}
		th.DeleteTensorMultiplet();
	}

	std::cout << "//////////////////////////////////////////////////////\n" << std::endl;
	std::cout << "//////                 Theory 2               ////////\n" << std::endl;
	std::cout << "//////////////////////////////////////////////////////\n" << std::endl;
	std::cout << "//////////////////////////////////////////////////////\n" << std::endl;




	Theory th2;

	for(int i : {-1,-12,-1,-2,-2,-3,-1,-4,-1,-4,-1,-4,-1,-4,-1,-4,-1,-4,-1,-3})
		th2.AddTensorMultiplet(i);


	for(int i=1;i<th2.GetT();++i) th2.intersect(i,i+1);

	//th.intersect(2,16);
	//th.intersect(16,2);

	//NOW SEARCHING FOR AT LEAST CONSISTENT STRUCTURE FOR SUGRA
	for(int i : { -1, -2, -3,-4,-6,-7,-8,-9,-10,-11,-12} )
	{
		th2.AddTensorMultiplet(i);
		for (int j = 1; j < 20; j++)
		{
			th2.intersect(j,21);
			int detInt = static_cast<int>(std::round( std::abs( th2.CheckUnimodularity() ) ));

			/* ---------- ② 정수 det 가 완전제곱인지 검사 ---------- */
			bool isSquare = std::find(squares.begin(), squares.end(), detInt)
				!= squares.end();

			if (isSquare)
			{
				std::cout << "Intersection form:\n" << th2 << "\n\n";
				std::cout << "Determinant : " << th2.GetDeterminant()
					<< "\nSignature:\n";
				for (double v : th2.GetSignature()) std::cout << v << '\n';
				Number2++;
				std::cout <<"\n Number : " << Number2 << "\n" <<std::endl;
			}
			else if (detInt > 625)
			{
				std::cout << "Too big one : (" << i << ',' << j << ")\n";
			}
			th2.not_intersect(j,21);


		}
		th2.DeleteTensorMultiplet();
	}

}



