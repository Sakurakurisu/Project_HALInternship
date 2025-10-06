#pragma once

struct PlayerScore
{
	int score;
	std::string id;


	PlayerScore(int score, std::string id) : score(score), id(id)
	{
	}
};
