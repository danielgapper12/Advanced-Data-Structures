/*
Needed to run in replit.com since Mac had problems with omp.h!
*/


#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <locale>
#include <omp.h>
#include <sstream>
#include <string>
#include <time.h>
#include <math.h>

#include "CategoryMap.hpp"

using namespace std;

void getNextCsvField(stringstream &ss, string &outputField) 
{
  outputField.clear();
  char nextChar = ss.peek();

  if (nextChar == '\"') {
    // starts with "
    ss.get();
    string temp;
    bool isInsideQuotes = true;
    while (isInsideQuotes && getline(ss, temp, '\"')) 
    {
      // read until the next "
      outputField += temp;
      if (ss.peek() == '\"') {
        ss.get();
        outputField += "\"";
      } else {
        isInsideQuotes = false;
      }
    }
    getline(ss, temp, ',');
  } else {
    getline(ss, outputField, ',');
  }
}

static inline void trim(string &s) 
{
  s.erase(s.begin(), find_if(s.begin(), s.end(),
                             [](unsigned char ch) { return !isspace(ch); }));
  s.erase(find_if(s.rbegin(), s.rend(),
                  [](unsigned char ch) { return !isspace(ch); })
              .base(),
          s.end());
}

void parseCSVAndInsertIntoCategoryMap(CategoryMap &categoryMap) 
{
  ifstream file("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__"
                "10k_data.csv");
  if (!file.is_open()) 
  {
    cerr << "Failed to open file. " << endl;
    return;
  }

  string line;
  string temp;

  getline(file, line);

  while (getline(file, line)) 
  {
    stringstream ss(line);
    string item, uniqId, productName, category;

    // Uniq Id
    getNextCsvField(ss, uniqId);
    getNextCsvField(ss, productName);

    // skip 2 fields until reach Category
    for (int i = 0; i < 2; ++i) 
    {
      getNextCsvField(ss, temp);
    }

    // Category
    getNextCsvField(ss, category);

    // Split Category into individual categories based on "|"
    stringstream categoryStream(category);
    while (getline(categoryStream, item, '|')) 
    {
      trim(item);
      ProductSummary productSummary(uniqId, productName);
      categoryMap.addProductToCategory(item, productSummary);
    }
  }
}

void printCategory(const string &category, const CategoryMap &categoryMap) 
{
  auto products = categoryMap.getProductsInCategory(category);

  if (!products.empty()) 
  {
    cout << "Products in category '" << category << "':" << endl;
    for (const auto &product : products) {
      cout << "Product Name: " << product.getProductName() << endl;
      cout << "Product ID: " << product.getUniqId() << endl;
      cout << "--------------------------------" << endl;
    }
  } else {
    cout << "Invalid Category or no products found in '" << category
         << "' category." << endl;
  }
}

void printHelp() {
  cout << "Supported list of commands: " << endl;
  cout << " 1. listInventory <category_string> - Lists just the id and name of "
          "all inventory belonging to the specified category. If the category "
          "doesn't exists, prints 'Invalid Category'.\n"
       << endl;
  cout << "2. query - takes a product and list of categories and checks to see "
          "if that product is in any of the specified categories. If the "
          "product is in any of the categories"
       << endl;
}

bool validCommand(string line) {
  return (line == ":help") || (line.rfind("listInventory") == 0) ||
         (line.rfind("query") == 0);
}

bool getNextQueryField(stringstream &ss, string &outputField) 
{
  outputField.clear();
  char nextChar = ss.peek();

  if (nextChar == '\"')
  {
    // starts with "
    ss.get();
    string temp;
    bool isInsideQuotes = true;
    while (isInsideQuotes && getline(ss, temp, '\"')) 
    {
      // Read until the next "
      outputField += temp;
      if (ss.peek() == ',') 
      {
        ss.get();
        isInsideQuotes = false;
      }
    }
  } else {
    getline(ss, outputField, ',');
  }
  return !outputField.empty();
}


void searchProduct(const string &targetProduct, const CategoryMap &categoryMap,
                   const vector<string> &categories) {
  bool found = false;
  int numThreads = 0;
  do
    {
      cout << "How many threads do you want to use? " << endl;
      cin >> numThreads;
      if (numThreads < 1)
      {
        cout << "Invalid number of threads. Please enter a positive integer." << endl;
      } else if(numThreads > 8)
      {
        cout << "Invalid number of threads. Please enter a number less than or equal to 8." << endl;
      }
    } while (numThreads < 1 || numThreads > 8);
  omp_set_num_threads(numThreads);  
  cout << "Using " << omp_get_max_threads() << " threads." << endl;

  #pragma omp parallel shared(found)
  {
    vector<ProductSummary> products;
    bool local_found = false;
    
    // start the timer
    double time = omp_get_wtime();
    
    #pragma omp for
    for (int i = 0; i < categories.size(); i++) // loops through each entered category
    {
      if (found) continue;  // Check the global found flag before processing

      int tid = omp_get_thread_num();

      products = categoryMap.getProductsInCategory(categories[i]);

      for (int j = 0; j < products.size() && !local_found; j++) // loops through each product in the category
      {
        if (products[j].getProductName() == targetProduct) 
        {
          local_found = true;

          #pragma omp critical
          {
            found = true;  // Set the global flag to prevent race condition
            
            cout << "Thread " << tid << " found " << targetProduct << " in category number " << i+1 << " called: " << categories[i] << endl;
            i = categories.size();
            time = omp_get_wtime() - time;
            cout << time << " seconds" << endl;
          }
          break;  // exits inner loop
        }
      }
    }
  }

  if (!found) 
  {
    cout << targetProduct << " not found." << endl;
  } 
}



void evalCommand(string line, CategoryMap &categoryMap) {
  if (line == ":help") {
    printHelp();
  } else if (line.rfind("listInventory") == 0) 
  {
    string category = line.substr(14); // starts after listInventory so at character 14
    printCategory(category, categoryMap);
  } else if (line.rfind("query") == 0) 
  {
    stringstream iss(line.substr(6)); // skip "query," part
    string productName, category;
    vector<string> categories;

    // Get the first field as productName
    getNextCsvField(iss, productName);

    // Continue to get each subsequent field as category
    while (getNextQueryField(iss, category)) 
    {
      if (!category.empty()) 
      {
        categories.push_back(category);
      }
    }

    cout << "Product Name: " << productName << endl;
    int i = 1;
    for (const string &cat : categories) 
    {
      cout << "Category " << i << ": " << cat << endl;
      i++;
    }

    searchProduct(productName, categoryMap, categories);
  }
}

void bootStrap(CategoryMap &categoryMap) {
  cout << "\n Welcome to Amazon Inventory Query System" << endl;
  cout << " enter :quit to exit. or :help to list supported commands." << endl;
  cout << "\n> ";
  // TODO: Do all your bootstrap operations here
  // example: reading from CSV and initializing the data structures
  // Don't dump all code into this single function
  // use proper programming practices

  parseCSVAndInsertIntoCategoryMap(categoryMap);
}

int main(int argc, char const *argv[]) {
  string line;

  CategoryMap categoryMap;

  bootStrap(categoryMap);

  while (getline(cin, line) && line != ":quit") {
    if (validCommand(line)) {
      evalCommand(line, categoryMap);
    } else {
      cout
          << "Command not supported. Enter :help for list of supported commands"
          << endl;
    }
    cout << "> ";
  }
  return 0;
}
