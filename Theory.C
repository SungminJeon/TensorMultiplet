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

Eigen::VectorXd Theory::GetEigenvalues() {

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
		
		//subtract all the other leading non-zeros
		for (int k = i+1; k < T; k++ )
		{
			if ( A(k,i) > 0 || A(k,i) < 0 )
			{
				A.row(k) = A.row(k)*A(i,i)-A(k,i)*A.row(i);

			}
		}
	}

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
double Theory::CheckUnimodularity()
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

	if (intersection_form(n-1,n-1) != -1 )
	{
		std::cout << "THIS CURVE CANNOT BE BLOWN DOWN\n" <<std::endl;
		
	}
	else
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
	int n = std::llround(std::abs(this->GetDeterminant()));
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














		


			

	


		
