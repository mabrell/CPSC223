#include "Station.h"
#include "LinkedList.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Constants
const int FAIL = -1;


int main(int argc, char* argv[])
{
	//cout << "it started";
	ofstream outfile;
	outfile.open("test_file.out");

	LinkedList list;
	Station s1("station1", true);
	Station s2("station2", false);

	list.insertStation(s1);
	list.insertStation(s2);

	Station temp = list.getNextStation();
	LinkedList list2 = LinkedList(list);
	
	list.removeStation(s1);

	list2 = list;

	list2.removeStation(s2);
	LinkedList list3 = LinkedList(list2);


	list.print(outfile);
	list3.print(outfile);

	if ( list.isCurrPosNull()) // check list
	{
		cout << "it's null!";
	}
	outfile.close();
	return 0;
}