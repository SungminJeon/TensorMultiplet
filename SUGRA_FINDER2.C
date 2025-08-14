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

	
	base = 197;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-6);
	TEST->AL(3,3);
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
	base = 198;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-6);
	TEST->AL(3,3,1);
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
	base = 199;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-6);
	TEST->AL(3,3);
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
	base = 200;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-6);
	TEST->AL(3,3);
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
	base = 201;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-6);
	TEST->AL(3,3,1);
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
	base = 202;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(4,3);
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
	base = 203;

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
	base = 204;

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
	base = 205;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(2,3);
	TEST->AT(-8);

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

		Theory B(*TEST);

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
	base = 206;

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
	base = 207;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(2,2);
	TEST->AT(-6);

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

		Theory B(*TEST);

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
	base = 208;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(2,3);
	TEST->AT(-8);

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

		Theory B(*TEST);

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
	base = 209;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(3,3);
	TEST->ATS(-1,-8);

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

		Theory B(*TEST);

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
	base = 210;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(3,4);
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

		Theory B(*TEST);

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
	base = 211;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(3,4);
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

		Theory B(*TEST);

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
	base = 212;

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
	TEST->ATS2(-2,-1,-8);
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
	base = 213;

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
	TEST->ATS(-1,-8);
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
	base = 214;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(2,2);
	TEST->AT(-6);

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

		Theory B(*TEST);

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
	base = 215;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(3,3);
	TEST->ATS(-1,-8);

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
	base = 216;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(3,4);
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

		Theory B(*TEST);

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
	base = 217;

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
	base = 218;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(4,4);
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

		Theory B(*TEST);

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
	base = 219;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(3,3);
	TEST->ATS(-1,-8);

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

		Theory B(*TEST);

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
	base = 220;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(3,3);
	TEST->ATS(-1,-8);

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

		Theory B(*TEST);

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
	base = 221;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	
	TEST->AT(-6);
	TEST->AL(3,4);
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

		Theory B(*TEST);

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
	base = 222;

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
	TEST->ATS2(-2,-1,-8);	
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
	base = 223;

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
	TEST->ATS(-1,-8);	
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
	base = 224;

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


	TEST->AT(-1);
	TEST->AT(-2);
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
	base = 225;

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
	TEST->ATS(-1,-8);
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
	base = 226;

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


	TEST->AL(4,3); 
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
	base = 227;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 228;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 229;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->ATS(-1,-12);

	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);


	TEST->AL(4,2); 
	TEST->AT(-4);
	TEST->AL(1,1);
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
	base = 230;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 231;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  




	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 232;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 233;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(3,3);
	TEST->AT(-8);
	TEST->AL(4,5);
	TEST->AT(-12);


	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);


	TEST->AL(4,2); 
	TEST->AT(-4);
	TEST->AL(1,1);
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
	base = 234;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);
	

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

		Theory B(*TEST);

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
	base = 235;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);
	

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

		Theory B(*TEST);

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
	base = 236;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  

	
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->ATS(-1,-12);
	

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

		Theory B(*TEST);

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
	base = 237;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);
	

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

		Theory B(*TEST);

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
	base = 238;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	
	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->ATS(-1,-12);
	

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

		Theory B(*TEST);

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
	base = 239;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 240;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 241;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  




	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->ATS(-1,-12);

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

		Theory B(*TEST);

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
	base = 242;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-1);
	TEST->ATS(-1,-8);

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

		Theory B(*TEST);

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
	base = 243;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-2);
	TEST->AT(-1);
	TEST->ATS(-1,-8);
	TEST->AL(4,5);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 244;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  




	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->ATS(-1,-12);

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

		Theory B(*TEST);

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
	base = 245;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  




	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->ATS(-1,-12);

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

		Theory B(*TEST);

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
	base = 246;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-6);
	TEST->AL(3,3);
	TEST->AT(-8);
	TEST->AL(4,5);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 247;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(3,3);
	TEST->AT(-8);
	TEST->AL(4,5);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 248;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	
	TEST->AT(-6);
	TEST->AL(3,3);
	TEST->AT(-8);
	TEST->AL(4,5);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 249;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



		
	TEST->AT(-6);
	TEST->AL(3,3);
	TEST->AT(-8);
	TEST->AL(4,5);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 250;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(3,3);
	TEST->AT(-8);
	TEST->AL(4,5);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 251;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-2);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->ATS3(-2,-2,-1,-12);


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

		Theory B(*TEST);

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
	base = 252;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-2);
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
	TEST->AL(4,2);
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
	base = 253;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-2);
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
	TEST->AL(4,2);
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
	base = 254;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(2,4);
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
	base = 255;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  




	TEST->AT(-6);
	TEST->AL(3,5);
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

		Theory B(*TEST);

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
	base = 256;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(3,5);
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

		Theory B(*TEST);

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
	base = 257;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(3,5);
	TEST->ATS(-1,-12);

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

		Theory B(*TEST);

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
	base = 258;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(4,5);
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

		Theory B(*TEST);

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
	base = 259;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-8);
	TEST->AL(4,5);
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

		Theory B(*TEST);

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
	base = 260;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	
	TEST->AT(-8);
	TEST->AL(4,5);
	TEST->ATS(-1,-12);

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

		Theory B(*TEST);

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
	base = 261;

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
	base = 262;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	
	TEST->AT(-6);
	TEST->AL(3,5);
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

		Theory B(*TEST);

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
	base = 263;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(4,5);
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

		Theory B(*TEST);

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
	base = 264;

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
	TEST->ATS(-1,-8);
	TEST->AT(-1);









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
	base = 265;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(4,5);
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

		Theory B(*TEST);

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
	base = 266;

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
	TEST->AT(-8);
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
	base = 267;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  




	TEST->AT(-8);
	TEST->AL(4,5);
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

		Theory B(*TEST);

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
	base = 268;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	
	TEST->AT(-6);
	TEST->AL(3,5);
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

		Theory B(*TEST);

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
	base = 269;

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
	TEST->ATS3(-2,-2,-1,-12);
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
	base = 270;

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

		Theory B(*TEST);

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
	base = 271;

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

		Theory B(*TEST);

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
	base = 272;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	
	TEST->AT(-8);
	TEST->AL(4,5);
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

		Theory B(*TEST);

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
	base = 273;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	
	TEST->AT(-8);
	TEST->AL(4,5);
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

		Theory B(*TEST);

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
	base = 274;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	
	TEST->AT(-8);
	TEST->AL(4,5);
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

		Theory B(*TEST);

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
	base = 275;

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
	TEST->AL(5,3);
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
	base = 276;

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
	base = 277;

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
	base = 278;

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
	base = 279;

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
	base = 280;

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
	base = 281;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(2,2);
	TEST->AT(-6);

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

		Theory B(*TEST);

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
	base = 282;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(2,2);
	TEST->AT(-6);

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

		Theory B(*TEST);

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
	base = 283;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  




	TEST->AT(-6);
	TEST->AL(2,2);
	TEST->AT(-6);

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

		Theory B(*TEST);

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
	base = 284;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  




	TEST->AT(-6);
	TEST->AL(3,3);
	TEST->ATS(-1,-8);

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

		Theory B(*TEST);

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
	base = 285;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-6);
	TEST->AL(3,4);
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

		Theory B(*TEST);

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
	base = 286;

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


	TEST->AL(3,3);
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
	base = 287;

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


	TEST->AL(3,2);
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
	base = 288;

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
	base = 289;

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


	TEST->AL(3,3);
	TEST->ATS(-1,-8);
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
	base = 290;

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
	TEST->AL(3,3); TEST->AT(-8);

	TEST->AL(4,3);
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
	base = 291;

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
	TEST->AL(3,3); TEST->AT(-8);

	TEST->AL(4,4);
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
	base = 292;

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

		Theory B(*TEST);

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
	base = 293;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  




	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	TEST->AL(4,2);
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
	base = 294;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 295;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  




	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->ATS(-1,-12);

	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AL(1,1);
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
	base = 296;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  




	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 297;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 298;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 299;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(3,3);
	TEST->AT(-8);
	TEST->AL(4,5);
	TEST->AT(-12);

	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);
	TEST->AL(5,5); TEST->AT(-12);

	TEST->AL(4,2);
	TEST->AT(-4);
	TEST->AL(1,1);
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
	base = 300;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-4);
	TEST->AT(-1);
	TEST->AT(-4);
	TEST->AL(1,1);
	TEST->AT(-4);
	TEST->AL(2,4);
	TEST->AT(-12);

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

		Theory B(*TEST);

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
	base = 301;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(4,5);
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

		Theory B(*TEST);

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
	base = 302;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-8);
	TEST->AL(4,5);
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

		Theory B(*TEST);

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
	base = 303;

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
	TEST->AL(4,2);
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
	base = 304;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(4,5);
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

		Theory B(*TEST);

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
	base = 305;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  


	TEST->AT(-8);
	TEST->AL(4,5);
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

		Theory B(*TEST);

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
	base = 306;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(4,5);
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

		Theory B(*TEST);

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
	base = 307;

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
	TEST->AT(-3);
	TEST->AT(-2);
	TEST->AT(-1);
	TEST->AT(-5);





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
	base = 308;

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
	TEST->AT(-3);
	TEST->AT(-1);
	TEST->AT(-5);
	TEST->AT(-1);



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
	base = 309;

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
	base = 310;

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
	base = 311;

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
	base = 312;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-6);
	TEST->AL(2,2);
	TEST->AT(-6);
	
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

		Theory B(*TEST);

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
	base = 313;

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
	base = 314;

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
	TEST->AL(3,3); TEST->AT(-8);
	TEST->AL(3,3); TEST->AT(-8);

	TEST->AL(4,4);
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
	base = 315;

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
	TEST->ATS2(-2,-1,-8);
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
	base = 316;

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
	base = 317;

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

	TEST->AT(-1);
	TEST->AT(-2);
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
	base = 318;

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

		Theory B(*TEST);

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
	base = 319;

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
	base = 320;

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
	TEST->ATS(-1,-8);
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
	base = 321;

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
	TEST->ATS(-1,-8);
	TEST->AT(-1);






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
	base = 322;

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
	base = 323;

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
	TEST->AT(-8);
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
	base = 324;

	std::cout << " //////////////// base number : " << base << " /////////////////////////// " << std::endl;  



	TEST->AT(-8);
	TEST->AL(4,5);
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

		Theory B(*TEST);

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
	base = 325;

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
	TEST->ATS3(-2,-2,-1,-12);
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
	base = 326;

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

		Theory B(*TEST);

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
	base = 327;

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

		Theory B(*TEST);

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
	base = 328;

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

		Theory B(*TEST);

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
	base = 329;

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

		Theory B(*TEST);

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
	base = 330;

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

		Theory B(*TEST);

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
	base = 331;

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

		Theory B(*TEST);

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
	base = 332;

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

		Theory B(*TEST);

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
	base = 333;

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
	base = 334;

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
	base = 335;

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
	base = 336;

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
	base = 337;

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
	base = 338;

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
	base = 339;

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
	

	TEST->AL(3,2);
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
	base = 340;

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
	TEST->ATS2(-2,-1,-8);
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
	base = 341;

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
	TEST->ATS(-1,-8);
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
	base = 342;

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

	TEST->AT(-1);
	TEST->AT(-2);
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
	base = 343;

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
	TEST->ATS(-1,-8);
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
	base = 344;

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
	
	TEST->AL(4,3);
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
	base = 345;

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
	
	
	TEST->AL(4,2);
	TEST->AT(-4);
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
	base = 346;

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
	
	
	TEST->AL(5,3);
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
	base = 347;

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
	TEST->AL(4,2);
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
	base = 348;

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
	base = 349;

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

	TEST->AL(5,4);
	TEST->ATS(-1,-8);
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
	base = 350;

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
	TEST->ATS(-1,-8);
	TEST->AT(-1);
	






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
	base = 351;

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

		Theory B(*TEST);

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
	base = 352;

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
	TEST->AT(-8);
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
	base = 353;

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

	TEST->AL(5,4);
	TEST->AT(-8);
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
	base = 354;

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
	TEST->ATS3(-2,-2,-1,-12);
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
	base = 355;

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

		Theory B(*TEST);

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
	base = 356;

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

		Theory B(*TEST);

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
	base = 357;

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

		Theory B(*TEST);

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
	base = 358;

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

		Theory B(*TEST);

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
	base = 359;

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

		Theory B(*TEST);

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
	base = 360;

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
	TEST->AL(5,3);
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
	base = 361;

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
	base = 362;

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
	base = 363;

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
	base = 364;

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
	base = 365;

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
	base = 366;

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

	TEST->AL(3,3);
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
	base = 367;

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

	TEST->AL(3,2);
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
	base = 368;

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
	base = 369;

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

	TEST->AL(3,3);
	TEST->ATS(-1,-8);
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
	base = 370;

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

	TEST->AL(4,3);
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
	base = 371;

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

	TEST->AL(4,4);
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
	base = 372;

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


	TEST->AL(4,2);
	TEST->AT(-4);
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
	base = 373;

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
	TEST->AL(4,2);
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
	base = 374;

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

	TEST->AL(5,4);
	TEST->AT(-8);
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
	base = 375;

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
	TEST->AL(5,3);
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
	base = 376;

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
	TEST->AL(5,4);
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
	base = 377;

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
	base = 378;

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
	base = 379;

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
	base = 380;

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

	TEST->AL(4,4);
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
	base = 381;

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
	TEST->AL(5,4);
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
	base = 382;

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
	base = 383;

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
	base = 384;

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
	base = 385;

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
	base = 386;

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
	base = 387;

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

		Theory B(*TEST);

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
	base = 388;

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
	base = 389;

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
	base = 390;

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

		Theory B(*TEST);

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
	base = 391;

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
	base = 392;

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





