#include <set>
#include <map>
#include <string>
#include <iostream>

#include <boost/filesystem.hpp>

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

using namespace std;
namespace bs = boost::filesystem;

// concepts:
// bool Equal(bs::path, bs::path)
// Hash(bs::path) -> Comparable (operator<)

template <typename ForwardIterator, typename Equal, typename Hash>
vector<set<bs::path>> filediff(ForwardIterator first,
                               ForwardIterator last,
                               Equal equal,
                               Hash hash) { return { }; }

BOOST_AUTO_TEST_CASE(irgendeinlustigername) {
    vector<bs::path> testpaths = { ".", "./trash" };
    auto res = filediff(begin(testpaths),
                        end(testpaths),
                        [] { return false; },
                        [] { return 1; });
    //return res.empty() ? 0 : 666;
    BOOST_CHECK(res.empty());
}
