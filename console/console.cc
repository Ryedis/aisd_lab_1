#include <iostream>
#include "polynomial/polynomial.h"
#include <complex>

using namespace pol;
using namespace std;


int main() {
	int list[] = { 2,3,4 };
	Polynomial<int> test(list,3);
	cout << test<<endl;

	cout<<calc_root_1(test)<<endl;

	complex<double> roots[2];
	complex<double>* answ = calc_root_2(roots, test);
	cout << answ[0] << ' ' << answ[1] << endl;
	
	return 0;
}