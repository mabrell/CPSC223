//Test driver
#include "BSTNode.h"
#include "pretty_print.h"
#include "BSTree.h"
#include "AVLTree.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;


int main(int argc, char* argv[])
{
	// BSTNode n1(46);
	// n1.insert(50);
	// n1.insert(47);
	// n1.insert(55);
	// n1.insert(66);
	// n1.insert(30);

	// n1.insert(49);
	// n1.insert(8);
	// n1.insert(47);
	// n1.remove(46);
	// n1.remove(12);

	// n1.insert(36);
	
	// print_pretty(n1, 1, 0, cout);
	// print_pretty(*n1.avl_balance(), 1, 0, cout);

	AVLTree* spruce = new AVLTree();
	
	for (int i = 0; i<10; i++)
	{
		spruce->insert(i);
		spruce->print_tree();
	}
	

	spruce->remove(7);
	spruce->remove(9);
	spruce->print_tree();
	delete(spruce);
	return 0;
}
