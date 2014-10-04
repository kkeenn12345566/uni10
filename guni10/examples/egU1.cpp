#include <iostream>
#include <uni10.hpp>

int main(){
	// Construct spin 1 Heisenberg model
	// Raw element
	double heisenberg_s1[] = \
		{1, 0, 0, 0, 0, 0, 0, 0, 0,\
		 0, 0, 0, 1, 0, 0, 0, 0, 0,\
		 0, 0,-1, 0, 1, 0, 0, 0, 0,\
		 0, 1, 0, 0, 0, 0, 0, 0, 0,\
		 0, 0, 1, 0, 0, 0, 1, 0, 0,\
		 0, 0, 0, 0, 0, 0, 0, 1, 0,\
		 0, 0, 0, 0, 1, 0,-1, 0, 0,\
		 0, 0, 0, 0, 0, 1, 0, 0, 0,\
		 0, 0, 0, 0, 0, 0, 0, 0, 1\
		};
	// Create in-coming and out-going bonds, without any symmetry.
	uni10::Bond bd_in(uni10::BD_IN, 3);
	uni10::Bond bd_out(uni10::BD_OUT, 3);
	std::vector<uni10::Bond> bonds;
	bonds.push_back(bd_in);
	bonds.push_back(bd_in);
	bonds.push_back(bd_out);
	bonds.push_back(bd_out);
	// Create tensor from the bonds and name it "H".
	uni10::UniTensor H(bonds, "H");
	H.addRawElem(heisenberg_s1);
	std::cout<< H;


	// Since it has U1 symmetry(total Sz conserved)
	// add U1 quantum number to the states of bonds.
	uni10::Qnum q0(0);
	uni10::Qnum q1(1);
	uni10::Qnum q_1(-1);
  std::vector<uni10::Qnum> qnums;
	qnums.push_back(q1);
	qnums.push_back(q0);
	qnums.push_back(q_1);

	// Create in-coming and out-going bonds
	bd_in.assign(uni10::BD_IN, qnums);
	bd_out.assign(uni10::BD_OUT, qnums);
	bonds.clear();
	bonds.push_back(bd_in);
	bonds.push_back(bd_in);
	bonds.push_back(bd_out);
	bonds.push_back(bd_out);

	// Create tensor from the bonds and name it "H_U1".
	uni10::UniTensor H_U1(bonds, "H_U1");
	// Add raw elements to tensor
	H_U1.addRawElem(heisenberg_s1);
	std::cout<< H_U1;

	// Check the quantum number of the blocks
	std::cout<<"The number of the blocks = "<< H_U1.blockNum()<<std::endl;
	std::vector<uni10::Qnum> block_qnums = H_U1.blockQnum();
	for(int q = 0; q < block_qnums.size(); q++)
		std::cout<< block_qnums[q]<<", ";
	std::cout<<std::endl<<std::endl;

	// Write out tensor
	H_U1.save("egU1_H_U1");

	return 0;
}
