#include <iostream>
#include <cassert>
#include <random>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt->ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}


void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	//cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30); // leak here
	//cout << "[" << rbt->ToPrefixString() << "]" << endl;
	rbt->Insert(15);
	//cout << "[" << rbt->ToPrefixString() << "]" << endl;
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	assert(rbt->ToPrefixString() == " B30  R45 ");	
	delete rbt;

	cout << "PASSED!" << endl << endl;
}


void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(10); // Left Left
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Right Left
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
	// symmetry!
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(15); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(35); // Left Right
	assert(rbt->ToPrefixString() == " B35  R30  R45 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	rbt->Insert(55); // Right Right
	assert(rbt->ToPrefixString() == " B45  R30  R55 ");
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	//cout << "rbt: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B15  R10  B45 ");
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	//cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}


void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);

	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	//cout << "["<< rbt.ToPostfixString() << "]"<<endl;
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	//cout << "tree: " << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	// probably should have a delete or something here
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(11);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(15);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(5);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(13);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(7);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(10);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(8);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);

    //cout << "[" << rbt2.ToPrefixString() << "]" << endl;
	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());

	rbt1.Insert(200);
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	cout << "PASSED!" << endl << endl;
}


void TestContains(){
	cout << "Testing Contains..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	assert(rbt->Contains(6) == false);
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);
	
	assert(rbt->Contains(34));
	delete rbt;

	cout << "PASSED!" << endl << endl;
}




void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(15);
	rbt->Insert(31);
	rbt->Insert(55);
	rbt->Insert(12);
	rbt->Insert(17);
	rbt->Insert(29);
	rbt->Insert(34);

	int max = rbt->GetMax();
	int min = rbt->GetMin();

	assert(max==55);
	assert(min==12);

	cout << "PASSED!" << endl << endl;
}




void TestRemoveWithOneChildSimple(){
    cout << "Testing Remove Node With One Child..." << endl;
    RedBlackTree rbt = RedBlackTree();
    rbt.Insert(45);
    rbt.Insert(17);
    rbt.Insert(50);
    rbt.Insert(22);
   // cout << "rbt: [" << rbt.ToPrefixString() << "]" << endl;
    assert(rbt.ToPrefixString() == " B45  B17  R22  B50 ");
    rbt.Remove(17);
    //cout << "rbt: " << rbt.ToPrefixString() << endl;
    assert(rbt.ToPrefixString() == " B45  B22  B50 ");
    cout << "PASSED!" << endl << endl;

    
}


void RemoveTests(){

	cout << "My Remove Tests: " << endl;

    //only one node case - root only
	RedBlackTree* rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Remove(30);
	//cout << rbt->ToInfixString() << endl;
	assert(rbt->ToInfixString() == "");
	cout << "PASSED!"<< endl;


    //only two nodes case, rmeove root
    rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(15);
    rbt->Remove(30);
	//cout << rbt->ToInfixString() << endl;
	assert(rbt->ToInfixString() == " B15 ");
	cout << "PASSED!"<< endl;

    //only two nodes case, remove left child
    rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(15);
    rbt->Remove(15);
	//cout << rbt->ToInfixString() << endl;
	assert(rbt->ToInfixString() == " B30 ");
	cout << "PASSED!"<< endl;

    //only two nodes case, remove right child
    rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(45);
    rbt->Remove(45);
	//cout << rbt->ToInfixString() << endl;
	assert(rbt->ToInfixString() == " B30 ");
	cout << "PASSED!"<< endl;


    //three nodes case, two children, remove left child 
    rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(15);
    rbt->Insert(45);
    rbt->Remove(15);
	//cout << "[" << rbt->ToInfixString() << "]" << endl;
	assert(rbt->ToInfixString() == " B30  R45 ");
	cout << "PASSED!"<< endl;

    //three nodes case, two children, remove right child 
    rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(15);
    rbt->Insert(45);
    rbt->Remove(45);
	//cout << "[" << rbt->ToInfixString() << "]" << endl;
	assert(rbt->ToInfixString() == " R15  B30 ");
	cout << "PASSED!"<< endl;

}


void BigTreeRemoveTests(){

    cout << endl << "Big Tree Remove Tests: " << endl;

    //remove node that has one children (right)
	RedBlackTree* rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(15);
    rbt->Insert(20);
    rbt->Insert(25);
    rbt->Insert(35);
    rbt->Insert(40);
    rbt->Insert(45);
    rbt->Insert(50);
    //cout << rbt->ToInfixString() << endl;
    rbt->Remove(45);
	//cout << rbt->ToInfixString() << endl;
	assert(rbt->ToInfixString() == " B15  R20  B25  B30  B35  R40  B50 ");
	cout << "PASSED!"<< endl;

    //remove node that has one children (left)
	rbt = new RedBlackTree();
    rbt->Insert(30);
    rbt->Insert(15);
    rbt->Insert(20);
    rbt->Insert(25);
    rbt->Insert(35);
    rbt->Insert(40);
    rbt->Insert(45);
    rbt->Insert(43);
    //cout << rbt->ToInfixString() << endl;
    rbt->Remove(45);
	//cout << rbt->ToInfixString() << endl;
	assert(rbt->ToInfixString() == " B15  R20  B25  B30  B35  R40  B43 ");
	cout << "PASSED!"<< endl;

    rbt = new RedBlackTree(); //(case 2)
    rbt->Insert(10);
    rbt->Insert(5);
    rbt->Insert(15);
    rbt->Insert(3);
    rbt->Insert(7);
    rbt->Remove(3);
    //cout << rbt->ToInfixString() << endl;
	assert(rbt->ToInfixString() == " B5  R7  B10  B15 ");
	cout << "PASSED!"<< endl;
}







void TestRightRightCase() {
    std::cout << "Testing Right-Right Case..." << std::endl;

    // Create a new Red-Black Tree and insert nodes to form a right-right case
    RedBlackTree *rbt = new RedBlackTree();
    rbt->Insert(40);
    rbt->Insert(20);
    rbt->Insert(60);
    rbt->Insert(70);

    // Validate the initial tree structure
    std::string expectedBeforeRemoval = " B40  B20  B60  R70 ";
    std::string actualBeforeRemoval = rbt->ToPrefixString();
    std::cout << "Tree before removal: " << actualBeforeRemoval << std::endl;
    assert(actualBeforeRemoval == expectedBeforeRemoval);

    // Remove the node to trigger a right-right rotation
    rbt->Remove(20);

    // Validate the tree structure after removal
    std::string expectedAfterRemoval = " B60  B40  B70 ";
    std::string actualAfterRemoval = rbt->ToPrefixString();
    std::cout << "Tree after removal: " << actualAfterRemoval << std::endl;
    assert(actualAfterRemoval == expectedAfterRemoval);

    // Clean up the tree
    delete rbt;

    std::cout << "PASSED!" << std::endl << std::endl;
}


int main(){

	
	TestSimpleConstructor();
	
	TestInsertFirstNode();
	TestInsertSecondNode();

	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();

	TestToStrings();
	TestInsertRandomTests();

	TestCopyConstructor();

	TestContains();
	TestGetMinimumMaximum();



	TestRemoveWithOneChildSimple();
    RemoveTests();
    BigTreeRemoveTests();
    TestRightRightCase();

	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}