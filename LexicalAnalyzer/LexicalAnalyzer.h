#pragma once

#include <string>
#include <vector>

namespace std {
	class LexicalAnalyzer {
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
		};

		inline static const vector<string> operators{
			"++","--",
			"<<=",">>=","<<",">>",
			"<=","<",">=",">","==","!=",
			"&&","||","!",
			"+=","-=","*=","/=","%=","&=","|=","=",
			"+","-","*","/","%","&","|","~",
			"?",":"
		};

		inline static const vector<string> delimiters{ ";" };

		inline static const vector<string> separators{ "," };

		inline static const string brackets = "(){}";

		inline static const string float_pattern = "(\\d+(\\.\\d*)?|\\.\\d+)e[+-]?\\d+|(\\d+\\.\\d*|\\.\\d+)[FfL]?";
		inline static const string int_pattern = "\\d+[Uu]?[Ll]{0,2}";

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
		};

		string in_str;
		vector<pair<string, int>> symbol_table;

		void preprocess() noexcept;
		void analyze() noexcept;

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
		};

		LexicalAnalyzer(const string &file_name) noexcept;
		void display() const noexcept;
	};
}
