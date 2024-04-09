#pragma once

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


class ProductSummary 
{
public:
    ProductSummary(const string& id, const string& name) 
        : uniqId(id), productName(name) {}
        
    string getUniqId() const 
    {
        return uniqId;
    }
    string getProductName() const 
    {
        return productName;
    }

private:
    string uniqId;
    string productName;
};

class CategoryMap 
{
public:
    void addProductToCategory(const string& category, const ProductSummary& product) 
    {
        categoryMap[category].push_back(product);
    }

    vector<ProductSummary> getProductsInCategory(const string& category) const 
    {
        auto it = categoryMap.find(category);
        if (it != categoryMap.end()) {
            return it->second;
        } else {
            return vector<ProductSummary>(); 
        }
    }

    bool categoryExists(const string& category) const 
    {
        return categoryMap.find(category) != categoryMap.end();
    }

    auto end() const {
        return categoryMap.end();
    }

private:
    unordered_map<string, vector<ProductSummary>> categoryMap;
};

