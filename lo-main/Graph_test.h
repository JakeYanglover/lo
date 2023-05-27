#ifndef GRAPH_TEST_H_INCLUDED
#define GRAPH_TEST_H_INCLUDED
#define INFINITY 1000000
#include <queue>
#include "graph.h"

class option
{
private:
    Graph *G;
public:
// Start with some implementations for the abstract functions
    option(Graph *g)
    {
        G = g;
    }


    void DFS(int v, void (*PreVisit)(int v), void (*PostVisit)(int v), void (*Visiting)(int v))   // Depth first search
    {
        G->setMark(v, VISITED); // Mark the current vertex as visited
        if (PreVisit != NULL) PreVisit(v); // Perform pre-visit action if provided
        if (Visiting != NULL) Visiting(v); // Perform visiting action if provided

        // Traverse all adjacent vertices that are not visited
        for (int w = G->first(v); w < G->n(); w = G->next(v, w)) {
            if (G->getMark(w) == UNVISITED) {
                DFS(w, PreVisit, PostVisit, Visiting); // Recursively visit adjacent vertices
            }
        }

        if (PostVisit != NULL) PostVisit(v); // Perform post-visit action if provided
    }

    void BFS(int start, void (*PreVisit)(int v), void (*PostVisit)(int v), void (*Visiting)(int v))
    {
        queue<int> Q;    // Queue for BFS
        Q.push(start);   // Put start vertex on the queue
        G->setMark(start, VISITED);
        PreVisit(start); // Mark it Visited
        while (!Q.empty())
        {
            int v = Q.front();  // Get next vertex from the queue
            Q.pop();
            Visiting(v);        // Visit the vertex
            for (int w = G->first(v); w < G->n(); w = G->next(v, w))
            {
                if (G->getMark(w) == UNVISITED)
                {
                    G->setMark(w, VISITED);
                    PreVisit(w);   // Mark it Visited
                    Q.push(w);     // Put it on the queue
                }
            }
            PostVisit(v); // Mark it Visited
        }
    }

    void Dijkstra1(int* D, int s)
    {
        for (int i = 0; i < G->n(); i++) {
            G->setMark(i, UNVISITED);
            D[i] = INFINITY;
        }
        //G->setMark(s, VISITED);

        D[s] = 0;
        
        for (int i = 0; i < G->n(); i++) {
            int v = minVertex(D);
            if (v == -1) return;
            G->setMark(v, VISITED);
            for (int w = G->first(v); w < G->n(); w = G->next(v,w))
                if (D[w] > (D[v] + G->weight(v,w)))
                    D[w] = D[v] + G->weight(v,w);
        }
        
    }

    int minVertex(int* D)   // Find min cost vertex
    {
        int i, v = -1;
        // Initialize v to some unvisited vertex
        for (i = 0; i < G->n(); i++)
            if (G->getMark(i) == UNVISITED)
            {
                v = i;
                break;
            }
        for (i++; i < G->n(); i++) // Now find smallest D value
            if ((G->getMark(i) == UNVISITED) && (D[i] < D[v]))
                v = i;
        return v;
    }

    void AddEdgetoMST(int v1, int v2)
    {
        cout << "Add edge " << v1 << " to " << v2 << "\n";
    }

    void Prim(int* D, int s)   // Prim's MST algorithm
    {
        int V[G->n()];
        for (int i = 0; i < G->n(); i++)
        {
            D[i]=INFINITY;
        }
        D[s] = 0;
        for(int i=0; i<G->n();i++)
        {
            int v= minVertex(D);
            G->setMark(v,VISITED);
            if(v!=s)
            {
                AddEdgetoMST(V[v],v);
            }
            if(D[v]==INFINITY) return;
            for(int w = G->first(v);w<G->n();w=G->next(v,w))
            {
                if(D[w]>G->weight(v,w))
                {
                    D[w]=G->weight(v,w);
                    V[w]=v;
                }
            }
        }
        
    }
};

#endif // GRAPH_TEST_H_INCLUDED
