#include <iostream>
#include <string>

using namespace std;

class ILogger{
public:
    virtual void log_info(string str) = 0;
};

class Reporting
{
    ILogger& logger;

public:
    Reporting(const ILogger& logger) : logger{logger} {}

    void prepare_report() {
        logger.log_info("Preparing the report");
    }
};
