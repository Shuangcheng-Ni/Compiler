#pragma once

#include <string>
#include <unordered_set>
#include <vector>

namespace std {
	class GrammarAnalyzer {
	protected:
		using Vset_t = unordered_set<string>;
		using Vpos_t = Vset_t::iterator;
		using Vattr_t = pair<Vpos_t, bool>;

		static constexpr bool is_VN = true;
		static constexpr bool is_VT = false;
		static bool VN_or_VT(const string &s) noexcept;

		Vset_t VN;
		Vset_t VT;
		vector<pair<Vpos_t, vector<Vattr_t>>> P;
		void clear() noexcept;

	public:
		GrammarAnalyzer() noexcept = default;
		explicit GrammarAnalyzer(const string &file_name) noexcept { load_grammar_file(file_name); }
		bool load_grammar_file(const string &file_name) noexcept;
	};
}
