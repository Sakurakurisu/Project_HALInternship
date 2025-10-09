#pragma once

/**
 * @brief プレイヤーのスコア情報を格納する構造体
 */
struct PlayerScore
{
	int score = 0; ///< プレイヤーのスコア
	std::string id = ""; ///< プレイヤーID

	PlayerScore() = default;

	/**
	 * @brief スコアとIDを指定するコンストラクタ
	 * @param score プレイヤーのスコア
	 * @param id プレイヤーID
	 */
	PlayerScore(int score, std::string id) : score(score), id(id)
	{
	}
};
