// Mateusz Kałwa

#include <stdexcept>
#include "Set.h"

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