#include "Theory.h"
#include <iostream>

int main()
{
	Theory th;
	static const std::array<int,10> squares =
	{1,4,9,16,25,36,49,64,81,100};
	int Number = 0;

	for(int i : {-4,-1,-4,-1,-4,-1,-4,-1,-4,-1})
		th.AddTensorMultiplet(i);


	for(int i=1;i<10;++i) th.intersect(i,i+1);

	th.intersect(3,10);

	Theory test = th;

	int detInt = static_cast<int>(std::round( std::abs( test.CheckUnimodularity() ) ));

	/* ---------- ② 정수 det 가 완전제곱인지 검사 ---------- */
	bool isSquare = std::find(squares.begin(), squares.end(), detInt)
		!= squares.end();


	//Blowdown and check unimodularity
	for(int i = 0; i < 10; i++ )
	{
		if( (test.GetIntersectionForm())(i,i) == -1 )
		{	
			test.Blowdown(i+1);

				if (isSquare)
				{
					std::cout << "Intersection form:\n" << test << "\n\n";
					std::cout << "Determinant : " << test.GetDeterminant()
						<< "\nSignature:\n";
					for (double v : test.GetSignature()) std::cout << v << '\n';
					Number++;
					
				}
				else if (detInt > 100)
				{
					std::cout << "Too big one\n";
				}
				else
				{
					std::cout << "IT'S NOT UNIMODULAR" << std::endl;
				}
		}

		test = th;


	}
	
	Theory th2;
	for (int i:{ -1,-2,-3,-2,-1,-8,-1,-2,-2,-2,-3,
	
}
