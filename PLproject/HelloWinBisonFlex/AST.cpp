#include <stdlib.h>
#include "AST.h"
#include <iostream>

using namespace std;

Symbol SymbolTable[MAX_SYMBOLS];
int n_symbols = 0;

AST *makeNum(int val) 
{
	//cout << "int AST�������" << endl;
    AST *p;
    p = (AST *)malloc(sizeof(AST));
    p->op = NUM;
    p->val = val;
    return p;
}
AST *makeFloat (float val)
{
	AST *p;
	p = (AST *)malloc(sizeof(AST));
	p->op = FLO;
	p->val = val;
	return p;
}



AST *makeAST(enum code op,AST *left,AST *right)
{
	//cout << "AST�� ����, op=" << op << endl;
    AST *p;
    p = (AST *)malloc(sizeof(AST));
    p->op = op;
    p->right = right;
    p->left = left;
    return p;
}

AST *getNth(AST *p,int nth)
{
    if(p->op != LIST){
	fprintf(stderr,"bad access to list getNth \n");
	exit(1);
    }
    if(nth > 0) return(getNth(p->right,nth-1));
    else return p->left;
}

AST *addLast(AST *l,AST *p)
{
    AST *q;

    if(l == NULL) return makeAST(LIST,p,NULL);
    q = l;
    while(q->right != NULL) q = q->right;
    q->right = makeAST(LIST,p,NULL);
    return l;
}

AST *addList(AST *list1, AST* list2) {
	AST *q;

	if (list1 == NULL) return list2;
	q = list1;
	while (q->right != NULL) q = q->right;
	q->right = list2;
	return list1;
}

AST *getNext(AST *p)
{
    if(p->op != LIST){
	fprintf(stderr,"bad access to list getNext \n");
	exit(1);
    }
    else return p->right;
}

Symbol *lookupSymbol(char *name)
{
    int i;
    Symbol *sp;

    sp = NULL;
    for(i = 0; i < n_symbols; i++){
	if(strcmp(SymbolTable[i].name,name) == 0){
	    sp = &SymbolTable[i];
		//cout << "�ɺ� �ߺ���" << endl;
	    break;
	}
    }
    if(sp == NULL){//��ã�������
	sp = &SymbolTable[n_symbols++];
	sp->name = _strdup(name);
    }
    return sp;
}

AST *makeSymbol(char *name)
{

	//cout << "�ɺ��������" << name << endl;
    AST *p;

    p = (AST *)malloc(sizeof(AST));
    p->op = SYM;
    p->sym = lookupSymbol(name);
    return p;
}

Symbol *getSymbol(AST *p)
{
	//cout << p->op << endl;
    if(p->op != SYM){
	fprintf(stderr,"bad access to symbol\n");
	exit(1);
    }
    else return p->sym;
}

