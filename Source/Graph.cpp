#include "Graph.hpp"
#include "Queue.hpp"

template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s) {    // assert 0 <= s < n
    reset();
    int clock = 0;
    int v = s;
    do {
        if (UNDISCOVERED == status(v)) {
            BFS(v, clock);
        }
    } while (s != (v = (++v % n)));
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int& clock) {    //assert 0 <= v < n
    Queue<int> Q;
    status(v) = DISCOVERED;
    Q.enqueue(v);
    while (!Q.empty()) {
        int v = Q.dequeue();
        dTime(v) = ++clock;
        for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
            if (UNDISCOVERED == status(u)) {
                status(u) = DISCOVERED;
                Q.enqueue(u);
                type(v, u) = TREE;
                parent(u) = v;
            }
            else {
                type(v, u) = CROSS;
            }
        }
        status(v) = VISITED;
    }
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s) {
    reset();
    int clock = 0;
    in v = s;
    do {
        if (UNDISCOVERED == status(v)) {
            DFS(v, clock);
        }
    } while (s != (v = (++v % n));
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int& clock) {
    dTime(v) = ++clock;
    status(v) = DISCOVERED;
    for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
        switch (status(u))
        {
        case UNDISCOVERED:
            type(v, u) = TREE;
            parent(u) = v;
            DFS(u, clock);
            break;
        case DISCOVERED:
            type(v, u) = BACKWARD;
            break;
        default:
            type(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
            break;
            break;
        }
    }
    status(v) = VISITED;
    fTime(v) = ++clock;
}

template <typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int s) {    // assert 0 <= s < n
    reset();
    int clock = 0;
    int v = s;
    Stack<Tv>* S = new Stack<Tv>;
    do {
        if (UNDISCOVERED == status(v)) {
            if (!TSort(v, clock, S)) {
                while (!S->empty()) {
                    S->pop();
                    break;
                }
            }
        }
    } while (s != (v = (++v % n)));
    return S;
}

template <typename Tv, typename Te>
bool Graph<Tv, Te>::TSort(int v, int& clock, Stack<Tv>* S) {    // asert 0 <= v < n
    dTime(v) = ++clock;
    status(v) = DISCOVERED;
    for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
        switch (status(u))
        {
        case UNDISCOVERED:
            parent(u) = v;
            type(v, u) = TREE;
            if (!TSort(u, clock, S)) {
                return false;
            }
            break;
        case DISCOVERED:
            type(v, u) = BACKWARD;
        default:
            type(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS;
            break;
        }
    }
    status(v) = VISITED;
    S->push(vertex(v));
    return true;
}

template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater) {    // assert 0 <= s < n
    reset();
    int v = s;
    do {
        if (UNDISCOVERED == status(v)) {
            PFS(v, prioUpdater);
        }
    } while (s != (v = (++v % n)));
}

template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::PFS(int s, PU prioUpdater) {
    priority(s) = 0;
    status(s) = VISITED;
    parent(s) = -1;
    while (1) {
        for (int w = firstNbr(s); -1 < w; w = nextNbr(s, w)) {
            prioUpdater(this, s, w);
        }
        for (int shortest = INT_MAX, w = 0; w < n; ++w) {
            if (UNDISCOVERED == status(w)) {
                if (shortest > priority(w)) {
                    shortest = priority(w);
                    s = w;
                }
            }
        }
        if (VISITED == status(s)) {
            break;
        }
        status(s) = VISITED;
        type(parent(s), s) = TREE;
    }
}
