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
    int vertex ;
    int weight ;
    int capacity ;

    Node() ;
    Node(int vertex, int weight, int capacity = NULL_VALUE) ;
    bool operator==(Node node) ;
    bool operator<(Node node) ;
    bool operator>(Node node) ;
};

Node::Node()
{
    vertex = NULL_VALUE ;
    weight = NULL_VALUE ;
    capacity = NULL_VALUE ;
}

Node::Node(int vertex, int weight, int capacity)
{
    this->vertex = vertex ;
    this->weight = weight ;
    this->capacity = capacity ;
}

bool Node::operator==(Node node)
{
    return (this->vertex==node.vertex && this->weight==node.weight);
}

bool Node::operator<(Node node)
{
    return (this->weight<node.weight);
}

bool Node::operator>(Node node)
{
    return (this->weight>node.weight);
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
    void insertItem(int item, int weight = NULL_VALUE, int capacity = NULL_VALUE) ;
    int searchItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int position) ;
    void changeItem(int item, int weight, int capacity = NULL_VALUE) ;
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
    if(list) delete [] list;
    list = 0 ;
}

void ArrayList::insertItem(int item, int weight, int capacity)
{
    if (length == listMaxSize)
    {
        Node * tempList ;
        listMaxSize = 2 * listMaxSize ;
        tempList = new Node[listMaxSize] ;
        int i ;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ;
        }
        delete[] list ;
        list = tempList ;
    }

    Node temp(item, weight, capacity) ;

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

void ArrayList::changeItem(int item, int weight, int capacity)
{
    int position = searchItem(item) ;
    if(weight!=NULL_VALUE) list[position].weight = weight ;
    if(capacity!=NULL_VALUE) list[position].capacity = capacity ;
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
        printf("[%d, %d, (%d)] -> ", list[i].vertex+1, list[i].weight, list[i].capacity+list[i].weight);
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
    Node * list ;
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
    void heapify(Node ara[], int n) ;
    Node findMin() ;
    void insert(Node key) ;
    void swap(int x, int y) ;
    void siftDown(int i) ;
    void siftUp(int i) ;
    Node extractMin() ;
    void deleteMin() ;
    Node replace(Node key) ;
    void increaseKey(int i, Node key) ;
    void decreaseKey(int i, Node key) ;
    void deleteNode(int i) ;
    int heapIndex(Node key) ;
};

MinHeap::MinHeap()
{
    length = 0 ;
    LIST_INIT_SIZE = 2 ;
    listMaxSize = LIST_INIT_SIZE ;
    list = new Node[listMaxSize] ;
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

void MinHeap::heapify(Node ara[], int n)
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

Node MinHeap::findMin()
{
    return list[0];
}

void MinHeap::insert(Node key)
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

void MinHeap::swap(int x, int y)
{
    aux[list[x].vertex] = y ;
    aux[list[y].vertex] = x ;

    Node temp = list[x] ;
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
    while(i>0 && list[i] < list[parent(i)])
    {
        swap(i, parent(i));
        i = parent(i);
    }
}

Node MinHeap::extractMin()
{
    if(length==0) return Node();

    Node min = list[0];

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

Node MinHeap::replace(Node key)
{
    Node temp = list[0] ;

    list[0] = key ;

    siftDown(0) ;

    return temp ;
}

void MinHeap::increaseKey(int i, Node key)
{
    if(i>=length) return;

    list[i] = key;

    siftDown(i);
}

void MinHeap::decreaseKey(int i, Node key)
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

int MinHeap::heapIndex(Node key)
{
    return aux[key.vertex] ;
}




class Graph
{
    int nVertices;
    int nEdges ;
    bool directed ;
    bool network ;
    ArrayList  * adjList ;
    int * inDegree ;

    int * color ;
    int * parent ;
    int * dist ;

    int * first ;
    int * last ;
    int time ;

    int * prev ;

    int * flow ;

public:

    Graph(bool dir = false, bool net = false) ;
    ~Graph() ;
    void setnVertices(int n) ;
    void addEdge(int u, int v, int capacity = NULL_VALUE, int weight = NULL_VALUE ) ;
    void setWeightCapacity(int u, int v, int w, int c = NULL_VALUE) ;
    void removeEdge(int u, int v) ;
    bool isEdge(int u, int v) ;
    int getCapacity(int u, int v) ;
    int getFlow(int u, int v) ;
    int getDegree(int u) ;
    bool hasCommonAdjacent(int u, int v) ;
    void printGraph() ;
    void printEdges() ;
    void bfs(int source) ;
    void bfsFlow(int source) ;
    int getDist(int u, int v) ;
    void dfs() ;
    void dfs(int u, int time) ;
    void printShortestPath(int v) ;
    int fordFulkerson(int s, int t) ;
};

Graph::Graph(bool dir, bool net)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ;
    network = net ;

    color  = 0 ;
    parent = 0 ;
    dist   = 0 ;

    first  = 0 ;
    last   = 0 ;
    time = 0 ;

    prev = 0 ;

    flow = 0 ;
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
    if(directed)
    {
        inDegree = new int[nVertices] ;
        for(int i=0; i<nVertices; i++)
            inDegree[i] = 0 ;
    }
}

void Graph::addEdge(int u, int v, int capacity, int weight)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return ;
    this->nEdges++ ;
    adjList[u].insertItem(v, weight, capacity) ;
    if(!directed) adjList[v].insertItem(u, weight, capacity) ;
    else inDegree[v]++ ;
}

void Graph::setWeightCapacity(int u, int v, int w, int c)
{
    adjList[u].changeItem(v, w, c) ;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return ;
    this->nEdges-- ;
    adjList[u].removeItem(v) ;
    if(!directed) adjList[v].removeItem(v) ;
    else inDegree[v]-- ;
}

bool Graph::isEdge(int u, int v)
{
    if(adjList[u].searchItem(v)!=NULL_VALUE) return true ;
    else return false ;
}

int Graph::getCapacity(int u, int v)
{
    int position = adjList[u].searchItem(v) ;
    return adjList[u].getItem(position).capacity ;
}

int Graph::getFlow(int u, int v)
{
    int position = adjList[u].searchItem(v) ;
    return adjList[u].getItem(position).weight ;
}

int Graph::getDegree(int u)
{
    if(!directed) return adjList[u].getLength() ;

    return (adjList[u].getLength() + inDegree[u]) ;
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

void Graph::bfsFlow(int source)
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
            if(adjList[u].getItem(i).capacity <= 0) continue ;

            item  = adjList[u].getItem(i).vertex ;

            if(color[item] == WHITE)
            {
                color[item] = GREY ;
                parent[item] = u ;
                dist[item] = dist[u] + 1 ;

                q.enqueue(item) ;
            }
        }

        color[u] = BLACK ;
    }
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
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d -> ", i+1);
        adjList[i].printList();
        printf("\n");
    }

    cout << endl ;
}

void Graph::printEdges()
{
    int length = 0, v;
    cout << "\nEdges: " << endl ;
    for(int i=0; i<nVertices; i++)
    {
        length = adjList[i].getLength() ;

        for(int j=0; j<length; j++)
        {
            v = adjList[i].getItem(j).vertex ;

            cout << i+1 << " " << v+1 << " " << adjList[i].getItem(j).weight << endl ;
        }
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

int Graph::fordFulkerson(int s, int t)
{
    int length = 0 ;
    int u, v, flow, capacity ;
    int bottleNeck = INFINITY ;
    int maxFlow = 0 ;

    Graph residual(true, true) ;
    residual.setnVertices(nVertices) ;

    for(int i=0; i<nVertices; i++)
    {
        length = adjList[i].getLength() ;
        for(int j=0; j<length; j++)
        {
            v = adjList[i].getItem(j).vertex ;
            capacity = getCapacity(i, v) ;
            setWeightCapacity(i, v, 0, capacity) ;
            residual.addEdge(i, v, capacity, 0) ;
            residual.addEdge(v, i, 0, NULL_VALUE) ;
        }
    }


    while(1)
    {
        residual.bfsFlow(s) ;
        if(residual.parent[t]==-1) break ;

        v = t ;
        while(residual.parent[v]!=-1)
        {
            u = residual.parent[v] ;
            capacity = residual.getCapacity(u, v) ;
            if(bottleNeck >= capacity) bottleNeck = capacity ;
            v = u ;
        }

        v = t ;
        while(residual.parent[v]!=-1)
        {
            u = residual.parent[v] ;
            flow = getFlow(u, v) ;
            if(flow!=NULL_VALUE)
            {
                capacity = getCapacity(u, v) ;
                setWeightCapacity(u, v, flow+bottleNeck, capacity-bottleNeck) ;
                residual.setWeightCapacity(u, v, flow+bottleNeck, capacity-bottleNeck) ;
                residual.setWeightCapacity(v, u, NULL_VALUE, flow+bottleNeck) ;
            }
            else
            {
                capacity = getCapacity(v, u) ;
                setWeightCapacity(v, u, flow-bottleNeck, capacity+bottleNeck) ;
                residual.setWeightCapacity(u, v, NULL_VALUE, capacity-bottleNeck) ;
                residual.setWeightCapacity(v, u, flow-bottleNeck, capacity+bottleNeck) ;
            }
            v = u ;
        }
    }

    length = adjList[s].getLength() ;
    for(int i=0; i<length; i++)
    {
        maxFlow = maxFlow + adjList[s].getItem(i).weight ;
    }

    bfsFlow(s) ;

    cout << "Edges of minimum cut: " << endl ;
    for(int i=0; i<nVertices; i++)
    {
        length = adjList[i].getLength() ;
        for(int j=0; j<length; j++)
        {
            v = adjList[i].getItem(j).vertex ;
            if(parent[i]!=-1 && parent[v]==-1) cout << i+1 << " " << v+1 << " " << adjList[i].getItem(j).weight << endl ;
        }
    }

    return maxFlow ;
}


int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int dir, net, n, m, s, t ;
    cin >> dir >> net ;
    Graph g(dir, net) ;
    cin >> n ;
    g.setnVertices(n) ;
    cin >> m ;

    int u, v, w, c ;
    for(int i=0; i<m; i++)
    {
        cin >> u >> v >> c;
        g.addEdge(u-1, v-1, c) ;
    }

    cin >> s >> t ;

    cout << "\nMax Flow: " << g.fordFulkerson(s-1, t-1) << endl ;

    g.printEdges() ;
    g.printGraph() ;
}