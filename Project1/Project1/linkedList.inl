#pragma once
#include <cassert>

#pragma region Node

// データを持つノード用
template <typename T>
LinkedList<T>::Node::Node(const T& value) : data(value), prev(nullptr), next(nullptr)
{
}

// ダミーノード用
template <typename T>
LinkedList<T>::Node::Node() : data(T()), prev(nullptr), next(nullptr)
{
}

#pragma endregion

#pragma region ConstIterator

// プライベートコンストラクタ
template <typename T>
LinkedList<T>::ConstIterator::ConstIterator(const Node* node, const LinkedList<T>* list) : mNode(node), mList(list)
{
}

// デフォルトコンストラクタ
template <typename T>
LinkedList<T>::ConstIterator::ConstIterator() : mNode(nullptr), mList(nullptr)
{
}

// イテレータの指す要素を取得(const版)
template <typename T>
const T& LinkedList<T>::ConstIterator::operator*() const
{
	assert(mNode);
	assert(mList && mNode != mList->mDummy);
	return mNode->data;
}

// アロー演算子(const版)
template <typename T>
const T* LinkedList<T>::ConstIterator::operator->() const
{
	assert(mNode);
	return &(mNode->data);
}

// 前置インクリメント
template <typename T>
typename LinkedList<T>::ConstIterator& LinkedList<T>::ConstIterator::operator++()
{
	assert(mNode);
	assert(mList && mNode != mList->mDummy);
	mNode = mNode->next;
	return *this;
}

// 後置インクリメント
template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::ConstIterator::operator++(int)
{
	assert(mNode);
	assert(mList && mNode != mList->mDummy);
	ConstIterator temp = *this;
	mNode = mNode->next;
	return temp;
}

// 前置デクリメント
template <typename T>
typename LinkedList<T>::ConstIterator& LinkedList<T>::ConstIterator::operator--()
{
	assert(mNode);
	// デクリメント後がダミーノードを指さないことを確認（--Begin()を防ぐ）
	assert(mList && mNode->prev != mList->mDummy);
	mNode = mNode->prev;
	return *this;
}

// 後置デクリメント
template <typename T>
typename LinkedList<T>::ConstIterator LinkedList<T>::ConstIterator::operator--(int)
{
	assert(mNode);
	// デクリメント後がダミーノードを指さないことを確認（--Begin()を防ぐ）
	assert(mList && mNode->prev != mList->mDummy);
	ConstIterator temp = *this;
	mNode = mNode->prev;
	return temp;
}

// 等価比較
template <typename T>
bool LinkedList<T>::ConstIterator::operator==(const ConstIterator& other) const
{
	return mNode == other.mNode;
}

// 非等価比較
template <typename T>
bool LinkedList<T>::ConstIterator::operator!=(const ConstIterator& other) const
{
	return mNode != other.mNode;
}

// 代入演算子
template <typename T>
typename LinkedList<T>::ConstIterator& LinkedList<T>::ConstIterator::operator=(const ConstIterator& other)
{
	mNode = other.mNode;
	mList = other.mList;
	return *this;
}

#pragma endregion

#pragma region Iterator

// プライベートコンストラクタ
template <typename T>
LinkedList<T>::Iterator::Iterator(Node* node, const LinkedList<T>* list) : ConstIterator(node, list)
{
}

// デフォルトコンストラクタ
template <typename T>
LinkedList<T>::Iterator::Iterator() : ConstIterator(nullptr, nullptr)
{
}

// イテレータの指す要素を取得(非const版)
template <typename T>
T& LinkedList<T>::Iterator::operator*()
{
	return const_cast<T&>(ConstIterator::operator*());
}

// アロー演算子
template <typename T>
T* LinkedList<T>::Iterator::operator->()
{
	return const_cast<T*>(ConstIterator::operator->());
}

#pragma endregion

#pragma region LinkedList

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
bool LinkedList<T>::Insert(const ConstIterator& it, const T& value)
{
	// リストが一致しない場合は挿入しない
	if (it.mList != this)
	{
		return false;
	}

	Node* current = const_cast<Node*>(it.mNode);
	assert(current);

	Node* newNode = new Node(value);

	newNode->next = current;
	newNode->prev = current->prev;
	current->prev->next = newNode;
	current->prev = newNode;

	mCount++;
	return true;
}


// イテレータが指す位置の要素を削除
template <typename T>
bool LinkedList<T>::Remove(const ConstIterator& it)
{
	Node* node = const_cast<Node*>(it.mNode);
	if (!node || node == mDummy)
	{
		return false;
	}

	// リストが一致しない場合は削除しない
	if (it.mList != this)
	{
		return false;
	}

	Node* nodeToDelete = node;

	nodeToDelete->prev->next = nodeToDelete->next;
	nodeToDelete->next->prev = nodeToDelete->prev;

	delete nodeToDelete;
	mCount--;

	return true;
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

#pragma endregion