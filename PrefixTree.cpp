#include "PrefixTree.h"

PrefixTree::TreeElem::TreeElem(const wchar_t& symbol,TreeElem* parent)
{
	this->symbol = symbol;
	this->parent = parent;
}

PrefixTree::TreeElem::TreeElem()
{

}

PrefixTree::PrefixTree()
{
	root = new TreeElem;
}

PrefixTree::~PrefixTree()
{
	rRun([](Iter el)->void{
		delete *el;
	});
}

void PrefixTree::rRun(std::function<void(Iter elem)> func)
{
	this->rRun(Iter(this->root), [&func](PrefixTree::Iter el)->void {
		func(el);
	});
}

void PrefixTree::rRun(Iter start, std::function<void(Iter elem)> func)
{
	if (start.isEmpty()) throw std::invalid_argument("start element is empty");
	TreeElem* it = *start;
	while ((*start)->run_of_child != (*start)->childs.size()) {
		if (!it->childs.empty() && it->run_of_child < it->childs.size()) {
			it = it->childs[it->run_of_child];
		}
		else {
			TreeElem* temp = it;
			it->run_of_child = 0;
			it = it->parent;
			++it->run_of_child;
			func(PrefixTree::Iter(temp));
		}
	}
	(*start)->run_of_child = 0;
}

void PrefixTree::Add(std::wstring str)
{
	if (str.empty()) return;
	word_count++;
	TreeElem* root = this->root;
	auto el = std::find_if(root->childs.begin(), root->childs.end(), [&str](const TreeElem* elem)->bool {
		if (elem->symbol == str[0]) return true;
		return false;
	});
	if (el == root->childs.end()) {
		TreeElem* it = root;
		for (int i = 0; i < str.length(); ++i) {
			it->childs.push_back(new TreeElem(str[i], it));
			it = it->childs.back();
		}
		it->finaly = true;
	}
	else {
		TreeElem* it = *el;
		for (int i = 1; i < str.length(); ++i) {
			auto el = std::find_if(it->childs.begin(), it->childs.end(), [&str,i](const TreeElem* elem)->bool {
				if (elem->symbol == str[i]) return true;
				return false;
			});
			if (el == it->childs.end()) {
				it->childs.push_back(new TreeElem(str[i], it));
				it = it->childs.back();
			}
			else it = *el;
		}
		it->finaly = true;
	}
}

void PrefixTree::Run(std::function<void(Iter iter)> func)
{
	this->Run(Iter(this->root), [&func](PrefixTree::Iter el)->void {
		func(el);
	});
}

void PrefixTree::Run(Iter start,std::function<void(Iter elem)> func)
{
	if (start.isEmpty()) throw std::invalid_argument("start element is empty");
	TreeElem* it = *start;
	while ((*start)->run_of_child < (*start)->childs.size()) {
		if (!it->childs.empty() && it->run_of_child < it->childs.size()) {
			it = it->childs[it->run_of_child];
			func(PrefixTree::Iter(it));
		}
		else {
			it->run_of_child = 0;
			it = it->parent;
			++it->run_of_child;
		}
	}
	(*start)->run_of_child = 0;
}

bool PrefixTree::Delete(std::wstring str) {
	if (str.empty()) return false;
	TreeElem* it = root;
	for (int i = 0; i < str.length(); ++i) {
		auto el = std::find_if(it->childs.begin(), it->childs.end(), [&str, i](const TreeElem* elem)->bool {
			if (elem->symbol == str[i]) return true;
			return false;
		});
		if (el != it->childs.end()) {
			it = *el;
		}
		else return false;
	}
	if (!it->childs.empty())
		it->finaly = false;
	else {
		TreeElem* oldElem = nullptr;
		do {
			oldElem = it;
			it = it->parent;
			auto el = std::find(it->childs.begin(), it->childs.end(), oldElem);
			it->childs.erase(el);
			delete oldElem;
			oldElem = nullptr;
		} while (it->childs.empty() && !it->finaly);
	}
	return true;
}

bool PrefixTree::Search(const std::wstring& str)
{
	return false;
}

PrefixTree::Iter PrefixTree::getRoot()
{
	return Iter(this->root);
}

PrefixTree::Iter::Iter(TreeElem* elem)
{
	this->elem = elem;
}


PrefixTree::Iter PrefixTree::Iter::goToParent()
{
	if (!elem->parent) throw std::domain_error("parent is nullptr");
	elem = elem->parent;
	return Iter(elem);
}

PrefixTree::Iter PrefixTree::Iter::goToChild(uint64_t index)
{
	if (elem->childs.size() <= index) throw std::out_of_range("index > size");
	elem = elem->childs[index];
	return Iter(elem);
}

bool PrefixTree::Iter::isEmpty()
{
	if (!this->elem) return true;
	return false;
}

PrefixTree::TreeElem* PrefixTree::Iter::operator*()
{
	if (!this->elem) throw std::domain_error("element of Iter is nullptr");
	return this->elem;
}
