#include "Theory.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

void save_blowdown_sequence( int i,
                                           // (-1,i)  인덱스
        const std::vector<Eigen::MatrixXi>& seq) // 단계별 Intersection Form
{
    try {
        /* 1) 경로 구성 -------------------------------------------------- */
        fs::path base_dir = "Bl_SUGRA_" + std::to_string(i);
       

      

        /* 2) 단계별 파일 저장 ------------------------------------------- */
        // Eigen 행렬 출력 형식을 깔끔하게 정의
        Eigen::IOFormat fmt(Eigen::StreamPrecision, 0, " ", "\n");

        for (std::size_t k = 0; k < seq.size(); ++k)
        {
            fs::path file = base_dir /
                ("step_" + std::to_string(k) + ".txt");

            std::ofstream ofs(file, std::ios::out | std::ios::trunc);
            if (!ofs) {
                throw std::runtime_error("cannot open " + file.string());
            }
            ofs << seq[k].format(fmt) << '\n';
        }
        std::cout << "Saved" << std::endl;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "filesystem error: " << e.what() << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << "error: " << e.what() << '\n';
    }
    
}



int main () 
{


	Theory th;
	int Number = 0;
	int base = 316;

	fs::path out_dir = std::string("./Bl_SUGRA_") + std::to_string(base);


		
	th.AddTensorMultiplet(-12);
	th.AddLink(5,5);
	th.AddTensorMultiplet(-12);
	th.AddLink(5,5); th.AddTensorMultiplet(-12);
	th.AddLink(5,5); th.AddTensorMultiplet(-12);
	th.AddLink(5,5); th.AddTensorMultiplet(-12);
	th.AddLink(5,5); th.AddTensorMultiplet(-12);
	th.AddLink(5,5); th.AddTensorMultiplet(-12);
	th.AddLink(5,5); th.AddTensorMultiplet(-12);
	th.AddLink(5,5); th.AddTensorMultiplet(-12);
	th.AddLink(5,5); th.AddTensorMultiplet(-12);

	th.AddLink(5,3);
	th.AddTensorMultiplet(-4);
	
	// side tensors
	th.AddTensorMultiplet(-1); th.intersect(13,th.GetT());
	


	for(int i=1;i<th.GetT()-1;++i) th.intersect(i,i+1);
		

	
		
	
			
	Theory* test;
	test = new Theory(th);



	std::vector<Eigen::MatrixXi> seq;


	bool c;
	std::vector<int> v;

	std::cout << "EIGENVALUES : \n" << test->GetEigenvalues() << std::endl;
	std::cout << "Detereminant : \n" << test->GetExactDet() << std::endl;
	std::cout << "TimeDirection : " << test->TimeDirection() << std::endl;	
	for( int i = 0; i < test->GetT(); i++)
	{
		if ( test->GetIntersectionForm()(i,i) == -1 )
		{
			bool b = test->Blowdown2(i+1);





			seq.push_back(test->GetIntersectionForm());

			std::cout << " Blowdowned " << std::endl;
			std::cout <<"Time direction for consistent base : " <<  test->TimeDirection() << std::endl;
			std::cout <<" DET : " << test->GetExactDet() <<std::endl;

			if ( b == 1 )
			{


				i = -1;
				//std::cout << " Blowdown " << std::endl;
				//std::cout << intersection_form << std::endl;
			}


		}


	}
	delete test;

	save_blowdown_sequence(base, seq);




			


		
		
	

}

