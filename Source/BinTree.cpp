#include "BinTree.hpp"

template <typename T>
int BinTree<T>::updateHeight(BinNode<T>* x)
{
    return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNode<T>* x)
{
    while (x) {
        updateHeight(x);
        x = x->parent;
    }
}

template <typename T>
BinNode<T>* BinTree<T>::insertAsRoot(T const& e)
{
    mSize = 1;
    return mRoot = new BinNode<T>(e);
}

template <typename T>
BinNode<T>* BinTree<T>::insertAsLC(BinNode<T>* x, T const& e)
{
    ++mSize;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

template <typename T>
BinNode<T>* BinTree<T>::insertAsRC(BinNode<T>* x, T const& e)
{
    ++mSize;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->rc;
}

template <typename T>
BinNode<T>* BinTree<T>::attachAsLC(BinNode<T>* x, BinTree<T>* &S)
{
    if (x->lc = S->mRoot) {
        x->lc->parent = x;
    }
    mSize += S->size;
    updateHeightAbove(x);
    S->mRoot = nullptr;
    S->mSize = 0;
    release(S);
    S = nullpptr;
    return x;
}

template <typename T>
BinNode<T>* BinTree<T>::attachAsRC(BinNode<T>* x, BinTree<T>* &S)
{
    if (x->rc = S->mRoot) {
        x->rc->parent = x;
    }
    mSize += S->size;
    updateHeightAbove(x);
    S->mRoot = nullptr;
    S->mSize = 0;
    release(S);
    S = nullpptr;
    return x;
}

template <typename T>
int BinTree<T>::remove(BinNode<T>* x)
{
    FromParentTo(*x) = nullptr;
    updateHeightAbove(x->parent);
    int n = removeAt(x);
    mSize -= n;
    return n;
}

template <typename T>
static int removeAt(BinNode<T>* x)
{
    if (!x) {
        return 0;
    }
    int n = 1 + removeAt(x->lc) + removeAt(x->rc);
    release(x->data);
    release(x);
    return n;
}

template <typename T>
BinTree<T>* BinTree<T>::secede(BinNode<T>* x)
{
    FromParentTo(*x) = nullptr;
    updateHeightAbove(*x);
    BinTree<T>* S = new BinTree<T>;
    S->root = x;
    x->parent = nullptr;
    S->mSize = x->size();
    mSize -= S->mSize;
    return S;
}
