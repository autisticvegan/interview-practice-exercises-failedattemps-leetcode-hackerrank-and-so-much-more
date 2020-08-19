    // -69 is just placeholder so we can index from 1 to 4
    std::vector<std::vector<int>> dirs = {{-69,-69},
                                           {0,1},
                                           {0,-1},
                                           {1,0},
                                            {-1,0}};
    
    bool isValid(std::vector<std::vector<int>>& g, 
                 int x, 
                 int y,
                std::vector<std::vector<int>>& dp) {
        
        return !(x < 0 || y < 0 || x >= g.size() || y >= g[0].size() || dp[x][y] != INT_MAX);
    }
    
    
    int minCost(vector<vector<int>>& grid) {
        
        int currentCost = 0;
        
        std::vector<std::vector<int>> dp(grid.size(), std::vector<int>(grid[0].size(), INT_MAX));
        
        std::queue<std::pair<int,int>> q;
        
        //explore from the first one, (recall exploring puts each one into the q)
        //it will keep exploring for valid connections.
        //inside the q loop, we will try changing the directions one at a time (for all 4 dirs)
        
        dfs(grid,0,0,dp,currentCost,q);
        
        while(!q.empty()) {
            
            ++currentCost;
            int sz = q.size();
            for(int i = 0; i < sz; ++i) {
                auto p = q.front();
                q.pop();
                for(int j = 1; j < 5; ++j) {
                    dfs(grid, p.first + dirs[j][0],
                       p.second + dirs[j][1],
                       dp,
                       currentCost,
                       q);
                }
            }
            
        }
        
        return dp[grid.size()-1][grid[0].size()-1];
        
    }
    
    
    //explore the grid, pushing spots into the q,
    //until we get to the edges or run into already calculated territory
    // for each spot, update the currentCost (remember cost is updated in main q loop)
    void dfs(std::vector<std::vector<int>>& g,
            int x,
            int y,
            std::vector<std::vector<int>>& dp,
            int currentCost,
            std::queue<std::pair<int,int>>& q) {
        
        if (!isValid(g,x,y,dp)) {
            return;
        }
        
        dp[x][y] = currentCost;
        
        q.push({x,y});
        
        int currentDir = g[x][y]; //note we have dummy value because grid values are 1 to 4
        dfs(g, x + dirs[currentDir][0], y + dirs[currentDir][1], dp, currentCost, q);
    }
};