/*
* C++ Program to Implement Adjacency List
 */
#include "cstdlib.h"
using namespace std;

/*
 * Adjacency List Node
 */
struct AdjListNode
{
  unsigned int dest;  //coordinate; the label of the node
  unsigned int significance;   //0 or accessible, 1 for hopper, 2 for gameboard, 3 for starting point, 4 for walls, 5 for hopper stopping point : note that numbering also indicate priority
  struct AdjListNode* next;
};

/*
 * Adjacency List
 */
struct AdjList
{
  struct AdjListNode *head;
};

/*
 * Class Graph
 */
class Graph
{
private:
  int V;  // number of nodes
  struct AdjList* array;
public:
  Graph(int V)
  {
    this->V = V;
    array = new AdjList [V];
    for (int i = 0; i < V; ++i)
      array[i].head = NULL;
  }
  /*
         * Creating New Adjacency List Node
   */
  AdjListNode* newAdjListNode(unsigned int dest, unsigned int significance)
  {
    AdjListNode* newNode = new AdjListNode;
    newNode->dest = dest;
    newNode->next = NULL;
    newNode->significance = significance;
    return newNode;
  }
  /*
         * Adding Edge to Graph
   */
  void addEdge(unsigned int src, unsigned int S2, unsigned int dest, unsigned int S1)
  {
    AdjListNode* newNode = newAdjListNode(dest, S1);
    newNode->next = array[src].head;
    array[src].head = newNode;
    newNode = newAdjListNode(src, S2);
    newNode->next = array[dest].head;
    array[dest].head = newNode;
  }
}; 

void buildList()
{
  Graph gh(90);
  // hopper region
  for (unsigned int i = 0; i < 30;i = i+10)
  {
     for (unsigned int j = 32; j < 36; j++) 
     {
       addEdge( j+ i,1, j + i + 1, 1);  //horizontal edges
       addEdge( j + i, 1, j + i +10, 1);  //vertical edges
     }
  }
  // edge between hopper and path
  for (unsigned int k = 0; k < 5; k++)
  {
    //bottom of hopper region
    addEdge(22 + k, 0, 23 + k, 0);  //horizontal
    addEdge(22 + k, 0, 32 + k, 1);  //vertical
    //top of hopper region
    addEdge(62 + k, 1, 63 + k, 1);  //horizontal
    addEdge(62 + k, 1, 72 + k, 0);   //vertical
  }
  for (unsigned int k = 0; k < 30; k = k + 10)  
  {
    //right side of hopper region
    addEdge(36 + k, 1, 46 + k, 1);  //vertical
    addEdge(36 + k, 1, 37 + k, 0);  //horizontal
  }
  for (unsigned int k = 0; k < 40; k = k + 10)
  {
    //left side of hopper region
    addEdge(31 + k, 0, 41 + k, 0);  //vertical
    addEdge(31 + k, 0, 32 + k, 1);  //horizontal
  }
  // remaining vertices: 21
    addEdge(21, 0, 22, 0);
    addEdge(21, 0, 31, 0);  
  //remaining pathways
    addEdge(71, 0, 72, 0);
    addEdge(71, 0, 81, 0);
    addEdge(77, 0, 78, 0);
    addEdge(77, 0, 87, 0);
    addEdge(27, 0, 28, 0);
    addEdge(27, 0, 37, 0);
  
  //Walls 
  for (unsigned int i = 1; i < 8; i++)
  {
    // bottom wall
    void addEdge (i, 4, i + 1, 4);   // horizontal
    void addEdge (i, 4, i + 10, 0);  // vertical 
    // left wall
    void addEdge (i * 10, 4, 10 + i * 10, 4);
    void addEdge (i * 10, 4, 1 + i * 10, 0);
  }
  for (unsigned int j = 0; j < 8; j++)
  {
    //top wall
    void addEdge(90 + j, 4, 91 + j, 4);
    //right side wall
    void addEdge( 8 + 10 * j, 4, 18 + 10 * j, 4);
  }
  void addEdge (0, 4, 1, 4);
  void addEdge (0, 4, 10, 4);
  

  //the rest of the path (significance == 0)
 
  for (unsigned int m = 1; l < 7; l++)
  {
    // 11 to 16
     void addEdge(10 + j, 0, 11 + j, 0);  //horizontal
      void addEdge(10 + j, 0, 20 + j, 0);  //vertical
     // 71 to 76
      void addEdge(70 + j, 0, 71 + j, 0);  //horizontal
       void addEdge(70 + j, 0, 80 + j, 0);  //vertical
     // 81 to 86
      void addEdge(80 + j, 0, 81 + j, 0);  //horizontal
      void addEdge(80 + j, 0, 90 + j, 4);  //vertical
  }
  // 17 - 77 column
  for (unsigned int n = 10; n < 80; n = n + 10)
  {
       void addEdge(7 + j, 0, 17 + j, 0);  //vertical
        void addEdge(7 + j, 0, 8 + j, 4);  //horizontal
  }
  
  //87
   void addEdge(87, 0, 88, 4);  //hor
   void addEdge(87, 0, 97, 4);  //ver
}


