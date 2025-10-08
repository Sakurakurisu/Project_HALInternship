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

	LinkedList() : mDummy(new Node()), mCount(0)
	{
		// ダミーノードを自分自身に循環させる（空リスト状態）
		mDummy->next = mDummy;
		mDummy->prev = mDummy;
	}

	~LinkedList()
	{
		Clean();

		delete mDummy;
	}


	/// <summary>
	/// イテレータが指す位置の要素を削除
	/// </summary>
	/// <param name="it">削除する要素を指すコンストイテレータ</param>
	/// <returns>削除に成功した場合はtrue、失敗した場合はfalse</returns>
	bool Remove(const ConstIterator& it)
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

	/// <summary>
	/// イテレータが指す位置の前に要素を挿入
	/// </summary>
	/// <param name="it">挿入位置を指すコンストイテレータ</param>
	/// <param name="value">挿入する値</param>
	/// <returns>挿入に成功した場合はtrue、失敗した場合はfalse</returns>
	bool Insert(const ConstIterator& it, const T& value)
	{
		Node* current = const_cast<Node*>(it.mNode);
		assert(current);

		if (it.mList != this)
		{
			return false;
		}

		Node* newNode = new Node(value);

		newNode->next = current;
		newNode->prev = current->prev;
		current->prev->next = newNode;
		current->prev = newNode;

		mCount++;
		return true;
	}

	/// <summary>
	/// 先頭イテレータ取得
	/// </summary>
	/// <returns>先頭を指すイテレータ</returns>
	Iterator Begin()
	{
		return Iterator(mDummy->next, this);
	}

	/// <summary>
	/// 末尾の次を指すイテレータ取得
	/// </summary>
	/// <returns>末尾の次を指すイテレータ</returns>
	Iterator End()
	{
		return Iterator(mDummy, this);
	}

	/// <summary>
	/// 先頭コンストイテレータ取得（明示的）
	/// </summary>
	/// <returns>先頭を指すコンストイテレータ</returns>
	ConstIterator CBegin() const
	{
		return ConstIterator(mDummy->next, this);
	}

	/// <summary>
	/// 末尾の次を指すコンストイテレータ取得（明示的）
	/// </summary>
	/// <returns>末尾の次を指すコンストイテレータ</returns>
	ConstIterator CEnd() const
	{
		return ConstIterator(mDummy, this);
	}

	/// <summary>
	/// リスト内の要素数を取得
	/// </summary>
	/// <returns>要素数</returns>
	size_t Count() const
	{
		return mCount;
	}

	/// <summary>
	/// リストに要素が存在するかチェック
	/// </summary>
	/// <returns>要素が存在する場合はtrue、空の場合はfalse</returns>
	bool Any() const
	{
		return mCount != 0;
	}

	/// <summary>
	/// リストのすべての要素を削除してメモリを解放
	/// </summary>
	void Clean()
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
};
