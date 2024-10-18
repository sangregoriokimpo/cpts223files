

#include <iostream>
#include <limits>
#include <vector>
using namespace std;


template <typename Comparable>
class AVLTree
{
public:
    AVLTree();
    ~AVLTree();

    void makeEmpty();
    const Comparable & findMin() const;
    const Comparable & findMax() const;

    bool contains(const Comparable & x) const;// DONE
    void insert(const Comparable & x);// DONE
    void remove(const Comparable & x);// DONE
    int treeSize() const; // DONE
    int computeHeight() const;// DONE
    int readRootHeight() const;// DONE
    bool isBalanced() const;// DONE
    bool isBST() const;// DONE



    double averageDepth() const;// DONE
    void removeByRank(int rank);// DONE

    // the next line follows textbook Figure 4.42, Line 19
    static const int ALLOWED_IMBALANCE = 1;
private:
    struct AVLNode  // refer to textbook, Figure 4.40
    {
        Comparable element;
        AVLNode *left;
        AVLNode *right;
        int height;

        AVLNode( const Comparable & theElement, AVLNode *lt, AVLNode *rt ): element(theElement), left(lt), right(rt) {}
        AVLNode( Comparable && theElement, AVLNode *lt, AVLNode *rt ): element(move(theElement)), left(lt), right(rt) {}
    };

    AVLNode *root;

    AVLNode * findMin( AVLNode * t ) const;
    AVLNode * findMax( AVLNode * t ) const;
    void makeEmpty( AVLNode * & t );

    void balance(AVLNode * & t);
    void rotateWithLeftChild( AVLNode * & t );// DONE
    void rotateWithRightChild( AVLNode * & t );// DONE
    void doubleWithLeftChild( AVLNode * & t);// DONE
    void doubleWithRightChild( AVLNode * & t);// DONE

    AVLNode* insertHelper(const Comparable &x , AVLNode *node);

    int getBalance(AVLNode *node);

    int height(AVLNode *node);

    int height(AVLNode *node) const;

    void destroyTree(AVLNode *node);

    AVLNode* removeHelper(const Comparable &x, AVLNode *node);

    bool isBSTHelper(AVLNode *node, const Comparable &min,const Comparable &max) const;

    bool isBalancedHelper(AVLNode *node) const;

    int computeHeightHelper(AVLNode *node) const;

    int treeSizeHelper(AVLNode *node) const;

    void totalDepthFunction(AVLNode *node,int depth, int &totalDepth, int &totalNodes) const;

    double averageDepthHelper(AVLNode *node) const;

    AVLNode* removeByRankHelper(AVLNode *node,int rank);

    bool containsHelper(const Comparable &x, AVLNode *node) const;
};

template<typename Comparable>
bool AVLTree<Comparable>::containsHelper(const Comparable &x, AVLTree::AVLNode *node) const {
    if(node == nullptr){
        return false;
    }
    if(x < node->element){
        return containsHelper(x,node->left);
    }else if(x > node->element){
        return containsHelper(x,node->right);
    }else{
        return true;
    }
}

template<typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::removeByRankHelper(AVLTree::AVLNode *node, int rank) {
    if(node == nullptr){
        return nullptr;
    }

    int ls = treeSizeHelper(node->left);
    int nr = ls +1;
    if(rank == nr){
        if(node->left == nullptr || node->right == nullptr){
            AVLNode *temp = node->left ? node->left : node->right;
            if(temp == nullptr){
                delete node;
                return nullptr;
            }else{
                delete node;
                return temp;
            }
        }else{
            AVLNode *temp = findMin(node->right);
            node->element = temp->element;
            node->right = removeByRankHelper(node->right,1);
        }
    }else if(rank < nr){
        node->left = removeByRankHelper(node->left,rank);
    }else{
        int newRank = rank - nr;
        node->right = removeByRankHelper(node->right,newRank);
    }

    balance(node);

    return node;

}

template<typename Comparable>
double AVLTree<Comparable>::averageDepthHelper(AVLTree::AVLNode *node) const{
    int td = 0;
    int tn = 0;
    totalDepthFunction(root,0,td,tn);
    if(tn == 0){
        return 0.0;
    }
    return static_cast<double>(td) / tn;
}

template<typename Comparable>
void AVLTree<Comparable>::totalDepthFunction(AVLTree::AVLNode *node, int depth, int &totalDepth, int &totalNodes) const{
    if(node == nullptr){
        return;
    }

    totalDepth += depth;
    totalNodes += 1;

    totalDepthFunction(node->left,depth + 1, totalDepth, totalNodes);
    totalDepthFunction(node->right,depth + 1, totalDepth, totalNodes);
}

template<typename Comparable>
int AVLTree<Comparable>::treeSizeHelper(AVLTree::AVLNode *node) const{
    if(node == nullptr){
        return 0;
    }
    int ls = treeSizeHelper(node->left);
    int rs = treeSizeHelper(node->right);

    return 1 + ls + rs;
}

template<typename Comparable>
int AVLTree<Comparable>::computeHeightHelper(AVLTree::AVLNode *node) const {
    if(node == nullptr){
        return 0;
    }
    int lh = computeHeightHelper(node->left);
    int rh = computeHeightHelper(node->right);
    return 1 + std::max(lh,rh);
}

template<typename Comparable>
int AVLTree<Comparable>::height(AVLTree::AVLNode *node) const {
    if(node == nullptr){
        return 0;
    }
    return node->height;
}

template<typename Comparable>
bool AVLTree<Comparable>::isBalancedHelper(AVLTree::AVLNode *node) const {
    if(node == nullptr){
        return true;
    }
    int lh = height(node->left);
    int rh =  height(node->right);

    if(abs(lh - rh) > ALLOWED_IMBALANCE){
        return false;
    }

    return isBalancedHelper(node->left) && isBalancedHelper(node->right);

}

template<typename Comparable>
bool AVLTree<Comparable>::isBSTHelper(AVLTree::AVLNode *node, const Comparable &min, const Comparable &max) const {
    if(node == nullptr){
        return true;
    }
    if(node->element <= min || node->element >= max){
        return false;
    }

    return isBSTHelper(node->left, min, node->element) &&
           isBSTHelper(node->right, node->element, max);
}

template<typename Comparable>
typename AVLTree<Comparable>::AVLNode *AVLTree<Comparable>::removeHelper(const Comparable &x, typename AVLTree<Comparable>::AVLNode *node) {
    if(node == nullptr){
        return nullptr;
    }

    if(x < node->element){
        node->left = removeHelper(x,node->left);
    }else if(x > node->element){
        node->right = removeHelper(x,node->right);
    }else{
       if(node->left == nullptr || node->right == nullptr){
           AVLNode *temp = node->left ? node->left : node->right;
           if(temp == nullptr){
               temp = node;
               node = nullptr;
           }else{
               node = temp;
           }
           delete temp;
       }else{
           AVLNode *temp = findMin(node->right);
           node->element = temp->element;
           node->right = removeHelper(temp->element,node->right);
       }
    }

    return node;
}



template<typename Comparable>
void AVLTree<Comparable>::destroyTree(AVLNode *node) {
    if(root != nullptr){
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

template<typename Comparable>
int AVLTree<Comparable>::height(AVLTree::AVLNode *node) {
    if(node == nullptr){
        return 0;
    }
    return node->height;
}

template<typename Comparable>
int AVLTree<Comparable>::getBalance(AVLTree::AVLNode *node) {
    if(node == nullptr){
        return 0;
    }
    return height(node->left) - height(node->right);
}

template<typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::insertHelper(const Comparable &x, AVLTree::AVLNode *node) {
    if(node == nullptr){
        return new AVLNode(x, nullptr, nullptr);
    }
    if(x < node->element){
        //node->left = insertHelper(node->left,x);
        node->left = insertHelper(x,node->left);
    }else if(x > node->element){
        //node->right = insertHelper(node->right,x);
        node->right = insertHelper(x,node->right);
    }else{
        return node;
    }

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balanceFactor = getBalance(node);


    if (balanceFactor > 1 && node->left != nullptr && x < node->left->element) {
        rotateWithLeftChild(node);
    }


    if (balanceFactor < -1 && node->right != nullptr && x > node->right->element) {
        rotateWithRightChild(node);
    }


    if (balanceFactor > 1 && node->left != nullptr && x > node->left->element) {
        rotateWithRightChild(node->left);
        rotateWithLeftChild(node);
    }

    if (balanceFactor < -1 && node->right != nullptr && x < node->right->element) {
        rotateWithLeftChild(node->right);
        rotateWithRightChild(node);
    }

    return node;

}

// constructor
template <class Comparable>
AVLTree<Comparable>::AVLTree() : root(NULL) {}

// destructor
template <class Comparable>
AVLTree<Comparable>::~AVLTree()
{
    makeEmpty();
}

// public makeEmpty: follow the makeEmpty in BST, referring to textbook, Figure 4.27
template <typename Comparable>
void AVLTree<Comparable>::makeEmpty() {
    makeEmpty(root);
}

// private recursive makeEmpty: follow the makeEmpty in BST, referring to textbook, Figure 4.27
template <typename Comparable>
void AVLTree<Comparable>::makeEmpty(AVLNode * & t) {
    if ( t != NULL ) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = NULL;
    }
}

// public findMin: follow the findMin in BST, referring to textbook, Figure 4.20
template <typename Comparable>
const Comparable & AVLTree<Comparable>::findMin() const {
    if (root == NULL) {
        throw underflow_error("Tree is empty");
    }
    return findMin(root)->element;
}

// private findMin: follow the findMin in BST, referring to textbook, Figure 4.20
template <typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::findMin(AVLNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->left == NULL) {
        return t;
    } else {
        return findMin(t->left);
    }
}

// public findMax: follow the findMax in BST, referring to textbook, Figure 4.21
template <typename Comparable>
const Comparable & AVLTree<Comparable>::findMax() const {
    if (root == NULL) {
        throw underflow_error("Tree is empty");
    }
    return findMax(root)->element;
}

// private findMax: follow the findMax in BST, referring to textbook, Figure 4.21
template <typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::findMax(AVLNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->right == NULL) {
        return t;
    } else {
        return findMax(t->right);
    }
}

// start our implementation:
// public contains: follow the contains in BST, referring to textbook, Figure 4.17 and Figure 4.18
template<typename Comparable>
bool AVLTree<Comparable>::contains( const Comparable & x ) const {
    return containsHelper(x,root);
}

// public insert: following BST, referring to textbook, Figure 4.17 and Figure 4.23
template<typename Comparable>
void AVLTree<Comparable>::insert(const Comparable & x) {
   root = insertHelper(x,root);
}

// public remove: refer to textbook, Figure 4.17 and Figure 4.26
template<typename Comparable>
void AVLTree<Comparable>::remove( const Comparable & x ) {
    root = removeHelper(x,root);
}

// private balance: refer to textbook, Figure 4.42, Line 21 - 40
// assume t is the node that violates the AVL condition, and we then identify which case to use (out of 4 cases)
template<typename Comparable>
void AVLTree<Comparable>::balance(AVLNode * & t) {
    t->height = 1+ std::max(height(t->left),height(t->right));
    int balanceFactor = getBalance(t);
    if(balanceFactor > 1){
        if(height(t->left->left) >=height(t->left->right)){
            rotateWithLeftChild(t);
        }else{
            rotateWithRightChild(t->left);
            rotateWithLeftChild(t);
        }
    }

    else if(balanceFactor < -1){
        if(height(t->right->right) >= height(t->right->left)){
            rotateWithRightChild(t);
        }else{
            rotateWithLeftChild(t->right);
            rotateWithRightChild(t);
        }
    }
}

// private rotateWithLeftChild: for case 1, referring to textbook, Figure 4.44 (code) and Figure 4.43 (visualization)
template<typename Comparable>
void AVLTree<Comparable>::rotateWithLeftChild(AVLNode * & k2) {
    if(k2->left == nullptr){
        return;
    }
    AVLNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = 1 + std::max(height(k2->left),height(k2->right));
    k1->height = 1 + std::max(height(k1->left),height(k1->right));
    k2 = k1;

}

// private rotateWithRightChild: for case 4 (the mirrored case of case 1)
template<typename Comparable>
void AVLTree<Comparable>::rotateWithRightChild(AVLNode * & k2) {
    if(k2->right == nullptr){
        return;
    }

    AVLNode *k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;

    k2->height = 1 + std::max(height(k2->left),height(k2->right));
    k1->height = 1 + std::max(height(k1->left),height(k1->right));
    k2 = k1;

}

// private doubleWithLeftChild: for case 2, see textbook, Figure 4.46 (code) and Figure 4.45 (visualization)
template<typename Comparable>
void AVLTree<Comparable>::doubleWithLeftChild(AVLNode * & k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

// private doubleWithRightChild: for case 3 (the mirrored case of case 2)
template<typename Comparable>
void AVLTree<Comparable>::doubleWithRightChild(AVLNode * & k3) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}

// public isBalanced
template <class Comparable>
bool AVLTree<Comparable>::isBalanced() const {
    return isBalancedHelper(root);
}

// public isBST
template <class Comparable>
bool AVLTree<Comparable>::isBST() const {
    return isBSTHelper(root,std::numeric_limits<Comparable>::lowest(), std::numeric_limits<Comparable>::max());
}

// public treeSize
template <typename Comparable>
int AVLTree<Comparable>::treeSize() const {
    return treeSizeHelper(root);
}

// public computeHeight. See Figure 4.61 in Textbook
template <typename Comparable>
int AVLTree<Comparable>::computeHeight() const {
    return computeHeightHelper(root);
}

// public readRootHeight
template <typename Comparable>
int AVLTree<Comparable>::readRootHeight() const {
    return root->height;
}

// public averageDepth
template <typename Comparable>
double AVLTree<Comparable>::averageDepth() const {
    return averageDepthHelper(root);
}

// public removeByRank
template <typename Comparable>
void AVLTree<Comparable>::removeByRank(int rank) {
    root = removeByRankHelper(root,rank);
}

