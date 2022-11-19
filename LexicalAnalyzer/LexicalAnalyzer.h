#pragma once

#include <string>
#include <vector>

namespace std {
	class LexicalAnalyzer { // �ʷ�������
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
		}; // �ؼ���

		inline static const vector<string> operators{
			"++","--",
			"<<=",">>=","<<",">>",
			"<=","<",">=",">","==","!=",
			"&&","||","!",
			"+=","-=","*=","/=","%=","&=","|=","=",
			"+","-","*","/","%","&","|","~",
			"?",":"
		}; // �����

		inline static const vector<string> delimiters{ ";" }; // ���

		inline static const vector<string> separators{ "," }; // �ָ���

		inline static const string brackets = "(){}"; // ����

		// ���㡢������������������ʽ(ģʽ��)
		inline static const string float_pattern = "(\\d+(\\.\\d*)?|\\.\\d+)e[+-]?\\d+[FfL]?|(\\d+\\.\\d*|\\.\\d+)[FfL]?";
		inline static const string int_pattern = "\\d+[Uu]?[Ll]{0,2}";

		// ��ʶ����������ʽ(ģʽ��)
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
		}; // ����������

		string in_str; // ��Դ�ļ���������ַ���
		vector<pair<string, int>> symbol_table; // ���ű�(����-��������)

		void preprocess() noexcept; // Ԥ����
		void analyze() noexcept; // �ʷ�����

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
		}; // �������͵�ö��

		LexicalAnalyzer(const string &file_name) noexcept; // ���캯��
		void display() const noexcept; // �����ű����������̨
		// ���ݷ��ű���Դ�ļ�ת��Ϊ���봮�����﷨������ʹ��
		void to_input_string(const string &input_string_file_name = "input_string.txt") const noexcept;
		void to_excel(const string &excel_name = "result.xls") const noexcept; // �����ű������excel�ļ�
	};
}
