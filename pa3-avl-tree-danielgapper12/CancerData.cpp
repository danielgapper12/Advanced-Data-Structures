#include "CancerData.h"

// Comparison operators
bool CancerData::operator<(const CancerData& other) const 
{
    return cancerRate < other.cancerRate;
}

bool CancerData::operator>(const CancerData& other) const 
{
    return cancerRate > other.cancerRate;
}

// Getter functions
string CancerData::getCountryName() const 
{
    return countryName; 
}

float CancerData::getCancerRate() const 
{ 
    return cancerRate; 
}

