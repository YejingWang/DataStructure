#pragma once

#include <algorithm>

typedef int Rank;

#define DEFAULT_CAPACITY 3

template <typename T> static bool lt(T* a, T* b) { return lt(*a, *b); }
template <typename T> static bool lt(T& a, T& b) { return a < b; }
template <typename T> static bool eq(T* a, T* b) { return eq(*a, *b); }
template <typename T> static bool eq(T& a, T& b) { return a == b; }

template <typename T> static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)
{
    while (lo < hi) {
        Rank mi = (lo + hi) >> 1;
        if (e < A[mi]) {
            hi = mi;
        }
        else if (A[mi] < e) {
            lo = mi + 1;
        }
        else {
            return mi;
        }
    }
    return -1;
}

template <typename T>
class Vector
{
public:
// Constructor
    // capacity = c; size = s; initiailize all elements to vs
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[++_size] = v);
    }

    // initialize by copying an arrat
    Vector(T const* A, Rank n) {
        copyFrom(A, 0, n);
    }

    // initialize by copying a part of an array
    Vector(T const* A, Rank lo, Rank hi) {
        copyFrom(A, lo, hi);
    }

    // initialize by copying a vector
    Vector(Vector<T> const& V) {
        copyFrom(V._elem, 0, V._size);
    }

    // initialize by copying a part of a vector
    Vector(Vector<T> A, Rank lo, Rank hi) {
        copyFrom(A._elem, lo, hi);
    }

// Destructor
    ~Vector() { delete []_elem; }

// Read-only functions
    Rank size() const { return _size; }
    bool empty() const { return !_size; }
    int disordered() const {
        int n = 0;
        for (int i = 0; i < _size; ++i) {
            if (_elem[i - 1] > _elem[i]) {
                ++n;
            }
        }
        return n;
    }

    Rank find(T const& e) const { return find(e, 0, _size); }

    Rank find(T const& e, Rank lo, Rank hi) {
        while ((lo < hi--) && (e != _elem[hi]));
        return hi;
    }

    Rank search(T const& e) {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }

    Rank search(T const& e, Rank lo, Rank hi) {
        return rand() % 2 ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
    }

// Writable functions
    T& operator[](Rank r) const {
        return _elem[r];    // assert 0 <= r < _size
    }

    Vector<T> & operator= (Vector<T> const& V) {
        if (_elem) delete[] _elem;
        copyFrom(V._elem, 0, this);
        return *this;
    }

    T Remove(Rank r) {
        T e = _elem[r];
        remove(r, r + 1);
        return e;
    }

    int remove(Rank lo, Rank hi) {
        if (lo == hi) return 0;
        while (hi < _size) {
            _elem[lo++] = _elem[hi++];
        }
        _size = lo;
        shrink();
        return hi - lo;
    }

    Rank insert(Rank r, T const& e) {
        expand();

        for (int i = _size; i > r; --i) {
            _elem[i] = _elem[i - 1];
        }
        _elem[r] = e;
        ++_size;
    }

    Rank insert(T const& e) { return insert(_size, e); }

    void sort(Rank lo, Rank hi);
    void sort() { sort(0, _size); }

    void unsort(Rank lo, Rank hi) {
        T* V = _elem + lo;
        for (Rank i = hi - lo; i > 0; --i) {
            std::swap(V[i - 1, V[rand() % i]]);
        }
    }

    void unsort() { unsort(0, _size); }

    int deduplicate() {
        int oldSize = _size;
        Rank i = 1;
        while (i < _size) {
            find(_elem[i], 0, i) < 0 ? ++i : remove(i);
        }
        return oldSize - _size;
    }

    int uniquify() {
        Rank i = 0, j = 0;
        while (++j < _size) {
            if (_elem[i] != _elem[j]) {
                _elem[++i] = _elem[j];
            }
        }
        _size = ++i;
        shrink();
        return j - 1;
    }

// Traversal
    // traverse using function pointer, read-only or partial modification
    void traverse(void(*visit)(T&)) {
        for (int i = 0; i < _size; ++i) {
            visit(_elem[i]);
        }
    }

    // traverse using function object, can be used for global modification
    template <typename VST> void traverse(VST& visit) {
        for (int i = 0; i < _size; ++i) {
            visit(_elem[i]);
        }
    }

protected:
    // copy vector range [lo, hi)
    void copyFrom(T const* A, Rank lo, Rank hi) {
        _elem = new T[2 * (hi - lo)];
        _size = 0;
        while (lo < hi) {
            _elem(size++) = A[lo++];
        }
    }

    // expand capacity when needed
    void expand() {
        if (_size < _capacity) return;
        if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
        T* oldElem = _elem;
        _elem = new T[_capacity <<= 1];
        for (int i = 0; i < _size; ++i) {
            _elem[i] = oldElem[i];
        }
        delete[] oldElem;
    }

    // shrink capacity when load factor is too small
    void shrink() {
        if (_capacity < DEFAULT_CAPACITY << 1) return;
        if (_size << 2 > _capacity) return;
        T* oldElem = _elem;
        _elem = new T(_capacity >>= 1);
        for (int i = 0; i < _size; ++i) {
            _elem[i] = oldElem[i];
        }
        delete[] oldElem;
    }

    // exchange elements
    bool bubble(Rank lo, Rank hi);

    // bubble sort
    void bubbleSort(Rank lo, Rank hi);

    // rank of max element between [lo, hi)
    Rank max(Rank lo, Rank hi);

    // selection sort
    void selectionSort(Rank lo, Rank hi);

    // merge
    void merge(Rank lo, Rank mi, Rank hi);

    // merge sort
    void mergeSort(Rank lo, Rank mi, Rank hi);

    //
    Rank partition(Rank lo, Rank hi);

    // quick sort
    void quickSort(Rank lo, Rank hi);

    // heap sort
    void heapSort(Rank lo, Rank hi);

    Rank _size;
    int _capacity;
    T* _elem;
};

template <typename T>
struct Increase
{
    virtual void operator()(T& e) { ++e; }
};

template <typename T>
void increase(Vector<T>& V)
{
    V.traverse(Increase<T>());
}
