   int minimumTotal(vector<vector<int>>& triangle) {
 
        // idea:
        // go from bottom to top
        // eventually return top
        // modify triangle as we go
        // start at i = size - 2;
        // then inspect row i + 1
        // j = 0 <= i
        // sum = min(i+1,j and i+1,j+1) + i,j
        // set i,j to that sum
        
        for(int i = triangle.size() - 2; i >= 0; --i) {
            
            for(int j = 0; j <= i; ++j) {
                
                int sum = std::min(triangle[i+1][j], triangle[i+1][j+1]) + triangle[i][j];
                triangle[i][j] = sum;
                
            }
            
            
        }
        
        return triangle[0][0];
    }