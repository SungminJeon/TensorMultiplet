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
	for (int i:{ -1,-12,-1,-2,-2,-3,-1,-4,-1,-4,-1,-4,-1,-4,-1,-4,-1,-4,-1,-3})
	{
		th2.AddTensorMultiplet(i);
	}
	for (int i =1; i < th2.GetT(); i++)
	{
		th2.intersect(i,i+1);
	}
	
	
	 

	test = th2;

	if (isSquare)
	{
		std::cout << "The theory is SUGRA" << test.CheckUnimodularity() << "\n" << std::endl;
	}
	//Blowdown and check unimodularity
	for(int i = 0; i < th2.GetT(); i++ )
	{
		if( (test.GetIntersectionForm())(i,i) == -1 )
		{	
			test.Blowdown(i+1);

			if (isSquare)
			{
				std::cout << "Intersection form:\n" << test << "\n\n";
				std::cout << "Determinant : " << test.CheckUnimodularity()
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

		test = th2;


	}


	Theory th3;
	for (int i:{ -2,-3,-1,-4,-1,-4,-1,-4,-1,-4,-1,-4,-1,-4,-1,-3,-2,-2,-1,-12})
	{
		th3.AddTensorMultiplet(i);
	}
	for (int i =1; i < th3.GetT(); i++)
	{
		th3.intersect(i,i+1);
	}




	test = th3;
	std::cout << "det of the theory 3: " << test.CheckUnimodularity() << "\n" << std::endl;
	std::cout << "intersection form of the theory : " << test.GetIntersectionForm() << "\n"; 
	std::cout << "\nSignature:\n";
	for (double v : test.GetSignature()) std::cout << v << '\n';
	
	//Blowdown and check unimodularity
	for(int i = 0; i < th3.GetT(); i++ )
	{
		if( (test.GetIntersectionForm())(i,i) == -1 )
		{	
			test.Blowdown(i+1);

			if (isSquare)
			{
				std::cout << "Intersection form:\n" << test << "\n\n";
				std::cout << "Determinant : " << test.CheckUnimodularity()
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

		test = th3;


	}




}
