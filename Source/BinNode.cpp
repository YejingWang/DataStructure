#include "BinNode.hpp"

#include "Stack.hpp"
#include "Queue.hpp"

template <typename T>
int BinNode<T>::size()
{
    int s = 1;
    if (lc) {
        s += lc->size();
    }
    if (rc) {
        s += rc->size();
    }
    return s;
}

template <typename T>
BinNode<T>* BinNode<T>::insertAsLC(T const& e)
{
    return lc = new BinNode(e, this);
}

template <typename T>
BinNode<T>* BinNode<T>::insertAsRC(T const& e)
{
    return rc = new BinNode(e, this);
}

template <typename T>
BinNode<T>* BinNode<T>::succ()
{
    BinNode<T>* s = this;
    if (rc) {
        s = rc;
        while (HasLChild(*s)) {
            s = s->lc;
        }
    }
    else {
        while (IsRChild(*s)) {
            s = s->parent;
        }
        s = s->parent;
    }
    return s;
}

template <typename T>
template <typename VST>
void BinNode<T>::travIn(VST& visit)
{
    switch (rand() % 5)
    {
    case 1:
        traIn_I1(this, visit);
        break;
    case 2:
        traIn_I2(this, visit);
        break;
    case 3:
        traIn_I3(this, visit);
        break;
    case 4:
        traIn_I4(this, visit);
        break;
    default:
        traIn_R(this, visit);
        break;
    }
}

template <typename T, typename VST>
void travPre_R(BinNode<T>* x, VST& visit)
{
    if (!x) {
        return;
    }
    visit(x->data);
    travPre_R(x->lc, visit);
    travPre_R(x->rc, visit);
}

template <typename T, typename VST>
void travPost_R(BinNode<T>* x, VST& visit)
{
    if (!x) {
        return;
    }
    travPost_R(x->lc, visit);
    travPost_R(x->rc, visit);
    visit(x->data);
}

template <typename T, typename VST>
void travIn_R(BinNode<T>* x, VST& visit)
{
    if (!x) {
        return;
    }
    travIn_R(x->lc, visit);
    visit(x->data);
    travIn_R(x->rc, visit);
}

template <typename T, typename VST>
static void visitAlongLeftBranch(BinNode<T>* x, VST& visit, Stack<BinNode<T>*>& S)
{
    while (x) {
        visit(x->data);
        S.push(x->rc);
        x = x->lc;
    }
}

template <typename T, typename VST>
void travPrev_I2(BinNode<T>* x, VST& visit)
{
    Stack<BinNode<T>*> S;
    while (true) {
        visitAlongLeftBranch(x, visit, S);
        if (S.empty()) {
            break;
        }
        x = S.pop();
    }
}

template <typename T>
void goAlongLeftBranch(BinNode<T>* x, Stack<BinNode<T>*>& S)
{
    while (x) {
        S.push(x);
        x = x->lc;
    }
}

template <typename T, typename VST>
void travIn_I1(BinNode<T>* x, VST& visit)
{
    Stack<BinNode<T*>> S;
    while (true) {
        goAlongLeftBranch(x, S);
        if (S.empty()) {
            break;
        }
        x = S.pop();
        visit(x->data);
        x = x->rc;
    }
}

template <typename T, typename VST>
void travIn_I2(BinNode<T>* x, VST& visit)
{
    Stack<BinNode<T>*> S;
    while (true) {
        if (x) {
            S.push(x);
            x = x->lc;
        }
        else if (!S.empty()) {
            x = S.pop();
            visit(x->data);
            x = x->rc;
        }
        else {
            break;
        }
    }
}

template <typename T, typename VST>
void travIn_I3(BinNode<T>* x, VST& visit)
{
    bool backtrack = false;    // O(1) space
    while (true) {
        if (!backtrack && HasLChild(*x)) {
            x = x->lc;
        }
        else {
            visit(x->data);
            if (HasRChild(*x)) {
                x = x->rc;
                backtrack = false;
            }
            else {
                if (!(x = x->succ())) {
                    break;
                }
                backtrack = true;
            }
        }
    }
}

template <typename T>
static void gotoHLVFL(Stack<BinNode<T>*>& S)
{
    while (BinNode<T>* x = S.top()) {
        if (HasLChild(*x)) {
            if (HasRChild(*x)) {
                S.push(x->rc);
            }
            S.push(x->lc);
        }
        else {
            S.push(x->rc);
        }
    }
    S.pop(); // pop the empty node
}

template <typename T, typename VST>
void travPost_I(BinNode<T>* x, VST& visit)
{
    Stack<BinNode<T>*> S;
    if (x) {
        S.push(x);
    }
    while (!S.empty()) {
        if (S.top() != x->parent) {
            gotoHLVFL(S);
        }
        x = S.pop();
        visit(x->data);
    }
}

template <typename T>
template <typename VST>
void BinNode<T>::travLevel(VST& visit)
{
    Queue<BinNode<T>*> Q;
    Q.enqueue(this);
    while (!Q.empty()) {
        BinNode<T>* x = Q.dequeue();
        visit(x->data);
        if (HasLChild(*x)) {
            Q.enqueue(x->lc);
        }
        if (HasRChild(*x)) {
            Q.enqueue(x->rc);
        }
    }
}
