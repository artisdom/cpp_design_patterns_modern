#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

struct Product
{
    string name;
    Color color;
    Size size;
};

struct ProductFilter
{
    typedef vector<Product*> Items;

    Items by_color(Items items, Color color);
    Items by_color_and_size(Items items, Size size, Color color);
};

ProductFilter::Items ProductFilter::by_color(Items items, Color color)
{
    Items result;

    for (auto& i : items)
        if (i->color == color)
            result.push_back(i);
    return result;
}

ProductFilter::Items ProductFilter::by_color_and_size(Items items, Size size, Color color)
{
    Items result;

    for (auto& i : items)
        if (i->size == size && i->color == color)
            result.push_back(i);
    return result;
}

template <typename T>
struct AndSpecification;

template <typename T>
struct Specification
{
    virtual bool is_satisfied(T* item) = 0;

    AndSpecification<T> operator &&(Specification& other) {
        return AndSpecification<T>(*this, other);
    }
};

template <typename T>
struct AndSpecification : Specification<T>
{
    Specification<T>& first;
    Specification<T>& second;

    AndSpecification(Specification<T>& first, Specification<T>& second) : first{first}, second{second} {}

    bool is_satisfied(T* item) override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

template <typename T>
struct Filter
{
    virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product>
{
    vector<Product*> filter(vector<Product*> items, Specification<Product>& spec) override {
        vector<Product*> result;
        for (auto& p : items)
            if (spec.is_satisfied(p))
                result.push_back(p);
        return result;
    }
};

struct ColorSpecification : Specification<Product>
{
    Color color;

    explicit ColorSpecification(const Color color) : color{color} {}

    bool is_satisfied(Product* item) override {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product>
{
    Size size;

    explicit SizeSpecification(const Size size) : size{size} {}

    bool is_satisfied(Product* item) override {
        return item->size == size;
    }
};

int main()
{
    Product apple{ "Apple", Color::Green, Size::Small };
    Product tree{ "Tree", Color::Green, Size::Large };
    Product house{ "House", Color::Blue, Size::Large };

    vector<Product *> all{ &apple, &tree, &house };

    BetterFilter bf;
    ColorSpecification green(Color::Green);

    auto green_things = bf.filter(all, green);

    for (auto& x : green_things)
        cout << x->name << " is green" << endl;


    SizeSpecification large(Size::Large);
    AndSpecification<Product> large_and_green{large, green};

    auto large_green_things = bf.filter(all, large_and_green);
    for (auto& x : large_green_things)
        cout << x->name << " is large and green" << endl;

    //AndSpecification<Product> large_and_green2 = ColorSpecification(Color::Green) && SizeSpecification(Size::Large);
    //auto large_and_green2 = ColorSpecification(Color::Green) && SizeSpecification(Size::Large);
    //auto large_and_green2 = green && SizeSpecification(Size::Large);
    auto large_and_green2 = green && large;
    // AndSpecification<Product> large_and_green2 = large && green;

    auto large_green_things2 = bf.filter(all, large_and_green2);
    for (auto& x : large_green_things2)
        cout << x->name << " is large and green" << endl;

    return 0;
}
