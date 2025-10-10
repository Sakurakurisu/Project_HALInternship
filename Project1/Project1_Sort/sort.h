#pragma once
#include "../Project1/linkedList.h"

/**
 * @brief ソートアルゴリズムを提供するクラス
 */
class Sort
{
public:
	/**
	 * @brief クイックソートでリストをソート
	 * @tparam T リストに格納される要素の型
	 * @param list ソート対象のリスト
	 */
	template <typename T>
	static void QuickSort(LinkedList<T>& list);
};

// QuickSortの補助関数（グローバル関数として定義）
template <typename T>
void QuickSortHelper(LinkedList<T>& list, typename LinkedList<T>::ConstIterator begin,
                     typename LinkedList<T>::ConstIterator end);

#include "sort.inl"
