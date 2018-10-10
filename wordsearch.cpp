class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        
        if(word.length() == 0)
            return false;
        
        //need a visited array, can also do it the other way of removing and adding back in chars,
        //but i think thats more complicated
        
        std::vector<std::vector<bool>> visited(board.size(), std::vector<bool>(board[0].size(), false));
        
        for(int i = 0; i < (int)board.size(); ++i)
        {
            for(int j = 0; j < (int)board[0].size(); ++j)
            {
                if(word[0] == board[i][j] && DFS(board, i,j,word,0, visited))
                    return true;
            }
        }
        
        
        return false;
    }
    
    bool IsInBoundsAndNotVisited(std::vector<std::vector<char>>& board, int row, int col, std::vector<std::vector<bool>>& visited)
    {
        if(row < 0 || col < 0 || row >= board.size() || col >= board[0].size() || visited[row][col] == true)
            return false;
    
        return true;
    }
    
    bool DFS(std::vector<std::vector<char>>& board, int row, int col, std::string& word, int pos, std::vector<std::vector<bool>>& visited)
    {
        //if we are at the end, we did it
        if(pos == word.length()-1)
            return true;
        
        //visit this node
        visited[row][col] = true;
        
        bool answer = false;
        
        //iterate in all four directions
        bool goNorth = IsInBoundsAndNotVisited(board, row,col+1, visited);
        bool goSouth = IsInBoundsAndNotVisited(board,row,col-1,visited);
        bool goEast = IsInBoundsAndNotVisited(board,row+1,col,visited);
        bool goWest = IsInBoundsAndNotVisited(board,row-1,col,visited);
        
        if(goNorth && word[pos+1] == board[row][col+1])
        {
            if(DFS(board,row,col+1,word,pos+1,visited))
                return true;
        }
            
        if(goSouth && word[pos+1] == board[row][col-1])
        {
            if(DFS(board,row,col-1,word,pos+1,visited))
                return true;
        }
            
      if(goEast && word[pos+1] == board[row+1][col])
      {
          if(DFS(board,row+1,col,word,pos+1,visited))
              return true;
      }  
        
     if(goWest && word[pos+1] == board[row-1][col])
     {
         if(DFS(board,row-1,col,word,pos+1,visited))
             return true;
     }
            
        //reset this square
        visited[row][col] = false;
        
        return false;
    }
};