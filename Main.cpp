#include "CommandParser.h"
#include "SequentialExplorer.h"
#include "RecordDeleter.h"
#include "RecordUpdater.h"
#include "ParseRecord.h"
#include "Definitions.h"

#include <iostream>
#include <string>

using namespace std;

/*
* Some pretext:
*	The RecordUpdater & RecordDeleter classes are not needed as this functionality may also be performed by the SequentialExplorer
*	However, for the sake of simplicity, this split has been implemented
*/

int main()
{
	CommandParser parser; //New command parser; to be used while the program is running

	while(unsigned short command = parser.parseCommand()) //Parse command, which is converted to an integer; terminates when a 0 is received from the parser
	{
		unsigned long long FN;
		cin >> FN; //Read faculty number here as it is needed for all three commands

		SequentialExplorer explorer; //New explorer instance for this command

		if(command == 1) //Update student grade
		{
			unsigned short grade;

			cin >> grade; //Input the grade

			RecordUpdater updater(FN, grade, explorer);  //New record updater class; takes our instance of the sequential explorer

			if (updater.updateR()) //All is good
				cout << RECORD_SAVED;
			else //No such record found for the given FN || or an error occured
				cout << RECORD_NOT_FOUND;

			cout << endl;
		}
		else if (command == 2) //Delete student record
		{
			RecordDeleter deleter(FN, explorer); //New record deleter class; takes our instance of the sequential explorer

			if (deleter.deleteR()) //All is good
				cout << RECORD_DELETED;
			else //No such record found for the given FN || or an error occured
				cout << RECORD_NOT_FOUND;

			cout << endl;
		}
		else if (command == 3) //Search the file for a student
		{
			string record; //Container for a student record
			bool recordFound = 0; //To make sure that we have actually found something

			while (recordIsValid(record = explorer.readRecord())) //Read the file line by line
			{
				if (isMatchingRecord(record, FN)) //Check for a match
				{
					cout << record << endl; //Print the matching record
					recordFound = 1; //Found a match

					break; //No need for further read operations, so break the loop; The sequential explorer will be closed as soon as we leave scope
				}
			}

			if (!recordFound) //No such record found for the given FN || or an error occured
				cout << RECORD_NOT_FOUND << endl;
		}
	}

    return 0;
}

