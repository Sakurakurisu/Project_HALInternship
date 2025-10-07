#pragma once
#include <cassert>

// コンストラクタ
template <typename T>
LinkedList<T>::LinkedList() : mDummy(new Node()), mCount(0)
{
	// ダミーノードを自分自身に循環させる（空リスト状態）
	mDummy->next = mDummy;
	mDummy->prev = mDummy;
}

// デストラクタ
template <typename T>
LinkedList<T>::~LinkedList()
{
	Clean();
	delete mDummy;
}

// イテレータが指す位置の前に要素を挿入
template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Insert(const ConstIterator& it, const T& value)
{
	Node* current = const_cast<Node*>(it.mNode);
#ifndef NDEBUG
	assert(current);
#endif

	if (it.mList != this)
	{
		return Iterator(mDummy, this);
	}

	Node* newNode = new Node(value);

	newNode->next = current;
	newNode->prev = current->prev;
	current->prev->next = newNode;
	current->prev = newNode;

	mCount++;
	return Iterator(newNode, this);
}


// イテレータが指す位置の要素を削除
template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Remove(const ConstIterator& it)
{
	Node* node = const_cast<Node*>(it.mNode);
	if (!node || node == mDummy)
	{
		return Iterator(mDummy, this);
	}

	// リストが一致しない場合は削除しない
	if (it.mList != this)
	{
		return Iterator(mDummy, this);
	}

	Node* nodeToDelete = node;
	Node* nextNode = nodeToDelete->next;

	nodeToDelete->prev->next = nodeToDelete->next;
	nodeToDelete->next->prev = nodeToDelete->prev;

	delete nodeToDelete;
	mCount--;

	return Iterator(nextNode, this);
}


// 先頭イテレータ取得
template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Begin()
{
	return Iterator(mDummy->next, this);
}

// 末尾の次を指すイテレータ取得
template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::End()
{
	return Iterator(mDummy, this);
}

// 末尾の次を指すイテレータ取得
template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::CBegin() const
{
	return ConstIterator(mDummy->next, this);
}

// 末尾の次を指すコンストイテレータ取得（明示的）
template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::CEnd() const
{
	return ConstIterator(mDummy, this);
}

// リスト内の要素数を取得
template <typename T>
size_t LinkedList<T>::Count() const
{
	return mCount;
}

// リストに要素が存在するかチェック
template <typename T>
bool LinkedList<T>::Any() const
{
	return mCount != 0;
}

// リストのすべての要素を削除してメモリを解放
template <typename T>
void LinkedList<T>::Clean()
{
	// ダミーノードの次から順に削除（ダミーノード自体は削除しない）
	Node* current = mDummy->next;
	while (current != mDummy)
	{
		Node* temp = current;
		current = current->next;
		delete temp;
	}

	// ダミーノードを空リスト状態に戻す
	mDummy->next = mDummy;
	mDummy->prev = mDummy;
	mCount = 0;
}