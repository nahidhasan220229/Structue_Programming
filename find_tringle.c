//*************************************************************************
// TITLE : A C PROGRAMME TO FIND EVERY TRINGLE OF A GRAPH
// AUTHOR : NAHID HASAN , UNDERGRADUATE STUDENT (2ND YEAR) Of KHULNA UNIVERSITY
//*************************************************************************

#include <stdio.h>

int num_triangles = 0; // Counter for the number of triangles found
int path = 0; // Total number of paths in the graph
int Adj_list[100000][2]; // List to store edges in the graph

// Define Structure for a Node in the Graph
struct Node {
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};

// Function to add a new node to the graph
int addNode(struct Node *p, int nid, int count) {
    // Increment path count for each node added
    path++; 
    int i = 0, ncount = count;
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid) {
            break;
        }
    }
    if (i == count) {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

// Function to add an adjacent node to a given node in the graph
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count) {
    int i = 0, index;
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid1) {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c + 1;
            break;
        }
    }
}

// Function to check if a node is already present in a list
int isNodeAdded(int *list, int lcount, int nid) {
    int i = 0;
    for (i = 0; i < lcount; i++) {
        if (list[i] == nid) {
            return 1;
        }
    }
    return 0;
}

// Recursive function to find all paths from start to end node
void findPaths(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount) {
    int index = 0, i = 0;
   
    // Check if list contains the end node
    if (list[lcount - 1] == end) {
        int tcost = 0;
        for (i = 0; i < lcount; i++) {
            tcost += clist[i];
        }
        return;
    }
   
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == start) {
            index = i;
            break;
        }
    }
   
    for (i = 0; i < p[index].adjcount; i++) {
        int a = isNodeAdded(list, lcount, p[index].adjs[i]);
        if (a == 0) {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;
           
            findPaths(p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}

// Function to find all triangles in the graph

//In the function nexted loop running for comparing every node. And after that we can fing the number of tringle.
void findTriangles(struct Node *nodes, int total_paths) {
    for (int i = 0; i < total_paths; i++) {
        for (int j = i + 1; j < total_paths; j++) {
            if (Adj_list[j][0] == Adj_list[i][0]) {
                for (int k = i + 1; k < total_paths; k++) {
                    if (Adj_list[j][1] == Adj_list[k][0]) {
                        if (Adj_list[k][1] == Adj_list[i][1]) {
                            num_triangles++;
                            printf("Triangle no. %d: %d %d %d\n", num_triangles, Adj_list[i][0], Adj_list[i][1], Adj_list[k][0]);
                        }
                    } else if (Adj_list[j][1] == Adj_list[k][1]) {
                        if (Adj_list[k][0] == Adj_list[i][1]) {
                            num_triangles++;
                            printf("Triangle no. %d: %d %d %d\n", num_triangles, Adj_list[i][0], Adj_list[i][1], Adj_list[k][1]);
                        }
                    }
                }
            } else if (Adj_list[j][1] == Adj_list[i][0]) {
                for (int k = i + 1; k < total_paths; k++) {
                    if (Adj_list[j][0] == Adj_list[k][0]) {
                        if (Adj_list[k][1] == Adj_list[i][1]) {
                            num_triangles++;
                            printf("Triangle no. %d: %d %d %d\n", num_triangles, Adj_list[i][0], Adj_list[i][1], Adj_list[k][0]);
                        }
                    } else if (Adj_list[j][0] == Adj_list[k][1]) {
                        if (Adj_list[k][0] == Adj_list[i][1]) {
                            num_triangles++;
                            printf("Triangle no. %d: %d %d %d\n", num_triangles, Adj_list[i][0], Adj_list[i][1], Adj_list[k][1]);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    struct Node nodes[50];
    int node_count = 0;
    int n1 = 0, n2 = 0, c = 0, x = 0;
   
    // Input edges until user enters -9
    while (1) {
        printf("Enter n1, n2, cost (Enter -9 to stop): ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c == -9) {
            break;
        }

        // Store edges in Adj_list
        Adj_list[x][0] = n1;
        Adj_list[x][1] = n2;
        x++;
    
        // Add nodes and edges to the graph
        node_count = addNode(&nodes[0], n1, node_count);
        node_count = addNode(&nodes[0], n2, node_count);
        addAdjacent(&nodes[0], n1, n2, c, node_count);
        addAdjacent(&nodes[0], n2, n1, c, node_count);
    }
   
    int start, end;
    printf("Enter start and end nodes: ");
    scanf("%d %d", &start, &end);

    int list[50], clist[50], lcount = 0;
    list[0] = start; 
    clist[0] = 0; 
    lcount = 1;

    // Find paths from start to end node
    findPaths(nodes, node_count, start, end, list, clist, lcount);

    printf("\nTriangles in the graph:\n");

    // Find and print triangles in the graph
    findTriangles(nodes, path / 2);

    // If no triangles are found, print a message
    if (num_triangles == 0) {
        printf("No triangles found.\n");
    }

    return 0;
}
