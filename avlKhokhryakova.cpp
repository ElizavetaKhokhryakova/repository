
#include <iostream>
#include<stdio.h>
#include <io.h>
#include<stdlib.h>


#define MAX_LENGTH 260

using namespace std;

struct node
{
	int key; //данные, размещенные на вершине дерева (в принципе любой тип)
	int height;//высота поддерева с корнем *node	
	node *left; //указатель на левого сына
	node *right;//указатель на правого сына
	node(int k) { key = k; left = right = 0; height = 1; }
	
};

//чтобы упростить основную прогу - учитывет возможность пустого указателя
int height(node* p)
{
	return p?p->height:0;
}

//возвращает разность высот левого и правого поддерева узла p
int bfactor(node* p)
{
	return height(p->right)-height(p->left);
}


//вычисляет height узла p по высотам его левого и правого поддеревьев
void fixheight(node* p)
{
	int hl = height(p->left);
	int hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

// правый поворот вокруг p - возвращает новую вершину поддерева
node* rotateright(node* p) 
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}


// левый поворот вокруг q 
node* rotateleft(node* q) 
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}


node* balance(node* p) // балансировка узла p
{
	fixheight(p);
	if( bfactor(p)==2 )
	{
		if( bfactor(p->right) < 0 )
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if( bfactor(p)==-2 )
	{
		if( bfactor(p->left) > 0  )
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // балансировка не нужна
}



// вставка ключа k в дерево с корнем p
node* insert(node* p, int k) 
{
	if( !p ) return new node(k);
	if( k<p->key )
		p->left = insert(p->left,k);
	else
		p->right = insert(p->right,k);
	return balance(p);
}




//максимальный элемент
int tree_max(node *current_node)
{
	int sum = current_node->key;
	if (current_node->right == NULL) return current_node->key;
	else return tree_max(current_node->right);
}



//удаление дерева вместе с корнем
void del_tree(node *current_node)
{
	int lev1 = 0, lev2 = 0;
	if (current_node->left != NULL) del_tree(current_node->left);
	if (current_node->right != NULL) del_tree(current_node->right);
	free(current_node);
}


int main()
{
	node *p = NULL;
	int dat;
	FILE *fl=NULL;

//reading a tree from file
	fl = fopen("tree.txt", "r");
	if (fl==NULL)
		printf("The file fscanf.out was not opened\n");
	else
	{

		while (!feof(fl)) //заполнение дерева с клавиатуры
		{
			fscanf(fl, "%d", &dat);
			p=insert(p, dat);
		}

	}

	printf("\n %d", tree_max(p));
	del_tree(p);

}
