#include <iostream>
#include <string>

using namespace std;

class Person
{
    // address
    string street_address, post_code, city;

    //employment
    string company_name, position;

    int annual_income = 0;

    Person() {}
};

class PersonBuilderBase
{
protected:
    Person& person;
    explicit PersonBuilderBase(Person& person) : person{ person } {}

public:
    operator Person() {
        return std::move(person);
    }

    // builder facets
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};

class PersonAddressBuiler : public PersonBuilderBase
{
    typedef PersonAddressBuiler self;

public:
    explicit PersonAddressBuiler(Person& person) : PersonBuilderBase{ person } {}

    self& at(std::string street_address) {
        person.street_address = street_address;
        return *this;
    }
};

class PersonBuilder : public PersonBuilderBase
{
    Person p; // object being built

public:
    PersonBuilder() : PersonBuilderBase{p} {}
};

int main()
{
    return 0;
}
