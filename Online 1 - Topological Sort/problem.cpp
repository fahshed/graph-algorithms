#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

class Graph
{
    int V;

    vector<int> *adjList;

public:

    Graph(int V)
    {
        this->V = V;
        adjList = new vector<int>[V];
    }

    void addEdge(int a, int b)
    {
        adjList[a].push_back(b);
    }

    void cycle()
    {
        int inDegree[V];
        int topSorted[V];

        for(int i=0; i<V; i++)
        {
            inDegree[i] = 0;
        }

        for(int i=0; i<V; i++)
        {
            vector<int>::iterator itr;

            for(itr = adjList[i].begin(); itr != adjList[i].end(); itr++)
            {
                inDegree[*itr]++;
            }
        }

        queue<int> q;

        for(int i=0; i<V; i++)
        {
            if(inDegree[i] == 0) q.push(i);
        }

        int vCount = 0;
        int v;

        while(!q.empty())
        {
            v = q.front();

            vector<int>::iterator itr;

            for(itr = adjList[v].begin(); itr != adjList[v].end(); itr++)
            {
                inDegree[*itr]--;

                if(inDegree[*itr] == 0) q.push(*itr);
            }

            q.pop();

            topSorted[vCount] = v;

            vCount++;

            cout << vCount << endl;
        }

        if(vCount == V)
        {
            for(int i=0; i<V; i++) cout << topSorted[i] << " ";
            cout << endl;
        }
        else
        {
            cout << "Has cycle." << endl;
        }
    }


    void DFSutil(int source, vector<bool> &visited)
    {
        stack<int> s;
        vector<int> cycle;

        s.push(source);

        int v;

        while(!s.empty())
        {
            v = s.top();

            s.pop();

            if(!visited[v])
            {
                cycle.push_back(v);
                visited[v] = true;
                cout << v << endl;
            }
            else continue;

            vector<int>::iterator itr;

            for(itr = adjList[v].begin(); itr != adjList[v].end(); itr++)
            {
                if(!visited[*itr]) s.push(*itr);
                else
                {
                    cycle.push_back(*itr);

                    vector<int>::iterator itr2;

                    bool block = true;

                    for(itr2 = cycle.begin(); itr2 != cycle.end(); itr2++)
                    {

                        if(block && *itr2 == * itr) block = false;
                        else if(!block)
                        {
                            cout << *itr2 << " ";
                        }
                    }
                }
            }

            cout << endl;

        }
    }

    void cycleDetect()
    {
        vector<bool> visited(V, false);

        for(int i=0; i<V; i++)
        {
            DFSutil(i, visited);
        }
    }
};


int main()
{
    Graph g(5);

    g.addEdge(1, 0);
    g.addEdge(2, 1);
    g.addEdge(0, 2);
    g.addEdge(3, 4);
    g.addEdge(4, 0);
    g.addEdge(0, 3);

    g.cycleDetect();
}
