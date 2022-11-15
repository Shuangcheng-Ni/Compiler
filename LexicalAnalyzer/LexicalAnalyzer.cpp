#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include "LexicalAnalyzer.h"
using namespace std;

void LexicalAnalyzer::preprocess() noexcept
{
	/* É¾³ý×¢ÊÍ */
	regex re;
	re.assign("//.*");
	in_str = regex_replace(in_str, re, " ");
	re.assign("/\\*(.|\\r|\\n)*?\\*/");
	in_str = regex_replace(in_str, re, " ");

	/* Ñ¹Ëõ¿Õ°××Ö·û */
	re.assign("\\s+");
	in_str = regex_replace(in_str, re, " ");
}

void LexicalAnalyzer::analyze() noexcept
{
	size_t pos = 0;
SCAN:
	while (pos < in_str.length())
	{
		if (in_str[pos] == ' ')
		{
			++pos;
			continue;
		}

		const vector<string> *const vsp[]{ &keywords,&operators,&delimiters,&separators };
		for (int i = 0; i < ssize(vsp); i++)
		{
			for (auto &s : *vsp[i])
			{
				if (!in_str.compare(pos, s.length(), s))
				{
					if (i == SymbolTypes::Keyword)
					{
						size_t end_pos = pos + s.length();
						if (end_pos < in_str.length() && (isalnum(in_str[end_pos]) || in_str[end_pos] == '_'))
							continue;
					}
					symbol_table.emplace_back(s, SymbolTypes::Keyword + i);
					pos += s.length();
					goto SCAN;
				}
			}
		}

		for (int i = 0; i < brackets.length(); i++)
		{
			if (in_str[pos] == brackets[i])
			{
				symbol_table.emplace_back(string(1, brackets[i]), SymbolTypes::Left_bracket + i);
				++pos;
				goto SCAN;
			}
		}

		const string *const sp[]{ &float_pattern,&int_pattern,&identifier_pattern };
		for (int i = 0; i < ssize(sp); i++)
		{
			regex re(*sp[i]);
			smatch result;
			if (regex_search(cbegin(in_str) + pos, cend(in_str), result, re) && result.position() == 0)
			{
				symbol_table.emplace_back(result.str(), SymbolTypes::Float_literal + i);
				pos += result.length();
				goto SCAN;
			}
		}

		cerr << "Lexical analyzing error. Stop analyzing." << endl;
		system("pause");
		exit(-1);
	}
}

LexicalAnalyzer::LexicalAnalyzer(const string &file_name) noexcept
{
	ifstream fin(file_name.c_str(), ios::in | ios::binary);
	if (!fin.is_open())
	{
		cerr << "Can\'t open source file!" << endl;
		system("pause");
		exit(-1);
	}
	ostringstream oss(ios::binary);
	oss << fin.rdbuf();
	fin.close();
	in_str = oss.str();

	preprocess();
	analyze();
}

void LexicalAnalyzer::display() const noexcept
{
	for (auto &[str, type_id] : symbol_table)
	{
		cout << "symbol: " << str << endl;
		cout << "type  : " << symbol_types[type_id] << endl;
	}
}

void LexicalAnalyzer::to_input_string() const noexcept
{
	for (auto &symbol_info : symbol_table)
		cout << symbol_types[symbol_info.second] << ' ';
}

void LexicalAnalyzer::to_excel(const string &excel_name) const noexcept
{
	ofstream fout(excel_name.c_str(), ios::out);
	if (!fout.is_open())
	{
		cerr << "Can\'t open output file!" << endl;
		system("pause");
		exit(-1);
	}
	fout << "symbol\ttype" << endl;
	for (auto &[str, type_id] : symbol_table)
		fout << str << '\t' << symbol_types[type_id] << endl;
}
