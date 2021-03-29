#include "BinNode.hpp"

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
