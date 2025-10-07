#include "pch.h"
#include "manualTest.h"
#include "../Project1/linkedList.h"

#pragma region データ数の取得テスト

/// <summary>
/// ID_8 const のメソッドであるか
/// </summary>
TEST(LinkedListTest, ConstMethodTest)
{
#if defined TT_TEST_Is_CONST
	LinkedList<int> list;
	list.Insert(list.End(), 10);


	const LinkedList<int>& constList = list;

	constList.Insert(list.End(), 10); //ここでエラー
#endif //TT_TEST_Is_CONST

	SUCCEED();
}

#pragma endregion

#pragma region データの挿入テスト

/// <summary>
/// ID_15 非constのメソッドであるか
/// </summary>
TEST(LinkedListTest, InsertIsNotConstMethodTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);


	const LinkedList<int>& constList = list;

#if defined TT_TEST_INSERT_WHEN_CONST

	constList.Insert(constList.End(), 20);

#endif //TT_TEST_INSERT_WHEN_CONST
}

#pragma endregion

#pragma region データの削除

/// <summary>
/// ID_22 非constのメソッドであるか
/// </summary>
TEST(LinkedListTest, RemoveIsNotConstMethodTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);


	const LinkedList<int>& constList = list;

#if defined TT_TEST_REMOVE_WHEN_CONST

	//constオブジェクトではInsertは呼び出せない（コンパイルエラーになるためコメントアウト）
	constList.Remove(constList.End(), 20);

#endif //TT_TEST_REMOVE_WHEN_CONST
}

#pragma endregion

#pragma region 先頭イテレータの取得

/// <summary>
/// ID_28 constのリストから、ConstIteratorでないIteratorの取得が行えない事をチェック
/// </summary>
TEST(LinkedListTest, BeginConstCheckTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	const LinkedList<int>& constList = list;

#if defined TT_TEST_REMOVE_WHEN_CONST

	auto it = constList.Begin();

#endif //TT_TEST_REMOVE_WHEN_CONST
}

#pragma endregion

#pragma region 先頭コンストイテレータの取得

/// <summary>
/// ID_34 constのメソッドであるか
/// </summary>
TEST(LinkedListTest, ConstIteratorBeginConstCheckTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	const LinkedList<int>& constList = list;

	// コンパイルエラーなし
	auto it = constList.CBegin();
}

#pragma endregion


#pragma region 末尾イテレータの取得

/// <summary>
/// ID_40 constのリストから、ConstIteratorでないIteratorの取得が行えない事をチェック
/// </summary>
TEST(LinkedListTest, EndCheckTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	const LinkedList<int>& constList = list;

#if defined TT_TEST_END_WHEN_CONST

	auto it = constList.End();

#endif //TT_TEST_END_WHEN_CONST
}

#pragma endregion


#pragma region 末尾コンストイテレータの取得

/// <summary>
/// ID_46 constのリストから、ConstIteratorでないIteratorの取得が行えない事をチェック
/// </summary>
TEST(LinkedListTest, EndConstCheckTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	const LinkedList<int>& constList = list;

	// 以下はコンパイルエラーなし
	auto it = constList.CEnd();
}

#pragma endregion

#pragma region イテレータの指す要素を取得する

/// <summary>
/// ID_2 ConstIteratorから取得した要素に対して、値の代入が行えないかをチェック
/// </summary>
TEST(LinkedListTest, ConstIteratorCannotModifyValueTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	auto it = list.CBegin();

	// 以下はコンパイルエラーになるためコメントアウト

#if defined TT_TEST_ITERATOR_CAN_MODIFY

	*it = 20;

#endif //TT_TEST_ITERATOR_CAN_MODIFY
}

#pragma endregion

#pragma region イテレータのコピーを行う

/// <summary>
/// ID_17 ConstIteratorから、Iteratorのコピーが作成されないかをチェック
/// </summary>
TEST(LinkedListTest, CannotCopyConstIteratorToIteratorTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	auto constIt = list.CBegin();

#if defined TT_TEST_CONST_ITERATOR_TO_ITERATOR_DISALLOWED

	LinkedList<int>::Iterator it = constIt;

#endif //TT_TEST_CONST_ITERATOR_TO_ITERATOR_DISALLOWED
}

#pragma endregion


#pragma region イテレータの代入を行う

/// <summary>
/// ID_19 IteratorにConstIteratorを代入できない事をチェック
/// </summary>
TEST(LinkedListTest, CannotAssignConstIteratorToIteratorTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	auto it = list.Begin();
	auto constIt = list.CBegin();

#if defined TT_TEST_CONST_ITERATOR_ASSIGN_TO_ITERATOR_DISALLOWED

	it = constIt;

#endif //TT_TEST_CONST_ITERATOR_ASSIGN_TO_ITERATOR_DISALLOWED
}

#pragma endregion
