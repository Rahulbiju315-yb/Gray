#include "grpch.h"
#include "ModelLoader.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "Gray/Window/Window.h"

namespace Gray
{
	ModelLoader::ModelLoader()
	{
        run = true;
        loader = std::thread(LoaderFun, std::ref(*this));
	}

    ModelLoader::~ModelLoader()
    {
        run = false;
        if (loader.joinable())
            loader.join();
    }

	
    void ModelLoader::OnEvent(Event& e, EventType type)
    {
       if (type == EventType::WindowClosed)
            loaderPool.clear();
    }

    void ModelLoader::AddManager(ModelManager& mm)
    {
        managers.push_back(&mm);
    }

    void ModelLoader::RemoveManager(ModelManager& mm)
    {
        managers.erase(std::remove(managers.begin(), managers.end(), &mm), managers.end());
    }

    ModelLoader& ModelLoader::GetModelLoader(int n)
    {
        if (loaderPool.size() == 0)
            loaderPool.push_back(ModelLoader());

        assert(n < loaderPool.size());
        return loaderPool[n];
    }


    bool ModelLoader::NextModelPath(std::pair<std::string, uint>& next, ModelManager& mm)
    {
        if (!mm.toLoad.IsEmpty())
        {
            mm.toLoad.DequeueTo(next);
            return true;
        }

        return false;
    }

    TextureManager& ModelLoader::GetTextureManager(ModelManager& mm)
    {
        return mm.texMan;
    }

    void ModelLoader::AddForInit(const std::pair<const aiScene*, uint>& loadedRes, ModelManager& mm)
    {
        mm.toInit.Enqueue(loadedRes);
    }

    void LoaderFun(ModelLoader& ml)
    {
        while (ml.run)
        {
            for (ModelManager* mm : ml.managers)
            {
                std::pair<std::string, uint> nextload;
                bool available = ml.NextModelPath(nextload, *mm);
                auto [path, id] = nextload;

                if (available)
                {
                   const aiScene* loadedScene = nullptr;
                   loadedScene = aiImportFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

                   if (loadedScene == nullptr)
                   {
                       GRAY_CORE_ERROR("Error Reading Model File " + path);
                       continue;
                   }

                   else
                       GRAY_CORE_INFO("Succesfully loaded model" + path);

				   std::vector<Material> materials;
                   CreateMaterials(loadedScene, materials, path, ml.GetTextureManager(*mm));

                   ml.AddForInit(std::make_pair(loadedScene, id), *mm);
                }
            }
        }
    }

    void OnWindowClose()
    {
        ModelLoader::loaderPool.clear();
    }
}