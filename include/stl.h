#ifndef STL_H
#define STL_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <set>

inline void initial_vector_with_3_mutiplies(std::vector<int>& v, size_t size)
{
    std::vector<int> temp(size);
    v = temp;
    int counter { 0 };
    std::generate(v.begin(), v.end(), [&counter]() {
        counter += 1;
        return counter * 3;
    });
}

inline int count_unique_above(std::vector<int> v, int n)
{
    std::set<int> my_set { v.begin(), v.end() };
    std::vector<int> above(my_set.size());

    auto end_above = std::copy_if(my_set.begin(), my_set.end(), above.begin(),
        [n](int a) { return a > n; });

    above.erase(end_above, above.end());

    return above.size();
}

inline std::string vector_to_string(std::vector<int> v, char separator)
{
    // std::cout << v.back() <<std::endl;
    std::string str = std::accumulate(v.rbegin() + 1, v.rend(),
        std::to_string(v.back()),
        [separator](std::string _str, int _v) {
            // std::cout << _str << std::endl;
            return _str + separator + std::to_string(_v);
        });
    return str;
}

#endif // STL_H