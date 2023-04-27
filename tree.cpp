#ifndef TREE_JACTGRL_CPP
#define TREE_JACTGRL_CPP

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
 
template <typename T>
struct TreeNode
{
    TreeNode<T>* left;
    TreeNode<T>* right;
    T value;
    
    TreeNode(T n_value = 0, TreeNode<T>* n_left = nullptr, TreeNode<T> *n_right = nullptr)
    : left{n_left}, right{n_right}, value{n_value} {}
    
    ~TreeNode()
    {
        delete left;
        delete right;
    }
    
    inline bool one_free_leaf()
    {
        return static_cast<bool>(left) != static_cast<bool>(right);
    }
    
};
 
template <typename T> 
class Tree
{
public:
    
    TreeNode<T>* root;
     
    Tree(TreeNode<T> *node = nullptr): root{node}
    {}
    
    template <typename lambda>
    TreeNode<T>* BFS(lambda criteria)
    {
        if(!root) return nullptr; //nullptrs should never be in the queue
        
        std::queue<TreeNode<T>*> q;
        q.push(root);
        
        while(!q.empty())
        {
            TreeNode<T>* current_node = q.front();
            q.pop();
            
            if (criteria(current_node))
                return current_node;
                
            if(current_node->left)
                q.push(current_node->left);
            if(current_node->right)
                q.push(current_node->right);
        }
        return nullptr;
    }
    
    void insert_node(TreeNode<T>* node)
    {
        TreeNode<T> *target = BFS(           \
        [](TreeNode<T> *n) -> bool           \
        {return !(n->left && n->right);} );  
        
        if(!target) {root = node; return;}
        
        if(!target->left) {target->left = node; return;}
        if(!target->right) {target->right = node; return;}
    }
    
    void insert_value(T val)
    {
        insert_node(new TreeNode<T>(val));
    }
    
};
 
template <typename T>
Tree<T> construct(std::vector<T> &arr)
{
    Tree<T> ret;
    for (T x: arr)
    {
        ret.insert_value(x);
    }
        
    return ret;
}
 

#endif //TREE_JSCTGRL_CPP
