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

template <typename ForwardIterator, typename Equal, typename Hash>
auto find_dups(ForwardIterator first,
               ForwardIterator last,
               Equal equal,
               Hash hash) -> std::vector<std::set<typename std::remove_reference<decltype(*first)>::type>> {
    using namespace std;
    typedef typename std::remove_reference<decltype(*first)>::type path_type;
    //map<decltype(hash(*first)), set<path_type>> res;
    map<int, set<string>> res;
    for (; first != last; ++first) {
        res[hash(*first)].emplace(*first);
    }
    for (auto& kvp : res) {
        if (kvp.second.size() > 1 && equal(*kvp.second.begin(), *kvp.second.rbegin())) {
            return vector<set<string>>{move(kvp.second)};
        }
    }
    return { };
}
