#pragma once

#include "../Project1/linkedList.h"

// QuickSortの補助関数
template <typename T>
void QuickSortHelper(LinkedList<T>& list, typename LinkedList<T>::ConstIterator begin, typename LinkedList<T>::ConstIterator end)
{

	if (*begin > *end)
	{
		list.Swap(begin, end);

		auto temp = begin;
		begin = end;
		end = temp;
	}

	auto leftPivot = begin;
	auto rightPivot = end;

	auto less = leftPivot;
	++less;
	auto great = rightPivot;
	--great;

	auto k = less;
	while (k != rightPivot)
	{
		auto greatNext = great;
		++greatNext;
		if (k == greatNext)
			break;

		if (*k <= *leftPivot)
		{
			list.Swap(k, less);

			bool greatEqualsK = (great == k);

			auto temp = k;
			k = less;
			less = temp;

			if (great == k)
			{
				great = k;
			}

			++less;
			++k;
		}
		else if (*k >= *rightPivot)
		{
			list.Swap(k, great);

			bool lessEqualsK = (less == k);

			auto temp = k;
			k = great;
			great = temp;

			if (lessEqualsK)
			{
				less = k;
			}

			--great;
		}
		else
		{
			++k;
		}
	}

	++great;
	--less;
	list.Swap(leftPivot, less);

	auto temp = leftPivot;
	leftPivot = less;
	less = temp;

	list.Swap(rightPivot, great);

	temp = rightPivot;
	rightPivot = great;
	great = temp;

	auto leftEnd = less;
	if (leftPivot != less && leftPivot != --leftEnd)
	{
		QuickSortHelper(list, leftPivot, leftEnd);
	}

	auto midBegin = less;
	++midBegin;
	auto midEnd = great;
	if (midBegin != great && midBegin != --midEnd)
	{
		QuickSortHelper(list, midBegin, midEnd);
	}

	auto rightBegin = great;
	if (rightBegin != rightPivot)
	{
		QuickSortHelper(list, rightBegin, rightPivot);
	}
}

//クイックソートでリストをソート
template <typename T>
void Sort::QuickSort(LinkedList<T>& list)
{
	// 空リストまたは1要素の場合は何もしない
	if (list.Count() <= 1)
	{
		return;
	}

	auto begin = list.CBegin();
	auto end = list.CEnd();
	--end;
	QuickSortHelper(list, begin, end);
}
