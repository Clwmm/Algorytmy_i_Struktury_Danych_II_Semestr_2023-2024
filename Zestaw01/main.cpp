// Mateusz Kałwa

#include <iostream>

template <class T>
class Set {
    struct Node {
        template <class U>
        Node(U&& val, Node* left = nullptr, Node* right = nullptr)
            : val(std::forward<U>(val)), prev(left), next(right) {}
        T val;
        Node* prev;
        Node* next;
    };

    Node* guard;
    size_t listSize = 0;

    T popBetween(Node* left, Node* right);
    T pop_back();

    template <class U>
    void insertBetween(Node* left, U&& x, Node* right);
    
    template <class U>
    void push_back(U&& x);

    template <class U>
    static Set<T>& assemble(U&& x, Set<T>& a, Set<T>& b);

    template <class U>
    static Set<T>& assemble_(U&& x, Set<T>& a);

public:

    Set();
    Set(Set& other);
    Set(Set&& other);

    Set<T>& operator=(Set<T>& other);
    Set<T>& operator+=(Set<T>& other);
    Set<T>& operator-=(Set<T>& other);
    Set<T>& operator|=(Set<T>& other);

    struct Iterator
    {
        Node* current;
        Iterator(Node* node) : current(node) {}

        T& operator*() { return this->current->val; }
        Iterator& operator++()
        {
            this->current = this->current->next;
            return *this;
        }
        Iterator& operator--()
        {
            this->current = this->current->prev;
            return *this;
        }
        bool operator==(const Iterator& other) const
        {
            return this->current == other.current;
        }
        bool operator!=(const Iterator& other) const
        {
            return this->current != other.current;
        }
    };

    static Set<T>& setUnion(Set<T>& a, Set<T>& b);
    static Set<T>& setIntersection(Set<T>& a, Set<T>& b);
    static Set<T>& setDifference(Set<T>& a, Set<T>& b);

    template <class U>
    bool push(U&& x);

    void pushSet(Set<T>& other);

    void removeFirst();
    bool remove(const T& x);
    size_t size();
    bool empty();
    void clear();
    void display();

    template <class U>
    Iterator insert(Iterator it, U&& x)
    {
        this->insertBetween(it.current->prev, std::forward<U>(x), it.current);
        return Iterator(it.current->prev);
    }

    Iterator find(const T& x)
    {
        Set<T>::Iterator it = this->begin();
        for (; it != this->end(); ++it)
        {
            if (*it == x)
                return it;
            if (*it > x)
                return this->end();
        }
        return this->end();
        //throw std::out_of_range("Element not found");
    }
    Iterator erase(Iterator it)
    {
        if (it == this->end())
            throw std::out_of_range("Iterator out of range");
        Set<T>::Iterator next = it.current->next;
        this->popBetween(it.current->prev, it.current->next);
        return next;
    }

    Iterator begin() { return Iterator(guard->next); }
    Iterator end() { return Iterator(guard); }
};


void addElements_to_c(Set<int>& c)
{
    // Adding elements to the first set
    c.push(5);
    c.push(4);
    c.push(3);
    c.push(6);
    c.push(1);
    c.push(2);
}

void addElements_to_d(Set<int>& d)
{
    // Adding elements to the second set
    d.push(7);
    d.push(10);
    d.push(5);
    d.push(9);
    d.push(8);
    d.push(6);
}

auto main() -> int
{
    Set<int> c;
    addElements_to_c(c);

    Set<int> d;
    addElements_to_d(d);

    std::cout << "First set: " << std::endl;
    c.display();
    std::cout << std::endl;

    std::cout << "Second set: " << std::endl;
    d.display();
    std::cout << std::endl;

    c += d;
    std::cout << "Union of two sets: " << std::endl;
    c.display();
    std::cout << std::endl;

    c.clear();
    addElements_to_c(c);

    c = Set<int>::setUnion(c, d);
    std::cout << "Recursive union of two sets: " << std::endl;
    c.display();
    std::cout << std::endl;

    c.clear();
    addElements_to_c(c);

    c -= d;
    std::cout << "Difference of two sets: " << std::endl;
    c.display();
    std::cout << std::endl;

    c.clear();
    addElements_to_c(c);

    c = Set<int>::setDifference(c, d);
    std::cout << "Recursive difference of two sets: " << std::endl;
    c.display();
    std::cout << std::endl;

    c.clear();
    addElements_to_c(c);

    c |= d;
    std::cout << "Intersection of two sets: " << std::endl;
    c.display();
    std::cout << std::endl;

    c.clear();
    addElements_to_c(c);

    c = Set<int>::setIntersection(c, d);
    std::cout << "Recursive intersection of two sets: " << std::endl;
    c.display();
    std::cout << std::endl;

    c.clear();
    addElements_to_c(c);

    // Testing the remove function
    c.remove(3);
    std::cout << "Removing 3 from the first set: " << std::endl;
    c.display();

    // Testing the find function
    if (c.find(3) != c.end())
        std::cout << "3 is in the first set" << std::endl;
    else
        std::cout << "3 is not in the first set" << std::endl;

    if (c.find(5) != c.end())
        std::cout << "5 is in the first set" << std::endl;
    else
        std::cout << "5 is not in the first set" << std::endl;
}

template<class T>
T Set<T>::popBetween(Node* left, Node* right)
{
    --this->listSize;
    Node* center = left->next;
    T val = center->val;
    delete center;
    left->next = right;
    right->prev = left;
    return val;
}

template<class T>
T Set<T>::pop_back()
{
    if (this->listSize == 0)
        throw std::underflow_error("Stack is empty");
    return this->popBetween(guard->prev->prev, guard);
}

template<class T>
Set<T>::Set()
{
    this->guard = new Node(T{}, nullptr, nullptr);
    this->guard->next = this->guard;
    this->guard->prev = this->guard;
}

template<class T>
Set<T>::Set(Set& other)
    : Set()
{
    Set<T>::Iterator it = other.begin();
    for (; it != other.end(); ++it)
        this->push_back(*it);
}

template<class T>
Set<T>::Set(Set&& other)
    : guard(other.guard), listSize(other.listSize) {}

template<class T>
Set<T>& Set<T>::operator=(Set<T>& other)
{
    if (this != &other)
    {
        this->clear();
        Set<T>::Iterator it = other.begin();
        for (; it != other.end(); ++it)
            this->push_back(*it);
    }
    return *this;
}

template<class T>
Set<T>& Set<T>::operator+=(Set<T>& other)
{
    Set<T>::Iterator it = other.begin();
    for (; it != other.end(); ++it)
        this->push(*it);
    return *this;
}

template<class T>
Set<T>& Set<T>::operator-=(Set<T>& other)
{
    Set<T>::Iterator it = other.begin();
    for (; it != other.end(); ++it)
        if (this->find(*it) != this->end())
            this->remove(*it);
    return *this;
}

template<class T>
Set<T>& Set<T>::operator|=(Set<T>& other)
{
    Set<T>::Iterator it = this->begin();
    for (; it != this->end();)
    {
        if (other.find(*it) == other.end())
            it = this->erase(it);
        else
            ++it;
    }
    return *this;
}

template<class T>
Set<T>& Set<T>::setUnion(Set<T>& a_, Set<T>& b_)
{
    Set<T> a = a_;
    Set<T> b = b_;
    Set<T>* nullSet = new Set<T>;

    if (a.size() == 0 && b.size() == 0)
        return *nullSet;
    else if (a.size() == 0)
    {
        T temp = *b.begin();
        b.removeFirst();
        return Set<T>::assemble(std::forward<T>(temp), *nullSet, b);
    }
    else if (b.size() == 0)
    {
        T temp = *a.begin();
        a.removeFirst();
        return Set<T>::assemble(std::forward<T>(temp), a, *nullSet);
    }
    else if (*a.begin() == *b.begin())
    {
        T temp = *a.begin();
        a.removeFirst();
        b.removeFirst();
        return Set<T>::assemble(std::forward<T>(temp), a, b);
    }
    else if (*a.begin() < *b.begin())
    {
        T temp = *a.begin();
        a.removeFirst();
        return Set<T>::assemble(std::forward<T>(temp), a, b);
    }
    else
    {
        T temp = *b.begin();
        b.removeFirst();
        return Set<T>::assemble(std::forward<T>(temp), a, b);
    }
}

template<class T>
Set<T>& Set<T>::setIntersection(Set<T>& a_, Set<T>& b_)
{
    Set<T> a = a_;
    Set<T> b = b_;
    Set<T>* nullSet = new Set<T>;

    if (a.size() == 0 || b.size() == 0)
        return *nullSet;
    else if (*a.begin() == *b.begin())
    {
        T temp = *a.begin();
        a.removeFirst();
        b.removeFirst();
        return Set<T>::assemble_(std::forward<T>(temp), Set<T>::setIntersection(a, b));
    }
    else if (*a.begin() < *b.begin())
    {
        a.removeFirst();
        return Set<T>::setIntersection(a, b);
    }
    else
    {
        b.removeFirst();
        return Set<T>::setIntersection(a, b);
    }
}

template<class T>
Set<T>& Set<T>::setDifference(Set<T>& a_, Set<T>& b_)
{
    a_ -= b_;
    return a_;
}

template<class T>
void Set<T>::pushSet(Set<T>& other)
{
    Set<T>::Iterator it = other.begin();
    for (; it != other.end(); ++it)
        this->push(*it);
}

template<class T>
void Set<T>::removeFirst()
{
    if (!this->empty())
        this->erase(this->begin());
}

template<class T>
bool Set<T>::remove(const T& x)
{
    Set<T>::Iterator it = this->begin();
    for (; it != this->end();)
    {
        if (*it == x)
        {
            it = this->erase(it);
            return true;
        }
        else
            ++it;
    }
    return false;
}

template<class T>
size_t Set<T>::size()
{
    return this->listSize;
}

template<class T>
bool Set<T>::empty()
{
    return this->size() == 0;
}

template<class T>
void Set<T>::clear()
{
    while (!this->empty())
        this->pop_back();
}

template<class T>
void Set<T>::display()
{
    Set<T>::Iterator it = this->begin();
    for (; it != this->end(); ++it)
        std::cout << *it << "\t";
    std::cout << std::endl;
}


template<class T>
template<class U>
void Set<T>::insertBetween(Node* left, U&& x, Node* right)
{
    Node* node = new Node(std::forward<U>(x), left, right);
    left->next = node;
    right->prev = node;
    ++this->listSize;
}

template<class T>
template<class U>
void Set<T>::push_back(U&& x)
{
    this->insertBetween(guard->prev, std::forward<U>(x), guard);
}

template<class T>
template<class U>
Set<T>& Set<T>::assemble(U&& x, Set<T>& a, Set<T>& b)
{
    Set<T>* result = new Set<T>;
    result->push_back(std::forward<U>(x));
    result->pushSet(Set<T>::setUnion(a, b));
    return *result;
}

template<class T>
template<class U>
Set<T>& Set<T>::assemble_(U&& x, Set<T>& a)
{
    Set<T>* result = new Set<T>;
    result->push_back(std::forward<U>(x));
    result->pushSet(a);
    return *result;
}

template<class T>
template<class U>
bool Set<T>::push(U&& x)
{
    if (this->find(x) == this->end())
    {
        Set<T>::Iterator it = this->begin();
        for (; it != this->end(); ++it)
            if (*it > x)
            {
                this->insert(it, std::forward<U>(x));
                return true;
            }
        this->push_back(std::forward<U>(x));
        return true;
    }
    return false;
}
