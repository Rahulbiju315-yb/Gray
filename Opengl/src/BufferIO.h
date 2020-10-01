#pragma once

#include <string>

class BufferIO
{
private:
	float* data;

public:
	BufferIO();
	~BufferIO();

	void load(std::string filePath);
	void load(float vertices[], unsigned int size);
	
	void write(std::string filePath);
	void clear();
	
	float* getBufferData();
};