#include <iostream>  // std::cout
#include <algorithm> // std::count
#include <vector>    // std::vector
#include <list>      // std::list
// print vector
template <class T>
void print_v(const std::vector<T> &v)
{
    for (auto x : v)
        std::cout << x << " ";
    std::cout << std::endl;
}
// global function
int neg(int x) { return -x; }
// function object
struct Neg
{
    int operator()(int x) { return -x; }
};

int main()
{
    { // 1. Count appearances of value 5 in range
        std::list<int> l = {32, 13, 5, 7, 22, -6, 44, 3, 5, 5};
        auto c = std::count(l.begin(), l.end(), 5);
        std::cout << c << std::endl; // 3
    }
    { // 2. Get iterator to smallest value in the range, or last if the range is empty
        std::vector<int> v = {32, 13, 5, 7, 22, -6, 44, 3, 5, 5};
        std::vector<int>::iterator it = std::min_element(v.begin(), v.end());
        std::cout << *it << " " << it[0] << " (idx: " << it - v.begin() << ")" << std::endl; //-6 -6 (idx: 5)
    }
    { // 3. Negate all elements of vector (4 ways)
        std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        print_v(v); // 1 2 3 4 5 6 7 8 9 10
        // using global function
        std::transform(v.begin(), v.end(), v.begin(), neg);
        print_v(v); //-1 -2 -3 -4 -5 -6 -7 -8 -9 -10

        // using lambda function
        std::transform(v.begin(), v.end(), v.begin(), [](int x)
                       { return -x; });
        print_v(v); // 1 2 3 4 5 6 7 8 9 10

        // using function object
        std::transform(v.begin(), v.end(), v.begin(), Neg());
        print_v(v); //-1 -2 -3 -4 -5 -6 -7 -8 -9 -10

        // using ready-made STL template
        std::transform(v.begin(), v.end(), v.begin(), std::negate<int>());
        print_v(v); // 1 2 3 4 5 6 7 8 9 10
    }
    { // 4. Add/subtrac two vectors, place result in a third vector
        std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::vector<int> w = {5, 2, 3, 4, 1, 5, 1, 3, 4, 6};
        std::vector<int> res;

        // using lambda function (add)
        // here a back_inserter must be used, as size of vector res is 0
        // back_inserter: constructs a back-insert iterator that inserts new elements at the end of the container
        std::transform(v.begin(), v.end(), w.begin(), back_inserter(res), [](int x, int y)
                       { return x + y; });
        print_v(res); // 6 4 6 8 6 11 8 11 13 16

        // function object (add)
        struct myAdd
        {
            int operator()(int a, int b) { return a + b; };
        };
        std::transform(v.begin(), v.end(), w.begin(), res.begin(), myAdd());
        print_v(res); // 6 4 6 8 6 11 8 11 13 16

        // ready-made STL template (subtrac, use std::plus<int>() for addition)
        std::transform(v.begin(), v.end(), w.begin(), res.begin(), std::minus<int>());
        print_v(res); //-4 0 0 0 4 1 6 5 5 4
    }
    // create and resize vectors
    { // a. fill vector with elements 0-100
      // resize the vector
        int size = 10;
        // Initialize the vector with
        // initial values as 0
        std::vector<int> V1(size, 0);
        // use srand() for different outputs
        std::srand(0);
        std::generate(V1.begin(), V1.end(), std::rand);
        print_v1(rand);
        // Print the values in the vector
        for (int i = 0; i < size; i++)
        {
            std::cout << V1[i] << " "; //
        }

        return 0;
    }
    /*  print_v(v); // 1 2 3 4 5 6 7 8 9 10
     // using global function
     std::transform(v.begin(), v.end(), v.begin(), neg);
     print_v(v); //-1 -2 -3 -4 -5 -6 -7 -8 -9 -10

     // using lambda function
     std::transform(v.begin(), v.end(), v.begin(), [](int x)
                    { return -x; });
     print_v(v); // 1 2 3 4 5 6 7 8 9 10

     // using function object
     std::tralrnsform(v.begin(), v.end(), v.begin(), Neg());
     print_v(v); //-1 -2 -3 -4 -5 -6 -7 -8 -9 -10

     // using ready-made STL template
     std::transform(v.begin(), v.end(), v.begin(), std::negate<int>());
     print_v(v); // 1 2 3 4 5 6 7 8 9 10*/
}
return 0;
}