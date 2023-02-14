//Please make sure you use 0 based indexing vertices
#include <bits/stdc++.h>
using namespace std;

void DFS(int node, vector<int>& vis, vector<int> adj[]){
  vis[node] = 1;
  cout << node << " ";
  for(auto it : adj[node]){
    if(!vis[it])
      DFS(it,vis,adj);
  }
}

void BFS(queue<int>& q, vector<int>& vis, vector<int> adj[]){
  if(q.empty())
      return;
  int node = q.front();
  q.pop();
  cout << node << " ";
  for(auto it : adj[node]){
    if(!vis[it]){
      vis[it] = 1;
      q.push(it);
    }
  }
  
  BFS(q,vis,adj);
}

bool pathDFS(int node, int des, vector<int>& vis, vector<int> adj[]){
  vis[node] = 1;
  cout << node << " ";
  if(node == des) return true; 
  for(auto it : adj[node]){
    if(!vis[it])
        if(pathDFS(it,des,vis,adj))
          return true;
  }
  
}

void pathBFS( queue<int>& q, int des, vector<int>& vis, vector<int> adj[]){
  if(q.empty())
      return;
  int node = q.front();
  q.pop();
  cout << node << " ";
  if(node == des)  return;
  for(auto it : adj[node]){
    if(!vis[it]){
      vis[it] = 1;
      q.push(it);
    }
  }

  pathBFS(q,des,vis,adj);
}

int main() {
  /*Vertices and Edges */
  int v,e;
  cout << "Enter number of vertices : ";
  cin >> v;
  cout << "\nEnter number of edges : ";
  cin >> e;

  /* Storing edges in adjacency list */
  vector<int> adj[v];
  cout << "\nEnter edges in the form of u v, where u ---> v"<<endl;
  for(int i = 0; i < e; i++){
    int u,v;
    cout << "\nEnter edge " << i+1 << " : ";
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  /* Visites array */
  vector<int> vis(v, 0);

  /* Menu Driven Code */
  bool flag = true;
  while(flag){
    cout << "\n\n1. Overall Traversal \n2. Path Traversal \n3. Exit" << endl;
    cout << "\nEnter Your choice : ";
    int ch;
    cin >> ch;
    queue<int> q;
    switch(ch){
      case 1:
        cout << "\n\nDFS : ";
        DFS(0, vis, adj);
        // Reseting visiting array
        for(int i = 0; i < v; i++)  vis[i] = 0;
        q.push(0);
        vis[0] = 1;
        cout << "\nBFS : ";
        BFS(q,vis,adj);
        // Reseting visiting array
        for(int i = 0; i < v; i++)  vis[i] = 0;
        break;
      
      case 2:
        int src;
        cout << "\nEnter source vertex : ";
        cin >> src;
        if(src < 0 or src >= v){
          cout << "\nInvalid Source Node";
          break;
        }
        int des;
        cout << "\nEnter destination vertex : ";
        cin >> des;
        if(des < 0 or des >= v){
          cout << "\nInvalid Destination Node";
          break;
        }
        cout << "\n\nDFS : ";
        pathDFS(src,des,vis,adj);
        // Reseting visiting array
        for(int i = 0; i < v; i++)  vis[i] = 0;
        q.push(src);
        vis[src] = 1;
        cout << "\nBFS : ";
        pathBFS(q,des,vis,adj);
        // Reseting visiting array
        for(int i = 0; i < v; i++)  vis[i] = 0;
        break;

      case 3:
        flag = false;
        break;

      default:
        cout << "\nInvalid Choice, please select between 1-3"<<endl;
    
      
    }
  }
}