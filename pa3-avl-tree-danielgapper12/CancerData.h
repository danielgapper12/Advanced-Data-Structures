#ifndef CANCERDATA_H
#include <iostream>
#include <string>
using namespace std;


class CancerData
{
public:
    // Default constructor
    CancerData() : countryName(""), cancerRate(0.0f) {}

    // Explicit constructor
    CancerData(const string& newCountryName, float newCancerRate) : countryName(newCountryName), cancerRate(newCancerRate) {}

    ~CancerData() = default;

    // other functions?

    // Comparison operators
    bool operator<(const CancerData& other) const;

    bool operator>(const CancerData& other) const;

    // Getter functions
    string getCountryName() const;

    float getCancerRate() const;

    // Print function
    friend ostream& operator<<(ostream& os, const CancerData& data) 
    {
        os << data.countryName << ": " << data.cancerRate;
        return os;
    }

private:
    string countryName;
    float cancerRate;
};


#endif