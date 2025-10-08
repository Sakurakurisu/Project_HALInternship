#pragma once

// コンパイル関連手動テスト(リスト)

// ※コンパイルが通れば成功

#pragma region List

#define TT_TEST_IS_CONST_LIST //ID_8 const のメソッドであるか

#define TT_TEST_GET_CBEGIN_CONST_LIST // ID_34 constのメソッドであるか

#define TT_TEST_GET_CEND_CONST_LIST // ID_46 constのリストから、ConstIteratorでないIteratorの取得が行えない事をチェック

#pragma endregion


//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

// ※コンパイルが通らなければ成功

#pragma region List

//#define TT_TEST_INSERT_WHEN_CONST_LIST // ID_15 非constのメソッドであるか

//#define TT_TEST_REMOVE_WHEN_CONST_LIST // ID_22 非constのメソッドであるか

//#define TT_TEST_GET_BEGIN_CONST_LIST // ID_28 constのリストから、ConstIteratorでないIteratorの取得が行えない事をチェック

//#define TT_TEST_END_WHEN_CONST_LIST // ID_40 constのリストから、ConstIteratorでないIteratorの取得が行えない事をチェック

#pragma endregion

#pragma region Iterator

//#define TT_TEST_ITERATOR_CAN_MODIFY // ID_2 ConstIteratorから取得した要素に対して、値の代入が行えないかをチェック

//#define TT_TEST_CONST_ITERATOR_TO_ITERATOR_DISALLOWED // ID_17 ConstIteratorから、Iteratorのコピーが作成されないかをチェック

//#define TT_TEST_CONST_ITERATOR_ASSIGN_TO_ITERATOR_DISALLOWED // ID_19 IteratorにConstIteratorを代入できない事をチェック

#pragma endregion
