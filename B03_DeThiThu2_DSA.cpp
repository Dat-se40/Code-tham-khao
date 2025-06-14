#include <iostream>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
int countNonLeaf(TreeNode* root){
    if( !root || !root->left && !root->right) return 0 ; 
    return 1 + countNonLeaf(root->left) + countNonLeaf(root->right);
}

int main()
{
    TreeNode *node4 = new TreeNode(4);
    TreeNode *node5 = new TreeNode(5);
    TreeNode *node2 = new TreeNode(2, node4, node5);
    TreeNode *node3 = new TreeNode(3);
    TreeNode *root = new TreeNode(1, node2, node3);

    int kq = countNonLeaf(root);
    cout << "So nut khong phai la: " << kq << endl;
    return 0;
}