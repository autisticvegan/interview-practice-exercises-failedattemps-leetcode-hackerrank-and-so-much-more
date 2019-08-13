class Solution {
public:
    int maxRepOpt1(string text) {

        // go through, and record teh indices of each
        // occurrence of letter.
        // then for each letter, 
        // step through the index vector
        // if we are 1 or 2 off (as in:
        // [i] == [i-1] + 1 or + 2)
        // then 
       std::map<char, std::vector<int>> letter2Indices;
        int i = 0;
        for(const auto& c : text) {
            letter2Indices[c].push_back(i);
            ++i;
        }
        int res = 0;
        for(const auto& p : letter2Indices) {

            if(p.second.size() == 0) {
                continue;
            }
            
        int count = 1;
        int count2 = 0;
        int max = 0;
            
            for(int i = 1; i < p.second.size(); ++i) {
                // if its 1 or 2 off then update counts
                if(p.second[i] == p.second[i-1] + 1) {
                    ++count;
                } else {
                    count2 = (p.second[i] == p.second[i-1] + 2) ?
                        count : 0;
                    count = 1;
                }
                
                max = std::max(max, count + count2);
            }
            
            int possibleExtra = p.second.size() > max ? 1 : 0;
            res = std::max(res, max + possibleExtra);
        }
        return res;
    }
};

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() {}

    Node(int _val, Node* _left, Node* _right, Node* _next) {
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
};
*/
class Solution {
public:
    //can also use level traversal
    //instead of printing, take next and set it to next
    
    Node* connect(Node* root) {
    Node* previous = root;
    Node* curr = nullptr;
        if(!root) {
            return root;
        }
        
        while(previous->left) {
           curr = previous;
            
            while(curr) {
                curr->left->next = curr->right;
                if(curr->next) {
                    curr->right->next = curr->next->left;
                }
                curr = curr->next;
            }
            
            
            previous = previous->left;
        }
        
        return root;
        
    }
};

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int H) {
      //binary search between max (10^9) and p.length
    // also similar to min gas station distance
        int l = 1;
        int r = 1000000000;
        
        while(l < r) {
            long mid = l + (r - l)/2;
            int total = 0;
            for(const auto& p : piles) {
                total += (p + mid - 1) / mid;
            }
            if(total > H) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        
        return l;
                  
        
    }
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        
        if(!root->left)
            return -1;
        
        int leftSide = root->val == root->left->val ? findSecondMinimumValue(root->left) : root->left->val;
        int rightSide = root->val == root->right->val ? findSecondMinimumValue(root->right) : root->right->val;
        
        if(leftSide == -1 || rightSide == -1) {
            return std::max(leftSide, rightSide);
        }
        
        return std::min(leftSide, rightSide);
    }
};

class Solution {
    vector<TreeNode*> nodes;

public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (!s && !t) return true;
        if (!s || !t) return false;

        getDepth(s, getDepth(t, -1));

        for (TreeNode* n: nodes)
            if (identical(n, t))
                return true;

        return false;
    }

    int getDepth(TreeNode* r, int d) {
        if (!r)
            return -1;

        int depth = max(getDepth(r->left, d), getDepth(r->right, d)) + 1;

        // Check if depth equals required value
        // Require depth is -1 for tree t (only return the depth, no push)
        if (depth == d)
            nodes.push_back(r);

        return depth;
    }

    bool identical(TreeNode* a, TreeNode* b) {
        if (!a && !b) return true;
        if (!a || !b || a->val != b->val) return false;

        return identical(a->left, b->left) && identical(a->right, b->right);
    }
};

class Solution {
public:
    vector<int> addToArrayForm(vector<int>& A, int K) {
        
        for(int i = A.size()-1; i >= 0 && K > 0; --i) {
            A[i] += K;
            K = A[i] / 10;
            A[i] %= 10;
        }
        std::reverse(A.begin(), A.end());
        while(K > 0) {
            A.push_back(K % 10);
            K /= 10;
        }
        std::reverse(A.begin(), A.end());
        return A;
    }
};

class Solution {
public:
    int findLHS(vector<int>& nums) {
        std::unordered_map<int, int> num2Count;
        int res = 0;
        for(const auto& i : nums) {
            num2Count[i]++;
            if(num2Count.count(i+1)) {
                res = std::max(res, num2Count[i] + num2Count[i+1]);
            }
            if(num2Count.count(i-1)) {
                res = std::max(res, num2Count[i] + num2Count[i-1]);
            }
        }
        return res;
    }
};

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {

        double res = INT_MIN;
        double curr = 0;
        for(int i = 0; i < nums.size(); ++i) {
            if(i < k) {
               curr += nums[i];
            } else {
               
                res = std::max(res, curr);
                 curr += nums[i];
                curr -= nums[i-k];
            }
            
        }
        res = std::max(res, curr);
        return res / k;
    }
};

class Solution {
public:
    int dayOfYear(string date) {
        //if year is % 4 == 0.  then feb has 29 days.
        
        std::unordered_map<int,int> month2Days;
        month2Days[1] = 31;
        month2Days[2] = 28;
        month2Days[3] = 31;
        month2Days[4] = 30;
        month2Days[5] = 31;
        month2Days[6] = 30;
                month2Days[7] = 31;
                month2Days[8] = 31;
                month2Days[9] = 30;
                month2Days[10] = 31;
                month2Days[11] = 30;
                month2Days[12] = 31;
        
        std::stringstream d(date);
        std::vector<int> tokens;
        std::string temp;
        
        while(std::getline(d, temp, '-')) {
            tokens.push_back(std::stoi(temp));
        }
        
        if(tokens[0] % 4 == 0 && tokens[0] != 1900) {
            month2Days[2]++;
        }

       // for(const auto& t : tokens) {
      //      std::cout << t << std::endl;
     //   }
        
        int total = 0;
        for(int i = 0; i < tokens[1] - 1; ++i) {
            total += month2Days[i+1];
        }

        total += tokens[2];
        return total;
    }
};

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        
        int total = 0;
        for(const auto& i : nums) {
            total += i;
        }
        
        int leftSum = 0;
        
        for(int i = 0; i < nums.size(); ++i) {
        
            leftSum += nums[i];

            if(total == leftSum) {
                return i;
            }
            total -= nums[i];
        }
        
        return -1;
    }
};