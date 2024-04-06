/*
o	(1 pt) What piece of data read from the file did you use for the key and why?
I used the username as the key since it was unique to each account. It was also easy to access since it was the first entry
and separated from the data with quotes.

o	(2 pts) Assuming that the map is using a red-black tree, what is the worst-case Big-O for inserting key-value pairs based on a key?
The worst case is O(log n) where n is the number of elements in the map. Red-black trees are balanced trees so inserting means that
you need to traverse the tree to the correct location, and upon insertion there may be a need to rebalance.

o	(2 pts) Assuming that the map is using a red-black tree, what is the worst-case Big-O for retrieving data based on a key?
The worst-case Big-O for retrieving data based on a key is also O(log n). This is similar to insertion as lookup operations also 
require traversing the tree down to the node that contains the key.

o	(2 pts) Assuming that the map is using a red-black tree, what is the worst-case Big-O for deleting key-value pairs based on a key?
The worst-case Big-O for deleting key-value pairs based on a key is also O(log n). It is similar to insertion and retrieval as deletion 
could potentially require traversing the tree to find the key and then require a rebalance after removing.

o	(2 pts) Assuming that the map is using a red-black tree, what is the worst-case Big-O for iterating through the entire map?
The worst-case Big-O for iterating through the entire map would be O(n). Regardless of how it is sorted, if an algorithm needs to
step through every element in any tree, it will be O(n)

o	(4 pts) Based on the specific algorithm that you used to find and remove a key-value pair based on a value, what is the worst-case Big-O?
I utilized the .erase method to remove a key-value pair based on the key. The operation for finding and erasing by key is O(log n). If you are
searching for a value, before removing though, then you need to scan through the entire map and look at each element so it becomes O(n).

o	(4 pts) Based on your conclusions of the tasks performed in this assignment, when and why should we use a map?
Maps should be used whenever fast lookups, insertions and deletions are beneficial and important. They are great for organizing data 
with quick access and modifications while maintaining order using unique keys.

*/


#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include "TwitterData.hpp"

// function declarations

void printMapRangeBased(const std::map<std::string, TwitterData>& accounts);
void printMapWithIterators(const std::map<std::string, TwitterData>& accounts);
void printMapOperatorOverload(const std::map<std::string, TwitterData>& accounts);

std::ostream& operator<<(std::ostream& os, const TwitterData& data);

int main(int argc, char *argv[]) 
{
	// we need a map to store our key-value pairs
	// std::map<keyType, ValueType>; What should the key be? What about the value?
    std::string filePath = "TwitterAccounts.csv";
    std::map<std::string, TwitterData> accounts;

	// Tasks 1(c) and (d) - Read the CSV file and insert the data into the std::map object
    std::ifstream file(filePath);
    if (!file.is_open()) 
	{
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return 1;
    }

    std::string line;
    // Skip the header row
    std::getline(file, line);
    while (std::getline(file, line)) 
	{
        std::istringstream lineStream(line);
        std::string userName, firstName, lastName, email, category, numTweetsStr;
        int numTweets;

        std::getline(lineStream, userName, ',');

        // remaining data in one block
        std::string dataBlock;
        std::getline(lineStream, dataBlock);

        // cut off front and back quotes from data block
        dataBlock = dataBlock.substr(1, dataBlock.length() - 2);

        std::istringstream dataStream(dataBlock);
        std::getline(dataStream, lastName, ',');
        std::getline(dataStream, firstName, ',');
        std::getline(dataStream, email, ',');
        std::getline(dataStream, numTweetsStr, ',');
        numTweets = stoi(numTweetsStr);
        std::getline(dataStream, category, ',');

        // combine first and last names into actualName
        std::string actualName = lastName + "," + firstName;

        TwitterData account;
        account.setUserName(userName);
        account.setActualName(actualName);
        account.setEmail(email);
        account.setNumTweets(numTweets);
        account.setCategory(category);

        // insert into or update the map
        accounts[userName] = account;
    }

	// Task 1(g) - 1st print - iterate through the std::map and print the key-value pairs; print using a range loop
    printMapRangeBased(accounts);

	// Task 1(e) - remove the key-value pair matching key “ken2005”
    accounts.erase("ken2005");

	// Task 1(g) - 2nd print - iterate through the std::map and print the key-value pairs; print using a for loop using iterators
    std::cout << "\nRemoved 'ken2005':" << std::endl;
    printMapWithIterators(accounts);

	// Task 1(f) - remove the key-value pair matching last and first name “Smith,Kathryn”
    for (auto it = accounts.begin(); it != accounts.end(); ) 
	{
        if (it->second.getActualName() == "Smith,Kathryn") 
		{
            it = accounts.erase(it);
        } else {
            ++it;
        }
    }

	// Task 1(g) - 3rd print - print using a “<< operator for map” . You need to define the operator function in main.cpp
    std::cout << "\nRemoved 'Smith,Kathryn':" << std::endl;
    printMapOperatorOverload(accounts);

	// Task 1(h) reorganize the data and store it in a map object where the keys are categories and values are vectors of TwitterData
    std::map<std::string, std::vector<TwitterData>> categorizedAccounts;
    for (const auto& pair : accounts) 
	{
        categorizedAccounts[pair.second.getCategory()].push_back(pair.second);
    }

	// Task 1(i) - print (MostViewedCategory, vector of TwitterData) pairs.
    std::cout << "\nAccounts are categorized by MostViewedCategory:" << std::endl;
    for (const auto& categoryPair : categorizedAccounts) 
	{
        std::cout << "Category: " << categoryPair.first << std::endl;
        for (const auto& data : categoryPair.second) 
		{
            std::cout << data << std::endl;
        }
    }
    return 0;
}

void printMapRangeBased(const std::map<std::string, TwitterData>& accounts) 
{
    std::cout << "\nFirst Print; range-based for loop:" << std::endl;
    for (const auto& pair : accounts) 
	{
        std::cout << "Username: " << pair.first << ", Data: " << pair.second << std::endl;
    }
}

void printMapWithIterators(const std::map<std::string, TwitterData>& accounts)
{
    std::cout << "\nSecond Print; for loop with iterators:" << std::endl;
    for (auto it = accounts.begin(); it != accounts.end(); ++it) 
	{
        std::cout << "Username: " << it->first << ", Data: " << it->second << std::endl;
    }
}

void printMapOperatorOverload(const std::map<std::string, TwitterData>& accounts) 
{
    std::cout << "\nThird Print; using operator<< overload:" << std::endl;
    for (const auto& pair : accounts) 
	{
        std::cout << pair.first << " => " << pair.second << std::endl;
    }
}


std::ostream& operator<<(std::ostream& os, const TwitterData& data) 
{
    os << "UserName: " << data.getUserName() << ", ActualName: " << data.getActualName() 
       << ", Email: " << data.getEmail() << ", NumTweets: " << data.getNumTweets() 
       << ", Category: " << data.getCategory();
    return os;
}
