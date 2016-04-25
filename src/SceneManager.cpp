#include "SceneManager.h"

SceneManager::SceneManager()
{

}

SceneManager::SceneManager(Game* game, char* filePath)
{
	instance = game->GetSDLInstance();
	audioMngr = game->GetAudioManager();

	std::vector<int> levelIndices;
	std::vector<char*> lines;
	std::ifstream file(filePath);
	std::string buffer;

	if (!file)
	{
		std::cout << std::endl << "File was loaded unsuccessfully (" << filePath << ")." << std::endl;
		return;
	}

	int i = 0;
	while (std::getline(file, buffer))
	{
		char* tmp;
		StrLib::str_copy((char*)buffer.c_str(), tmp);
		lines.push_back(tmp);

		i++;
		if (StrLib::str_contains(tmp, "level"))
			levelIndices.push_back(i);
	}

	LoadScenes(game, lines, levelIndices);
	if (scenes.size() > 0)
	{
		currentScene = 0;
		std::cout << "\n";
	}
}

SceneManager::~SceneManager()
{

}

void SceneManager::Update()
{
	if (currentScene >= 0)
	{
		scenes[currentScene]->Update();
		
		if (scenes[currentScene]->GetObjectiveCount() <= 0)
			NextScene();
	}
}

void SceneManager::HandleInput(SDL_Event &event)
{
	if (currentScene >= 0)
		scenes[currentScene]->HandleInput(event);
}

void SceneManager::Render()
{
	if (currentScene >= 0)
		scenes[currentScene]->Render();
}

void SceneManager::NextScene()
{
	if (currentScene + 1 < scenes.size())
	{
		currentScene++;
		instance->SetRenderScale(GetScalar().x, GetScalar().y);
		audioMngr->PauseMusic();
	}
}

void SceneManager::PreviousScene()
{
	if (currentScene > 0)
	{
		currentScene--;
		instance->SetRenderScale(GetScalar().x, GetScalar().y);
		audioMngr->PauseMusic();
	}
}

void SceneManager::UpdateSceneObject(char* serialized)
{
	std::vector<char*> elements = StrLib::str_split(serialized, ",");
	FunctionalObject* target = scenes[currentScene]->FindObjectWithID(atoi(StrLib::str_split(elements[0], ":")[1]));

	target->Deserialize(elements);
}

void SceneManager::LoadScenes(Game* game, std::vector<char*> &lines, std::vector<int> &indices)
{
	constructor = new ObjectConstructor(lines);

	for (unsigned int i = 0; i < indices.size(); i++)
		scenes.push_back(new Scene(game, lines, indices[i], constructor));
}

Scene* &SceneManager::GetScene(int index) { return scenes[index]; }
int SceneManager::GetCurrentIndex() { return currentScene; }
glm::vec2 SceneManager::GetScalar() { return scenes[currentScene]->GetSize(); }