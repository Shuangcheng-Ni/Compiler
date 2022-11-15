#include <fstream>
#include <iostream>
#include <sstream>
#include "GrammarAnalyzer.h"
using namespace std;

bool GrammarAnalyzer::load_grammar_file(const string &file_name) noexcept
{
	ifstream fin(file_name.c_str(), ios::in | ios::binary);
	if (!fin.is_open())
	{
		cerr << "Can\'t open grammar file." << endl;
		return false;
	}
	stringstream ss;
	ss << fin.rdbuf();
	
	while (!ss.eof())
	{
		string line;
		getline(ss, line);
		if (ss.fail() && line.empty())
			break;

	}
	return true;
}
