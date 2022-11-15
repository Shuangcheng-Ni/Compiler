#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include "GrammarAnalyzer.h"
using namespace std;

bool GrammarAnalyzer::VN_or_VT(const string &s) noexcept
{
	if (s.length() >= 2 && s.front() == '<' && s.back() == '>')
		return is_VN;
	else
		return is_VT;
}

void GrammarAnalyzer::clear() noexcept
{
	VN.clear();
	VT.clear();
	P.clear();
}

bool GrammarAnalyzer::load_grammar_file(const string &file_name) noexcept
{
	ifstream fin(file_name.c_str(), ios::in | ios::binary);
	if (!fin.is_open())
	{
		cerr << "Can\'t open grammar file." << endl;
		return false;
	}
	ostringstream oss(ios::binary);
	oss << fin.rdbuf();
	fin.close();
	istringstream iss(oss.str(), ios::binary);

	this->clear();
	regex re("\\S+");
	smatch result;

	while (!iss.eof())
	{
		string line;
		getline(iss, line);
		if (iss.fail() && line.empty())
			break;

		bool is_left_part = true, is_right_part = false;
		Vpos_t left_part;
		vector<Vattr_t> right_part;

		for (auto cit = cbegin(line); regex_search(cit, cend(line), result, re);)
		{
			string word = result.str();
			if (!is_right_part && word == "->")
				is_right_part = true;
			else if (!is_right_part)
			{
				if (!is_left_part || VN_or_VT(word) == is_VT)
				{
					cerr << "Grammar format error. Stop analyzing." << endl;
					return false;
				}
				left_part = VN.emplace(word.substr(1, word.length() - 2)).first;
				is_left_part = false;
			}
			else if (word == "|")
			{
				P.emplace_back(left_part, right_part);
				right_part.clear();
			}
			else
			{
				if (VN_or_VT(word) == is_VN)
					right_part.emplace_back(VN.emplace(word.substr(1, word.length() - 2)).first, is_VN);
				else
					right_part.emplace_back(VT.emplace(word).first, is_VT);
			}
			cit += result.position() + word.length();
		}

		P.emplace_back(left_part, right_part);
	}

	/*cout << "VN: ";
	for (auto &s : VN)
		cout << s << ' ';
	cout << endl;

	cout << "VT: ";
	for (auto &s : VT)
		cout << s << ' ';
	cout << endl;

	cout << "P: ";
	for (auto &[i, j] : P)
	{
		cout << *i << " ->";
		for (auto &[m, n] : j)
			cout << ' ' << *m << ',' << n;
		cout << endl;
	}*/
	return true;
}
