#pragma once
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <cmath>
#include <utility>
#include <initializer_list>

class PrefixTree {
public:
	class TreeElem {
	public:
		std::vector<TreeElem*> childs;
		TreeElem* parent = nullptr;
		wchar_t symbol = L'\0';
		uint64_t run_of_child = 0;
		bool finaly = false;
		double weight = 0;
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
private:
	void specRun(Iter start, std::function<void(Iter elem)>func);
public:
	PrefixTree();
	PrefixTree(const std::initializer_list<std::wstring> &init_list);
	~PrefixTree();
	void Run(std::function<void(Iter elem)>func);
	void Run(Iter start,std::function<void(Iter elem)>func);
	void rRun(std::function<void(Iter elem)>func);
	void rRun(Iter start, std::function<void(Iter elem)>func);
	void Add(std::wstring str);
	bool Delete(std::wstring str,bool isLower = true);
	std::vector<std::pair<std::wstring, double>>& Search(const std::wstring& str,bool isLower = true);
	Iter getRoot();
	void Clear();
};