#include "pch.h"
#include "manualTest.h"
#include "../Project1/linkedList.h"

#pragma region データ数の取得テスト

/**
 * @brief ID_8 const のメソッドであるか
 */
TEST(LinkedListManualTest, ConstMethodTest)
{
#if defined TT_TEST_IS_CONST_LIST
	LinkedList<int> list;
	list.Insert(list.End(), 10);


	const LinkedList<int>& constList = list;

	int count = constList.Count();
#endif //TT_TEST_IS_CONST_LIST

	SUCCEED();
}

#pragma endregion

#pragma region データの挿入テスト

/**
 * @brief ID_15 非constのメソッドであるか
 */
TEST(LinkedListManualTest, InsertIsNotConstMethodTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);


	const LinkedList<int>& constList = list;

#if defined TT_TEST_INSERT_WHEN_CONST_LIST

	constList.Insert(constList.End(), 20);

#endif //TT_TEST_INSERT_WHEN_CONST_LIST
}

#pragma endregion

#pragma region データの削除

/**
 * @brief ID_22 非constのメソッドであるか
 */
TEST(LinkedListManualTest, RemoveIsNotConstMethodTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);


	const LinkedList<int>& constList = list;

#if defined TT_TEST_REMOVE_WHEN_CONST_LIST

	//constオブジェクトではInsertは呼び出せない（コンパイルエラーになるためコメントアウト）
	constList.Remove(constList.End(), 20);

#endif //TT_TEST_REMOVE_WHEN_CONST_LIST
}

#pragma endregion

#pragma region 先頭イテレータの取得

/**
 * @brief ID_28 constのリストから、ConstIteratorでないIteratorの取得が行えない事をチェック
 */
TEST(LinkedListManualTest, BeginConstCheckTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	const LinkedList<int>& constList = list;

#if defined TT_TEST_GET_BEGIN_CONST_LIST

	auto it = constList.Begin();

#endif //TT_TEST_GET_BEGIN_CONST_LIST
}

#pragma endregion

#pragma region 先頭コンストイテレータの取得

/**
 * @brief ID_34 constのメソッドであるか
 */
TEST(LinkedListManualTest, ConstIteratorBeginConstCheckTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	const LinkedList<int>& constList = list;

#if defined TT_TEST_GET_CBEGIN_CONST_LIST
	// コンパイルエラーなし
	auto it = constList.CBegin();
#endif //TT_TEST_GET_CBEGIN_CONST_LIST
}

#pragma endregion


#pragma region 末尾イテレータの取得

/**
 * @brief ID_40 constのリストから、ConstIteratorでないIteratorの取得が行えない事をチェック
 */
TEST(LinkedListManualTest, EndCheckTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	const LinkedList<int>& constList = list;

#if defined TT_TEST_END_WHEN_CONST_LIST

	auto it = constList.End();

#endif //TT_TEST_END_WHEN_CONST_LIST
}

#pragma endregion


#pragma region 末尾コンストイテレータの取得

/**
 * @brief ID_46 constのリストから、ConstIteratorでないIteratorの取得が行えない事をチェック
 */
TEST(LinkedListManualTest, EndConstCheckTest)
{
	LinkedList<int> list;
	list.Insert(list.End(), 10);

	const LinkedList<int>& constList = list;

#if defined TT_TEST_GET_CEND_CONST_LIST
	// 以下はコンパイルエラーなし
	auto it = constList.CEnd();
#endif //TT_TEST_GET_CEND_CONST_LIST
}

#pragma endregion

#pragma region イテレータの指す要素を取得する

/**
 * @brief ID_2 ConstIteratorから取得した要素に対して、値の代入が行えないかをチェック
 */
TEST(LinkedListManualTest, ConstIteratorCannotModifyValueTest)
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

/**
 * @brief ID_17 ConstIteratorから、Iteratorのコピーが作成されないかをチェック
 */
TEST(LinkedListManualTest, CannotCopyConstIteratorToIteratorTest)
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

/**
 * @brief ID_19 IteratorにConstIteratorを代入できない事をチェック
 */
TEST(LinkedListManualTest, CannotAssignConstIteratorToIteratorTest)
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
