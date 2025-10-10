#pragma once
#include "../Project1/linkedList.h"

/**
 * @brief クイックソート(双軸)を実装するクラス
 */
class QuickSort
{
public:
	/**
	 * @brief クイックソートでリストをソート
	 * @tparam T リストに格納される要素の型
	 * @param list ソート対象のリスト
	 */
	template <typename T>
	static void Sort(LinkedList<T>& list);

private:
	/**
	 * @brief クイックソートの補助関数(再帰処理)
	 * @tparam T リストに格納される要素の型
	 * @param list ソート対象のリスト
	 * @param begin ソート範囲の開始イテレータ
	 * @param end ソート範囲の終了イテレータ
	 */
	template <typename T>
	static void SortHelper(LinkedList<T>& list, typename LinkedList<T>::ConstIterator begin,
	                       typename LinkedList<T>::ConstIterator end);
};

#include "quickSort.inl"
