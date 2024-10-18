#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
#include <vector>
#include <queue>
using namespace std;


/* ----------------------------------------------------------------------------
---- Below is declaration of BST class, referring to textbook, Figure 4.16 ----
---------------------------------------------------------------------------- */

template <typename Comparable>
class BST
{
public:
	BST();
	~BST();
	void makeEmpty();

	const Comparable & findMin() const;
	const Comparable & findMax() const;

	bool contains(const Comparable & x) const;
	void insert(const Comparable & x);
	void remove(const Comparable & x);
	int treeSize() const;
	int treeHeight() const;
	void printInOrder() const;
	void printLevels() const;
	void printMaxPath() const;

private:




	struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt): element(theElement), left(lt), right(rt) {}
		BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt): element(move(theElement)), left(lt), right(rt) {}
        explicit BinaryNode(const Comparable & theElement);
        explicit BinaryNode(Comparable && theElement);
	};

    class queue{
    private:
        struct queueNode{
            BinaryNode *bn;
            queueNode *next;
            queueNode(BinaryNode *t) : bn(t),next(nullptr){};

        };

        queueNode *f;
        queueNode *r;



    private:
        int size;
    public:
        int getSize() const {
            return size;
        }

        queueNode *getF() const {
            return f;
        }

        queueNode *getR() const {
            return r;
        }


        queue() : f(nullptr),r(nullptr),size(0){};

        ~queue(){
            while(!isEmpty()){
                dequeue();
            }
        }

        [[nodiscard]] bool isEmpty() const{
            return f == nullptr;
        }

        void enqueue(BinaryNode *t){
            auto *n = new queueNode(t);
            if(isEmpty()){
                r = n;
                f = n;
            }else{
                r->next = n;
                r = n;
            }
            size++;
        }

        BinaryNode * dequeue(){
            if(isEmpty()){
                return nullptr;
            }
            queueNode *tp = f;
            BinaryNode *n = f->bn;
            f = f->next;
            delete tp;
            if(f == nullptr){
                r = nullptr;
            }
            size--;
            return n;
        }

    };

	BinaryNode *root;

	BinaryNode * findMin( BinaryNode * t ) const;
	BinaryNode * findMax( BinaryNode * t ) const;
	void makeEmpty( BinaryNode * & t );

    void printInOrderUtil(BinaryNode *t) const;
    //typename removeUtil(BinaryNode *t, const Comparable & x);
    BinaryNode * removeUtil(BinaryNode *t, const Comparable & x);
    int treeSizeUtil(BinaryNode *t) const;
    int treeHeightUtil(BinaryNode *t) const;
    void printMaxPathUtil(BinaryNode *t) const;
    bool containsUtil(BinaryNode *t,const Comparable & x) const;

    [[nodiscard]] int max(int lh, int rh) const;
};

template<typename Comparable>
bool BST<Comparable>::containsUtil(BST::BinaryNode *t, const Comparable &x) const {
    if(t == nullptr){
        return false;
    }
    if(t->element == x){
        return true;
    }


    if(t->element < x){
        return containsUtil(t->right,x);
    }

    return containsUtil(t->left,x);
}

template<typename Comparable>
void BST<Comparable>::printMaxPathUtil(BST::BinaryNode *t) const {
    if(t == nullptr){
        return;
    }

    cout << t->element << " -> ";

    if(t->left == nullptr && t->right == nullptr){
        return;
    }

    int lh = treeHeightUtil(t->left);
    int rh = treeHeightUtil(t->right);

    if(lh > rh ){
        printMaxPathUtil(t->left);
    }else{
        printMaxPathUtil(t->right);
    }
}

template<typename Comparable>
int BST<Comparable>::max(int lh, int rh) const {
    if(lh > rh){
        return lh;
    }else{
        return rh;
    }
}


template<typename Comparable>
int BST<Comparable>::treeHeightUtil(BST::BinaryNode *t) const{
    if(t == nullptr){
        return -1;
    }
    int lh= 0;
    int rh = 0;
    lh = treeHeightUtil(t->left);
    rh = treeHeightUtil(t->right);
    return 1 + max(lh,rh);
}

template<typename Comparable>
int BST<Comparable>::treeSizeUtil(BST::BinaryNode *t) const{
    if(t == nullptr){
        return 0;
    }
    int ls = 0;
    int rs = 0;
    rs = treeSizeUtil(t->left);
    ls = treeSizeUtil(t->right);
    return ls + rs + 1;
}

template<typename Comparable>
typename BST<Comparable>::BinaryNode *BST<Comparable>::removeUtil(BST::BinaryNode *t, const Comparable &x) {
    if(t == nullptr){
        return nullptr;
    }
    if(x < t->element){
        t->left = removeUtil(t->left,x);
    }else if(x > t->element){
        t->right = removeUtil(t->right,x);
    }else{
        if(t->left == nullptr && t->right == nullptr){
            delete t;
            return nullptr;
        }
        if(t->left == nullptr){
            BinaryNode * tp = t->right;
            delete t;
            return tp;
        }
        if(t->right == nullptr){
            BinaryNode *tp = t->left;
            delete t;
            return tp;
        }

        BinaryNode *mn = findMin(t->right);
        t->element = mn->element;
        t->right = removeUtil(t->right,mn->element);
    }
    return t;


}





template<typename Comparable>
void BST<Comparable>::printInOrderUtil(BST::BinaryNode *t) const {
    if(t == nullptr){
        return;
    }else{
        printInOrderUtil(t->left);
        cout << t->element << " -> ";
        printInOrderUtil(t->right);
    }
}


template<typename Comparable>
BST<Comparable>::BinaryNode::BinaryNode(Comparable &&theElement): element(std::move(theElement)),left(nullptr),right(
        nullptr) {
//    element = theElement;
//    left = nullptr;
//    right = nullptr;
}

template<typename Comparable>
BST<Comparable>::BinaryNode::BinaryNode(const Comparable &theElement): element(std::move(theElement)),left(nullptr),right(
        nullptr) {
//    element = theElement;
//    left = nullptr;
//    right = nullptr;

}


/* --------------------------------------------------------------
---- Below is implementation of public and private functions ----
-------------------------------------------------------------- */

// constructor
template<typename Comparable>
BST<Comparable>::BST() : root(NULL) {}

// destructor, refer to textbook, Figure 4.27
template<typename Comparable>
BST<Comparable>::~BST() {
	makeEmpty();
}

// public makeEmpty: refer to textbook, Figure 4.27
template <typename Comparable>
void BST<Comparable>::makeEmpty() {
    makeEmpty(root);
}

// private recursive makeEmpty: refer to textbook, Figure 4.27
template <typename Comparable>
void BST<Comparable>::makeEmpty(BinaryNode *& t) {
    if ( t != NULL ) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = NULL;
    }
}

// // public findMin
template <typename Comparable>
const Comparable & BST<Comparable>::findMin() const {
    if (root == NULL) {
    	throw underflow_error("Tree is empty");
	}
    return findMin(root)->element;
}

// private findMin: refer to textbook, Figure 4.20
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMin(BinaryNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->left == NULL) {
        return t;
    } else {
        return findMin(t->left);
    }
}

// public findMax
template <typename Comparable>
const Comparable & BST<Comparable>::findMax() const {
    if (root == NULL) {
    	throw underflow_error("Tree is empty");
	}
    return findMax(root)->element;
}

// private findMax: refer to textbook, Figure 4.21
template <typename Comparable>
typename BST<Comparable>::BinaryNode* BST<Comparable>::findMax(BinaryNode * t) const {
    if ( t == NULL ) {
        return NULL;
    } else if (t->right == NULL) {
        return t;
    } else {
        return findMin(t->right);
    }
}

// public contains: refer to textbook, Figure 4.17, Line 4 - 7
template<typename Comparable>
bool BST<Comparable>::contains( const Comparable & x ) const {
    return containsUtil(root,x);
}

// public insert: refer to textbook, Figure 4.17, Line 12 - 15
template<typename Comparable>
void BST<Comparable>::insert(const Comparable & x) {
	if(root == nullptr){
        root = new typename BST<Comparable>::BinaryNode(x);
        return;
    }

    auto curr = root;
    for(;;){
        auto currentElement = curr->element;
        if(x < currentElement){
            auto p = curr->left;
            if(p){
                curr = p;
                continue;
            }
            curr->left = new typename BST<Comparable>::BinaryNode(x);
            break;
        }
        else if (x > currentElement){
            auto p = curr->right;
            if(p){
                curr = p;
                continue;
            }
            curr->right = new typename BST<Comparable>::BinaryNode(x);
            break;
        }
        else{
            std::cerr << "Duplicate value \n";
            return;
        }
    }
}


// public remove: refer to textbook, Figure 4.17, Line 20 - 23
template<typename Comparable>
void BST<Comparable>::remove( const Comparable & x ) {
    removeUtil(root,x);
}

// public treeSize
template <typename Comparable>
int BST<Comparable>::treeSize() const {
	return treeSizeUtil(root);
}

// public treeHeight
template <typename Comparable>
int BST<Comparable>::treeHeight() const {
	return treeHeightUtil(root);
}

// public printInOrder: refer to textbook, Figure 4.60
template<typename Comparable>
void BST<Comparable>::printInOrder() const {
	printInOrderUtil(root);
    cout << endl;
}

// public printLevels
//template <typename Comparable>
//void BST<Comparable>::printLevels() const {
//    queue q;
//    q.enqueue(root);
//    int level = 1;
//    while(!q.isEmpty()){
//        int ls = 0;
//        ls = q.isEmpty() ? 0 : 1;
//
//
//
//        while(ls--){
//            BinaryNode *n = q.dequeue();
//            cout << "level " << level << ": "<< n->element << " ";
//            if(n->left){
//                q.enqueue(n->left);
//            }
//            if(n->right){
//                q.enqueue(n->right);
//            }
//        }
//        cout << endl;
//        level++;
//
//    }
//}

// public printLevels
template <typename Comparable>
void BST<Comparable>::printLevels() const {
    if(root == nullptr){
        return;
    }
    queue q;
    q.enqueue(root);
    int level=1;
    while(!q.isEmpty()){
        int levelSize = q.getSize();
        cout << "level: " << level << ":  ";
        for(int i = 0; i < levelSize; ++i){
            BinaryNode *bn = q.getF()->bn;
            cout << bn->element << " ";
            q.dequeue();
            if(bn->left != nullptr){
                q.enqueue(bn->left);
            }
            if(bn->right != nullptr){
                q.enqueue(bn->right);
            }
        }
        cout << endl;
        level++;
    }
}

// public printMaxPath
template <typename Comparable>
void BST<Comparable>::printMaxPath() const {
	printMaxPathUtil(root);
    cout << endl;
}

#endif
