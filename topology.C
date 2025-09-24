#include <iostream>
#include <fstream>
#include "Theory.h"



int main() {


	//low topology SCFT first.. we want to get the full list of SCFT by computer sweeping
	

	int params[] = {
		// 기본 AT 꼬리 패턴
		1, 12, 122, 1222, 12222, 122222, 1222222, 12222222, 122222222, 1222222222,

		// interiors
		22, 33, 44, 55, 331, 32, 23, 42, 24, 43, 34, 53, 35, 54, 45,

		// alkali 2 links with no -5
		991, 9920, 9902, 993,

		// alkali 1 links with no -5
		91, 92, 93, 94, 95, 96, 97, 98, 99, 910, 911, 912, 913, 914, 915, 916, 917,

		// alkali 3 links with one -5 curve
		99910, 99901, 99920, 99902, 99930, 99903,

		// alkali 2 links with one -5 curve
		994, 995, 996, 997, 998, 999, 9910, 9911, 9912, 9913, 9914,

		// alkali 1 links with one -5 curve
		918, 919, 920, 921, 922, 923, 924, 925, 926, 927,
		928, 929, 930, 931, 932, 933, 934, 935, 936, 937,
		938, 939, 940, 941, 942, 943, 944, 945,

		// alkali 2 links with two -5 curves
		9915, 9916, 9917,

		// alkali 1 links with two -5 curves
		946, 947, 948, 949, 950, 951, 952, 953, 954, 955, 956, 957
	};

	int Nparams = sizeof(params) / sizeof(params[0]);

	int num = 0;
	int num2 = 0;
	int num3 = 0;

	for (int n: { 4, 6, 7, 8, 12 })
	{
		for ( int i = 0; i < Nparams; i++)
		{

			TheoryGraph G;
			Tensor g;


			auto S1 = G.add(s(params[i]));   // 사이드 링크 #1  (AT(-1), AT(-2)로 구성)
			auto N = G.add(n_(n));  

			try {G.connect(S1, N);} catch (const std::invalid_argument&) {continue;}

			
			Eigen::MatrixXi glued = G.ComposeIF_UnitGluing();

			g.SetIF(glued);
			g.Setb0Q();

			if ( g.TimeDirection() == 0 && g.NullDirection() == 0)
			{
				g.ForcedBlowdown();
				if ( g.NullDirection() == 0 && g.TimeDirection() == 0)
				{
					num++;
					std::cout << "SCFT found " << std::endl;
					std::cout << g.GetIntersectionForm() << std::endl;
#include <fstream>

					// SCFT 찾은 블록 안

					const Eigen::MatrixXi IF = glued;

					std::ofstream ofs("SCFT_Sg.txt", std::ios::app); // append 모드
					if (!ofs) {
						std::cerr << "[!] cannot open output file\n";
					} else {
						for (int r = 0; r < IF.rows(); ++r) {
							for (int c = 0; c < IF.cols(); ++c) {
								if (c) ofs << ' ';     // 공백 구분
								ofs << IF(r, c);
							}
							ofs << '\n';
						}
						ofs << '\n';  // 행렬 사이에 빈 줄
					}



					std::cout << "=== Graph Edges ===\n";
					G.printLinearWithSides();
				}
			}
		}
	}


	for (int i = 0; i < Nparams; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			for ( int n: { 4, 6, 7, 12 } )
			{

				TheoryGraph G;
				Tensor g;


				auto S1 = G.add(s(params[i]));   // 사이드 링크 #1  (AT(-1), AT(-2)로 구성)
				auto N = G.add(n_(n));  
				auto S2 = G.add(s(params[j]));

				try {G.connect(S1, N);} catch (const std::invalid_argument&) {continue;}
				try {G.connect(S2, N);} catch (const std::invalid_argument&) {continue;}


				Eigen::MatrixXi glued = G.ComposeIF_UnitGluing();

				g.SetIF(glued);
				g.Setb0Q();

				if ( g.TimeDirection() == 0 && g.NullDirection() == 0)
				{
					g.ForcedBlowdown();
					if ( g.NullDirection() == 0 && g.TimeDirection() == 0)
					{
						num2++;
						std::cout << "SCFT found " << std::endl;
						std::cout << g.GetIntersectionForm() << std::endl;

						const Eigen::MatrixXi IF = glued;

						std::ofstream ofs("SCFT_SgS.txt", std::ios::app); // append 모드
						if (!ofs) {
							std::cerr << "[!] cannot open output file\n";
						} else {
							for (int r = 0; r < IF.rows(); ++r) {
								for (int c = 0; c < IF.cols(); ++c) {
									if (c) ofs << ' ';     // 공백 구분
									ofs << IF(r, c);
								}
								ofs << '\n';
							}
							ofs << '\n';  // 행렬 사이에 빈 줄
						}




						std::cout << "=== Graph Edges ===\n";
						G.printLinearWithSides();
					}
				}
			}
		}
	}

	/*
	for (int i = 0; i < Nparams; i++)
	{
		for (int j = 0; j <= i; j++)
		{

			for (int k = 0; k <= j; k++)
			{
				for ( int n: { 4, 6, 7, 12 } )
				{

					TheoryGraph G;
					Tensor g;


					auto S1 = G.add(s(params[i]));   // 사이드 링크 #1  (AT(-1), AT(-2)로 구성)
					auto N = G.add(n_(n));  
					auto S2 = G.add(s(params[j]));
					auto S3 = G.add(s(params[k]));

					try {G.connect(S1, N);} catch (const std::invalid_argument&) {continue;}
					try {G.connect(S2, N);} catch (const std::invalid_argument&) {continue;}
					try {G.connect(S3, N);} catch (const std::invalid_argument&) {continue;}


	
					Eigen::MatrixXi glued = G.ComposeIF_UnitGluing();

					g.SetIF(glued);
					g.Setb0Q();

					if ( g.TimeDirection() == 0 && g.NullDirection() == 0)
					{
						g.ForcedBlowdown();
						if ( g.NullDirection() == 0 && g.TimeDirection() == 0)
						{
							num3++;
							std::cout << "SCFT found " << std::endl;
							std::cout << g.GetIntersectionForm() << std::endl;

							std::cout << "=== Graph Edges ===\n";
							G.printLinearWithSides();
						}
					}
				}
			}
		}
	}
	*/


	std::cout << "total SCFT s-n: " << num << std::endl;
       	std::cout << "total SCFT s-n-s: " << num2 << std::endl;
	std::cout << "total SCFT s-n-s: " << num3 << std::endl;	

}
