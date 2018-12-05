#include "RecordDeleter.h"
#include "ParseRecord.h"
#include "Definitions.h"
#include <cstring>

using namespace std;

//Init FN & explorer types
RecordDeleter::RecordDeleter(unsigned long long FN, SequentialExplorer& explorer) : FN(FN), explorer(explorer) {}

/*
* This functions read ALL of the data from the DB file and writes it to a new tmp file.
* One line is skipped in the new file, only if a matching record is found (the one that has to be deleted)
*/
bool RecordDeleter::deleteR()
{
	ofstream output; //New ofstream for the tmp file

	output.open("StudentsGrades.tmp", ios::app); //Open the tmp file in append mode
	
	string record; //A container for a student record
	bool recordDeleted = 0; //Flag to make sure that the operation worked

	while (recordIsValid(record = explorer.readRecord())) //Read the file line by line
	{
		if (!isMatchingRecord(record, FN)) //Check that we don't have a match
			output << record << endl; //Write that record to the tmp file
		else //We have a match
			recordDeleted = 1; //Don't write that record; Only flag the operation as successful
	}

	output.close(); //All of the data has been written, so close the tmp file

	if (recordDeleted)
	{
		remove(STUDENT_GRADES_DB); //Remove old DB file
		rename("StudentsGrades.tmp", STUDENT_GRADES_DB); //Rename tmp file
		return recordDeleted;
	}
	else
	{
		remove("StudentsGrades.tmp"); //The operation failed, so delete the tmp file
		return recordDeleted;
	}
}
