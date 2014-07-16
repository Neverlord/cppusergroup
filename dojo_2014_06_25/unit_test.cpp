#include "find_dups.hpp"

#include <boost/filesystem.hpp>
#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

using namespace std;
namespace bs = boost::filesystem;

BOOST_AUTO_TEST_CASE(nodups) {
    vector<string> testpaths = { ".", ".." };
    auto res = find_dups(begin(testpaths),
            end(testpaths),
                         [](const string&, const string&) { return false; },
                         [](const string&) { return 1; });
    //return res.empty() ? 0 : 666;
    BOOST_CHECK(res.empty());
}

BOOST_AUTO_TEST_CASE(somedups) {
    vector<bs::path> testpaths{ ".", ".." };
    auto res = find_dups(begin(testpaths),
                         end(testpaths),
                         [](const bs::path&, const bs::path&) { return true; },
                         [](const bs::path&) { return 1; });
    //return res.empty() ? 0 : 666;
    BOOST_CHECK(!res.empty());
}
