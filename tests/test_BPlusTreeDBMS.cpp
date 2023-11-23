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







// Actual TEST cases 
TEST_F(test_BPlusTreeDBMS, TestSmallestKeyGeqV){

	std::string data = "test001";
	unsigned int level = 0;
	bool leaf = true; 
	unsigned int slots = 4; 

	int arr[ORDER_M] = {1,2,3,4};
	Node* children[ORDER_M + 1] = {NULL, NULL, NULL, NULL, NULL};
	Node myNode(data, level, leaf, slots, arr, children);

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

TEST_F(test_BPlusTreeDBMS, TestBPlusTreeDBMSFunc2){
    BPlusTreeDBMS myobj1;
    
    // ASSERT_EQ(15, myobj1.BPlusTreeDBMSFunc());
        
        
}

// TEST_F(test_BPlusTreeDBMS, TestBPlusTreeDBMSFunc3){
//     BPlusTreeDBMS myobj2;
    
//     ASSERT_NE(21, myobj2.BPlusTreeDBMSFunc(3));
        
        
// }