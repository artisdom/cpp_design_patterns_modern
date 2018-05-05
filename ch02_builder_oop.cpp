#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct HtmlElement
{
    string name;
    string text;
    vector<HtmlElement> elements;

    HtmlElement() {}
    HtmlElement(const string& name, const string& text) : name{name}, text{text} {}

    string str(int indent = 0) const {
        ostringstream oss;

        oss << "<" << name << ">";

        for (auto e : elements) {
            oss << "  <" << e.name << ">" << e.text << "</" << e.name << ">";
        }

        oss << "</" << name << ">";

        return oss.str();
    }
};

int main()
{
    string words[] = { "hello", "world" };
    HtmlElement list{ "ul", ""};

    for (auto w : words)
        list.elements.emplace_back(HtmlElement("li", w));

    printf("%s: \n", list.str().c_str());

    return 0;
}
