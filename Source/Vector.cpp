#include "Vector.hpp"

template <typename T>
void permute(Vector<T>& V)
{
    for (int i = V.size(); i > 0; --i) {
        std::swap(V[i - 1], V[rand() % i]);
    }
}

template <typename T>
static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)
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
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
    mElem = new T[mCapacity = 2 * (hi - lo)];
    mSize = 0;
    while (lo < hi) {
        mElem[mSize++] = A[lo++];
    }
}

template <typename T>
void Vector<T>::expand()
{
    if (mSize < mCapacity) return;
    if (mCapacity < DEFAULT_CAPACITY) {
        mCapacity = DEFAULT_CAPACITY;
    }
    T* oldElem = mElem;
    mElem = new T[mCapacity <<= 1];
    for (int i = 0; i < mSize; ++i) {
        mElem[i] = oldElem[i];
    }
    delete[]oldElem;
}

template <typename T>
void Vector<T>::shrink()
{
    if (mCapacity < DEFAULT_CAPACITY << 1) return;
    if (mSize << 2 > mCapacity) return;
    T* oldElem = mElem;
    mElem = new T[mCapacity >>= 1];
    for (int i = 0; i < mSize; ++i) {
        mElem = oldElem[i]
    }
    delete[]oldElem;
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
    T* V = mElem + lo;
    for (Rank i = hi - lo; i > 0; --i) {
        std::swap(V[i - 1], V[rand() % i]);
    }
}

template <typename T>
int Vector<T>::disordered() const
{
    int n = 0;
    for (int i = 1; i < mSize; ++i) {
        if (mElem[i - 1] > mElem[i]) {
            ++n;
        }
    }
    return n;
}

template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
{
    // assert 0 <= lo < hi <= mSize
    while ((lo < hi--) && (e != mElem[hi]));
    return hi;
}

template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const
{
    // assert 0 <= lo < hi <= mSize
    return (rand() % 2) ? binSearch(mElem, e, lo, hi) : fibSearch(mElem, e, lo, hi);
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
    if (mElem) {
        delete[]mElem;
    }
    copyFrom(V.mElem, 0, V.size());
    return *this;   // return reference to the current object for chain assignment
}

template <typename T>
T& Vector<T>::operator[](Rank r) const
{
    // assert 0 <= r <= mSize
    return mElem[r];
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e)
{
    expand();
    for (int i = mSize; i > r; --i) {
        mElem[i] = mElem[i - 1];
    }
    mElem[r] = e;
    ++mSize;
    return r;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
    if (lo == hi) return 0;
    while (hi < mSize) {
        mElem[lo++] = mElem[hi++]
    }
    mSize = lo;
    shrink();
    return hi - lo;
}

template <typename T>
T Vector<T>::remove(Rank r)
{
    T e = mElem[r];
    remove(r, r + 1);
    return e;
}

template <typename T>
int Vector<T>::deduplicate()
{
    int oldSize = mSize;
    Rank i = 1;
    while (i < mSize) {
        (find(mElem[i], 0, i) < 0) ? ++i : remove(i);
    }
    return oldSize - mSize;
}

/* O(n^2) */
/*
template <typename T>
int Vector<T>::uniquify()
{
    int oldSize = mSize;
    Rank i = 1;
    while (i < mSize) {
        mElem[i-1] == mElem[i] ? remove(i) : ++i;
    }
    return oldSize - mSize;
}
*/

/* O(n) */
template <typename T>
int Vector<T>::uniquify()
{
    Rank i = 0, j = 0;
    while (++j < mSize) {
        if (mElem[i] != mElem[j]) {
            mElem[i++] = mElem[j];
        }
    }
    mSize = ++i;
    shrink();
    return j - 1;
}

template <typename T>
void Vector<T>::traverse(void(*visit)(T&)) {
    for (int i = 0; i < mSize; ++i) {
        visit(mElem[i]);
    }
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST& visit) {
    for (int i = 0; i < mSize; ++i) {
        visit(mElem[i]);
    }
}

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
