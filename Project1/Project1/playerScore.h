#pragma once

struct PlayerScore
{
	int score = 0;
	std::string id = "";

	PlayerScore() = default;

	PlayerScore(int score, std::string id) : score(score), id(id)
	{
	}
};
