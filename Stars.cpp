//============================================================================
// Name       : Chance Borba
// Class      :  CS 2500
// Due Date   : 10 - 5 -18
// Assignment : Star Map
// Description : This program reads a data set from a grid of numbers and finds the points
// of the values, which is the location of the star.
//============================================================================


#include <iostream>
#include <fstream>
using namespace std;

const int MAPSIZE = 20;
typedef int StarMap[MAPSIZE][MAPSIZE];

// This class contains the member variables and functions required to find stars.
class StarFinder
{
	public:
		void clear();
		void readIn();
		void printOut();
		void findStars();

	private:
		StarMap map;
		ifstream fin;
		ofstream fout;
		int stopX, stopY;
		bool brighter(int, int, int);
		bool isStar(int, int);

};// end class

int main()
{
	StarFinder sf;

	sf.clear();
	sf.readIn();
	sf.printOut();
	sf.findStars();



	return 0;
}//end main

// This function clears the array so that extraneous data is not included on accident
void StarFinder::clear()
{
	for (int x = 0; x < MAPSIZE; x++)
		for (int y = 0; y < MAPSIZE; y++)
			map[x][y] = 0;

}// end clear

// This function reads in the data file
void StarFinder::readIn()
{
	fin.open("rawdata.txt");
	fin >> stopX >> stopY;

	for (int x = 0; x < stopX; x++)
	{
		for (int y = 0; y < stopY; y++)
			fin >> map[x][y];
	}
	fin.close();

}// end readIn

// This function prints out the contents of the array to ensure the file was read properly
void StarFinder::printOut()
{
	for (int x = 0; x < stopX; x++)
	{
		for (int y = 0; y < stopY; y++)
			cout << map[x][y] << " ";

		cout << endl;
	}

	cout << endl;
}// end printOut

// This function makes sure that any attempts to read data from outside of the array
// Will fail as this will keep the program in bounds
bool StarFinder::brighter(int x, int y, int location)
{
	if (x < 0 || y < 0 || x >= stopX || y >= stopY)
		return true;
	else
		return (location >= map[x][y] + 4);

} // end brighter

// This function checks each of the eight directions around a given location on the map
// to determine if that location qualifies as a star, by calling the brighter function
bool StarFinder::isStar(int x, int y)
{
	return (brighter(x - 1, y - 1, map[x][y]) &&
		   brighter(x -1, y, map[x][y]) &&
		   brighter(x - 1, y + 1, map[x][y]) &&
		   brighter(x, y + 1, map[x][y]) &&
		   brighter(x + 1, y + 1, map[x][y]) &&
		   brighter(x + 1, y, map[x][y]) &&
		   brighter(x + 1, y - 1, map[x][y]) &&
		   brighter(x, y - 1, map[x][y]));

} // end isStar

// This function creates a file that places stars in the locations of the array
void StarFinder::findStars()
{
	fout.open("stars.txt");

	for (int x = 0; x < stopX; x++)
	{
		for (int y = 0; y < stopY; y++)
		{
			if (isStar(x, y) == true)
			{
				fout << "* ";
				cout << "Star found at the following coordinates: ";
				cout << "(" << x << ", " << y << ")" << endl;

			} // end if
			else
				fout << ". ";

		}// end inner for
		fout << endl;

}// end outer for
		fout.close();

}// end findStars


