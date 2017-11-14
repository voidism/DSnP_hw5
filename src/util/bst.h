/****************************************************************************
  FileName     [ bst.h ]
  PackageName  [ util ]
  Synopsis     [ Define binary search tree package ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2005-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef BST_H
#define BST_H

#include <cassert>

using namespace std;

template <class T> class BSTree;

// BSTreeNode is supposed to be a private class. User don't need to see it.
// Only BSTree and BSTree::iterator can access it.
//
// DO NOT add any public data member or function to this class!!
//
template <class T>
class BSTreeNode
{
   // TODO: design your own class!!
   BSTreeNode(const T& d, BSTreeNode<T>* p = 0, BSTree<T>* n = 0):
      _data(d), _left(p), _right(n) {}

   // [NOTE] DO NOT ADD or REMOVE any data member
   T              _data;
   DListNode<T>*  _left;
   DListNode<T>*  _right;
};


template <class T>
class BSTree
{
   // TODO: design your own class!!
   BSTree() {
      _root = new BSTree<T>(T());
      _root->_prev = _root->_next = 0;
   }
   ~BSTree() { clear(); delete _root; }
   class iterator { 

     friend class BSTree;

   public:
      iterator(BSTreeNode<T>* n= 0): _node(n) {}
      iterator(const iterator& i) : _node(i._node) {}
      ~iterator() {} // Should NOT delete _node

      // TODO: implement these overloaded operators
      const T& operator * () const { return *(_node); }
      T& operator * () { return _node->_data; }
      iterator& operator ++ () { 
        if(_node._right!=0){
          _trace.push(_node);
          _node = _node._right;
          toMin();
        }
        else{
          while(1){
            T *pre = _node;
            if(!goBack()){
              if(_node._right!=0) {
                _node=_node._right;
                break;
              }
              else{
                _node = &_tail;
                break;
              }
            }
            if (_node._left == pre)
              break;
          }
        }
        return *(this); 
      }
      iterator operator ++ (int) {
        iterator tmp = *(this);
        ++*(this);
        return tmp;
      }
      iterator& operator -- () { 
        if(_node._left!=0){
          _trace.push(_node);
          _node = _node._left;
          toMax();
        }
        else{
          while(1){
            T *pre = _node;
            if(!goBack()){
              if(_node._left!=0) {
                _node=_node._left;
                break;
              }
              else{
                break;
              }
            }
            if(_node._right==pre) break;
          }
        }
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

      bool operator != (const iterator& i) const { return !(_node == i._node); }
      bool operator == (const iterator& i) const { return _node == i._node; }

   private:
      BSTreeNode<T>* _node;
      BSTreeNode<T> _tail;
      iterator toMin()
      {
        while(_node._left!=0) {
          _trace.push(_node);
          _node = _node._left;
        }
        return *this;
      }
      iterator toMax(){
        while(_node._right!=0) {
          _trace.push(_node);
          _node = _node._right;
        }
        return *this;
      }
      bool goBack(){
        if(_trace.empty()) return false;
        _node = _trace.top();
        _trace.pop();
        return true;
      }
   };

   iterator begin() const { return iterator(_root).toMin(); }
   
   iterator end() const { return iterator(&_tail); }
   
   bool empty() const { 
     return _size==0; }
   
   size_t size() const {
     return _size;
   }

   void insert(const T& x) {
     insertnode(x, _root);
     _size++;
   }
   void insertnode(const T& x,BSTreeNode* t) {
     if(t==0) t = new BSTreeNode(x,0,0);
     else if(t->_data >= x) insertnode(x,t->_left);
     else if(t->_data < x) insertnode(x,t->_right);
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
     delete pos._node;
     return true;
   }
   bool erase(const T& x) {
      return false;
   }

   void clear() {
   }  // delete all nodes except for the root node
   void sort() const {
   }

 private:
   DListNode<T>*  _root;
   size_t _size;
};

#endif // BST_H
