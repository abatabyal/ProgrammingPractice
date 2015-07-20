#if 1

#include <iostream>
//#include <conio.h>
#include <iomanip>
#include <unistd.h>
#include <assert.h>

using namespace std;

void *memcpy1(void *dest, void *src, size_t t);
void *memcpy2(void *dest, void *src, size_t t);
void *memmove1(void *dest, void *src, size_t t);
void *memset1(void *dest, int val, size_t t);
void strcpy1(char dest[], char src[]);
int atoi1(char *str);
double atof1(char* str);

struct metaBlock{
	size_t size;
	struct metaBlock* next;
	bool isFree;
};

#define METASIZE sizeof(struct metaBlock)
struct metaBlock *globalStart = NULL;			//global pointer : points to the start of heap
void* malloc1(size_t size);
void free1(void* ptr);
struct metaBlock* requestSpace(struct metaBlock *last, size_t size);
struct metaBlock* findFreeBlock(struct metaBlock **last, size_t size);


int main()
{
	/*char dest[50];
	char str1[] = "0123456789abcdefghijklmnopqrstuvwxyzab";
	memcpy1(dest, str1, strlen(str1)+1);
	memcpy2(dest, str1, strlen(str1)+1);
	memmove1(dest, str1, strlen(str1)+1);
	memset1(dest, 0, strlen(str1) + 1);
	strcpy1(dest, str1);

	char str[] = "-000123100";
	cout << atoi1(str);*/

	char str[] = "-.100";
	cout << std::setprecision(9) << atof1(str);

//	_getch();
}

void* malloc1(size_t size)
{
	struct metaBlock *block;
	if (globalStart == NULL)
	{
		block = requestSpace(NULL, size);
		if (block == NULL)
			return NULL;
		globalStart = block;
	}
	else
	{
		struct metaBlock *last = globalStart;
		block = findFreeBlock(&last, size);
		if (block == NULL)
		{
			block = requestSpace(last, size);
			if (block == NULL)
				return NULL;
		}
		else
			block->isFree = false;			//split block is missing : have to implement
	}
	return (block + 1);
}

void free1(void* ptr)
{
	if (ptr == NULL)
		return;

	struct metaBlock *block = (struct metaBlock*)ptr - 1;
	assert(block->isFree == false);
	block->isFree = true;
}

struct metaBlock* findFreeBlock(struct metaBlock **last, size_t size)
{
	struct metaBlock* current = globalStart;
	while (current && !(current->isFree && current->size >= size))
	{
		*last = current;
		current = current->next;
	}
	return current;
}

struct metaBlock* requestSpace(struct metaBlock *last, size_t size)
{
	struct metaBlock* block = (struct metaBlock*) sbrk(size + METASIZE);	//doubt : sbrk return address : not confirmed

	if (block == NULL)
		return NULL;

	if (last)
		last->next = block;

	block->size = size;
	block->isFree = false;
	block->next = NULL;

	return block;
}

double atof1(char* str)
{
	int signMultiplier = 1;
	if (*str == '-')
	{
		str++;
		signMultiplier = -1;
	}

	bool flag = false;
	int msb = 0;
	int lsb = 0;
	int lsbDivisor = 1;
	while (*str)
	{
		if (*str == '.')
			flag = true;
		else
		{
			if (!flag)
			{
				msb = msb * 10 + (*str - '0');
			}
			else
			{
				lsb = lsb * 10 + (*str - '0');
				lsbDivisor *= 10;
			}
		}
		str++;
	}

	double num = 0;
	num = msb + (double)lsb / (double)lsbDivisor;
	return num*signMultiplier;
}

int atoi1(char *str)
{
	int num = 0;
	int i = 0;
	bool flag = false;
	if (str[0] == '-')
	{
		flag = true;
		i++;
	}
	for (; i < strlen(str); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			num = num * 10 + str[i] - '0';
		}
		else
		{
			cout << "Invalid characters " << endl;
			return 0;
		}
	}
	
	if (flag)
		num = -1 * num;
	return num;
}

void strcpy1(char dest[], char src[])
{
	int i = 0;
	while (true)
	{
		dest[i] = src[i];
		if (dest[i] == '\0')
			break;
		i++;
	}
}

void *memset1(void *dest, int val, size_t t)
{
	char *dest1 = (char*)dest;
	for (int i = 0; i < t; i++)
		dest1[i] = (char)val;

	return dest;
}

void *memmove1(void *dest, void *src, size_t t)
{
	//stackoverflow.com/questions/3572309/memmove-implementation-in-c
	char *dest1 = (char*)dest;
	char *src1 = (char*)src;

	if (src1 + t > dest1)
	{
		while (t--)
			dest1[t] = src1[t];
	}
	else
	{
		for (int i = 0; i < t; i++)
			dest1[i] = src1[i];
	}

	return dest1;
}

void *memcpy1(void *dest, void *src, size_t t)
{
	char *dest1 = (char*)dest;
	char *src1 = (char*)src;

	for (int i = 0; i < t; i++)
		dest1[i] = src1[i];

	return dest;
}

void *memcpy2(void *dest, void *src, size_t t)
{
	int *dest1 = (int*)dest;
	int *src1 = (int*)src;
	int i = 0;
	for (i = 0; i < t/4; i++)
		dest1[i] = src1[i];

	char *dest2 = (char*)&dest1[i];
	char *src2 = (char*)&src1[i];
	for (i = 0; i < t%4; i++)
		dest2[i] = src2[i];

	return dest;
}

#endif
