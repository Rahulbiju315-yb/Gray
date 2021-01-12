Default constructor - alloc mem for refCount. make its value 1
Constructor for NoCopy - refCount = nullptr
Copy constructor - copy; increase refCount if other object has non-null refCount, else dont;
Destructor - if refCount is not null :: check if refCount's value is 1 - then delete resource from memory
										else decrement its value
			 else				     :: do nothing

									