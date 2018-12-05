#include "RecordUpdater.h"
#include "ParseRecord.h"

#include <iostream>

using namespace std;

//Init FN, grade & explorer types
RecordUpdater::RecordUpdater(unsigned long long FN, unsigned short grade, SequentialExplorer & explorer) : FN(FN), grade(grade), explorer(explorer) {}

/*
* This function reads through the DB file via the sequential explorer.
* When we have found the student, whose record we want to update, we get a put pointer to the start of his record's line and overwrite the whole record
* The new record only differs in regards to the student's grade
*
* IMPORTANT: THIS FUNCTION WILL NOT WORK PROPERLY IF WE WANT TO UPDATE THE LAST RECORD IN THE FILE AND IT ENDS WITH AN EOF, INSTEAD OF A NEWLINE;
* TAKING THE ABOVE INTO ACCOUNT, WE ASSUME THAT THE DB FILE WILL BE PROPERLY FORMATTED
*/
bool RecordUpdater::updateR()
{
	string record; //A container for a student record
	streampos line_pos = ios_base::beg; //A container for a put pointer to the start of a student's record; We begin at the very start of the DB file.
	bool recordUpdated = 0; //Flag to make sure that the operation succeeded
	fstream* &file = explorer.getDBFile(); //Referance to fstream handled by the sequential explorer

	while (recordIsValid(record =explorer.readRecord())) //Read the file line by line
	{
		if (isMatchingRecord(record, FN))  //Check for a match
		{	
			file->seekp(line_pos, ios_base::beg); //Set the put pointer to the start of the current record

			record = record.substr(0, record.size() - 1); //Remove the grade (1 char) from the old record in memory
			record.append(to_string(grade)); //Append the new grade to the updated record in memory

			file->write(record.c_str(), record.length()); //Overwrite the old record with the new one

			recordUpdated = 1; //The operation was a success

			break; //No need to read further, break the read loop
		}

		line_pos = file->tellp(); //Update the put pointer to the start of the next student's record
	}

	return recordUpdated;
}
