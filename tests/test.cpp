// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
// #include "../code_1/<HEADER FILE>.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include "test_helpers.hpp"

using namespace std;

class test_x : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_x::total_grade = 0;
double test_x::max_grade = 100;



/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

TEST_F(test_x, TestInsert){
    
    
    string result;
    string expected;
       
    int len = 5;
    
    string commits[] = {"computer", "science", "fun", "difficult", "science"};
    int tabSize = 5;
    
    result = test_insert(commits, len, tabSize);
    
    expected = "0|| science (1,4,)\n1|| \n2|| \n3|| \n4|| difficult (3,)-->fun (2,)-->computer (0,)\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
    
    //testcase 2
    string commits2[] = {"discrete", "math", "test", "computing", "homework"};
    
    result = test_insert(commits2, len, tabSize);
    
    expected = "0|| \n1|| homework (4,)-->math (1,)-->discrete (0,)\n2|| computing (3,)\n3|| test (2,)\n4|| \n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(6);
    

}

//TODO add more tests for insert. Design tests for search from hashTable.


TEST_F(test_x, TESTADD){
    
    
    string result;
    string expected;
       
    string commits3[] = {"f1.txt", "f2.txt"};
    expected = "commitID: 0\ncommit message:\nf1_0.txt -> f2_0.txt\n0|| \n1|| \n2|| \n3|| \n4|| \nList of files in <<.minigit>>: \n";
    result = test_add(commits3, 2, 1);
        
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    
    //testcase2 add new file and No Commit
    string commits4[] = {"f3.txt"};
    expected = "commitID: 0\ncommit message:computer science\nf1_0.txt -> f2_0.txt\ncommitID: 1\ncommit message:\nf1_0.txt -> f2_0.txt -> f3_0.txt\n0|| science (0,)\n1|| \n2|| \n3|| \n4|| computer (0,)\nList of files in <<.minigit>>: \nminigit/f1_0.txt\nminigit/f2_0.txt\n";
    result = test_add(commits4,1,2);
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
}

TEST_F(test_x, TESTRM){
    
    string result;
    string expected;
    
    //test case1 remove first node
    expected = "commitID: 0\ncommit message:computer science\nf1_0.txt -> f2_0.txt\ncommitID: 1\ncommit message:\nf1_0.txt -> f2_0.txt -> f3_0.txt\nAfter delete:\ncommitID: 0\ncommit message:computer science\nf2_0.txt\ncommitID: 1\ncommit message:\nf2_0.txt -> f3_0.txt\n";
    result = test_rm("f1_0.txt");
     ASSERT_EQ(expected, result);
    add_points_to_grade(4);
    
    //test case 2  remove middle node
    expected = "commitID: 0\ncommit message:computer science\nf1_0.txt -> f2_0.txt\ncommitID: 1\ncommit message:\nf1_0.txt -> f2_0.txt -> f3_0.txt\nAfter delete:\ncommitID: 0\ncommit message:computer science\nf1_0.txt\ncommitID: 1\ncommit message:\nf1_0.txt -> f3_0.txt\n";
    result = test_rm("f2_0.txt");
     ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    //test case 3 remove end node
    expected = "commitID: 0\ncommit message:computer science\nf1_0.txt -> f2_0.txt\ncommitID: 1\ncommit message:\nf1_0.txt -> f2_0.txt -> f3_0.txt\nAfter delete:\ncommitID: 0\ncommit message:computer science\nf1_0.txt -> f2_0.txt\ncommitID: 1\ncommit message:\nf1_0.txt -> f2_0.txt\n";
    result = test_rm("f3_0.txt");
     ASSERT_EQ(expected, result);
    add_points_to_grade(5);
}

TEST_F(test_x, TESTCommit){
    
    string result;
    string expected;
    
    //testcase1 initial state with two SLL files
    expected = "commitID: 0\ncommit message:computer science\nf1_0.txt -> f2_0.txt\ncommitID: 1\ncommit message:\nf1_0.txt -> f2_0.txt\n0|| science (0,)\n1|| \n2|| \n3|| \n4|| computer (0,)\nList of files in <<.minigit>>: \nminigit/f1_0.txt\nminigit/f2_0.txt\n";
    result = test_commit(1);
    ASSERT_EQ(expected, result);
    add_points_to_grade(8);
    
    
    //testcase2 first commit, already exist in minigit, not changed
    expected = "commitID: 0\ncommit message:computer science\nf1_0.txt -> f2_0.txt\ncommitID: 1\ncommit message:\nf1_0.txt -> f2_0.txt\n0|| science (0,)\n1|| \n2|| \n3|| \n4|| computer (0,)\nList of files in <<.minigit>>: \nminigit/f1_0.txt\nminigit/f2_0.txt\n";
    result = test_commit(2);
    ASSERT_EQ(expected, result);
    add_points_to_grade(8);
    
    //testcase3 second commit, only first file exist in minigit, one file changed, new file add and commit
    expected = "commitID: 0\ncommit message:computer science\nf1_0.txt -> f2_0.txt\ncommitID: 1\ncommit message:science fun\nf1_1.txt -> f2_0.txt -> f3_0.txt\ncommitID: 2\ncommit message:\nf1_1.txt -> f2_0.txt -> f3_0.txt\n0|| science (0,1,)\n1|| \n2|| \n3|| \n4|| fun (1,)-->computer (0,)\nList of files in <<.minigit>>: \nminigit/f3_0.txt\nminigit/f1_1.txt\nminigit/f1_0.txt\nminigit/f2_0.txt\n";
    result = test_commit(3);
    ASSERT_EQ(expected, result);
    add_points_to_grade(8);
    
    //testcase4 second commit, only second file exist in minigit, one file changed, new file add and commit
   expected = "commitID: 0\ncommit message:computer science\nf1_0.txt -> f2_0.txt\ncommitID: 1\ncommit message:science fun\nf1_0.txt -> f2_1.txt -> f3_0.txt\ncommitID: 2\ncommit message:\nf1_0.txt -> f2_1.txt -> f3_0.txt\n0|| science (0,1,)\n1|| \n2|| \n3|| \n4|| fun (1,)-->computer (0,)\nList of files in <<.minigit>>: \nminigit/f2_1.txt\nminigit/f3_0.txt\nminigit/f1_0.txt\nminigit/f2_0.txt\n";
    result= test_commit(4);
    ASSERT_EQ(expected, result);
    add_points_to_grade(8);
    
    
    //testcase5 third commit after second commit with only sccond file changed, without changing anything before third commit
    expected = "commitID: 0\ncommit message:computer science\nf1_0.txt -> f2_0.txt\ncommitID: 1\ncommit message:science fun\nf1_0.txt -> f2_1.txt -> f3_0.txt\ncommitID: 2\ncommit message:mathematics homework\nf1_0.txt -> f2_1.txt -> f3_0.txt\ncommitID: 3\ncommit message:\nf1_0.txt -> f2_1.txt -> f3_0.txt\n0|| science (0,1,)\n1|| homework (2,)\n2|| \n3|| mathematics (2,)\n4|| fun (1,)-->computer (0,)\nList of files in <<.minigit>>: \nminigit/f2_1.txt\nminigit/f3_0.txt\nminigit/f1_0.txt\nminigit/f2_0.txt\n";
    result = test_commit(5);
    ASSERT_EQ(expected, result);
    add_points_to_grade(8); 
    
    //testcase6  
    expected = "commitID: 0\ncommit message:\nf1_0.txt -> f2_0.txt\ncommitID: 0\ncommit message:computer science\nf1_0.txt -> f2_0.txt\ncommitID: 1\ncommit message:science fun\nf1_1.txt -> f2_0.txt -> f3_0.txt\ncommitID: 2\ncommit message:strawberry cheese\nf1_1.txt -> f2_0.txt -> f3_1.txt\ncommitID: 3\ncommit message:\nf1_1.txt -> f2_0.txt -> f3_1.txt\n0|| science (0,1,)\n1|| cheese (2,)\n2|| \n3|| \n4|| strawberry (2,)-->fun (1,)-->computer (0,)\nList of files in <<.minigit>>: \nminigit/f3_0.txt\nminigit/f1_1.txt\nminigit/f3_1.txt\nminigit/f1_0.txt\nminigit/f2_0.txt\n";
    result = test_commit(6);
    ASSERT_EQ(expected, result);
    add_points_to_grade(8);
    
}

TEST_F(test_x, test_searchHash){
    
    string result;
    string expected;
    expected = "commitID: 0\ncommit message:computer science\nf1_0.txt -> f2_0.txt\ncommitID: 1\ncommit message:science fun\nf1_0.txt -> f2_1.txt -> f3_0.txt\ncommitID: 2\ncommit message:water ocean\nf1_0.txt -> f2_1.txt -> f3_0.txt\ncommitID: 3\ncommit message:mountain water yellow\nf1_0.txt -> f2_1.txt -> f3_1.txt\ncommitID: 4\ncommit message:\nf1_0.txt -> f2_1.txt -> f3_1.txt\n0|| mountain (3,)-->science (0,1,)\n1|| \n2|| water (2,3,)\n3|| yellow (3,)-->ocean (2,)\n4|| fun (1,)-->computer (0,)\nList of files in <<.minigit>>: \nminigit/f2_1.txt\nminigit/f3_0.txt\nminigit/f3_1.txt\nminigit/f1_0.txt\nminigit/f2_0.txt\ncommit IDs containing water 2 3 ";
    result = test_searchHash("water");
    ASSERT_EQ(expected, result);
    add_points_to_grade(8);
}
        
TEST_F(test_x, TESTCheckOut){
    
    string result, expected;
    expected = "commitID: 0\ncommit message:computer science\nf1_0.txt -> f2_0.txt\ncommitID: 1\ncommit message:science fun\nf1_0.txt -> f2_1.txt -> f3_0.txt\ncommitID: 2\ncommit message:water ocean\nf1_0.txt -> f2_1.txt -> f3_0.txt\ncommitID: 3\ncommit message:mountain water yellow\nf1_0.txt -> f2_1.txt -> f3_1.txt\ncommitID: 4\ncommit message:\nf1_0.txt -> f2_1.txt -> f3_1.txt\n0|| mountain (3,)-->science (0,1,)\n1|| \n2|| water (2,3,)\n3|| yellow (3,)-->ocean (2,)\n4|| fun (1,)-->computer (0,)\nList of files in <<.minigit>>: \nminigit/f2_1.txt\nminigit/f3_0.txt\nminigit/f3_1.txt\nminigit/f1_0.txt\nminigit/f2_0.txt\n------------------------------\nOverwriting files into minigit..\nf1_0.txt\nf2_1.txt\nf3_0.txt\nfinished.\n";
    result = test_checkOut("1");
    ASSERT_EQ(expected, result);
    add_points_to_grade(8);
    
}
        
TEST_F(test_x, test_DiffandStatus){
    
    string result;
    string expected;
    expected = "Hello refreshing\npurified drinking water\n\n__________________________________________\nHello refreshing\npurified drinking water\n\n\nwater punch";
    result = test_DiffandStatus("f1_0.txt");
    ASSERT_EQ(expected, result);
    add_points_to_grade(5);
    
    
}
    
