//Student ID: 220229
//Project 2:
//Finding all tringle in a list


#include <stdio.h>
int num_tringle=0, path=0, Adj_list[100000][2];               //number of tringle,total path,list of adjacent node......

struct Node
{
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};

int addNode (struct Node * p, int nid, int count)
{
    path++;                                                    //count path for two times for each node......
    int i =0, ncount = count;
    for (i=0;i<count;i++)
    {
        if (p[i].nodeid == nid) { break; }
    }
    if (i == count)
    {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

void addAdjacent (struct Node *p, int nid1, int nid2, int cost, int count)
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

int added (int * list, int lcount, int nid)
{
    int i =0;
    for (i=0;i<lcount;i++)
    {
        if (list[i] == nid) { return 1; }
    }
    return 0;
}


void findpath (struct Node * p, int count, int start, int end, int * list, int *clist, int lcount)
{
    int index = 0, i=0;
   
   
    //check if list contains the end node
    if (list[lcount-1] == end)
    {
        int tcost = 0;
        for (i=0;i<lcount;i++)
        {
            //printf (" %d ", list[i]);
            tcost += clist[i];
        }
        //printf (" cost = %d", tcost);
        return;
    }
   
    for (i=0;i<count;i++)
    {
        if (p[i].nodeid == start) { index = i; break; }
    }
   
    for (i=0;i<p[index].adjcount;i++)
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


//finding all tringle

void triangle(struct Node *nodes, int total_path)
{
    for(int i=0; i<total_path; i++){
        for(int j=i+1; j<total_path; j++){
            if(Adj_list[j][0]==Adj_list[i][0])
            {
                for(int k=i+1; k<total_path; k++)
                {
                    if(Adj_list[j][1]==Adj_list[k][0])
                    {
                        if(Adj_list[k][1]==Adj_list[i][1])
                        {
                            num_tringle++;
                            printf("Tringle no.%d is: %d %d %d\n",num_tringle,Adj_list[i][0], Adj_list[i][1], Adj_list[k][0]);
                        }
                    }
                    else if(Adj_list[j][1]==Adj_list[k][1])
                    {
                        if(Adj_list[k][0]==Adj_list[i][1])
                        {
                            num_tringle++,
                            printf("Tringle no.%d is: %d %d %d\n",num_tringle,Adj_list[i][0], Adj_list[i][1], Adj_list[k][1]);
                        }
                    }
                }
            }
            else if(Adj_list[j][1]==Adj_list[i][0])
            {
                for(int k=i+1; k<total_path; k++){
                    if(Adj_list[j][0]==Adj_list[k][0])
                    {
                        if(Adj_list[k][1]==Adj_list[i][1])
                        {
                            num_tringle++;
                            printf("Tringle no.%d is: %d %d %d\n",num_tringle,Adj_list[i][0], Adj_list[i][1], Adj_list[k][0]);
                        }
                    }
                    else if(Adj_list[j][0]==Adj_list[k][1])
                    {
                        if(Adj_list[k][0]==Adj_list[i][1])
                        {
                            num_tringle++;
                            printf("Tringle no.%d is: %d %d %d\n",num_tringle,Adj_list[i][0], Adj_list[i][1], Adj_list[k][1]);
                        }
                    }
                }
            }
        }
    }
}



int main() {
   
    struct Node nodes[50];
    int nodecount = 0;
    int n1=0, n2=0, c = 0,x=0;
   
    while (1)
    {
        printf ("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c== -9) {break;}

        Adj_list[x][0]= n1;
        Adj_list[x][1]= n2;
        x++;
    
        nodecount = addNode (&nodes[0], n1, nodecount);
        nodecount = addNode (&nodes[0], n2, nodecount);
       
        addAdjacent (&nodes[0], n1, n2, c, nodecount);
        addAdjacent (&nodes[0], n2, n1, c, nodecount);
    }
   
    int start, end;
    printf ("start, end ? ");
    scanf ("%d %d", &start, &end);
    int list[50], clist[50], lcount = 0;
    list[0] = start; clist[0] = 0; lcount = 1;

    findpath (nodes, nodecount, start, end, list, clist, lcount);

    printf("\nThe tringles are : \n");

    triangle(nodes,path/2);

    //Ensuring tringle 

    if(num_tringle==0)
    {
        printf("No tringle found\n");
    }

    return 0;
}