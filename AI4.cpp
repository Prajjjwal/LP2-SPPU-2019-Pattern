#include<bits/stdc++.h>
using namespace std;

bool isSafe(int row, int col, vector<string> board,int n){
    int dupRow = row;
    int dupCol = col;

    while(row >= 0 and col >= 0){
        if(board[row][col] == 'Q')
            return false;
        row--;
        col--;
    }

    row = dupRow;
    col =dupCol;

    while(col >= 0){
        if(board[row][col] == 'Q')
            return false;
        col--;
    }

    row = dupRow;
    col =dupCol;

    while(row < n and col >= 0){
        if(board[row][col] == 'Q')
            return false;
        row++;
        col--;
    }

    return true;

}
void backtracking(int col, vector<string>& board, vector<vector<string>>& ans, int n){
    if(col == n){
        ans.push_back(board);
        return;
    }

    for(int row = 0; row < n; row++){
        if(isSafe(row,col,board,n)){
            board[row][col] = 'Q';
            backtracking(col+1,board,ans,n);
            board[row][col] = '.';
        }
    }
}

void branchAndBound(int col, vector<string>& board, vector<vector<string>>& ans,vector<bool>& leftRow,vector<bool>& upperDiagonal,vector<bool>& lowerDiagonal, int n){
    if(col == n){
        ans.push_back(board);
        return;
    }

    for(int row = 0; row < n; row++){
        if(leftRow[row] == false and upperDiagonal[n-1+col-row] == false and lowerDiagonal[row+col] == false){
            leftRow[row] = true;
            upperDiagonal[n-1+col-row] = true;
            lowerDiagonal[row+col] = true;
            board[row][col] = 'Q';
            branchAndBound(col+1,board,ans,leftRow,upperDiagonal,lowerDiagonal,n);
            leftRow[row] = false;
            upperDiagonal[n-1+col-row] = false;
            lowerDiagonal[row+col] = false;
            board[row][col] = '.';
        }
    }
}

int main(){
    int n;
    cout << "\nEnter size of the board : ";
    cin >> n;
    if(n > 12){
        cout << "\nSize is too big, too many possible outcomes";
        return 0;
    }

    vector<vector<string>> ans;
    vector<string> board(n);
    string s(n,'.');
    vector<bool> leftRow(n,false);
    vector<bool> upperDiagonal(2*n-1,false);
    vector<bool> lowerDiagonal(2*n-1,false);

    for(int i = 0; i < n; i++)
        board[i] = s;
    
    cout << "\n\n1. Backtracking\n2.Branch and Bound"<<endl;
    cout << "\nEnter your choice : ";
    int ch;
    cin >> ch;
    switch (ch)
    {
    case 1:
        backtracking(0,board,ans,n);
        break;
    case 2:
        branchAndBound(0,board,ans,leftRow,upperDiagonal,lowerDiagonal,n);
        break;
    default:
        cout << "Invalid choice!";
        break;
    }

    if(ans.size() == 0)
        cout << "No possible arrangements";
    else{
        for(int i = 0; i < ans.size(); i++){
            cout << "\nArrangement "<<i+1<<endl;
            for(int j = 0; j < ans[0].size(); j++){
                cout << ans[i][j];
                cout << endl;
            }
        }
    }
    return 0;
}