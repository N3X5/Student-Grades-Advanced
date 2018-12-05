#include "SequentialExplorer.h"
#include "Definitions.h"

using namespace std;

SequentialExplorer::SequentialExplorer()
{
	input = new fstream(STUDENT_GRADES_DB); //New file stream
}

SequentialExplorer::~SequentialExplorer()
{
	closeReader(); //Close the stream (if not already closed)
	delete input; //Destroy input fstream object
}

std::string SequentialExplorer::readRecord()
{
	string result = RECORD_NOT_FOUND; //Default return if there are no records || or if we reach EOF
	string line; // tmp line to store record

	if (getline(*input, line)) //If we have  a record =>
		result = line; //Assign that record to the result of the func
	else
		closeReader(); //Close the stream if there are no more records || if an error is encountered;

	//^ With referance to the above, please take note that once instance of this class only explores the file once!

	return result;
}

std::fstream *& SequentialExplorer::getDBFile()
{
	return input; //Return a reference to our current stream, which may not be in its initial state
}

void SequentialExplorer::closeReader()
{
	input->close(); //Close the stream
}

