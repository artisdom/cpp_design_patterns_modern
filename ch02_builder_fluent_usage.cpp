#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

struct HtmlBuilder;

struct HtmlElement
{
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;

    static unique_ptr<HtmlBuilder> build(const string& root_name) {

        return make_unique<HtmlBuilder>(root_name);

    }

    string str(int indent = 0) const {
      ostringstream oss;

      oss << "<" << name << ">";
      for (auto e : elements) {
        oss << "  <" << e.name << ">" << e.text << "</" << e.name << ">";
      }
      oss << "</" << name << ">";

      return oss.str();
    }

protected: //hide all constructors
    HtmlElement() {}
    HtmlElement(const string &name, const string &text)
        : name{name}, text{text} {}
};

struct HtmlBuilder
{
    HtmlElement root;

    HtmlElement build() const {
        return root;
    }

    //HtmlBuilder(string root_name) { root.name = root_name; }

    HtmlBuilder& add_child(string child_name, string child_text) {
        HtmlElement e{ child_name, child_text };
        root.elements.emplace_back(e);
        return *this;
    }

    string str() { return root.str(); }

    operator HtmlElement() const { return root; }
};

int main()
{
    HtmlBuilder builder{ "ul" };
    builder.add_child("li", "hello").add_child("li", "world");
    cout << builder.str() << endl;

    return 0;
}
