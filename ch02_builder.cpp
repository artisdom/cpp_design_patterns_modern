#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    string words[] = { "hello", "world" };
    ostringstream oss;

    oss << "<ul>";

    for (auto w : words)
        oss << "  <li>" << w << "</li>";

    oss << "</ul>";

    printf("%s: \n", oss.str().c_str());

    return 0;
}
