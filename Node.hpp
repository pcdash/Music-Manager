//
//  Node.hpp
//  Music Manager
//
//  Created by Paul Valdez on 7/21/18.
//  Copyright © 2018 Paul Valdez. All rights reserved.
//
//Changed so that the constructor and set data use references

#ifndef Node_h
#define Node_h

#include <iostream>
#include <string>

template <class D>
class Node {
public:
    //constructor
    Node(D & info = "", Node<D> * newNext = nullptr, Node<D> * newPrev = nullptr);
    //Destructor
    ~Node();
    
    //Setters and getters
    void setNext(Node<D> * const newNext);
    void setPrev(Node<D> * const newPrev);
    void setData(const D & newInfo);
    void setSongNumber(const int newSongNumber);
    
    D & getData();
    int getSongNumber() const;
    Node<D> * getNext();
    Node<D> * getPrev();
    
    
    bool operator == (Node<D> * rhs);
private:
    int mSongNumber;
    D mInformation;
    Node<D> *mpNext;
    Node<D> *mpPrev;
};

//constructor
template <class D>
Node<D>::Node(D & info, Node<D> * newNext, Node<D> * newPrev)
{
    this -> mInformation = info;
    this -> mpNext = newNext;
    this -> mpPrev = newPrev;
}
//Destructor
template <class D>
Node<D>::~Node()
{
    //Doesnt do anything because no dynamic memory allocated
   // std::cout << "Inside Nodes destructor" << std::endl;
}
template <class D>
bool Node<D>::operator == (Node<D> * rhs)
{
    return (this -> mInformation == rhs -> getInformation());
}

//Setters and getters
template <class D>
void Node<D>::setNext(Node<D> * const newNext)
{
    this -> mpNext = newNext;
}

template <class D>
void Node<D>::setPrev(Node<D> * const newPrev)
{
    this -> mpPrev = newPrev;
}

template <class D>
void Node<D>::setData(const D & newInfo)
{
    this -> mInformation = newInfo;
}

template <class D>
void Node<D>::setSongNumber(const int newSongNumber)
{
    this -> mSongNumber = newSongNumber;
}

template <class D>
D & Node<D>::getData()
{
    return this -> mInformation;
}

template <class D>
int Node<D>::getSongNumber() const
{
    return this -> mSongNumber;
}

template <class D>
Node<D> * Node<D>::getNext()
{
    return this -> mpNext;
}

template <class D>
Node<D> * Node<D>::getPrev()
{
    return this -> mpPrev;
}

#endif /* Node_h */
