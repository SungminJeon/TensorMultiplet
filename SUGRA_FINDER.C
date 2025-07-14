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
	base = 6;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(3,2);
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
	base = 7;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(3,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);

	TEST->AL(2,3);
	TEST->AT(-8);







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
	base = 8;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
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
	base = 9;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
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
	base = 10;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(3,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
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
	base = 11;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);

	TEST->AL(2,3);
	TEST->AT(-8);







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
	base = 12;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(3,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);

	TEST->AL(2,3);
	TEST->AT(-8);







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
	base = 13;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
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
	base = 14;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
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
	base = 15;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);

	TEST->AL(2,3);
	TEST->AT(-8);







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
	base = 16;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(3,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);


	TEST->AL(2,3);
	TEST->AT(-8);







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
	base = 17;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
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
	base = 18;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
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
	base = 19;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);


	TEST->AL(2,3);
	TEST->AT(-8);







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
	base = 20;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
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
	base = 21;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
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
	base = 22;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);


	TEST->AL(2,3);
	TEST->AT(-8);







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
	base = 23;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
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
	base = 24;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
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
	base = 25;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);


	TEST->AL(2,3);
	TEST->AT(-8);







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
	base = 26;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-3);
	TEST->AT(-1);
	TEST->ATS2(-3,-1,-6);

	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);


	TEST->AL(3,5);
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
	base = 27;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
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
	base = 28;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-3);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->AT(-6);

	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	


	TEST->AL(3,5);
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
	base = 29;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);


	TEST->AL(2,3);
	TEST->AT(-8);







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
	base = 30;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,3);
	TEST->AT(-6);

	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	


	TEST->AL(2,2);
	TEST->AT(-4);







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
	base = 31;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
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
	base = 32;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
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
	base = 33;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,3);
	TEST->AT(-6);

	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	


	TEST->AL(2,2);
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);







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
	base = 34;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-3);
	TEST->AT(-1);
	TEST->ATS2(-3,-1,-6);

	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	


	TEST->AL(3,5);
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
	base = 35;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);


	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);



	TEST->AL(3,5);
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
	base = 36;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1), TEST->AT(-4);

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
	base = 37;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(4,2);
	TEST->AT(-4);

	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
	TEST->AL(1,1); TEST->AT(-4);
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
	base = 38;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,3);
	TEST->AT(-6);

	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	


	TEST->AL(3,3);
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
	base = 39;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,3);
	TEST->AT(-6);

	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);



	TEST->AL(2,2);
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);







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
	base = 40;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-1);
	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	



	TEST->AL(3,2);
	TEST->AT(-4);







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
	base = 41;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(4,3);
	TEST->AT(-6);

	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);



	TEST->AL(3,4);
	TEST->AT(-8);








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
	base = 42;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,3);
	TEST->AT(-6);

	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);



	TEST->AL(3,3,1);
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
	base = 43;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-3);
	TEST->AT(-1);
	TEST->AT(-6);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	



	TEST->AL(4,5);
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
	base = 44;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,3);
	TEST->AT(-6);

	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);



	TEST->AL(3,4);
	TEST->AT(-8);
	







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
	base = 45;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-3);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->ATS(-1,-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	



	TEST->AL(4,5);
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
	base = 46;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(2,2);
	TEST->AT(-6);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);



	TEST->AL(3,3);
	TEST->AT(-6);
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
	base = 47;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,3);
	TEST->AT(-6);

	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);



	TEST->AL(3,5);
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
	base = 48;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,3);
	TEST->AT(-6);

	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);



	TEST->AL(3,3);
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
	base = 49;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,3);
	TEST->AT(-6);

	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);



	TEST->AL(2,2);
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);







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
	base = 50;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-1);
	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);




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

	TEST->Initialize();
	base = 51;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-3);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	



	TEST->AL(4,5);
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

	delete TEST;
	ofs.close();
}





