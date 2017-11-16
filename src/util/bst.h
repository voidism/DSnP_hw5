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
#include <stack>

//#define find_parent_to_me(mother){
//      if(!mother.goBack()) _hand = &_root;
//      else if(mother._node->_left==pos._node) _hand = &mother._node->_left;
//      else if(mother._node->_right==pos._node) _hand = &mother._node->_right;
//    }

#define erase_hand(_hand)                          \
  if (posnode->_left == 0 && posnode->_right == 0) \
  {                                                \
    delete posnode;                                \
    _hand = 0;                                     \
    --_size;                                       \
    return true;                                   \
  }                                                \
  else if (posnode->_left == 0)                    \
  {                                                \
    _hand = posnode->_right;                       \
    delete posnode;                                \
    --_size;                                       \
    return true;                                   \
  }                                                \
  else if (posnode->_right == 0)                   \
  {                                                \
    _hand = posnode->_left;                        \
    delete posnode;                                \
    --_size;                                       \
    return true;                                   \
  }                                                \
  else                                             \
  {                                                \
    iterator alter = pos;                          \
    if (++alter == pos)                            \
      --alter;                                     \
    posnode->_data = alter._node->_data;           \
    erase(alter);                                  \
    return true;                                   \
  }

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
   friend class BSTree<T>;
   friend class BSTree<T>::iterator;
   // TODO: design your own class!!
   BSTreeNode(const T& d, BSTreeNode<T>* p = 0, BSTreeNode<T>* n = 0):
      _data(d), _left(p), _right(n) {}

   // [NOTE] DO NOT ADD or REMOVE any data member
   T              _data;
   BSTreeNode<T>*  _left;
   BSTreeNode<T>*  _right;
};


template <class T>
class BSTree
{
   // TODO: design your own class!!
   public:
    BSTree() {
      _root = _tail = new BSTreeNode<T>(T());
      
      _size = 0;
      //     _root->_left = _root->_right = 0;
   }
   ~BSTree() { clear(); delete _root; }
   class iterator { 

     friend class BSTree;

   public:
      iterator(BSTreeNode<T>* n= 0): _node(n) {
        //_trace.push(n);
      }
      iterator(const BSTreeNode<T>* n= 0): _node(n) {}
      iterator(const iterator& i) : _node(i._node), _trace(i._trace) {}
      ~iterator() {} // Should NOT delete _node

      // TODO: implement these overloaded operators
      const T& operator * () const { return *(_node); }
      T& operator * () { return _node->_data; }
      iterator& operator ++ () { 
        //_trace.push(_root);
        if(_node->_right!=0){
          _trace.push(_node);
          _node = _node->_right;
          toMin();
        }
        else{
          while(1){
            BSTreeNode<T>* pre = _node;
            goBack();
            if (_trace.empty())
            {
              // if(_node->_right!=0) {
              //   _node=_node->_right;
              //   break;
              // }
              // else{
              //   _node = 0;
                break;
              //}
            }
            if (_node->_left == pre)
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
        //_trace.push(BSTree::_root);
        if(_node->_left!=0){
          _trace.push(_node);
          _node = _node->_left;
          toMax();
        }
        else{
          while(1){
            BSTreeNode<T>* pre = _node;
            goBack();
            if (_trace.empty())
            {
              // if(_node->_left!=0) {
              //   _node=_node->_left;
              //   break;
              // }
              // else{
                break;
              //}
            }
            if(_node->_right==pre) break;
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
      stack<BSTreeNode<T> *> _trace;
      iterator toMin()
      {
        while(_node->_left!=0) {
          //BSTreeNode<T> *copy_node = _node;
          _trace.push(_node);

          //cout << "push push >< ~MIN~ !!!\n";
          _node = _node->_left;
        }
        return *this;
      }
      iterator toMax(){
        while(_node->_right!=0) {
          //BSTreeNode<T> *copy_node = _node;
          _trace.push(_node);
          //cout << "push push >< ~MAX~ !!!\n";
          _node = _node->_right;
        }
        return *this;
      }
      bool goBack(){
        //cout << "let go back!!\n";
        if (_trace.empty())
          return false;
        _node = _trace.top();
        _trace.pop();
        return true;
      }
   };

   iterator begin() const{
     iterator tmp(_root);
     tmp.toMin();
     return tmp;
    }
   
   iterator end() const{
     //return iterator(_tail);
     iterator tmp(_tail);
     return tmp;
   }

   bool empty() const { 
     return _size==0; }
   
   size_t size() const {
     return _size;
   }

   void insert(const T& x) {
     insertnode(x, _root);
     _size++;
   }
   void insertnode(const T& x,BSTreeNode<T>*& t) {
     if(t==_tail) t = new BSTreeNode<T>(x,0,_tail);
     else if(t==0) {
         t = new BSTreeNode<T>(x, 0, 0);
     }
     else if(t->_data >= x) insertnode(x,t->_left);
     else if(t->_data < x) insertnode(x,t->_right);
     //else if(t->_data == x) insertnode(x,--t->_right);
    }
   void pop_front() {
     erase(begin());
   }
   void pop_back() {
     iterator tmp(_root);
     tmp.toMax();
     tmp.goBack();
     erase(tmp);
    }
    // BSTreeNode<T>* find_parent_to_me(iterator& pos){
    //   iterator mother = pos;
    //   if(!mother.goBack()){
    //     return _root;
    //   }
    //   else if(mother._node->_left==pos._node) return &mother._node->_left;
    //   else if(mother._node->_right==pos._node) return &mother._node->_right;
    // }

   // return false if nothing to erase
   bool erase(iterator pos) { 
     if(empty()) return false;
     if(pos._node==_tail) return false;
     BSTreeNode<T> *posnode = pos._node;
     iterator &mother = pos;
     if(!mother.goBack()){erase_hand(_root);}
     if(mother._node->_left == posnode) { erase_hand(mother._node->_left); }
     else if(mother._node->_right == posnode) { erase_hand(mother._node->_right); }
     //else cout << "fuckup bitch!\n"; 
     return false;
   }




   bool erase(const T &x)
   {

     iterator walker = iterator(_root);
     int found = 0;
     while (found == 0)
     {
       if(x==walker._node->_data) {
         found = 1;
         break;
       }
       else if (walker._node->_data >= x)
       {
         walker._trace.push(walker._node);
         if (walker._node->_left == 0)
         {
           found = -1;
           break;
         }
         walker._node = walker._node->_left;
     }
     else if(walker._node->_data < x) {
       walker._trace.push(walker._node);
       if(walker._node->_right==0) {
         found = -1;
         break;
       }
       walker._node = walker._node->_right;
      }
     }
     if (found==-1) return false;
     bool result = erase(walker);
     return result;
   }
      
   void clear() {
     while(!empty()) pop_front();
    // int nothing = 0;
    // for (iterator i = begin(); i != end(); i++)
    // {
    //   if(i._node->_left==_tail) cout<< "fuckyou left is tail!!!\n";
    //   else if(i._node->_right==_tail) cout<< "fuckyou right is tail!!!\n";
    //   else nothing++;
    // }
    // cout << "safe nothing:" << nothing << endl;
    // nothing = 0;
    // iterator i = begin(), j = begin();
    // while (!empty()){
    //   j++;
    //   cout << i._node->_data << endl;
    //   if (!erase(i))
    //     nothing++;
    //   if(j==_tail)break;
    //   i = j;
    // }
    // cout << "fuck it can't be erase bitch! : " << nothing << endl;

    //for(iterator i = begin(); i != end(); ++i) { erase(i); }

   } // delete all nodes except for the root node
   void sort() const {}
   void print() const {
     cout << "PRINT\n";
   }

 private:
   BSTreeNode<T>* _root;
   BSTreeNode<T> *_tail;
   size_t _size;
};

#endif // BST_H
