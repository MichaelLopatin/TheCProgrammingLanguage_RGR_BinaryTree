
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <locale.h>
#include <string.h>//для работы со строками
#include <time.h>//для рандома, для clock
#include <stdlib.h>//для рандома
#include <conio.h>//ввод вывод с клавиатуры

#define N 4//длина массива указателей в узле дерева

int OBJ = 30;//начальное количество объектов
int OBJADD = 0;//количество добавленных объектов 

			   //подсчет операций
unsigned int ID = 0; //Количество инкрементов и декрементов (++ --)
unsigned int COM = 0; // сравнение (< > <= >= == != )
unsigned int LOG = 0; // логические операции (&& || )
unsigned int MATH = 0; // арифметические операции (+ - * / % ++ --
unsigned int AS = 0; // присваивание assignment ( = += -= *= /= )
unsigned int ADD = 0; // & * sazeof

unsigned int TIME = 0; // время работы программы
unsigned int TIMEBEGIN = 0; // время начала отрезка
unsigned int TIMEEND = 0; // время окончания отрезка

struct Tree
{
	Tree *leftBranch;
	Tree *rightBranch;
	int *dataArray[N] = { NULL };
};
typedef struct Tree Tree;

//присваивание значений элементам массива
void generateObjects(int *objects);
// "быстрая" сортировка массива 
void sortObjects(int *objects, int leftIndex, int rightIndex);
// запись в двумерный массив индекатора и упорядоченное значение объекта
void objectsFirstToSecond(int *objectsFirst, int **objectsSecond);
//переписывает начальное количество вершин в массив//не забыть обнулять
void numberOfNodes(int* amountNodes, int leftIndex, int rightIndex);
//записывает в массив значение первого эл-та топа
void putFirstElementValueOfNodeInnerFun(int * count, int *indexFirstElementValueOfNode, int **objectsSecond, int leftIndex, int rightIndex);
// оболочка для numberOfNodesToFirstElementValueOfNode со счетчиком
void putFirstElementValueOfNode(int *indexFirstElementValueOfNode, int **objectsSecond, int leftIndex, int rightIndex);
// создание дерева
void createTree(Tree **nodePointer, int **objectsSecond, int *indexFirstElementValueOfNode, int amountNodes);
// добавление узла дереву
void insertNode(Tree **nodePointer, int *ptr, int indexDataArray);
// показ дерева
void showTree(Tree *nodePointer, int amountNodes);
// отображение узла
void showDone(Tree *nodePointer, int LevelToShow, int currentDeep);
// добавляет элемент в дерево
void insertElement(Tree *nodePointer, int *element);
// оболочка для insertElement добавляет эл-ты из массива
void insertElementToTree(Tree **nodePointer, int **objectsSecond);
//находит глубину дерева
int findMaxDeep(Tree *nodePointer, int amountNodes);
//находит длину левой ветви дерева
int findLeftBranchLn(Tree *nodePointer, int amountNodes);
//находит длину правой ветви дерева
int findRightBranchLn(Tree *nodePointer, int amountNodes);
// обходит дерево LRT
void bypassTreeInOrder(Tree *nodePointer);
// считает кол-во вершин в созданном дереве
void countNodes(Tree *nodePointer, int *amountNodes);
// считает кол-во вершин в созданном дереве (внутренняя функция)
void countNodesInnerFunc(Tree *nodePointer, int *amountNodes);
// объединяет первоначальный массив с добавленными
void objectsFirstAndAdded(int *objectsFirst, int *addedElements, int *firstAndAddedElements);
// запись в двумерный массив индекатора и упорядоченное значение элемента после добавления
void objectsFirstAndAddedToElemBalance(int *firstAndAddedElements, int **elementArrayForBalanceTree);
// удаляет дерево
void deleteTreeInOrder(Tree *nodePointer);
// отображает статистику по дереву
void showStatistic(Tree *nodePointer, int *amountNodes);
// вывод на экран параметров трудоемкости
void showLabor();
void bypassTreeInOrderHorizontal(Tree *nodePointer, int deep);

void main()
{
	setlocale(LC_ALL, "Russian");

	TIMEBEGIN = clock();

	int i;
	int amountNodes = 0;//кол-во вершин в дереве при первоначальном создании
	int amountNodes2 = 0;//кол-во вершин в дереве после создания или изменения// не забывать обнулять
	int countIndexNodes = 0;//счетчик индексов узлов при создании дерева для заполнения data
	int *objectsFirst = NULL;//динамический массив с объектами
	int *indexFirstElementValueOfNode = NULL;//динамический массив со значениями (индексы objectsSecond, где лежат значения узлов) 
	int **objectsSecond = NULL;//динамический двумерный массив с индикатором передачи параметра дереву
	int *addedElements = NULL; // массив с добавленными элементами
	int *firstAndAddedElements = NULL; // массив с прежними и добавленными эелементами
	int **elementArrayForBalanceTree = NULL;// массив, с прежними и добавленными эелементами с индикатором, для дальнейшей балансировки дерева
	Tree *root = NULL;//указатель на корень дерева
	AS += 11;
	// инициализация указателей
	objectsFirst = (int*)malloc(sizeof(int)*OBJ); AS++; ADD++;
	objectsSecond = (int**)malloc(sizeof(int*)*OBJ); AS++; ADD++;
	numberOfNodes(&amountNodes, 0, OBJ - 1); ADD++;
	indexFirstElementValueOfNode = (int*)malloc(sizeof(int)*amountNodes); AS++; ADD++;
	for (i = 0; i < OBJ; i++)
	{
		ID++; COM++;
		objectsSecond[i] = (int*)malloc(sizeof(int) * 2); AS++; ID++; ADD++; MATH++;
	}

	// создание первоначального дерева
	objectsFirstToSecond(objectsFirst, objectsSecond);
	putFirstElementValueOfNode(indexFirstElementValueOfNode, objectsSecond, 0, OBJ - 1);
	createTree(&root, objectsSecond, indexFirstElementValueOfNode, amountNodes); ADD++;
	printf("Первоначальные элементы дерева (упорядоченные):\n");
	for (i = 0; i < OBJ; i++)
	{
		ID++; COM++;
		printf("%4d ", objectsSecond[i][1]);
		if ((i + 1) % 10 == 0)
		{
			COM++; MATH++; MATH++;
			printf("\n");
		}
	}
	AS++;
	printf("\n");
	insertElementToTree(&root, objectsSecond); ADD++;
	countNodes(root, &amountNodes2); ADD++;
	showTree(root, amountNodes2);
	bypassTreeInOrder(root);
	showStatistic(root, &amountNodes2); ADD++;
	TIMEEND = clock();
	TIME = TIME + TIMEEND - TIMEBEGIN;

	// считывание добавляемых в дерево элементов
	printf("\nВведите, сколько элементов вы хотите добавить в дерево:\n");
	scanf("%d", &OBJADD);
	addedElements = (int*)malloc(sizeof(int) * OBJADD);
	for (i = 0; i < OBJADD; i++)
	{
		printf("Введите %d-ое число:\n", i + 1);
		scanf("%d", &addedElements[i]);
		while (addedElements[i] == 0)
		{
			printf("Введите число не равное нулю.\n");
			printf("Введите %d-ое число:\n", i + 1);
			scanf("%d", &addedElements[i]);
		}
	}

	TIMEBEGIN = clock();
	// добавление и отображение измененного дерева
	printf("\n");
	for (i = 0; i<OBJADD; i++)
	{
		ID++; COM++;
		insertElement(root, &(addedElements[i])); ADD++;
	}
	AS++;
	countNodes(root, &amountNodes2); ADD++;
	printf("Дерево с добавленными элементами:\n");
	showTree(root, amountNodes2);
	printf("Дерево с добавленными элементами:\n");
	bypassTreeInOrder(root);
	showStatistic(root, &amountNodes2); ADD++;

	// освобождение памяти и обнуление
	deleteTreeInOrder(root);
	root = NULL; AS++;
	free(indexFirstElementValueOfNode);
	for (i = 0; i < OBJ; i++)
	{
		ID++; COM++;
		free(objectsSecond[i]);
	}
	AS++;
	free(objectsSecond);
	indexFirstElementValueOfNode = NULL; AS++;
	amountNodes = 0; AS++;


	// создание сбалансированного дерева с добавленными элементами
	numberOfNodes(&amountNodes, 0, (OBJ + OBJADD - 1)); ADD++;

	// инициализация указателей
	indexFirstElementValueOfNode = (int*)malloc(sizeof(int)*amountNodes); AS++; ADD++;
	firstAndAddedElements = (int*)malloc(sizeof(int) * (OBJ + OBJADD)); AS++; ADD++;
	elementArrayForBalanceTree = (int**)malloc(sizeof(int*)*(OBJ + OBJADD)); AS++; ADD++;
	for (i = 0; i < (OBJ + OBJADD); i++)
	{
		ID++; COM++;
		elementArrayForBalanceTree[i] = (int*)malloc(sizeof(int) * 2); AS++; ADD++; MATH++;
	}
	AS++;

	// создание первоначального сбалансированного дерева с добавленными элементами
	objectsFirstAndAdded(objectsFirst, addedElements, firstAndAddedElements);
	objectsFirstAndAddedToElemBalance(firstAndAddedElements, elementArrayForBalanceTree);
	putFirstElementValueOfNode(indexFirstElementValueOfNode, elementArrayForBalanceTree, 0, (OBJ + OBJADD - 1));
	printf("Элементы дерева (упорядоченные):\n");
	for (i = 0; i < OBJ + OBJADD; i++)
	{
		ID++; COM++;
		printf("%4d ", elementArrayForBalanceTree[i][1]);
		if ((i + 1) % 10 == 0)
		{
			COM++; MATH++; MATH++;
			printf("\n");
		}
	}
	AS++;
	printf("\n");
	// создание сбалансированного дерева с добавленными элементами
	createTree(&root, elementArrayForBalanceTree, indexFirstElementValueOfNode, amountNodes); ADD++;
	insertElementToTree(&root, elementArrayForBalanceTree); ADD++;
	// вывод на экран
	countNodes(root, &amountNodes2);
	printf("Сбалансированное дерево с добавленными элементами:\n");
	showTree(root, amountNodes2);
	printf("Сбалансированное дерево с добавленными элементами:\n");
	bypassTreeInOrder(root);
	showStatistic(root, &amountNodes2); ADD++;

	TIMEEND = clock();
	TIME = TIME + TIMEEND - TIMEBEGIN;
	showLabor();
	printf("\n");
	printf("\n");
	bypassTreeInOrderHorizontal(root, 0);
}


void generateObjects(int *objects)
{
	int i;
	int objRand;
	for (i = 0; i < OBJ; i++)
	{
		COM++;
		ID++;
		srand(i*i); MATH++;
		objRand = (((rand() + 1) % (OBJ * 100) * (rand() + 1) % (OBJ * 100) * (997 + OBJ) * (983 + OBJ))) % (OBJ * 10 + 999) + 1; AS++;
		srand(objRand * i*OBJ);
		objRand += (((rand() + 1) % (N * 100) * (rand() + 1) % (N * 100) * (997 + N) * (983 + OBJ))) % (OBJ * 10 + 999) + 1; AS++;
		if (objRand < 0)
		{
			COM++;
			objRand = -objRand; AS++;
		}
		if (objRand == 0)
		{
			COM++;
			objRand = (i + N)*N; AS++; MATH++;
		}
		objRand = objRand % (OBJ * 10 + 9999999 % OBJ); AS++;
		*(objects + i) = objRand; AS++;
		MATH++; MATH++; MATH++; MATH++; MATH++; MATH++; MATH++; MATH++; MATH++; MATH++;
		MATH++; MATH++; MATH++; MATH++; MATH++; MATH++; MATH++; MATH++; MATH++; MATH++;
		MATH++; MATH++; MATH++; MATH++; MATH++; MATH++; MATH++; MATH++; MATH++; MATH++;
		MATH++; MATH++; MATH++; MATH++; MATH++; MATH++; MATH++;
	}
	AS++;
}

void sortObjects(int *objects, int leftIndex, int rightIndex)
{
	int i, j, mode;
	int glass;
	if (leftIndex >= rightIndex)
	{
		COM++;
		return;
	}
	for (i = leftIndex, j = rightIndex, mode = 1; i < j;)
	{
		COM++;
		if (objects[i] > objects[j])
		{
			COM++;
			glass = objects[i]; AS++;
			objects[i] = objects[j]; AS++;
			objects[j] = glass; AS++;
			mode = -mode; AS++;
		}
		if (mode > 0)
		{
			j--; ID++; COM++;
		}
		if (mode < 0)
		{
			i++; ID++; COM++;
		}
	}
	AS += 3;
	sortObjects(objects, leftIndex, i - 1); MATH++;
	sortObjects(objects, i + 1, rightIndex); MATH++;
}

void objectsFirstToSecond(int *objectsFirst, int **objectsSecond)
{
	int i;
	generateObjects(objectsFirst);//запись значений объектов в массив
	sortObjects(objectsFirst, 0, OBJ - 1);
	for (i = 0; i < OBJ; i++)
	{
		ID++; COM++;
		objectsSecond[i][0] = 0; AS++;
		objectsSecond[i][1] = *(objectsFirst + i); AS++; ADD++; MATH++;
	}AS++;
}

void numberOfNodes(int *pointerAmountNodes, int leftIndex, int rightIndex)
{
	int middleIndex;

	if (leftIndex > rightIndex)
	{
		COM++;
		return;
	}
	if (leftIndex == rightIndex)
	{
		COM++;
		middleIndex = leftIndex; AS++;
		*pointerAmountNodes = (*pointerAmountNodes) + 1; AS++; ADD++; ADD++; ADD++; ADD++; MATH++;
		return;
	}
	if (leftIndex < rightIndex)
	{
		COM++; MATH++; MATH++;
		if (((rightIndex + 1) - (leftIndex)) <= N)
		{
			COM++;
			middleIndex = leftIndex; AS++;
			*pointerAmountNodes = (*pointerAmountNodes) + 1; AS++; ADD++; ADD++; ADD++; ADD++; MATH++;
			return;
		}MATH++; MATH++;
		if (((rightIndex + 1) - (leftIndex)) > N)
		{
			COM++;
			middleIndex = leftIndex + (((rightIndex + 1) - (leftIndex)) / 2) - (N / 2); AS++; MATH++; MATH++; MATH++; MATH++; MATH++; MATH++;
			*pointerAmountNodes = (*pointerAmountNodes) + 1; AS++; ADD++; ADD++; ADD++; ADD++; MATH++;
			numberOfNodes(pointerAmountNodes, leftIndex, middleIndex - 1); MATH++;
			numberOfNodes(pointerAmountNodes, middleIndex + N, rightIndex); MATH++;
		}
	}
}

void putFirstElementValueOfNode(int *firstElementValueOfNode, int **objectsSecond, int leftIndex, int rightIndex)
{
	int count = 0; AS++;
	putFirstElementValueOfNodeInnerFun(&count, firstElementValueOfNode, objectsSecond, leftIndex, rightIndex); ADD++;
}

void putFirstElementValueOfNodeInnerFun(int * count, int *firstElementValueOfNode, int **objectsSecond, int leftIndex, int rightIndex)
{
	int middleIndex;

	if (leftIndex > rightIndex)
	{
		COM++;
		return;
	}
	if (leftIndex == rightIndex)
	{
		COM++;
		middleIndex = leftIndex; AS++;
		*(firstElementValueOfNode + *count) = middleIndex; AS++; ADD++; ADD++; MATH++;
		objectsSecond[middleIndex][0] = 1; AS++;
		*count = (*count) + 1; AS++; ADD++; ADD++; MATH++;
		return;
	}
	if (leftIndex < rightIndex)
	{
		COM++; MATH++; MATH++;
		if (((rightIndex + 1) - (leftIndex)) <= N)
		{
			COM++;
			middleIndex = leftIndex; AS++;
			*(firstElementValueOfNode + *count) = middleIndex; AS++; ADD++; ADD++;
			objectsSecond[middleIndex][0] = 1; AS++;
			*count = (*count) + 1; AS++; ADD++; ADD++;
			return;
		}MATH++; MATH++;
		if (((rightIndex + 1) - (leftIndex)) > N)
		{
			COM++;
			middleIndex = leftIndex + (((rightIndex + 1) - (leftIndex)) / 2) - (N / 2); AS++; MATH++; MATH++; MATH++; MATH++; MATH++; MATH++;
			*(firstElementValueOfNode + *count) = middleIndex; AS++; ADD++; ADD++; MATH++;
			objectsSecond[middleIndex][0] = 1; AS++;
			*count = (*count) + 1; AS++; ADD++; ADD++; MATH++;
			putFirstElementValueOfNodeInnerFun(count, firstElementValueOfNode, objectsSecond, leftIndex, middleIndex - 1); MATH++;
			putFirstElementValueOfNodeInnerFun(count, firstElementValueOfNode, objectsSecond, middleIndex + N, rightIndex); MATH++;
		}
	}
}

void createTree(Tree **nodePointer, int **objectsSecond, int *firstElementValueOfNode, int amountNodes)
{
	int i;
	for (i = 0; i < amountNodes; i++)
	{
		ID++; COM++;
		insertNode(nodePointer, &(objectsSecond[firstElementValueOfNode[i]][1]), 0); ADD++;
	} AS++;
}

void insertNode(Tree **nodePointer, int *ptr, int indexDataArray)
{
	int i;
	if (*nodePointer == NULL)
	{
		COM++; ADD++;
		*nodePointer = (Tree*)malloc(sizeof(Tree)); AS++; ADD++; ADD++;
		if (*nodePointer != NULL)
		{
			COM++; ADD++;
			for (i = 0; i < N; i++)
			{
				ID++; COM++;
				(*nodePointer)->dataArray[i] = NULL; AS++; ADD++;
			}
			(*nodePointer)->dataArray[indexDataArray] = ptr; AS++; ADD++;
			(*nodePointer)->leftBranch = NULL; AS++; ADD++;
			(*nodePointer)->rightBranch = NULL; AS++; ADD++;
		}
		else
		{
			printf("%d не добавлен. Недостаточно памяти.\n", *ptr); ADD++;
		}
	}
	else if (*ptr < *((*nodePointer)->dataArray[indexDataArray]))
	{
		COM++; ADD++; ADD++;
		insertNode(&((*nodePointer)->leftBranch), ptr, indexDataArray); ADD++; ADD++;
	}
	else if (*ptr >= *((*nodePointer)->dataArray[indexDataArray]))
	{
		COM++; ADD++; ADD++;
		insertNode(&((*nodePointer)->rightBranch), ptr, indexDataArray); ADD++; ADD++;
	}
}

void showTree(Tree *nodePointer, int amountNodes)
{
	int i;
	int treeWidth = 1; AS++;//максимальная ширина дерева 
	int treeDeep = 0; AS++;//максимальная глубина упорядоченного дерева 

	treeDeep = findMaxDeep(nodePointer, 1); AS++;
	for (i = 1; i <= treeDeep + 1; i++)
	{
		ID++; COM++; MATH++;
		if ((i) <= treeDeep + 1)
		{
			COM++; MATH++;
			printf("Уровень погружения: %d\n\n", i);
		}
		showDone(nodePointer, i, 1);
	} AS++;
	printf("Конец дерева.\n\n");
}

void showDone(Tree *nodePointer, int levelToShow, int currentDeep)
{

	if (currentDeep < levelToShow)
	{
		COM++;
		if (nodePointer != NULL)
		{
			COM++;
			showDone(nodePointer->leftBranch, levelToShow, currentDeep + 1); MATH++;
			showDone(nodePointer->rightBranch, levelToShow, currentDeep + 1); MATH++;
		}
	}
	else
	{
		if (nodePointer != NULL)
		{
			COM++;
			int i;
			for (i = 0; i < N; i++)
			{
				ID++; COM++;
				if ((nodePointer->dataArray[i]) != NULL)
				{
					COM++;
					printf("%p  {%d}\n", nodePointer->dataArray[i], *(nodePointer->dataArray[i])); ADD++;
				}
				else
				{
					printf("***  {...}\n");
				}
			}
			printf("\n");
		}
		if (nodePointer == NULL)
		{
			COM++;
			printf("NULL\n\n");
		}
	}
}

void insertElement(Tree *nodePointer, int *element)
{
	int i;
	int *bufElement;
	int countOverflow = 0; AS++;

	if (nodePointer == NULL)
	{
		COM++;
		insertNode(&nodePointer, element, 0); ADD++;
	}

	if (nodePointer->rightBranch != NULL)
	{
		COM++; ADD++; ADD++;
		if (*element >= *(nodePointer->dataArray[0]))
		{
			COM++; ADD++; ADD++;
			if (*element >= *(nodePointer->rightBranch->dataArray[0]))
			{
				COM++;
				insertElement(nodePointer->rightBranch, element);
			}
			else if (*element < *(nodePointer->rightBranch->dataArray[0]))
			{
				COM++; ADD++; ADD++; MATH++;
				if (nodePointer->dataArray[N - 1] != NULL)
				{
					COM++; ADD++; ADD++; MATH++;
					if (*element >= *(nodePointer->dataArray[N - 1]))
					{
						COM++;
						insertElement(nodePointer->rightBranch, element);
					}
				}LOG++; ADD++; ADD++; MATH++; MATH++;
				if ((nodePointer->dataArray[N - 1] == NULL) || (*element < (*(nodePointer->dataArray[N - 1]))))
				{
					COM++;
					for (i = 0; i < N; i++)
					{
						ID++; COM++; LOG++; ADD++; ADD++;
						if ((nodePointer->dataArray[i] != NULL) && (*element >(*(nodePointer->dataArray[i]))))
						{
							COM++;
							continue;
						}
						else if (nodePointer->dataArray[i] == NULL)
						{
							COM++;
							nodePointer->dataArray[i] = element; AS++;
							return;
						}
						else if (*element <= *(nodePointer->dataArray[i]))
						{
							COM++; ADD++; ADD++;
							bufElement = nodePointer->dataArray[i]; AS++;
							nodePointer->dataArray[i] = element; AS++;
							element = bufElement; AS++;
							countOverflow = i; AS++;
						}
						if (countOverflow == 3)
						{
							COM++;
							insertNode(&(nodePointer->rightBranch), element, 0); ADD++;
							return;
						}
					} AS++;
				}
			}
		}
	}
	else if (nodePointer->rightBranch == NULL)
	{
		COM++; ADD++; ADD++;
		if (*element >= *(nodePointer->dataArray[0]))
		{
			COM++; MATH++;
			if (nodePointer->dataArray[N - 1] != NULL)
			{
				COM++; ADD++; ADD++; MATH++;
				if (*element >= *(nodePointer->dataArray[N - 1]))
				{
					COM++;
					insertNode(&nodePointer, element, 0); ADD++;
				}
			}LOG++; ADD++; ADD++; MATH++; MATH++;
			if ((nodePointer->dataArray[N - 1] == NULL) || (*element < (*(nodePointer->dataArray[N - 1]))))
			{
				for (i = 0; i < N; i++)
				{
					ID++; COM++; LOG++; ADD++; ADD++;
					if ((nodePointer->dataArray[i] != NULL) && (*element >(*(nodePointer->dataArray[i]))))
					{
						COM++; LOG++;
						continue;
					}
					else if (nodePointer->dataArray[i] == NULL)
					{
						COM++;
						nodePointer->dataArray[i] = element; AS++;
						return;
					}
					else if (*element <= *(nodePointer->dataArray[i]))
					{
						COM++; ADD++; ADD++;
						bufElement = nodePointer->dataArray[i]; AS++;
						nodePointer->dataArray[i] = element; AS++;
						element = bufElement; AS++;
						countOverflow = i; AS++;
					}
					if (countOverflow == 3)
					{
						COM++;
						insertNode(&(nodePointer->rightBranch), element, 0); ADD++;
						return;
					}
				} AS++;
			}
		}
	}ADD++; ADD++;
	if (*element < *(nodePointer->dataArray[0]))
	{
		COM++;
		countOverflow = 0;
		if (nodePointer->leftBranch != NULL)
		{
			COM++;
			insertElement(nodePointer->leftBranch, element);
		}
		else if (nodePointer->leftBranch == NULL)
		{
			COM++;
			for (i = 0; i < N; i++)
			{
				ID++; COM++;
				if (nodePointer->dataArray[i] == NULL)
				{
					COM++;
					nodePointer->dataArray[i] = element; AS++;
					return;
				}ADD++; ADD++;
				if (*element < *(nodePointer->dataArray[i]))
				{
					COM++;
					bufElement = nodePointer->dataArray[i]; AS++;
					nodePointer->dataArray[i] = element; AS++;
					element = bufElement; AS++;
					countOverflow = i; AS++;
				}
				if (countOverflow == 3)
				{
					COM++;
					insertNode(&(nodePointer->rightBranch), element, 0); ADD++;
					return;
				}
			} AS++;
		}
	}
}

void insertElementToTree(Tree **nodePointer, int **objectsSecond)
{
	int i;
	for (i = 0; i < OBJ; i++)
	{
		ID++; COM++;
		if (objectsSecond[i][0] != 1)
		{
			COM++; ADD++; ADD++;
			insertElement(*nodePointer, &(objectsSecond[i][1])); ADD++; ADD++;
		}
		else
		{
			continue;
		}
	}
}

int findMaxDeep(Tree *nodePointer, int amountNodes)
{
	int left = 0, right = 0; AS++; AS++;
	if (nodePointer->leftBranch != NULL)
	{
		left = findMaxDeep(nodePointer->leftBranch, amountNodes + 1); AS++; COM++;
	}
	if (nodePointer->rightBranch != NULL)
	{
		right = findMaxDeep(nodePointer->rightBranch, amountNodes + 1); AS++; COM++;
	}LOG++; LOG++;
	if (left >= amountNodes&&left >= right)
	{
		COM++;
		return left;
	}
	else if (right >= amountNodes&&right >= left)
	{
		COM++;
		return right;
	}
	else return amountNodes;
}

int findLeftBranchLn(Tree *nodePointer, int amountNodes)
{
	int left = 0, right = 0; AS++; AS++;
	if (nodePointer->leftBranch != NULL)
	{
		left = findLeftBranchLn(nodePointer->leftBranch, amountNodes + 1); AS++; COM++; MATH++;
	}
	if (nodePointer->rightBranch != NULL)
	{
		right = findLeftBranchLn(nodePointer->rightBranch, amountNodes + 1); AS++; COM++; MATH++;
	}
	LOG++; LOG++;
	if (left >= amountNodes&&left >= right)
	{
		COM++; return left;
	}
	else if (right >= amountNodes&&right >= left)
	{
		COM++; return right;
	}
	else return amountNodes;
}

int findRightBranchLn(Tree *nodePointer, int amountNodes)
{
	int left = 0, right = 0; AS++; AS++;
	if (nodePointer->leftBranch != NULL)
	{
		left = findRightBranchLn(nodePointer->leftBranch, amountNodes + 1); AS++; COM++; MATH++;
	}
	if (nodePointer->rightBranch != NULL)
	{
		right = findRightBranchLn(nodePointer->rightBranch, amountNodes + 1); AS++; COM++; MATH++;
	}LOG++; LOG++;
	if (left >= amountNodes&&left >= right)
	{
		COM++;
		return left;
	}
	else if (right >= amountNodes&&right >= left)
	{
		COM++;
		return right;
	}
	else return amountNodes;
}

void bypassTreeInOrder(Tree *nodePointer)
{
	int i;
	if (nodePointer != NULL)
	{
		COM++;
		bypassTreeInOrder(nodePointer->leftBranch);
		for (i = 0; i < N; i++)
		{
			ID++; COM++;
			if (nodePointer->dataArray[i] != NULL)
			{
				COM++;
				printf("|%p {%4d}| ", nodePointer->dataArray[i], *(nodePointer->dataArray[i])); ADD++;
			}
			else if (nodePointer->dataArray[i] == NULL)
			{
				COM++;
				printf("|  NULL   {....}| ");
			}

		}
		printf("\n");
		bypassTreeInOrder(nodePointer->rightBranch);
	}
}

void countNodesInnerFunc(Tree *nodePointer, int *amountNodes)
{
	if (nodePointer != NULL)
	{
		COM++;
		countNodesInnerFunc(nodePointer->leftBranch, amountNodes);
		if (nodePointer->dataArray[0] != NULL)
		{
			*amountNodes = *amountNodes + 1; AS++; COM++; ADD++; ADD++;
		}
		countNodesInnerFunc(nodePointer->rightBranch, amountNodes);
	}
}

void countNodes(Tree *nodePointer, int *amountNodes)
{
	*amountNodes = 0; AS++;
	countNodesInnerFunc(nodePointer, amountNodes);
}

void objectsFirstAndAdded(int *objectsFirst, int *addedElements, int *firstAndAddedElements)
{
	int i;
	for (i = 0; i < OBJ; i++)
	{
		ID++; COM++;
		*(firstAndAddedElements + i) = *(objectsFirst + i); AS++; ADD++; ADD++; MATH++; MATH++;
	}
	for (i = OBJ; i < (OBJ + OBJADD); i++)
	{
		ID++; COM++;
		*(firstAndAddedElements + i) = *(addedElements + (i - OBJ)); AS++; ADD++; ADD++; MATH++; MATH++; MATH++;
	} AS++;
}

void objectsFirstAndAddedToElemBalance(int *firstAndAddedElements, int **elementArrayForBalanceTree)
{
	int i;
	sortObjects(firstAndAddedElements, 0, (OBJ + OBJADD - 1)); MATH++; MATH++;
	for (i = 0; i < (OBJ + OBJADD); i++)
	{
		ID++; COM++; MATH++;
		elementArrayForBalanceTree[i][0] = 0; AS++;
		elementArrayForBalanceTree[i][1] = *(firstAndAddedElements + i); AS++; ADD++; MATH++;
	} AS++;
}

void deleteTreeInOrder(Tree *nodePointer)
{
	if (nodePointer != NULL)
	{
		COM++;
		if (nodePointer->leftBranch != NULL)
		{
			deleteTreeInOrder(nodePointer->leftBranch); COM++;
		}
		if (nodePointer->rightBranch != NULL)
		{
			deleteTreeInOrder(nodePointer->rightBranch); COM++;
		}LOG++;
		if ((nodePointer->leftBranch == NULL) && (nodePointer->rightBranch == NULL))
		{
			free(nodePointer); COM++;
		}
	}
}

void showStatistic(Tree *nodePointer, int *amountNodes)
{
	countNodes(nodePointer, amountNodes);
	printf("\n");
	printf("Характеристики дерева:\n");
	printf("Колличество узлов: %d\n", *amountNodes); ADD++;
	printf("Глубина дерева: %d\n", findMaxDeep(nodePointer, 1));
	printf("Глубина левой ветви дерева: %d\n", findLeftBranchLn(nodePointer->leftBranch, 2));
	printf("Глубина правой ветви дерева: %d\n", findRightBranchLn(nodePointer->rightBranch, 2));
	MATH++;
	if ((findLeftBranchLn(nodePointer->leftBranch, 2) - findRightBranchLn(nodePointer->rightBranch, 2)) < 0)
	{
		COM++; MATH++;
		if ((findRightBranchLn(nodePointer->rightBranch, 2) - findLeftBranchLn(nodePointer->leftBranch, 2)) > 1)
		{
			COM++;
			printf("Дерево несбалансированно.\n");
		}
		else
		{
			printf("Дерево сбалансированно.\n");
		}
	}
	else if ((findLeftBranchLn(nodePointer->leftBranch, 2) - findRightBranchLn(nodePointer->rightBranch, 2)) > 1)
	{
		COM++; MATH++;
		printf("Дерево несбалансированно.\n");
	}
	else
	{
		printf("Дерево сбалансированно.\n");
	}
	printf("\n");
}

void showLabor()
{
	ID = ID + COM + LOG + MATH + AS + ADD;
	printf("%10d - Начальное количество объектов\n", OBJ);
	printf("%10u - Количество инкрементов и декрементов (++ --)\n", ID);
	printf("%10u - Количество операций сравнения (< > <= >= == != )\n", COM);
	printf("%10u - Количество логических операций ( && ||)\n", LOG);
	printf("%10u - Количество арифметических операций ( + - * / % ++ -- )\n", MATH);
	printf("%10u - Количество операций присваивания ( = += -= *= /= )\n", AS + 1);
	printf("%10u - Количество операций с адресами & * и sazeof\n", ADD);
	printf("%10u - Количество всех операций\n", (2 * ID + COM + LOG + MATH + AS + ADD));
	printf("%10u - \"Грязное\" время работы программы\n", TIME);
}

void bypassTreeInOrderHorizontal(Tree *nodePointer, int deep)
{
	int i, j;
	if (nodePointer != NULL)
	{
		bypassTreeInOrderHorizontal(nodePointer->leftBranch, deep + 1);
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < deep; j++)
			{
				printf("                  ");
			}
			if (nodePointer->dataArray[i] != NULL)
			{
				printf("|%p {%4d}|\n", nodePointer->dataArray[i], *(nodePointer->dataArray[i]));
			}
			else if (nodePointer->dataArray[i] == NULL)
			{
				printf("|  NULL   {....}|\n");
			}
		}
		printf("\n");
		bypassTreeInOrderHorizontal(nodePointer->rightBranch, deep + 1);
	}
}