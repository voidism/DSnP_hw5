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

#define erase_hand(_hand, _mom)        \
  if (_hand->_left != 0 &&             \
      (_hand->_right == _tail))        \
  {                                    \
    _hand = _hand->_left;              \
    _hand->_parent = _mom;             \
    iterator nanja(_hand);             \
    nanja.toMax();                     \
    nanja._node->_right = _tail;       \
    _tail->_parent = nanja._node;      \
    delete posnode;                    \
    returntrue;                        \
  }                                    \
  else if (_hand->_left == 0 &&             \
      (_hand->_right == 0))            \
  {                                    \
    delete posnode;                    \
    _hand = 0;                         \
    returntrue;                        \
  }                                    \
  else if (_hand->_left == 0)          \
  {                                    \
    _hand = _hand->_right;             \
    _hand->_parent = _mom;             \
    delete posnode;                    \
    returntrue;                        \
  }                                    \
  else if (_hand->_right == 0)         \
  {                                    \
    _hand = _hand->_left;              \
    _hand->_parent = _mom;             \
    delete posnode;                    \
    returntrue;                        \
  }                                    \
  else                                 \
  {                                    \
    iterator alter = pos;              \
    alter++;                           \
    _hand->_data = alter._node->_data; \
    return erase(alter);               \
  }

#define returntrue \
  _size--;         \
  _root->_parent = 0;\
  return true;

template <class T>
class BSTree;

// BSTreeNode is supposed to be a private class. User don't need to see it.
// Only BSTree and BSTree::iterator can access it.
//
// DO NOT add any public data member or function to this class!!
//
template <class T>
class BSTreeNode
{
  // TODO: design your own class!!
  friend class BSTree<T>;
  friend class BSTree<T>::iterator;
  // TODO: design your own class!!
  BSTreeNode(const T &d, BSTreeNode<T> *l = 0, BSTreeNode<T> *r = 0, BSTreeNode<T> *p = 0) : _data(d), _left(l), _right(r), _parent(p) {}

  // [NOTE] DO NOT ADD or REMOVE any data member
  T _data;
  BSTreeNode<T> *_left;
  BSTreeNode<T> *_right;
  BSTreeNode<T> *_parent;
};

template <class T>
class BSTree
{
  // TODO: design your own class!!
public:
  BSTree()
  {
    _root = _tail = new BSTreeNode<T>(T(), 0, 0, 0);

    _size = 0;
    //     _root->_left = _root->_right = 0;
  }
  ~BSTree()
  {
    clear();
    delete _root;
  }
  class iterator
  {

    friend class BSTree;

  public:
    iterator(BSTreeNode<T> *n = 0) : _node(n)
    {
      //_trace.push(n);
    }
    iterator(const BSTreeNode<T> *n = 0) : _node(n) {}
    iterator(const iterator &i) : _node(i._node) {}
    ~iterator() {} // Should NOT delete _node

    // TODO: implement these overloaded operators
    const T &operator*() const { return *(_node); }
    T &operator*() { return _node->_data; }
    iterator &operator++()
    {
      //iterator tmp = *this;
      if (_node->_right != 0)
      {
        _node = _node->_right;
        toMin();
      }
      else
      {
        while (1)
        {
          BSTreeNode<T> *pre = _node;
          if (_node->_parent == 0)
          {
            //*this = tmp;
            break;
          }
          _node = _node->_parent;
          if (_node->_left == pre)
            break;
        }
      }
      return *(this);
    }
    iterator operator++(int)
    {
      iterator tmp = *(this);
      ++*(this);
      return tmp;
    }
    iterator &operator--()
    {
      //_trace.push(BSTree::_root);
      //iterator tmp = *this;
      if (_node->_left != 0)
      {
        _node = _node->_left;
        toMax();
      }
      else
      {
        while (1)
        {
          BSTreeNode<T> *pre = _node;
          if (_node->_parent == 0)
          {
            //*this = tmp;
            break;
          }
          _node = _node->_parent;
          if (_node->_right == pre)
            break;
        }
      }
      return *(this);
    }
    iterator operator--(int)
    {
      iterator tmp = *(this);
      --*(this);
      return tmp;
    }

    iterator &operator=(const iterator &i)
    {
      _node = i._node;
      return *(this);
    }

    bool operator!=(const iterator &i) const { return !(_node == i._node); }
    bool operator==(const iterator &i) const { return _node == i._node; }

  private:
    BSTreeNode<T> *_node;
    iterator toMin()
    {
      while (_node->_left != 0)
      {
        _node = _node->_left;
      }
      return *this;
    }
    iterator toMax()
    {
      while (_node->_right != 0)
      {
        _node = _node->_right;
      }
      return *this;
    }
  };

  iterator begin() const
  {
    iterator tmp(_root);
    tmp.toMin();
    return tmp;
  }

  iterator end() const
  {
    iterator tmp(_tail);
    return tmp;
  }

  bool empty() const
  {
    return _size == 0;
  }

  size_t size() const
  {
    return _size;
  }

  // void insert(const T &x)
  // {
  //   if (_root == _tail)
  //   {
  //     _root = new BSTreeNode<T>(x, 0, _tail, 0);
  //     _tail->_parent = _root;
  //   }
  //   else
  //   {
  //     insertnode(x, 0, _root);
  //     _size++;
  //   }
  // }
  // void insertnode(const T &x, BSTreeNode<T> *m, BSTreeNode<T> *&t)
  // {
  //   if (t == _tail)
  //     t = new BSTreeNode<T>(x, 0, _tail, m);
  //   else if (t == 0)
  //   {
  //     t = new BSTreeNode<T>(x, 0, 0, m);
  //   }
  //   else if (t->_data >= x)
  //     insertnode(x, t, t->_left);
  //   else if (t->_data < x)
  //     insertnode(x, t, t->_right);
  //   //else if(t->_data == x) insertnode(x,--t->_right);
  // }
  void insert(const T& x) {
    if(_root == _tail){
      _tail->_parent = _root= new BSTreeNode<T>(x, 0, _tail, 0);
      _size++;
      return;
    }
    BSTreeNode<T>* nanja(_root);
    BSTreeNode<T>* sidekick = nanja;
    while (nanja != 0 && nanja != _tail){
      sidekick = nanja;
      if(x>=nanja->_data) nanja = nanja->_right;
      else nanja = nanja->_left;
    }
    if(nanja==0){ 
      if(sidekick->_data<=x)
      sidekick->_right = new BSTreeNode<T>(x, 0, 0, sidekick); 
      else
      sidekick->_left = new BSTreeNode<T>(x, 0, 0, sidekick);
      _size++;
    }
    else if (nanja == _tail){
      sidekick->_right = _tail->_parent = new BSTreeNode<T>(x, 0, _tail, sidekick);
      _size++;
    }
  }
  void pop_front()
  {
    erase(begin());
  }
  void pop_back()
  {
    iterator tmp = end();
    //tmp._node = tmp._node->_parent;
    tmp--;
    erase(tmp);
  }
  // return false if nothing to erase
  bool erase(iterator pos)
  {
    if (empty())
      return false;
    if (pos._node == _tail)
      return false;
    BSTreeNode<T> *posnode = pos._node;
    if (!pos._node->_parent)
    {
      erase_hand(_root, 0);
    }
    //iterator mother(pos._node->_parent);
    BSTreeNode<T> *mother = posnode->_parent;
    if (pos._node->_parent->_left == posnode)
    {
      erase_hand(pos._node->_parent->_left, mother);
    }
    else if (pos._node->_parent->_right == posnode)
    {
      erase_hand(pos._node->_parent->_right, mother);
    }
    return false;
  }
  

  bool erase(const T &x)
  {

    iterator walker = iterator(_root);
    int found = 0;
    while (found == 0)
    {
      if (x == walker._node->_data)
      {
        found = 1;
        break;
      }
      else if (walker._node->_data >= x)
      {
        if (walker._node->_left == 0)
        {
          found = -1;
          break;
        }
        walker._node = walker._node->_left;
      }
      else if (walker._node->_data < x)
      {
        if (walker._node->_right == 0)
        {
          found = -1;
          break;
        }
        walker._node = walker._node->_right;
      }
    }
    if (found == -1)
      return false;
    bool result = erase(walker);
    return result;
  }

  void clear()
  {
    while (!empty())
      pop_front();
  } // delete all nodes except for the root node
  void sort() const {}
  void print() const {}

private:
  BSTreeNode<T> *_root;
  BSTreeNode<T> *_tail;
  size_t _size;
};

#endif // BST_H
