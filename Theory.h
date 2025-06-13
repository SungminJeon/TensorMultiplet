#pragma once
#include <Eigen/Dense>
#include <vector>

class Theory {
	private:
    		//string gauge_alg;				// types of gauge algebra 
								// -> data is needed..?
    		Eigen::MatrixXi  intersection_form;          // intersection form
		int T;

	public:
    		Theory();                      
    		~Theory() = default;
		void Initialize();

    		/* -------- queries -------- */
		Eigen::MatrixXi GetIntersectionForm() const;
    		//string getAnomaly()          const { return anomaly; }
   		double GetDeterminant();
	   	int GetExactDet();	
		Eigen::VectorXd	GetEigenvalues();
	   	double IsUnimodular();
		Eigen::VectorXi GetSignature();
		int GetT();
		int TimeDirection();
		bool IsSUGRA();
		bool IsHirzebruch();	

    		/* -------- modifiers -------*/
    		void AddTensorMultiplet(int charge);
		void AddT(int charge);		// anomaly += charge
    		//void AddTensorMultiplet(int charge, int anomalyPart); // anomaly += anomalyPart
    		void intersect(int n, int m, int k=1);
		void not_intersect(int n, int m);
		void DeleteTensorMultiplet();
		void Blowdown(int n);
		void CompleteBlowdown();
		void LSTBlowdown();
		void AddLink(int n, int m, bool b=0);
		
			

	friend std::ostream& operator<<(std::ostream& os, const Theory& th);
};

