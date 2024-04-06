/*
What is a move constructor?
A move constructor is similar to a copy constructor except a copy constructor copies the actual data and a move 
constructor instead work with r-value references and move semantics which means it points to an already existing
object in the memory. Move constructors are more efficient than using several iterations of a copy constructor
and are used to move resources in the heap by using pointers to point to the data instead of copying it.

What is a move assignment operator?
A move assignment operator is similar to a copy assignment operator, but instead of copying the data it just
moves the ownership of the data to the new object. It uses the && reference qualifier and is more efficient as
it doesn't create extra copies of each piece of data.

What is the time complexity (Big-O) in the worst-case for the BST::empty() algorithm? Explain.
The worst-case time complexity for empty()would be O(1) for worst case since it only needs to check the root of empty(). 
Since it has access to the root the size doesn't matter and the worst case will still be O(1).

What is the time complexity (Big-O) in the worst-case for the BST::add() algorithm? Explain.
The worst-case time complexity for add() would be O(N) since the BST is stored as a singly linkedlist and it
will need to iterate through all of it to get to the leaf where it will be added. This would be different
if the BST was sorted.

What is the time complexity (Big-O) in the worst-case for the BST::makeEmpty () algorithm? Explain.
The worst-case time complexity for makeEmpty() would also be O(N) since the functions needs to iterate once
through the entire BST to make it empty.

What is the time complexity (Big-O) in the worst-case for the BST::printLevelOrder () algorithm? Explain.
The worst-case time complexity for printLevelOrder() would be O(N) as well as this function also needs to 
iterate through the entire BST once printing.

What is the time complexity (Big-O) in the worst-case for the BST::cloneTree () algorithm? Explain.
The worst-case time complexity for cloneTree() is also O(N) since similar to the makeEmpty() function, it needs to 
visit each node once and the work done at each node is constant time. 

*/

#include <iostream>
#include "BST.h" 

int main(){

	/* MA TODO: Implement */
	/* Create a BST string tree (bst_test) ; add the following string values to the bst_test in order: "C", "p", "t", "s", "2", "3" , "B", "S", "T"*/
	BST<string> bst_test = {"C", "p", "t", "s", "2", "3" , "B", "S", "T"}; 

	/* MA TODO: Implement */
	// Test1: Test printLevelOrder()
	/* Print the tree you created using
	    a. In-order print
	    a. Level-order print
	    a. Post-order print
	    a. Pre-order print */
	bst_test.printInOrder();
	bst_test.printLevelOrder();
	bst_test.printPostOrder();
	bst_test.printPreOrder();


	/* MA TODO: Implement */
	// Test2: Test copy constructor -1
	/* Create a new BST tree (bst_copy1) ; initialize bst_copy1 with 'bst_test's data, using the copy constructor */
	/* Test condition: Check if the size of bst_copy1 is same as bst_test; and  bst_copy1 contains the values "B", "S", "T" 
	    * if so, print the mesaage: "Copy constructor test-1 passed!"";
		* else *print the message: "Copy constructor test-1 failed!"" and print both bst_test and bst_copy1 using level order print.*/
	BST<string> bst_copy1(bst_test);
    if (bst_copy1.size() == bst_test.size() && bst_copy1.contains("B") && bst_copy1.contains("S") && bst_copy1.contains("T")) 
	{
        cout << "Copy constructor test-1 passed!" << endl;
    } else {
        cout << "Copy constructor test-1 failed!" << endl;
        cout << "Original BST in level order: ";
        bst_test.printLevelOrder();
        cout << "Copied BST in level order: ";
        bst_copy1.printLevelOrder();
    }


	/* MA TODO: Implement */
	// Test3: Test copy constructor - 2
	/* Update one of the strings in bst_copy1 tree using the following statement:  */
	   // bst_copy1.getNode("B")->setValue("A");
	/* Assuming copy constructor does a deep copy, the above statement should update bst_copy1 only, and not bst_test. */
	/* Test condition: 
	    * if bst_test contains "B" and it doesn't contain "A", test passes. Print the message: "Copy constructor test-2 passed!"";
		* else *print the message: "Copy constructor test-2 failed!"" and print bst_test using level order print.*/
	bst_copy1.getNode("B")->setValue("A");
    if (bst_test.contains("B") && !bst_test.contains("A")) 
	{
        cout << "Copy constructor test-2 passed!" << endl;
    } else {
        cout << "Copy constructor test-2 failed!" << endl;
        cout << "Original BST in level order: ";
        bst_test.printLevelOrder();
    }
	


	/* MA TODO: Implement */
	// Test4: Test copy assignment
	/* Create a new BST tree (bst_copy2) ; initialize bst_copy2 with 'bst_test's data, using the copy assignment operator. */
	/* Test condition: Check if the size of bst_copy2 is same as bst_test and  bst_copy2 contains the values "B", "S", "T" 
	    * if so, print the mesaage: "Copy assignment operator test passed!"";
		* else *print the message: "Copy assignment operator test failed!"" and print both bst_test and bst_copy2 using level order print.*/
	BST<string> bst_copy2;
    bst_copy2 = bst_test;
    if (bst_copy2.size() == bst_test.size() && bst_copy2.contains("B") && bst_copy2.contains("S") && bst_copy2.contains("T")) 
	{
        cout << "Copy assignment operator test passed!" << endl;
    } else {
        cout << "Copy assignment operator test failed!" << endl;
        cout << "Original BST in level order: ";
        bst_test.printLevelOrder();
        cout << "Copied BST in level order: ";
        bst_copy2.printLevelOrder();
    }


	/* MA TODO: Implement */
	// Test5: Test move constructor
	/* Create a new BST tree (bst_move1) ; initialize bst_move1 with 'bst_test's data, using the move constructor */
	/* Test condition: Check if the size of bst_move1 is 9 and  bst_move1 contains the values "B", "S", "T", and bst_test is empty (use the empty() function of BST to check if bst_test is empty.).  
	    * if so, print the mesaage: "Move constructor test passed!"";
		* else *print the message: "Move constructor test failed!"" and print bst_move1 using level order print.*/

	// having issues with "std::move"
	BST<string> bst_move1(std::move(bst_test));

    if (bst_move1.size() == 9 && bst_move1.contains("B") && bst_move1.contains("S") && bst_move1.contains("T") && bst_test.empty()) 
	{
        cout << "Move constructor test passed!" << endl;
    } else {
        cout << "Move constructor test failed!" << endl;
        cout << "Moved BST in level order: ";
        bst_move1.printLevelOrder();
    }

	


	/* MA TODO: Implement */
	// Test6: Test move assignment 
	/* Create a new BST tree (bst_move2) ; initialize bst_move2 with rvalue BST<string>({"B","S","T"}), using the move assignment operator */
	/* Test condition: Check if the size of bst_move2 is 3 and  bst_move2 contains the values "B", "S", "T". 
	    * if so, print the mesaage: "Move assignment operator test passed!"";
		* else *print the message: "Move assignment operator test failed!"" and print  bst_move2  using level order print.*/
	BST<string> bst_move2 = BST<string>({"B", "S", "T"});
    if (bst_move2.size() == 3 && bst_move2.contains("B") && bst_move2.contains("S") && bst_move2.contains("T")) 
	{
        cout << "Move assignment operator test passed!" << endl;
    } else {
        cout << "Move assignment operator test failed!" << endl;
        cout << "Moved BST, here printed in level order: ";
        bst_move2.printLevelOrder();
    }

	return 0;
}