#ifndef RECORD_UPDATER_H
#define RECORD_UPDATER_H

#include "SequentialExplorer.h"
#include <fstream>

//Simple class that supports updating a students record (only the grade)
class RecordUpdater
{
private:
	unsigned long long FN; //Faculty number record to update
	unsigned short grade; //New grade for a given student
	SequentialExplorer& explorer; //Referance to a sequential explorer instance

public:
	//Init FN, grade & explorer types
	RecordUpdater(unsigned long long FN, unsigned short grade, SequentialExplorer& explorer);

	bool updateR(); //Update the record and return a state: 0 - Failed to delete, 1 - Success
};

#endif

