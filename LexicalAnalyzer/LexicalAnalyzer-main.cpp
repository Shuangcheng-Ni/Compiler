#include <iostream>
#include "LexicalAnalyzer.h"
using namespace std;

int main()
{
	string file_name;
	getline(cin, file_name);
	LexicalAnalyzer la(file_name);
	la.display();
	la.to_input_string();
	la.to_excel();
	return 0;
}
