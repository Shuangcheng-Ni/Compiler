#pragma once

#include <string>
#include <vector>

namespace std {
	class LexicalAnalyzer { // 词法分析器
	protected:
		inline static const vector<string> keywords{
			"int","long long","long","short","char","bool",
			"float","long double","double",
			"void",
			"const","extern","static","auto","register",
			"if","else if","else",
			"switch","case","default",
			"for","while","do",
			"break","continue",
			"return"
		}; // 关键字

		inline static const vector<string> operators{
			"++","--",
			"<<=",">>=","<<",">>",
			"<=","<",">=",">","==","!=",
			"&&","||","!",
			"+=","-=","*=","/=","%=","&=","|=","=",
			"+","-","*","/","%","&","|","~",
			"?",":"
		}; // 运算符

		inline static const vector<string> delimiters{ ";" }; // 界符

		inline static const vector<string> separators{ "," }; // 分隔符

		inline static const string brackets = "(){}"; // 括号

		// 浮点、整型字面量的正则表达式(模式串)
		inline static const string float_pattern = "(\\d+(\\.\\d*)?|\\.\\d+)e[+-]?\\d+[FfL]?|(\\d+\\.\\d*|\\.\\d+)[FfL]?";
		inline static const string int_pattern = "\\d+[Uu]?[Ll]{0,2}";

		// 标识符的正则表达式(模式串)
		inline static const string identifier_pattern = "[A-Za-z_]\\w*";

		inline static const vector<string> symbol_types{
			"keyword",
			"operator",
			"delimiter",
			"separator",
			"left_bracket",
			"right_bracket",
			"left_brace",
			"right_brace",
			"float_literal",
			"int_literal",
			"identifier"
		}; // 符号类型名

		string in_str; // 将源文件整体读入字符串
		vector<pair<string, int>> symbol_table; // 符号表(符号-符号类型)

		void preprocess() noexcept; // 预处理
		void analyze() noexcept; // 词法分析

	public:
		enum SymbolTypes {
			Keyword,
			Operator,
			Delimiter,
			Separator,
			Left_bracket,
			Right_bracket,
			Left_brace,
			Right_brace,
			Float_literal,
			Int_literal,
			Identifier
		}; // 符号类型的枚举

		LexicalAnalyzer(const string &file_name) noexcept; // 构造函数
		void display() const noexcept; // 将符号表输出到控制台
		// 根据符号表，将源文件转化为输入串，供语法分析器使用
		void to_input_string(const string &input_string_file_name = "input_string.txt") const noexcept;
		void to_excel(const string &excel_name = "result.xls") const noexcept; // 将符号表输出到excel文件
	};
}
