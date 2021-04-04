#pragma once

#include "BinNodeMacro.hpp"

#define stature(p) ((p) ? (p)->height : -1)

typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T>
struct BinNode {
    T data;
    BinNode<T>* parent;
    BinNode<T>* lc;
    BinNode<T>* rc;
    int height;
    int npl;    // Null Path Length
    RBColor color;

    BinNode() :
        parent(nullptr),
        lc(nullptr),
        rc(nullptr),
        height(0),
        npl(1),
        color(RB_RED)
    {}

    BinNode(T e, BinNode<T>* p = nullptr, BinNode<T>* lci = nullptr,
        BinNode<T>* rci = nullptr, int h = 0, int l = 1, RBColor c = RB_RED) :
        data(e),
        parent(p),
        lc(lci),
        rc(rci),
        height(h),
        npl(l),
        color(c)
    {}

    int size();
    BinNode<T>* insertAsLC(T const&);
    BinNode<T>* insertAsRC(T const&);
    BinNode<T>* succ(); // successor in inorder traversal
    template <typename VST> void travLevel(VST&);
    template <typename VST> void travPre(VST&);
    template <typename VST> void travIn(VST&);
    template <typename VST> void travPost(VST&);

    bool operator<(BinNode const& bn) { return data < bn.data; }
    bool operator==(BinNode const& bn) { return data == bn.data; }
};
