#pragma once

#include "BinNode.hpp"
#include "util/comparator.hpp"

template <typename T>
class BinTree {
protected:
    int mSize;
    BinNode<T>* mRoot;
    virtual int updateHeight(BinNode<T>* x);
    void updateHeightAbove(BinNode<T>* x);

    BinNode<T>* insertAsLC(T const & e);

public:
    BinTree() :
        mSize(0),
        mRoot(nullptr)
    {}

    ~BinTree() {
        if (0 < mSize) {
            remove(mRoot);
        }
    }

    int size() const { return mSize; }
    bool empty() const { return !mRoot; }
    BinNode<T>* root() const { return mRoot; }
    BinNode<T>* insertAsRoot(T const& e);
    BinNode<T>* insertAsLC(BinNode<T>* x, T const& e);
    BinNode<T>* insertAsRC(BinNode<T>* x, T const& e);
    BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>* &T);
    BinNode<T>* attachAsRC(BinNode<T>* x, BinTree<T>* &T);
    int remove(BinNode<T>* x);
    BinTree<T>* secede(BinNode<T>* x);

    template <typename VST>
    void travLevel(VST& visit) {
        if (mRoot) {
            mRoot->travLevel(visit);
        }
    }

    template <typename VST>
    void travPre(VST& visit) {
        if (mRoot) {
            mRoot->travPre(visit);
        }
    }

    template <typename VST>
    void travIn(VST& visit) {
        if (mRoot) {
            mRoot->travIn(visit);
        }
    }

    template <typename VST>
    void travPost(VST& visit) {
        if (mRoot) {
            mRoot->travPost(visit);
        }
    }

    bool operator<(BinTree<T> const& t) {
        return mRoot && t.mRoot && lt(mRoot, t.mRoot);
    }

    bool operator==(BinTree<T> const& t) {
        return mRoot && t.mRoot && (mRoot == t.mRoot);
    }
};
