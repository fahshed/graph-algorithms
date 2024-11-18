#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3



class Node
{
public:
    int vertex;
    int weight;

    Node();
    Node(int vertex, int weight);
    bool operator==(Node node);
};

Node::Node()
{
    vertex = NULL_VALUE ;
    weight = NULL_VALUE ;
}

Node::Node(int vertex, int weight)
{
    this->vertex = vertex ;
    this->weight = weight ;
}

bool Node::operator==(Node node)
{
    return (this->vertex==node.vertex && this->weight==node.weight);
}



class ArrayList
{
    Node *list;
    int length;
    int listMaxSize;
    int listInitSize;

public:

    ArrayList();
    ~ArrayList();
    void insertItem(int item, int weight = NULL_VALUE) ;
    int searchItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int position) ;
    Node getItem(int position) ;
    int getLength() ;
    void printList();
};

ArrayList::ArrayList()
{
    listInitSize = 2;
    listMaxSize = listInitSize;
    list = new Node[listMaxSize];
    length = 0;
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

void ArrayList::insertItem(int item, int weight)
{
    if (length == listMaxSize)
    {
        Node * tempList ;
        listMaxSize = 2 * listMaxSize ;
        tempList = new Node[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ;
        }
        delete[] list ;
        list = tempList ;
    };

    Node temp(item, weight) ;

    list[length] = temp ;
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i].vertex == item ) return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position)
{
    if ( position < 0 || position >= length ) return ;
    list[position] = list[length-1] ;
    length-- ;
}

void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ;
    removeItemAt(position) ;
}

Node ArrayList::getItem(int position)
{
    if(position < 0 || position >= length) return Node();
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

void ArrayList::printList()
{
    for(int i=0; i<length; i++)
        printf("[%d, %d] -> ", list[i].vertex, list[i].weight);
    //printf("Current size: %d, current length: %d\n", listMaxSize, length);
}




class Queue
{
    int queueInitSize;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize]; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}

void Queue::enqueue(int item)
{
    if(length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}

bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}

int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}

Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}






class MinHeap
{
    int * list ;
    int * aux ;
    int listMaxSize ;
    int length ;
    int LIST_INIT_SIZE ;

public:

    MinHeap();
    int parent(int i) ;
    int leftChild(int i) ;
    int rightChild(int i) ;
    int size() ;
    bool isEmpty() ;
    void heapify(int ara[], int n) ;
    int findMin() ;
    void insert(int key) ;
    void swap(int x, int y) ;
    void siftDown(int i) ;
    void siftUp(int i) ;
    int extractMin() ;
    void deleteMin() ;
    int replace(int key) ;
    void increaseKey(int i, int key) ;
    void decreaseKey(int i, int key) ;
    void deleteNode(int i) ;
};

MinHeap::MinHeap()
{
    length = 0 ;
    LIST_INIT_SIZE = 2 ;
    listMaxSize = LIST_INIT_SIZE ;
    list = new int[listMaxSize] ;
    aux = new int[length] ;
}

int MinHeap::parent(int i)
{
    return (i-1)/2;
}

int MinHeap::leftChild(int i)
{
    return 2*i + 1;
}

int MinHeap::rightChild(int i)
{
    return 2*i + 2;
}

int MinHeap::size()
{
    return length;
}

bool MinHeap::isEmpty()
{
    return length == 0;
}

void MinHeap::heapify(int ara[], int n)
{
    listMaxSize = 2 * n ;
    length = n ;

    delete [] list ;
    list = new int[listMaxSize] ;
    delete [] aux ;
    aux = new int[listMaxSize] ;

    for(int i=0; i<length; i++)
    {
        list[i] = ara[i] ;
        aux[i] = i ;
    }

    for(int i=(length-1)/2; i>=0; i--)
    {
        siftDown(i);
    }

    for(int i=0; i<length; i++)
    {
        cout << list[i] << " " ;
    }

    cout << endl ;

    for(int i=0; i<length; i++)
    {
        cout << aux[i] << " " ;
    }

    cout << endl ;
}

int MinHeap::findMin()
{
    return list[0];
}

void MinHeap::insert(int key)
{
    if(length == listMaxSize)
    {
        listMaxSize = 2 * listMaxSize ;

        int * tempList ;
        tempList = new int[listMaxSize] ;

        for(int i=0; i<length; i++)
        {
            tempList[i] = aux[i] ;
        }
        delete [] aux ;
        aux = tempList ;

        for(int i = 0; i<length ; i++)
        {
            tempList[i] = list[i] ;
        }
        delete [] list ;
        list = tempList ;
    };

    list[length] = key ;
    aux[length] = length ;
    siftUp(length) ;

    length++ ;
}

void MinHeap::swap(int x, int y)
{
    int temp = list[x] ;
    list[x] = list[y] ;
    list[y] = temp ;


}

void MinHeap::siftDown(int i)
{
    int left = leftChild(i) ;
    int right = rightChild(i) ;

    int min = i ;

    if(left<length && list[left]<list[min]) min = left ;
    if(right<length && list[right]<list[min]) min = right ;

    if(min != i)
    {
        swap(i, min) ;
        siftDown(min) ;
    }
}

void MinHeap::siftUp(int i)
{
    while(i!=0 && list[i] < list[parent(i)])
    {
        swap(i, parent(i));
        i = parent(i);
    }
}

int MinHeap::extractMin()
{
    if(length==0) return NULL_VALUE;

    int min = list[0];

    if(length==1)
    {
        length--;
        return min;
    }

    swap(0, length-1);
    length--;

    siftDown(0);

    return min ;
}

void MinHeap::deleteMin()
{
    if(length==0) return ;

    if(length==1) length--;

    swap(0, length-1);
    length--;

    siftDown(0);
}

int MinHeap::replace(int key)
{
    int temp = list[0] ;

    list[0] = key ;

    siftDown(0) ;

    return temp ;
}

void MinHeap::increaseKey(int i, int key)
{
    if(i>=length) return;

    list[i] = key;

    siftDown(i);
}

void MinHeap::decreaseKey(int i, int key)
{
    if(i>=length) return ;

    list[i] = key ;

    siftUp(i) ;
}

void MinHeap::deleteNode(int i)
{
    if(length==0) return ;
    if(length==1) length-- ;

    swap(i, length-1) ;
    length-- ;

    siftDown(i) ;
}




class Graph
{
    int nVertices;
    int nEdges ;
    bool directed ;
    ArrayList  * adjList ;

    int * color ;
    int * parent ;
    int * dist ;

    int * first ;
    int * last ;
    int time ;

    int * wDist ;
    int * prev ;

public:

    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v, int weight = NULL_VALUE);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getIndegree(int u);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    void printGraph();
    void bfs(int source);
    int getDist(int u, int v);
    void dfs();
    void dfs(int u, int time);

    void dijkstra(int s) ;
};

Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ;

    color  = 0 ;
    parent = 0 ;
    dist   = 0 ;

    first  = 0 ;
    last   = 0 ;
}

Graph::~Graph()
{
    if(adjList) delete[] adjList ;
    if(color) delete[] color ;
    if(parent) delete[] parent ;
    if(dist) delete[] dist ;
    if(first) delete[] first ;
    if(last) delete[] last ;
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ;
    adjList = new ArrayList[nVertices] ;
}

void Graph::addEdge(int u, int v, int weight)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    this->nEdges++ ;
    adjList[u].insertItem(v, weight) ;
    if(!directed) adjList[v].insertItem(u, weight) ;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return ;
    this->nEdges-- ;
    adjList[u].removeItem(v) ;
    if(!directed) adjList[v].removeItem(v) ;
}

bool Graph::isEdge(int u, int v)
{
    if(adjList[u].searchItem(v)!=NULL_VALUE) return true;
    else return false;
}

int Graph::getIndegree(int u)
{
    if(!directed) return NULL_VALUE ;

    int indegree = 0 ;
    int l;
    for(int i=0; i<nVertices; i++)
    {
        if(adjList[i].searchItem(u)!=NULL_VALUE) indegree++;
    }
    return indegree ;
}

int Graph::getDegree(int u)
{
    if(!directed) return adjList[u].getLength();

    return (adjList[u].getLength() + getIndegree(u)) ;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    int ulength = adjList[u].getLength() ;
    int vlength = adjList[v].getLength() ;

    int item ;

    for(int i=0; i<ulength; i++)
    {
        item = adjList[u].getItem(i).vertex ;

        for(int j=0; j<vlength; j++)
        {
            if(item == adjList[v].getItem(j).vertex) return true ;
        }
    }

    return false ;
}

void Graph::bfs(int source)
{
    color  = new int[nVertices] ;
    parent = new int[nVertices] ;
    dist   = new int[nVertices] ;

    int length ;
    int item ;
    int u ;

    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }

    Queue q ;

    color[source] = GREY ;
    dist[source] = 0 ;

    q.enqueue(source) ;

    while(!q.empty())
    {
        u = q.dequeue() ;

        length = adjList[u].getLength() ;

        for(int i=0; i<length; i++)
        {
            item  = adjList[u].getItem(i).vertex ;

            if(color[item]==WHITE)
            {
                color[item] = GREY ;
                parent[item] = u ;
                dist[item] = dist[u] + 1 ;

                q.enqueue(item) ;
            }
        }

        color[u] = BLACK ;

        printf("%d ", u) ;
    }

    printf("\n") ;
}

int Graph::getDist(int u, int v)
{
    bfs(u);
    return dist[v];
}

void Graph::dfs()
{
    color  = new int[nVertices];
    parent = new int[nVertices];
    first = new int[nVertices];
    last  = new int[nVertices];

    time = 0;

    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE;
        parent[i] = -1;
    }


    for(int i=0; i<nVertices; i++)
    {
        if(color[i]==WHITE)
        {
            dfs(i,time);
        }
    }

    printf("\n");
}

void Graph::dfs(int u, int time)
{
    int length ;
    int item ;

    color[u] = GREY ;
    first[u] = time + 1 ;

    printf("%d ", u) ;

    length = adjList[u].getLength() ;

    for(int i=0; i<length; i++)
    {
        item  = adjList[u].getItem(i).vertex ;

        if(color[item]==WHITE)
        {
            parent[item] = u ;
            dfs(item, time) ;
        }
    }

    color[u] = BLACK ;
    last[u] = time + 1 ;
}

void Graph::printGraph()
{
    printf("Number of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d -> ", i);
        adjList[i].printList();
        printf("\n");
    }
}

void Graph::dijkstra(int s)
{
    int u, v, l ;
    int length ;
    wDist = new int[nVertices] ;
    prev = new int[nVertices] ;

    for(int i=0; i<nVertices; i++)
    {
        wDist[i] = INFINITY ;
        prev[i] = NULL_VALUE ;
    }

    dist[s] = 0 ;

    MinHeap H ;
    H.heapify(dist, nVertices) ;

    while(!H.isEmpty())
    {
        u = H.extractMin() ;
        length = adjList[u].getLength() ;

        for(int i=0; i<length; i++)
        {
            v = adjList[u].getItem(i).vertex ;
            l = adjList[u].getItem(i).weight ;

            if(dist[v] > (dist[u] + l))
            {
                dist[v] = dist[u] + l ;
                prev[v] = u ;
                //H.decreaseKey()
            }
        }
    }
}



int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m ;
    Graph g(true) ;
    cin >> n ;
    g.setnVertices(n) ;
    cin >> m ;

    int u, v, w;

    for(int i=0; i<m; i++)
    {
        cin >> u >> v >> w ;

        g.addEdge(u, v, w) ;
    }

    cin >> n ;

    int ara[n] ;

    for(int i=0; i<n; i++)
    {
        cin >> ara[i] ;
    }

    MinHeap H ;

    g.printGraph();
    g.bfs(2);
    H.heapify(ara, n) ;

    //H.insert(5);

    //H.decreaseKey(3, 0) ;
    //H.increaseKey(1, 11) ;
    //H.insert(15) ;

    /*while(!H.isEmpty())
    {
        cout << H.extractMin() << " " ;
    }

    /*
    while(1)
    {
        /*printf("2. Remove Edge. 3. Edge check. \n");
        printf("4. Degree of a vertex. 5.Has common Adjacent. 6. BFS. 7.Get distance. 8.DFS. 9. Print Graph. 10. Exit.\n");

        int ch;
        scanf("%d",&ch);

        if(ch==1)
        {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            g.addEdge(u, v, w);
        }
        else if(ch==2)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u, v);
        }
        else if(ch==3)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.isEdge(u, v)) printf("Edge exist.\n");
            else printf("Edge does not exist.\n");
        }
        else if(ch==4)
        {
            int u;
            scanf("%d", &u);
            printf("Degree: %d\n", g.getDegree(u));
        }
        else if(ch==5)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            if(g.hasCommonAdjacent(u, v)) printf("Yes.\n");
            else printf("No.\n");
        }
        else if(ch==6)
        {
            int u;
            scanf("%d", &u);
            g.bfs(u);
        }
        else if(ch==7)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("The distance from %d to %d is %d.\n", u, v, g.getDist(u,v));
        }
        else if(ch==8)
        {
            g.dfs();
        }
        else if(ch==9)
        {
            g.printGraph();
        }
        else if(ch==10)
        {
            break;
        }
    }
    */
}
