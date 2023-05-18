# DataStructures

Basic implementation of commonly used data structures in C++.
I made this projet to learn how to implement them by myself while improving my C++ skills.
## Implemented Data structures:
### 1. DynamicArray: 
Similar to std::vector class, it is an array that dynamically resizes itself to
hold the data that we add to it.

My implementation is very basic, it uses a simple array and it reallocates 
a new one everytime we need more space for our elements. When less than
a certain percentage of the available space is used it creates a smaller
array and deletes the old one.

The main problem with this implementation is that it calls the default 
contructor for each element in the array when we first create it. 
That's problematic when the contruction of the objects is expensive.

Usage:
```cpp
// Default
DynamicArray<int> myArray;

// Construct with a specific start size (Default is 2 elements)
DyanimcArray<int> myArray(5);

// By copy 
DynamicArray<int> myArray2 = myArray;

// Move is also supported
DynamicArray<int> myArray2 = std::move(myArray);

// With multiple elements
DyanimcArray<int> myArray = {1, 2, 3};

// Copy assign
myArray2 = myArray;

// Move assign
myArray2 = std::move(myArray);

// Acces elements using [] (does not check if index is out of bound)
int a = myArray[1];

// Access using at method (an exception is thrown if index is out of bound)
myArray.at(0);

// Push elements using push_back (has an overload to move complex types)
myArray.push_back(9);

// Push my elements at once (also has move overload)
myArray.push_back({1, 2, 3});

// Pop elements from array
myArray.pop_back();
// 
```
