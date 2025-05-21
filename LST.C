#include "Theory.h"
#include <iostream>

int main()
{
    Theory th;

    
    for(int i : {-2,-1,-4,-1,-4,-1,-4,-1,-4,-1,-4,-1,-4,-1,-4,-1,-2})
        th.AddTensorMultiplet(i);

    
    for(int i=1;i<17;++i) th.intersect(i,i+1);

    //th.intersect(2,16);
    //th.intersect(16,2);
    std::cout << "Intersection form:\n" << th << "\n\n";
    std::cout << "Determinant : " << th.GetDeterminant() << "\nEigenvalues:\n";
    for(double v : th.GetEigenvalues()) std::cout << v << '\n';


    th.Initialize();
    std::cout << "Intersection form for debugging\n" << th.GetIntersectionForm() <<std::endl;

    for(int i : {-4,-1,-4,-1,-4,-1,-4,-1,-4,-1})
        th.AddTensorMultiplet(i);

    
    for(int i=1;i<9;++i) th.intersect(i,i+1);

    th.intersect(3,10);

    std::cout << "Intersection form:\n" << th << "\n\n";
    std::cout << "Determinant : " << th.GetDeterminant() << "\nEigenvalues:\n";
    for(double v : th.GetEigenvalues()) std::cout << v << '\n';
    std::cout << "CHECKING METHOD\n"<< th.CheckUnimodularity() << std::endl;
    std::cout << "Signature\n" << std::endl;
    for(int i : th.GetSignature()) std::cout << i << '\n';

    std::cout<<"AFTER BLOWDOWN A CURVE\n"<<std::endl;
    th.Blowdown(2);
    std::cout << th.GetIntersectionForm() << std::endl;
}
