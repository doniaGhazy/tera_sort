#ifndef QUICKSORT_H
#define quickSort_H
#include <algorithm>
template <typename ITEM>
class quickSort
{
  private:
	void quick_Sort(ITEM **items, int left, int right);
	void insertionSort (ITEM ** items, int list_size);

  public:
	void quick_Sort(ITEM** items, int list_size);

};
template <typename ITEM>
ITEM** median3(ITEM** items, int left, int right)
{
	int center = (left + right) / 2;
	if (items[center] < items[left])
		std::swap(items[left], items[center]);
	if (items[right] < items[left])
		std::swap(items[left], items[right]);
	if (items[right] < items[center])
		std::swap(items[center], items[right]);
		std::swap(items[center],items[right - 1]);
	return &items[right - 1];
}

template <typename ITEM>
void quickSort<ITEM>::quick_Sort(ITEM **items, int left, int right)
{
	if (left + 50 <= right)
	{//here
		 ITEM** pivot = median3(items, left, right);
		int i = left, j = right - 1;
		for (;;)
		{
			while (&items[++i] < pivot)
				;
			while (pivot < &items[--j])
				;
			if (i < j)
			std::swap(items[i], items[j]);
			else
				break;
		}
		std::swap(items[i], items[right - 1]);
		quick_Sort(items, left, i - 1);
		quick_Sort(items, i + 1, right);
	}
	else
		insertionSort(items + left, right - left + 1);
}

template <typename ITEM>
void quickSort<ITEM>::quick_Sort(ITEM** items, int list_size)
{
	quick_Sort(items, 0, list_size - 1);
}

template <typename ITEM>
void quickSort<ITEM>::insertionSort (ITEM ** items, int list_size)
{
	if ( list_size <= 1 ) return;
	for ( int i = 1 ; i < list_size ; i ++)
	{
		ITEM *tmp = items[i];
		int j = i;
		for ( ; j > 0 && tmp < items[j-1] ; j -- )
			items[j] = items[j-1];
		items[j]= tmp;
	}
}
#endif
