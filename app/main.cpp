#include "../code/BPlusTreeDBMS.h"
#include <iostream>
#include <string>

using namespace std;

bool check_required_argc(int argc, int required_len)
{
	if (argc == required_len)
	{
		return true; 
	}
	cout << "Incorrect Operands" << endl; 
	return false; 
}



int main (int argc, const char * argv[])
{
  // no argv[1] given
    cout << "TEST!!!!!!! APP!!!!!!!!!!" << endl;


	

	return 0;
}
