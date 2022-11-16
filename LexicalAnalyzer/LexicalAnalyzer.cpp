#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include "LexicalAnalyzer.h"
using namespace std;

/***************************************************************************
  函数名称：LexicalAnalyzer::preprocess
  功    能：预处理
  输入参数：
  返 回 值：
  说    明：删除注释、压缩空白字符
***************************************************************************/
void LexicalAnalyzer::preprocess() noexcept
{
	/* 删除注释 */
	regex re;
	re.assign("//.*");
	in_str = regex_replace(in_str, re, " ");
	re.assign("/\\*(.|\\r|\\n)*?\\*/");
	in_str = regex_replace(in_str, re, " ");

	/* 压缩空白字符 */
	re.assign("\\s+");
	in_str = regex_replace(in_str, re, " ");
}

/***************************************************************************
  函数名称：LexicalAnalyzer::analyze
  功    能：词法分析
  输入参数：
  返 回 值：
  说    明：判断符号类型，存入符号表
  原    理：每次向前扫描若干个字符，与可能的符号或模式串进行匹配，即DFA
***************************************************************************/
void LexicalAnalyzer::analyze() noexcept
{
	size_t pos = 0;
SCAN:
	while (pos < in_str.length())
	{
		// 忽略空格
		if (in_str[pos] == ' ')
		{
			++pos;
			continue;
		}

		// 依次匹配可能的关键字、运算符、界符、分隔符，匹配到则继续匹配后续字符
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
							continue; // 如果匹配到关键字，需要向后展望1个字符，判断其是否实际为标识符
					}
					symbol_table.emplace_back(s, SymbolTypes::Keyword + i);
					pos += s.length();
					goto SCAN;
				}
			}
		}

		// 依次匹配可能的(、)、{、}，匹配到则继续匹配后续字符
		for (int i = 0; i < brackets.length(); i++)
		{
			if (in_str[pos] == brackets[i])
			{
				symbol_table.emplace_back(string(1, brackets[i]), SymbolTypes::Left_bracket + i);
				++pos;
				goto SCAN;
			}
		}

		// 依次匹配浮点、整型字面量、标识符的正则表达式(模式串)，匹配不到则报错
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

/***************************************************************************
  函数名称：LexicalAnalyzer::LexicalAnalyzer
  功    能：构造函数
  输入参数：const string &file_name : 源文件名
  返 回 值：
  说    明：调用预处理和词法分析函数
***************************************************************************/
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

/***************************************************************************
  函数名称：LexicalAnalyzer::display
  功    能：将符号表输出到控制台
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void LexicalAnalyzer::display() const noexcept
{
	for (auto &[str, type_id] : symbol_table)
	{
		cout << "symbol: " << str << endl;
		cout << "type  : " << symbol_types[type_id] << endl;
	}
}

/***************************************************************************
  函数名称：LexicalAnalyzer::to_input_string
  功    能：根据符号表，将源文件转化为输入串，供语法分析器使用
  输入参数：const string &input_string_file_name : 存输入串的文件名
  返 回 值：
  说    明：
***************************************************************************/
void LexicalAnalyzer::to_input_string(const string &input_string_file_name) const noexcept
{
	ofstream fout(input_string_file_name.c_str(), ios::out);
	if (!fout.is_open())
	{
		cerr << "Can\'t open output file!" << endl;
		system("pause");
		exit(-1);
	}
	for (auto &symbol_info : symbol_table)
		fout << (symbol_info.second == SymbolTypes::Keyword ? symbol_info.first : symbol_types[symbol_info.second]) << ' ';
	fout.close();
}

/***************************************************************************
  函数名称：LexicalAnalyzer::to_excel
  功    能：将符号表输出到excel文件
  输入参数：const string &input_string_file_name : excel文件名
  返 回 值：
  说    明：
***************************************************************************/
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
	fout.close();
}
