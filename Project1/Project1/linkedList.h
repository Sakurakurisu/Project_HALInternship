#pragma once
#include <cassert>

/// <summary>
/// 双方向リストのテンプレートクラス
/// </summary>
/// <typeparam name="T">リストに格納する要素の型</typeparam>
template <typename T>
class LinkedList
{
private:
	// ノード構造体
	struct Node
	{
		T data;
		Node* prev;
		Node* next;

		// データを持つノード用
		Node(const T& value) : data(value), prev(nullptr), next(nullptr)
		{
		}

		// ダミーノード用
		Node() : data(T()), prev(nullptr), next(nullptr)
		{
		}
	};

	// ダミーノード（末尾の次を指す）
	Node* mDummy;
	size_t mCount;

public:
	/// <summary>
	/// コンストイテレータクラス
	/// </summary>
	class ConstIterator
	{
	private:
		const Node* mNode;
		const LinkedList<T>* mList;
		friend class LinkedList<T>;

		ConstIterator(const Node* node, const LinkedList<T>* list) : mNode(node), mList(list)
		{
		}

	public:
		ConstIterator() : mNode(nullptr), mList(nullptr)
		{
		}

		/// <summary>
		/// イテレータの指す要素を取得（const版）
		/// </summary>
		const T& operator*() const
		{
			assert(mNode);
			assert(mList && mNode != mList->mDummy);
			return mNode->data;
		}

		/// <summary>
		/// アロー演算子（const版）
		/// </summary>
		const T* operator->() const
		{
			assert(mNode);
			return &(mNode->data);
		}

		/// <summary>
		/// 前置インクリメント
		/// </summary>
		ConstIterator& operator++()
		{
			assert(mNode);
			assert(mList && mNode != mList->mDummy);
			mNode = mNode->next;
			return *this;
		}

		/// <summary>
		/// 後置インクリメント
		/// </summary>
		ConstIterator operator++(int)
		{
			assert(mNode);
			assert(mList && mNode != mList->mDummy);
			ConstIterator temp = *this;
			mNode = mNode->next;
			return temp;
		}

		/// <summary>
		/// 前置デクリメント
		/// </summary>
		ConstIterator& operator--()
		{
			assert(mNode);
			// デクリメント後がダミーノードを指さないことを確認（--Begin()を防ぐ）
			assert(mList && mNode->prev != mList->mDummy);
			mNode = mNode->prev;
			return *this;
		}

		/// <summary>
		/// 後置デクリメント
		/// </summary>
		ConstIterator operator--(int)
		{
			assert(mNode);
			// デクリメント後がダミーノードを指さないことを確認（--Begin()を防ぐ）
			assert(mList && mNode->prev != mList->mDummy);
			ConstIterator temp = *this;
			mNode = mNode->prev;
			return temp;
		}

		/// <summary>
		/// 等価比較
		/// </summary>
		bool operator==(const ConstIterator& other) const
		{
			return mNode == other.mNode;
		}

		/// <summary>
		/// 非等価比較
		/// </summary>
		bool operator!=(const ConstIterator& other) const
		{
			return mNode != other.mNode;
		}

		/// <summary>
		/// 代入演算子
		/// </summary>
		ConstIterator& operator=(const ConstIterator& other)
		{
			mNode = other.mNode;
			mList = other.mList;
			return *this;
		}
	};

	/// <summary>
	/// イテレータクラス
	/// </summary>
	class Iterator : public ConstIterator
	{
	private:
		friend class LinkedList<T>;

		Iterator(Node* node, const LinkedList<T>* list) : ConstIterator(node, list)
		{
		}

	public:
		Iterator() : ConstIterator(nullptr, nullptr)
		{
		}

		/// <summary>
		/// イテレータの指す要素を取得（非const版）
		/// </summary>
		T& operator*()
		{
			return const_cast<T&>(ConstIterator::operator*());
		}

		/// <summary>
		/// アロー演算子
		/// </summary>
		T* operator->()
		{
			return const_cast<T*>(ConstIterator::operator->());
		}
	};

	LinkedList();

	~LinkedList();


	/// <summary>
	/// イテレータが指す位置の前に要素を挿入
	/// </summary>
	/// <param name="it">挿入位置を指すコンストイテレータ</param>
	/// <param name="value">挿入する値</param>
	/// <returns>挿入に成功した場合はtrue、失敗した場合はfalse</returns>
	bool Insert(const ConstIterator& it, const T& value);

	/// <summary>
	/// イテレータが指す位置の要素を削除
	/// </summary>
	/// <param name="it">削除する要素を指すコンストイテレータ</param>
	/// <returns>削除に成功した場合はtrue、失敗した場合はfalse</returns>
	bool Remove(const ConstIterator& it);

	/// <summary>
	/// 先頭イテレータ取得
	/// </summary>
	/// <returns>先頭を指すイテレータ</returns>
	Iterator Begin();

	/// <summary>
	/// 末尾の次を指すイテレータ取得
	/// </summary>
	/// <returns>末尾の次を指すイテレータ</returns>
	Iterator End();

	/// <summary>
	/// 先頭コンストイテレータ取得（明示的）
	/// </summary>
	/// <returns>先頭を指すコンストイテレータ</returns>
	ConstIterator CBegin() const;

	/// <summary>
	/// 末尾の次を指すコンストイテレータ取得（明示的）
	/// </summary>
	/// <returns>末尾の次を指すコンストイテレータ</returns>
	ConstIterator CEnd() const;

	/// <summary>
	/// リスト内の要素数を取得
	/// </summary>
	/// <returns>要素数</returns>
	size_t Count() const;

	/// <summary>
	/// リストに要素が存在するかチェック
	/// </summary>
	/// <returns>要素が存在する場合はtrue、空の場合はfalse</returns>
	bool Any() const;

	/// <summary>
	/// リストのすべての要素を削除してメモリを解放
	/// </summary>
	void Clean();
};

// テンプレート関数の実装をインクルード
#include "linkedList.inl"
