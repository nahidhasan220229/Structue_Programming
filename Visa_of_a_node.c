//Student ID: 220229
//Project 1:
//Traverse every node with visa 


#include <stdio.h>

int flag[100000]= {0},pp=0;                                                    //flag for check node path, pp for path count

struct Node
{
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};

int addNode (struct Node * p, int nid, int count)                                //add node to node
{
    int i =0, ncount = count;
    for (i=0;i<count;i++)
    {
        if (p[i].nodeid == nid) 
        { 
            break; 
        }
    }
    if (i == count)
    {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

void addAdjacent (struct Node *p, int nid1, int nid2, int cost, int count)                                //adjacent node list
{
    int i =0, index;
    for (i=0;i<count;i++)
    {
        if (p[i].nodeid == nid1)
        {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c+1;
           
            break;
        }
    }
}

int added (int * list, int lcount, int nid)                            //check the node with previous element
{
    int i =0;
    for (i=0;i<lcount;i++)
    {
        if (list[i] == nid) { return 1; }
    }
    return 0;
}


void findpath (struct Node * p, int count, int start, int end, int * list, int *clist, int lcount)            //find every path of the graph
{
    int index = 0;
   
   
    //check if list contains the end node
    if (list[lcount-1] == end)
    {
        int tcost = 0, x = 1;
        for(int i = 0; i < lcount; i++){
            if(flag[list[i]] == 0){                     //if visa of the node is not present in the list then avoid the node
                x = 0;
                break;
            }
        }
        if(x == 1){
            printf ("\n");
            for (int i=0;i<lcount;i++)
            {
                printf (" %d ", list[i]);
                tcost += clist[i];
            }
            pp++;
            printf (" cost = %d", tcost);
        }
        return;
    }
   
    for (int i=0;i<count;i++)
    {
        if (p[i].nodeid == start) { index = i; break; }
    }
   
    for (int i=0;i<p[index].adjcount;i++)
    {
        int a = added (list, lcount, p[index].adjs[i]);
        if (a == 0)
        {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;
           
            findpath (p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}

int main() {
   
    struct Node nodes[50];
    int nodecount = 0;
    int n1=0, n2=0, c = 0;
   
    while (1)
    {
        printf ("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c== -9) {break;}
        nodecount = addNode (&nodes[0], n1, nodecount);
        nodecount = addNode (&nodes[0], n2, nodecount);
       
        addAdjacent (&nodes[0], n1, n2, c, nodecount);
        addAdjacent (&nodes[0], n2, n1, c, nodecount);
    }
   
    int start, end;
    printf ("start, end ? ");
    scanf ("%d %d", &start, &end);
    flag[start]++;                      //Starting Node do not need any visa

    int visa[50];                       //Take visa.....
    printf("List of visa: ");

    for(int i=0;i<50;i++)
    {
        scanf("%d",&visa[i]);
        if(visa[i]==-9)
        {
            break;
        }
        flag[visa[i]]++;                //Surity of having visa in particular node
    }

    int NoNeedVisa[50];
    printf("Enter the Node which do not need visa: ");
    for(int i=0;i<50;i++)
    {
        scanf("%d",&NoNeedVisa[i]);
        if(NoNeedVisa[i]==-9)
        {
            break;
        }
        flag[NoNeedVisa[i]]++;                //Surity of having visa in particular node
    }
    int list[50], clist[50], lcount = 0;
    list[0] = start; clist[0] = 0; lcount = 1;

    findpath (nodes, nodecount, start, end, list, clist, lcount);
    if(pp==0)
    {
        printf("No path found");
    }

    return 0;
}
