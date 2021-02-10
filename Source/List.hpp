#pragma once

#include "ListNode.hpp"

template <typename T>
class List {
private:
    int mSize;
    ListNodePosi(T) mHeader;
    ListNodePosi(T) mTrailer;

protected:
    void init();
    int clear();
    void copyNodes(ListNodePosi(T), int);
    void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);
    void mergeSort(ListNodePosi(T)&, int);
    void selectSort(ListNodePosi(T), int);
    void insertionSort(ListNodePosi(T), int);

public:
    List() { init(); }
    List(List<T> const& L);
    List(List<T> const& L, Rank r, int n);
    List(ListNodePosi(T) p, int n);
    ~List();

    Rank size() const { return mSize; }
    bool empty() const { return mSize <= 0; }
    T& operator[](Rank r) const;
    ListNodePosi(T) first const { return mHeader->succ; }
};
