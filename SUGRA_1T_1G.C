#include "Theory.h"
#include <iostream>

int main()
{
	Theory th;
	static const std::array<int,45> squares =
	{1,4,9,16,25,36,49,64,81,100,121,144,169,196,225,256,289,324,361,400,441,484,529,576,625,676,729,784,841,900,961,1024,1089,1156,1225,1296,1369,1444,1521,1600,1681,1764,1849,1936,2025};
	int Number = 0;
//	int Number2 = 0;
//	int Number3 = 0;

	for(int i : {-1,-2,-3,-2,-1,-8,-1,-2,-3,-1,-5,-1,-3,-2,-2,-1,-12,-1,-2,-2,-3,-1,-5,-1,-3,-2,-2,-1,-12,-1,-2,-2,-3,-1,-5,-1,-3,-2,-2,-1,-12,-1,-2,-2,-3,-1,-5,-1,-3,-2,-2,-1,-12,-1,-2,-2,-3,-1,-5,-1,-3,-2,-2,-1,-12,-1,-2,-2,-3,-1,-5,-1,-2,-1,-8,-1,-2,-3,-2,-1})
		th.AddTensorMultiplet(i);


	for(int i=1;i<th.GetT();++i) th.intersect(i,i+1);

	//th.intersect(2,16);
	//th.intersect(16,2);

	//NOW SEARCHING FOR AT LEAST CONSISTENT STRUCTURE FOR SUGRA
	for(int i : { -1, -2, -3} )
	{
		th.AddTensorMultiplet(i);
		for (int j = 1; j < th.GetT(); j++)
		{
			th.intersect(j,th.GetT());
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
			else if (detInt > 2025)
			{
				std::cout << "Too big one : (" << i << ',' << j << ")\n";
			}
			th.not_intersect(j,th.GetT());


		}
		th.DeleteTensorMultiplet();
	}
}

		
