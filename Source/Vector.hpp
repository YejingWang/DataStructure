#pragma once

#include <algorithm>

typedef int Rank;

#define DEFAULT_CAPACITY 3

template <typename T>
class Vector
{
protected:
    Rank mSize;
    int mCapacity;
    T* mElem;

    void copyFrom(T const* A, Rank lo, Rank hi); // copy vector range [lo, hi)
    void expand(); // expand capacity when needed
    void shrink(); // shrink capacity when load factor is too small
    bool bubble(Rank lo, Rank hi); // exchange elements
    void bubbleSort(Rank lo, Rank hi); // bubble sort
    Rank max(Rank lo, Rank hi); // rank of max element between [lo, hi)
    void selectionSort(Rank lo, Rank hi); // selection sort
    void merge(Rank lo, Rank mi, Rank hi); // merge
    void mergeSort(Rank lo, Rank mi, Rank hi); // merge sort
    Rank partition(Rank lo, Rank hi); //
    void quickSort(Rank lo, Rank hi);// quick sort
    void heapSort(Rank lo, Rank hi);// heap sort

public:
    /* Constructor */
    // capacity = c; size = s; initiailize all elements to v
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
        // assert: s <= c
        mElem = new T[mCapacity = c];
        for (mSize = 0; mSize < s; mElem[mSize++] = v);
    }
    Vector(T const* A, Rank n) { copyFrom(A, 0, n); }
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
    Vector(Vector<T> const& V) { copyFrom(V.mElem, 0, V.mSize); }
    Vector(Vector<T> A, Rank lo, Rank hi) { copyFrom(A.mElem, lo, hi); }

    /* Destructor */
    ~Vector() { delete[]mElem; }

    /* Read-only*/
    Rank size() const { return mSize; }
    bool empty() const { return !mSize; }
    int disordered() const;
    Rank find(T const& e) const { return find(e, 0, mSize); }
    Rank find(T const& e, Rank lo, Rank hi) const;
    Rank search(T const& e) const { return (0 >= mSize) ? -1 : search(e, 0, mSize); }
    Rank search(T const& e, Rank lo, Rank hi) const;

    /* Writable */
    T& operator[](Rank r) const;
    Vector<T>& operator= (Vector<T> const&);
    T remove(Rank r);
    int remove(Rank lo, Rank hi);
    Rank insert(Rank r, T const& e);
    Rank insert(T const& e) { return insert(mSize, e); }
    void sort(Rank lo, Rank hi);
    void sort() { sort(0, mSize); }
    void unsort(Rank lo, Rank hi);
    void unsort() { unsort(0, mSize); }
    int deduplicate();
    int uniquify();

    /* Traversal */
    void traverse(void(*visit)(T&)); // traverse using function pointer, read-only or partial modification
    template <typename VST> void traverse(VST& visit); // traverse using function object, can be used for global modification
};
