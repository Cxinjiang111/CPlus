#include<iostream>

template<typename T>
class ListItem;
template<typename T>
std::ostream& operator<<(std::ostream& out, ListItem<T>& d);

template<typename T>
class ListItem
{
public:
    ListItem(const T& t) : Data(t), Next(nullptr) {}
    ListItem(T&& t) : Data(std::forward<T>(t)), Next(nullptr) {}
    template<typename... Types>
    ListItem(Types&&... args) : Data(std::forward<Types>(args)...), Next(nullptr) {}

    void setnext(ListItem<T>* n)
    {
        Next = n;
    }
    ListItem<T>* next()
    {
        return Next;
    }
    friend std::ostream& operator<< <T>(std::ostream& out, ListItem& d);
private:
    ListItem<T>* Next;
    T* Data;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, ListItem<T>& d)
{
    out << d.Data;
    return out;
}

template<typename T>
class list
{
public:
    list() noexcept : Head(nullptr) {}
    void push(const T& t)
    {
        ListItem<T>* Data = new ListItem<T>(t);
        Data->setnext(Head);
        Head = Data;
    }
    void push(T&& t)
    {
        ListItem<T>* Data = new ListItem<T>(t);
        Data->setnext(Head);
        Head = Data;
    }
    template<typename... Types>
    void emplace(Types&&... args)
    {
        ListItem<T>* Data = new ListItem<T>(std::forward<Types>(args)...);
        Data->setnext(Head);
        Head = Data;

    }
    ListItem<T>* front()
    {
        return Head;
    }
private:
    ListItem<T>* Head;
};

template <typename T>
class ListIter
{
public:
    using value_type = T;
    using reference = T & ;
    using const_referenct = const T&;
    using pointer = T * ;
    using const_pointor = const T*;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    ListIter(pointer p = nullptr) : Iter(p) {}

    bool operator==(const ListIter& rhs) const noexcept
    {
        return Iter == rhs.Iter;
    }
    bool operator!=(const ListIter& rhs) const noexcept
    {
        return Iter != rhs.Iter;
    }
    ListIter& operator++()
    {
        Iter = Iter->next();
        return *this;
    }
    ListIter& operator++(int)
    {
        value_type tmp = *this;
        ++&*this;
        return tmp;
    }
    reference operator*()
    {
        return *Iter;
    }
    pointer operator->()
    {
        return Iter;
    }
private:
    pointer Iter;
};

int main(int args, char* argv[])
{
	list<std::string> l;
	l.push(std::string("hello"));
	l.push("world");
	l.push("abcd");
	l.push("efg");
	l.push("kmm");
	ListIter<ListItem<std::string>> iter(l.front());
	ListIter<ListItem<std::string>> end;
	while (iter != end)
	{
		std::cout << *iter << std::endl;
		++iter;
	}
	return 0;
}
