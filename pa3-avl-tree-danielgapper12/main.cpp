#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include "AVLTree.h" 
#include "CancerData.h"

using namespace std;

/*
° (2 pts) What is the worst-case Big-O of the insert()algorithm for the AVL tree? Explain.
The worst-case time complexity of insert() is O(log n) where n is the # of nodes. This is because AVL Trees have an insertion 
complexity of O(log n). They are able to achieve this since they remain balanced.

° (5 pts) What is the worst-case Big-O of the printInOrder()algorithm for the AVL tree? Explain.

The worst-case time complexity of printInOrder() is O(n). This is beacuse it traverses each node once so regardless of how 
it is stored it will need to go through each element, thus O(n).

° (3 pts) What is the worst-case Big-O of the findMax()algorithm for the AVL tree? Explain
The worst-case time complexity is O(log n) since the max value is stored in the furthest right leaf. To get here we need to go down 
each level which is log n away from the root. 

*/


void populateTreeFromFile(const string &filename, AVLTree<CancerData> &tree)
{
    ifstream file(filename);
    string line;
    while (getline(file, line)) 
    {
        istringstream iss(line);
        string countryName;
        string rateStr;
        float cancerRate;

        size_t lastSpace = line.find_last_of(' ');
        countryName = line.substr(0, lastSpace);
        rateStr = line.substr(lastSpace + 1);

        // removes non-digit chars (leaves decimal)
        rateStr.erase(remove_if(rateStr.begin(), rateStr.end(), [](char c) 
        { 
            return !std::isdigit(c) && c != '.'; 
        }), rateStr.end());

        // debugging with stod
        try {
            cancerRate = stof(rateStr); 
        } catch (const invalid_argument& e) 
        {
            cerr << "Invalid argument for stof conversion: " << rateStr << endl;
            continue; 
        } catch (const out_of_range& e) 
        {
            cerr << "Out of range error for stof conversion: " << rateStr << endl;
            continue; 
        }

        tree.insert(CancerData(countryName, cancerRate));
    }

}


void printMax(AVLNode<CancerData> *root, int rank)
{
    if (root != nullptr)
    {
        printMax(root->getRight(), rank);
        cout << rank << ", " << root->getData() << ", " << root->getData() << endl;
        rank++;
        printMax(root->getLeft(), rank);
    }
}

void reverseInOrderTraversal(AVLNode<CancerData>* node, int& count, int& rank, const string& label, int limit) 
{
    if (node == nullptr || count >= limit) 
    {
        return;
    }

    reverseInOrderTraversal(node->getRight(), count, rank, label, limit);

    if (count < limit) 
    {
        cout << label << ": " << rank << ". " << node->getData().getCountryName() << ". " << node->getData().getCancerRate() << endl;
        count++; 
        rank++;

        reverseInOrderTraversal(node->getLeft(), count, rank, label, limit);
    }
}


void printTopCountries(AVLTree<CancerData>& tree, const string& label, int count = 50) 
{
    int rank = 1;
    int processed = 0; // Counter to keep track of how many countries have been printed
    
    reverseInOrderTraversal(tree.getRoot(), processed, rank, label, count);
}


int main(void)
{
    AVLTree<CancerData> allPopulationsTree;
    AVLTree<CancerData> menCancerRatesTree;
    AVLTree<CancerData> womenCancerRatesTree;

    populateTreeFromFile("allcancerdata2018.csv", allPopulationsTree);
    populateTreeFromFile("mencancerdata2018.csv", menCancerRatesTree);
    populateTreeFromFile("womencancerdata2018.csv", womenCancerRatesTree);

    //  (2 pts) Listed 1 – 50 (from highest to lowest rate), the global cancer rates for all groups. The
    // output should be displayed on separate lines in the form:
    // o <label: rank number. country name. rate>, where label is “all”.
    printTopCountries(allPopulationsTree, "all");

    //  (2 pts) Listed 1 – 50 (from highest to lowest rate), the global cancer rates for men. The output
    // should be displayed on separate lines in the form:
    // o < label: rank number. country name. rate>, where label is “men”.
    printTopCountries(menCancerRatesTree, "men");


    //  (2 pts) Listed 1 – 50 (from highest to lowest rate), the global cancer rates for women. The
    // output should be displayed on separate lines in the form:
    // o < label: rank number. country name. rate>, where label is “women”
    printTopCountries(womenCancerRatesTree, "women");

    // (2 pts) Listed on 3 separate lines the 1st ranked country for the global cancer rates for all
    // groups. The output should be displayed on separate lines in the form:
    // o <label: rank number. country name. rate>, where label is “all.
    // 1st rank
    cout << "All Cancer Data Rank: 1. Country Name: " << allPopulationsTree.findMax().getCountryName() << ". Rate: " << allPopulationsTree.findMax().getCancerRate() << endl;
    cout << "Men Cancer Rank: 1. Country Name: " << menCancerRatesTree.findMax().getCountryName() << ". Rate: " << menCancerRatesTree.findMax().getCancerRate() << endl;
    cout << "Women Cancer Rank: 1. Country Name: " << womenCancerRatesTree.findMax().getCountryName() << ". Rate: " << womenCancerRatesTree.findMax().getCancerRate() << endl;
    

    //  (2 pts) Listed on 3 separate lines the 50th ranked country for the global cancer rates for all
    // groups. The output should be displayed on separate lines in the form:
    // o <label: rank number. country name. rate>, where label is “all”
    // 50th rank
    cout << "All Cancer Data Rank: 50. Country Name: " << allPopulationsTree.findMin().getCountryName() << ". Rate: " << allPopulationsTree.findMin().getCancerRate() << endl;
    cout << "Men Cancer Rank: 50. Country Name: " << menCancerRatesTree.findMin().getCountryName() << ". Rate: " << menCancerRatesTree.findMin().getCancerRate() << endl;
    cout << "Women Cancer Rank: 50. Country Name: " << womenCancerRatesTree.findMin().getCountryName() << ". Rate: " << womenCancerRatesTree.findMin().getCancerRate() << endl;
    


    return 0;
}