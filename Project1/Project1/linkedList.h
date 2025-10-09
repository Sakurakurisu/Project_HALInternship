#pragma once
#include <cassert>

/**
 * @brief 双方向リストのテンプレートクラス
 * @tparam T リストに格納する要素の型
 */
template <typename T>
class LinkedList
{
private:
	/**
	 * @brief ノード構造体
	 */
	struct Node
	{
		T data;
		Node* prev;
		Node* next;

		/**
		 * @brief データを持つノード用コンストラクタ
		 * @param value ノードに格納する値
		 */
		Node(const T& value);

		/**
		 * @brief ダミーノード用デフォルトコンストラクタ
		 */
		Node();
	};

	Node* mDummy; ///< ダミーノード（末尾の次を指す）
	size_t mCount;

public:
	/**
	 * @brief コンストイテレータクラス
	 */
	class ConstIterator
	{
	private:
		const Node* mNode; ///< イテレータが指すノード
		const LinkedList<T>* mList; ///< イテレータが属するリスト
		friend class LinkedList<T>;

		/**
		 * @brief プライベートコンストラクタ
		 * @param node 指すノード
		 * @param list 属するリスト
		 */
		ConstIterator(const Node* node, const LinkedList<T>* list);

	public:
		/**
		 * @brief デフォルトコンストラクタ
		 */
		ConstIterator();

		/**
		 * @brief イテレータの指す要素を取得（const版）
		 * @return 要素へのconst参照
		 */
		const T& operator*() const;

		/**
		 * @brief アロー演算子（const版）
		 * @return 要素へのconstポインタ
		 */
		const T* operator->() const;

		/**
		 * @brief 前置インクリメント演算子
		 * @return インクリメント後のイテレータへの参照
		 */
		ConstIterator& operator++();

		/**
		 * @brief 後置インクリメント演算子
		 * @return インクリメント前のイテレータのコピー
		 */
		ConstIterator operator++(int);

		/**
		 * @brief 前置デクリメント演算子
		 * @return デクリメント後のイテレータへの参照
		 */
		ConstIterator& operator--();

		/**
		 * @brief 後置デクリメント演算子
		 * @return デクリメント前のイテレータのコピー
		 */
		ConstIterator operator--(int);

		/**
		 * @brief 等価比較演算子
		 * @param other 比較対象のイテレータ
		 * @return 等しい場合true
		 */
		bool operator==(const ConstIterator& other) const;

		/**
		 * @brief 非等価比較演算子
		 * @param other 比較対象のイテレータ
		 * @return 等しくない場合true
		 */
		bool operator!=(const ConstIterator& other) const;

		/**
		 * @brief 代入演算子
		 * @param other 代入元のイテレータ
		 * @return 代入後の自身への参照
		 */
		ConstIterator& operator=(const ConstIterator& other);
	};

	/**
	 * @brief イテレータクラス
	 */
	class Iterator : public ConstIterator
	{
	private:
		friend class LinkedList<T>;

		/**
		 * @brief プライベートコンストラクタ
		 * @param node 指すノード
		 * @param list 属するリスト
		 */
		Iterator(Node* node, const LinkedList<T>* list);

	public:
		/**
		 * @brief デフォルトコンストラクタ
		 */
		Iterator();

		/**
		 * @brief イテレータの指す要素を取得（非const版）
		 * @return 要素への参照
		 */
		T& operator*();

		/**
		 * @brief アロー演算子（非const版）
		 * @return 要素へのポインタ
		 */
		T* operator->();
	};

	/**
	 * @brief コンストラクタ
	 */
	LinkedList();

	/**
	 * @brief デストラクタ
	 */
	~LinkedList();

	/**
	 * @brief イテレータが指す位置の前に要素を挿入
	 * @param it 挿入位置を指すコンストイテレータ
	 * @param value 挿入する値
	 * @return 挿入に成功した場合true、失敗した場合false
	 */
	bool Insert(const ConstIterator& it, const T& value);

	/**
	 * @brief イテレータが指す位置の要素を削除
	 * @param it 削除する要素を指すコンストイテレータ
	 * @return 削除に成功した場合true、失敗した場合false
	 */
	bool Remove(const ConstIterator& it);

	/**
	 * @brief 先頭イテレータ取得
	 * @return 先頭を指すイテレータ
	 */
	Iterator Begin();

	/**
	 * @brief 末尾の次を指すイテレータ取得
	 * @return 末尾の次を指すイテレータ
	 */
	Iterator End();

	/**
	 * @brief 先頭コンストイテレータ取得（明示的）
	 * @return 先頭を指すコンストイテレータ
	 */
	ConstIterator CBegin() const;

	/**
	 * @brief 末尾の次を指すコンストイテレータ取得（明示的）
	 * @return 末尾の次を指すコンストイテレータ
	 */
	ConstIterator CEnd() const;

	/**
	 * @brief リスト内の要素数を取得
	 * @return 要素数
	 */
	size_t Count() const;

	/**
	 * @brief リストに要素が存在するかチェック
	 * @return 要素が存在する場合true、空の場合false
	 */
	bool Any() const;

	/**
	 * @brief リストのすべての要素を削除してメモリを解放
	 */
	void Clean();

	/**
	 * @brief 2つのコンストイテレータが指すノードの位置を交換
	 * @param a 交換する最初のコンストイテレータ
	 * @param b 交換する2番目のコンストイテレータ
	 */
	void Swap(const ConstIterator& a, const ConstIterator& b);
};

// テンプレート関数の実装をインクルード
#include "linkedList.inl"
