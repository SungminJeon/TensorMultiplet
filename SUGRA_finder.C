
#include <iostream>
#include "Theory.h"
#include <vector>

int main()
{


	Theory th;
	Theory* test = new Theory(th);

/*
	test->AddT(-8);
	test->AddLink(4,5);
	test->AddT(-12);
	test->AddLink(5,5); test-> AddT(-12);
	test->AddLink(5,5); test-> AddT(-12);
	test->AddLink(5,5); test-> AddT(-12);
	test->AddLink(5,5); test-> AddT(-12);
	test->AddLink(5,5); test-> AddT(-12);
	test->AddLink(5,5);
	test->AddT(-12);
	test->AddLink(4,2);
	test->AddT(-4);
	test->AddT(-1);
	test->AddT(-4);


	test->AddT(-1); test->intersect(test->GetT(),12);
	test->AddT(-1); test->intersect(test->GetT(),84);

	for (int i = 1; i < test->GetT()-2; i++)
	{
		test->intersect(i,i+1);
	}

	test->AddT(-1);
	//test->AddT(-1); test->intersect(test->GetT(),test->GetT()-1);


	std::cout << test->GetIntersectionForm() << std::endl;

*/


	test->AddT(-12);
	test->AddLink(5,5);
	test->AddT(-12);
	test->AddLink(5,5); test->AddT(-12);
	test->AddLink(5,5); test->AddT(-12);
	test->AddLink(5,5); test->AddT(-12);
	test->AddLink(5,5); test->AddT(-12);
	test->AddLink(5,5); test->AddT(-12);
	test->AddLink(5,5); test->AddT(-12);
	test->AddLink(5,5); test->AddT(-12);
	test->AddLink(5,5); test->AddT(-12);
	test->AddLink(5,3);
	test->AddT(-4);
	


	test->AddT(-1); test->intersect(test->GetT(),13); 

	for(int i =1; i<test->GetT()-1;i++)
	{
		test->intersect(i,i+1);
	}

	test->AddT(-1);
//	test->AddT(-1); test->intersect(test->GetT(), test->GetT()-1);

	for (int enode1 : {-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2})
	{
		//for (int enode2 : {-6,-5,-4,-3,-2})
		//{

			test->SetElement(0,0,enode1);
			//std::cout << test->GetIntersectionForm()(0,0) <<std::endl;
		//	test->SetElement(test->GetT()-3,test->GetT()-3,enode2);

		//	std::cout << test->GetIntersectionForm() << std::endl;
			
		
			for (int j = 1; j < test->GetT(); j++)
			{
				test->intersect(test->GetT(),j);

			//	std::cout << test->GetIntersectionForm() <<std::endl;
				bool b = test->IsSUGRA();


				if (b == 1)
				{
					std::cout << "SUGRA FOUND (enode1,enode2) : ("<< enode1 << ", "  ") intersect : "  << j << " DET : " << test->IsUnimodular() << " time direction : " << test->TimeDirection() <<  std::endl;

					//std::cout << test->GetIntersectionForm() << std::endl;

					Theory forbl(*test);
					for (int bl = 0; bl < forbl.GetT()-1; bl++)
					{
					
						
						if (forbl.GetIntersectionForm()(bl,bl) == -1 && forbl.GetIntersectionForm()(bl,forbl.GetT()-1) == 0)
						{
							bool c = forbl.Blowdown2(bl+1);

							bool cons = forbl.IsUnimodular();

							if ( c == 1 && cons ==1 )
							{
								bl = -1;
							}
							else if ( cons == 0 )
							{
								std::cout << "//////    BLOWDOWN CONSISTENCY VIOLATION     ///// " <<std::endl;
								break;
							}

							
						
						}
					}

					if ( forbl.IsSUGRA() == 1 )
					{
						std::cout << forbl.GetIntersectionForm() <<std::endl;
					}
					else if (forbl.IsSUGRA() == 0)
					{
						std::cout << "//////    BLOWDOWN CONSISTENCY VIOLATION     ///// " <<std::endl;
					}

				}
				





				
				else if (b == 0)
				{
					std::cout << "**NOT SUGRA** (enode1,enode2) : ("<< enode1 << ", "   ") intersect : "  << j << " DET : " << test->IsUnimodular() << " time direction : " << test->TimeDirection() <<  std::endl;
	
				}

				test->not_intersect(test->GetT(),j);
			}
		//}
	}

	delete test;
}




