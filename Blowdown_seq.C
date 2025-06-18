#include "Theory.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

void save_blowdown_sequence(
        int i,                                   // (-1,i)  인덱스
        const std::vector<Eigen::MatrixXi>& seq) // 단계별 Intersection Form
{
    try {
        /* 1) 경로 구성 -------------------------------------------------- */
        fs::path base_dir = "LST_360_Blowdown_seq";
        fs::path curve_dir = base_dir /
            ("LST_360_Blowdown_seq_(-1," + std::to_string(i) + ")");

        // 중간 경로까지 모두 한 번에 생성 (이미 있으면 아무 일도 안 함)
        fs::create_directories(curve_dir);

        /* 2) 단계별 파일 저장 ------------------------------------------- */
        // Eigen 행렬 출력 형식을 깔끔하게 정의
        Eigen::IOFormat fmt(Eigen::StreamPrecision, 0, " ", "\n");

        for (std::size_t k = 0; k < seq.size(); ++k)
        {
            fs::path file = curve_dir /
                ("step_" + std::to_string(k) + ".txt");

            std::ofstream ofs(file, std::ios::out | std::ios::trunc);
            if (!ofs) {
                throw std::runtime_error("cannot open " + file.string());
            }
            ofs << seq[k].format(fmt) << '\n';
        }
        std::cout << "saved curve (-1," << i << ")  (" << seq.size()
                  << " steps)\n";
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "filesystem error: " << e.what() << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
    }
}

int main()
{
	Theory th;
	int Number = 0;
	int base = 360;
	// for file
	fs::path out_dir = std::string("./LST_360_Blowdown_seq"); 




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

	

	//NOW SEARCHING FOR AT LEAST CONSISTENT STRUCTURE FOR SUGRA
	for(int k : {-1} )
	{
		th.AddTensorMultiplet(k);
		//int T = th.GetT();
		
		for (int j = 1; j < th.GetT(); j++)
		{
			th.intersect(j,th.GetT());
			Theory* test;
			test = new Theory(th);

		

			std::vector<Eigen::MatrixXi> seq;
			
			bool b;
			bool c;
			std::vector<int> v;

			std::cout << "INTERSECTION CURVE " << j << std::endl;
			std::cout << "EIGENVALUES : \n" << test->GetEigenvalues() << std::endl;
		       	std::cout << "TimeDirection : " << test->TimeDirection() << std::endl;	
			for( int i = 0; i < test->GetT()-1; i++)
			{
				if(test->GetIntersectionForm()(i,i) == -1 && test->GetIntersectionForm()(i,test->GetT()-1) == 0 )
				{

					

					b = test->IsSUGRA();
					v.clear();
					for (int j = 0; j < test->GetT() ; j++)
					{
						if (test->GetIntersectionForm()(i,j) == 1)
						{
							v.push_back(j);
						}
					}

					if (v.size() < 3)
					{
						c = 1;
					}
					else
					{
						c = 0;
					}



					if (b == 1 && c == 1)
					{
						test->Blowdown2(i+1);
						seq.push_back(test->GetIntersectionForm());

						std::cout << " Blowdowned " << std::endl;
						std::cout <<"Time direction for consistent base : " <<  test->TimeDirection() << std::endl;

						i = -1;
						//std::cout << " Blowdown " << std::endl;
						//std::cout << intersection_form << std::endl;
					}
					else if ( b == 0 || c == 0)
					{
						std::cout << "NOT SUGRA ANYMORE" << std::endl;
						std::cout << test->GetEigenvalues() << std::endl;

						

						for (int m = 0; m < test->GetT(); m++)
						{
							if ( test->GetEigenvalues()[m] > 0 )
							{
								std::cout << " EV : " << test->GetEigenvalues()[m] << ", " << m << std::endl;
							}
						}

						
						std::cout << test -> TimeDirection() << std::endl;

						seq.push_back(test->GetIntersectionForm());

						break;
					}	
				}
				

			}
			delete test;

			save_blowdown_sequence(j,seq);




			th.not_intersect(j,th.GetT());


		}
		th.DeleteTensorMultiplet();
	}

}
