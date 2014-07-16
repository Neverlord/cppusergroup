#include <set>
#include <map>
#include <vector>
#include <string>
#include <type_traits>
#include <iostream>
#include <algorithm>

// concepts:
// bool Equal(bs::path, bs::path)
// Hash(bs::path) -> Comparable (operator<)

template <typename T>
struct find_dups_result {
    typedef std::vector<std::set<typename std::remove_reference<T>::type>> type;
};

template <typename ForwardIterator, typename Equal, typename Hash>
auto find_dups(ForwardIterator first,
               ForwardIterator last,
               Equal equal,
               Hash hash)
-> typename find_dups_result<decltype(*first)>::type {
    using namespace std;
    using path_type = typename remove_reference<decltype(*first)>::type;
    map<decltype(hash(*first)), set<path_type>> res;
    for (; first != last; ++first) {
        res[hash(*first)].insert(*first);
    }
    for (auto& kvp : res) {
        if (kvp.second.size() > 1 && 
            equal(*kvp.second.begin(), *kvp.second.rbegin())) 
        {
            return vector<set<path_type>>{move(kvp.second)};
        }
    }
    return { };
}
