#pragma once

/// <summary>
/// 双方向連結リストのテンプレートクラス
/// </summary>
/// <typeparam name="T">リストに格納する要素の型</typeparam>
template <typename T>
class LinkedList
{
private:
	// 連結リストのノード構造体
	struct Node
	{
		T data;
		Node* prev;
		Node* next;

		Node(const T& value) : data(value), prev(nullptr), next(nullptr)
		{
		}
	};

	Node* head;
	Node* tail;
	size_t count;

public:
	LinkedList() : head(nullptr), tail(nullptr), count(0)
	{
	}

	~LinkedList()
	{
		Clean();
	}

	/// <summary>
	/// リストの先頭に要素を追加
	/// </summary>
	/// <param name="value">追加する値</param>
	void PushFront(const T& value)
	{
		Node* newNode = new Node(value);
		if (head == nullptr)
		{
			// リストが空の場合、先頭と末尾は同じノードを指す
			head = newNode;
			tail = newNode;
		}
		else
		{
			// 新しいノードを現在の先頭の前に挿入
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		count++;
	}

	/// <summary>
	/// リストの末尾に要素を追加
	/// </summary>
	/// <param name="value">追加する値</param>
	void PushBack(const T& value)
	{
		Node* newNode = new Node(value);
		if (head == nullptr)
		{
			// リストが空の場合、先頭と末尾は同じノードを指す
			head = newNode;
			tail = newNode;
		}
		else
		{
			// 新しいノードを現在の末尾の後に挿入
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		count++;
	}

	/// <summary>
	/// リストの先頭要素を削除して返す
	/// </summary>
	/// <returns>削除された要素の値</returns>
	T PopFront()
	{
		if (!head)
		{
			throw std::runtime_error("LinkedList is empty");
		}
		Node* temp = head;
		T value = temp->data;
		head = head->next;
		if (head)
		{
			head->prev = nullptr;
		}
		else
		{
			// リストが空になった場合
			tail = nullptr;
		}
		delete temp;
		count--;
		return value;
	}

	/// <summary>
	/// リストの末尾要素を削除して返す
	/// </summary>
	/// <returns>削除された要素の値</returns>
	T PopBack()
	{
		if (!tail)
		{
			throw std::runtime_error("LinkedList is empty");
		}
		Node* temp = tail;
		T value = temp->data;
		tail = tail->prev;
		if (tail)
		{
			tail->next = nullptr;
		}
		else
		{
			// リストが空になった場合
			head = nullptr;
		}
		delete temp;
		count--;
		return value;
	}

	/// <summary>
	/// リストの先頭要素を削除（値を返さない）
	/// </summary>
	/// <returns>削除に成功した場合はtrue、リストが空の場合はfalse</returns>
	bool RemoveFront()
	{
		if (head)
		{
			Node* temp = head;
			head = head->next;
			if (head)
			{
				head->prev = nullptr;
			}
			else
			{
				tail = nullptr;
			}
			delete temp;
			count--;
			return true;
		}
		return false;
	}

	/// <summary>
	/// リストの末尾要素を削除（値を返さない）
	/// </summary>
	/// <returns>削除に成功した場合はtrue、リストが空の場合はfalse</returns>
	bool RemoveBack()
	{
		if (tail)
		{
			Node* temp = tail;
			tail = tail->prev;
			if (tail)
			{
				tail->next = nullptr;
			}
			else
			{
				head = nullptr;
			}
			delete temp;
			count--;
			return true;
		}
		return false;
	}

	/// <summary>
	/// リストの先頭要素を取得（削除しない）
	/// </summary>
	/// <returns>先頭要素への定数参照</returns>
	/// <exception cref="std::runtime_error">リストが空の場合</exception>
	const T& Head() const
	{
		if (!head)
		{
			throw std::runtime_error("List is empty");
		}
		return head->data;
	}

	/// <summary>
	/// リストの末尾要素を取得（削除しない）
	/// </summary>
	/// <returns>末尾要素への定数参照</returns>
	/// <exception cref="std::runtime_error">リストが空の場合</exception>
	const T& Tail() const
	{
		if (!tail)
		{
			throw std::runtime_error("List is empty");
		}
		return tail->data;
	}

	/// <summary>
	/// リスト内の要素数を取得
	/// </summary>
	/// <returns>要素数</returns>
	size_t Count() const
	{
		return count;
	}

	/// <summary>
	/// リストに要素が存在するかチェック
	/// </summary>
	/// <returns>要素が存在する場合はtrue、空の場合はfalse</returns>
	bool Any() const
	{
		return count != 0;
	}

	/// <summary>
	/// リストのすべての要素を削除してメモリを解放
	/// </summary>
	void Clean()
	{
		while (head)
		{
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	/// <summary>
	/// リストの先頭から末尾まで各要素に対して関数を実行
	/// </summary>
	/// <param name="func">各要素に対して実行する関数ポインタ</param>
	void ForEachFromHead(void (*func)(T&))
	{
		Node* current = head;
		while (current)
		{
			func(current->data);
			current = current->next;
		}
	}

	/// <summary>
	/// リストの末尾から先頭まで各要素に対して関数を実行
	/// </summary>
	/// <param name="func">各要素に対して実行する関数ポインタ</param>
	void ForEachFromTail(void (*func)(T&))
	{
		Node* current = tail;
		while (current)
		{
			func(current->data);
			current = current->prev;
		}
	}
};
