#include <iostream>

using namespace std ; 

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
    int countNonLeaf(TreeNode* root) {
    if (root == nullptr || (root->left == nullptr && root->right == nullptr))
        return 0;
    return 1 + countNonLeaf(root->left) + countNonLeaf(root->right);
}

int main(){
    return 0 ; 
}