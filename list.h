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
 *    Alexander Dohms, Stephen Costigan, Shaun Crook
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
  ~list() 
   {
   }

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
   // Status
   //

   bool empty()  const { return numElements; }
   size_t size() const { return numElements > 0 ? numElements : 0; }


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
 * NODE
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
   Node()  
   {
      pNext = pPrev = this;
   }
   Node(const T &  data)  
   {
      pNext = pPrev = this;
   }
   Node(      T && data)  
   {
      pNext = pPrev = this;
   }

   //
   // Data
   //

   T data;                 // user data
   Node * pNext;       // pointer to next node
   Node * pPrev;       // pointer to previous node
};

/*************************************************
 * LIST ITERATOR
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
          FOR i <-1 � num-1
            pNew <- NEW Node(T)
            pNew.pPrev <- pPrev
            pNew.pPrev.pNext <- pNew
            pPrevious <- pNew

          pNew.pNext <- NULL
          pTail <- pNew
          numElements <- num*/
   numElements = 99;
   pHead = pTail = new list <T> ::Node();
}

/*****************************************
 * LIST :: ITERATOR constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
template <class Iterator>
list <T> ::list(Iterator first, Iterator last) 
{
    pHead = pTail = nullptr;
    numElements = 0;
    auto it = first;

    while (it != last) 
    {
        push_back(*it);
        numElements++;
        it++;
    }
}

/*****************************************
 * LIST :: INITIALIZER constructors
 * Create a list initialized to a set of values
 ****************************************/
template <typename T>
list <T> ::list(const std::initializer_list<T>& il)
{
    pHead = pTail = nullptr;
    numElements = il.size();
    pHead = pTail = new list <T> ::Node();
    for (T const item : il)
    {
        push_back(item);
    }
}

/*****************************************
 * LIST :: NON-DEFAULT constructors
 * Create a list initialized to a value
 ****************************************/
template <typename T>
list <T> ::list(size_t num)
{
   numElements = 99;
   pHead = pTail = new list <T> ::Node();
}

/*****************************************
 * LIST :: DEFAULT constructors - Finished | Alexander
 ****************************************/
template <typename T>
list <T> ::list() 
{
    numElements = 0;
    pHead = pTail = nullptr;
}

/*****************************************
 * LIST :: COPY constructors - Finished | Alexander
 ****************************************/
template <typename T>
list <T> ::list(list& rhs) 
{
    pHead = pTail = nullptr;
    numElements = 0;
    *this = rhs;
}

/*****************************************
 * LIST :: MOVE constructors - Finished | Alexander
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
 * LIST :: assignment operator - MOVE - Finished | Alexander
 * Copy one list onto another
 *     INPUT  : a list to be moved
 *     OUTPUT :
 *     COST   : O(n) with respect to the size of the LHS 
 *********************************************/
template <typename T>
list <T>& list <T> :: operator = (list <T> && rhs)
{
    clear();
    swap(rhs);
}

/**********************************************
 * LIST :: assignment operator
 * Copy one list onto another
 *     INPUT  : a list to be copied
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
list <T> & list <T> :: operator = (list <T> & rhs)
{
   return *this;
}

/**********************************************
 * LIST :: assignment operator
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
   return *this;
}

/**********************************************
 * LIST :: CLEAR
 * Remove all the items currently in the linked list
 *     INPUT  :
 *     OUTPUT :
 *     COST   : O(n) with respect to the number of nodes
 *********************************************/
template <typename T>
void list <T> :: clear()
{

    //if (numElements > 0) {
    //    while (pHead != nullptr)
    //    {
    //        Node* pDelete = pHead;
    //        pHead = pHead->pNext;
    //        delete pDelete;
    //    }
    //}
    //// Set list default values
    //pHead = pTail = NULL;
    //numElements = 0;

        
        // Set list default values
        pHead = pTail = nullptr;
        numElements = 0;

}

/*********************************************
 * LIST :: PUSH BACK
 * add an item to the end of the list
 *    INPUT  : data to be added to the list
 *    OUTPUT :
 *    COST   : O(1)
 *********************************************/
template <typename T>
void list <T> :: push_back(const T & data)
{

}

template <typename T>
void list <T> ::push_back(T && data)
{

}

/*********************************************
 * LIST :: PUSH FRONT
 * add an item to the head of the list
 *     INPUT  : data to be added to the list
 *     OUTPUT :
 *     COST   : O(1)
 *********************************************/
template <typename T>
void list <T> :: push_front(const T & data)
{

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

}

/*********************************************
 * LIST :: FRONT
 * retrieves the first element in the list
 *     INPUT  : 
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
template <typename T>
T & list <T> :: front()
{
   return *(new T);
}

/*********************************************
 * LIST :: BACK
 * retrieves the last element in the list
 *     INPUT  : 
 *     OUTPUT : data to be displayed
 *     COST   : O(1)
 *********************************************/
template <typename T>
T & list <T> :: back()
{
   return *(new T);
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
   return end();
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
   return end();
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

}


//#endif
}; // namespace custom
