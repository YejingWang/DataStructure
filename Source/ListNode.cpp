#include "ListNode.hpp"

template <typename T>
ListNode<T>* ListNode<T>::insertAsPred(T const& e)
{
    ListNode<T>* x = new ListNode<T>(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}

template <typename T>
ListNode<T>* ListNode<T>::insertAsSucc(T const& e)
{
    ListNode<T>* x = new ListNode<T>(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}
