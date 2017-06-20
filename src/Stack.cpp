/**
* \file Stack.cpp
*
* This file contains the Stack struct data object
* implementation.
*
* \data Creation: 20/06/2017
* \data Alteration: 20/06/2017
* \author Lucas Fonseca dos Santos
*/
#include "../include/Stack.h"
#define SUCCESS_MSG "Successful Operation!"

using namespace std;

/**
 * Node element object constructor.
 *
 * \param d Node data content.
 */
Node::Node(Data d) {
   this->next = NULL;
   this->content = d;
}

/**
 * Node element object destructor.
 */
Node::~Node() {
   this->next = NULL;
}

/**
 * Stack data struct object constructor.
 */
Stack::Stack() {
   this->top = NULL;
   this->size = 0;
}

/**
 * Stack data struct object destructor.
 */
Stack::~Stack() {
   if(isEmpty()) return;
   Node* tmpNode = this->top;
   Node* tmpPreviusNode;
   while(tmpNode->next != NULL)  {
      tmpPreviusNode = tmpNode;
      tmpNode = tmpNode->next;
      delete tmpPreviusNode;
   }
   delete this->top;
   this->top = NULL;
}

/**
 * Push method by stack to insert new data
 * elements in struct. This method always insert
 * an element on the stack top, following the stack protocol.
 *
 * \param content New insertion data content.
 * \return String Result of operation: Success or failure.
 */
string Stack::push(Data content) {
   if(!isEmpty()) {
      Node* tmpNode = new Node(content);
      tmpNode->next = this->top;
      this->top = tmpNode;
      this->size++;
      return SUCCESS_MSG;
   }else {
      this->top = new Node(content);
      this->size++;
      return SUCCESS_MSG;
   }
}

/**
 * Pop method by stack to remove an element 
 * in struct. This method, it always remove
 * the top element, following the protocol 
 * of the stack.
 *
 * \return Data Data element that was removed.
 */
Data Stack::pop() {
   if(isEmpty()) return FAILURE_ELEMENT;
   Data returnData = getTop();
   Node* tmpNode = this->top;
   this->top = this->top->next;
   delete tmpNode;
   this->size--;
   return returnData;
}

/**
 * This method verifys the condition of stack, if it is
 * empty or no. If it is empty, returns true.
 *
 * \return bool Result of verify about the stack condition.
 */
inline bool Stack::isEmpty() {
   return (this->top == NULL);
}

/**
 * This method gets top element of stack and returns it
 * without removes.
 *
 * \return Data Data element of stack top.
 */
inline Data Stack::getTop() {
   return this->top->content;
}

/**
 * This method searchs an element on stack struct and
 * returns if this element was found. THIS METHOD NOT
 * PRESERVES THE ELEMENTS.
 *
 * \return bool Boolean with result of element search.
 */
 bool Stack::searchElement(Data d) {
    if(!isEmpty()) {
      if(d == getTop()) return true;
      Stack* s = new Stack();
      bool search = false;
      while((pop() != d) && !isEmpty()) {
         (pop() == d)? search = !search : search;
         s->push(pop());
      }
      while(!s->isEmpty()) {
         push(s->pop());
      }
      return search;
    }else{
       return false;
    }
 }

 /**
  * This method is responsible to search an element in stack
  * struck and pop it. It uses an other auxiliar stack to execute
  * this.
  *
  * \param d Data element to search and pop.
  * \return Data Element poped by this method.
  */
Data Stack::searchAndPopElement(Data d) {
   if(!isEmpty()) {
      if(!(d == getTop())) {
         Stack* auxSt = new Stack();
         while(d != getTop() && !isEmpty()) {
            auxSt->push(pop());
         }
         Data result = FAILURE_ELEMENT;
         (d == getTop()) ? result  = getTop() : result;
         while(!auxSt->isEmpty()) {
            push(auxSt->pop());
         }
         return result;
      }else {
         return pop();
      }
   }else {
      return FAILURE_ELEMENT;
   }
}