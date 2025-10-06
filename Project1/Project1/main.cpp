#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "linkedList.h"
#include "playerScore.h"


int main()
{
	auto linkedList = new LinkedList<PlayerScore>();

	std::ifstream file("Scores.txt");

	// スコアファイルを開く
	if (!file.is_open())
	{
		return 1;
	}

	// ファイルから1行ずつ読み込み
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream info(line);

		std::string scoreStr;
		std::string id;

		std::getline(info, scoreStr, '	');
		std::getline(info, id);

		auto playerScore = PlayerScore(std::stoi(scoreStr), id);

		// PlayerScoreを作成してリストに追加
		linkedList->Insert(linkedList->End(), playerScore);
	}

	file.close();

	for (auto it = linkedList->CBegin(); it != linkedList->CEnd(); ++it)
	{
		std::cout << "Score: " << it->score << "	ID: " << it->id << std::endl;
	}

	delete linkedList;

	return 0;
}
