/*[2015]（15分）用单链表保存 n 个整数，结点的结构为 [data][link]，且|data|≤n(n 为正整数)。
现要求设计一个时间复杂度尽可能高效的算法，对于链表中 data 的绝对值相等的节点，
仅保留第一次出现的节点而删除其余绝对值相等的节点。例如，若给定单链表 head 如下：
head □→21→-15→-15→-7→15
则删除节点后的 head 为
head □→21→-15→-7
*/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int data;
	struct Node* link;
}Node;

//尾插法创建链表
void CreateList(Node** head, int arr[], int len) {
	*head = (Node*)malloc(sizeof(Node));
	(*head)->link = NULL;
	Node* p = *head;
	for (int i = 0; i < len; i++) {
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->data = arr[i];
		newNode->link = NULL;
		p->link = newNode;
		p = newNode;
	}
}

//打印链表
void Print(Node* head) {
	Node* p = head->link;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->link;
	}
	printf("\n");
}

//删除绝对值重复结点
void DelSameAbs(Node* head, int n) {
	int* flag = (int*)calloc(n + 1, sizeof(int));
	Node* p = head->link;                     //p指向当前遍历的第一个结点
	Node* pre = head;                         //pre是p的前驱结点

	while (p != NULL) {
		int val = abs(p->data);
		if (flag[val] == 1) {
			pre->link = p->link;
			free(p);
			p = pre->link;
		}
		else {
			//第一次出现，打上标记，pre和p后移
			flag[val] = 1;
			pre = p;
			p = p->link;
		}
	}
	free(flag);                                  // 释放标记数组
}

int main() {
	int arr[] = { 21, -15, -15, -7, 15 };
	int n = sizeof(arr) / sizeof(arr[0]);    //计算n
	Node* head;

	CreateList(&head, arr, n);
	printf("去重前：\n");
	Print(head);

	DelSameAbs(head, n);
	printf("去重后: \n");
	Print(head);

	return 0;
}