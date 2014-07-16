#include <iostream>
#include <fstream>
#include <functional>
#include "find_dups.hpp"

#include <boost/filesystem.hpp>
#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

using namespace std;
namespace bs = boost::filesystem;

size_t my_hash(const bs::path &p)
{
    std::ifstream file(p.string());
    std::string buffer{std::istreambuf_iterator<char>(file),
                       std::istreambuf_iterator<char>()};


    std::hash<string> f;
    return f(buffer);
}

bool my_equal(const bs::path &p1,const bs::path &p2)
{
    typedef std::istreambuf_iterator<char> iterator;
    std::ifstream f1(p1.string()), f2(p2.string());
    std::string b1{iterator(f1),iterator()};
    std::string b2{iterator(f2),iterator()};

    return b1==b2;
}

BOOST_AUTO_TEST_CASE(nodups) {
    vector<string> testpaths{ ".", ".." };
    auto res = find_dups(begin(testpaths),
            end(testpaths),
                         [](const string&, const string&) { return false; },
                         [](const string&) { return 1; });
    //return res.empty() ? 0 : 666;
    BOOST_CHECK(res.empty());
}

BOOST_AUTO_TEST_CASE(somedups) {
    vector<bs::path> testpaths = { "test1.hpp","test2.hpp"};
    auto res = find_dups(begin(testpaths),
                         end(testpaths),
                         my_equal,
                         my_hash);
    //return res.empty() ? 0 : 666;
    BOOST_CHECK(!res.empty());
}

BOOST_AUTO_TEST_CASE(gitdups) {
    auto res = find_dups(bs::recursive_directory_iterator(bs::path("../.git")),
                         bs::recursive_directory_iterator(),
                         my_equal,
                         my_hash);
    //return res.empty() ? 0 : 666;
    BOOST_CHECK(res.empty());
}
