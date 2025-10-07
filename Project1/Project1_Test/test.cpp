#include "pch.h"
#include "../Project1/linkedList.h"

/// <summary>
/// リストの内容が期待される配列と一致するかをチェック
/// </summary>
/// <param name="list">チェックするリスト</param>
/// <param name="expected">期待値の配列</param>
/// <param name="length">配列の長さ</param>
/// <returns>一致する場合はtrue、それ以外はfalse</returns>
bool CheckList(const LinkedList<int>& list, const int* expected, size_t length)
{
	// 要素数が一致するかチェック
	if (list.Count() != length)
	{
		return false;
	}

	// リストと配列を同時に走査して比較
	auto listIt = list.CBegin();
	size_t index = 0;

	while (listIt != list.CEnd() && index < length)
	{
		if (*listIt != expected[index])
		{
			return false;
		}
		++listIt;
		++index;
	}

	return true;
}

#pragma region データ数の取得テスト

/// <summary>
/// ID_0 リストが空である場合の戻り値
/// </summary>
TEST(LinkedListTest, EmptyListTest)
{
	LinkedList<int> list;

	//想定する戻り値 0
	EXPECT_EQ(0, list.Count());
}

/// <summary>
/// ID_1 リスト末尾への挿入を行った際の戻り値
/// </summary>
TEST(LinkedListTest, InsertAtEndReturnValueSuccessTest)
{
	LinkedList<int> list;

	list.Insert(list.End(), 10);
	//想定する戻り値 1
	EXPECT_EQ(1, list.Count());
}

/// <summary>
/// ID_2 リスト末尾への挿入が失敗した際の戻り値
/// </summary>
TEST(LinkedListTest, InsertAtEndReturnValueFailTest)
{
	LinkedList<int> list;

	LinkedList<int> otherList;

	list.Insert(otherList.End(), 10);

	//想定する戻り値 0
	EXPECT_EQ(0, list.Count());
}

/// <summary>
/// ID_3 データの挿入を行った際の戻り値
/// </summary>
TEST(LinkedListTest, InsertDateReturnValueSuccessTest)
{
	LinkedList<int> list;

	auto it = list.Begin();

	list.Insert(it, 10);

	//想定する戻り値 1
	EXPECT_EQ(1, list.Count());
}

/// <summary>
/// ID_4 データの挿入に失敗した際の戻り値
/// </summary>
TEST(LinkedListTest, InsertDataReturnValueFailTest)
{
	LinkedList<int> list;

	LinkedList<int> otherList;

	list.Insert(otherList.Begin(), 10);

	//想定する戻り値 0
	EXPECT_EQ(0, list.Count());
}

/// <summary>
///  ID_5 データの削除を行った際の戻り値
/// </summary>
TEST(LinkedListTest, RemoveDataReturnValueSuccessTest)
{
	LinkedList<int> list;

	auto it = list.Insert(list.End(), 10);

	list.Remove(it);

	//想定する戻り値 0
	EXPECT_EQ(0, list.Count());
}

/// <summary>
/// ID_6 データの削除が失敗した際の戻り値
/// </summary>
TEST(LinkedListTest, RemoveDataReturnValueFailTest)
{
	LinkedList<int> list;

	list.Insert(list.End(), 10);

	LinkedList<int> otherList;

	list.Remove(otherList.End());

	//想定する戻り値 1
	EXPECT_EQ(1, list.Count());
}

/// <summary>
/// ID_7 リストが空である場合に、データの削除を行った際の戻り値
/// </summary>
TEST(LinkedListTest, RemoveDataAtEmptyListReturnValueTest)
{
	LinkedList<int> list;

	list.Remove(list.Begin());


	//想定する戻り値 0
	EXPECT_EQ(0, list.Count());
}

#pragma endregion

#pragma region データの挿入テスト

/// <summary>
/// ID_9 リストが空である場合に、挿入した際の挙動
/// </summary>
TEST(LinkedListTest, InsertToEmptyListReturnValueTest)
{
	{
		LinkedList<int> list;

		//先頭イテレータを引数で渡した場合
		list.Insert(list.Begin(), 10);

		//イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる。
		EXPECT_TRUE(10 == *list.Begin());
	}

	{
		LinkedList<int> list;

		//末尾イテレータを引数で渡した場合
		list.Insert(list.End(), 20);
		//イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる。
		EXPECT_TRUE(20 == *list.Begin());
	}
}

/// <summary>
/// ID_10 リストに複数の要素がある場合に、先頭イテレータを渡して、挿入した際の挙動
/// </summary>
TEST(LinkedListTest, InsertAtBeginReturnValueTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 20);
	list.Insert(list.End(), 30);

	auto it = list.Insert(list.Begin(), 10);

	++it;

	//先頭に要素が挿入され、元々先頭だった要素が２番目になる
	EXPECT_TRUE(20 == *it);
}

/// <summary>
/// ID_11 リストに複数の要素がある場合に、末尾イテレータを渡して、挿入した際の挙動
/// </summary>
TEST(LinkedListTest, InsertAtEndWithMultipleElementsReturnValueTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);

	// 末尾に要素を挿入
	auto it = list.Insert(list.End(), 30);

	// イテレータの指す位置に要素が挿入される
	EXPECT_TRUE(30 == *it);
}

/// <summary>
/// ID_12 リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して、挿入した際の挙動
/// </summary>
TEST(LinkedListTest, InsertAtMiddleReturnValueTest)
{
	// 先頭に要素を挿入
	{
		LinkedList<int> list;
		list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);
		list.Insert(list.End(), 40);

		auto it = list.Insert(list.Begin(), 10);
		++it;
		//イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる
		EXPECT_TRUE(20 == *it);
		int expected[4] = {10, 20, 30, 40};
		//格納済みの要素に影響がない
		EXPECT_TRUE(CheckList(list, expected, 4));
	}

	// 中間に要素を挿入
	{
		LinkedList<int> list;
		list.Insert(list.End(), 10);
		auto middleIt = list.Insert(list.End(), 30);
		list.Insert(list.End(), 40);


		auto it = list.Insert(middleIt, 20);
		++it;
		//イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる
		EXPECT_TRUE(30 == *it);
		int expected[4] = {10, 20, 30, 40};
		//格納済みの要素に影響がない
		EXPECT_TRUE(CheckList(list, expected, 4));
	}

	// 末尾に要素を挿入
	{
		LinkedList<int> list;
		list.Insert(list.End(), 10);
		list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);

		auto it = list.Insert(list.End(), 40);
		++it;
		//イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる
		EXPECT_TRUE(it == list.End());
		int expected[4] = {10, 20, 30, 40};
		//格納済みの要素に影響がない
		EXPECT_TRUE(CheckList(list, expected, 4));
	}
}

/// <summary>
/// ID_13 ConstIteratorを指定して、挿入した際の挙動
/// </summary>
TEST(LinkedListTest, InsertWithConstIteratorReturnValueTest)
{
	// 先頭に要素を挿入
	{
		LinkedList<int> list;
		list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);
		list.Insert(list.End(), 40);

		auto it = list.Insert(list.CBegin(), 10);
		++it;
		//コンストイテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる
		EXPECT_TRUE(20 == *it);
		int expected[4] = {10, 20, 30, 40};
		//格納済みの要素に影響がない
		EXPECT_TRUE(CheckList(list, expected, 4));
	}

	// 中央に要素を挿入
	{
		LinkedList<int> list;
		list.Insert(list.End(), 10);
		auto middleIt = list.Insert(list.End(), 30);
		list.Insert(list.End(), 40);

		LinkedList<int>::ConstIterator middleConstIt = middleIt;
		auto it = list.Insert(middleConstIt, 20);
		++it;
		//コンストイテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる
		EXPECT_TRUE(30 == *it);
		int expected[4] = {10, 20, 30, 40};
		//格納済みの要素に影響がない
		EXPECT_TRUE(CheckList(list, expected, 4));
	}

	// 末尾に要素を挿入
	{
		LinkedList<int> list;
		list.Insert(list.End(), 10);
		list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);

		auto it = list.Insert(list.CEnd(), 40);
		++it;
		//コンストイテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる
		EXPECT_TRUE(it == list.End());
		int expected[4] = {10, 20, 30, 40};
		//格納済みの要素に影響がない
		EXPECT_TRUE(CheckList(list, expected, 4));
	}
}

/// <summary>
/// ID_14 不正なイテレータを渡して、挿入した際の挙動
/// </summary>
TEST(LinkedListTest, InsertWithInvalidIteratorReturnValueTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	LinkedList<int> otherList;
	otherList.Insert(otherList.End(), 99);

	auto invalidIt = otherList.Begin();

	list.Insert(invalidIt, 20);

	//何も起こらない
	EXPECT_FALSE(20 == *list.Begin());
}

#pragma endregion

#pragma region データの削除

/// <summary>
/// ID_16 リストが空である場合に、削除を行った際の挙動
/// </summary>
TEST(LinkedListTest, RemoveOnEmptyListTest)
{
	{
		LinkedList<int> list;

		list.Remove(list.Begin());

		//何も起こらない
		EXPECT_FALSE(list.Any());
	}

	{
		LinkedList<int> list;

		list.Remove(list.End());

		//何も起こらない
		EXPECT_FALSE(list.Any());
	}
}

/// <summary>
/// ID_17 リストに複数の要素がある場合に、先頭イテレータを渡して、削除した際の挙動
/// </summary>
TEST(LinkedListTest, RemoveOnMultipleElementListTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);
	list.Insert(list.End(), 30);

	// 先頭イテレータを削除
	list.Remove(list.Begin());
	EXPECT_TRUE(2 == list.Count());

	//先頭要素の削除
	EXPECT_TRUE(20 == *list.Begin());
}

/// <summary>
/// ID_18 リストに複数の要素がある場合に、末尾イテレータを渡して、削除した際の挙動
/// </summary>
TEST(LinkedListTest, RemoveLastOnMultipleElementsListTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);
	list.Insert(list.End(), 30);

	EXPECT_EQ(3, list.Count());

	// 末尾イテレータを削除
	list.Remove(list.End());

	//何も起こらない
	EXPECT_FALSE(2 == list.Count());
}

/// <summary>
/// ID_19 リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して削除した際の挙動
/// </summary>
TEST(LinkedListTest, RemoveMiddleElementTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	auto middleIt = list.Insert(list.End(), 20);
	list.Insert(list.End(), 30);

	// 中間要素を削除
	list.Remove(middleIt);

	auto it = list.Begin();
	++it;

	//期待される位置に要素が格納されている
	EXPECT_TRUE(30 == *it);

	int expected[2] = {10, 30};
	//格納済みの要素に影響がない
	EXPECT_TRUE(CheckList(list, expected, 2));
}

/// <summary>
/// ID_20 ConstIteratorを渡して、削除を行った際の挙動
/// </summary>
TEST(LinkedListTest, RemoveWithConstIteratorTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);
	list.Insert(list.End(), 30);

	list.Remove(list.CBegin());

	auto it = list.Begin();
	//期待される位置に要素が格納されている
	EXPECT_TRUE(20 == *it);

	int expected[2] = {20, 30};
	//格納済みの要素に影響がない
	EXPECT_TRUE(CheckList(list, expected, 2));
}

/// <summary>
/// ID_21 不正なイテレータを渡して、削除した際の挙動
/// </summary>
TEST(LinkedListTest, RemoveWithInvalidIteratorTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	// デフォルト構築された無効なイテレータ
	LinkedList<int>::Iterator invalidIt;

	list.Remove(invalidIt);

	// 何も起こらない
	// リストの要素がないイテレータ、別リストの要素を指すイテレータを渡した際の挙動など
	EXPECT_TRUE(1 == list.Count());
}

#pragma endregion

#pragma region 先頭イテレータの取得

/// <summary>
/// ID_23 リストが空である場合に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, BeginOnEmptyListTest)
{
	LinkedList<int> list;

	// 空リストで Begin() を呼び出す
	auto it = list.Begin();

	//ダミーノードを指すイテレータが返る
	EXPECT_EQ(it, list.End());
}

/// <summary>
/// ID_24 リストに要素が一つある場合に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, BeginOnNonEmptyListTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	// Begin() を呼び出す
	auto it = list.Begin();

	// 先頭要素を指すイテレータが返る
	EXPECT_EQ(10, *it);
}

/// <summary>
/// ID_25 リストに二つ以上の要素がある場合に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, BeginOnMultipleElementsListTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);
	list.Insert(list.End(), 30);

	// Begin() を呼び出す
	auto it = list.Begin();

	// 先頭要素を指すイテレータが返る
	EXPECT_EQ(10, *it);
}

/// <summary>
/// ID_26 データの挿入を行った後に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, BeginAfterInsertTest)
{
	//先頭に挿入
	{
		LinkedList<int> list;

		list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);
		list.Insert(list.End(), 40);

		list.Insert(list.Begin(), 10);

		//先頭要素を指すイテレータが返る
		EXPECT_EQ(10, *list.Begin());
	}

	//中央に挿入
	{
		LinkedList<int> list;

		list.Insert(list.End(), 10);
		auto it = list.Insert(list.End(), 30);
		list.Insert(list.End(), 40);

		list.Insert(it, 20);

		//先頭要素を指すイテレータが返る
		EXPECT_EQ(10, *list.Begin());
	}

	//末尾に挿入
	{
		LinkedList<int> list;

		list.Insert(list.End(), 10);
		auto it = list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);

		list.Insert(list.End(), 40);

		//先頭要素を指すイテレータが返る
		EXPECT_EQ(10, *list.Begin());
	}
}

/// <summary>
/// ID_27 データの削除を行った後に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, BeginAfterRemoveTest)
{
	// 先頭に削除
	{
		LinkedList<int> list;
		list.Insert(list.End(), 10);
		list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);

		list.Remove(list.Begin());
		//先頭要素を指すイテレータが返る
		EXPECT_EQ(20, *list.Begin());
	}

	//中央に削除
	{
		LinkedList<int> list;
		list.Insert(list.End(), 10);
		auto it = list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);

		list.Remove(it);
		//先頭要素を指すイテレータが返る
		EXPECT_EQ(10, *list.Begin());
	}

	//末尾に削除
	{
		LinkedList<int> list;
		list.Insert(list.End(), 10);
		list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);

		list.Remove(list.End());
		//先頭要素を指すイテレータが返る
		EXPECT_EQ(10, *list.Begin());
	}
}

#pragma endregion

#pragma region 先頭コンストイテレータの取得

/// <summary>
/// ID_29 リストが空である場合に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, BeginConstOnEmptyListTest)
{
	LinkedList<int> list;

	// 空リストで CBegin() を呼び出す
	auto it = list.CBegin();

	//ダミーノードを指すコンストイテレータが返る
	EXPECT_EQ(it, list.CEnd());
}

/// <summary>
/// ID_30 リストに要素が一つある場合に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, BeginConstOnNonEmptyListTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	// CBegin() を呼び出す
	auto it = list.CBegin();

	//先頭要素を指すコンストイテレータが返る
	EXPECT_EQ(10, *it);
}

/// <summary>
/// ID_31 リストに二つ以上の要素がある場合に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, BeginConstOnMultipleElementsListTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);
	list.Insert(list.End(), 30);

	// CBegin() を呼び出す
	auto it = list.CBegin();

	//先頭要素を指すコンストイテレータが返る
	EXPECT_EQ(10, *it);
}

/// <summary>
/// ID_32 データの挿入を行った後に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, BeginConstAfterInsertTest)
{
	LinkedList<int> list;

	list.Insert(list.End(), 10);
	auto it = list.Insert(list.End(), 30);
	list.Insert(list.End(), 40);


	//先頭に挿入
	list.Insert(list.Begin(), 0);
	//先頭要素を指すコンストイテレータが返る
	EXPECT_EQ(0, *list.CBegin());


	//中央に挿入
	list.Insert(it, 20);
	//先頭要素を指すコンストイテレータが返る
	EXPECT_EQ(0, *list.CBegin());

	//末尾に挿入
	list.Insert(list.End(), 50);
	//先頭要素を指すコンストイテレータが返る
	EXPECT_EQ(0, *list.CBegin());
}

/// <summary>
/// ID_33 データの削除を行った後に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, BeginConstAfterRemoveTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);
	auto it = list.Insert(list.End(), 30);
	list.Insert(list.End(), 40);

	// 先頭に削除
	list.Remove(list.Begin());
	//先頭要素を指すコンストイテレータが返る
	EXPECT_EQ(20, *list.CBegin());

	//中央に削除
	it = list.Remove(it);
	//先頭要素を指すコンストイテレータが返る
	EXPECT_EQ(20, *list.CBegin());

	//末尾に削除
	list.Remove(list.End());
	//先頭要素を指すコンストイテレータが返る
	EXPECT_EQ(20, *list.CBegin());
}


#pragma endregion

#pragma region 末尾イテレータの取得

/// <summary>
/// ID_35 リストが空である場合に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, EndOnEmptyListTest)
{
	LinkedList<int> list;

	// 空リストで End() を呼び出す
	auto it = list.End();

	//ダミーノードを指すイテレータが返る
	EXPECT_EQ(it, list.End());
}

/// <summary>
/// ID_36 リストに要素が一つある場合に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, EndOnNonEmptyListTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	auto it = list.End();

	//末尾を指すイテレータが返る
	EXPECT_EQ(it, list.End());
}

/// <summary>
/// ID_37 リストに二つ以上の要素がある場合に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, EndOnMultipleElementsListTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);
	list.Insert(list.End(), 30);

	auto it = list.End();

	//末尾を指すイテレータが返る
	EXPECT_EQ(it, list.End());
}

/// <summary>
/// ID_38 データの挿入を行った後に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, EndAfterInsertTest)
{
	//先頭に挿入
	{
		LinkedList<int> list;

		list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);
		list.Insert(list.End(), 40);

		list.Insert(list.Begin(), 10);

		auto endIt = list.End();
		//末尾を指すイテレータが返る
		EXPECT_EQ(endIt, list.End());
	}

	//中央に挿入
	{
		LinkedList<int> list;

		list.Insert(list.End(), 10);
		auto it = list.Insert(list.End(), 30);
		list.Insert(list.End(), 40);

		list.Insert(it, 20);

		auto endIt = list.End();
		//末尾を指すイテレータが返る
		EXPECT_EQ(endIt, list.End());
	}

	//末尾に挿入
	{
		LinkedList<int> list;

		list.Insert(list.End(), 10);
		list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);

		list.Insert(list.End(), 40);

		auto endIt = list.End();
		//末尾を指すイテレータが返る
		EXPECT_EQ(endIt, list.End());
	}
}

/// <summary>
/// ID_39 データの削除を行った後に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, EndAfterRemoveTest)
{
	// 先頭に削除
	{
		LinkedList<int> list;
		list.Insert(list.End(), 10);
		list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);

		list.Remove(list.Begin());
		auto endIt = list.End();
		//末尾を指すイテレータが返る
		EXPECT_EQ(endIt, list.End());
	}

	//中央に削除
	{
		LinkedList<int> list;
		list.Insert(list.End(), 10);
		auto it = list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);

		list.Remove(it);
		auto endIt = list.End();
		//末尾を指すイテレータが返る
		EXPECT_EQ(endIt, list.End());
	}

	//末尾に削除
	{
		LinkedList<int> list;
		list.Insert(list.End(), 10);
		list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);

		list.Remove(list.End());

		auto endIt = list.End();
		//末尾を指すイテレータが返る
		EXPECT_EQ(endIt, list.End());
	}
}


#pragma endregion

#pragma region 末尾コンストイテレータの取得

/// <summary>
/// ID_41 リストが空である場合に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, EndConstOnEmptyListTest)
{
	LinkedList<int> list;

	// 空リストで End() を呼び出す
	auto it = list.CEnd();

	//ダミーノードを指すコンストイテレータが返る
	EXPECT_EQ(it, list.CEnd());
}

/// <summary>
/// ID_42 リストに要素が一つある場合に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, EndConstOnNonEmptyListTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	auto it = list.CEnd();

	//末尾を指すコンストイテレータが返る
	EXPECT_EQ(it, list.CEnd());
}

/// <summary>
/// ID_43 リストに二つ以上の要素がある場合に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, EndConstOnMultipleElementsListTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);
	list.Insert(list.End(), 30);

	auto it = list.CEnd();

	//末尾を指すコンストイテレータが返る
	EXPECT_EQ(it, list.CEnd());
}

/// <summary>
/// ID_44 データの挿入を行った後に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, EndConstAfterInsertTest)
{
	//先頭に挿入
	{
		LinkedList<int> list;

		list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);
		list.Insert(list.End(), 40);

		list.Insert(list.Begin(), 10);

		auto endIt = list.CEnd();
		//末尾を指すコンストイテレータが返る
		EXPECT_EQ(endIt, list.CEnd());
	}

	//中央に挿入
	{
		LinkedList<int> list;

		list.Insert(list.End(), 10);
		auto it = list.Insert(list.End(), 30);
		list.Insert(list.End(), 40);

		list.Insert(it, 20);

		auto endIt = list.CEnd();
		//末尾を指すコンストイテレータが返る
		EXPECT_EQ(endIt, list.CEnd());
	}

	//末尾に挿入
	{
		LinkedList<int> list;

		list.Insert(list.End(), 10);
		list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);

		list.Insert(list.End(), 40);

		auto endIt = list.CEnd();
		//末尾を指すコンストイテレータが返る
		EXPECT_EQ(endIt, list.CEnd());
	}
}

/// <summary>
/// ID_45 データの削除を行った後に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, EndConstAfterRemoveTest)
{
	// 先頭に削除
	{
		LinkedList<int> list;
		list.Insert(list.End(), 10);
		list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);

		list.Remove(list.Begin());
		auto endIt = list.CEnd();
		//末尾を指すコンストイテレータが返る
		EXPECT_EQ(endIt, list.CEnd());
	}

	//中央に削除
	{
		LinkedList<int> list;
		list.Insert(list.End(), 10);
		auto it = list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);

		list.Remove(it);
		auto endIt = list.CEnd();
		//末尾を指すコンストイテレータが返る
		EXPECT_EQ(endIt, list.CEnd());
	}

	//末尾に削除
	{
		LinkedList<int> list;
		list.Insert(list.End(), 10);
		list.Insert(list.End(), 20);
		list.Insert(list.End(), 30);

		list.Remove(list.End());

		auto endIt = list.CEnd();
		//末尾を指すコンストイテレータが返る
		EXPECT_EQ(endIt, list.CEnd());
	}
}

#pragma endregion

#pragma region イテレータの指す要素を取得する

/// <summary>
/// ID_0 リストの参照がない状態で呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, DereferenceInvalidIteratorTest)
{
	LinkedList<int>::Iterator it;

	// Assert発生
	EXPECT_DEATH(*it, ".*");
}

/// <summary>
/// ID_1 Iteratorから取得した要素に対して、値の代入が行えるかをチェック
/// </summary>
TEST(LinkedListTest, IteratorModifyValueTest)
{
	LinkedList<int> list;
	auto it = list.Insert(list.End(), 10);

	EXPECT_EQ(10, *it);

	*it = 20;

	EXPECT_EQ(20, *it);
}

/// <summary>
/// ID_3 リストが空の際の、先頭イテレータに対して呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, DereferenceBeginOnEmptyListTest)
{
	LinkedList<int> list;

	auto it = list.Begin();

	// Assert発生
	EXPECT_DEATH(*it, ".*");
}

/// <summary>
/// ID_4 末尾イテレータに対して呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, DereferenceEndIteratorTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);

	auto it = list.End();

	// Assert発生
	EXPECT_DEATH(*it, ".*");
}

#pragma endregion

#pragma region イテレータをリストの末尾に向かって一つ進める

/// <summary>
/// ID_5 リストの参照がない状態で呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, IncrementInvalidIteratorTest)
{
	LinkedList<int>::Iterator it;

	// Assert発生
	EXPECT_DEATH(++it, ".*");
}

/// <summary>
/// ID_6 リストが空の際の、先頭イテレータに対して呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, IncrementBeginOnEmptyListTest)
{
	LinkedList<int> list;
	auto it = list.Begin();

	// Assert発生
	EXPECT_DEATH(++it, ".*");
}

/// <summary>
/// ID_7 末尾イテレータに対して呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, IncrementEndIteratorTest)
{
	LinkedList<int> list;

	auto it = list.End();

	// Assert発生
	EXPECT_DEATH(++it, ".*");
}

/// <summary>
/// ID_8 リストに二つ以上の要素がある場合に呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, IncrementOnMultipleElementsListTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);
	list.Insert(list.End(), 30);

	auto it = list.Begin();
	EXPECT_EQ(10, *it);

	// 次の要素に進める
	++it;
	EXPECT_EQ(20, *it);

	// 次の要素に進める
	++it;
	EXPECT_EQ(30, *it);

	// 末尾に到達
	++it;
	EXPECT_EQ(it, list.End());
}

/// <summary>
/// ID_9 前置インクリメントを行った際の挙動(++演算子オーバーロードで実装した場合)
/// </summary>
TEST(LinkedListTest, PreIncrementReturnValueTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);

	auto it = list.Begin();
	// インクリメント前の値
	EXPECT_EQ(10, *it);

	// 前置インクリメント:インクリメント後の値を返す
	auto& result = ++it;

	// インクリメント後の値 次の要素を指す
	EXPECT_EQ(20, *result);
	EXPECT_EQ(20, *it);
}

/// <summary>
/// ID_10 後置インクリメントを行った際の挙動(++演算子オーバーロードで実装した場合)
/// </summary>
TEST(LinkedListTest, PostIncrementReturnValueTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);

	auto it = list.Begin();
	// インクリメント前の値
	EXPECT_EQ(10, *it);

	// 後置インクリメント:インクリメント前の値を返す
	auto result = it++;

	// インクリメント後の値
	EXPECT_EQ(10, *result);
	EXPECT_EQ(20, *it);
}

#pragma endregion

#pragma region イテレータをリストの先頭に向かって一つ進める

/// <summary>
/// ID_11 リストの参照がない状態で呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, DecrementInvalidIteratorTest)
{
	LinkedList<int>::Iterator it;

	// Assert発生
	EXPECT_DEATH(--it, ".*");
}

/// <summary>
/// ID_12 リストが空の際の、末尾イテレータに対して呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, DecrementEndOnEmptyListTest)
{
	LinkedList<int> list;
	auto it = list.End();

	// Assert発生
	EXPECT_DEATH(--it, ".*");
}

/// <summary>
/// ID_13 先頭イテレータに対して呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, DecrementBeginIteratorTest)
{
	LinkedList<int> list;

	auto it = list.Begin();

	// Assert発生
	EXPECT_DEATH(--it, ".*");
}

/// <summary>
/// ID_14 リストに二つ以上の要素がある場合に呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, DecrementOnMultipleElementsListTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);
	auto it = list.Insert(list.End(), 30);

	EXPECT_EQ(30, *it);

	// 前の要素に進める
	--it;
	EXPECT_EQ(20, *it);

	// 先頭に到達
	--it;
	EXPECT_EQ(10, *it);
}

/// <summary>
/// ID_15 前置デクリメントを行った際の挙動( --演算子オーバーロードで実装した場合 )
/// </summary>
TEST(LinkedListTest, PreDecrementReturnValueTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	auto it = list.Insert(list.End(), 20);

	// デクリメント前の値
	EXPECT_EQ(20, *it);

	// 前置デクリメント:デクリメント後の値を返す
	auto& result = --it;

	// デクリメント後の値 前の要素を指す
	EXPECT_EQ(10, *result);
	EXPECT_EQ(10, *it);
}

/// <summary>
/// ID_16 後置デクリメントを行った際の挙動( --演算子オーバーロードで実装した場合 )
/// </summary>
TEST(LinkedListTest, PostDecrementReturnValueTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	auto it = list.Insert(list.End(), 20);

	// デクリメント前の値
	EXPECT_EQ(20, *it);

	// 後置デクリメント:デクリメント前の値を返す
	auto result = it--;

	// デクリメント後の値
	EXPECT_EQ(20, *result);
	EXPECT_EQ(10, *it);
}

#pragma endregion

#pragma region イテレータのコピーを行う

/// <summary>
/// ID_18 コピーコンストラクト後の値がコピー元と等しいことをチェック
/// </summary>
TEST(LinkedListTest, CopyConstructorTest)
{
	LinkedList<int> list;
	auto it = list.Insert(list.End(), 10);

	EXPECT_EQ(10, *it);

	// コピーコンストラクタ
	LinkedList<int>::Iterator itCopy = it;

	// コピー元と同じ値を指している
	EXPECT_EQ(10, *itCopy);
	EXPECT_EQ(it, itCopy);
}

#pragma endregion

#pragma region イテレータの代入を行う

/// <summary>
/// ID_20 代入後の値がコピー元と等しいことをチェック
/// </summary>
TEST(LinkedListTest, AssignmentOperatorTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);

	auto it1 = list.Begin();
	auto it2 = list.Begin();
	++it2;

	// 代入演算子
	it1 = it2;

	// 代入元と同じ値を指している
	EXPECT_EQ(it1, it2);
	EXPECT_EQ(*it1, *it2);
}

#pragma endregion

#pragma region 二つのイテレータが同一のものであるか 比較を行う

/// <summary>
/// ID_21 リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
/// </summary>
TEST(LinkedListTest, CompareBeginAndEndOnEmptyListTest)
{
	LinkedList<int> list;

	auto beginIt = list.Begin();
	auto endIt = list.End();

	// 空リストでは Begin() == End()
	EXPECT_TRUE(beginIt == endIt);
}

/// <summary>
/// ID_22 同一のイテレータを比較した際の挙動
/// </summary>
TEST(LinkedListTest, CompareSameIteratorTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	auto it1 = list.Begin();
	auto it2 = it1;

	// 同じイテレータ
	EXPECT_TRUE(it1 == it2);
}

/// <summary>
/// ID_23 異なるイテレータを比較した際の挙動
/// </summary>
TEST(LinkedListTest, CompareDifferentIteratorTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);

	auto it1 = list.Begin();
	auto it2 = list.Begin();
	++it2;

	// 異なる位置のイテレータ
	EXPECT_FALSE(it1 == it2);
}

#pragma endregion

#pragma region 二つのイテレータが異なるものであるか 比較を行う

/// <summary>
/// ID_24 リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
/// </summary>
TEST(LinkedListTest, CompareNotEqualBeginAndEndOnEmptyListTest)
{
	LinkedList<int> list;

	auto it1 = list.Begin();
	auto it2 = list.End();

	// 空リストでは Begin() == End()
	EXPECT_FALSE(it1 != it2);
}

/// <summary>
/// ID_25 同一のイテレータを比較した際の挙動
/// </summary>
TEST(LinkedListTest, CompareNotEqualSameIteratorTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	auto it1 = list.Begin();
	auto it2 = it1;

	// 同じイテレータ
	EXPECT_FALSE(it1 != it2);
}

/// <summary>
/// ID_26 異なるイテレータを比較した際の挙動
/// </summary>
TEST(LinkedListTest, CompareNotEqualDifferentIteratorTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);

	auto it1 = list.Begin();
	auto it2 = list.Begin();
	++it2;

	// 異なる位置のイテレータ
	EXPECT_TRUE(it1 != it2);
}

#pragma endregion
