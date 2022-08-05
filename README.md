# TrieTree
Префиксное дерево
открытые подтипы:
Iter - оболочка для TreeElem позволяющая перемещаться по элементам дерева. Перегружен оператор *
Открытые методы:
void Run(std::function<void(Iter elem)>func)
void Run(Iter start,std::function<void(Iter elem)>func)
void rRun(std::function<void(Iter elem)>func)
void rRun(Iter start, std::function<void(Iter elem)>func)
void Add(std::wstring str,bool isLower) - второй параметр отвечает за чувствительность к регистру
bool Delete(std::wstring str,bool isLower = true) - второй параметр отвечает за чувствительность к регистру
std::vector<std::pair<std::wstring, double>>& Search(const std::wstring& str,bool isLower = true) - второй параметр отвечает за чувствительность к регистру, возвращает 
вектор с парами которые хранят слова с их весами.
Iter getRoot()
uint16_t getCountWords() - возвращает колличество слов в дереве
void Clear()
