//*************************************************************************
// TITLE : A C PROGRAMME TO FIND PATH WITH GIVEN VISA
// AUTHOR : NAHID HASAN , UNDERGRADUATE STUDENT (2ND YEAR) Of KHULNA UNIVERSITY
//*************************************************************************




#include <stdio.h>

// Flag for checking node path, PathCount for path count
int Flag[100000] = {0};
int PathCount = 0;

// Define Structure for a Node in the Graph
struct Node {
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};

// Function to add a new node to the graph
int addNode(struct Node *p, int nid, int count) {
    int i = 0;
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid) {
            break;
        }
    }
    if (i == count) {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        count++;
    }
    return count;
}

// Function to add an adjacent node to a given node in the graph
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count) {
    int i = 0;
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
int added(int *list, int lcount, int nid) {
    int i = 0;
    for (i = 0; i < lcount; i++) {
        if (list[i] == nid) {
            return 1;
        }
    }
    return 0;
}

// Recursive function to find all paths from start to end node, considering visa constraints
void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount) {
    int index = 0;
    
    // Check if list contains the end node
    if (list[lcount - 1] == end) {
        int tcost = 0, x = 1;
        // Check if all nodes in the path have the visa
        for (int i = 0; i < lcount; i++) {
            if (Flag[list[i]] == 0) {
                // If any node doesn't have the visa, set x to 0 and break
                x = 0;
                break;
            }
        }
        // If all nodes have the visa, print the path
        if (x == 1) {
            printf("\n");
            for (int i = 0; i < lcount; i++) {
                printf(" %d ", list[i]);
                tcost += clist[i];
            }
            PathCount++;
            printf(" cost = %d", tcost);
        }
        return;
    }
    
    // Find the index of the start node in the graph
    for (int i = 0; i < count; i++) {
        if (p[i].nodeid == start) {
            index = i;
            break;
        }
    }
    
    // Explore adjacent nodes
    for (int i = 0; i < p[index].adjcount; i++) {
        int a = added(list, lcount, p[index].adjs[i]);
        if (a == 0) {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;
            findpath(p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}

int main() {
    struct Node nodes[50];
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0;
    
    // Take input for node connections and their associated costs until -9 is entered
    while (1) {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c == -9) {
            break;
        }
        nodecount = addNode(&nodes[0], n1, nodecount);
        nodecount = addNode(&nodes[0], n2, nodecount);
        addAdjacent(&nodes[0], n1, n2, c, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, nodecount);
    }
    
    int start, end;
    printf("start, end ? ");
    scanf("%d %d", &start, &end);
    // Starting Node does not need any visa
    Flag[start]++; 

    // Take input for the nodes where a "visa" is present
    int visa[50];
    printf("List of visa: ");
    for (int i = 0; i < 50; i++) {
        scanf("%d", &visa[i]);
        if (visa[i] == -9) {
            break;
        }
        // Mark nodes with a visa
        Flag[visa[i]]++; 
    }

    // Take input for the nodes which do not need a visa
    int NoNeedVisa[50];
    printf("Enter the Node which do not need visa: ");
    for (int i = 0; i < 50; i++) {
        scanf("%d", &NoNeedVisa[i]);
        if (NoNeedVisa[i] == -9) {
            break;
        }
        // Mark nodes which do not need a visa
        Flag[NoNeedVisa[i]]++; 
    }
    
    int list[50], clist[50], lcount = 0;
    list[0] = start;
    clist[0] = 0;
    lcount = 1;

    // Find and print all paths from start to end node, considering visa constraints
    findpath(nodes, nodecount, start, end, list, clist, lcount);
    if (PathCount == 0) {
        printf("No path found");
    }

    return 0;
}
