#pragma once

#include "../Project1/linkedList.h"

// クイックソートの補助関数(双軸クイックソート)
template <typename T>
void QuickSort::SortHelper(LinkedList<T>& list, typename LinkedList<T>::ConstIterator begin, typename LinkedList<T>::ConstIterator end)
{
	// 左ピボットと右ピボットを比較し、必要なら交換(leftPivot <= rightPivotを保証)
	if (*begin > *end)
	{
		list.Swap(begin, end);
	}

	// 2つのピボット要素を設定
	auto leftPivot = begin;   
	auto rightPivot = end;    

	// 分割境界イテレータを初期化
	auto less = leftPivot;    
	++less;
	auto great = rightPivot;  
	--great;

	// 配列を走査するイテレータ
	auto k = less;
	while (k != rightPivot)
	{
		// kがgreatを超えたら終了
		auto greatNext = great;
		++greatNext;
		if (k == greatNext)
			break;

		// 現在の要素が左ピボット以下の場合
		if (*k <= *leftPivot)
		{
			// Swap後にgreatの位置を追跡するため、事前に確認
			bool greatEqualsK = (great == k);

			list.Swap(k, less);

			// greatがkと同じ位置だった場合、greatを更新
			if (greatEqualsK)
			{
				great = k;
			}

			++less;  // less境界を進める
			++k;     // 次の要素へ
		}
		// 現在の要素が右ピボット以上の場合
		else if (*k >= *rightPivot)
		{
			// Swap後にlessの位置を追跡するため、事前に確認
			bool lessEqualsK = (less == k);

			list.Swap(k, great);

			// lessがkと同じ位置だった場合、lessを更新
			if (lessEqualsK)
			{
				less = k;
			}

			--great;  // great境界を戻す
			// kは進めない(swapした要素をもう一度チェックする必要があるため)
		}
		// 現在の要素が2つのピボットの間にある場合
		else
		{
			++k;  // そのまま次の要素へ
		}
	}

	// ピボットを最終位置に移動
	++great;
	--less;
	list.Swap(leftPivot, less);   // 左ピボットを正しい位置へ

	list.Swap(rightPivot, great); // 右ピボットを正しい位置へ

	// 3つの部分配列に分割して再帰的にソート

	// 左側の部分配列を再帰的にソート (leftPivotより小さい要素)
	auto leftEnd = less;
	if (leftPivot != less && leftPivot != --leftEnd)
	{
		SortHelper(list, leftPivot, leftEnd);
	}

	// 中央の部分配列を再帰的にソート (2つのピボットの間の要素)
	auto midBegin = less;
	++midBegin;
	auto midEnd = great;
	if (midBegin != great && midBegin != --midEnd)
	{
		SortHelper(list, midBegin, midEnd);
	}

	// 右側の部分配列を再帰的にソート (rightPivotより大きい要素)
	auto rightBegin = great;
	++rightBegin;
	if (rightBegin != rightPivot)
	{
		SortHelper(list, rightBegin, rightPivot);
	}
}

// クイックソートでリストをソート
template <typename T>
void QuickSort::Sort(LinkedList<T>& list)
{
	// 空リストまたは1要素の場合は何もしない
	if (list.Count() <= 1)
	{
		return;
	}

	auto begin = list.CBegin();
	auto end = list.CEnd();
	--end;
	SortHelper(list, begin, end);
}
