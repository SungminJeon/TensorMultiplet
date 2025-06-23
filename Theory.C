#include "Theory.h"
#include <iostream>
#include <iomanip>
#include <Eigen/Dense>


std::ostream& operator<<(std::ostream& os, const Theory& th)
{
    /* 원하는 출력 형식을 자유롭게 작성 */
    return os << th.GetIntersectionForm();
}
Theory::Theory() {

	Initialize();
}



void Theory::Initialize() {
	intersection_form.resize(0,0);
	T = 0;
}


Eigen::MatrixXi Theory::GetIntersectionForm() const {

	return intersection_form;
}

double Theory::GetDeterminant() {

	return intersection_form.cast<double>().determinant();
}
int Theory::GetT() 
{
	return T;
}

Eigen::VectorXd Theory::GetEigenvalues2() {

	Eigen::MatrixXd Ad = intersection_form.cast<double>();
	Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> es(Ad);
	Eigen::VectorXd vec = es.eigenvalues();	
	Eigen::MatrixXi A   = intersection_form;	
	int nullity = 0;
	

	// DETERMINE THE NULLITY OF THE INTERSECTION FORM (i.e. number of null directions)
	for (int i = 0; i < T; i++) 
	{

		for (int j = i; j < T; j++ )
		{ 
			if ( j == i && A(j,i) !=0 ) {break;}
			else if ( A(j,i) == 0 ) 
			{ continue; }
			else if ( A(j,i) > 0 || A(j,i) < 0 )
			{ A.row(j).swap(A.row(i)); break;}

		
		}
		
		std::cout << A << std::endl;
		//subtract all the other leading non-zeros
		for (int k = i+1; k < T; k++ )
		{
			if ( A(k,i) > 0 || A(k,i) < 0 )
			{
				A.row(k) = A.row(k)*A(i,i)-A(k,i)*A.row(i);
				std::cout << A << std::endl;

			}
		}
	}

	std::cout << A<< std::endl;
	

	for (int i = 0; i < T; i++)
	{
		if ( A(i,i) == 0 )
		{
			nullity++;
		}
	}
//	std::cout << A << std::endl;
//	std::cout << nullity << std::endl;

	// at the moment, we get the number of null directions.
	// now, what we wanna do is just sorting the eigenvalues in increasing order 
	
	for (int i = 0; i < T; i++)
	{	
		for (int j = i+1; j < T; j++)
		{
			if ( abs(vec(j)) < abs((vec(i))) ) 
			{	
				std::swap(vec(i),vec(j));
				
			}
		}	
	}
	
	// replace the small errors by zeros
	
	for (int k = 0; k < nullity; k++)
	{
		vec(k) = 0;
	}

	return vec;
}
Eigen::VectorXd Theory::GetEigenvalues() {
    // ❶ 안전 체크
    if(intersection_form.rows() != intersection_form.cols()) 
        throw std::runtime_error("intersection_form is not square.");

    const int n = intersection_form.rows();

    // ❷ 수치 고윳값
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> es(intersection_form.cast<double>());
    if(es.info() != Eigen::Success) 
        throw std::runtime_error("Eigen decomposition failed.");

    Eigen::VectorXd vec = es.eigenvalues();

    // ❸ 정수 rank -> nullity
    Eigen::FullPivLU<Eigen::MatrixXd> lu(intersection_form.cast<double>());
    int nullity = n - lu.rank();

    // ❹ 정렬 & 0 덮어쓰기
    std::sort(vec.data(), vec.data()+n, 
              [](double a, double b){ return std::abs(a) < std::abs(b); });
    vec.head(nullity).setZero();

    return vec;
}
int Theory::IsUnimodular()
{	
	double det = 1;
	Eigen::VectorXd V = this->GetEigenvalues();

	for ( int i = 0; i < T; i++)
	{	
		if ( V(i) > 0 || V(i) < 0 )
		{
			det *= V(i);
		}
	}

          

	return std::llround(det); 
}
int Theory::GetExactDet()
{		
	
	return std::llround(this->GetDeterminant());


}

Eigen::VectorXi Theory::GetSignature()
{
	Eigen::VectorXd v = this->GetEigenvalues();
	for (int i = 0; i < T; i++)
	{	
		if ( v(i) > 0 ) { v(i) = 1; }
		if ( v(i) < 0 ) { v(i) = -1;}

	}

	for (int j = 0; j < T; j++)
	{
	
		if ( v(j) > 0 || v(j) < 0 )
		{
			for (int k = j+1; k < T; k++)
			{
				if (v(k) < v(j))
				{
					std::swap(v(k), v(j));
				}
			}
		}
	}

	return v.cast<int>();
}
			

void Theory::AddTensorMultiplet(int charge)
{	
	T++;
	intersection_form.conservativeResize(T,T);
	
	for (int i = 0; i < T; i++)
	{
		intersection_form(T-1,i) = 0;
		intersection_form(i,T-1) = 0;
	}
	intersection_form(T-1,T-1) = charge;

}
void Theory::AddT(int charge)
{	
	T++;
	intersection_form.conservativeResize(T,T);
	
	for (int i = 0; i < T; i++)
	{
		intersection_form(T-1,i) = 0;
		intersection_form(i,T-1) = 0;
	}
	intersection_form(T-1,T-1) = charge;

}


void Theory::intersect(int n, int m, int k)
{
	intersection_form(n-1, m-1) = k;
	intersection_form(m-1, n-1) = k;

}
void Theory::not_intersect(int n, int m)
{
	intersection_form(n-1,m-1) = 0;
	intersection_form(m-1,n-1) = 0;
}
void Theory::DeleteTensorMultiplet()
{
	T--;
	intersection_form.conservativeResize(T,T);
}
void Theory::Blowdown(int n)
{
	std::vector<int> v;

	if(intersection_form(n-1,n-1) != -1)
	{
		std::cout << "THIS CURVE CANNOT BE BLOWN DOWN\n" <<std::endl;
		
	}
	else
	{


		std::vector<int> vec;
		for ( int a = 0; a < T ;a++ )
		{
			if ( intersection_form(a,n-1) == 1 )
			{
				vec.push_back(a);
			}
		}	
		if ( vec.size() == 2 )
		{
			if ( !(intersection_form(vec[0],vec[0]) >= 0 || intersection_form(vec[1],vec[1]) >= 0 ) )
			{
				T--;
				Eigen::MatrixXi B = Eigen::MatrixXi::Zero(T,T);
				for (int i=0; i<T; i++)
				{
					for (int j=0; j<T; j++)
					{
						if ( i < n-1 && j < n-1 )
						{
							B(i,j) = intersection_form(i,j);
						}
						if ( i >= n-1 && j < n-1 )
						{
							B(i,j) = intersection_form(i+1,j);
						}
						if ( i < n-1 && j >= n-1)
						{	
							B(i,j) = intersection_form(i,j+1);
						}
						else if ( i >= n-1 && j >= n-1)
						{
							B(i,j) = intersection_form(i+1,j+1);
						}
					}
				}


				for (int k=0; k < T+1; k++)
				{


					if( intersection_form(n-1,k) == 1 )
					{	
						if ( k < n-1 )
						{
							v.push_back(k);
							B(k,k) += 1;					

						}
						if ( k > n-1 )
						{
							v.push_back(k-1);
							B(k-1,k-1) +=1;
						}
					}
				}


				if (v.size() > 1)
				{
					B(v[0],v[1]) = 1;
					B(v[1],v[0]) = 1;
				}	

				intersection_form = B;

			}
		}
		else if ( vec.size() == 1 )
		{
			if ( !(intersection_form(vec[0],vec[0]) >= 0) )
			{
				T--;
				Eigen::MatrixXi B = Eigen::MatrixXi::Zero(T,T);
				for (int i=0; i<T; i++)
				{
					for (int j=0; j<T; j++)
					{
						if ( i < n-1 && j < n-1 )
						{
							B(i,j) = intersection_form(i,j);
						}
						if ( i >= n-1 && j < n-1 )
						{
							B(i,j) = intersection_form(i+1,j);
						}
						if ( i < n-1 && j >= n-1)
						{	
							B(i,j) = intersection_form(i,j+1);
						}
						else if ( i >= n-1 && j >= n-1)
						{
							B(i,j) = intersection_form(i+1,j+1);
						}
					}
				}


				for (int k=0; k < T+1; k++)
				{


					if( intersection_form(n-1,k) == 1 )
					{	
						if ( k < n-1 )
						{
							v.push_back(k);
							B(k,k) += 1;					

						}
						if ( k > n-1 )
						{
							v.push_back(k-1);
							B(k-1,k-1) +=1;
						}
					}
				}


				if (v.size() > 1)
				{
					B(v[0],v[1]) = 1;
					B(v[1],v[0]) = 1;
				}	

				intersection_form = B;

			}
		}
		else if (vec.size() == 0)
		{
			std::cout << "No intersecting curves" << std::endl;
		}
		else if (vec.size() > 2)
		{
			std::cout << "Inconsistent base" << std::endl;
		}
				


	}
}

bool Theory::Blowdown2(int n)
{
	std::vector<int> v;
	bool b = 1;

	if(intersection_form(n-1,n-1) != -1)
	{
		std::cout << "THIS CURVE CANNOT BE BLOWN DOWN\n" <<std::endl;
		
	}
	else
	{


		std::vector<int> vec;
		for ( int a = 0; a < T ;a++ )
		{
			if ( intersection_form(a,n-1) == 1 )
			{
				vec.push_back(a);
			}
		}	
		if ( vec.size() >= 2 )
		{
			for (int a =0; a < vec.size(); a++)
			{
				if ( intersection_form(vec[a],vec[a]) >= 0)
				{
					b = 0;
					break;
				}
			}


			if ( b == 1 )
			{
				T--;
				Eigen::MatrixXi B = Eigen::MatrixXi::Zero(T,T);
				for (int i=0; i<T; i++)
				{
					for (int j=0; j<T; j++)
					{
						if ( i < n-1 && j < n-1 )
						{
							B(i,j) = intersection_form(i,j);
						}
						if ( i >= n-1 && j < n-1 )
						{
							B(i,j) = intersection_form(i+1,j);
						}
						if ( i < n-1 && j >= n-1)
						{	
							B(i,j) = intersection_form(i,j+1);
						}
						else if ( i >= n-1 && j >= n-1)
						{
							B(i,j) = intersection_form(i+1,j+1);
						}
					}
				}


				for (int k=0; k < T+1; k++)
				{


					if( intersection_form(n-1,k) == 1 )
					{	
						if ( k < n-1 )
						{
							v.push_back(k);
							B(k,k) += 1;					

						}
						if ( k > n-1 )
						{
							v.push_back(k-1);
							B(k-1,k-1) +=1;
						}
					}
				}


				for (int a2 = 0; a2 < v.size() ;a2++)
				{
					for (int a3 = 0; a3 < a2; a3++)
					{
						B(v[a2],v[a3])++;
						B(v[a3],v[a2])++;
					}
				}	

				intersection_form = B;

			}
		}
		else if ( vec.size() == 1)
		{
			if ( !(intersection_form(vec[0],vec[0]) >= 0) )
			{
				T--;
				Eigen::MatrixXi B = Eigen::MatrixXi::Zero(T,T);
				for (int i=0; i<T; i++)
				{
					for (int j=0; j<T; j++)
					{
						if ( i < n-1 && j < n-1 )
						{
							B(i,j) = intersection_form(i,j);
						}
						if ( i >= n-1 && j < n-1 )
						{
							B(i,j) = intersection_form(i+1,j);
						}
						if ( i < n-1 && j >= n-1)
						{	
							B(i,j) = intersection_form(i,j+1);
						}
						else if ( i >= n-1 && j >= n-1)
						{
							B(i,j) = intersection_form(i+1,j+1);
						}
					}
				}


				for (int k=0; k < T+1; k++)
				{


					if( intersection_form(n-1,k) == 1 )
					{	
						if ( k < n-1 )
						{
							v.push_back(k);
							B(k,k) += 1;					

						}
						if ( k > n-1 )
						{
							v.push_back(k-1);
							B(k-1,k-1) +=1;
						}
					}
				}


				if (v.size() > 1)
				{
					B(v[0],v[1])++;
					B(v[1],v[0])++;
				}	

				intersection_form = B;

			}
		}
		else if (vec.size() == 0)
		{
			std::cout << "No intersecting curves" << std::endl;
		}
		else if (b == 0)
		{
			std::cout << "Inconsistent base" << std::endl;
		}
				

		return b;

	}
}	
bool Theory::Blowdown3(int n)
{
	std::vector<int> v;
	bool b = 1;

	if(intersection_form(n-1,n-1) != -1)
	{
		std::cout << "THIS CURVE CANNOT BE BLOWN DOWN\n" <<std::endl;
		
	}
	else
	{


		std::vector<int> vec;
		for ( int a = 0; a < T ;a++ )
		{
			if ( intersection_form(a,n-1) == 1 )
			{
				vec.push_back(a);
			}
		}	
		if ( vec.size() >= 2 )
		{
			
			

			if ( b == 1 )
			{
				T--;
				Eigen::MatrixXi B = Eigen::MatrixXi::Zero(T,T);
				for (int i=0; i<T; i++)
				{
					for (int j=0; j<T; j++)
					{
						if ( i < n-1 && j < n-1 )
						{
							B(i,j) = intersection_form(i,j);
						}
						if ( i >= n-1 && j < n-1 )
						{
							B(i,j) = intersection_form(i+1,j);
						}
						if ( i < n-1 && j >= n-1)
						{	
							B(i,j) = intersection_form(i,j+1);
						}
						else if ( i >= n-1 && j >= n-1)
						{
							B(i,j) = intersection_form(i+1,j+1);
						}
					}
				}


				for (int k=0; k < T+1; k++)
				{


					if( intersection_form(n-1,k) == 1 )
					{	
						if ( k < n-1 )
						{
							v.push_back(k);
							B(k,k) += 1;					

						}
						if ( k > n-1 )
						{
							v.push_back(k-1);
							B(k-1,k-1) +=1;
						}
					}
				}


				for (int a2 = 0; a2 < v.size() ;a2++)
				{
					for (int a3 = 0; a3 < a2; a3++)
					{
						B(v[a2],v[a3])++;
						B(v[a3],v[a2])++;
					}
				}	

				intersection_form = B;

			}
		}
		else if ( vec.size() == 1)
		{
			if ( !(intersection_form(vec[0],vec[0]) >= 0) )
			{
				T--;
				Eigen::MatrixXi B = Eigen::MatrixXi::Zero(T,T);
				for (int i=0; i<T; i++)
				{
					for (int j=0; j<T; j++)
					{
						if ( i < n-1 && j < n-1 )
						{
							B(i,j) = intersection_form(i,j);
						}
						if ( i >= n-1 && j < n-1 )
						{
							B(i,j) = intersection_form(i+1,j);
						}
						if ( i < n-1 && j >= n-1)
						{	
							B(i,j) = intersection_form(i,j+1);
						}
						else if ( i >= n-1 && j >= n-1)
						{
							B(i,j) = intersection_form(i+1,j+1);
						}
					}
				}


				for (int k=0; k < T+1; k++)
				{


					if( intersection_form(n-1,k) == 1 )
					{	
						if ( k < n-1 )
						{
							v.push_back(k);
							B(k,k) += 1;					

						}
						if ( k > n-1 )
						{
							v.push_back(k-1);
							B(k-1,k-1) +=1;
						}
					}
				}


				if (v.size() > 1)
				{
					B(v[0],v[1])++;
					B(v[1],v[0])++;
				}	

				intersection_form = B;

			}
		}
		else if (vec.size() == 0)
		{
			std::cout << "No intersecting curves" << std::endl;
		}
		else if (b == 0)
		{
			std::cout << "Inconsistent base" << std::endl;
		}
				

		return b;

	}
}	

void Theory::AddLink(int n, int m, bool b)
{

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
	if(b==0)
	{
		if (n==1 && m==1)
		{
			AddTensorMultiplet(-1);
		}
		if (n==2 && m==2)
		{
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-1);
		}
		if (n==3 && m==3)
		{
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-1);
		}
		if (n==4 && m==4)
		{
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-5);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-1);
		}
		if (n==5 && m==5)
		{
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-5);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-1);
		}
		if (n==3 && m==2)
		{
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-1);
		}
		if (n==2 && m==3)
		{
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-1);
		}
		if (n==4 && m==2)
		{
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-1);
		}
		if (n==2 && m==4)
		{

			AddTensorMultiplet(-1);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-1);
		}
		if (n==3 && m==4)
		{

			AddTensorMultiplet(-1);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-5);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-1);
		}
		if (n==4 && m==3)
		{

			AddTensorMultiplet(-1);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-5);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-1);
		}
		if (n==3 && m==5)
		{

			AddTensorMultiplet(-1);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-5);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-1);
		}
		if (n==5 && m==3)
		{

			AddTensorMultiplet(-1);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-5);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-1);
		}

		if (n==4 && m==5)
		{

			AddTensorMultiplet(-1);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-5);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-1);
		}
		if (n==5 && m==4)
		{

			AddTensorMultiplet(-1);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-5);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-2);
			AddTensorMultiplet(-1);
		}

	}
	else if ( b==1)
	{
		if( n==3 && m==3)
		{

			AddTensorMultiplet(-1);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-5);
			AddTensorMultiplet(-1);
			AddTensorMultiplet(-3);
			AddTensorMultiplet(-1);
		}
	}
	else
	{
		std::cout << "\n///////////////    NO SUCH LINK EXISTS  ////////////////\n" <<std::endl;
	}


}

bool Theory::IsSUGRA()
{
	bool c = 0;
	int n = std::llround(std::abs(this->IsUnimodular()));
	int sqrtn = std::llround(std::sqrt((long double)n));
	int timedir = 0;

	bool b = (sqrtn*sqrtn == n && n > 0);

	for (int i = 0; i < (this->GetSignature()).size();i++)
	{
		if ( (this->GetSignature())[i] == 1)
		{
			timedir ++;
		}
	}

	if ( timedir == 1)
	{
		c = 1;
	}
	else if (timedir != 1)
	{
		c = 0;
	}


	return b&&c;
}

void Theory::CompleteBlowdown()
{
	for (int i = 0; i < T; i++)
	{
		if (intersection_form(i,i) == -1)
		{
			this->Blowdown(i+1);
			i = -1;
			std::cout << intersection_form << std::endl;
			std::cout << this->GetSignature() << std::endl;
			if (T < 4)
			{
				break;
			}
		}
	}
}

void Theory::LSTBlowdown()
{

	bool b;
	bool c;
	std::vector<int> v;
	for( int i = 0; i < T-1; i++)
	{
		if(intersection_form(i,i) == -1 && intersection_form(i,T-1) == 0 )
		{
			
			b = this -> IsSUGRA();
			v.clear();
			for (int j = 0; j < T ; j++)
			{
				if (intersection_form(i,j) == 1)
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
				this -> Blowdown(i+1);
				i = -1;
				//std::cout << " Blowdown " << std::endl;
				//std::cout << intersection_form << std::endl;
			}
			else if ( b == 0 || c == 0)
			{
				//std::cout << "NOT SUGRA ANYMORE" << std::endl;

				break;
			}	
		}
		
	}
}
void Theory::ForcedBlowdown()
{

	bool c;
	std::vector<int> v;
	for( int i = 0; i < T-1; i++)
	{
		if(intersection_form(i,i) == -1)
		{
			v.clear();
			for (int j = 0; j < T ; j++)
			{
				if (intersection_form(i,j) == 1)
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


			
			if (c == 1)
			{
				this -> Blowdown(i+1);
				i = -1;
				//std::cout << " Blowdown " << std::endl;
				//std::cout << intersection_form << std::endl;
				//std::cout << this->GetSignature() << std::endl;
			}
			else if (c == 0)
			{
				//std::cout << "NOT SUGRA ANYMORE" << std::endl;

				break;
			}	
		}
		
	}
}


bool Theory::IsHirzebruch()
{

	bool b;

	this -> LSTBlowdown();
	//std::cout << intersection_form << std::endl;
	for ( int i  = 0; i < T; i++)
	{
	
		if ( this -> GetIntersectionForm()(i,i) == -1 )
		{
			//std::cout << " BLOWDOWN : " << i << std::endl;
			//std::cout << intersection_form <<std::endl;
			b = this->IsSUGRA();

			if (b == 1)
			{
				if ( i >= 1 && i <= T-2 &&(intersection_form(i+1,i+1) < 0 && intersection_form(i-1,i-1) < 0))
				{
					this -> Blowdown(i+1);
					i = -1;
				}
				else if ( i == 0 && intersection_form(1,1) < 0)
				{
					this -> Blowdown(i+1);
					i = -1;

				}
				else if ( i == T-1 && intersection_form(i-1,i-1) < 0 )
				{
					this -> Blowdown(i+1);
					i = -1;
				}
	
				
					
			}
			else 
			{
				break;
			}	
		}
	}

	if (this -> GetT() == 2)
	{
		if (intersection_form(0,1) == 1 && ((intersection_form(0,0) == 0 && intersection_form(1,1) < 0) || intersection_form(1,1) ==0 && intersection_form(0,0) < 0))
		{
			b = 1;
		}
		else
		{
			b = 0;
		}


	}
	else
	{
		b = 0;
	}

	return b;
}

int Theory::TimeDirection()
{
	int timedir = 0;

	for (int i = 0; i < (this -> GetSignature()).size(); i++)
	{

		if ((this -> GetSignature())[i] == 1)
		{
			timedir++;
		}
	}

	return timedir;
}

int Theory::NullDirection()
{
	int nulldir = 0;

	for (int i = 0; i <(this->GetSignature()).size(); i++)
	{
		if ((this->GetSignature())[i] == 0)
		{
			nulldir++;
		}
	}
	return nulldir;
}
int Theory::SpaceDirection()
{
	int spacedir = 0;

	for (int i = 0; i <(this->GetSignature()).size(); i++)
	{
		if ((this->GetSignature())[i] == -1)
		{
			spacedir++;
		}
	}
	return spacedir;
}
void Theory::SetElement(int n, int m, int k)
{
	intersection_form(n,m) = k;
}










		


			

	


		
