#include <iostream>
#include "Tensor.h"
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


	Tensor* TEST = new Theory();


	
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 52;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AL(2,3);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 53;

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
	



	TEST->AL(3,3,1);
	TEST->AT(-6);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 54;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-5);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-3);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 55;

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
	



	TEST->AL(3,4);
	TEST->AT(-8);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 56;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);


	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	



	TEST->AL(3,3);
	TEST->AT(-4);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 57;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-5);
	TEST->AL(2,3);
	TEST->AT(-8);


	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	



	TEST->AL(4,5);
	TEST->AT(-12);
	TEST->AT(-1);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 58;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	



	TEST->AL(4,5);
	TEST->AT(-12);
	TEST->AT(-1);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 59;

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
	



	TEST->AL(3,5);
	TEST->AT(-12);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 60;

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
	TEST->AL(2,2); TEST->AT(-6);

	TEST->AL(3,3);
	TEST->AT(-6);
	

	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 61;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);


	TEST->AL(3,2);
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 62;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-3);
	TEST->AT(-1);
	TEST->AT(-5);
	TEST->AT(-1);
	TEST->AT(-3);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 63;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-2);
	TEST->AT(-1);
	TEST->ATS(-1,-8);

	TEST->AL(3,3); TEST->AT(-8);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 64;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	TEST->AL(5,4);
	TEST->AT(-8);
	TEST->AL(3,3);
	TEST->AT(-8);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 65;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	
	


	TEST->AL(3,3);
	TEST->ATS2(-2,-1,-8);
	TEST->AT(-1);
	TEST->AT(-2);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 66;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-3);
	TEST->AT(-1);
	TEST->AT(-6);

	TEST->AL(3,3); TEST->AT(-8);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 67;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 68;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(4,4);
	TEST->AT(-8);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 69;

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
	TEST->AL(2,2); TEST->AT(-6);


	TEST->AL(3,3,1);
	TEST->AT(-6);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 70;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);


	TEST->AL(3,3);
	TEST->ATS(-1,-8);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 71;

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
	TEST->AL(2,2); TEST->AT(-6);

	TEST->AL(3,4);
	TEST->AT(-8);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 72;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 73;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);


	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 74;

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
	TEST->AL(2,2); TEST->AT(-6);
	


	TEST->AL(3,5);
	TEST->AT(-12);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 75;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-5);
	TEST->AL(2,3);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 76;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 77;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	


	TEST->AL(3,3);
	TEST->AT(-4);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 78;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);


	TEST->AL(3,3); 
	TEST->ATS(-1,-8);
	TEST->AL(3,3);
	TEST->AT(-6);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 79;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	


	TEST->AL(3,2);
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 80;

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
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);


	TEST->AL(3,4);
	TEST->AT(-8);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 81;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);




	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-3);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->AT(-5);
	TEST->AT(-1);
	TEST->AT(-3);
	







	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 82;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);




	TEST->AL(3,3);
	TEST->ATS2(-2,-1,-8);
	TEST->AT(-1);
	TEST->AT(-2);
	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 83;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(4,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);




	TEST->AL(4,4);
	TEST->AT(-8);
	
	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 84;

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
	TEST->AL(2,2); TEST->AT(-6);
	TEST->AL(2,2); TEST->AT(-6);
	


	TEST->AL(3,5);
	TEST->AT(-12);
	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 85;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);



	TEST->AL(4,3);
	TEST->AT(-6);
	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 86;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);



	TEST->AL(3,3);
	TEST->ATS(-1,-8);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 87;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  




	TEST->AT(-1);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-8);

	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);



	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 88;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);



	TEST->AL(4,4);
	TEST->AT(-8);
	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 89;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 90;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);


	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 91;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-2);
	TEST->AT(-1);
	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-8);

	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);



	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 92;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 93;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);


	TEST->AL(3,3);
	TEST->AT(-4);
	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 94;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	

	TEST->AL(3,3);
	TEST->ATS(-1,-8);
	TEST->AL(3,3);
	TEST->AT(-6);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 95;

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 96;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	

	TEST->AL(3,2);
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 97;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);
	

	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	
	
	

	TEST->AL(5,4);
	TEST->AT(-8);
	TEST->AL(3,3);
	TEST->AT(-8);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 98;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	

	TEST->AL(4,3);
	TEST->AT(-6);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 99;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	

	TEST->AL(4,4);
	TEST->AT(-8);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 100;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 101;

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 102;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 103;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	

	TEST->AL(3,3);
	TEST->ATS(-1,-8);
	TEST->AL(3,3);
	TEST->AT(-6);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 104;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-1);
	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	

	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(4,2);
	TEST->AT(-4);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 105;

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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 106;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);



	TEST->AL(4,3);
	TEST->AT(-6);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 107;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-1);
	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	

	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 108;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-1);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	

	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 109;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);



	TEST->AL(4,4);
	TEST->AT(-8);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 110;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 111;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-2);
	TEST->AT(-1);
	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	

	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 112;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 113;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-1);
	TEST->ATS(-1,-8);
	TEST->AL(4,5);
	TEST->AT(-12);

	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);


	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	TEST->AT(-1);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 114;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-1);
	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	

	TEST->AL(5,4);
	TEST->AT(-8);
	TEST->AT(-1);
	TEST->AT(-2);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 115;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  




	TEST->AT(-1);
	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	

	TEST->AL(5,5);
	TEST->AT(-8);
	TEST->AT(-1);
	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 116;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-3);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->AT(-8);
	TEST->AL(4,5);
	TEST->AT(-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	

	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 117;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);



	TEST->AL(4,4);
	TEST->AT(-8);
	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 118;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->ATS2(-2,-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	

	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);	
	TEST->AT(-1);






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 119;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-3);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->ATS2(-2,-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	

	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 120;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);

	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 121;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	

	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	TEST->AT(-1);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 122;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	
	TEST->AT(-1);
	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	

	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 123;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	

	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 124;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-5);
	TEST->AL(2,4);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	

	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	TEST->AT(-1);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 125;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	

	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 126;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	

	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-3);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 127;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);


	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 128;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-3);
	TEST->AT(-1);
	TEST->AT(-5);
	TEST->AT(-1);
	TEST->AT(-3);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);


	TEST->AL(5,5); 
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 129;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-1);
	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 130;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-5);
	TEST->AT(-1);
	TEST->AT(-3);
	TEST->AT(-1);
	TEST->AT(-5);
	TEST->AT(-1);
	TEST->AT(-3);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->AT(-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);


	TEST->AL(5,5); 
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);	



	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 131;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);
	
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 132;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,3);
	TEST->AT(-4);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 133;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	
	TEST->AT(-6);
	TEST->AL(3,5);
	TEST->AT(-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	
	
	TEST->AL(5,5); 
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	TEST->AT(-1);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 134;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-1);
	TEST->ATS(-1,-8);
	TEST->AL(4,5);
	TEST->AT(-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);


	TEST->AL(5,5); 
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 135;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(4,5);
	TEST->AT(-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);


	TEST->AL(5,5); 
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	TEST->AT(-1);
	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 136;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  




	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->AT(-6);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 137;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-1);
	TEST->AT(-8);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 138;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-2);
	TEST->AT(-1);
	TEST->AT(-8);
	TEST->AL(4,5);
	TEST->AT(-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	
	TEST->AL(5,5); 
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 139;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	TEST->AT(-1);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 140;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,4);
	TEST->ATS(-1,-8);
	TEST->AT(-1);
	TEST->AT(-2);	






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 141;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-8);
	TEST->AT(-1);
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 142;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,4);
	TEST->AT(-8);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 143;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->AT(-8);
	TEST->AT(-1);
	TEST->AT(-2);
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 144;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->ATS2(-2,-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 145;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS3(-2,-2,-1,-12);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 146;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 147;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);
	
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 148;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS2(-2,-1,-12);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 149;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->AT(-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 150;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,4);
	TEST->AT(-8);
	TEST->AL(3,3);
	TEST->AT(-6);

		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 151;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 152;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 153;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-5);
	TEST->AL(2,4);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);

		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 154;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-3);
	TEST->AT(-1);
	TEST->AT(-3);
	TEST->AT(-2);
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 155;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-3);
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 156;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 157;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 158;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-3);
	TEST->AT(-1);
	TEST->AT(-5);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-3);
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 159;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(3,5);
	TEST->AT(-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);

		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 160;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(4,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,4);
	TEST->AT(-8);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 161;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,4);
	TEST->AT(-8);
	
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);
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

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 162;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,3);
	TEST->AT(-4);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 163;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,3);
	TEST->AT(-6);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 164;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(4,5);
	TEST->AT(-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 165;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-3);
	TEST->AT(-1);
	TEST->AT(-5);
	TEST->AT(-1);
	TEST->AT(-3);
	TEST->AT(-1);
	TEST->AT(-5);
	TEST->AT(-1);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 166;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-3);
	TEST->AT(-1);
	TEST->AT(-5);
	TEST->AT(-1);
	TEST->AT(-3);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->AT(-5);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 167;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,4);
	TEST->AT(-8);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 168;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 169;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->AT(-6);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 170;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 171;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,4);
	TEST->ATS(-1,-8);
	TEST->AT(-1);
	TEST->AT(-2);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 172;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-8);
	TEST->AT(-1);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 173;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,4);
	TEST->AT(-8);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 174;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->AT(-8);
	TEST->AT(-1);
	TEST->AT(-2);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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


*/


	
	TEST->Initialize();
	base = 175;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS3(-2,-2,-1,-12);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	
		




	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 176;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS2(-2,-1,-12);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 177;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,4);
	TEST->AT(-8);
	TEST->AL(3,3);
	TEST->AT(-6);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 178;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 179;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-2);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 180;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-3);
	TEST->AT(-1);
	TEST->AT(-3);
	TEST->AT(-2);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 181;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-3);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 182;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 183;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-3);
	TEST->AT(-1);
	TEST->AT(-5);
	TEST->AT(-1);
	TEST->AT(-2);
	TEST->AT(-3);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 184;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,3);
	TEST->AT(-4);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 185;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,3);
	TEST->AT(-6);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 186;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,4);
	TEST->AT(-8);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 187;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 188;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,4);
	TEST->AT(-8);
	TEST->AL(3,3);
	TEST->AT(-6);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 189;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,3);
	TEST->AT(-6);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 190;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,4);
	TEST->AT(-8);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 191;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 192;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,4);
	TEST->AT(-8);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 193;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 194;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 195;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);


	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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
	base = 196;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-12);
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);


	
	TEST->AL(5,5);
	TEST->ATS(-1,-12);
	TEST->AL(5,5);
	TEST->AT(-12);
	
		






	std::cout << TEST->GetIntersectionForm() << std::endl;

	

	for (int i = 1; i <= TEST->GetT(); i++ )
	{
		TEST->ATE(-1,i);
		TEST->Setb0Q();

		Tensor B(*TEST);

		bool c = B.IsSUGRA();

		if ( c == 1)
		{
			std::cout << "SUGRA CANDIDATE FOUND (i= " << i << " )\n" << std::endl;
			B.LSTBlowdown(2);

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





