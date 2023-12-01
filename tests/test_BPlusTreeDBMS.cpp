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
	int arr[ORDER_M] = {1,2,3,4};
	Node myNode("test001", 0, true, 4, arr);
	BPlusTree myBPlusTree; 

	// cout << "i should be 0: " << myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 1) << endl;
	ASSERT_EQ(0, myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 1));

	// cout << "i should be 1: " << myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 2) << endl;
	ASSERT_EQ(1, myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 2));

	// cout << "i should be -1: " << myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 12) << endl;
	ASSERT_EQ(-1, myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 12));

	// cout << "i should be 3: " << myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 4) << endl;
	ASSERT_NE(4, myBPlusTree.IndexOfKiSmallestKeyGeqV(&myNode, 4));


	// Node(std::string _data, unsigned int _level, bool _leaf, unsigned int _slots, int _keys[ORDER_M], Node* _children[ORDER_M + 1]);

	// ASSERT_EQ(0, myobj.BPlusTreeDBMSFunc());
	// cout << "!!!!!!!!!!!" << endl; 
	// ASSERT_EQ(1, myobj.BPlusTreeDBMSFunc());
	// cout << "~~~~~~~~~" << endl; 

	// ASSERT_FALSE(myobj.test_false());

	// ASSERT_TRUE(myobj.test_true());




        
}

TEST_F(test_BPlusTreeDBMS, TestBPlusTree_Find){
    BPlusTree* myBPlusTree = mkBPlusTree1();

	
	
	Node* found_node = myBPlusTree->find(16);
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


	// ASSERT_EQ(GlobalNodeTracker1[0], myBPlusTree->find(2)); 
	ASSERT_EQ(GlobalNodeTracker1[1], myBPlusTree->find(16)); 
	ASSERT_EQ(GlobalNodeTracker1[2], myBPlusTree->find(20)); 
	ASSERT_EQ(GlobalNodeTracker1[3], myBPlusTree->find(27)); 
	ASSERT_EQ(GlobalNodeTracker1[4], myBPlusTree->find(39)); 

	ASSERT_NE(GlobalNodeTracker1[4], myBPlusTree->find(7)); 
	ASSERT_NE(GlobalNodeTracker1[3], myBPlusTree->find(14)); 
	ASSERT_NE(GlobalNodeTracker1[2], myBPlusTree->find(30)); 
	ASSERT_NE(GlobalNodeTracker1[1], myBPlusTree->find(13)); 
	ASSERT_NE(GlobalNodeTracker1[0], myBPlusTree->find(17)); 

    
	for (unsigned int i=0; i<ORDER_M; ++i)
	{
		delete GlobalNodeTracker1[i];
	}
	delete GlobalRoot1;
	delete myBPlusTree;
}



TEST_F(test_BPlusTreeDBMS, TestBPlusTree_FindRange){

	BPlusTree* myBPlusTree = mkBPlusTree1();

	std::vector <Node *> resultSet = myBPlusTree->findRange(15, 28);

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


    
	for (unsigned int i=0; i<ORDER_M; ++i)
	{
		delete GlobalNodeTracker1[i];
	}
	delete GlobalRoot1;
	delete myBPlusTree;
        
        
}


TEST_F(test_BPlusTreeDBMS, TestBPlusTree_InsertInLeaf){

	// TESTing key < keys[0]
	BPlusTree* myBPlusTree = mkBPlusTree1();
	int arr[] = {5, 8};
	Node* Leaf_Example = new Node("test_leaf", 0, true, 2, 
        arr);
	
	// for (unsigned int i=0; i < Leaf_Example->getSlots(); ++i)
	// {
	// 	cout << Leaf_Example->accessKeys()[i] << endl;
	// }	

	myBPlusTree->InsertInLeaf(Leaf_Example, 4);

	// for (unsigned int i=0; i<Leaf_Example->getSlots(); ++i)
	// {
	// 	cout << Leaf_Example->accessKeys()[i] << endl;
	// }	

	ASSERT_TRUE(Leaf_Example->accessKeys()[0] == 4);
	ASSERT_TRUE(Leaf_Example->accessKeys()[1] == 5);
	ASSERT_TRUE(Leaf_Example->accessKeys()[2] == 8);
	delete Leaf_Example;




	// // TESTing key insert in the middle 
	BPlusTree* myBPlusTree1 = mkBPlusTree1();
	int arr1[] = {5, 8};
	Node* Leaf_Example1 = new Node("test_leaf", 0, true, 2, 
        arr1);
	
	// for (unsigned int i=0; i < Leaf_Example1->getSlots(); ++i)
	// {
	// 	cout << Leaf_Example1->accessKeys()[i] << endl;
	// }	

	myBPlusTree1->InsertInLeaf(Leaf_Example1, 7);

	// for (unsigned int i=0; i<Leaf_Example1->getSlots(); ++i)
	// {
	// 	cout << Leaf_Example1->accessKeys()[i] << endl;
	// }	

	ASSERT_TRUE(Leaf_Example1->accessKeys()[0] == 5);
	ASSERT_TRUE(Leaf_Example1->accessKeys()[1] == 7);
	ASSERT_TRUE(Leaf_Example1->accessKeys()[2] == 8);
	delete Leaf_Example1;





	// // TESTing key insert at the END
	BPlusTree* myBPlusTree2 = mkBPlusTree1();
	int arr2[] = {5, 8};
	Node* Leaf_Example2 = new Node("test_leaf", 0, true, 2, 
        arr2);
	
	for (unsigned int i=0; i < Leaf_Example2->getSlots(); ++i)
	{
		cout << Leaf_Example2->accessKeys()[i] << endl;
	}	

	myBPlusTree2->InsertInLeaf(Leaf_Example2, 9);

	for (unsigned int i=0; i<Leaf_Example2->getSlots(); ++i)
	{
		cout << Leaf_Example2->accessKeys()[i] << endl;
	}	

	ASSERT_TRUE(Leaf_Example2->accessKeys()[0] == 5);
	ASSERT_TRUE(Leaf_Example2->accessKeys()[1] == 8);
	ASSERT_TRUE(Leaf_Example2->accessKeys()[2] == 9);
	delete Leaf_Example2;




}





TEST_F(test_BPlusTreeDBMS, TestBPlusTree_GetParentNode){

	BPlusTree* myBPlusTree = mkBPlusTree1();

	Node* Random_N = new Node();


	ASSERT_EQ(NULL, myBPlusTree->getParentNode(Random_N));

	for (unsigned int i = 0; i < ORDER_M; ++i)
	{
		ASSERT_EQ(GlobalRoot1, myBPlusTree->getParentNode(GlobalNodeTracker1[i]));
	}
	


    delete Random_N;
	for (unsigned int i=0; i<ORDER_M; ++i)
	{
		delete GlobalNodeTracker1[i];
	}
	delete GlobalRoot1;
	delete myBPlusTree;
        
        
}


TEST_F(test_BPlusTreeDBMS, TestBPlusTree_InsertInInternalNode)
{
	BPlusTree* myBPlusTree = mkBPlusTree2();
	Node* P = myBPlusTree->getParentNode(GlobalNodeTracker2[4]);
	ASSERT_TRUE(P == GlobalNodeTracker2[0]);

	Node* N = GlobalNodeTracker2[4];

	int arr[] = {17, 18}; 
	Node* NPrime = new Node("NPrime", 2, true, 2, arr);

	int KPrime = NPrime->accessKeys()[0];


	myBPlusTree->InsertInInternalNode(P, N, KPrime, NPrime);

	cout << "CURRENT P->accessKeys()[2]: " << P->accessKeys()[2] << endl; 
	cout << P->accessChildren()[3] << " Should be the same address as " << NPrime << endl;

	ASSERT_EQ(P->accessChildren()[3], NPrime);

	cout << P->accessChildren()[3]->accessKeys()[0] << endl; 
	cout << P->accessChildren()[3]->accessKeys()[1] << endl; 

	cout << "====================" << endl; 

	cout << NPrime->accessKeys()[0] << endl; 
	cout << NPrime->accessKeys()[1] << endl; 


	delete NPrime; 

	for (unsigned int i=0; i<8; ++i)
	{
		delete GlobalNodeTracker2[i];
	}
	delete GlobalRoot2;
	delete myBPlusTree;

}



TEST_F(test_BPlusTreeDBMS, TestBPlusTree_Insert)
{
	BPlusTree* myBPlusTree = mkBPlusTree1();

	cout << "Checking what is in Root Node BEFORE INSERT: " << endl; 
	for (unsigned int i=0; i<GlobalRoot1->getSlots(); ++i)
	{
		cout <<	GlobalRoot1->accessKeys()[i] << " " ;
	}
	cout << endl;

	bool inserted = myBPlusTree->insert(8);

	cout << "Insert successfully? " << std::boolalpha << inserted << endl;

	Node* newLeafNode = myBPlusTree->find(8);

	cout << "Checking what is in Root Node: " << endl; 
	Node* myRootNode = myBPlusTree->getRootNode();
	for (unsigned int i=0; i<myRootNode->getSlots(); ++i)
	{
		cout <<	myRootNode->accessKeys()[i] << " " ;
	}
	cout << endl;

	cout << "Checking what is in Left Child Pointer of Root Node: " << endl; 
	for (unsigned int i=0; i<myRootNode->accessChildren()[0]->getSlots(); ++i)
	{
		cout <<	myRootNode->accessChildren()[0]->accessKeys()[i] << " " ;
	}
	cout << endl;

	cout << "Checking what is in Right Child Pointer of Root Node: " << endl; 
	for (unsigned int i=0; i<myRootNode->accessChildren()[1]->getSlots(); ++i)
	{
		cout <<	myRootNode->accessChildren()[1]->accessKeys()[i] << " " ;
	}
	cout << endl;


	cout << "Checking what is in Left Child Pointer of Root's Left child: " << endl; 
	for (unsigned int i=0; i<myRootNode->accessChildren()[0]->accessChildren()[0]->getSlots(); ++i)
	{
		cout <<	myRootNode->accessChildren()[0]->accessChildren()[0]->accessKeys()[i] << " " ;
	}
	cout << endl;

	cout << "Checking what is in Mid1 Child Pointer of Root's Left child: " << endl; 
	for (unsigned int i=0; i<myRootNode->accessChildren()[0]->accessChildren()[1]->getSlots(); ++i)
	{
		cout <<	myRootNode->accessChildren()[0]->accessChildren()[1]->accessKeys()[i] << " " ;
	}
	cout << endl;


	cout << "Checking what is in MId2 Child Pointer of Root's Left child: " << endl; 
	for (unsigned int i=0; i<myRootNode->accessChildren()[0]->accessChildren()[2]->getSlots(); ++i)
	{
		cout <<	myRootNode->accessChildren()[0]->accessChildren()[2]->accessKeys()[i] << " " ;
	}
	cout << endl;

	cout << "Checking what is in MId2 Child Pointer of Root's Left child: " << endl; 
	for (unsigned int i=0; i<myRootNode->accessChildren()[0]->accessChildren()[2]->getSlots(); ++i)
	{
		cout <<	myRootNode->accessChildren()[0]->accessChildren()[2]->accessKeys()[i] << " " ;
	}
	cout << endl;

	cout << "Checking what is in Left Child Pointer of Root's Right child: " << endl; 
	for (unsigned int i=0; i<myRootNode->accessChildren()[1]->accessChildren()[0]->getSlots(); ++i)
	{
		cout <<	myRootNode->accessChildren()[1]->accessChildren()[0]->accessKeys()[i] << " " ;
	}
	cout << endl;

	cout << "Checking what is in Mid1 Child Pointer of Root's Right child: " << endl; 
	for (unsigned int i=0; i<myRootNode->accessChildren()[1]->accessChildren()[1]->getSlots(); ++i)
	{
		cout <<	myRootNode->accessChildren()[1]->accessChildren()[1]->accessKeys()[i] << " " ;
	}
	cout << endl;

	cout << "Checking what is in Mid2 Child Pointer of Root's Right child: " << endl; 
	for (unsigned int i=0; i<myRootNode->accessChildren()[1]->accessChildren()[2]->getSlots(); ++i)
	{
		cout <<	myRootNode->accessChildren()[1]->accessChildren()[2]->accessKeys()[i] << " " ;
	}
	cout << endl;







	delete newLeafNode; 

	for (unsigned int i=0; i<ORDER_M; ++i)
	{
		delete GlobalNodeTracker1[i];
	}
	delete GlobalRoot1;
	delete myBPlusTree;

}








// Helper functions 
BPlusTree* mkBPlusTree1()
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

	int arr2[ORDER_M] = {14, 15, 16};
	Node* myNodeMid1 = new Node("mid1", 1, true, 3, arr2);

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
	myBPlusTree->setRoot(myNodeRoot);


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







