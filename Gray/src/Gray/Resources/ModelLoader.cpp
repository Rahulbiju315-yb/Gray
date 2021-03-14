#include "grpch.h"
#include "ModelLoader.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "Gray/Window/Window.h"

namespace Gray
{
    ModelLoader::ModelLoader()
        : run(true)
	{
        loader = std::thread(LoaderFun, std::ref(*this));
	}

    ModelLoader::ModelLoader(ModelLoader&& src) noexcept
        : loader(std::move(src.loader)),
          managers(std::move(src.managers)),
          run(src.run)
    {
    }

    ModelLoader::~ModelLoader()
    {
        run = false;
        cvar.notify_one();

        if (loader.joinable())
            loader.join();
    }

    void ModelLoader::AddManager(ModelManager& mm)
    {
        managers.push_back(&mm);
    }

    void ModelLoader::RemoveManager(ModelManager& mm)
    {
        managers.erase(std::remove(managers.begin(), managers.end(), &mm), managers.end());
    }

    bool ModelLoader::RequiresLoading()
    {
        for (ModelManager* mm : managers)
        {
            if (mm->RequiresLoading())
                return true;
        }

        return false;
    }

    void ModelLoader::Notify()
    {
        cvar.notify_one();
    }

    bool ModelLoader::IsRunning()
    {
        return run;
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
            {
                std::unique_lock lock(ml.cvmutex);
                ml.cvar.wait(lock, [&]
                    {
                        return ml.RequiresLoading() || !ml.IsRunning();
                    });
            }

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

				   /*std::vector<Material> materials;
                   CreateMaterials(loadedScene, materials, path, ml.GetTextureManager(*mm));*/

                   ml.AddForInit(std::make_pair(loadedScene, id), *mm);
                }
            }
        }
    }
}