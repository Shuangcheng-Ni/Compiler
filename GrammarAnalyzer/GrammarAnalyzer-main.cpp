#include <iostream>
#include "GrammarAnalyzer.h"
using namespace std;

int main()
{
	string file_name;
	cin >> file_name;
	GrammarAnalyzer ga(file_name);
	return 0;
}
