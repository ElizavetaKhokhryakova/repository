
#include <iostream>
#include<stdio.h>
#include <io.h>
#include<stdlib.h>


#define MAX_LENGTH 260

using namespace std;

struct node
{
	int key; //äàííûå, ðàçìåùåííûå íà âåðøèíå äåðåâà (â ïðèíöèïå ëþáîé òèï)
	int height;//âûñîòà ïîääåðåâà ñ êîðíåì *node	
	node *left; //óêàçàòåëü íà ëåâîãî ñûíà
	node *right;//óêàçàòåëü íà ïðàâîãî ñûíà
	node(int k) { key = k; left = right = 0; height = 1; }
	
};

//÷òîáû óïðîñòèòü îñíîâíóþ ïðîãó - ó÷èòûâåò âîçìîæíîñòü ïóñòîãî óêàçàòåëÿ
int height(node* p)
{
	return p?p->height:0;
}

//âîçâðàùàåò ðàçíîñòü âûñîò ëåâîãî è ïðàâîãî ïîääåðåâà óçëà p
int bfactor(node* p)
{
	return height(p->right)-height(p->left);
}


//âû÷èñëÿåò height óçëà p ïî âûñîòàì åãî ëåâîãî è ïðàâîãî ïîääåðåâüåâ
void fixheight(node* p)
{
	int hl = height(p->left);
	int hr = height(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

// ïðàâûé ïîâîðîò âîêðóã p - âîçâðàùàåò íîâóþ âåðøèíó ïîääåðåâà
node* rotateright(node* p) 
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}


// ëåâûé ïîâîðîò âîêðóã q 
node* rotateleft(node* q) 
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}


node* balance(node* p) // áàëàíñèðîâêà óçëà p
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
	return p; // áàëàíñèðîâêà íå íóæíà
}



// âñòàâêà êëþ÷à k â äåðåâî ñ êîðíåì p
node* insert(node* p, int k) 
{
	if( !p ) return new node(k);
	if( k<p->key )
		p->left = insert(p->left,k);
	else
		p->right = insert(p->right,k);
	return balance(p);
}




//ìàêñèìàëüíûé ýëåìåíò
int tree_max(node *current_node)
{
	int sum = current_node->key;
	if (current_node->right == NULL) return current_node->key;
	else return tree_max(current_node->right);
}



//óäàëåíèå äåðåâà âìåñòå ñ êîðíåì
void del_tree(node *current_node)
{
	int lev1 = 0, lev2 = 0;
	if (current_node->left != NULL) del_tree(current_node->left);
	if (current_node->right != NULL) del_tree(current_node->right);
	free(current_node);
}

//óäàëåíèå óçëà ïî çíà÷åíèþ êëþ÷à (Delkey ñî âñïîìîãàòåëüíûìè)
node *SearchMin(node *x)
{
if (x->left) return SearchMin(x->left);
else return x;
}

node *DeleteMin(node *x)
{
if (x->left==NULL) return x->right;
x->left=DeleteMin(x->left);
return balance(x);
}

node *Delkey(node *x, int k)
{
if (x==NULL) return NULL;
if (k<x->key) x->left=Delkey(x->left, k);
else if (k>x->key) x->right=Delkey(x->right, k);
else
{
node *y=x->left;
node *z=x->right;
delete x;
if (z==NULL) return y;
node* min=SearchMin(z);
min->right=DeleteMin(z);
min->left=y;
return balance(min);
}
return balance(x);
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

		while (!feof(fl)) //çàïîëíåíèå äåðåâà ñ êëàâèàòóðû
		{
			fscanf(fl, "%d", &dat);
			p=insert(p, dat);
		}

	}
	p=Delkey(p,2);
	printf("\n %d", tree_max(p));
	del_tree(p);

}
