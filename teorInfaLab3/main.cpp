#include <iostream>

struct BinaryTree{
    int data;
    short level;
    BinaryTree * right;
    BinaryTree * left;
};

BinaryTree * inic(int value);
BinaryTree*inic(int value);
void print(BinaryTree * binaryTree);
void add(BinaryTree *& binaryTree, int value);
int main(){
    BinaryTree * parent = NULL;
    add(parent,0);
    add(parent,1);
    add(parent,3);
    add(parent,5);
    add(parent,7);
    add(parent,9);
    print(parent);
    std::cout<<std::endl;
    system("pause");
    return 0;
}

BinaryTree * inic(int value){
    BinaryTree* binaryTree=new BinaryTree;
    binaryTree->data=value;
    binaryTree->level=0;
    binaryTree->left=NULL;
    binaryTree->right=NULL;
}

void add(BinaryTree *& binaryTree, int value){
    if(binaryTree == NULL){
        binaryTree=inic(value);
        return;
    }
    BinaryTree * help;
    binaryTree->level++;
    if(binaryTree->right==NULL && binaryTree->left==NULL){
        binaryTree->right=inic(value);
        binaryTree->left=inic(value+1);
        return;
    }
    help=binaryTree->right;
    if(binaryTree->right->right!=NULL && binaryTree->right->left!=NULL && (help->level>binaryTree->left->level)) help=binaryTree->left;
    add(help,value);

}

void print(BinaryTree * binaryTree){
    if(binaryTree==NULL) {
        return;
    }
    std::cout<<binaryTree->data<<" ";
    /*ПРЯМОЙ ОБХОД*/
    print(binaryTree->right);
    print(binaryTree->left);


}