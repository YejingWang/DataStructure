#pragma once

#include "ListNode.hpp"

template <typename T>
class List {
private:
    int mSize;
    ListNode<T>* mHeader;
    ListNode<T>* mTrailer;

protected:
    void init();
    int clear();
    void copyNodes(ListNode<T>*, int);
    void merge(ListNode<T>*&, int, List<T>&, ListNode<T>*, int);
    void mergeSort(ListNode<T>*&, int);
    void selectSort(ListNode<T>*, int);
    void insertionSort(ListNode<T>*, int);

public:
    List() { init(); } // default constructor
    List(List<T> const& L); // copy constructor
    List(List<T> const& L, Rank r, int n); // copy n nodes in L starting from rth node
    List(ListNode<T>* p, int n); // copy n nodes starting from p
    ~List(); // destructor

    /* Read-only */
    Rank size() const { return mSize; }
    bool empty() const { return mSize <= 0; }
    T& operator[](Rank r) const;
    ListNode<T>* first() const { return mHeader->succ; }
    ListNode<T>* last() const{ return mTrailer->pred; }
    bool valid(ListNode<T>* p) { return p && (mTrailer != p) && (mHeader != p); }
    int disordered() const;
    ListNode<T>* find(T const& e) const { return find(e, mSize, mTrailer); }
    ListNode<T>* find(T const& e, int n, ListNode<T>* p) const;
    ListNode<T>* search(T const& e) const { return search(e, mSize, mTrailer); }
    ListNode<T>* search(T const& e, int n, ListNode<T>* p) const;
    ListNode<T>* selectMax(ListNode<T>* p, int n);
    ListNode<T>* selectMax() { return selectMax(mHeader->succ, mSize); }

    /* Writable */
    ListNode<T>* insertAsFirst(T const& e);
    ListNode<T>* insertAsLast(T const& e);
    ListNode<T>* insertA(ListNode<T>* p, T const& e);
    ListNode<T>* insertB(ListNode<T>* p, T const& e);
    T remove(ListNode<T>* p);
    void merge(List<T>& L) { merge(first(), mSize, L, L.first(), L.size()); }
    void sort(ListNode<T>* p, int n);
    void sort() { sort(first(), mSize); }
    int deduplicate();
    int uniquify();
    void reserve();

    /* Traversal */
    void traverse(void(*)(T&));
    template <typename VST> void traverse(VST&);
};
