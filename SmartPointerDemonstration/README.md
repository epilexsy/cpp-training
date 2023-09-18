# Trying out Smart pointers in C++


## Problems with Normal Pointers <sup>Source: GFG</sup>

Some Issues with normal pointers in C++ are as follows:
    - Memory Leaks: This occurs when memory is repeatedly allocated by a program but never freed. This leads to excessive memory consumption and eventually leads to a system crash. 
    - Dangling Pointers: A dangling pointer is a pointer that occurs at the time when the object is de-allocated from memory without modifying the value of the pointer.
    - Wild Pointers: Wild pointers are pointers that are declared and allocated memory but the pointer is never initialized to point to any valid object or address.
    - Data Inconsistency: Data inconsistency occurs when some data is stored in memory but is not updated in a consistent manner.
    - Buffer Overflow: When a pointer is used to write data to a memory address that is outside of the allocated memory block. This leads to the corruption of data which can be exploited by malicious attackers.