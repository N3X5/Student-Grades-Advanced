#ifndef RECORD_DELETER_H
#define RECORD_DELETER_H

#include "SequentialExplorer.h"
#include <fstream>
#include <string>

//Simple class that supports the deletion of a student record
class RecordDeleter 
{
private:
	unsigned long long FN; //Faculty number record to delete
	SequentialExplorer& explorer; //Referance to a sequential explorer instance
public:
	RecordDeleter(unsigned long long FN, SequentialExplorer& explorer); //Init FN & explorer types
	
	bool deleteR(); //Delete the record and return a state: 0 - Failed to delete, 1 - Success
};

#endif

