#include <iostream>
#include <iomanip>

using namespace std;

void createmap(int *a);
void dumparr(int *a);
bool DFSLoop(int *a,int i);
void kruskal(int *a);
void prim(int *a);

int main()
{
    int matrix[100]= {0};
    createmap(matrix);
    dumparr(matrix);
    kruskal(matrix);
    prim(matrix);
    //DFSLoop(matrix,0);
    return 0;
}

void dumparr(int *a)
{
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            cout << setw(3) << a[i*10+j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void createmap(int *a)
{
    int start,dest,weight;
    int cnt;
    cin >> cnt;
    while(cnt)
    {
        cin >> start >> dest >> weight;
        cnt--;
        a[start*10+dest]=weight;
        a[dest*10+start]=weight;
    }
}

/* test case
12
0 9 1
0 1 2
1 2 4
1 3 3
1 4 5
3 4 6
1 5 7
5 6 9
6 7 8
7 8 10
8 9 11
3 5 12
*/

void prim(int *a)
{
    cout << "Prim's Algorithm:" << endl;
    int prim_matrix[100];
    int prim_ans[100]= {0};
    int prim_visited[10]= {0};
    int min; // record the min
    int u = 0, v = 0; // row&column
    int total = 0;

    // copy array & change 0 to 999
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            prim_matrix[i*10+j] = a[i*10+j];
            if(prim_matrix[i*10+j]==0)
            {
                prim_matrix[i*10+j] = 999;
            }
        }
    }

    // starting algorithm
    dumparr(prim_ans); // print init stat
    prim_visited[0] = 1;
    for(int counter = 0; counter < 9 ; counter++) // find nine times(ten nodes)
    {
        min = 999; // restart the min
        for(int i = 0; i < 10; i++) // ten nodes
        {
            if(prim_visited[i]==1) // focus the node
            {
                for(int j = 0; j < 10; j++) // and find the path who is min
                {
                    if(prim_visited[j]==0) // only care unvisited
                    {
                        if(min > prim_matrix[i*10+j]) // record min & index
                        {
                            min = prim_matrix[i*10+j];
                            u = i;
                            v = j;
                        }
                    }
                }
            }
        }
        // after interview ten nodes , we get the only one node with the min path
        prim_visited[v] = 1;
        total += min;
        prim_ans[u*10+v] = prim_matrix[u*10+v];
        prim_ans[v*10+u] = prim_matrix[v*10+u];
        dumparr(prim_ans);
        prim_matrix[u*10+v] = 999; //remove the weight
        prim_matrix[v*10+u] = 999;
        //cout<<"edge connect"<<u<<"->"<<v<<": "<<min<<endl;
    }
    cout<<"The total weight of the spanning tree is "<<total<<endl<<endl;
}

void kruskal(int *a)
{
    cout << "Kruskal's Algorithm:" << endl;
    int kruskal_matrix[100];
    int kruskal_ans[100]= {0};
    int parent[10]= {0}; // store parent of nodes
    int min;
    int u = 0;
    int v = 0;
    int temp1,temp2;
    int noOfEdges = 1;
    int total = 0;

    // copy array & change 0 to 999
    for(int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            kruskal_matrix[i*10+j] = a[i*10+j];
            if(kruskal_matrix[i*10+j]==0)
            {
                kruskal_matrix[i*10+j] = 999;
            }
        }
    }

    // starting algorithm
    dumparr(kruskal_ans);
    while(noOfEdges < 10)
    {
        min = 999;
        // find the min edge
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if(kruskal_matrix[i*10+j] < min)
                {
                    min = kruskal_matrix[i*10+j];
                    u = i;
                    v = j;
                    temp1=u;
                    temp2=j;
                }
            }
        }

        // check loop(cycle)
        while(parent[u]) // parent[u]!=0
        {
            u = parent[u];
        }
        while(parent[v]) // parent[v]!=0
        {
            v = parent[v];
        }
        // if v==u , loop exist
        if(v!=u)
        {
            // success connect!!!
            noOfEdges++;
            cout<<"edge connect "<<temp1<<"->"<<temp2<<": "<<min<<endl;
            total+=min;
            parent[v] = u;

            kruskal_ans[temp1*10+temp2]=kruskal_matrix[temp1*10+temp2];
            kruskal_ans[temp2*10+temp1]=kruskal_matrix[temp2*10+temp1];
            dumparr(kruskal_ans);
        }
        // no matter what , clean the data
        kruskal_matrix[temp1*10+temp2] = 999;
        kruskal_matrix[temp2*10+temp1] = 999;
    }
    cout<<"The total weight of the spanning tree is "<<total<<endl<<endl;
}

//i=0~9 有十個頂點
int visited[10]= {0};
bool DFSLoop(int *a,int i) //第二個參數是目前走訪頂點
{
    cout<<i<<" "; //印出拜訪順序
    visited[i]=1; //已拜訪過
    for(int j=0; j<10; j++)   //拜訪每個頂點
    {
        if(visited[j]!=1 && a[i*10+j]>0)  //拜訪過不用再拜訪
        {
            if(a[j*10+j]!=0)
            {
                return false; //有迴路
            }
            DFSLoop(a, j); //遞迴
        }
    }
}
