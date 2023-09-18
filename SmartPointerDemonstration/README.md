# Trying out Smart pointers in C++
Concept/Demo code for reference in the future.
<br>

## Problems with Normal Pointers 

Some Issues with normal pointers in C++ are as follows:  <sup>Source: GFG</sup>

 - **Memory Leaks**: This occurs when memory is repeatedly allocated by a program but never freed. This leads to excessive memory consumption and eventually leads to a system crash.
 - **Dangling Pointers:** A dangling pointer is a pointer that occurs at the time when the object is de-allocated from memory without modifying the value of the pointer.
 - **Wild Pointers:** Wild pointers are pointers that are declared and allocated memory but the pointer is never initialized to point to any valid object or address.
 - **Data Inconsistency:** Data inconsistency occurs when some data is stored in memory but is not updated in a consistent manner.
 - **Buffer Overflow:** When a pointer is used to write data to a memory address that is outside of the allocated memory block. This leads to the corruption of data which can be exploited by malicious attackers.

Output:
```
[ Unique pointer ] - cannot be copied nor moved without using std::move()
-----
Unique ptr H1->age = 18
Unique ptr H2->age after moving ptr from H1 to H2: 18

[ Shared pointer ] - can be copied and maintains a use_count for how many pointers to object exist
-----
Shared ptr H3->age = 17
Shared ptr H4->age where H4 = H3: 17
H3.use_count(): 2
H3.use_count() after H4.reset(): 1

[ Weak pointer ] - used to observe a shared pointer to a resource, can be temporarily converted to a shared ptr
-----
weakptr = H3, lockedptr = weakptr.lock() lockedptr->age: 17
temporary H3.use_count() while in if block: 2
H3.use_count() after end of if block: 1
weakptr.lock() did not return shared_ptr as H3.reset()!


All pointers deleted after end of program.
```
