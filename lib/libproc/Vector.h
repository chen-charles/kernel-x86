#ifndef VECTOR_H
#define VECTOR_H
/********************************
 * COP 4530
 * FSU Department of Computer Sience
 * retrieved from https://github.com/rkk09c/Vector 
 * modified
 ********************************/

//#include <iostream>
//#include <stdexcept>

#ifndef NULL
#define NULL    0
#endif

template <typename T>
class Vector {
 public:
    // iterator support
    typedef T* iterator;
    typedef const T* const_iterator;

    // constructor, destructor, and copy constructor
    Vector<T>()
    {
        theSize = 0;
        theCapacity = 0;
        array = NULL;
    }; // default zero parameter constructor
    
    Vector<T>(const Vector &rhs)
    {
        operator=(rhs);
    }; // copy constructor
    
    
    // num elements with value of val
    explicit Vector<T>(int num, const T& val = T())
    {
        theSize = num;
        theCapacity = num;
        array = new T[theCapacity];
        for (int i = 0; i < theSize; i++)
            array[i] = val;
    };
    
    // constructs with elements [start, end)
    Vector<T>(const_iterator start, int num)
    {
        theSize = num;
        theCapacity = num;
        array = new T[theCapacity];
        for (int i = 0; i < theSize; i++) {
            array[i] = *start;
            start++;
        }
    };

    ~Vector<T>()
    {
        delete [] array;
        array = 0;
    }; // destructor

    // operators

    // index operator
    T& operator[](int index)
    {
        return array[index];
    };
    const T& operator[](int index) const
    {
        return array[index];
    };

    // assignment operator
    const Vector& operator=(const Vector &rhs)
    {
        if (this != &rhs) {
            delete [] array;
            theSize = rhs.size();
            theCapacity = rhs.theCapacity;
            array = new T[ capacity()];
            for (int i = 0; i < size(); i++)
                array[i] = rhs.array[i];
        }
        return *this;
    }

    // at function. safer than operator[]
    T& at(int loc )
    {
        if (loc > theSize) {
    //        throw out_of_range("Out of range\n");
            return *new T();
        } else
            return array[loc];
    };
    const T& at(int loc ) const
    {
        if (loc > theSize) {
    //        throw out_of_range("Out of range value\n");
            return *new T();
        } else
            return array[loc];
    };

    T &front()
    {
        return array[0];
    }; // reference to the first element
    const T& front() const
    {
        return array[0];
    };
    T &back()
    {
        return array[theSize - 1];
    }; // reference to the last element
    const T & back() const
    {
        return array[theSize - 1];
    };

    // accessor member functions
    int size() const
    {
        return theSize;
    }; // number of elements
    int capacity() const
    {
        return theCapacity + 1;
    }; // capacity of vector
    bool empty() const
    {
        if (size() == 0)
            return true;
        else
            return false;
    }; // check if list is empty

    // mutator member functions
    void clear()
    {
        delete [] array;
        theSize = 0;
    }; // delete all elements
    

    void push_back(const T & val)
    {
        if (theSize == theCapacity)

            reserve(2 * theCapacity + 1);

        array[theSize++] = val;
    }; // insert to the end
    T pop_back()
    {
        theSize--;
        return *array;
    }; // delete and return last element
    void push_front(const T & val)
    {
        if (theSize == theCapacity)
            reserve(size());
        for (int i = theSize; i > 0; i--)
            array[i + 1] = array[i];

        array[0] = val;
    }; // insert to the end
    T pop_front()
    {
        for (int i = 0; i < theSize; i++) {
            array[i] = array[i + 1];
        }
        theSize--;
    return *array;
    }; // delete and return first element


    void resize(int newSize)
    {
        if (newSize > theCapacity)
            reserve(newSize * 2 + 1);
        else
            theSize = newSize;
    }; // resize vector
    void reserve(int newCapacity)
    {
        if (newCapacity < theSize)
            return;

        T *oldArray = array;

        array = new T[ newCapacity ];
        for (int k = 0; k < theSize; k++)
            array[k] = oldArray[k];

        theCapacity = newCapacity;

        delete [] oldArray;
    }; // reserve memory

    // print out all elements. ofc is deliminitor
//    void print(std::ostream& os, char ofc = ' ') const;

    // iterator support
    iterator begin(){return &array[0];}; // iterator to first element
    const_iterator begin() const{return &array[0];};
    iterator end(){return &array[theSize];}; // end marker iterator
    const_iterator end() const{return &array[theSize];};
    iterator insert(iterator itr, const T& val)
    {
        iterator itr1;
        if (theSize == theCapacity || theSize == 0)
            reserve(size());

        for (itr1 = end(); itr1 > itr; --itr1) {
            *itr1 = --*itr1;
        }
        *itr = val;
    }; // insert val ahead of itr
    iterator erase(iterator itr)
    {
        while (itr != end()) {
            *itr = ++*itr;
            ++itr;
        }
        theSize--;
        return itr;
    }; // erase one element
    iterator erase(iterator start, iterator end)
    {
    begin = &array[0];
        end = &array[theSize];

        *begin = *(end - 1);
        theSize = 1;
        return begin;
    }; // erase [start, end)


private:
    int theSize; // number of elements
    int theCapacity; // number of elements that can be stored
    T *array; // dynamic array to store elements.

    void doubleCapacity()
    {
        if (theCapacity == 0)
            theCapacity = 1;
        else
            2 * theCapacity + 1;
    };
}; // end of class Vector

// overloading comparison operators
template <typename T>
bool operator==(const Vector<T> & lhs, const Vector<T> &rhs)
{
    int flag_chk = 0;
    if (lhs.size() == rhs.size()) {
        for (int i = 0; i < lhs.size(); i++) {
            if (lhs[i] != rhs[i]) {
                flag_chk = 1;
            }
        }
        if (flag_chk == 1) return false;
        else return true;
    } else
        return false;
}

template <typename T>
bool operator!=(const Vector<T> & lhs, const Vector<T> &rhs)
{
    int flag_chk = 0;
    if (lhs.size() != rhs.size()) {
        for (int i = 0; i < lhs.size(); i++) {
            if (lhs[i] == rhs[i]) {
                flag_chk = 1;
            }
        }
        if (flag_chk == 1) return false;
        else return true;
    } else
        return false;
};

// overloading output operator
//template <typename T>
//std::ostream& operator<<(std::ostream &os, const Vector<T> &v);

// include the implementation file here

#endif
