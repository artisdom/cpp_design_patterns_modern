#include <iostream>
#include <vector>

using namespace std;

struct Document
{

};

struct IMachine
{
  virtual void print(vector<Document*> docs) = 0;
  virtual void fax(vector<Document*> docs) = 0;
  virtual void scan(vector<Document*> docs) = 0;
};

struct MyFavouritePrinter /* : IMachine */
{
    void print(vector<Document*> docs) override;
    void fax(vector<Document*> docs) override;
    void scan(vector<Document*> docs) override;
};

struct IPrinter
{
    virtual void print(vector<Document*> docs) = 0;
};

struct IScanner
{
    virtual void scan(vector<Document*> docs) = 0;
};

struct Printer: IPrinter
{
    void print(vector<Document*> docs) override;
};

struct Scanner : IScanner
{
    void scan(vector<Document*> docs) override;
};

struct IMachine2: IPrinter, IScanner /* IFax and so on */
{

};

struct Machine : IMachine2
{
    IPrinter& printer;
    IScanner& scanner;

    Machine(IPrinter& printer, IScanner& scanner) : printer{printer}, scanner{scanner} {}

    void print(vector<Document*> docs) override {
        printer.print(docs);
    }

    void scan(vector<Document*> docs) override {
        scanner.scan(docs);
    }
};
