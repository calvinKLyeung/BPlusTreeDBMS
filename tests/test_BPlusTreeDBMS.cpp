// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include "../code/BPlusTreeDBMS.h"
#include "../code/BPlusTree.h"
#include "../code/Node.h"

#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include <ctime>
#include <cmath>

#define private public
using namespace std;


class test_BPlusTreeDBMS : public ::testing::Test {

// Grade calculation
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		// std::ofstream outgrade("./total_grade.txt");
		// if(outgrade.is_open()){
		// 	outgrade.clear();
		// 	outgrade << (int)0;
		// 	outgrade.close();
		// }
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		// std::ofstream outgrade("./total_grade.txt");
		// if(outgrade.is_open()){
		// 	outgrade.clear();
		// 	outgrade << (int)std::ceil(100*total_grade/max_grade);
		// 	outgrade.close();
		// 	std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		// }
	}

	void add_points_to_grade(double points){
		// if(!::testing::Test::HasFailure()){
		// 	total_grade += points;
		// }
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		// std::ofstream outgrade("./total_grade.txt");
		// if(outgrade.is_open()){
		// 	outgrade.clear();
		// 	outgrade << (int)std::ceil(100*total_grade/max_grade);
		// 	outgrade.close();
		// }
	}
	
	// static double total_grade;
	// static double max_grade;
};





// Global variable for Testing 
Node* NodeTracker[ORDER_M + 1] = {NULL};
Node* GlobalRoot = NULL;

// function declarations 
BPlusTree* mkBPlusTree();





// Actual TEST cases 
TEST_F(test_BPlusTreeDBMS, TestSmallestKeyGeqV){

	// std::string data = "test001";
	// unsigned int level = 0;
	// bool leaf = true; 
	// unsigned int slots = 4; 
	int arr[ORDER_M] = {1,2,3,4};
	Node myNode("test001", 0, true, 4, arr);
	BPlusTree myBPlusTree; 

	cout << "i should be 0: " << myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 1) << endl;
	ASSERT_EQ(0, myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 1));

	cout << "i should be 1: " << myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 2) << endl;
	ASSERT_EQ(1, myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 2));

	cout << "i should be -1: " << myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 12) << endl;
	ASSERT_EQ(-1, myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 12));

	cout << "i should be 3: " << myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 4) << endl;
	ASSERT_NE(4, myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 4));


	// Node(std::string _data, unsigned int _level, bool _leaf, unsigned int _slots, int _keys[ORDER_M], Node* _children[ORDER_M + 1]);

	// ASSERT_EQ(0, myobj.BPlusTreeDBMSFunc());
	// cout << "!!!!!!!!!!!" << endl; 
	// ASSERT_EQ(1, myobj.BPlusTreeDBMSFunc());
	// cout << "~~~~~~~~~" << endl; 

	// ASSERT_FALSE(myobj.test_false());

	// ASSERT_TRUE(myobj.test_true());




        
}

TEST_F(test_BPlusTreeDBMS, TestBPlusTreeFind){
    BPlusTree* myBPlusTree = mkBPlusTree();

	cout << "Checking if 16 is found in myNodeLeft" << endl; 
	
	
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	Node* found_node = myBPlusTree->find(16);
	cout << "=============================================" << endl;
	cout << found_node << endl;
	cout << "What is in found_node" << endl;
	for (unsigned int i=0; i<ORDER_M; ++i)
	{
		cout << found_node->accessKeysArray()[i] << endl; 
	}
	cout << "What is in NodeTracker[0]" << endl;
	for (unsigned int i=0; i<ORDER_M; ++i)
	{
		cout << NodeTracker[1]->accessKeysArray()[i] << endl; 
	}


	// ASSERT_EQ(NodeTracker[0], myBPlusTree->find(2)); 
	ASSERT_EQ(NodeTracker[1], myBPlusTree->find(16)); 
	ASSERT_EQ(NodeTracker[2], myBPlusTree->find(20)); 
	ASSERT_EQ(NodeTracker[3], myBPlusTree->find(27)); 
	ASSERT_EQ(NodeTracker[4], myBPlusTree->find(39)); 

	ASSERT_NE(NodeTracker[4], myBPlusTree->find(7)); 
	ASSERT_NE(NodeTracker[3], myBPlusTree->find(14)); 
	ASSERT_NE(NodeTracker[2], myBPlusTree->find(30)); 
	ASSERT_NE(NodeTracker[1], myBPlusTree->find(13)); 
	ASSERT_NE(NodeTracker[0], myBPlusTree->find(17)); 

    
	for (unsigned int i=0; i<5; ++i)
	{
		delete NodeTracker[i];
	}
	delete GlobalRoot;
	delete myBPlusTree;
}

// TEST_F(test_BPlusTreeDBMS, TestBPlusTreeDBMSFunc3){
//     BPlusTreeDBMS myobj2;
    
//     ASSERT_NE(21, myobj2.BPlusTreeDBMSFunc(3));
        
        
// }



// Helper functions 
BPlusTree* mkBPlusTree()
{
	// Test BPlusTree Reference: https://web.stanford.edu/class/cs346/2015/notes/Blink.pdf
	BPlusTree* myBPlusTree = new BPlusTree; 
	

	// instantiations 
	// Root 
	int arr[ORDER_M] = {13, 17, 24, 30};
	Node* myNodeRoot = new Node("root", 0, false, 4, arr);

	// children nodes 
	int arr1[ORDER_M] = {2, 3, 5, 7};
	Node* myNodeLeft = new Node("left", 1, true, 4, arr1);

	int arr2[ORDER_M] = {14, 16};
	Node* myNodeMid1 = new Node("mid1", 1, true, 2, arr2);

	int arr3[ORDER_M] = {19, 20, 22};
	Node* myNodeMid2 = new Node("mid2", 1, true, 3, arr3);

	int arr4[ORDER_M] = {24, 27, 29};
	Node* myNodeMid3 = new Node("mid3", 1, true, 3, arr4);

	int arr5[ORDER_M] = {33, 34, 38, 39};
	Node* myNodeRight = new Node("right", 1, true, 4, arr5);

	// connect between Leaf nodes 

	// set Left
	myNodeLeft->setNext(myNodeMid1);
	// set Mid1 
	myNodeMid1->setPrev(myNodeLeft);
	myNodeMid1->setNext(myNodeMid2);
	// set Mid2
	myNodeMid2->setPrev(myNodeMid1);
	myNodeMid2->setNext(myNodeMid3);
	// set Mid3 
	myNodeMid3->setPrev(myNodeMid2);
	myNodeMid3->setNext(myNodeLeft);
	// set Left
	myNodeRight->setPrev(myNodeMid3);

	// set Root's children 
	myNodeRoot->accessChildren()[0] = myNodeLeft;
	myNodeRoot->accessChildren()[1] = myNodeMid1;
	myNodeRoot->accessChildren()[2] = myNodeMid2;
	myNodeRoot->accessChildren()[3] = myNodeMid3;
	myNodeRoot->accessChildren()[4] = myNodeRight;

	// set Root 
	myBPlusTree->setRoot(myNodeRoot);


	// Global NodeTrackerForTesting
	GlobalRoot = myNodeRoot;
	NodeTracker[0] = myNodeLeft;
	NodeTracker[1] = myNodeMid1;
	NodeTracker[2] = myNodeMid2;
	NodeTracker[3] = myNodeMid3;
	NodeTracker[4] = myNodeRight;


	return myBPlusTree; 
}


