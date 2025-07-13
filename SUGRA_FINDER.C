#include <iostream>
#include "Theory.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>



static std::string csv_escape(std::string_view s)
{
	bool need_quote = false;
	std::string out;
	out.reserve(s.size() + 2);

	for(char c : s) {
		if (c == '"' || c == ',' || c == '\n' || c == '\r') need_quote = true;
		if (c == '"')  out += "\"\"";
		else           out += c;
	}
	if (need_quote)  return '"' + out + '"';
	return out;
}


static std::string matrix_field(const Eigen::MatrixXi& M)
{
	std::ostringstream ss;
	for(int r = 0; r < M.rows(); ++r) {
		for(int c = 0; c < M.cols(); ++c) {
			ss << M(r,c);
			if (c < M.cols()-1) ss << ' ';
		}
		if (r < M.rows()-1) ss << ';';
	}
	return csv_escape(ss.str());
}



int main() {


	std::ofstream ofs("sugra_candidates.csv", std::ios::app);
	if (ofs.tellp() == 0)
		ofs << "base,intersect to,T,det,signature,matrix\n";

	int base;


	Theory* TEST = new Theory();

	base = 1;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-1);
	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-3);

	std::cout << TEST->GetIntersectionForm() << std::endl;


	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		
		TEST->Setb0Q();

		Theory B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.FBlowdown();
			std::cout << B.GetIFb0Q() << std::endl;

			int d = B.GetExactDet();
			int sig = B.TimeDirection();

			ofs << base << ',' << i << ',' << B.GetT() << ','
				<< d    << ',' << sig << ','
				<< matrix_field(B.GetIFb0Q()) << '\n';

			B.ForcedBlowdown();
			std::cout << B.GetIFb0Q() << std::endl;

		}
		else if( c==0 )
		{
			std::cout << "NOT SUGRA" << std::endl;
		}

		TEST->DeleteTensorMultiplet();
	}



	TEST->Initialize();
	base = 2;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-2);
	TEST->AT(-3);
	TEST->AT(-1);
	TEST->AT(-4);
	
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

	std::cout << TEST->GetIntersectionForm() << std::endl;


	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Theory B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.FBlowdown();

			std::cout << B.GetIFb0Q() << std::endl;
			
			int d = B.GetExactDet();
			int sig = B.TimeDirection();

			ofs << base << ',' << i << ',' << B.GetT() << ','
				<< d    << ',' << sig << ','
				<< matrix_field(B.GetIFb0Q()) << '\n';



			B.ForcedBlowdown();
			std::cout << B.GetIFb0Q() << std::endl;

		}
		else if( c==0)
		{
			std::cout << "NOT SUGRA" << std::endl;
		}

		TEST->DeleteTensorMultiplet();
	}


	TEST->Initialize();
	base = 3;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-3);
	TEST->AT(-1);
	TEST->AT(-4);
	
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

	std::cout << TEST->GetIntersectionForm() << std::endl;


	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Theory B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.FBlowdown();

			std::cout << B.GetIFb0Q() << std::endl;

			int d = B.GetExactDet();
			int sig = B.TimeDirection();

			ofs << base << ',' << i << ',' << B.GetT() << ','
				<< d    << ',' << sig << ','
				<< matrix_field(B.GetIFb0Q()) << '\n';

			B.ForcedBlowdown();
			std::cout << B.GetIFb0Q() << std::endl;

		}
		else if( c==0)
		{
			std::cout << "NOT SUGRA" << std::endl;
			
		}

		TEST->DeleteTensorMultiplet();
	}

	TEST->Initialize();
	base = 4;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-6);
	TEST->AL(2,2);
	TEST->AT(-4);
	
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(2,2);
	TEST->AT(-6);

	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Theory B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.FBlowdown();

			std::cout << B.GetIFb0Q() << std::endl;

			int d = B.GetExactDet();
			int sig = B.TimeDirection();

			ofs << base << ',' << i << ',' << B.GetT() << ','
				<< d    << ',' << sig << ','
				<< matrix_field(B.GetIFb0Q()) << '\n';

			B.ForcedBlowdown();
			std::cout << B.GetIFb0Q() << std::endl;

		}
		else if( c==0)
		{
			std::cout << "NOT SUGRA" << std::endl;
	
		}

		TEST->DeleteTensorMultiplet();
	}
	
	TEST->Initialize();
	base = 5;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	
	TEST->AL(2,4);
	TEST->AT(-12);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);

	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Theory B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.FBlowdown();

			std::cout << B.GetIFb0Q() << std::endl;

			int d = B.GetExactDet();
			int sig = B.TimeDirection();

			ofs << base << ',' << i << ',' << B.GetT() << ','
				<< d    << ',' << sig << ','
				<< matrix_field(B.GetIFb0Q()) << '\n';

			B.ForcedBlowdown();
			std::cout << B.GetIFb0Q() << std::endl;

		}
		else if( c==0)
		{
			std::cout << "NOT SUGRA" << std::endl;
	
		}

		TEST->DeleteTensorMultiplet();
	}


	delete TEST;
	ofs.close();
}





