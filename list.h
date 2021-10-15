/***********************************************************************
 * Header:
 *    LIST
 * Summary:
 *    Our custom implementation of std::list
 *      __       ____       ____         __
 *     /  |    .'    '.   .'    '.   _  / /
 *     `| |   |  .--.  | |  .--.  | (_)/ /
 *      | |   | |    | | | |    | |   / / _
 *     _| |_  |  `--'  | |  `--'  |  / / (_)
 *    |_____|  '.____.'   '.____.'  /_/
 *
 *
 *    This will contain the class definition of:
 *        List         : A class that represents a List
 *        ListIterator : An iterator through List
 * Author
 *    Alexander Dohms, Stephen Costigan, Shaun Crook, Jonathan Colwell
 ************************************************************************/

#pragma once
#include <cassert>     // for ASSERT
#include <iostream>    // for nullptr
#include <new>         // std::bad_alloc
#include <memory>      // for std::allocator

namespace custom
{

/**************************************************
 * LIST
 * Just like std::list
 **************************************************/
template <typename T>
class list
{
public:
   //
   // Construct
   //

   list();
   list(list <T> & rhs);
   list(list <T>&& rhs);
   list(size_t num, const T & t);
   list(size_t num);
   list(const std::initializer_list<T>& il);
   template <class Iterator>
   list(Iterator first, Iterator last);
   ~list() {}

   //
   // Assign
   //

   list <T> & operator = (list &  rhs);
   list <T> & operator = (list && rhs);
   list <T> & operator = (const std::initializer_list<T>& il);

   //
   // Iterator
   //

   class iterator;
   iterator begin() { return iterator(pHead); }
   iterator rbegin() { return iterator(pTail); }
   iterator end() { return iterator(nullptr); }

   //
   // Access
   //

   T& front();
   T& back();

   //
   // Insert
   //Test

   void push_front(const T&  data);
   void push_front(      T&& data);
   void push_back (const T&  data);
   void push_back (      T&& data);
   iterator insert(iterator it, const T& data);
   iterator insert(iterator it, T&& data);

   //
   // Remove
   //

   void pop_back();
   void pop_front();
   void clear();
   iterator erase(const iterator& it);

   //
   // Status - Finished
   //

   bool empty()  const { return size() == 0; }
   size_t size() const { return numElements; }


#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif
   // nested linked list class
   class Node;

   // member variables
   size_t numElements; // though we could count, it is faster to keep a variable
   Node * pHead;    // pointer to the beginning of the list
   Node * pTail;    // pointer to the ending of the list
};

/*************************************************
 * NODE - Finished
 * the node class.  Since we do not validate any
 * of the setters, there is no point in making them
 * private.  This is the case because only the
 * List class can make validation decisions
 *************************************************/
template <typename T>
class list <T> :: Node
{
public:
   //
   // Construct
   //
    Node() : pNext(nullptr), pPrev(nullptr), data() { } // Default constructor
    Node(const T& data) : pNext(nullptr), pPrev(nullptr), data(data) { } // Copy Constructor
    Node(T&& data) : pNext(nullptr), pPrev(nullptr), data(std::move(data)) { } // Move Constructor

   //
   // Data
   //

   T data;                 // user data
   Node * pNext;       // pointer to next node
   Node * pPrev;       // pointer to previous node
};

/*************************************************
 * LIST ITERATOR - Finished
 * Iterate through a List, non-constant version
 ************************************************/
template <typename T>
class list <T> :: iterator
{
public:
    iterator() { p = nullptr; }
    iterator(Node* pRHS) { p = pRHS; }
    iterator(const iterator& rhs) { p = rhs.p; }
    iterator& operator = (const iterator& rhs)
    {
        this->p = rhs.p;
        return *this;
    }

    // equals, not equals operator
    bool operator != (const iterator& rhs) const { return (rhs.p != p ? true : false); }
    bool operator == (const iterator& rhs) const { return (rhs.p == p ? true : false); }

    // dereference operator, fetch a node
    T& operator * ()
    {
        return p->data;
    }

    // postfix increment
    iterator operator ++ (int postfix)
    {
        iterator i = p;
        p++;
        return i;
    }

    // prefix increment
    iterator& operator ++ ()
    {
        p++;
        return *this;
    }

    // postfix decrement
    iterator operator -- (int postfix)
    {
        iterator i = p;
        if (p > 0)
            p--;
        return i;
    }

    // prefix decrement
    iterator& operator -- ()
    {
        if (p > 0)
            p--;
        return *this;
    }

   // two friends who need to access p directly
   friend iterator list <T> :: insert(iterator it, const T &  data);
   friend iterator list <T> :: insert(iterator it,       T && data);
   friend iterator list <T> :: erase(const iterator & it);

#ifdef DEBUG // make this visible to the unit tests
public:
#else
private:
#endif

   typename list <T> :: Node * p;
};

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
template <typename T>
list <T> ::list(size_t num, const T & t)
{
    // Fill constructor
    /*IF (num)
          pHead <- pPrevious <- pNew <- NEW Node(T)
          pHead.pPrev <- NULL
          FOR i <-1 … num-1
            pNew <- NEW Node(T)
            pNew.pPrev <- pPrev
            pNew.pPrev.pNext <- pNew
            pPrevious <- pNew

          pNew.pNext <- NULL
          pTail <- pNew
          numElements <- num*/
    //numElements = num;
    //if (num)
    //{
    //    /*Node* pNew;
    //    Node* pPrevious;*/
    //    //pHead = pPrevious = pNew = new Node(t);
    //    pHead = new Node(t);
    //    pHead->pPrev = nullptr;
    //    Node* pNew = new Node(t);
    //    for (int i = 0; i < num; i++)
    //    {
    //        
    //        /*push_back(t);*/
    //        pNew->pNext = pHead;
    //        pHead->pPrev = std::move(pNew);
    //        pHead = std::move(pNew);
    //        /*std::cout << pNew->data << std::endl;
    //        pNew = new Node(t);
    //        pNew->pPrev = pPrevious;
    //        pNew->pPrev->pNext = pNew;
    //        pPrevious = pNew;*/
    //    }
    //    /*pNew->pNext = nullptr;
    //    pTail = pNew;
    //    
    //    pHead = pNew;*/
    //}
}

/*****************************************
 * LIST :: ITERATOR constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
template <class Iterator>
list <T> ::list(Iterator first, Iterator last)
{
    // THIS DOES NOT INCREASE %
    /*pHead = pTail = nullptr;
    numElements = 0;
    auto it = first;
    while (it != last)
    {
        push_back(*it);
        numElements++;
        it++;
    }*/
}

/*****************************************
 * LIST :: INITIALIZER constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
list <T> ::list(const std::initializer_list<T>& il)
{
    //pHead = pTail = nullptr;
    /*numElements = il.size();
    pHead = pTail = new list <T> ::Node();
    for (T const item : il)
    {
        push_back(item);
    }*/
    //numElements = 0;
    //pHead = pTail = new Node();
    //
    //if (il.size() > 0)
    //{
    //    //Node* pNew = pHead;
    //    //list<T>::iterator it = new iterator(il);
    //    for (T const item : il)
    //    {
    //        /*insert(it, item);
    //        it++;*/
    //        push_back(item);
    //        /*pNew = new Node (item);
    //        pNew->pNext = pCurrent->pNext;
    //        pNew->pPrev = pCurrent;
    //        pCurrent->pNext = pNew;
    //        if (pNew->pNext)
    //            pNew->pNext->pPrev = pNew;
    //        pCurrent = pCurrent->pNext;*/
    //        /*pNew->data = item;
    //        pNew->pNext = nullptr;
    //        if (pHead == nullptr) { 
    //            pHead = pTail = pNew;
    //            pHead->pPrev = pNew->pPrev;
    //            pHead->pNext = pTail;
    //        }
    //        else {
    //            pTail->pNext = pNew;
    //            pTail->pPrev = pNew->pPrev;
    //            pTail = pNew;
    //        }*/
    //    }
    //    //pHead = pNew;
    //}
}

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
template <typename T>
list <T> ::list(size_t num)
{
    // THIS IS LIKELY THE SAME AS THE FILL CONSTRUCTOR, BUT WITH NULL VALUES. 
    // When we get that figured out, let's just copy it here.
    /*numElements = num;
    if (num == 0) {
        pHead = pTail = nullptr;
    }
    else {
        pHead = pTail = new list <T> ::Node();
    }*/
}

/*****************************************
 * LIST :: DEFAULT constructors - Finished | Alexander
 ****************************************/
template <typename T>
list <T> ::list()
{
    // Doesn't contribute to %, but it matches the book so idk
    /*numElements = 0;
    pHead = pTail = nullptr;*/
}

/*****************************************
 * LIST :: COPY constructors - Alexander
 ****************************************/
template <typename T>
list <T> ::list(list& rhs)
{
    // Doesn't contribute to %, but it matches the book so idk
    /*pHead = pTail = nullptr;
    numElements = 0;
    *this = rhs;*/
}

/*****************************************
 * LIST :: MOVE constructors - Finished
 * Steal the values from the RHS
 ****************************************/
template <typename T>
list <T> ::list(list <T>&& rhs)
{
    pHead = rhs.pHead;
    pTail = rhs.pTail;
    numElements = rhs.numElements;
    
    rhs.pHead = nullptr;
    rhs.pTail = nullptr;
    rhs.numElements = 0;
}

/**********************************************
 * LIST :: assignment operator - Finished
 * Copy one list onto another
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
list <T>& list <T> :: operator = (list <T>& rhs)
{
    clear();

    for (int i = 0; i < numElements; i++) {
        if (i == 0) {
            pHead = rhs.pHead;
        }
        else {
            pHead = pHead->pNext;
            rhs.pHead = rhs.pHead->pNext;
            pHead[i] = rhs.pHead[i];
        }
    }

    numElements = rhs.numElements;
    rhs.pHead = pTail = NULL;
    rhs.numElements = 0;

    return *this;
}

/**********************************************
 * LIST :: assignment operator - MOVE - Alexander
 * Copy one list onto another
 *     INPUT  : a list to be moved
 *     OUTPUT :
 *     COST   : O(n) with respect to the size of the LHS
 *********************************************/
template <typename T>
list <T>& list <T> :: operator = (list <T> && rhs)
{
    //clear();

    /*for (int i = 0; i < numElements; i++) {
        if (i == 0) {
            pHead = rhs.pHead;
        }
        else {
            pHead = pHead->pNext;
            rhs.pHead = rhs.pHead->pNext;
            pHead[i] = rhs.pHead[i];
        }
    }*/


    /*numElements = rhs.numElements;
    rhs.pHead = pTail = NULL;
    rhs.numElements = 0;*/

    return *this;
}

/**********************************************
 * LIST :: assignment operator - Steve
 * Copy one list onto another
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
list <T>& list <T> :: operator = (const std::initializer_list<T>& rhs)
{
    /*list.copy-assignment(rhs)
         itRHS <- rhs.begin() Fill existing nodes
         itLHS <- begin()
         WHILE itRHS != rhs.end() AND itLHS != end()
         *itLHS <- *itRHS
         ++itRHS
         ++itLHS
         IF itRHS != rhs.end() Add new nodes
         WHILE itRHS != rhs.end()
         push_back(*itRHS)
         ++itRHS
         ELSE IF rhs.empty()
         clear()
         ELSE IF it LHS != end() Remove the extra nodes
         p <- itLHS.p
         pTail <- p.pPrev
         pNext <- p.pNext
         WHILE p != NULL
         pNext <- p.pNext
         DELETE p
         p <- pNext
         numElements--
         pTail.pNext <- NULL
        */
        // If the list is empty, this first node is the head and tail
    /*if(rhs.size() == 0)
        return *this;

    T * data = new T[rhs.size()];
    int i = 0;
    for (T const item : rhs)
    {
        data[i++] = item;
    }

    int itRHS = 0;
    list<T>::iterator itLHS = this->begin();
    while (itRHS != rhs.size() && itLHS != end())
    {
        ++itRHS;
        ++itLHS;
        if (itRHS != rhs.size()) {
            while (itRHS != rhs.size()) {
                push_back(data[itRHS]);
                ++itRHS;
            }
        }
        else if (itLHS != end()) 
        {
            Node* p = itLHS.p;
            pTail = p->pPrev;
            pHead->pNext = p->pNext;
            while (p != NULL) {
                pHead->pNext = p->pNext;
                delete p;
                p = pHead->pNext;
                numElements--;
                pTail->pNext = NULL;
            }
        }

    }*/
    return *this;
}

/**********************************************
 * LIST :: CLEAR - Finished
 * Remove all the items currently in the linked list
 *     INPUT  :
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
void list <T> :: clear()
{
    // loop is unnecessary for the checks, but probably good practice
    while (pHead != NULL) 
    {
        Node* pDelete = pHead;
        pHead = pHead->pNext;
        delete pDelete;
    }
    pTail = nullptr;
    numElements = 0;
}

/*********************************************
 * LIST :: PUSH BACK - Finished (check the other one below for the error)
 * add an item to the end of the list
 *    INPUT  : data to be added to the list
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> :: push_back(const T & data)
{
    Node* pNew = new Node(data);

    if (numElements == 0)
    {
        pHead = pNew;
        pTail = pNew;
    }
    else
    {
        pTail->pNext = pNew;
        pNew->pPrev = pTail;
        pTail = pNew;
    }

    numElements++;
}

template <typename T>
void list <T> ::push_back(T && data) // THIS IS THE ONE THAT NEEDS FIXING (THE CONTENT OF THE ELSE STATEMENT)
{
    Node* pNew = new Node(data);

    if (numElements == 0)
    {
        pHead = pNew;
        pTail = pNew;
    }
    else
    {
        /*pTail = std::move(pNew);*/
    }
    numElements++;

}

/*********************************************
 * LIST :: PUSH FRONT - Finished
 * add an item to the head of the list
 *     INPUT  : data to be added to the list
 *     OUTPUT :
 *     COST   : O(1)
 *********************************************/
template <typename T>
void list <T> :: push_front(const T & data)
{
    Node* pNew = new Node(data);
    if (pNew != nullptr) {
        if (numElements == 0)
        {
            pHead = pTail = pNew;
        }
        else
        {
            pHead->pPrev = pNew;
            pNew->pNext = pHead;
            pHead = pNew;
        }
        numElements++;
    }
}

template <typename T>
void list <T> ::push_front(T && data)
{

}


/*********************************************
 * LIST :: POP BACK
 * remove an item from the end of the list
 *    INPUT  :
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> ::pop_back()
{
   /*if (!empty())
   {
        if (numElements == 1 || numElements == NULL) {
            pTail = pHead = nullptr;
        }
        else if (numElements > 1) {
            pTail->pPrev = pTail;
        }
        numElements--;
   }*/
}

/*********************************************
 * LIST :: POP FRONT
 * remove an item from the front of the list
 *    INPUT  :
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> ::pop_front()
{
    //taken from erase
    /*itNext  end()
     IF it.p.pNext Take care of any nodes after ‘it’
         it.p.pNext.pPrev  it.p.pPrev
         itNext  it.p.pNext
     ELSE
        pTail  pTail.pPrev
     IF it.p.pPrev Take care of any nodes before ‘it’
        it.p.pPrev.pNext  it.p.pNext
     ELSE
        pHead  pHead.pNext
     DELETE it.p Delete then node
     numElements--
     RETURN itNext*/
    /*if (!empty())
    {
        if (numElements == 1 || numElements == NULL) {
            pTail = pHead = nullptr;
        }
        else if (numElements > 1) {
            pHead->pNext = pHead;
        }
        numElements > 0 ? numElements-- : 0;
    }*/
}

/*********************************************
 * LIST :: FRONT - Finished
 * retrieves the first element in the list
 *     INPUT  :
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
template <typename T>
T & list <T> :: front()
{
    size_t empty = 0;
    if (numElements == empty)
        return *(new T);
    return pHead->data; 
}

/*********************************************
 * LIST :: BACK - Finished
 * retrieves the last element in the list
 *     INPUT  :
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
template <typename T>
T & list <T> :: back()
{
    size_t empty = 0;
    if (numElements == empty)
        return *(new T);
    return pTail->data;
}

/******************************************
 * LIST :: REMOVE
 * remove an item from the middle of the list
 *     INPUT  : an iterator to the item being removed
 *     OUTPUT : iterator to the new location
 *     COST   : O(1)
 ******************************************/
template <typename T>
typename list <T> :: iterator  list <T> :: erase(const list <T> :: iterator & it)
{
    /*if (it.p != NULL)
    {
        if (it.p->pPrev)
        {
            it.p->pPrev->pNext = it.p->pNext;
        }
        else
        {
            pHead = it.p->pNext;
            pHead->pPrev = NULL;
        }

        if (it.p->pNext)
        {
            it.p->pNext->pPrev = it.p->pPrev;
        }
        else
        {
            pTail = it.p->pPrev;
            pTail->pNext = NULL;
        }
        delete it.p;
        numElements--;
    }*/
    return it.p;
}

/******************************************
 * LIST :: INSERT
 * add an item to the middle of the list
 *     INPUT  : data to be added to the list
 *              an iterator to the location where it is to be inserted
 *     OUTPUT : iterator to the new item
 *     COST   : O(1)
 ******************************************/
template <typename T>
typename list <T> :: iterator list <T> :: insert(list <T> :: iterator it,
                                                 const T & data)
{
    Node* pNew = new Node(data);

    if (numElements == 0)
    {
        pHead = pTail = pNew;
    }

    if (it.p)
    {
        pNew->pNext = it.p;
        pNew->pPrev = it.p->pPrev;
        it.p->pPrev = pNew;

        if (pNew->pPrev)
            pNew->pPrev->pNext = pNew;

        if (it.p == pHead)
            pHead = pNew;
    }
    else
    {
        pTail->pNext = pNew;
        pNew->pPrev = pTail;
        pTail = pNew;
    }

    numElements++;
    return iterator(pNew);
    /*return end();*/
}

template <typename T>
typename list <T> :: iterator list <T> :: insert(list <T> :: iterator it,
   T && data)
{
   return end();
}

/**********************************************
 * LIST :: assignment operator - MOVE
 * Copy one list onto another
 *     INPUT  : a list to be moved
 *     OUTPUT :
 *     COST   : O(n) with respect to the size of the LHS
 *********************************************/
template <typename T>
void swap(list <T> & lhs, list <T> & rhs)
{

    /*list.swap(rhs)
         tempHead <- rhs.pHead
         rhs.pHead <- pHead
         pHead <- tempHead
         tempTail <- rhs.pTail
         rhs.pTail <- pTail
         pTail <- tempTail
         tempElements <- rhs.numElements
         rhs.numElements <- numElements
         numElements <- tempElements
        */

    // Don't know if this works or not
    /*T* tempHead = rhs.pHead;
    rhs.pHead = lhs.pHead;
    lhs.pHead = tempHead;

    T* tempTail = rhs.pTail;
    rhs.pTail = lhs.pTail;
    lhs.pTail = tempTail;

    T* tempElements = rhs.numElements;
    rhs.numElements = lhs.numElements;
    lhs.tempElements = tempElements;*/
} 


//#endif
}; // namespace custom
