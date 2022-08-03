#pragma once
#include <string>
#include <vector>
#include <functional>
class PrefixTree {
public:
	class TreeElem {
	public:
		std::vector<TreeElem*> childs;
		TreeElem* parent = nullptr;
		wchar_t symbol = L'\0';
		uint64_t run_of_child = 0;
		bool finaly = false;
		TreeElem(const wchar_t& symbol,TreeElem * parent = nullptr);
		TreeElem();
	};
	TreeElem* root = nullptr;
private:
	uint16_t word_count = 0;
public:
	PrefixTree();
	~PrefixTree();
	void Run(std::function<void(const TreeElem* elem)>func);
	void rRun(std::function<void(const TreeElem* elem)>func);
	void Add(std::wstring str);
	bool Delete(std::wstring str);
};