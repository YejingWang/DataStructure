#pragma once

/**************************************************************
* Status and properties of BinNode
**************************************************************/
#define IsRoot(x)       (!((x).parent))
#define IsLChild(x)     (!IsRoot(x) && (&(x) == (x).parent->lc))
#define IsRChild(x)     (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x)    (!IsRoot(x))
#define HasLChild(x)    ((x).lc)
#define HasRChild(x)    ((x).rc)
#define HasChild(x)     (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))

/**************************************************************
* Nodes and pointers related to BinNode
**************************************************************/
#define sibling(p)      (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)
#define uncle(x)        (IsLChild(*((x)->parent)) ? (x)->parent->parent->rc : (x)->parent->parent->lc)
#define FromParentTo(x) (IsRoot(x) ? mRoot : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))
