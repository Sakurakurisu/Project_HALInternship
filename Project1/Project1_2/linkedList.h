#pragma once
#include <stdexcept>

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

		Node(const T& value) : data(value), prev(nullptr), next(nullptr)
		{
		}
	};

	Node* mHead;
	Node* mTail;
	size_t mCount;

public:
	// コンストイテレータクラスの前方宣言
	class ConstIterator;

	/// <summary>
	/// イテレータクラス
	/// </summary>
	class Iterator
	{
	private:
		Node* mNode;
		friend class LinkedList<T>;
		friend class ConstIterator;

		Iterator(Node* n) : mNode(n)
		{
		}

	public:
		Iterator() : mNode(nullptr)
		{
		}

		/// <summary>
		/// イテレータの指す要素を取得（非const版）
		/// </summary>
		T& operator*()
		{
			if (!mNode)
			{
				throw std::runtime_error("Invalid iterator");
			}
			return mNode->data;
		}

		/// <summary>
		/// アロー演算子
		/// </summary>
		T* operator->()
		{
			if (!mNode)
			{
				throw std::runtime_error("Invalid iterator");
			}
			return &(mNode->data);
		}
	};

	/// <summary>
	/// コンストイテレータクラス
	/// </summary>
	class ConstIterator
	{
	private:
		const Node* mNode;
		friend class LinkedList<T>;

		ConstIterator(const Node* n) : mNode(n)
		{
		}

	public:
		ConstIterator() : mNode(nullptr)
		{
		}

		/// <summary>
		/// イテレータの指す要素を取得（const版）
		/// </summary>
		const T& operator*() const
		{
			if (!mNode)
			{
				throw std::runtime_error("Invalid iterator");
			}
			return mNode->data;
		}

		/// <summary>
		/// アロー演算子（const版）
		/// </summary>
		const T* operator->() const
		{
			if (!mNode)
			{
				throw std::runtime_error("Invalid iterator");
			}
			return &(mNode->data);
		}

		/// <summary>
		/// 前置インクリメント
		/// </summary>
		ConstIterator& operator++()
		{
			if (mNode)
			{
				mNode = mNode->next;
			}
			return *this;
		}

		/// <summary>
		/// 前置デクリメント
		/// </summary>
		ConstIterator& operator--()
		{
			if (mNode)
			{
				mNode = mNode->prev;
			}
			return *this;
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
			return *this;
		}
	};

	LinkedList() : mHead(nullptr), mTail(nullptr), mCount(0)
	{
	}

	~LinkedList()
	{
		Clean();
	}


	/// <summary>
	/// イテレータが指す位置の要素を削除
	/// </summary>
	/// <param name="it">削除する要素を指すイテレータ</param>
	/// <returns>削除された要素の次を指すイテレータ</returns>
	Iterator Remove(Iterator it)
	{
		if (!it.mNode)
		{
			return Iterator(nullptr);
		}

		Node* nodeToDelete = it.mNode;
		Node* nextNode = nodeToDelete->next;

		// 前後のノードを繋ぎ直す
		if (nodeToDelete->prev)
		{
			nodeToDelete->prev->next = nodeToDelete->next;
		}
		else
		{
			// 先頭ノードの場合
			mHead = nodeToDelete->next;
		}

		if (nodeToDelete->next)
		{
			nodeToDelete->next->prev = nodeToDelete->prev;
		}
		else
		{
			// 末尾ノードの場合
			mTail = nodeToDelete->prev;
		}

		delete nodeToDelete;
		mCount--;

		return Iterator(nextNode);
	}

	/// <summary>
	/// イテレータが指す位置の前に要素を挿入
	/// </summary>
	/// <param name="it">挿入位置を指すイテレータ</param>
	/// <param name="value">挿入する値</param>
	/// <returns>挿入された要素を指すイテレータ</returns>
	Iterator Insert(Iterator it, const T& value)
	{
		// 末尾への挿入、またはリストが空の場合
		if (!it.mNode)
		{
			Node* newNode = new Node(value);
			if (mHead == nullptr)
			{
				mHead = newNode;
				mTail = newNode;
			}
			else
			{
				mTail->next = newNode;
				newNode->prev = mTail;
				mTail = newNode;
			}
			mCount++;
			return Iterator(mTail);
		}

		Node* newNode = new Node(value);
		Node* current = it.mNode;

		newNode->next = current;
		newNode->prev = current->prev;

		if (current->prev)
		{
			current->prev->next = newNode;
		}
		else
		{
			// 先頭への挿入
			mHead = newNode;
		}

		current->prev = newNode;
		mCount++;

		return Iterator(newNode);
	}

	/// <summary>
	/// 先頭イテレータ取得
	/// </summary>
	/// <returns>先頭を指すイテレータ</returns>
	Iterator Begin()
	{
		return Iterator(mHead);
	}

	/// <summary>
	/// 末尾の次を指すイテレータ取得
	/// </summary>
	/// <returns>末尾の次を指すイテレータ</returns>
	Iterator End()
	{
		return Iterator(nullptr);
	}

	/// <summary>
	/// 先頭コンストイテレータ取得（明示的）
	/// </summary>
	/// <returns>先頭を指すコンストイテレータ</returns>
	ConstIterator CBegin() const
	{
		return ConstIterator(mHead);
	}

	/// <summary>
	/// 末尾の次を指すコンストイテレータ取得（明示的）
	/// </summary>
	/// <returns>末尾の次を指すコンストイテレータ</returns>
	ConstIterator CEnd() const
	{
		return ConstIterator(mTail);
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
		while (mHead)
		{
			Node* temp = mHead;
			mHead = mHead->next;
			delete temp;
		}
		mHead = nullptr;
		mTail = nullptr;
		mCount = 0;
	}
};
