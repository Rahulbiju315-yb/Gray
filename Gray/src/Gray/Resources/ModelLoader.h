#pragma once

#include "thread"
#include "mutex"
#include "ModelManager.h"
#include "assimp/scene.h"
#include "Gray/Events/EventListener.h"

namespace Gray
{
	class ModelLoader
	{
	public:
		ModelLoader();
		ModelLoader(ModelLoader&&) noexcept;
		~ModelLoader();

		void AddManager(ModelManager& mm);
		void RemoveManager(ModelManager& mm);
		bool RequiresLoading();
		void Notify();
		bool IsRunning();

	private:
		std::thread loader;
		std::vector<ModelManager*> managers;
		std::condition_variable cvar;
		std::mutex cvmutex;

		bool run;

		ModelLoader& operator=(const ModelLoader&) = delete;
		ModelLoader& operator=(ModelLoader&&) = delete;

		bool NextModelPath(std::pair<std::string, uint>& next, ModelManager& mm);
		void AddForInit(const std::pair<const aiScene*, uint>& loadedRes, ModelManager& mm);
		TextureManager& GetTextureManager(ModelManager& mm);

		friend void LoaderFun(ModelLoader& ml);
	};

	void LoaderFun(ModelLoader& mm);

}