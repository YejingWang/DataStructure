#include <assert.h>

#include "List.hpp"

template <typename T>
void List<T>::init()
{
    mHeader = new ListNode<T>;
    mTrailer = new ListNode<T>;
    mHeader->succ = mTrailer;
    mHeader->pred = nullptr;
    mTrailer->pred = mHeader;
    mTrailer->succ = nullptr;
    mSize = 0;
}

template <typename T>
T& List<T>::operator[](Rank r) const
{
    assert(0 <= r && r < mSize);
    ListNode<T>* p = first();
    while (0 < r--) {
        p = p->succ;
    }
    return p->data;
}

template <typename T>
ListNode<T>* List<T>::find(T const& e, int n, ListNode<T>* p) const
{
    // 0 <= n <= rank(p) < mSize
    while (0 < n--) {
        if (e == (p = p->pred)->data) {
            return p;
        }
    }
    return nullptr;
}

template <typename T>
ListNode<T>* List<T>::search(T const& e, int n, ListNode<T>* p) const
{
    // 0 <= n <= rank(p) < mSize
    while (0 < n--) {
        if ((p = p->pred)->data <= e) {
            break;
        }
    }
    return p;
}

template <typename T>
ListNode<T>* List<T>::insertAsFirst(T const& e)
{
    ++mSize;
    return mHeader->insertAsSucc(e);
}

template <typename T>
ListNode<T>* List<T>::insertAsLast(T const& e)
{
    ++mSize;
    return mTrailer->insertAsPred(e);
}

template <typename T>
ListNode<T>* List<T>::insertA(ListNode<T>* p, T const& e)
{
    ++mSize;
    return p->insertAsSucc(e);
}

template <typename T>
ListNode<T>* List<T>::insertB(ListNode<T>* p, T const& e)
{
    ++mSize;
    return p->insertAsPred(e);
}

template <typename T>
void List<T>::copyNodes(ListNode<T>* p, int n)
{
    init();
    while (0 < n--) {
        insertAsLast(p->data);
        p = p->succ;
    }
}

template <typename T>
List<T>::List(ListNode<T>* p, int n)
{
    copyNodes(p, n);
}

template <typename T>
List<T>::List(List<T> const& L)
{
    copyNodes(L.first(), L.mSize);
}

template <typename T>
List<T>::List(List<T> const& L, Rank r, int n)
{
    copyNodes(L[r], n);
}

template <typename T>
T List<T>::remove(ListNode<T>* p)
{
    T e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p;
    --mSize;
    return e;
}

template <typename T>
List<T>::~List()
{
    clear();
    delete mHeader;
    delete mTrailer;
}

template <typename T>
int List<T>::clear()
{
    int oldSize = mSize;
    while (0 < mSize) {
        remove(mHeader->succ);
    }
    return oldSize;
}

template <typename T>
int List<T>::deduplicate()
{
    if (mSize < 2) {
        return 0;
    }
    ListNode<T>* p = mHeader;
    Rank r = 0;
    int oldSize = mSize;
    while (mTrailer != (p = p->succ)) {
        ListNode<T>* q = find(p->data, r, p);
        q ? remove(q) : ++r;
    }
    return oldSize - mSize;
}

template <typename T>
int List<T>::uniquify()
{
    if (mSize < 2) {
        return 0;
    }
    int oldSize = mSize;
    ListNode<T>* p = first();
    ListNode<T>* q;
    while (mTrailer != (q = p->succ)) {
        if (p->data != q->data) {
            p = q;
        }
        else {
            remove(q);
        }
    }
    return oldSize - mSize;
}

template <typename T>
void List<T>::traverse(void(*visit)(T&))
{
    for (ListNode<T>* p = mHeader->succ; p != mTrailer; p = p->succ) {
        visit(p->data);
    }
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST& visit)
{
    for (ListNode<T>* p = mHeader->succ; p != mTrailer; p = p->succ) {
        visit(p->data);
    }
}

template <typename T>
void List<T>::sort(ListNode<T>* p, int n)
{
    switch (rand() % 3)
    {
    case 1:
        insertionSort(p, n);
        break;
    case 2:
        selectionSort(p, n);
        break;
    default:
        mergeSort(p, n);
        break;
    }
}

template <typename T>
void List<T>::insertionSort(ListNode<T>* p, int n)
{
    for (int r = 0; r < n; ++r) {
        insertA(search(p->data, r, p), p->data);
        p = p->succ;
        remove(p->pred);
    }
}

template <typename T>
void List<T>::selectSort(ListNode<T>* p, int n)
{
    ListNode<T>* head = p->pred;
    ListNode<T>* tail = p;
    for (int r = 0; r < n; ++r) {
        tail = tail->succ;
    }
    while (1 < n) {
        ListNode<T>* max = selectMax(head->succ, n);
        insertB(tail, remove(max));
        tail = tail->pred;
        --n;
    }
}

template <typename T>
ListNode<T>* List<T>::selectMax(ListNode<T>* p, int n)
{
    ListNode<T>* max = p;
    for (ListNode<T>* cur = p; 1 < n; --n) {
        if (!lt((cur = cur->succ)->data, max->data)) {
            max = cur;
        }
    }
    return max;
}

template <typename T>
void List<T>::merge(ListNode<T>*& p, int n, List<T>& L, ListNode<T>* q, int m)
{
    // this.valid(p) && rank(p) + n < mSize && this.sorted(p, n)
    // L.valid(q) && rank(q) + m <= L.size() && L.sorted(q, m)
    ListNode<T>* pp = p->pred;
    while (0 < m) {
        if ((0 < n) && (p->data <= q->data)) {
            if (q == (p = p->succ)) {
                break;
            }
            --n;
        }
        else {
            insertB(p, L.remove(q = q->succ)->pred);
            --m;
        }
    }
    p = pp->succ;
}

template <typename T>
void List<T>::mergeSort(ListNode<T>*& p, int n)
{
    if (n < 2) {
        return;
    }
    int m = n >> 1;
    ListNode<T> q = p;
    for (int i = 0; i < m; ++i) {
        q = q->succ;
    }
    mergeSort(p, m);
    mergeSort(q, n - m);
    merge(p, m, *this, q, n - m);
}
