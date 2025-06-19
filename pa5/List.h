/***
 * Alyssa Nolasco
 * anolasc2
 * 2024 Fall CSE101 PA5
 * List.h
 * Header file for List ADT's functions and procedures 
***/


//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT. List is a double ended queue with a vertical
// cursor standing between elements. The cursor position is always defined
// to be an int in the range 0 (at front) to length of List (at back).
// An empty list consists of the vertical cursor only, with no elements.
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>

#ifndef List_H_INCLUDE_
#define List_H_INCLUDE_

// Exported types -------------------------------------------------------------
typedef int ListElement;

class List{
private:

   // private Node struct
   struct Node{
      // Node fields
      ListElement data;
      Node* next;
      Node* prev;
      // Node constructor
      Node(ListElement x);
   };

   // List fields
   Node* frontDummy;
   Node* backDummy;
   Node* beforeCursor;
   Node* afterCursor;
   int pos_cursor;
   int num_elements;

public:

   // Class Constructors & Destructors ----------------------------------------

   // Creates new List in the empty state.
   List();

   // Copy constructor.
   List(const List& L);   

   // Destructor
   ~List();


   // Access functions --------------------------------------------------------
   int length() const;
   ListElement front() const;
   ListElement back() const;
   int position() const;
   ListElement peekNext() const;
   ListElement peekPrev() const;

   // Manipulation procedures -------------------------------------------------
   void clear();
   void moveFront();
   void moveBack();
   ListElement moveNext();
   ListElement movePrev();
   void insertAfter(ListElement x);
   void insertBefore(ListElement x);
   void setAfter(ListElement x);
   void setBefore(ListElement x);
   void eraseAfter();
   void eraseBefore();

   // Other Functions ---------------------------------------------------------
   int findNext(ListElement x);
   int findPrev(ListElement x);
   void cleanup();
   List concat(const List& L) const;
   std::string to_string() const;
   bool equals(const List& R) const;

   // Overriden Operators -----------------------------------------------------
   friend std::ostream& operator<<( std::ostream& stream, const List& L );
   friend bool operator==( const List& A, const List& B );
   List& operator=( const List& L );

};

#endif

