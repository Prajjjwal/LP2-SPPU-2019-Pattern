/*PRIM'S ALGORITHM*/

//Please make sure you use 0 based indexing vertices
#include<bits/stdc++.h>
using namespace std;

void printMST(vector<pair<int,int>> adj[], int v){
    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq; //Stores {weight,{adjacentNode,parentNode}}

    vector<int> vis(v); // Visited array
    vector<vector<int>> path; //To store and print MST
    int cost = 0;
    pq.push({0,{0,-1}});

    while(!pq.empty()){
        auto it = pq.top();
        pq.pop();

        int wt = it.first;
        int node = it.second.first;
        int parent = it.second.second;

        if(vis[node]) continue;
        vis[node] = 1;
        if(parent != -1){
            vector<int> tmp(3);
            tmp[0] = parent;
            tmp[1] = node;
            tmp[2] = wt;
            cost += wt;
            path.push_back(tmp);
        }

        for(auto it : adj[node]){
            int adjNode = it.first;
            int weight = it.second;
            if(!vis[adjNode]){
                pq.push({weight,{adjNode,node}});
            }
        }
    }

    cout << "\n\nMINIMUM SPANNING TREE USING PRIM'S ALGORITHM"<<endl<<endl;
    cout << "u ------ wt ------> v"<<endl;
    for(auto it : path){
        cout <<"\n" <<it[0] << " ------ " << it[2] << " ------> " << it[1];
    }
    cout << "\n\nCost : " << cost<<endl;
}

int main(){
    cout << "\nENTER 0-BASED VERTEX TREE"<<endl;
    int v,e;
    cout << "\nEnter number of vertices : ";
    cin >> v;
    cout << "\nEnter number of edges : ";
    cin >> e;

    vector<pair<int,int>> adj[v];

    cout << "\n\nEnter edges in the form of u v w, where u---w--->v"<<endl; // u = start point of edge, v = end point of edge, w = weight of the egde
    
    for(int i = 0; i < e; i++){
        int u,v,w;
        cout << "\nEnter edge "<<i+1<<" : ";
        cin  >> u >> v >> w;

        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    printMST(adj,v);

    return 0;
}