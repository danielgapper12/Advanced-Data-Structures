#include "TwitterData.hpp"

// Constructor
TwitterData::TwitterData () 
{
	mpUserName =  mpActualName = mpEmail = mpCategory = nullptr;
	mpNumTweets = nullptr;
}

// Destructor
TwitterData::~TwitterData() 
{
	// Task 1(b) - you need to implement
    delete mpUserName;
    delete mpActualName;
    delete mpEmail;
    delete mpCategory;
    delete mpNumTweets;
}

// Copy Constructor - deep copy
TwitterData::TwitterData(const TwitterData& other) 
{
	// Task 1(b) - you need to implement
    if (other.mpUserName) 
	{
        mpUserName = new std::string(*(other.mpUserName));
    } else {
        mpUserName = nullptr;
    }

    if (other.mpActualName) 
	{
        mpActualName = new std::string(*(other.mpActualName));
    } else {
        mpActualName = nullptr;
    }

    if (other.mpEmail) 
	{
        mpEmail = new std::string(*(other.mpEmail));
    } else {
        mpEmail = nullptr;
    }

    if (other.mpCategory) 
	{
        mpCategory = new std::string(*(other.mpCategory));
    } else {
        mpCategory = nullptr;
    }

    if (other.mpNumTweets) 
	{
        mpNumTweets = new int(*(other.mpNumTweets));
    } else {
        mpNumTweets = nullptr;
    }
}

// Move Constructor
TwitterData::TwitterData(TwitterData&& other) noexcept : mpUserName(other.mpUserName), mpActualName(other.mpActualName), mpEmail(other.mpEmail), mpCategory(other.mpCategory), mpNumTweets(other.mpNumTweets) 
{
	// Task 1(b) - you need to implement
    other.mpUserName = nullptr;
    other.mpActualName = nullptr;
    other.mpEmail = nullptr;
    other.mpCategory = nullptr;
    other.mpNumTweets = nullptr;
}

// Copy Assignment Operator
TwitterData& TwitterData::operator=(const TwitterData& other) 
{
	// Task 1(b) - you need to implement
    if (this != &other) {
        delete mpUserName;
        delete mpActualName;
        delete mpEmail;
        delete mpCategory;
        delete mpNumTweets;

        mpUserName = new std::string(*other.mpUserName);
        mpActualName = new std::string(*other.mpActualName);
        mpEmail = new std::string(*other.mpEmail);
        mpCategory = new std::string(*other.mpCategory);
        mpNumTweets = new int(*other.mpNumTweets);
    }
    return *this;
}

// Move Assignment Operator
TwitterData& TwitterData::operator=(TwitterData&& other) noexcept 
{
	// Task 1(b) - you need to implement
    if (this != &other) 
	{
        delete mpUserName;
        delete mpActualName;
        delete mpEmail;
        delete mpCategory;
        delete mpNumTweets;

        mpUserName = other.mpUserName;
        mpActualName = other.mpActualName;
        mpEmail = other.mpEmail;
        mpCategory = other.mpCategory;
        mpNumTweets = other.mpNumTweets;

        other.mpUserName = nullptr;
        other.mpActualName = nullptr;
        other.mpEmail = nullptr;
        other.mpCategory = nullptr;
        other.mpNumTweets = nullptr;
    }
    return *this;
}

\

// Getters Implementation
std::string TwitterData::getUserName() const
{
	return *(this->mpUserName);
}

std::string TwitterData::getActualName() const
{
	return *(this->mpActualName);
}

std::string TwitterData::getEmail() const
{
	return *(this->mpEmail);
}

std::string TwitterData::getCategory() const
{
	return *(this->mpCategory);
}

int TwitterData::getNumTweets() const
{
	return *(this->mpNumTweets);
}

// Setters Implementation
void TwitterData::setUserName(const std::string& newUserName) 
{
    // Task 1(a) - you need to implement
	// do we need to allocate space for a std::string here?
	if (!mpUserName) mpUserName = new std::string;
    *mpUserName = newUserName;
}

void TwitterData::setActualName(const std::string& newActualName) 
{
	// Task 1(a) - you need to implement
	// do we need to allocate space for a std::string here?
    if (!mpActualName) mpActualName = new std::string;
    *mpActualName = newActualName;
}

void TwitterData::setEmail(const std::string& newEmail) 
{
	// Task 1(a) - you need to implement
	// do we need to allocate space for a std::string here?
    if (!mpEmail) mpEmail = new std::string;
    *mpEmail = newEmail;
}

void TwitterData::setCategory(const std::string& newCategory) 
{
	// Task 1(a) - you need to implement
	// do we need to allocate space for a std::string here?
    if (!mpCategory) mpCategory = new std::string;
    *mpCategory = newCategory;
}

void TwitterData::setNumTweets(const int& newNumTweets) 
{
	// Task 1(a) - you need to implement
	// do we need to allocate space for an int here?
    if (!mpNumTweets) mpNumTweets = new int;
    *mpNumTweets = newNumTweets;
}
