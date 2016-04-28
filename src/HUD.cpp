#include "HUD.h"
#include "SceneManager.h"

HUD::HUD()
{

}

HUD::HUD(Game* game, glm::vec2 position, int fontPt)
{
	this->game = game;
	this->position = position;

	Scene* currentScene = game->GetSceneManager()->GetScene(game->GetSceneManager()->GetCurrentIndex());
	playerCount = currentScene->playerCount;
	playerScores = new int[playerCount];
	
	for (unsigned int i = 0; i < playerCount; i++)
	{
		playerScores[i] = 0;
		AddPlayerDisplay(i, fontPt);
	}
}

HUD::~HUD()
{

}

void HUD::Update()
{

}

void HUD::Render()
{
	for (unsigned int i = 0; i < labels.size(); i++)
		labels[i]->Render();

	for (unsigned int i = 0; i < scores.size(); i++)
		scores[i]->Render();
}

void HUD::AddScore(int index, int value)
{
	playerScores[index - 1] += value;
	scores[index - 1]->SetText(StrLib::to_char(playerScores[index - 1]));
}

void HUD::SaveScores(char* filePath)
{
	std::vector<char*> lines;
	std::vector<char*> scoreText = { "" };
	char* fullPath;

	if (scores.size() > 1)
	{
		fullPath = StrLib::str_concat(std::vector<char*> { filePath, "online_scores.data" });

		for (unsigned int i = 0; i < playerCount; i++)
		{
			char* tmp = StrLib::str_concat(std::vector<char*> { "p", StrLib::to_char((int)i + 1), " : ", StrLib::to_char(playerScores[i]) });

			if (i != scores.size() - 1)
				tmp = StrLib::str_concat(std::vector<char*> { tmp, " / " });

			scoreText[0] = StrLib::str_concat(std::vector<char*> { scoreText[0], tmp });
		}

		scoreText[0] = StrLib::str_concat(std::vector<char*> { scoreText[0], "\n" });
	}
	else
	{
		fullPath = StrLib::str_concat(std::vector<char*> { filePath, "offline_scores.data" });

		scoreText[0] = StrLib::str_concat(std::vector<char*> { "Player 1 : ", StrLib::to_char(scores[0]), "\n" });
	}

	FileLib::LoadFromFile(fullPath, lines);
	FileLib::AppendToFile(fullPath, scoreText);
}

void HUD::AddPlayerDisplay(int index, int fontPt)
{
	char* playerName = StrLib::str_concat(std::vector<char*> { "Player ", StrLib::to_char(index + 1), ":" });
	char* score = StrLib::to_char(playerScores[index]);

	glm::vec2 offset = glm::vec2((strlen(playerName) * fontPt) * index, 0);
	labels.push_back(new Text(game, position + offset, fontPt, playerName));

	offset += glm::vec2(4 * fontPt, 0);
	scores.push_back(new DynamicText(game, position + offset, fontPt, score));
}