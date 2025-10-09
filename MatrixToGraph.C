#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>


string MatrixTranslator(Eigen::MatrixXi M)
{
	for (int i =0; i < row().M; i++)
	{
		if (M(i,i) == { -4,-6,-7,-8,-12})
		{
			// finding first Node 
			int first node = -M(i,i);
			

