#pragma once
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <exception>
#include <stdexcept>
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
public:
	class Iter {
	private:
		TreeElem* elem = nullptr;
	public:
		Iter(TreeElem* elem);
		Iter goToParent();
		Iter goToChild(uint64_t index);
		bool isEmpty();
		TreeElem* operator*();
	};
private:
	TreeElem* root = nullptr;
	uint16_t word_count = 0;
public:
	PrefixTree();
	~PrefixTree();
	void Run(std::function<void(Iter elem)>func);
	void Run(Iter start,std::function<void(Iter elem)>func);
	void rRun(std::function<void(Iter elem)>func);
	void rRun(Iter start, std::function<void(Iter elem)>func);
	void Add(std::wstring str);
	bool Delete(std::wstring str);
	bool Search(const std::wstring& str);
	Iter getRoot();
};