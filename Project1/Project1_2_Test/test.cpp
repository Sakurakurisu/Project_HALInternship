#include "pch.h"
#include "../Project1_2/linkedList.h"

#pragma region データ数の取得テスト

/// <summary>
/// ID_0 リストが空である場合の戻り値
/// </summary>
TEST(LinkedListTest, EmptyListTest)
{
	LinkedList<int> list;

	EXPECT_EQ(0, list.Count());
}

/// <summary>
/// ID_1 リスト末尾への挿入を行った際の戻り値
/// </summary>
TEST(LinkedListTest, InsertAtEndReturnValueSuccessTest)
{
	LinkedList<int> list;

	list.Insert(list.End(), 10);
	EXPECT_EQ(1, list.Count());
}

/// <summary>
/// ID_2 リスト末尾への挿入が失敗した際の戻り値
/// </summary>
TEST(LinkedListTest, InsertAtEndReturnValueFailTest)
{
	//LinkedList<int> list;

	//list.Insert(list.End(), 10);
	//EXPECT_EQ(0, list.Count());
}

/// <summary>
/// ID_3 データの挿入を行った際の戻り値
/// </summary>
TEST(LinkedListTest, InsertDateReturnValueSuccessTest)
{
	LinkedList<int> list;

	list.Insert(list.End(), 10);
	EXPECT_EQ(1, list.Count());
}

/// <summary>
/// ID_4 データの挿入に失敗した際の戻り値
/// </summary>
TEST(LinkedListTest, InsertDataReturnValueFailTest)
{
	//LinkedList<int> list;

	//list.Insert(list.End(), 10);
	//EXPECT_EQ(0, list.Count());
}

/// <summary>
///  ID_5 データの削除を行った際の戻り値
/// </summary>
TEST(LinkedListTest, RemoveDataReturnValueSuccessTest)
{
	LinkedList<int> list;

	list.Insert(list.End(), 10);
	list.Remove(list.Begin());
	EXPECT_EQ(0, list.Count());
}

/// <summary>
/// ID_6 データの削除が失敗した際の戻り値
/// </summary>
TEST(LinkedListTest, RemoveDataReturnValueFailTest)
{
	//LinkedList<int> list;

	//list.Insert(list.End(), 10);
	//list.Remove(list.Begin());
	//EXPECT_EQ(1, list.Count());
}

/// <summary>
/// ID_7 リストが空である場合に、データの削除を行った際の戻り値
/// </summary>
TEST(LinkedListTest, RemoveDataAtEmptyListReturnValueTest)
{
	LinkedList<int> list;

	list.Remove(list.Begin());
	EXPECT_EQ(0, list.Count());
}

/// <summary>
/// ID_8 const のメソッドであるか
/// </summary>
TEST(LinkedListTest, ConstMethodTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	// constオブジェクトではInsertは呼び出せない（コンパイルエラーになるためコメントアウト）
	//const LinkedList<int>& constList = list;
	//constList.Insert(list.End(), 10);
}

#pragma endregion

#pragma region データの挿入テスト

/// <summary>
/// ID_9 リストが空である場合に、挿入した際の挙動
/// </summary>
TEST(LinkedListTest, InsertToEmptyListReturnValueTest)
{
	LinkedList<int> list;

	list.Insert(list.End(), 10);


	EXPECT_TRUE(10 == * list.Begin());
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

	EXPECT_FALSE(20 == ++*it);
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
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	auto it = list.Insert(list.End(), 30);
	list.Insert(list.End(), 40);


	// 中間に要素を挿入（30の前に20を挿入）
	auto insertedIt = list.Insert(it, 20);

	// 挿入された要素を指すイテレータが返される
	EXPECT_TRUE(20 == *insertedIt);

	// 順序確認: 10 -> 20 -> 30 -> 40
	auto iter = list.CBegin();
	EXPECT_EQ(10, *iter);
	++iter;
	EXPECT_EQ(20, *iter);
	++iter;
	EXPECT_EQ(30, *iter);
	++iter;
	EXPECT_EQ(40, *iter);
}

/// <summary>
/// ID_13 ConstIteratorを指定して、挿入した際の挙動
/// </summary>
TEST(LinkedListTest, InsertWithConstIteratorReturnValueTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	// 以下の行はコンパイルエラーになるためコメントアウト
	// auto it = list.Insert(list.CBegin(), 5);  // コンパイルエラー
}

/// <summary>
/// ID_14 不正なイテレータを渡して、挿入した際の挙動
/// </summary>
TEST(LinkedListTest, InsertWithInvalidIteratorReturnValueTest)
{
	/*LinkedList<int> list;
	list.Insert(list.End(), 10);

	LinkedList<int> otherList;
	otherList.Insert(otherList.End(), 99);

	auto invalidIt = otherList.Begin();

	list.Insert(invalidIt, 20);

	EXPECT_FALSE(20 == *list.Begin());*/
}

/// <summary>
/// ID_15 非constのメソッドであるか
/// </summary>
TEST(LinkedListTest, InsertIsNotConstMethodTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	// constオブジェクトではInsertは呼び出せない（コンパイルエラーになるためコメントアウト）
	// const LinkedList<int>& constList = list;
	// constList.Insert(constList.End(), 20);  // コンパイルエラー
}

#pragma endregion

#pragma region データの削除

/// <summary>
/// ID_16 リストが空である場合に、削除を行った際の挙動
/// </summary>
TEST(LinkedListTest, RemoveOnEmptyListTest)
{
	LinkedList<int> list;

	list.Remove(list.Begin());

	EXPECT_FALSE(list.Any());
}

/// <summary>
/// ID_17 リストに要素が一つある場合に、先頭イテレータを渡して、削除した際の挙動
/// </summary>
TEST(LinkedListTest, RemoveOnSingleElementListTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);
	list.Insert(list.End(), 30);

	EXPECT_EQ(3, list.Count());

	list.Remove(list.Begin());

	EXPECT_TRUE(2 == list.Count());
}

/// <summary>
/// ID_18 リストに複数の要素がある場合に、末尾イテレータを渡して、削除した際の挙動
/// </summary>
TEST(LinkedListTest, RemoveFirstOnMultipleElementsListTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);
	list.Insert(list.End(), 30);

	EXPECT_EQ(3, list.Count());

	// 先頭要素を削除
	auto it = list.Remove(list.End());

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

	EXPECT_TRUE(10 == *list.CBegin());


	auto it = list.CBegin();
	++it;

	EXPECT_TRUE(30 == *it);
}

/// <summary>
/// ID_20 ConstIteratorを渡して、削除を行った際の挙動
/// </summary>
TEST(LinkedListTest, RemoveWithConstIteratorTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	// 以下はコンパイルエラーになるためコメントアウト
	// auto it = list.Remove(list.CBegin());  // コンパイルエラー
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

	// 空リストなので要素数は0
	EXPECT_EQ(0, list.Count());
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
	LinkedList<int> list;

	list.Insert(list.End(), 10);
	auto it = list.Insert(list.End(), 30);
	list.Insert(list.End(), 40);


	//先頭に挿入
	list.Insert(list.Begin(), 0);
	EXPECT_EQ(0, *list.CBegin());


	//中央に挿入
	list.Insert(it, 20);
	EXPECT_EQ(0, *list.CBegin());

	//末尾に挿入
	list.Insert(list.End(), 50);
	EXPECT_EQ(0, *list.CBegin());
}

/// <summary>
/// ID_27 データの削除を行った後に、呼び出した際の挙動
/// </summary>
TEST(LinkedListTest, BeginAfterRemoveTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);
	list.Insert(list.End(), 20);
	auto it = list.Insert(list.End(), 30);
	list.Insert(list.End(), 40);

	// 先頭に削除
	list.Remove(list.Begin());
	EXPECT_EQ(20, *list.CBegin());

	//中央に削除
	it = list.Remove(it);
	EXPECT_EQ(40, *it);

	//末尾に削除
	list.Remove(list.End());
	// End() は末尾を指すので削除できない可能性がある
	EXPECT_EQ(2, list.Count());
}

/// <summary>
/// ID_28 constのリストから、ConstIteratorでないIteratorの取得が行えない事をチェック
/// </summary>
TEST(LinkedListTest, BeginConstCheckTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	const LinkedList<int>& constList = list;

	// 以下はコンパイルエラーになるためコメントアウト
	// auto it = constList.Begin();  // コンパイルエラー：constオブジェクトから非constメソッドは呼べない
}

#pragma endregion
