#pragma once
#include<iostream>
#include<cstdio>

const int MAXSIZE = 50;

typedef struct array {
	int data[MAXSIZE];
	int size;
}Array, * ArrPointer;

Array createArray(int a[],int n)
{
	Array arr;
	arr.size= n;
	for (int i = 0; i < n; i++)
	{
		arr.data[i] = a[i];
	}
	return arr;
}

void OutputArray(Array arr)
{
	for (int i = 0; i < arr.size; i++)
		std::cout << arr.data[i]<<" ";
	std::cout << std::endl;
}

int getBinaryIndex(Array arr,int x)
{
	int left = 0;
	int right = arr.size - 1;
	while (left<=right)
	{
		int mid = (left + right) / 2;
		if (arr.data[mid] < x)
			left = mid + 1;
		else if (arr.data[mid] > x)
			right = mid - 1;
		else
			return mid;
	}
	return -1;
}

int deletMin(Array &arr)
{
	if (arr.size == 0)
		return -1;
	int minVal = arr.data[0];
	int index = 0;
	for (int i = 1; i < arr.size; i++)
	{
		if (minVal > arr.data[i])
		{
			minVal = arr.data[i];
			index = i;
		}
	}
	if (index != arr.size - 1)
	{
		arr.data[index] = arr.data[arr.size - 1];
	}
	arr.data[arr.size - 1] = -1;
	arr.size--;
	return minVal;
}

void inverseArr(Array &arr,int left,int right)
{
	for (int i = 0; i < (right- left+1) / 2; i++)
	{
		int tmp = arr.data[i+left];
		arr.data[i+left] = arr.data[right - i];
		arr.data[right - i] = tmp;
	}
	OutputArray(arr);
}

void converseArr(Array& arr, int p)
{
	inverseArr(arr, 0, p-1);
	inverseArr(arr, p, arr.size-1);
	inverseArr(arr, 0, arr.size-1);
	OutputArray(arr);
}

void deletX(Array &arr,int x)
{
	int index = arr.size -1;
	for (int i = 0; i <= index; i++)
	{
		if (arr.data[i] == x)
		{
			while (index > i && arr.data[index] == x)
			{
				arr.data[index] = 0;
				index--;
				arr.size--;
			}
			arr.data[i] = arr.data[index--];
			arr.size--;
		}
	}
}

void deletBetweenXYSorted(Array& arr, int x, int y)
{
	int left = getBinaryIndex(arr,x);
	int right = getBinaryIndex(arr, y);
	if (left == -1 || right == 1 || left > right)
		return;
	right++;
	while (right < arr.size)
	{
		arr.data[left++] = arr.data[right++];
	}
	arr.size -= right - left;
}

void deletBetweenXYUnsorted(Array& arr, int x, int y)
{
	int size = arr.size;
	int bag[MAXSIZE] = {};
	int cnt = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr.data[i] >= x && arr.data[i] <= y)
			cnt++;
		bag[i] = cnt;
	}
	for (int i = 0; i < size; i++)
	{
		if (arr.data[i]<x || arr.data[i]>y)
			arr.data[i - bag[i]] = arr.data[i];
	}
	arr.size -= cnt;
	OutputArray(arr);
}
void deletRepeatElement(Array& arr)
{
	int last = 1;
	int pre = arr.data[0];
	int size = arr.size;
	for (int i = 1; i <size; i++)
	{
		if (arr.data[i] != pre)
		{
			pre = arr.data[i];
			arr.data[last++] = arr.data[i];
		}
		else
			arr.size--;
	}
	OutputArray(arr);
}

void Merge(Array a, Array b)
{
	int res[2 * MAXSIZE] = {};
	int index = 0;
	int index1 = 0;
	int index2 = 0;
	while (index1 < a.size && index2 < b.size)
	{
		if (a.data[index1] < b.data[index2])
			res[index++] = a.data[index1++];
		else
			res[index++] = b.data[index2++];
	}
	if(index1<a.size)
		res[index++] = a.data[index1++];
	if(index2<b.size)
		res[index++] = b.data[index2++];
	for (int i = 0; i < a.size + b.size; i++)
		std::cout << res[i]<<" ";
}

void insertX(Array arr, int x)
{
	int left = 0;
	int right = arr.size - 1;
	int mid = 0;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (arr.data[mid] < x)
			left = mid + 1;
		else if (arr.data[mid] > x)
			right = mid - 1;
		else
			break;
	}
	if (left <= right)//若存在则与后继元素换序
	{
		int tmp = arr.data[mid];
		arr.data[mid] = arr.data[mid + 1];
		arr.data[mid + 1] = tmp;
	}
	else//若不存在则插入有序表中
	{
		left = arr.data[mid] > x ? mid : mid + 1;
		right = arr.size-1;
		while (right>=left)
		{
			arr.data[right + 1] = arr.data[right--];
		}
		arr.data[left] = x;
		arr.size++;
	}
	OutputArray(arr);
}

int SearchMedian(int a[], int b[], int n)
{
	int al = 0, ar = n - 1;
	int bl = 0, br = n - 1;
	while (al != ar || bl != br)
	{
		int ma = (al + ar) / 2;
		int mb = (bl + br) / 2;
		if (a[ma] == b[mb])
			return a[ma];
		if (a[ma] < b[mb])
		{
			if ((al + ar) % 2 == 0)
			{
				al = ma;
				br = mb;
			}
			else
			{
				al = ma + 1;
				br = mb;
			}
		}
		else
		{
			if ((al + ar) % 2 == 0)
			{
				ar = ma;
				bl = mb;
			}
			else
			{
				ar = ma ;
				bl = mb + 1;
			}
		}
		return a[al] < b[bl] ? a[al] : b[bl];
	}
	return -1;
}

int getMinPositiveInt(Array& arr)
{
	int b[MAXSIZE] = {};
	memset(b, 0, sizeof(int) * MAXSIZE);
	for (int i = 0; i < arr.size; i++)
		if (arr.data[i] > 0)
			b[arr.data[i] - 1] = 1;
	for (int i = 0; i < MAXSIZE; i++)
		if (b[i] != 0)
			return i+1;
	return MAXSIZE + 1;
}

bool minest(int a, int b, int c)
{
	if (a < b && a < c)	return true;
	return false;
}

int findMinTrip(int a[], int n, int b[], int m, int c[], int p)
{
	int i = 0, j = 0, k = 0, Dmin = 0x7fffffff, D;
	while (i < n && j < m && k < p && Dmin>0)
	{
		D = abs(a[i] - b[j]) + abs(b[j] - c[k]) + abs(a[i] - c[k]);
		Dmin = Dmin > D ? D : Dmin;
		if (minest(a[i], b[j], c[k]))
			i++;
		else if (minest(b[j], c[k], a[i]))
			j++;
		else
			k++;
	}
	return Dmin;
}