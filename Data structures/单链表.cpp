#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

typedef int Elemtype;
typedef struct Node {
	Elemtype data;
	Node* next;
}Node;

//初始化链表（带头结点）
void InitList(Node** H) {
	*H = (Node*)malloc(sizeof(Node));
	(*H)->next = NULL;
}

//头插
void HeadInsert(Node* H, Elemtype val) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = val;
	newNode->next = H->next;
	H->next = newNode;
}

//尾插
void TailInsert(Node* H, Elemtype val) {
	Node* p = H;
	while (p->next != NULL) {
		p = p->next;
	}

	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = val;
	newNode->next = NULL;
	p->next = newNode;
}

//指定插入
int Insert(Node* H, int pos, Elemtype val) {
	if (pos < 1)
		return 0;
	Node* p = H;
	int i = 0;
	while (p != NULL && i < pos - 1) {
		p = p->next;
		i++;
	}
	if (p == NULL)
		return 0;
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = val;
	newNode->next = p->next;
	p->next = newNode;
	return 1;
}

//获取链表长度
int GetLen(Node* H) {
	Node* p = H->next;
	int len = 0;
	while (p != NULL) {
		len++;
		p = p->next;
	}
	return len;
}

//删除节点
int Delete(Node* H, int pos, Elemtype* val) {
	if (pos < 1)
		return 0;
	Node* p = H;
	int i = 0;
	while (p->next != NULL && i < pos - 1) {
		p = p->next;
		i++;
	}
	if (p == NULL || p->next == NULL)
		return 0;
	Node* DelNode = p->next;
	*val = DelNode->data;
	p->next = DelNode->next;
	free(DelNode);
	return 1;
}

//输出链表
void Print(Node* H) {
	Node* p = H->next;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

//释放链表内存
void FreeList(Node* H) {
	Node* p = H, * q;
	while (p != NULL) {
		q = p;
		p = p->next;
		free(q);
	}
}

int main() {
	SetConsoleOutputCP(CP_UTF8);
	Node* H;
	InitList(&H);
	int val;
	HeadInsert(H, 1);
	HeadInsert(H, 2);
	printf("头插后：\n");
	Print(H);
	TailInsert(H, 3);
	TailInsert(H, 4);
	printf("尾插后：\n");
	Print(H);
	Insert(H, 2, 8);
	printf("第2位插入8：\n");
	Print(H);
	printf("链表长度为:%d\n", GetLen(H));
	Delete(H, 3, &val);
	printf("删除第3个节点，删除的值：%d\n", val);
	printf("删除后：\n");
	Print(H);
	FreeList(H);
	return 0;
}
