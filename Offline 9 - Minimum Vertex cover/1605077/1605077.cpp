#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3



class Node
{
public:
    int from ;
    int vertex ;
    int weight ;

    Node() ;
    Node(int vertex, int weight, int from = NULL_VALUE) ;
    bool operator==(Node node) ;
    bool operator<(Node node) ;
    bool operator>(Node node) ;
};

Node::Node()
{
    from = NULL_VALUE ;
    vertex = NULL_VALUE ;
    weight = NULL_VALUE ;
}

Node::Node(int vertex, int weight, int from)
{
    this->vertex = vertex ;
    this->weight = weight ;
    this->from = from ;
}

bool Node::operator==(Node node)
{
    return (this->from==node.from && this->vertex==node.vertex && this->weight==node.weight) ;
}

bool Node::operator<(Node node)
{
    return (this->weight<node.weight) ;
}

bool Node::operator>(Node node)
{
    return (this->weight>node.weight) ;
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
    void printList() ;
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
    if(list) delete [] list ;
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
        if( list[i].vertex == item ) return i ;
    }

    return NULL_VALUE ;
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
    if(position < 0 || position >= length) return Node() ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

void ArrayList::printList()
{
    for(int i=0; i<length; i++)
        printf("%d -> ", list[i].vertex) ;
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





class MaxHeap
{
    Node * list ;
    int * aux ;
    int listMaxSize ;
    int length ;
    int LIST_INIT_SIZE ;

public:

    MaxHeap();
    int parent(int i) ;
    int leftChild(int i) ;
    int rightChild(int i) ;
    int size() ;
    bool isEmpty() ;
    void heapify(Node ara[], int n) ;
    Node findMax() ;
    void insert(Node key) ;
    void swap(int x, int y) ;
    void siftDown(int i) ;
    void siftUp(int i) ;
    Node extractMax() ;
    void deleteMax() ;
    Node replace(Node key) ;
    void increaseKey(int i, Node key) ;
    void decreaseKey(int i, Node key) ;
    void deleteNode(int i) ;
    int heapIndex(Node key) ;
};

MaxHeap::MaxHeap()
{
    length = 0 ;
    LIST_INIT_SIZE = 2 ;
    listMaxSize = LIST_INIT_SIZE ;
    list = new Node[listMaxSize] ;
    aux = new int[length] ;
}

int MaxHeap::parent(int i)
{
    return (i-1)/2;
}

int MaxHeap::leftChild(int i)
{
    return 2*i + 1;
}

int MaxHeap::rightChild(int i)
{
    return 2*i + 2;
}

int MaxHeap::size()
{
    return length;
}

bool MaxHeap::isEmpty()
{
    return length == 0;
}

void MaxHeap::heapify(Node ara[], int n)
{
    listMaxSize = 2 * n ;
    length = n ;

    delete [] list ;
    list = new Node[listMaxSize] ;
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
}

Node MaxHeap::findMax()
{
    return list[0];
}

void MaxHeap::insert(Node key)
{
    if(length == listMaxSize)
    {
        listMaxSize = 2 * listMaxSize ;

        int * tempAux;
        tempAux = new int[listMaxSize] ;
        for(int i=0; i<length; i++)
        {
            tempAux[i] = aux[i] ;
        }
        delete [] aux ;
        aux = tempAux ;

        Node * tempList ;
        tempList = new Node[listMaxSize] ;
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

void MaxHeap::swap(int x, int y)
{
    aux[list[x].vertex] = y ;
    aux[list[y].vertex] = x ;

    Node temp = list[x] ;
    list[x] = list[y] ;
    list[y] = temp ;
}

void MaxHeap::siftDown(int i)
{
    int left = leftChild(i) ;
    int right = rightChild(i) ;

    int max = i ;

    if(left<length && list[left]>list[max]) max = left ;
    if(right<length && list[right]>list[max]) max = right ;

    if(max != i)
    {
        swap(i, max) ;
        siftDown(max) ;
    }
}

void MaxHeap::siftUp(int i)
{
    while(i>0 && list[i] > list[parent(i)])
    {
        swap(i, parent(i));
        i = parent(i);
    }
}

Node MaxHeap::extractMax()
{
    if(length==0) return Node();

    Node max = list[0];

    if(length==1)
    {
        length--;
        return max;
    }

    swap(0, length-1);
    length--;

    siftDown(0);

    return max ;
}

void MaxHeap::deleteMax()
{
    if(length==0) return ;

    if(length==1) length--;

    swap(0, length-1);
    length--;

    siftDown(0);
}

Node MaxHeap::replace(Node key)
{
    Node temp = list[0] ;

    list[0] = key ;

    siftDown(0) ;

    return temp ;
}

void MaxHeap::increaseKey(int i, Node key)
{
    if(i>=length) return;

    list[i] = key;

    siftUp(i);
}

void MaxHeap::decreaseKey(int i, Node key)
{
    if(i>=length) return ;
    list[i] = key ;
    siftDown(i) ;
}

void MaxHeap::deleteNode(int i)
{
    if(length==0) return ;
    if(length==1) length-- ;

    swap(i, length-1) ;
    length-- ;

    siftDown(i) ;
}

int MaxHeap::heapIndex(Node key)
{
    return aux[key.vertex] ;
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

    Node * wDist ;
    int * prev ;

public:

    Graph(bool dir = false) ;
    ~Graph() ;
    void setnVertices(int n) ;
    void addEdge(int u, int v, int weight = NULL_VALUE) ;
    void removeEdge(int u, int v) ;
    bool isEdge(int u, int v) ;
    int getIndegree(int u) ;
    int getDegree(int u) ;
    bool hasCommonAdjacent(int u, int v) ;
    void printGraph() ;
    void bfs(int source) ;
    int getDist(int u, int v) ;
    void dfs() ;
    void dfs(int u, int time) ;
    void randVertexCover() ;
    void degreeVertexCover() ;
    void printShortestPath(int v) ;
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
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return ;
    this->nEdges++ ;
    adjList[u].insertItem(v, weight) ;
    if(!directed) adjList[v].insertItem(u, weight) ;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return ;
    this->nEdges-- ;
    adjList[u].removeItem(v) ;
    if(!directed) adjList[v].removeItem(u) ;
}

bool Graph::isEdge(int u, int v)
{
    if(adjList[u].searchItem(v)!=NULL_VALUE)
    {
        return true ;
    }
    else return false ;
}

int Graph::getIndegree(int u)
{
    if(!directed) return NULL_VALUE ;

    int indegree = 0 ;
    int l ;
    for(int i=0; i<nVertices; i++)
    {
        if(adjList[i].searchItem(u)!=NULL_VALUE) indegree++ ;
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

void Graph::printShortestPath(int v)
{
    ArrayList path ;

    path.insertItem(v) ;
    while(prev[v]!=NULL_VALUE)
    {
        v = prev[v] ;
        path.insertItem(v) ;
    }

    int l = path.getLength() ;

    for(int i=l-1; i>=0; i--)
    {
        cout << path.getItem(i).vertex << "->" ;
    }

    cout << endl ;
}

void Graph::randVertexCover()
{
    int u, v ;
    int length ;
    Node item ;
    bool inCover[nVertices] ;
    ArrayList vCover ;

    for(int i=0; i<nVertices; i++)
    {
        inCover[i] = false ;
    }

    Graph g(false) ;
    g.setnVertices(nVertices) ;

    int index = 0 ;
    Node edges[nEdges] ;

    for(int i=0; i<nVertices; i++)
    {
        length = adjList[i].getLength() ;

        for(int j=0; j<length; j++)
        {
            item = adjList[i].getItem(j) ;

            u = i ;
            v = item.vertex ;
            item.from = u ;

            if(!g.isEdge(u, v))
            {
                g.addEdge(u, v) ;
                edges[index] = item ;
                index++ ;
            }
        }
    }

    int i = 0 ;
    while(g.nEdges>=1)
    {
        i = rand() % index ;
        item = edges[i] ;

        //cout << item.from << " " << item.vertex << endl ;
        //cout << endl ;

        if(!inCover[item.from])
        {
            vCover.insertItem(item.from) ;
            inCover[item.from] = true ;

            while(g.adjList[item.from].getLength())
            {
                v = g.adjList[item.from].getItem(0).vertex ;
                g.removeEdge(item.from, v) ;

                //cout << item.from << " " << v << endl ;
            }
        }


        if(!inCover[item.vertex])
        {
            vCover.insertItem(item.vertex) ;
            inCover[item.vertex] = true ;

            length = g.adjList[item.vertex].getLength() ;

            while(g.adjList[item.vertex].getLength())
            {
                v = g.adjList[item.vertex].getItem(0).vertex ;
                g.removeEdge(item.vertex, v) ;

                //cout << item.vertex << " " << v << endl ;
            }
        }

        //cout << endl ;
        //cout << g.nEdges << endl ;
        //cout << endl ;
    }

    //g.printGraph() ;

    int l = vCover.getLength() ;
    cout << l << endl ;
}


void Graph::degreeVertexCover()
{
    int u, v ;
    int length ;
    Node item ;
    bool inCover[nVertices] ;
    ArrayList vCover ;
    bool covered[nEdges] ;

    for(int i=0; i<nVertices; i++)
    {
        inCover[i] = false ;
    }

    for(int i=0; i<nEdges; i++)
    {
        covered[i] = false ;
    }

    Graph g(false) ;
    g.setnVertices(nVertices) ;

    int index = 0 ;
    Node edges[nEdges] ;

    for(int i=0; i<nVertices; i++)
    {
        length = adjList[i].getLength() ;

        for(int j=0; j<length; j++)
        {
            item = adjList[i].getItem(j) ;

            u = i ;
            v = item.vertex ;
            item.from = u ;
            item.weight = getDegree(u) + getDegree(v) ;

            if(!g.isEdge(u, v))
            {
                g.addEdge(u, v) ;
                edges[index] = item ;
                index++ ;
            }
        }
    }


    while(g.nEdges>=1)
    {
        for(int i=0; i<index; i++)
        {
            edges[i].weight = g.getDegree(edges[i].from) + g.getDegree(edges[i].vertex) ;
        }

        int max = 0 ;

        for(int i=0; i<index; i++)
        {
            if(edges[max].weight < edges[i].weight && covered[i]==false) max = i ;
        }

        item = edges[max] ;

        //cout << item.from << " " << item.vertex << endl ;
        //cout << endl ;

        if(!inCover[item.from])
        {
            vCover.insertItem(item.from) ;
            inCover[item.from] = true ;

            while(g.adjList[item.from].getLength())
            {
                v = g.adjList[item.from].getItem(0).vertex ;
                g.removeEdge(item.from, v) ;

                //cout << item.from << " " << v << endl ;
            }
        }

        if(!inCover[item.vertex])
        {
            vCover.insertItem(item.vertex) ;
            inCover[item.vertex] = true ;

            length = g.adjList[item.vertex].getLength() ;

            while(g.adjList[item.vertex].getLength())
            {
                v = g.adjList[item.vertex].getItem(0).vertex ;
                g.removeEdge(item.vertex, v) ;

                //cout << item.vertex << " " << v << endl ;
            }
        }

        //cout << endl ;
        //cout << endl ;

        covered[max] = true ;
    }

    //g.printGraph() ;

    int l = vCover.getLength() ;
    cout << l << endl ;
}



int main()
{
    //freopen("input.txt", "r", stdin) ;
    freopen("graph 4.txt", "r", stdin) ;

    //freopen("output.txt", "w", stdout) ;

    srand(time(NULL)) ;

    int dir, n, m, s ;
    cin >> dir ;
    Graph g(dir) ;
    cin >> n ;
    g.setnVertices(n) ;
    cin >> m ;

    int u, v ;
    for(int i=0; i<m; i++)
    {
        cin >> u >> v ;
        g.addEdge(u, v) ;
    }

    //g.printGraph() ;

    //g.randVertexCover() ;

    g.degreeVertexCover() ;
}
