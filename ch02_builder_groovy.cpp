#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Tag
{
    string name;
    string text;
    vector<Tag> children;
    vector<std::pair<string, string>> attributes;

    friend ostream& operator << (ostream& os, const Tag& tag) {
    }

//protected:
    Tag(const string& name, string& text) : name{name}, text{text} {}

    Tag(const string& name, vector<Tag>& children) : name{name}, children{children} {}

};

struct P : Tag
{
    explicit P(const std::string& text) : Tag{"p", text} {}

    P(std::initializer_list<Tag> children) : Tag("p", children) {}

};

struct IMG : Tag
{
    explicit IMG(const string& url) : Tag{ "img", "" } {
        attributes.emplace_back({"src", url});
    }
};

int main()
{
    return 0;
}
