#ifndef SEQUENTIAL_EXPLORER_H
#define SEQUENTIAL_EXPLORER_H

#include <string>
#include <fstream>

/*
* The sequential explorer has two main functions:
*	1) Explore the file line by line and return the relevant student record
*	2) Provide active access to the current stream, so that further write / read operation may be performed
*/
class SequentialExplorer
{
private:
	std::fstream* input; //Our current input file
	void closeReader(); //Close the reader; Called either on destruction of the instance || when we've read  through the whole file
public:
	SequentialExplorer(); //Open the current DB file
	~SequentialExplorer(); //Close the stream and delete input fstream

	std::string readRecord(); //Read a single record

	std::fstream* &getDBFile(); //Provide access to the current stream
};

#endif
