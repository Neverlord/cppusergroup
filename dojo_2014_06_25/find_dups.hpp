#include <set>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

// concepts:
// bool Equal(bs::path, bs::path)
// Hash(bs::path) -> Comparable (operator<)

template <typename ForwardIterator, typename Equal, typename Hash>
auto find_dups(ForwardIterator first,
               ForwardIterator last,
               Equal equal,
               Hash hash) -> std::vector<std::set<decltype(*first)>> {
    typedef decltype(*first) path_type;
    std::map<decltype(hash(*first)), std::set<path_type>> res;
    for (; first != last; ++first) {
        res[hash(*first)].emplace(*first);
    }
    //for (auto& kvp : res) {
        //if (kvp.second.size() > 1) return {std::move(kvp.second)};
    //}
    return { };
}
