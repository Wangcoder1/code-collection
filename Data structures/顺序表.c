#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MaxSize 50
typedef int ElemType;
typedef struct {
	ElemType data[MaxSize];
	int length;
}SqList;

//1.创建顺序表
SqList* CreateList() {
	SqList* L = (SqList*)malloc(sizeof(SqList));
	if (L == NULL)  // 防止内存分配失败
	{
		printf("内存分配失败！\n");
		return 0;
	}
	L->length = 0;
	return L;
}

/* 法二：初始化函数，利用二级指针
void InitList(SqList** L) {
	//此L存main里L的地址，*L解指针得到main里L存的结构体的地址，**L继续解指针得到地址对应的SqList结构体
	*L = (SqList*)malloc(sizeof(SqList));
	//为main里L赋值，malloc在堆上开辟一块内存，用来存放SqList结构体，并且返回这块结构体的起始地址
	(*L)->length = 0;
}
int main(){
	SqList* L;
*/

//2.导入数组
bool InitFromArray(SqList* L, ElemType arr[], int n)
{
	if (n < 0 || n > MaxSize) return false;
	for (int i = 0;i < n;i++)
	{
		L->data[i] = arr[i];
	}
	L->length = n;
	return true;
}

//3.判断是否为空
bool ListEmpty(SqList* L) {                    //用一级指针，L存的值是结构体地址
	return (L->length == 0);
}

//4.获取顺序表长度
int ListLength(SqList* L) {
	return (L->length);
}

//5.输出顺序表所有元素
void PrintList(SqList* L) {
	for (int i = 0; i < L->length; i++) {
		printf("%d ", L->data[i]);
	}
	printf("\n");
}

//6.按逻辑序号取元素，放入e
bool GetElem(SqList* L, int i, ElemType* e) {
	if (i < 1 || i > L->length)
		return false;
	*e = L->data[i - 1];
	return true;
}

//7.按值查找，返回逻辑序号，找不到返回
int LocateElem(SqList* L, ElemType e) {
	int i = 0;
	while (i < L->length&& L->data[i] != e) {
		i++;
	}
	if (i >= L->length) {
		return 0;
	}
	else {
		return i + 1;
	}
}

//8.在第i个位置插入元素e
bool ListInsert(SqList** L, int i, ElemType e) {
	if (i < 1 || i >(*L)->length + 1 || (*L)->length >= MaxSize)
		return false;
	i--;
	for (int j = (*L)->length; j > i; j--) {
		(*L)->data[j] = (*L)->data[j - 1];
	}
	(*L)->data[i] = e;
	(*L)->length++;
	return true;
}

//9.删除第i个元素，被删除元素存入e
bool ListDelete(SqList** L, int i, ElemType* e) {
	if (i < 1 || i >(*L)->length)
		return false;
	i--;
	*e = (*L)->data[i];
	for (int j = i; j < (*L)->length - 1; j++) {
		(*L)->data[j] = (*L)->data[j + 1];
	}
	(*L)->length--;
	return true;
}

//10.销毁顺序表，释放内存
void DestroyList(SqList** L) {
	free(*L);
	*L = NULL;
}

int main() {
	SqList* L = CreateList();                  //一级指针，取L里面存的地址对应的SqList结构体
	ElemType arr[] = { 10, 20, 30, 40, 50 };
	int n = 5;
	ElemType val;
	bool ret;

	printf("===== 1.由数组创建顺序表 =====\n");
	printf("顺序表内容：");
	InitFromArray(L, arr, n);
	PrintList(L);

	printf("\n===== 2.获取第3个元素 =====\n");
	ret = GetElem(L, 3, &val);
	if (ret) printf("第3个元素 = %d\n", val);

	printf("\n===== 3.查找值40的位置 =====\n");
	int pos = LocateElem(L, 40);
	if (pos != 0) printf("40在第%d位\n", pos);
	else printf("没有找到\n");

	printf("\n===== 4.在第2位插入99 =====\n");
	ret = ListInsert(&L, 2, 99);
	if (ret) {
		printf("插入成功，表：");
		PrintList(L);
	}

	printf("\n===== 5.删除第4位元素 =====\n");
	ret = ListDelete(&L, 4, &val);
	if (ret) {
		printf("删掉的元素是：%d\n", val);
		printf("删除后表：");
		PrintList(L);
	}

	printf("\n===== 6.长度、判空 =====\n");
	printf("当前长度=%d\n", ListLength(L));
	if (ListEmpty(L)) printf("是空表\n");
	else printf("不是空表\n");

	// 销毁
	DestroyList(&L);
	return 0;
}
