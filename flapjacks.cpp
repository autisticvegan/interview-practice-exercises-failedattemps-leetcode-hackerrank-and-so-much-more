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
    int maxLevelSum(TreeNode* root) {
        
        
        std::queue<TreeNode*> q;
        q.push(root);
        
        int finalLevel = 1;
        int level = 0;
        int sum = INT_MIN;
        while(!q.empty()) {
            ++level;
            
            int iterations = q.size();
            int sumNew = 0;
            for(int i = 0; i < iterations; ++i) {
                
                TreeNode* t = q.front();
                q.pop();
                
                sumNew += t->val;
                
                if(t->left) {
                    q.push(t->left);
                }
                
                if(t->right) {
                    q.push(t->right);
                }
            }
            
            if(sumNew > sum) {
                sum = sumNew;
                finalLevel = level;
            }
        }
        
        return finalLevel;
        
    }
};