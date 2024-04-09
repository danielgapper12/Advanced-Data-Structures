#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <locale>


#include "HashTable.hpp"
#include "ProductDetails.hpp"
#include "CategoryMap.hpp"

using namespace std;


void getNextCsvField(stringstream& ss, string& outputField) 
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
            if (ss.peek() == '\"') 
            { 
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


void parseCSVAndInsertIntoHashTable(HashTable<string, ProductDetails>& hashTable) 
{
    ifstream file("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data.csv");
    string line;

    // skip header line
    getline(file, line);

    while (getline(file, line)) 
    {
        stringstream ss(line);
        string item;

        getline(ss, item, ','); // Uniq Id
        string uniqId = item; 

        string productName = "";
        getNextCsvField(ss, productName);
        
        string brandName = "";
        getNextCsvField(ss, brandName);

        string asin = "";
        getNextCsvField(ss, asin);

        string category = "";
        getNextCsvField(ss, category);

        string upcEanCode = "";
        getNextCsvField(ss, upcEanCode);

        string listPrice = "";
        getNextCsvField(ss, listPrice);

        string sellingPrice = "";
        getNextCsvField(ss, sellingPrice);

        string quantity = "";
        getNextCsvField(ss, quantity);

        string modelNumber = "";
        getNextCsvField(ss, modelNumber);

        string aboutProduct = "";
        getNextCsvField(ss, aboutProduct);

        string productSpecifications = ""; 
        getNextCsvField(ss, productSpecifications);

        string technicalDetails = "";
        getNextCsvField(ss, technicalDetails);

        string shippingWeight = "";
        getNextCsvField(ss, shippingWeight);
         
        string productDimensions = "";
        getNextCsvField(ss, productDimensions);

        string image = ""; 
        getNextCsvField(ss, image);

        string variants = "";
        getNextCsvField(ss, variants);

        string sku = "";
        getNextCsvField(ss, sku);

        string productURL = "";
        getNextCsvField(ss, productURL);

        string stock = "";
        getNextCsvField(ss, stock);

        string details = "";
        getNextCsvField(ss, details);

        string dimensions = "";
        getNextCsvField(ss, dimensions);

        string color = "";
        getNextCsvField(ss, color);

        string ingredients = "";
        getNextCsvField(ss, ingredients);

        string directionToUse = "";
        getNextCsvField(ss, directionToUse);
 
        string isAmazonSeller = "";
        getNextCsvField(ss, isAmazonSeller);

        string sizeQuantityVariant = "";
        getNextCsvField(ss, sizeQuantityVariant);

        string productDescription = "";
        getNextCsvField(ss, productDescription);


        // construct ProductDetails object
        ProductDetails productDetails(uniqId, productName, brandName, asin, category, upcEanCode, listPrice, 
            sellingPrice, quantity, modelNumber, aboutProduct, productSpecifications, technicalDetails, 
            shippingWeight, productDimensions, image, variants, sku, productURL, stock, details, 
            dimensions, color, ingredients, directionToUse, isAmazonSeller, sizeQuantityVariant, productDescription);

        // insert into hash table
        hashTable.insert(uniqId, productDetails);
    }
}

static inline void trim(string &s) 
{
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) 
    {
        return !isspace(ch);
    }));
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) 
    {
        return !isspace(ch);
    }).base(), s.end());
}

void parseCSVAndInsertIntoCategoryMap(CategoryMap& categoryMap) 
{
    ifstream file("marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data.csv");
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

void printProduct(const ProductDetails& productDetails)
{
    cout << "Product Name: " << productDetails.getProductName() << endl;
    cout << "Brand Name: " << productDetails.getBrandName() << endl;
    cout << "Asin: " << productDetails.getAsin() << endl;
    if (productDetails.getCategory() != "")
    {
        cout << "Category: " << productDetails.getCategory() << endl;
    } else{
        cout << "Category: NA"  << endl;
    }
    cout << "upcEanCode: " << productDetails.getUpcEanCode() << endl;
    cout << "List Price: " << productDetails.getListPrice() << endl;
    cout << "Selling Price: " << productDetails.getSellingPrice() << endl;
    cout << "Quantity: " << productDetails.getQuantity() << endl;
    cout << "Model Number: " << productDetails.getModelNumber() << endl;
    cout << "About Product: " << productDetails.getAboutProduct() << endl;
    cout << "Product Specifications: " << productDetails.getProductSpecification() << endl;
    cout << "Technical Details: " << productDetails.getTechnicalDetails() << endl;
    cout << "Shipping Weight: " << productDetails.getShippingWeight() << endl;
    cout << "Product Dimensions: " << productDetails.getProductDimensions() << endl;
    cout << "Image: " << productDetails.getImage() << endl;
    cout << "Variants: " << productDetails.getVariants() << endl;
    cout << "Sku: " << productDetails.getSku() << endl;
    cout << "Product URL: " << productDetails.getProductUrl() << endl;
    cout << "Stock: " << productDetails.getStock() << endl;
    cout << "Product Details: " << productDetails.getDetails() << endl;
    cout << "Dimensions: " << productDetails.getDimensions() << endl;
    cout << "Color: " << productDetails.getColor() << endl;
    cout << "Ingredients: " << productDetails.getIngredients() << endl;
    cout << "Direction To Use: " << productDetails.getDirectionToUse() << endl;
    cout << "Is Amazon Seller: " << productDetails.getIsAmazonSeller() << endl;
    cout << "Size Quantity Variant: " << productDetails.getSizeQuantityVariant() << endl;
    cout << "Product Description: " << productDetails.getProductDescription() << endl;
}

void printCategory(const string& category, const CategoryMap& categoryMap) 
{
    auto products = categoryMap.getProductsInCategory(category);

    if (!products.empty()) 
    {
        cout << "Products in category '" << category << "':" << endl;
        for (const auto& product : products) 
        {
            cout << "Product Name: " << product.getProductName() << endl;
            cout << "Product ID: " << product.getUniqId() << endl;
            cout << "--------------------------------" << endl;
        }
    } else {
        cout << "Invalid Category or no products found in '" << category << "' category." << endl;
    }
}

void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
}

bool validCommand(string line)
{
    return (line == ":help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}

void evalCommand(string line, CategoryMap& categoryMap, HashTable<string, ProductDetails> hashTable)
{
    if (line == ":help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {

        // Look up the appropriate datastructure to find if the inventory exist
        cout << "Line starts with find" << endl;

        string inventoryId = line.substr(5); // starts after find so at character 5
        auto productDetails = hashTable.find(inventoryId);

        cout << "uniqId: " << productDetails->getUniqId() << endl;
        if (productDetails != nullptr)
        {
            printProduct(*productDetails); 
        }
        else
        {
            cout << "Inventory/Product not found." << endl;
        }

    }
    // if line starts with listInventory
    else if (line.rfind("listInventory") == 0)
    {
        cout << "line starts with listInventory" << endl;
        string category = line.substr(14); // starts after listInventory so at character 14
        printCategory(category, categoryMap); 
    }
}

void bootStrap(CategoryMap& categoryMap, HashTable<string, ProductDetails> &hashTable)
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter :quit to exit. or :help to list supported commands." << endl;
    cout << "\n> ";
    // TODO: Do all your bootstrap operations here
    // example: reading from CSV and initializing the data structures
    // Don't dump all code into this single function
    // use proper programming practices
    
    parseCSVAndInsertIntoHashTable(hashTable);
    parseCSVAndInsertIntoCategoryMap(categoryMap);
}




int main(int argc, char const *argv[])
{
    string line;
    HashTable<string, ProductDetails> productHashTable(20011); 

    CategoryMap categoryMap;

    bootStrap(categoryMap, productHashTable);

    while (getline(cin, line) && line != ":quit")
    {
        if (validCommand(line))
        {
            evalCommand(line, categoryMap, productHashTable);
        }
        else
        {
            cout << "Command not supported. Enter :help for list of supported commands" << endl;
        }
        cout << "> ";
    }
    return 0;
}
