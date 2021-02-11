#pragma once

#include "thread"
#include "mutex"
#include "ModelManager.h"
#include "assimp/scene.h"
#include "Gray/Events/EventListener.h"

namespace Gray
{
	class ModelLoader : public EventListener
	{
	public:
		ModelLoader(ModelLoader&&) = default;
		~ModelLoader();

		void AddManager(ModelManager& mm);
		void RemoveManager(ModelManager& mm);

		static ModelLoader& GetModelLoader(int n = 0);
		void OnEvent(Event& e, EventType type) override;

	private:
		std::thread loader;
		std::vector<ModelManager*> managers;
		static std::vector<ModelLoader> loaderPool;

		bool run;

		ModelLoader();
		ModelLoader(const ModelLoader&) = delete;


		ModelLoader& operator=(const ModelLoader&) = delete;
		ModelLoader& operator=(ModelLoader&&) = delete;

		bool NextModelPath(std::pair<std::string, uint>& next, ModelManager& mm);
		void AddForInit(const std::pair<const aiScene*, uint>& loadedRes, ModelManager& mm);
		TextureManager& GetTextureManager(ModelManager& mm);

		friend void LoaderFun(ModelLoader& ml);
		friend void OnWindowClose();
	};

	void LoaderFun(ModelLoader& mm);

}