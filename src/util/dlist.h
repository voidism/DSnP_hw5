/****************************************************************************
  FileName     [ dlist.h ]
  PackageName  [ util ]
  Synopsis     [ Define doubly linked list package ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2005-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef DLIST_H
#define DLIST_H

#include <cassert>

template <class T> class DList;

// DListNode is supposed to be a private class. User don't need to see it.
// Only DList and DList::iterator can access it.
//
// DO NOT add any public data member or function to this class!!
//
template <class T>
class DListNode
{
   friend class DList<T>;
   friend class DList<T>::iterator;

   DListNode(const T& d, DListNode<T>* p = 0, DListNode<T>* n = 0):
      _data(d), _prev(p), _next(n) {}

   // [NOTE] DO NOT ADD or REMOVE any data member
   T              _data;
   DListNode<T>*  _prev;
   DListNode<T>*  _next;
};


template <class T>
class DList
{
public:
   // TODO: decide the initial value for _isSorted
   DList() {
      _head = new DListNode<T>(T());
      _head->_prev = _head->_next = _head; // _head is a dummy node
      //_head->_data = "DUMMY";
      _isSorted = true;
   }
   ~DList() { clear(); delete _head; }

   // DO NOT add any more data member or function for class iterator
   class iterator
   {
      friend class DList;

   public:
      iterator(DListNode<T>* n= 0): _node(n) {}
      iterator(const iterator& i) : _node(i._node) {}
      ~iterator() {} // Should NOT delete _node

      // TODO: implement these overloaded operators
      const T& operator * () const { return *(this); }
      T& operator * () { return _node->_data; }
      iterator& operator ++ () {
        _node = _node->_next;
        return *(this);
      }
      iterator operator ++ (int) {
        iterator tmp = *(this);
        ++*(this);
        return tmp;
      }
      iterator& operator -- () {
        _node = _node->_prev;
        return *(this);
      }
      iterator operator -- (int) { 
        iterator tmp = *(this);
        --*(this);
        return tmp; 
      }

      iterator& operator = (const iterator& i) {
        _node = i._node;
        return *(this);
      }

      bool operator != (const iterator& i) const { 
        if(_node == i._node) return false; 
        else return true;
      }
      bool operator == (const iterator& i) const { 
        if(_node == i._node) return true; 
        else return false; }

   private:
      DListNode<T>* _node;
   };

   // TODO: implement these functions
   iterator begin() const { return iterator(_head); }
   iterator end() const { return iterator(_head->_prev); }
   bool empty() const { 
     if(end()==begin()) return true;
     else return false; }
   size_t size() const { 
     if(empty()) return 0;
     size_t size=0;
     for (iterator li = begin(); li != end(); li++) size++;
     return size;
   }

   void push_back(const T& x) {
     if(empty()) _head = _head->_prev = _head->_next = new DListNode<T>(x,end()._node->_prev,end()._node);
     else end()._node->_prev = end()._node->_prev->_next = new DListNode<T>(x,end()._node->_prev,end()._node);
     _isSorted = false;
   }
   void pop_front() { 
     if(!empty()){
       DListNode<T> *predelete = _head;
       _head->_prev->_next = _head->_next;
       _head->_next->_prev = _head->_prev;
       _head = _head->_next;
       delete predelete;
     }
   }
   void pop_back() {
     if(!empty()){
       DListNode<T> *predelete = end()._node->_prev;
       end()._node->_prev->_prev->_next = end()._node;
       end()._node->_prev = end()._node->_prev->_prev;
       delete predelete;
     }
   }

   // return false if nothing to erase
   bool erase(iterator pos) { 
     if(empty()) return false;
     if(pos._node==_head){ pop_front(); return true;}
     pos._node->_prev->_next = pos._node->_next;
     pos._node->_next->_prev = pos._node->_prev;
     delete pos._node;
     return true;
   }
   bool erase(const T& x) { 
     if(empty()) return false;
     for (iterator li = begin(); li != end();li++){
       if(li._node->_data == x){
         return erase(li);
       }
      }
      return false;
   }

   void clear() { 
     if(!empty()){
     //for (iterator li = begin(); li != end();li++){
     //    erase(li);
     // }
     while(!empty()){
       pop_front();
     }
     }
   }  // delete all nodes except for the dummy node
   void sort() const {
     if(!_isSorted)
     quicksort(begin(), end());
     _isSorted = true;
   }

 private:
   // [NOTE] DO NOT ADD or REMOVE any data member
   DListNode<T>*  _head;     // = dummy node if list is empty
   mutable bool   _isSorted; // (optionally) to indicate the array is sorted

   // [OPTIONAL TODO] helper functions; called by public member functions
   void quicksort(iterator head,iterator end) const
   {
     if (head._node&&end._node&&head!=end)
     {
       iterator tail(end._node->_prev);
       if (head != tail)
       {
         iterator p = head._node->_prev;
         for (iterator i = head; i != end; i++)
         {
           if (*i < *tail)
           {
             p._node = p._node->_next;
             const T tmp = p._node->_data;
             p._node->_data = i._node->_data;
             i._node->_data = tmp;
           }
         }
         p._node = p._node->_next;
         const T tmp = p._node->_data;
         *p = *tail;
         *tail = tmp;
         quicksort(head, p);
         quicksort(++p, end);
       }
    }
   }
};

#endif // DLIST_H
