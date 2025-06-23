#include <iostream>
#include "Theory.h"
#include <vector>


int main() {


        Theory th;
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

	th.AddTensorMultiplet(-1); th.intersect(10,th.GetT());


	//std::cout << th.GetIntersectionForm() <<std::endl;

        th.SetElement(0,0,123);

	//th.Blowdown(th.GetT());


        std::cout << " ForcedBLOWDOWNED : " <<std::endl;
        std::cout << th.GetIntersectionForm() << std::endl;

       // th.IsHirzebruch();
       //   std::cout << th.GetIntersectionForm() <<std::endl;

  //      th.LSTBlowdown();

    //    std::cout << " LSTBLOWDOWNED : " <<std::endl;
      //  std::cout << th.GetIntersectionForm() << std::endl;

        //th.IsHirzebruch();
}
