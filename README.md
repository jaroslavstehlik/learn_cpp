# learn_cpp
Small little project where I am trying to learn c++.    
So far implemented.  

### mstr::unique_pointer<T>

- Class which manages the lifetime of a raw pointer.  
- It cannot be copied, which prevents dangling pointers.  
- It can be moved, which changes ownership.  
- When destroyed or reset it releases the content of the pointer.  

### mstr::shared_pointer<T>

- Class which manages the lifetime of a raw pointer using a reference counter.  
- The reference counter is implemented using a raw pointer to an int.  
- It can be copied, which increases the reference count.  
- It can be moved, which changes ownership.  
- Only when all references are destroyed, the underlying raw pointer is released.    

### mstr::vector<T>

- Class which manages array allocation and de-allocation.  
- It does not support capacity yet.  
- When the vector size is increased or decreased, new dynamic array is created,   
  all elements are moved to the newly created array  
  and the previous array is destroyed.  
- It uses the std::allocator and de-allocator to prevent premature element construction.    

## What I have learned from this so far

- **constructor**  
  usually allocates resources


- **copy constructor**  
  usually allocates resources by copying contents of other class instance


- **move constructor**  
  moves resources and invalidates the contents of other class instance


- **copy assignment operator**  
  releases any existing resources  
  and does the same thing as copy constructor


- **move assignment operator**  
  releases any existing resources    
  and does the same thing as move constructor


- **destructor**  
  releases resources


- **de-referencing and decrementing value**  
  (*ptr)-- is not the same as *ptr--;  


- **Vector capacity allocation**  
  does not cause underlying type allocation unless pushed or emplaced or inserted.


- **Vector emplace**  
  method itself moves arguments to correct place, do not encapsulate using { } causes copy


- **Vector front and back**  
  is not the same as begin and end.
