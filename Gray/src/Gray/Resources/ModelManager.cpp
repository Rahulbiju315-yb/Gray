#include "grpch.h"
#include "ModelManager.h"
#include "Gray/Algo/Search.h"
#include "ModelLoader.h"
#include "assimp/cimport.h"

namespace Gray
{
    ModelManager::ModelManager()
        : ml( ModelLoader::GetModelLoader(0))
    {
        ml.AddManager(*this);
    }

    ModelManager::~ModelManager()
    {
        ml.RemoveManager(*this);
    }

    uint ModelManager::GetModel(const std::string& path)
    {
        static uint nextID = 0;

        int index = Lsearch(paths, path);
    
        if (index == -1)
        {
            nextID++;

            models.push_back(Model());
            IDs.push_back(nextID);
            paths.push_back(path);

            toLoad.Enqueue({ path, nextID });
            
            return nextID;
        }

        assert(index < IDs.size());
        return IDs[index];
    }

    bool ModelManager::RequireLoading()
    {
        return toLoad.IsEmpty();
    }

    bool ModelManager::RequireInit()
    {
        return toInit.IsEmpty();
    }

    void ModelManager::InitModels()
    {
        while(RequireInit())
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
        }
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