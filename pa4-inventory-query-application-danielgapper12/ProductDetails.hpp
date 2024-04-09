#pragma once

#include "HashTable.hpp"

using namespace std;

class ProductDetails
{
public:

     // Constructor
    ProductDetails(const string& Id, const string& name, const string& brand, const string& code, const string& cat,
                   const string& upcCode, const string& price, const string& sellingPrice, const string& qty,
                   const string& model, const string& about, const string& spec, const string& details,
                   const string& weight, const string& dimensions, const string& img, const string& vars,
                   const string& skuCode, const string& url, const string& stockStatus, const string& newDetails,
                   const string& dims, const string& col, const string& ing, const string& direction, 
                   const string& seller, const string& sizeQtyVar, const string& description)
        : uniqId(Id), productName(name), brandName(brand), asin(code), category(cat), upcEanCode(upcCode),
          listPrice(price), sellingPrice(sellingPrice), quantity(qty), modelNumber(model), aboutProduct(about),
          productSpecification(spec), technicalDetails(details), shippingWeight(weight), productDimensions(dimensions),
          image(img), variants(vars), sku(skuCode), productUrl(url), stock(stockStatus), details(newDetails),
          dimensions(dims), color(col), ingredients(ing), directionToUse(direction), isAmazonSeller(seller),
          sizeQuantityVariant(sizeQtyVar), productDescription(description)
    {}
    // Setters
    void setUniqId(const string& Id) { uniqId = Id; }
    void setProductName(const string& name) { productName = name; }
    void setBrandName(const string& name) { brandName = name; }
    void setAsin(const string& code) { asin = code; }
    void setCategory(const string& cat) { category = cat; }
    void setUpcEanCode(const string& code) { upcEanCode = code; }
    void setListPrice(const string& price) { listPrice = price; }
    void setSellingPrice(const string& price) { sellingPrice = price; }
    void setQuantity(const string& qty) { quantity = qty; }
    void setModelNumber(const string& number) { modelNumber = number; }
    void setAboutProduct(const string& about) { aboutProduct = about; }
    void setProductSpecification(const string& spec) { productSpecification = spec; }
    void setTechnicalDetails(const string& details) { technicalDetails = details; }
    void setShippingWeight(const string& weight) { shippingWeight = weight; }
    void setProductDimensions(const string& dimensions) { productDimensions = dimensions; }
    void setImage(const string& img) { image = img; }
    void setVariants(const string& vars) { variants = vars; }
    void setSku(const string& skuCode) { sku = skuCode; }
    void setProductUrl(const string& url) { productUrl = url; }
    void setStock(const string& stockStatus) { stock = stockStatus; }
    void setDetails(const string& newDetails) { details = newDetails; }
    void setDimensions(const string& dims) { dimensions = dims; }
    void setColor(const string& col) { color = col; }
    void setIngredients(const string& ing) { ingredients = ing; }
    void setDirectionToUse(const string& direction) { directionToUse = direction; }
    void setIsAmazonSeller(const string& seller) { isAmazonSeller = seller; }
    void setSizeQuantityVariant(const string& sizeQtyVar) { sizeQuantityVariant = sizeQtyVar; }
    void setProductDescription(const string& description) { productDescription = description; }

    // Getters
    string getUniqId() const { return uniqId; }
    string getProductName() const { return productName; }
    string getBrandName() const { return brandName; }
    string getAsin() const { return asin; }
    string getCategory() const { return category; }
    string getUpcEanCode() const { return upcEanCode; }
    string getListPrice() const { return listPrice; }
    string getSellingPrice() const { return sellingPrice; }
    string getQuantity() const { return quantity; }
    string getModelNumber() const { return modelNumber; }
    string getAboutProduct() const { return aboutProduct; }
    string getProductSpecification() const { return productSpecification; }
    string getTechnicalDetails() const { return technicalDetails; }
    string getShippingWeight() const { return shippingWeight; }
    string getProductDimensions() const { return productDimensions; }
    string getImage() const { return image; }
    string getVariants() const { return variants; }
    string getSku() const { return sku; }
    string getProductUrl() const { return productUrl; }
    string getStock() const { return stock; }
    string getDetails() const { return details; }
    string getDimensions() const { return dimensions; }
    string getColor() const { return color; }
    string getIngredients() const { return ingredients; }
    string getDirectionToUse() const { return directionToUse; }
    string getIsAmazonSeller() const { return isAmazonSeller; }
    string getSizeQuantityVariant() const { return sizeQuantityVariant; }
    string getProductDescription() const { return productDescription; }


private:
    string uniqId;
    string productName;
    string brandName;
    string asin;
    string category; 
    string upcEanCode;
    string listPrice;
    string sellingPrice;
    string quantity;
    string modelNumber; 
    string aboutProduct;
    string productSpecification;
    string technicalDetails;
    string shippingWeight;
    string productDimensions;
    string image;
    string variants;
    string sku;
    string productUrl;
    string stock;
    string details;
    string dimensions;
    string color;
    string ingredients;
    string directionToUse;
    string isAmazonSeller;
    string sizeQuantityVariant;
    string productDescription;
};
