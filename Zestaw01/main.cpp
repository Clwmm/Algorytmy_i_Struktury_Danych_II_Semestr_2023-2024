// Mateusz Kałwa

#include <stdexcept>
#include <iostream>

template<class T>
class Set {
    struct Node {
        template <class U>
        Node(U&& val = 0, Node* left = nullptr, Node* right = nullptr)
            : val(std::forward<U>(val)), prev(left), next(right) {}
        T val;
        Node* prev;
        Node* next;
    };

    Node* guard;
    size_t listSize = 0;

    template <class U>
    void insertBetween(Node* left, U&& x, Node* right)
    {
        Node* node = new Node(std::forward<U>(x), left, right);
        left->next = node;
        right->prev = node;
        ++this->listSize;
    }

    T popBetween(Node* left, Node* right)
    {
        --this->listSize;
        Node* center = left->next;
        T val = center->val;
        delete center;
        left->next = right;
        right->prev = left;
        return val;
    }

    // BACK METHODS
    template <class U>
    void push_back(U&& x) // Dołącza element na koniec listy
    {
        this->insertBetween(guard->prev, std::forward<U>(x), guard);
    }
    T pop_back() // Usuwa i zwraca element z końca listy
    {
        if (this->listSize == 0)
            throw std::underflow_error("Stack is empty");
        return this->popBetween(guard->prev->prev, guard);
    }


public:
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

    Set()
    {
        this->guard = new Node(0, nullptr, nullptr);
        this->guard->next = this->guard;
        this->guard->prev = this->guard;
    }

    Set(Set& other) // COPY CONSTRUCTOR
        : Set()
    {
        Set<T>::Iterator it = other.begin();
        for (; it != other.end(); ++it)
            this->push_back(*it);
    }

    Set(Set&& other) // MOVE CONSTRUCTOR
        : guard(other.guard), listSize(other.listSize) { }


    // OPERATOR OVERLOADS

    Set& operator+=(Set<T>& other) // Suma dwóch zbiorów
    {
        Set<T>::Iterator it = other.begin();
        for (; it != other.end(); ++it)
        {
            if (this->find(*it) == this->end())
                this->push_back(*it);
        }
        
        return *this;
    }

    Set& operator-=(Set<T>& other) // Różnica dwóch zbiorów
    {
        Set<T>::Iterator it = other.begin();
        for (; it != other.end(); ++it)
        {
            if (this->find(*it) != this->end())
                this->remove(*it);
        }
        return *this;
    }

    Set& operator|=(Set<T>& other) // Przecięcie dwóch zbiorów
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

    // FRONT METHODS
    template <class U>
    bool push(U&& x) // Dołącza element na początek listy
    {
        if (this->find(x) == this->end())
        {
            this->push_back(std::forward<U>(x));
            return true;
        }
        return false;
    }

    Iterator find(const T& x)// Wyszukuje element o wartości `x`
                             // i zwraca jego pozycję
    {
        Set<T>::Iterator it = this->begin();
        for (; it != this->end(); ++it)
            if (*it == x)
                return it;
        return this->end();
        //throw std::out_of_range("Element not found");
    }

    Iterator erase(Iterator it)// Usuwa element wskazywany przez iterator 
                               // i zwraca iterator do kolejnego elementu

    {
        if (it == this->end())
            throw std::out_of_range("Iterator out of range");
        Set<T>::Iterator next = it.current->next;
        this->popBetween(it.current->prev, it.current->next);
        return next;
    }

    template <class U>
    Iterator insert(Iterator it, U&& x)// Wstawia element x przed pozycję it 
                                       // i zwraca pozycję x
    {
        this->insertBetween(it.current->prev, std::forward<U>(x), it.current);
        return Iterator(it.current->prev);
    }

    bool remove(const T& x) // Usuwa wystąpienia x i zwraca ich liczbę
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

    int size() // Zwraca liczbę elementów w liście
    {
        return this->listSize;
    }

    bool empty() // Zwraca 'true' gdy lista jest pusta
    {
        return this->size() == 0;
    }
    void clear() // Czyści listę
    {
        while (!this->empty())
            this->pop_back();
    }

    void display() // Wyświetla zawartość listy
    {
        Set<T>::Iterator it = this->begin();
        for (; it != this->end(); ++it)
            std::cout << *it << "\t";
        std::cout << std::endl;
    }

    Iterator begin() { return Iterator(guard->next); } // Zwraca iterator na pierwszy element
    Iterator end() { return Iterator(guard); } // Zwraca iterator na koniec listy,
                                               // czyli za ostatnim elementem

};


void addElements_to_c(Set<int>& c)
{
    // Adding elements to the first set
    c.push(1);
    c.push(2);
    c.push(3);
    c.push(4);
    c.push(5);
    c.push(6);
}

void addElements_to_d(Set<int>& d)
{
    // Adding elements to the second set
    d.push(5);
    d.push(6);
    d.push(7);
    d.push(8);
    d.push(9);
    d.push(10);
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
    std::cout << "Sum of two sets: " << std::endl;
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

    c |= d;
    std::cout << "Intersection of two sets: " << std::endl;
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