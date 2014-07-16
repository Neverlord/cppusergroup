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
struct find_dups_result 
{
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
    vector<set<path_type>> result;

    for (; first != last; ++first) 
        res[hash(*first)].insert(*first);
    
    for (auto& kvp : res) 
    {
        auto &my_set = kvp.second;
        set<path_type> my_dups;

        while (my_set.size() > 1 ) 
        {
            auto my_first = my_set.begin();
            my_first++;
            while(my_first != my_set.end())
            {
                if(equal(*my_set.begin(),*my_first))
                {
                    my_dups.insert(*my_set.begin());
                    my_dups.insert(*my_first);
                    my_first = my_set.erase(my_first);
                }
                else
                    ++my_first;
            }
                
            my_set.erase(my_set.begin());
        }
        
        if(!my_dups.empty()) result.push_back(my_dups);
    }

    return result;
}
