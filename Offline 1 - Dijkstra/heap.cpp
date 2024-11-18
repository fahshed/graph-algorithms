#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define LIST_INIT_SIZE 2
#define NULL -99999

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

class MaxHeap
{
    int * list;
    int listMaxSize;
    int length;

public:

    MaxHeap()
    {
        length = 0;
    }

    int parent(int i)
    {
        return (i-1)/2;
    }

    int leftChild(int i)
    {
        return 2*i + 1;
    }

    int rightChild(int i)
    {
        return 2*i + 2;
    }

    int size()
    {
        return length;
    }

    bool isEmpty()
    {
        return length == 0;
    }

    void createHeap()
    {
        listMaxSize = LIST_INIT_SIZE;

        cout << "Heap created" << endl;

        length = 0;
    }

    void heapify(int ara[], int n)
    {
        for(int i=0; i<n; i++)
        {
            this->insert(ara[i]);
        }
    }

    int findMax()
    {
        return list[0];
    }

    void insert(int key)
    {
        int i = length;

        list[i] = key;

        siftUp(i);

        length++;
    }

    void siftdown(int i)
    {
        int left = leftChild(i);
        int right = rightChild(i);

        int max = i;

        if(left<length && list[max]<list[left])  max = left;
        if(right<length && list[max]<list[right]) max = right;

        if(max!=i)
        {
            swap(&list[i], &list[max]);
            siftdown(max);
        }
    }

    void siftUp(int i)
    {
        while(i!=0 && list[i] > list[parent(i)])
        {
            swap(&list[i], &list[parent(i)]);
            i = parent(i);
        }
    }

    int extractMax()
    {
        if(length==0) return NULL;

        int temp = list[0];

        if(length==1)
        {
            length--;
            return temp;
        }

        swap(&list[0], &list[length-1]);
        length--;

        siftdown(0);

        return temp;
    }

    void deleteMax()
    {
        if(length==0) return;

        if(length==1) length--;

        swap(&list[0], &list[length-1]);
        length--;

        siftdown(0);
    }

    int replace(int key)
    {
        int temp = list[0];

        list[0] = key;

        siftdown(0);

        return temp;
    }

    void increaseKey(int i, int key)
    {
        cout << "ss" << endl;

        if(i>=length) return;



        list[i] = key;

        siftUp(i);
    }

    void decreaseKey(int i, int key)
    {
        if(i>=length) return;

        list[i]= key;

        siftdown(i);
    }

    void mergeHeap(MaxHeap a, MaxHeap b)
    {
        int l1 = a.size();
        int l2 = b.size();

        int ara[l1+l2];

        for(int i=0; i<l1 ; i++)
        {
            ara[i] = a.list[i];
        }

        int j=0;

        for(int i=l1; i<(l1+l2); i++)
        {
            ara[i] = b.list[j];
            j++;
        }

        this->heapify(ara, l1+l2);
    }

    void meldHeap(MaxHeap *a, MaxHeap *b)
    {
        int l1 = a->size();
        int l2 = b->size();

        cout << l1 << " ";

        int ara[l1+l2];

        for(int i=0; i<l1 ; i++)
        {
            ara[i] = a->list[i];
        }

        int j=0;

        for(int i=l1; i<(l1+l2); i++)
        {
            ara[i] = b->list[j];
            j++;
        }

        cout << l1+l2 << endl;

        for(int i=0; i<l1+l2; i++)
        {
            cout << ara[i] << " ";
        }

        this->heapify(ara, l1+l2);
    }

    void deleteNode(int i)
    {
        if(length==0) return;

        if(length==1) length--;

        swap(&list[i], &list[length-1]);
        length--;

        siftdown(i);
    }
};



int main()
{
    while(1)
    {
        cout << "6.online" << endl;

        int ch;
        scanf("%d",&ch);

        if(ch==1)
        {
            MaxHeap a;
            a.createHeap();
        }
        else if(ch==2)
        {
            MaxHeap *a = new MaxHeap();

            int n;

            cin >> n;

            int ara[n];

            for(int i=0; i<n; i++)
            {
                cin >> ara[i];
            }

            a->heapify(ara, n);

            for(int i=0; i<n; i++)
            {
                cout << a->extractMax() << " ";
            }

        }
        else if(ch==3)
        {
            MaxHeap a;
            a.createHeap();

            int n;

            cin >> n;

            int ara[n];

            for(int i=0; i<n; i++)
            {
                cin >> ara[i];
            }

            a.heapify(ara, n);

            cout << "ss" << endl;


            MaxHeap b;
            b.createHeap();

            cin >> n;

            for(int i=0; i<n; i++)
            {
                cin >> ara[i];
            }

            MaxHeap c;
            c.createHeap();

            c.mergeHeap(a,b);
        }
        else if(ch==4)
        {
            MaxHeap a;
            a.createHeap();

            int n;

            cin >> n;

            int ara[n];

            for(int i=0; i<n; i++)
            {
                cin >> ara[i];
            }

            a.heapify(ara, n);

            cout << a.size() << endl;
        }
        else if(ch==5)
        {
            MaxHeap a;
            a.createHeap();

            if(a.isEmpty()) cout << "Empty" << endl;
        }
        else if(ch==6)
        {
            MaxHeap a;
            a.createHeap();

            int n;

            cin >> n;

            int ara[n];

            for(int i=0; i<n; i++)
            {
                cin >> ara[i];
            }

            a.heapify(ara, n);

/*
            for(int i=0; i<n; i++)
            {
                ara[i] = a.extractMax();
            }
*/
            for(int i=0; i<n; i++)
            {
                cout << ara[i] << " ";
            }


            cout << endl;

            int value;

            cin >> value;
            int temp;

            int coins[n];
            int freq[n];
            int counter = 0;
            int index = 0;

            for(int i=0; i<n; i++)
            {
                temp = a.extractMax();

                if(value/temp!=0)
                {
                    coins[index] = temp;
                    freq[index] = value/temp;
                    counter = counter + freq[index];
                    value = value % temp;
                    index++;
                }

                if(value==0) break;
            }

            cout << endl;

            cout << counter << endl;

            for(int i=0; i< index; i++)
            {
                cout << coins[i] << " " << freq[i] << endl;
            }


        }
        else if(ch==7)
        {
            MaxHeap a;
            a.createHeap();

            int n;

            cin >> n;

            int ara[n];

            for(int i=0; i<n; i++)
            {
                cin >> ara[i];
            }

            a.heapify(ara, n);

            cout << "Enter key and index : ";

            int key,i;

            cin >>  key;

            cin >> i;

            a.decreaseKey(key,i);
        }
        else if(ch==8)
        {
            MaxHeap *a = new MaxHeap();
            a->createHeap();

            int n;

            cin >> n;

            int ara[n];

            for(int i=0; i<n; i++)
            {
                cin >> ara[i];
            }

            a->heapify(ara, n);

            MaxHeap *b = new MaxHeap();

            b->createHeap();

            cin >> n;

            for(int i=0; i<n; i++)
            {
                cin >> ara[i];
            }

            b->heapify(ara, n);

            MaxHeap c;

            c.createHeap();

            c.meldHeap(a, b);

            int l = c.size();

            for(int i=0; i<l; i++)
            {
                cout << c.extractMax() << " ";
            }

            delete a;

            delete b;
        }
        else if(ch==9)
        {
            MaxHeap a;
            a.createHeap();

            int n;

            cin >> n;

            int ara[n];

            for(int i=0; i<n; i++)
            {
                cin >> ara[i];
            }

            a.heapify(ara, n);

            cout << "Max : " << a.findMax() << endl;
        }
        else if(ch==10)
        {
            MaxHeap a;
            a.createHeap();

            int n;

            cin >> n;

            int ara[n];

            for(int i=0; i<n; i++)
            {
                cin >> ara[i];
            }

            a.heapify(ara, n);

            cout << "Enter key ";

            int key;

            cin >>  key;

            a.insert(key);
        }
        else if(ch==11)
        {
            MaxHeap a;
            a.createHeap();

            int n;

            cin >> n;

            int ara[n];

            for(int i=0; i<n; i++)
            {
                cin >> ara[i];
            }

            a.heapify(ara, n);

            a.deleteMax();
        }
        else if(ch==12)
        {

            MaxHeap a;
            a.createHeap();

            int n;

            cin >> n;

            int ara[n];

            for(int i=0; i<n; i++)
            {
                cin >> ara[i];
            }

            a.heapify(ara, n);

            cout << "Enter key index: ";

            int key;

            cin >> key;

            a.replace(key);
        }
    }
}

