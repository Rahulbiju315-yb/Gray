#include "grpch.h"
#include "ModelManager.h"
#include "ModelLoader.h"
#include "ModelLoaderPool.h"
#include "assimp/cimport.h"
#include "Gray/Algo/Search.h"

namespace Gray
{
    ModelManager::ModelManager()
        : ml( ModelLoaderPool::GetModelLoader(0)),
          nUninit(0)
    {
        ml.AddManager(*this);
    }

    ModelManager::~ModelManager()
    {
        ml.RemoveManager(*this);
    }

    uint ModelManager::GetModelId(const std::string& path)
    {
        static uint nextID = 0;

        int index = Lsearch(paths, path);
    
        if (index == -1)
        {
            nextID++;

            models.push_back(Model());
            IDs.push_back(nextID);
            paths.push_back(path);

            toLoad.Enqueue(std::pair{ path, nextID });
            ml.Notify();

            nUninit++;
            return nextID;
        }

        assert(index < IDs.size());
        return IDs[index];
    }

    bool ModelManager::RequiresLoading()
    {
        return !toLoad.IsEmpty();
    }

    bool ModelManager::RequireInit()
    {
        return (nUninit != 0) || texMan.RequireInit();
    }

    void ModelManager::InitModels()
    {
        while(!toInit.IsEmpty())
        {
            std::pair<const aiScene*, uint> loadResult; 
            toInit.DequeueTo(loadResult);

            auto [scene, id] = loadResult;
            int index = Bsearch(IDs, id);

            if (index != -1 && scene)
            {
                assert(index < models.size());
                assert(index < paths.size());
                models[index].LoadScene(scene, paths[index], texMan);
                aiReleaseImport(scene);
            }

            nUninit--;
        }
        if (texMan.RequireInit())
            texMan.InitTextures();
    }

    std::vector<Model> ModelManager::GetModels(const std::vector<uint>& reqIDs)
    {
        std::vector<Model> reqModels;
        reqModels.reserve(reqIDs.size());

        for (const uint& ID : reqIDs)
        {
            int index = Bsearch(IDs, ID);
            assert(index < models.size());

            reqModels.push_back(models[index]);
        }

        return reqModels;
    }

}