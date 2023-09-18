#include <iostream>
#include <memory>

/*
	Basic smart pointer
	Smart pointer initialization:
	SmartPtr<TYPE> PTRNAME(POINTER TO OBJECT ADDRESS)

	new int() returns pointer to new integer object
*/

template <class T> class SmartPtr {
    T* ptr;
public:
    explicit SmartPtr(T* p = NULL) {
        ptr = p; 
    }

    ~SmartPtr() {
        delete ptr;
    }

    /* 
        Return memory address of object when smart pointer is dereferenced,
        like a regular pointer.
        Do this by overloading dereferencing method.
    */

    T& operator*() { 
        return *ptr; 
    }

    /*
        return pointer itself when arrow operator is used
        so that members of T can be accessed.
    */

    T* operator->() { 
        return ptr; 
    }

};

class Human {
public:
	int age;

	Human(int age){
		this->age = age;
	}

	int incrementAge(int amount=1){
		if (age > 0) {
			age += amount;
		}
		return age;
	}
};

int main(){
/*
	Types of smart pointers in C++ 11:
	- auto_ptr (deprecated and replaced with unique_ptr)
    - unique_ptr
    - shared_ptr
    - weak_ptr
*/

	// Unique pointer
	std::cout << "[ Unique pointer ] - cannot be copied nor moved without using std::move()\n-----" << std::endl;

	std::unique_ptr<Human> H1(new Human(18));
	std::cout << "Unique ptr H1->age = " << H1->age << std::endl;

	// Giving ownership of pointer to Human object to H2, Since it cannot be copied nor moved without using move()
	std::unique_ptr<Human> H2;
	H2 = std::move(H1);
	std::cout << "Unique ptr H2->age after moving ptr from H1 to H2: " << H2->age << "\n" << std::endl;

	// Shared pointer
	std::cout << "[ Shared pointer ] - can be copied and maintains a use_count for how many pointers to object exist\n-----" << std::endl;

	std::shared_ptr<Human> H3(new Human(17));
	std::cout << "Shared ptr H3->age = " << H3->age << std::endl;

	std::shared_ptr<Human> H4 = H3;
	std::cout << "Shared ptr H4->age where H4 = H3: " << H4->age << std::endl;
	std::cout << "H3.use_count(): " << H3.use_count() << std::endl;
	H4.reset();
	std::cout << "H3.use_count() after H4.reset(): " << H3.use_count() << "\n" << std::endl;

	// Weak pointer
	std::cout << "[ Weak pointer ] - used to observe a shared pointer to a resource, can be temporarily converted to a shared ptr\n-----" << std::endl;

	std::weak_ptr<Human> weakptr = H3;
	if (auto lockedptr = weakptr.lock()){
		std::cout << "weakptr = H3, lockedptr = weakptr.lock() lockedptr->age: " << lockedptr->age << std::endl;
		std::cout << "temporary H3.use_count() while in if block: " << H3.use_count() << std::endl;
	}
	// lockedptr deleted
	std::cout << "H3.use_count() after end of if block: " << H3.use_count() << std::endl;
	H3.reset();
	if (auto lockedptr = weakptr.lock()) {
		std::cout << "IMPOSSIBLE" << std::endl;
	}
	else {
		std::cout << "weakptr.lock() did not return shared_ptr as H3.reset()!\n" << std::endl;
	}

	std::cout << "\nAll pointers deleted after end of program.\n" << std::endl;
	return 0;	
}