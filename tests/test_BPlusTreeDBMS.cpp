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
Node* GlobalNodeTracker1[ORDER_M + 1] = {NULL};
Node* GlobalRoot1 = NULL;

Node* GlobalNodeTracker2[8] = {NULL};
Node* GlobalRoot2 = NULL;

// function declarations 
BPlusTree* mkBPlusTree1();
BPlusTree* mkBPlusTree2();

bool BPlusTreeInvariantChecker();





// Actual TEST cases 
TEST_F(test_BPlusTreeDBMS, TestBPlusTree_IndexOfKiSmallestKeyGeqV){

	// std::string data = "test001";
	// unsigned int level = 0;
	// bool leaf = true; 
	// unsigned int slots = 4; 
	int arr_keys[ORDER_M] = {1,2,3,4};
	std::string arr_values[ORDER_M] = {"one", "two", "three", "four"};

	Node myNode("test001", 0, true, 4, arr_keys, arr_values);
	BPlusTree myBPlusTree_IndexOfKiSmallestKeyGeqV; 

	// cout << "i should be 0: " << myBPlusTree.IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(&myNode, 1) << endl;
	ASSERT_EQ(0, myBPlusTree_IndexOfKiSmallestKeyGeqV.IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(&myNode, 1));

	// cout << "i should be 1: " << myBPlusTree.IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(&myNode, 2) << endl;
	ASSERT_EQ(1, myBPlusTree_IndexOfKiSmallestKeyGeqV.IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(&myNode, 2));

	// cout << "i should be -1: " << myBPlusTree.IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(&myNode, 12) << endl;
	ASSERT_EQ(-1, myBPlusTree_IndexOfKiSmallestKeyGeqV.IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(&myNode, 12));

	// cout << "i should be 3: " << myBPlusTree.IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(&myNode, 4) << endl;
	ASSERT_NE(4, myBPlusTree_IndexOfKiSmallestKeyGeqV.IndexOfSmallestKeyInCurrNodeGreaterThanOrEqualToGivenKey(&myNode, 4));


	// Node(std::string _data, unsigned int _level, bool _leaf, unsigned int _slots, int _keys[ORDER_M], Node* _children[ORDER_M + 1]);

	// ASSERT_EQ(0, myobj.BPlusTreeDBMSFunc());
	// cout << "!!!!!!!!!!!" << endl; 
	// ASSERT_EQ(1, myobj.BPlusTreeDBMSFunc());
	// cout << "~~~~~~~~~" << endl; 

	// ASSERT_FALSE(myobj.test_false());

	// ASSERT_TRUE(myobj.test_true());




        
}

TEST_F(test_BPlusTreeDBMS, TestBPlusTree_Find){
    BPlusTree* myBPlusTree_Find = mkBPlusTree1();

	
	
	// Node* found_node = myBPlusTree_Find->Find(16);
	// cout << found_node << endl;
	// cout << "What is in found_node" << endl;
	// for (unsigned int i=0; i<ORDER_M; ++i)
	// {
	// 	cout << found_node->accessKeys()[i] << endl; 
	// }
	// cout << "What is in GlobalNodeTracker1[0]" << endl;
	// for (unsigned int i=0; i<ORDER_M; ++i)
	// {
	// 	cout << GlobalNodeTracker1[1]->accessKeys()[i] << endl; 
	// }


	// ASSERT_EQ(GlobalNodeTracker1[0], myBPlusTree->Find(2)); 
	ASSERT_EQ(GlobalNodeTracker1[1], myBPlusTree_Find->Find(16)); 
	ASSERT_EQ(GlobalNodeTracker1[2], myBPlusTree_Find->Find(20)); 
	ASSERT_EQ(GlobalNodeTracker1[3], myBPlusTree_Find->Find(27)); 
	ASSERT_EQ(GlobalNodeTracker1[4], myBPlusTree_Find->Find(39)); 

	ASSERT_NE(GlobalNodeTracker1[4], myBPlusTree_Find->Find(7)); 
	ASSERT_NE(GlobalNodeTracker1[3], myBPlusTree_Find->Find(14)); 
	ASSERT_NE(GlobalNodeTracker1[2], myBPlusTree_Find->Find(30)); 
	ASSERT_NE(GlobalNodeTracker1[1], myBPlusTree_Find->Find(13)); 
	ASSERT_NE(GlobalNodeTracker1[0], myBPlusTree_Find->Find(17)); 

    
	// for (unsigned int i=0; i<ORDER_M; ++i)
	// {
	// 	delete GlobalNodeTracker1[i];
	// }
	// delete GlobalRoot1;
	// delete myBPlusTree_Find;
}



TEST_F(test_BPlusTreeDBMS, TestBPlusTree_FindRange){

	BPlusTree* myBPlusTree_FindRange = mkBPlusTree1();

	std::vector <Node *> resultSet = myBPlusTree_FindRange->FindRange(15, 28);

	// for(auto node : resultSet) 
	// {
	// 	cout << "The Adress of the node in Result Set is:" << endl; 
  	// 	cout << node << endl; 
	// 	for (unsigned int i=0; i<node->getSlots(); ++i)
	// 	{
	// 		cout << node->accessKeys()[i] << " "; 
	// 	}
	// 	cout << endl; 
	// }   

	// for (unsigned int i=0; i<resultSet.size(); ++i)
	// {
	// 	cout << GlobalNodeTracker1[i+1] << " SHOULD BE THE SAME ADRESS AS " << resultSet[i] << endl; 
	// }


	ASSERT_EQ(GlobalNodeTracker1[1], resultSet[0]); 
	ASSERT_EQ(GlobalNodeTracker1[2], resultSet[1]); 
	ASSERT_EQ(GlobalNodeTracker1[3], resultSet[2]); 

	for (auto node : resultSet)
	{
		ASSERT_NE(GlobalNodeTracker1[0], node); 
	}
	for (auto node : resultSet)
	{
		ASSERT_NE(GlobalNodeTracker1[4], node); 
	}


    
	// for (unsigned int i=0; i<ORDER_M; ++i)
	// {
	// 	delete GlobalNodeTracker1[i];
	// }
	// delete GlobalRoot1;
	// delete myBPlusTree_FindRange;
        
        
}


TEST_F(test_BPlusTreeDBMS, TestBPlusTree_InsertInLeaf){

	// TESTing key < keys[0]
	BPlusTree* myBPlusTree_InsertInLeaf = mkBPlusTree1();
	int arr_keys[] = {5, 8};
	std::string arr_values[] = {"five", "eight"};
	Node* Leaf_Example = new Node("test_leaf", 0, true, 2, arr_keys, arr_values);
	
	// for (unsigned int i=0; i < Leaf_Example->getSlots(); ++i)
	// {
	// 	cout << Leaf_Example->accessKeys()[i] << endl;
	// }	

	myBPlusTree_InsertInLeaf->InsertInLeaf(Leaf_Example, 4, "four");

	// for (unsigned int i=0; i<Leaf_Example->getSlots(); ++i)
	// {
	// 	cout << Leaf_Example->accessKeys()[i] << endl;
	// }	

	ASSERT_TRUE(Leaf_Example->accessKeys()[0] == 4);
	ASSERT_TRUE(Leaf_Example->accessKeys()[1] == 5);
	ASSERT_TRUE(Leaf_Example->accessKeys()[2] == 8);

	ASSERT_TRUE(Leaf_Example->accessValues()[0] == "four");
	ASSERT_TRUE(Leaf_Example->accessValues()[1] == "five");
	ASSERT_TRUE(Leaf_Example->accessValues()[2] == "eight");

	delete Leaf_Example;




	// // TESTing key insert in the middle 
	BPlusTree* myBPlusTree_InsertInLeaf_1 = mkBPlusTree1();
	int arr_keys1[] = {5, 8};
	std::string arr_values1[] = {"five", "eight"};
	Node* Leaf_Example1 = new Node("test_leaf", 0, true, 2, arr_keys1, arr_values1);

	cout << endl; 
	for (unsigned int i=0; i<Leaf_Example1->getSlots(); ++i)
	{
		cout << Leaf_Example1->accessKeys()[i] << " : " << Leaf_Example1->accessValues()[i] << " " << endl;
	}
	cout << endl;
	
	// for (unsigned int i=0; i < Leaf_Example1->getSlots(); ++i)
	// {
	// 	cout << Leaf_Example1->accessKeys()[i] << endl;
	// }	
	cout << "INSERTING 7 and seven to singl Leaf Node for testing " << endl; 
	myBPlusTree_InsertInLeaf_1->InsertInLeaf(Leaf_Example1, 7, "seven");

	cout << "What is in  Leaf_Example1 after INSERTING 7 : seven?" << endl; 
	for (unsigned int i=0; i<Leaf_Example1->getSlots(); ++i)
	{
		cout << Leaf_Example1->accessKeys()[i] << " : " << Leaf_Example1->accessValues()[i] << " " << endl;
	}
	cout << endl;


	// for (unsigned int i=0; i<Leaf_Example1->getSlots(); ++i)
	// {
	// 	cout << Leaf_Example1->accessKeys()[i] << endl;
	// }	

	ASSERT_TRUE(Leaf_Example1->accessKeys()[0] == 5);
	ASSERT_TRUE(Leaf_Example1->accessKeys()[1] == 7);
	ASSERT_TRUE(Leaf_Example1->accessKeys()[2] == 8);

	cout << "What is in Leaf_Example->accessValues()[0]???" << endl;
	cout << Leaf_Example->accessValues()[0] << endl; 

	ASSERT_TRUE(Leaf_Example1->accessValues()[0] == "five");
	ASSERT_TRUE(Leaf_Example1->accessValues()[1] == "seven");
	ASSERT_TRUE(Leaf_Example1->accessValues()[2] == "eight");
	delete Leaf_Example1;





	// // TESTing key insert at the END
	BPlusTree* myBPlusTree_InsertInLeaf_2 = mkBPlusTree1();
	int arr_keys2[] = {5, 8};
	std::string arr_values2[] = {"five", "eight"};
	Node* Leaf_Example2 = new Node("test_leaf", 0, true, 2, 
        arr_keys2, arr_values2);
	
	for (unsigned int i=0; i < Leaf_Example2->getSlots(); ++i)
	{
		cout << Leaf_Example2->accessKeys()[i] << endl;
	}	

	myBPlusTree_InsertInLeaf_2->InsertInLeaf(Leaf_Example2, 9, "nine");

	for (unsigned int i=0; i<Leaf_Example2->getSlots(); ++i)
	{
		cout << Leaf_Example2->accessKeys()[i] << endl;
	}	

	ASSERT_TRUE(Leaf_Example2->accessKeys()[0] == 5);
	ASSERT_TRUE(Leaf_Example2->accessKeys()[1] == 8);
	ASSERT_TRUE(Leaf_Example2->accessKeys()[2] == 9);

	ASSERT_TRUE(Leaf_Example2->accessValues()[0] == "five");
	ASSERT_TRUE(Leaf_Example2->accessValues()[1] == "eight");
	ASSERT_TRUE(Leaf_Example2->accessValues()[2] == "nine");

	delete Leaf_Example2;




}





TEST_F(test_BPlusTreeDBMS, TestBPlusTree_GetParentNode){

	BPlusTree* myBPlusTree_GetParentNode = mkBPlusTree1();

	Node* Random_N = new Node();


	ASSERT_EQ(NULL, myBPlusTree_GetParentNode->getParentNode(Random_N));

	for (unsigned int i = 0; i < ORDER_M; ++i)
	{
		ASSERT_EQ(GlobalRoot1, myBPlusTree_GetParentNode->getParentNode(GlobalNodeTracker1[i]));
	}
	


    // delete Random_N;
	// for (unsigned int i=0; i<ORDER_M; ++i)
	// {
	// 	delete GlobalNodeTracker1[i];
	// }
	// delete GlobalRoot1;
	// delete myBPlusTree_GetParentNode;
        
        
}


TEST_F(test_BPlusTreeDBMS, TestBPlusTree_InsertInInternalNode)
{
	BPlusTree* myBPlusTree_InsertInInternalNode = mkBPlusTree2();
	Node* P = myBPlusTree_InsertInInternalNode->getParentNode(GlobalNodeTracker2[4]);
	ASSERT_TRUE(P == GlobalNodeTracker2[0]);

	Node* N = GlobalNodeTracker2[4];

	int arr_keys[] = {17, 18}; 
	std::string arr_values[] = {"seventeen", "eighteen"};
	Node* NPrime = new Node("NPrime", 2, true, 2, arr_keys, arr_values);

	int KPrime = NPrime->accessKeys()[0];


	myBPlusTree_InsertInInternalNode->InsertInInternalNode(P, N, KPrime, NPrime);

	// cout << "CURRENT P->accessKeys()[2]: " << P->accessKeys()[2] << endl; 
	// cout << P->accessChildren()[3] << " Should be the same address as " << NPrime << endl;

	ASSERT_EQ(P->accessChildren()[3], NPrime);

	// cout << P->accessChildren()[3]->accessKeys()[0] << endl; 
	// cout << P->accessChildren()[3]->accessKeys()[1] << endl; 

	// cout << "====================" << endl; 

	// cout << NPrime->accessKeys()[0] << endl; 
	// cout << NPrime->accessKeys()[1] << endl; 


	// delete NPrime; 

	// for (unsigned int i=0; i<8; ++i)
	// {
	// 	delete GlobalNodeTracker2[i];
	// }
	// delete GlobalRoot2;
	// delete myBPlusTree_InsertInInternalNode;

}



// Global variables for Testing 
Node* GlobalInsert[20] = {NULL};
Node* GlobalInsertRoot = NULL;

TEST_F(test_BPlusTreeDBMS, TestBPlusTree_Insert)
{
	// Version 0 BPlusTree test 

	BPlusTree* myBPlusTree_Insert = mkBPlusTree1();

	cout << "Checking what is in Root Node BEFORE INSERT: " << endl; 
	for (unsigned int i=0; i<GlobalRoot1->getSlots(); ++i)
	{
		cout <<	GlobalRoot1->accessKeys()[i] << " " ;
	}
	cout << endl;

	bool inserted = myBPlusTree_Insert->Insert(8, "eight");

	cout << "Insert successfully? " << std::boolalpha << inserted << endl;

	// Node* newLeafNode = myBPlusTree_Insert->Find(8);








	// cout << "Checking what is in Root Node: " << endl; 
	Node* myRootNode = myBPlusTree_Insert->getRootNode();
	// for (unsigned int i=0; i<myRootNode->getSlots(); ++i)
	// {
	// 	cout <<	myRootNode->accessKeys()[i] << " " ;
	// }
	// cout << endl;
	ASSERT_EQ(myRootNode->accessKeys()[0], 17);
	ASSERT_EQ(myRootNode->getSlots(), 1);


	// cout << "Checking what is in Left Internal node Child Pointer of Root Node: " << endl; 
	// for (unsigned int i=0; i<myRootNode->accessChildren()[0]->getSlots(); ++i)
	// {
	// 	cout <<	myRootNode->accessChildren()[0]->accessKeys()[i] << " " ;
	// }
	// cout << endl;
	ASSERT_EQ(myRootNode->accessChildren()[0]->getKeyByIndex(0), 5);
	ASSERT_EQ(myRootNode->accessChildren()[0]->getKeyByIndex(1), 13);
	ASSERT_EQ(myRootNode->accessChildren()[0]->getSlots(), 2);



	// cout << "Checking what is in Right Child Pointer of Root Node: " << endl; 
	// for (unsigned int i=0; i<myRootNode->accessChildren()[1]->getSlots(); ++i)
	// {
	// 	cout <<	myRootNode->accessChildren()[1]->accessKeys()[i] << " " ;
	// }
	// cout << endl;

	ASSERT_EQ(myRootNode->accessChildren()[1]->getKeyByIndex(0), 24);
	ASSERT_EQ(myRootNode->accessChildren()[1]->getKeyByIndex(1), 30);
	ASSERT_EQ(myRootNode->accessChildren()[1]->getSlots(), 2);



	// cout << "Checking what is in Left Child Pointer of Root's Left child: " << endl; 
	// for (unsigned int i=0; i<myRootNode->accessChildren()[0]->accessChildren()[0]->getSlots(); ++i)
	// {
	// 	cout <<	myRootNode->accessChildren()[0]->accessChildren()[0]->accessKeys()[i] << " " ;
	// }
	// cout << endl;

	ASSERT_EQ(myRootNode->accessChildren()[0]->accessChildren()[0]->getKeyByIndex(0), 2);
	ASSERT_EQ(myRootNode->accessChildren()[0]->accessChildren()[0]->getKeyByIndex(1), 3);
	ASSERT_EQ(myRootNode->accessChildren()[0]->accessChildren()[0]->getSlots(), 2);


	// cout << "Checking what is in Mid1 Child Pointer of Root's Left child: " << endl; 
	// for (unsigned int i=0; i<myRootNode->accessChildren()[0]->accessChildren()[1]->getSlots(); ++i)
	// {
	// 	cout <<	myRootNode->accessChildren()[0]->accessChildren()[1]->accessKeys()[i] << " " ;
	// }
	// cout << endl;

	ASSERT_EQ(myRootNode->accessChildren()[0]->accessChildren()[1]->getKeyByIndex(0), 5);
	ASSERT_EQ(myRootNode->accessChildren()[0]->accessChildren()[1]->getKeyByIndex(1), 7);
	ASSERT_EQ(myRootNode->accessChildren()[0]->accessChildren()[1]->getKeyByIndex(2), 8);
	ASSERT_EQ(myRootNode->accessChildren()[0]->accessChildren()[1]->getSlots(), 3);




	// cout << "Checking what is in MId2 Child Pointer of Root's Left child: " << endl; 
	// for (unsigned int i=0; i<myRootNode->accessChildren()[0]->accessChildren()[2]->getSlots(); ++i)
	// {
	// 	cout <<	myRootNode->accessChildren()[0]->accessChildren()[2]->accessKeys()[i] << " " ;
	// }
	// cout << endl;


	ASSERT_EQ(myRootNode->accessChildren()[0]->accessChildren()[2]->getKeyByIndex(0), 14);
	ASSERT_EQ(myRootNode->accessChildren()[0]->accessChildren()[2]->getKeyByIndex(1), 16);
	ASSERT_EQ(myRootNode->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);


	// cout << "Checking what is in Left Child Pointer of Root's Right child: " << endl; 
	// for (unsigned int i=0; i<myRootNode->accessChildren()[1]->accessChildren()[0]->getSlots(); ++i)
	// {
	// 	cout <<	myRootNode->accessChildren()[1]->accessChildren()[0]->accessKeys()[i] << " " ;
	// }
	// cout << endl;

	ASSERT_EQ(myRootNode->accessChildren()[1]->accessChildren()[0]->getKeyByIndex(0), 19);
	ASSERT_EQ(myRootNode->accessChildren()[1]->accessChildren()[0]->getKeyByIndex(1), 20);
	ASSERT_EQ(myRootNode->accessChildren()[1]->accessChildren()[0]->getKeyByIndex(2), 22);
	ASSERT_EQ(myRootNode->accessChildren()[1]->accessChildren()[0]->getSlots(), 3);



	// cout << "Checking what is in Mid1 Child Pointer of Root's Right child: " << endl; 
	// for (unsigned int i=0; i<myRootNode->accessChildren()[1]->accessChildren()[1]->getSlots(); ++i)
	// {
	// 	cout <<	myRootNode->accessChildren()[1]->accessChildren()[1]->accessKeys()[i] << " " ;
	// }
	// cout << endl;

	ASSERT_EQ(myRootNode->accessChildren()[1]->accessChildren()[1]->getKeyByIndex(0), 24);
	ASSERT_EQ(myRootNode->accessChildren()[1]->accessChildren()[1]->getKeyByIndex(1), 27);
	ASSERT_EQ(myRootNode->accessChildren()[1]->accessChildren()[1]->getKeyByIndex(2), 29);
	ASSERT_EQ(myRootNode->accessChildren()[1]->accessChildren()[1]->getSlots(), 3);


	// cout << "Checking what is in Mid2 Child Pointer of Root's Right child: " << endl; 
	// for (unsigned int i=0; i<myRootNode->accessChildren()[1]->accessChildren()[2]->getSlots(); ++i)
	// {
	// 	cout <<	myRootNode->accessChildren()[1]->accessChildren()[2]->accessKeys()[i] << " " ;
	// }
	// cout << endl;

	ASSERT_EQ(myRootNode->accessChildren()[1]->accessChildren()[2]->getKeyByIndex(0), 33);
	ASSERT_EQ(myRootNode->accessChildren()[1]->accessChildren()[2]->getKeyByIndex(1), 34);
	ASSERT_EQ(myRootNode->accessChildren()[1]->accessChildren()[2]->getKeyByIndex(2), 38);
	ASSERT_EQ(myRootNode->accessChildren()[1]->accessChildren()[2]->getKeyByIndex(3), 39);
	ASSERT_EQ(myRootNode->accessChildren()[1]->accessChildren()[2]->getSlots(), 4);


	// delete newLeafNode; 

	// for (unsigned int i=0; i<ORDER_M; ++i)
	// {
	// 	delete GlobalNodeTracker1[i];
	// }
	// delete GlobalRoot1;
	// delete myBPlusTree_Insert;



	// ========================================ANOTHER EXAMPLE of INSERT========================================




	// Version 1 BPlusTree test 
	// Building BPlusTree from scratch, root == NULL
	//             		   			[7, 13]
	//       	[3, 5]	   			[9, 11]					[15, 17]
	// [1, 2] [3, 4] [5, 6]   [7, 8] [9, 10] [11, 12]	[13, 14] [15, 16] [17, 18, 19] 
	BPlusTree* myBPlusTree_Insert_1 = new BPlusTree;


	myBPlusTree_Insert_1->Insert(1, "one"); 

	// Check Root Node after Insert(1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);

	myBPlusTree_Insert_1->Insert(2, "two"); 

	// Check Root Node after Insert(2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);

	myBPlusTree_Insert_1->Insert(3, "three"); 

	// Check Root Node after Insert(3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[2], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessValues()[2], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);



	myBPlusTree_Insert_1->Insert(4, "four"); 

	// Check Root Node after Insert(4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[2], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[3], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessValues()[2], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessValues()[3], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);


	myBPlusTree_Insert_1->Insert(5, "five"); 


	// after Insert(5);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[2], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[2], "five");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getNext(), nullptr);


	myBPlusTree_Insert_1->Insert(6, "six"); 


	// after Insert(6);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[2], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[3], 6);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[2], "five");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[3], "six");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getNext(), nullptr);


	myBPlusTree_Insert_1->Insert(7, "seven"); 


	// after Insert(7);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[1], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]);
	// Check Root -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[2], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessValues()[0], "five");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessValues()[1], "six");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessValues()[2], "seven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getNext(), nullptr);


	myBPlusTree_Insert_1->Insert(8, "eight"); 


	// after Insert(8);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[1], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]);
	// Check Root -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[2], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[3], 8);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessValues()[0], "five");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessValues()[1], "six");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessValues()[2], "seven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessValues()[3], "eight");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getNext(), nullptr);


	myBPlusTree_Insert_1->Insert(9, "nine"); 
	// after Insert(9);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[1], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[2], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]);
	// Check Root -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessValues()[0], "five");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessValues()[1], "six");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]);
	// Check Root -> Mid3 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessKeys()[1], 8);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessKeys()[2], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessValues()[0], "seven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessValues()[1], "eight");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessValues()[2], "nine");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->getNext(), nullptr);


	myBPlusTree_Insert_1->Insert(10, "ten"); 
	// after Insert(10);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[1], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[2], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]);
	// Check Root -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessValues()[0], "five");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessValues()[1], "six");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]);
	// Check Root -> Mid3 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessKeys()[1], 8);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessKeys()[2], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessKeys()[3], 10);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessValues()[0], "seven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessValues()[1], "eight");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessValues()[2], "nine");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessValues()[3], "ten");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->getNext(), nullptr);



	myBPlusTree_Insert_1->Insert(11, "eleven"); 
	// after Insert(11);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[1], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[2], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[3], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]);
	// Check Root -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessValues()[0], "five");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessValues()[1], "six");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]);
	// Check Root -> Mid3 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessKeys()[1], 8);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessValues()[0], "seven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessValues()[1], "eight");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]);
	// Check Root -> Right Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->accessKeys()[1], 10);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->accessKeys()[2], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->accessValues()[0], "nine");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->accessValues()[1], "ten");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->accessValues()[2], "eleven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->getNext(), nullptr);


	myBPlusTree_Insert_1->Insert(12, "twelve"); 
	// after Insert(12);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[1], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[2], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[3], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]);
	// Check Root -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessValues()[0], "five");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessValues()[1], "six");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]);
	// Check Root -> Mid3 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessKeys()[1], 8);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessValues()[0], "seven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->accessValues()[1], "eight");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]);
	// Check Root -> Right Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->accessKeys()[1], 10);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->accessKeys()[2], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->accessKeys()[3], 12);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->accessValues()[0], "nine");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->accessValues()[1], "ten");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->accessValues()[2], "eleven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->accessValues()[3], "twelve");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[3]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[4]->getNext(), nullptr);


	myBPlusTree_Insert_1->Insert(13, "thirteen"); 
	// after Insert(13);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[1], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getNext(), nullptr);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[1], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getNext(), nullptr);
	// Check Root -> Left -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	// Check Root -> Left -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	// Check Root -> Left -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[0], "five");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[1], "six");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	// Check Root -> Mid1 -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[1], 8);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[0], "seven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[1], "eight");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	// Check Root -> Mid1 -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[1], 10);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[0], "nine");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[1], "ten");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	// Check Root -> Mid1 -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[0], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[1], 12);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[2], 13);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[0], "eleven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[1], "twelve");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[2], "thirteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getNext(), nullptr);


	myBPlusTree_Insert_1->Insert(14, "fourteen"); 
	// after Insert(14);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[1], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getNext(), nullptr);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[1], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getNext(), nullptr);
	// Check Root -> Left -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	// Check Root -> Left -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	// Check Root -> Left -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[0], "five");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[1], "six");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	// Check Root -> Mid1 -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[1], 8);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[0], "seven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[1], "eight");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	// Check Root -> Mid1 -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[1], 10);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[0], "nine");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[1], "ten");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	// Check Root -> Mid1 -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[0], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[1], 12);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[2], 13);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[3], 14);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[0], "eleven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[1], "twelve");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[2], "thirteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[3], "fourteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getNext(), nullptr);

	myBPlusTree_Insert_1->Insert(15, "fifteen"); 
	// after Insert(15);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[1], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getNext(), nullptr);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[1], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[2], 13);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getNext(), nullptr);
	// Check Root -> Left -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	// Check Root -> Left -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	// Check Root -> Left -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[0], "five");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[1], "six");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	// Check Root -> Mid1 -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[1], 8);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[0], "seven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[1], "eight");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	// Check Root -> Mid1 -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[1], 10);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[0], "nine");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[1], "ten");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	// Check Root -> Mid1 -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[0], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[1], 12);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[0], "eleven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[1], "twelve");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]);
	// Check Root -> Mid1 -> Mid3 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessKeys()[0], 13);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessKeys()[1], 14);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessKeys()[2], 15);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessValues()[0], "thirteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessValues()[1], "fourteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessValues()[2], "fifteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->getNext(), nullptr);

	myBPlusTree_Insert_1->Insert(16, "sixteen"); 
	// after Insert(16);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[1], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getNext(), nullptr);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[1], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[2], 13);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getNext(), nullptr);
	// Check Root -> Left -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	// Check Root -> Left -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	// Check Root -> Left -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[0], "five");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[1], "six");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	// Check Root -> Mid1 -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[1], 8);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[0], "seven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[1], "eight");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	// Check Root -> Mid1 -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[1], 10);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[0], "nine");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[1], "ten");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	// Check Root -> Mid1 -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[0], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[1], 12);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[0], "eleven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[1], "twelve");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]);
	// Check Root -> Mid1 -> Mid3 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessKeys()[0], 13);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessKeys()[1], 14);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessKeys()[2], 15);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessKeys()[3], 16);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessValues()[0], "thirteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessValues()[1], "fourteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessValues()[2], "fifteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessValues()[3], "sixteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->getNext(), nullptr);

	myBPlusTree_Insert_1->Insert(17, "seventeen"); 
	// after Insert(17);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[1], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getNext(), nullptr);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[1], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[2], 13);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[3], 15);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getNext(), nullptr);
	// Check Root -> Left -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	// Check Root -> Left -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	// Check Root -> Left -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[0], "five");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[1], "six");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	// Check Root -> Mid1 -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[1], 8);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[0], "seven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[1], "eight");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	// Check Root -> Mid1 -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[1], 10);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[0], "nine");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[1], "ten");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	// Check Root -> Mid1 -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[0], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[1], 12);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[0], "eleven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[1], "twelve");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]);
	// Check Root -> Mid1 -> Mid3 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessKeys()[0], 13);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessKeys()[1], 14);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessValues()[0], "thirteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessValues()[1], "fourteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]);
	// Check Root -> Mid1 -> Right Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->accessKeys()[0], 15);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->accessKeys()[1], 16);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->accessKeys()[2], 17);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->accessValues()[0], "fifteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->accessValues()[1], "sixteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->accessValues()[2], "seventeen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->getNext(), nullptr);

	myBPlusTree_Insert_1->Insert(18, "eighteen"); 
	// after Insert(18);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[1], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getNext(), nullptr);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[1], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[2], 13);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[3], 15);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getNext(), nullptr);
	// Check Root -> Left -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	// Check Root -> Left -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	// Check Root -> Left -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[0], "five");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[1], "six");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	// Check Root -> Mid1 -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[1], 8);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[0], "seven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[1], "eight");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	// Check Root -> Mid1 -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[1], 10);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[0], "nine");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[1], "ten");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	// Check Root -> Mid1 -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[0], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[1], 12);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[0], "eleven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[1], "twelve");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]);
	// Check Root -> Mid1 -> Mid3 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessKeys()[0], 13);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessKeys()[1], 14);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessValues()[0], "thirteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->accessValues()[1], "fourteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]);
	// Check Root -> Mid1 -> Right Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->accessKeys()[0], 15);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->accessKeys()[1], 16);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->accessKeys()[2], 17);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->accessKeys()[3], 18);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->accessValues()[0], "fifteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->accessValues()[1], "sixteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->accessValues()[2], "seventeen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->accessValues()[3], "eighteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[3]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[4]->getNext(), nullptr);

	myBPlusTree_Insert_1->Insert(19, "nineteen"); 
	// after Insert(19);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessKeys()[1], 13);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessKeys()[1], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->getNext(), nullptr);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessKeys()[1], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->getNext(), nullptr);
	// Check Root -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[0], 15);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessKeys()[1], 17);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->getNext(), nullptr);

	// Check Root -> Left -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	// Check Root -> Left -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	// Check Root -> Left -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[0], "five");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[1], "six");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	
	// Check Root -> Mid1 -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[1], 8);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[0], "seven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[1], "eight");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	// Check Root -> Mid1 -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[1], 10);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[0], "nine");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[1], "ten");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	// Check Root -> Mid1 -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[0], 11);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[1], 12);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[0], "eleven");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[1], "twelve");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[0]);
	
	// Check Root -> Mid2 -> Left Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[0]->accessKeys()[0], 13);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[0]->accessKeys()[1], 14);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[0]->accessValues()[0], "thirteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[0]->accessValues()[1], "fourteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[0]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[0]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[1]);
	// Check Root -> Mid2 -> Mid1 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[1]->accessKeys()[0], 15);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[1]->accessKeys()[1], 16);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[1]->accessValues()[0], "fifteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[1]->accessValues()[1], "sixteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[1]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[1]->getNext(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[2]);
	// Check Root -> Mid2 -> Mid2 Node
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[2]->accessKeys()[0], 17);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[2]->accessKeys()[1], 18);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[2]->accessKeys()[2], 19);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[2]->accessValues()[0], "seventeen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[2]->accessValues()[1], "eighteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[2]->accessValues()[2], "nineteen");
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[2]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[2]->getPrev(), myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_Insert_1->getRootNode()->accessChildren()[2]->accessChildren()[2]->getNext(), nullptr);


	// // Adding to the above tree to make 
	// //             		   			[7, 13]
	// //       	[3, 5]	   			[9, 11]					[15, 17]
	// // [1, 2] [3, 4] [5, 6]   [7, 8] [9, 10] [11, 12]	[13, 14] [15, 16] [17, 18, 19] 

	// // Insert [20 to 37] to a B+ Tree 
	// for (unsigned int i=20; i<38; ++i)
	// {
	// 	myBPlusTree_Insert_1->Insert(i); 
	// }








	// delete myBPlusTree_Insert_1;





}




TEST_F(test_BPlusTreeDBMS, TestBPlusTree_DeleteDefaultTestCases)
{
	BPlusTree* myBPlusTree_DeleteDefaultTestCases = mkBPlusTree1();

	myBPlusTree_DeleteDefaultTestCases->Insert(8, "eight"); 

	// cout << endl;
	// cout << "8 should be in Mid1 of Left of Root" << endl;
	// for (unsigned int i=0; i < myBPlusTree->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(); ++i)
	// {
	// 	cout << myBPlusTree->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[i] << " "; 
	// }
	// cout << endl;


	myBPlusTree_DeleteDefaultTestCases->Delete(19);

	// Do We hafve the correct TREE after removing 20? 
	// cout << endl;
	// cout << "19's node should only remain 20, 22" << endl;
	// for (unsigned int i=0; i < myBPlusTree->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(); ++i)
	// {
	// 	cout << myBPlusTree->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[i] << " "; 
	// }
	// cout << endl;

	// ROOT 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessKeys()[0], 17);

	// Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessKeys()[1], 13);

	// Left of Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[0], 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[1], 3);

	// Mid1 of Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[1], 7);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[2], 8);

	// Mid2 of Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[0], 14);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[1], 16);


	// Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessKeys()[0], 24);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessKeys()[1], 30);

	// Left of Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[0], 20);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[1], 22);


	// Mid1 of Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[1]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[0], 24);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[1], 27);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[2], 29);


	// Mid2 of Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[0], 33);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[1], 34);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[2], 38);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[3], 39);



	// Problem in Delete 20 
	myBPlusTree_DeleteDefaultTestCases->Delete(20);

	// ROOT 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessKeys()[0], 17);

	// Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessKeys()[1], 13);

	// Left of Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[0], 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[1], 3);

	// Mid1 of Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[1], 7);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[2], 8);

	// Mid2 of Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[0], 14);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[1], 16);


	// Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessKeys()[0], 27);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessKeys()[1], 30);

	// Left of Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[0], 22);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[1], 24);


	// Mid1 of Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[0], 27);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[1], 29);


	// Mid2 of Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[0], 33);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[1], 34);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[2], 38);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[3], 39);







	// Try remove 24 
	myBPlusTree_DeleteDefaultTestCases->Delete(24);

	// Do We hafve the correct TREE after removing 24? 
	// ROOT 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessKeys()[1], 13);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessKeys()[2], 17);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessKeys()[3], 30);


	// Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessKeys()[0], 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->accessKeys()[1], 3);

	// Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessKeys()[1], 7);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->accessKeys()[2], 8);

	// Mid2 of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[2]->accessKeys()[0], 14);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[2]->accessKeys()[1], 16);

	// Mid3 of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[3]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[3]->accessKeys()[0], 22);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[3]->accessKeys()[1], 27);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[3]->accessKeys()[2], 29);

	// Right of Root 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[4]->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[4]->accessKeys()[0], 33);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[4]->accessKeys()[1], 34);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[4]->accessKeys()[2], 38);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[4]->accessKeys()[3], 39);

	// Check Sibling of Leafs 
	// Left 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]->getNext(), myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]);
	
	// Mid1 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->getPrev(), myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]->getNext(), myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[2]);

	// Mid2 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[2]->getPrev(), myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[2]->getNext(), myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[3]);

	// Mid3 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[3]->getPrev(), myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[3]->getNext(), myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[4]);

	// Right 
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[4]->getPrev(), myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[3]);
	ASSERT_EQ(myBPlusTree_DeleteDefaultTestCases->getRootNode()->accessChildren()[4]->getNext(), nullptr);



	// delete myBPlusTree_DeleteDefaultTestCases; 

}




TEST_F(test_BPlusTreeDBMS, TestBPlusTree_DeleteExtraTestCases)
{
	BPlusTree* myBPlusTree_DeleteExtraTestCases = mkBPlusTree1();



	myBPlusTree_DeleteExtraTestCases->Insert(8, "eight"); 

	
	// Do We hafve the correct TREE after Inserting 8 ? 
	// ROOT 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessKeys()[0], 17);

	// Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessKeys()[1], 13);

	// Left of Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[0], 2);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[1], 3);



	// Mid1 of Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[1], 7);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[2], 8);

	// Mid2 of Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[0], 14);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[1], 16);


	// Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessKeys()[0], 24);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessKeys()[1], 30);


	// for (unsigned int i=0 ; i<myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(); ++i)
	// {
	// 	cout << myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[i] << " ";

	// }
	// cout << endl; 


	// Left of Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[0], 19);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[1], 20);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[2], 22);

	// Mid1 of Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[1]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[0], 24);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[1], 27);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[2], 29);

	// Mid2 of Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[0], 33);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[1], 34);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[2], 38);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[3], 39);




	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl; 

	myBPlusTree_DeleteExtraTestCases->Delete(14);


	// Do We hafve the correct TREE after removing 14? 
	// ROOT 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessKeys()[0], 17);

	// Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessKeys()[1], 8);

	// Left of Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[0], 2);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[1], 3);

	// Mid1 of Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[1], 7);

	// Mid2 of Left of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[0], 8);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[1], 16);


	// Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessKeys()[0], 24);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessKeys()[1], 30);

	// Left of Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[0], 19);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[1], 20);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[2], 22);

	// Mid1 of Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[1]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[0], 24);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[1], 27);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[2], 29);

	// Mid2 of Mid1 of Root 
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[0], 33);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[1], 34);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[2], 38);
	ASSERT_EQ(myBPlusTree_DeleteExtraTestCases->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[3], 39);



}




TEST_F(test_BPlusTreeDBMS, TestBPlusTree_DeleteOneToNineteenTestCases)
{



	BPlusTree* myBPlusTree_OneToNineteen = new BPlusTree;

	myBPlusTree_OneToNineteen->Insert(1, "one");


	myBPlusTree_OneToNineteen->Delete(1);


	// //             		   			[7, 13]
	// //       	[3, 5]	   			[9, 11]					[15, 17]
	// // [1, 2] [3, 4] [5, 6]   [7, 8] [9, 10] [11, 12]	[13, 14] [15, 16] [17, 18, 19] 

	cout << "~~~Inserting~~~" << endl; 
	// for (unsigned int i=1; i < 20; ++i)
	// {
	// 	myBPlusTree_OneToNineteen->Insert(i);
	// 	cout << i << " "; 
	// }
	// cout << endl; 

	myBPlusTree_OneToNineteen->Insert(1, "one");
	myBPlusTree_OneToNineteen->Insert(2, "two");
	myBPlusTree_OneToNineteen->Insert(3, "three");
	myBPlusTree_OneToNineteen->Insert(4, "four");
	myBPlusTree_OneToNineteen->Insert(5, "five");
	myBPlusTree_OneToNineteen->Insert(6, "six");
	myBPlusTree_OneToNineteen->Insert(7, "seven");
	myBPlusTree_OneToNineteen->Insert(8, "eight");
	myBPlusTree_OneToNineteen->Insert(9, "nine");
	myBPlusTree_OneToNineteen->Insert(10, "ten");
	myBPlusTree_OneToNineteen->Insert(11, "eleven");
	myBPlusTree_OneToNineteen->Insert(12, "twelve");
	myBPlusTree_OneToNineteen->Insert(13, "thirteen");
	myBPlusTree_OneToNineteen->Insert(14, "fourteen");
	myBPlusTree_OneToNineteen->Insert(15, "fifteen");
	myBPlusTree_OneToNineteen->Insert(16, "sixteen");
	myBPlusTree_OneToNineteen->Insert(17, "seventeen");
	myBPlusTree_OneToNineteen->Insert(18, "eighteen");
	myBPlusTree_OneToNineteen->Insert(19, "nineteen");





	// Check if the Insert() is successfully representing the above B+ Tree 
	// Check Root Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessKeys()[1], 13);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->getNext(), nullptr);
	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessKeys()[1], 5);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->getNext(), nullptr);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessKeys()[1], 11);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->getNext(), nullptr);
	// Check Root -> Mid2 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessKeys()[0], 15);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessKeys()[1], 17);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->getNext(), nullptr);

	// Check Root -> Left -> Left Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[0], 1);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[1], 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[0], "one");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessValues()[1], "two");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	// Check Root -> Left -> Mid1 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[0], 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[1], 4);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[0], "three");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessValues()[1], "four");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	// Check Root -> Left -> Mid2 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[0], "five");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessValues()[1], "six");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	
	// Check Root -> Mid1 -> Left Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[1], 8);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[0], "seven");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessValues()[1], "eight");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	// Check Root -> Mid1 -> Mid1 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[1], 10);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[0], "nine");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessValues()[1], "ten");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	// Check Root -> Mid1 -> Mid2 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[0], 11);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[1], 12);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[0], "eleven");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessValues()[1], "twelve");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[0]);
	
	// Check Root -> Mid2 -> Left Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[0]->accessKeys()[0], 13);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[0]->accessKeys()[1], 14);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[0]->accessValues()[0], "thirteen");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[0]->accessValues()[1], "fourteen");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[0]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[0]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[1]);
	// Check Root -> Mid2 -> Mid1 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[1]->accessKeys()[0], 15);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[1]->accessKeys()[1], 16);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[1]->accessValues()[0], "fifteen");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[1]->accessValues()[1], "sixteen");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[1]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[1]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[2]);
	// Check Root -> Mid2 -> Mid2 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[2]->accessKeys()[0], 17);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[2]->accessKeys()[1], 18);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[2]->accessKeys()[2], 19);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[2]->accessValues()[0], "seventeen");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[2]->accessValues()[1], "eighteen");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[2]->accessValues()[2], "nineteen");
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[2]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[2]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessChildren()[2]->getNext(), nullptr);





	myBPlusTree_OneToNineteen->Delete(1);

	// after Delete(1);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessKeys()[0], 13);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->getNext(), nullptr);

	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessKeys()[1], 7);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessKeys()[2], 9);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessKeys()[3], 11);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->getSlots(), 4);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->getNext(), nullptr);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessKeys()[0], 15);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessKeys()[1], 17);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->getNext(), nullptr);

	// Check Root -> Left -> Left Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[0], 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[1], 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[2], 4);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	// Check Root -> Left -> Mid1 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	// Check Root -> Left -> Mid2 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[1], 8);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[3]);
	// Check Root -> Left -> Mid3 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[3]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[3]->accessKeys()[1], 10);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[3]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[3]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[3]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[4]);
	// Check Root -> Left -> Right Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[4]->accessKeys()[0], 11);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[4]->accessKeys()[1], 12);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[4]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[4]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[3]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[4]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]);

	// Check Root -> Mid1 -> Left Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[0], 13);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[1], 14);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[4]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	// Check Root -> Mid1 -> Mid1 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[0], 15);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[1], 16);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	// Check Root -> Mid1 -> Mid2 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[0], 17);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[1], 18);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[2], 19);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->getNext(), nullptr);
	

	Node* found14 = myBPlusTree_OneToNineteen->Find(14); 

	cout << "What is FOUND in 14" << endl; 
	for (unsigned int i = 0; i < found14->getSlots(); ++i)
    {   
        cout << found14->accessKeys()[i] << " ";
    }
	cout << endl; 


	myBPlusTree_OneToNineteen->Delete(14);

	// after Delete(14);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessKeys()[0], 11);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->getNext(), nullptr);

	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessKeys()[1], 7);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessKeys()[2], 9);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->getNext(), nullptr);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessKeys()[0], 13);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessKeys()[1], 17);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->getNext(), nullptr);

	// Check Root -> Left -> Left Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[0], 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[1], 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[2], 4);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	// Check Root -> Left -> Mid1 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[1], 6);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	// Check Root -> Left -> Mid2 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[0], 7);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[1], 8);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[3]);
	// Check Root -> Left -> Mid3 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[3]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[3]->accessKeys()[1], 10);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[3]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[3]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[3]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	// Check Root -> Left -> Right Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[0], 11);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[1], 12);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[3]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	// Check Root -> Mid1 -> Left Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[0], 13);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[1], 15);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[2], 16);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	// Check Root -> Mid1 -> Mid2 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[0], 17);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[1], 18);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[2], 19);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->getNext(), nullptr);




	myBPlusTree_OneToNineteen->Delete(6);
	// after Delete(6);
	// Check Root Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessKeys()[0], 11);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->getSlots(), 1);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->getNext(), nullptr);

	// Check Root -> Left Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessKeys()[1], 9);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->getNext(), nullptr);
	// Check Root -> Mid1 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessKeys()[0], 13);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessKeys()[1], 17);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->getNext(), nullptr);

	// Check Root -> Left -> Left Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[0], 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[1], 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->accessKeys()[2], 4);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->getPrev(), nullptr);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	// Check Root -> Left -> Mid1 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[0], 5);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[1], 7);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->accessKeys()[2], 8);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	// Check Root -> Left -> Mid2 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[0], 9);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->accessKeys()[1], 10);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	// Check Root -> Left -> Right Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[0], 11);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->accessKeys()[1], 12);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->getSlots(), 2);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessChildren()[2]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	// Check Root -> Mid1 -> Left Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[0], 13);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[1], 15);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->accessKeys()[2], 16);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[0]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]);
	// Check Root -> Mid1 -> Mid2 Node
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[0], 17);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[1], 18);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->accessKeys()[2], 19);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->getSlots(), 3);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[1]);
	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessChildren()[2]->getNext(), nullptr);





	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl; 








	// myBPlusTree_OneToNineteen->Delete(7);
	// myBPlusTree_OneToNineteen->Delete(8);
	// myBPlusTree_OneToNineteen->Delete(4);




	// // after Delete(6); Delete(7); Delete(8); Delete(4);
	// // Check Root Node
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessKeys()[0], 9);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessKeys()[1], 11);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessKeys()[2], 13);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessKeys()[3], 17);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->getSlots(), 4);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->getPrev(), nullptr);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->getNext(), nullptr);

	// // Check Root -> Left Node
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessKeys()[0], 2);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessKeys()[1], 3);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->accessKeys()[2], 5);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->getSlots(), 3);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->getPrev(), nullptr);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]);
	// // Check Root -> Mid1 Node
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessKeys()[0], 9);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->accessKeys()[1], 10);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->getSlots(), 2);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[0]);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]);
	// // Check Root -> Mid2 Node
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessKeys()[0], 11);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->accessKeys()[1], 12);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->getSlots(), 2);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[1]);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[3]);
	// // Check Root -> Mid3 Node
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[3]->accessKeys()[0], 13);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[3]->accessKeys()[1], 15);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[3]->accessKeys()[2], 16);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[3]->getSlots(), 3);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[3]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[2]);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[3]->getNext(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[4]);
	// // Check Root -> Right Node
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[4]->accessKeys()[0], 17);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[4]->accessKeys()[1], 18);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[4]->accessKeys()[2], 19);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[4]->getSlots(), 3);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[4]->getPrev(), myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[3]);
	// ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode()->accessChildren()[4]->getNext(), nullptr);






	cout << "~~~Deleting~~~" << endl; 
	for (int i=2; i < 20; ++i)
	{
		if (i == 14 || i == 6)
		{
			continue;
		}
		myBPlusTree_OneToNineteen->Delete(i);
		cout << i << " "; 
	}
	cout << endl; 

	// cout << "What is in the ROOT after deleing ???" << endl; 
	// for (unsigned int i = 0; i < myBPlusTree_OneToNineteen->getRootNode()->getSlots(); ++i)
	// {
	// 	cout << myBPlusTree_OneToNineteen->getRootNode()->accessKeys()[i] << " ";
	// }
	// cout << endl; 

	// if (myBPlusTree_OneToNineteen->getRootNode() == nullptr)
	// {
	// 	cout << "NULL is it !" << endl; 
	// }
	// else
	// {
	// 	cout << "I still don't know what's wrong..." << endl;
	// }




	// cout << "What is in the Empty ROOT NODE? " << endl; 
	// for (unsigned int i=0; i < myBPlusTree_OneToNineteen->getRootNode()->getSlots(); ++i)
	// {
	// 	cout << myBPlusTree_OneToNineteen->getRootNode()->accessKeys()[i] << " ";
	// }
	// cout << endl; 






	ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode(), nullptr);

	cout << "This means ASSERT_EQ(myBPlusTree_OneToNineteen->getRootNode(), nullptr); Passes!!!!" << endl;



}


TEST_F(test_BPlusTreeDBMS, TestBPlusTreeDBMS_CRUD)
{
	BPlusTreeDBMS* myDBMS = new BPlusTreeDBMS;
	ASSERT_EQ(myDBMS->Create(1, "testing 001"), true);

	ASSERT_EQ(myDBMS->ReadByKey(1), true);
	ASSERT_EQ(myDBMS->Update(1, "Update 001"), true);
	ASSERT_EQ(myDBMS->ReadByKey(1), true);
	ASSERT_EQ(myDBMS->Delete(1), true);

	if (myDBMS->getBPlusTree()->getRootNode() == NULL)
	{
		cout << "The Root node should be NULL!" << endl; 
	}


	myDBMS->Create(1300, "Computer Science 1: Starting Computing");
	myDBMS->Create(2270, "Computer Science 2: Data Structures");
	myDBMS->Create(2400, "Computer Systems");
	myDBMS->Create(2824, "Discrete Structures");
	myDBMS->Create(3104, "Algorithms");
	myDBMS->Create(3155, "Principles of Programming Languages");
	myDBMS->Create(3308, "Software Development Methods and Tools");
	myDBMS->Create(1000, "Computer Science as a Field of Work and Study");
	myDBMS->Create(2820, "Linear Algebra with Computer Science Applications");
	myDBMS->Create(3022, "Introduction to Data Science with Probability and Statistics");
	myDBMS->Create(3112, "Professional Development in Computer Science");
	myDBMS->Create(3202, "Introduction to Artificial Intelligence");
	myDBMS->Create(3287, "Design and Analysis of Database Systems");
	myDBMS->Create(3302, "Introduction to Robotics");
	myDBMS->Create(3403, "Introduction to CyberSecurity for a Converged World");
	myDBMS->Create(3702, "Cognitive Science");
	myDBMS->Create(3753, "Design and Analysis of Operating Systems");
	myDBMS->Create(4122, "Information Visualization");
	myDBMS->Create(4253, "Datacenter Scale Computing - Methods, Systems and Techniques");
	myDBMS->Create(4502, "Data Mining");
	myDBMS->Create(4622, "Machine Learning");
	myDBMS->Create(4830, "Special Topics in Applied Computer Science");
	myDBMS->Create(4900, "Upper Division, Undergraduate Level Independent Study");

	myDBMS->ReadByRange(0000, 999);
	myDBMS->ReadByRange(1000, 1999);
	myDBMS->ReadByRange(2000, 2999);
	myDBMS->ReadByRange(3000, 3999);
	myDBMS->ReadByRange(4000, 4999);
	myDBMS->ReadByRange(5000, 7000);


	myDBMS->Create(4830, "Special Topics in Computer Science: Current Topics in Computer Science: Advances in Datacenter Networking and Cloud Computing");
	myDBMS->Update(4830, "Special Topics in Computer Science: Current Topics in Computer Science: Advances in Datacenter Networking and Cloud Computing");

	myDBMS->ReadByKey(2824); 
	myDBMS->ReadByKey(4830);
	ASSERT_EQ(myDBMS->ReadByKey(2822), false);
	ASSERT_EQ(myDBMS->ReadByKey(4831), false);



}










// Helper functions 
BPlusTree* mkBPlusTree1()
{
	//						  [13, 17, 24, 30]			
	//[2, 3, 5, 7]   [14, 16]	[19, 20, 22]	[24, 27, 29]	[33, 34, 38, 39]



	// Test BPlusTree Reference: https://web.stanford.edu/class/cs346/2015/notes/Blink.pdf
	BPlusTree* myBPlusTree = new BPlusTree; 
	

	// instantiations 
	// Root 
	int arr_keys[ORDER_M] = {13, 17, 24, 30};
	std::string arr_values[ORDER_M] = {"thirteen", "seventeen", "twentyfour", "thirty"}; 
	Node* myNodeRoot = new Node("root", 0, false, 4, arr_keys, arr_values);

	// children nodes 
	int arr_keys1[ORDER_M] = {2, 3, 5, 7};
	std::string arr_values1[ORDER_M] = {"two", "three", "five", "seven"}; 
	Node* myNodeLeft = new Node("left", 1, true, 4, arr_keys1, arr_values1);

	int arr_keys2[ORDER_M] = {14, 16};
	std::string arr_values2[ORDER_M] = {"fourteen", "sixteen"}; 
	Node* myNodeMid1 = new Node("mid1", 1, true, 2, arr_keys2, arr_values2);

	int arr_keys3[ORDER_M] = {19, 20, 22};
	std::string arr_values3[ORDER_M] = {"nineteen", "twenty", "twentytwo"}; 
	Node* myNodeMid2 = new Node("mid2", 1, true, 3, arr_keys3, arr_values3);

	int arr_keys4[ORDER_M] = {24, 27, 29};
	std::string arr_values4[ORDER_M] = {"twentyfour", "twentyseven", "twentynine"}; 
	Node* myNodeMid3 = new Node("mid3", 1, true, 3, arr_keys4, arr_values4);

	int arr_keys5[ORDER_M] = {33, 34, 38, 39};
	std::string arr_values5[ORDER_M] = {"thirtythree", "thirtyfour", "thirtyeight", "thirtynine"}; 
	Node* myNodeRight = new Node("right", 1, true, 4, arr_keys5, arr_values5);

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
	myNodeMid3->setNext(myNodeRight);
	// set Left
	myNodeRight->setPrev(myNodeMid3);

	// set Root's children 
	myNodeRoot->accessChildren()[0] = myNodeLeft;
	myNodeRoot->accessChildren()[1] = myNodeMid1;
	myNodeRoot->accessChildren()[2] = myNodeMid2;
	myNodeRoot->accessChildren()[3] = myNodeMid3;
	myNodeRoot->accessChildren()[4] = myNodeRight;

	// set Root 
	myBPlusTree->setRootNode(myNodeRoot);


	// Global GlobalNodeTracker1 ForTesting
	GlobalRoot1 = myNodeRoot;
	GlobalNodeTracker1[0] = myNodeLeft;
	GlobalNodeTracker1[1] = myNodeMid1;
	GlobalNodeTracker1[2] = myNodeMid2;
	GlobalNodeTracker1[3] = myNodeMid3;
	GlobalNodeTracker1[4] = myNodeRight;


	return myBPlusTree; 
}


BPlusTree* mkBPlusTree2()
{
	//						  [17]			
	//



	// Test BPlusTree Reference: https://web.stanford.edu/class/cs346/2015/notes/Blink.pdf
	BPlusTree* myBPlusTree = new BPlusTree; 
	

	// instantiations 
	// Root 
	int arr[ORDER_M] = {17};
	Node* myNodeRoot = new Node("root", 0, false, 1, arr);

	// level 1
	int arr1[ORDER_M] = {5, 13};
	Node* mylevel1_left = new Node("level1_left", 1, false, 2, arr1);

	int arr2[ORDER_M] = {24, 30};
	Node* mylevel1_mid1 = new Node("level1_mid1", 1, false, 2, arr2);

	// level 2, under level1_left
	int arr3[ORDER_M] = {2, 3};
	Node* mylevel2_0 = new Node("level2_0", 1, true, 2, arr3);

	int arr4[ORDER_M] = {5, 7, 8};
	Node* mylevel2_1 = new Node("level2_1", 1, true, 3, arr4);

	int arr5[ORDER_M] = {14, 15, 16, 17};
	Node* mylevel2_2 = new Node("level2_2", 1, true, 4, arr5);

	// level 2, under level1_mid1
	int arr6[ORDER_M] = {19, 20, 22};
	Node* mylevel2_3 = new Node("level2_3", 1, true, 3, arr6);

	int arr7[ORDER_M] = {22, 27, 29};
	Node* mylevel2_4 = new Node("level2_4", 1, true, 3, arr7);

	int arr8[ORDER_M] = {33, 34, 38, 39};
	Node* mylevel2_5 = new Node("level2_5", 1, true, 4, arr8);

	// connect between Leaf nodes 

	
	mylevel2_0->setNext(mylevel2_1);
	
	mylevel2_1->setPrev(mylevel2_0);
	mylevel2_1->setNext(mylevel2_2);
	
	mylevel2_2->setPrev(mylevel2_1);
	mylevel2_2->setNext(mylevel2_3);
	
	mylevel2_3->setPrev(mylevel2_2);
	mylevel2_3->setNext(mylevel2_4);
	
	mylevel2_4->setPrev(mylevel2_3);
	mylevel2_4->setNext(mylevel2_5);

	mylevel2_5->setPrev(mylevel2_4);



	// set Root's children 
	myNodeRoot->accessChildren()[0] = mylevel1_left;
	myNodeRoot->accessChildren()[1] = mylevel1_mid1;

	// set mylevel1_left's children 
	mylevel1_left->accessChildren()[0] = mylevel2_0;
	mylevel1_left->accessChildren()[1] = mylevel2_1;
	mylevel1_left->accessChildren()[2] = mylevel2_2;

	// set mylevel1_mid1's children 
	mylevel1_mid1->accessChildren()[0] = mylevel2_3;
	mylevel1_mid1->accessChildren()[1] = mylevel2_4;
	mylevel1_mid1->accessChildren()[2] = mylevel2_5;

	// set Root 
	myBPlusTree->setRootNode(myNodeRoot);


	// Global GlobalNodeTracker1 ForTesting
	GlobalRoot2 = myNodeRoot;
	GlobalNodeTracker2[0] = mylevel1_left;
	GlobalNodeTracker2[1] = mylevel1_mid1;
	GlobalNodeTracker2[2] = mylevel2_0;
	GlobalNodeTracker2[3] = mylevel2_1;
	GlobalNodeTracker2[4] = mylevel2_2;
	GlobalNodeTracker2[5] = mylevel2_3;
	GlobalNodeTracker2[6] = mylevel2_4;
	GlobalNodeTracker2[7] = mylevel2_5;


	return myBPlusTree; 
}






bool BPlusTreeInvariantChecker()
{


	return false; 
}







