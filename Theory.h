#pragma once
#include <Eigen/Dense>
#include <vector>

class Theory {
	private:
    		//string gauge_alg;				// types of gauge algebra 
								// -> data is needed..?
    		Eigen::MatrixXi  intersection_form;          // intersection form
		int T;
		std::vector<int>  b0_comp;

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
		Eigen::VectorXd GetEigenvalues2();
	   	int IsUnimodular();
		Eigen::VectorXi GetSignature();
		int GetT();
		int TimeDirection();
		int NullDirection();
		int SpaceDirection(); 
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
		bool Blowdown2(int n);			//formal blowdown with only 1 intersection 
		bool Blowdown3(int n);
		bool Blowdown4(int n);			//formal blowdown with bigger than 1 intersection
		void CompleteBlowdown();
		void LSTBlowdown();
		void ForcedBlowdown();
		void AddLink(int n, int m, bool b=0);
		void SetElement(int n, int m, int k);
		void Setb0Q();
		std::vector<int> Getb0Q();
		Eigen::MatrixXi GetIFb0Q();
		
			

	friend std::ostream& operator<<(std::ostream& os, const Theory& th);
};

