    int findKthPositive(vector<int>& arr, int k) {
       
        
        //binary search, formula for moving left is
        // arr[m] - 1 - m < k
        
        int left = 0;
        int right = arr.size();
        
        while (left < right) {
            
            int mid = (left + right) / 2;
            if (arr[mid] - 1 - mid < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
            
        }
       
        return k + left;
        //return k + left
    }
	
	    const static int N = 127;

    // dp[left][k] means the minimal coding size for substring 
    // s[left:] and removing at most k chars
    int dp[N][N];

    string str;
    int n;

    // get length of digit
    inline int xs(int x) { return x == 1 ? 0 : x < 10 ? 1 : x < 100 ? 2 : 3; }

    int solve(int left, int k) {
        if(k < 0) return N;  // invalid, return INF
        if(left >= n or n - left <= k) return 0;  // empty

        int& res = dp[left][k];
        if(res != -1) return res;
        res = N;

        int cnt[26] = {0};
        // we try to make s[left:j] (both inculded) as one group,
        // and all chars in this group should be the same.
        // so we must keep the most chars in this range and remove others
        // the range length is (j - left + 1)
        // and the number of chars we need to remove is (j - left + 1 - most)
        for(int j = left, most = 0; j < n; j++) {
            most = max(most, ++cnt[str[j] - 'a']);  // most = max(count(s[left:j])
            res = min(res, 1 + xs(most) + solve(j + 1, k - (j - left + 1 - most)));
        }
        return res;
    }
public:
    int getLengthOfOptimalCompression(string s, int k) {
        memset(dp, -1, sizeof(dp));
        str = s;
        n = s.size();
        return solve(0, k);
    }
	
	
	    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int max_area = 0;
        for(int i = 0; i < grid.size(); i++)
            for(int j = 0; j < grid[0].size(); j++)
                if(grid[i][j] == 1)max_area = max(max_area, AreaOfIsland(grid, i, j));
        return max_area;
    }
    
    int AreaOfIsland(vector<vector<int>>& grid, int i, int j){
        if( i >= 0 && i < grid.size() && j >= 0 && j < grid[0].size() && grid[i][j] == 1){
            grid[i][j] = 0;
            return 1 + AreaOfIsland(grid, i+1, j) + AreaOfIsland(grid, i-1, j) + AreaOfIsland(grid, i, j-1) + AreaOfIsland(grid, i, j+1);
        }
        return 0;
    }
	
	
	    bool canConvertString(string s, string t, int k) {
            if (s.size() != t.size())
        return false;
    int mul[26] = {};
    for (int i = 0; i < s.size(); ++i) {
        int shift = t[i] - s[i] + (t[i] < s[i] ? 26 : 0);
        if (shift != 0 && shift + mul[shift] * 26 > k)
            return false;
        ++mul[shift];
    }
    return true;
    }
	
	
	    int minFlips(string target) {
        //greedy approach works
        int currState = 0;
        int totalFlips = 0;
        
        for (const auto& c : target) {
            
            if (c - '0' != currState) {
                
                currState = c - '0';
                ++totalFlips;
            }
            
            
        }
        
        
        return totalFlips;
    }
	
	    int minInsertions(string s) {
        
        
        int needOnRight = 0;
        int totalNeeded = 0;
        
        for (const auto& c : s) {
            
            
            if ( c == ')') {
                
                needOnRight--;
                if (needOnRight < 0) {
                    // we need to add a left one, which means we need 2 right ones
                    totalNeeded++;
                    needOnRight += 2;
                }
                
            } else {
                // we have hit a (
                
                // if its even, we just will add 2 to the right
                // else if its odd, then we can use 1 from our running right total
                
                if (needOnRight % 2 != 0) {
                    needOnRight--;
                    totalNeeded++;
                }
                needOnRight += 2;
            }
            
        }
        
        
        
        return totalNeeded + needOnRight;
        
    }
	
	
	    int cnt = 0;
    vector<int> calcPairs(TreeNode* root, int dist)
    {
        //since this is a leaf node, return empty vector list
        if((root->left == NULL) && (root->right == NULL))
        {
            vector<int> v1;
            return v1;
        }
        
        //Left and Right to find the pairs and then to merge and send them
        vector<int> left;
        vector<int> right;
        
        //if the left node is not empty
        if(root->left)
        {
            //get the vector from the left
            left = calcPairs(root->left, dist);
            
            //if the vector from left is of size 0 then, it means we are just above a leaf node
            if(left.size()==0)
                left.push_back(1);
        }
        
        //if the right node is not empty
        if(root->right)
        {
            //get the vector from right
            right = calcPairs(root->right, dist);
            
            //if the right vectors is 0 then, it means we are just above a leaf node
            if(right.size()==0)
                    right.push_back(1);
        }
        
        //count the pairs less than or equal to the distance.
        for(int i=0; i<left.size(); i++)
        {
            for(int j=0; j<right.size(); j++)
            {
                if(left[i]+right[j]<=dist)
                    cnt++;
            }
        }
        
        //merging the vectors and increasing their height from the upcoming node.
        int i = 0;
        for(int i=0; i<left.size(); i++)
            ++left[i];
        while(i<right.size())
        {
            left.push_back(right[i]+1);
            i++;
        }
        return left;       
    }
    int countPairs(TreeNode* root, int distance) {
        vector<int> v = calcPairs(root, distance);
        return cnt;
    }
	
	    string restoreString(string s, vector<int>& indices) {
        std::string r = s;
        
        for (int i = 0; i < indices.size(); ++i) {
            r[indices[i]] = s[i];
        }
        
        return r;
    }
	
	
	    int longestAwesome(string s) {
            vector<int> dp(1024, s.size());
    int res = 0, mask = 0;
    dp[0] = -1;
    for (auto i = 0; i < s.size(); ++i) {
        mask ^= 1 << (s[i] - '0');
        res = max(res, i - dp[mask]);
        for (auto j = 0; j <= 9; ++j)
            res = max(res, i - dp[mask ^ (1 << j)]);
        dp[mask] = min(dp[mask], i);
    }
    return res;
    }
	
	
	
	