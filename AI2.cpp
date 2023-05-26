/* RAT IN A MAZE*/
//The given solution uses 0-index grid

#include<bits/stdc++.h>
using namespace std;

int heuristic(int x, int y, int desX, int desY){
    return abs(desX-x) + abs(desY-y);
}

void astar( vector<vector<int>>& grid,int srcX,int srcY,int desX,int desY,int n,int m){
    //manhatten, distance, srcX,srcY
    priority_queue<pair<int, pair<int,pair<int,int>>>,vector<pair<int,pair<int,pair<int,int>>>>, greater<pair<int,pair<int,pair<int,int>>>>> pq;

    pq.push({0,{0,{srcX,srcY}}});
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1,-1}));
    vector<vector<int>> vis(n,vector<int>(m,0));
    vis[srcX][srcY] = 1;

    int manhatten = 0, distance = 0;
    bool flag = false;

    while(!pq.empty()){
        auto it = pq.top();
        pq.pop();

        int mdist = it.first;
        int dist = it.second.first;
        int x = it.second.second.first;
        int y = it.second.second.second;

        if(x == desX and y == desY){
            manhatten = mdist;
            distance = dist;
            flag = true;
            break;
        }

        for(int i = -1; i <= 1; i++){
            for(int j = -1; j <= 1; j++){
                if(i != 0 or j!= 0){
                    int newX = x + i;
                    int newY = y + j;

                    if(newX >= 0 and newX < n and newY >= 0 and newY < m and grid[newX][newY] == 0 and !vis[newX][newY]){
                        int tempd = heuristic(newX,newY,desX,desY);
                        pq.push({mdist+tempd,{dist+1,{newX,newY}}});
                        vis[newX][newY] = 1;
                        parent[newX][newY] = {x,y};
                    }
                }
            }
        }
    }

    if(flag){
        cout << "\n\nManhatten Distance : "<< manhatten << endl;
        cout << "Distance : "<< distance << endl;
        cout << "\nPath is : "<<endl;

        vector<pair<int,int>> path;

        int currX = desX;
        int currY = desY;

        while(currX != srcX or currY != srcY){
            path.push_back({currX,currY});
            pair<int,int> temp = parent[currX][currY];
            currX = temp.first;
            currY = temp.second;
        }
        path.push_back({srcX,srcY});

        reverse(path.begin(),path.end());

        for(auto it : path){
            cout << "(" << it.first << "," << it.second << ")" << endl;
        }
    }
    else{
        cout << "\nPath not found!!";
    }


}

int main(){
    int r,c;
    cout << "Enter number of rows in the grid : ";
    cin >> r;
    cout << "\nEnter number of columns in the grid : ";
    cin >> c;

    vector<vector<int>> grid(r, vector<int>(c,0));

    int b;
    cout << "\n\nEnter number of blocked cells in the grid : ";
    cin >> b;

    for(int i = 0; i < b; i++){
        int x,y;
        cout << "\nEnter coordinates (r,c) of the blocked cell " << i+1 << " : ";
        cin >> x >> y;
        grid[x][y] = 1;
    }

    int srcX, srcY, desX, desY;
    cout << "\n\nEnter coordinates (r,c) of the source cell : ";
    cin >> srcX >> srcY;

    cout << "\nEnter coordinates (r,c) of the destination cell : ";
    cin >> desX >> desY;

    if(grid[srcX][srcY] == 1 or grid[desX][desY] == 1)
        cout << "\n\nYou have entered a blocked as as source or destination";
    
    astar(grid,srcX,srcY,desX,desY,r,c);

    return 0;
}