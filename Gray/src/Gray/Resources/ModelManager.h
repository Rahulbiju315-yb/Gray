#pragma once
#include "thread"
#include "mutex"
#include "vector"
#include "Gray/Graphics/Model/Model.h"
#include "TextureManager.h"
#include "Gray/DS/SafeQueue.h"

typedef unsigned int uint;

namespace Gray
{
    class ModelManager
    {
    public:
        ModelManager();
        ModelManager(const ModelManager&) = delete;
        ModelManager(ModelManager&&) = delete;

        ~ModelManager();

        ModelManager& operator=(const ModelManager&) = delete;
        ModelManager& operator=(ModelManager&&) = delete;

        uint GetModelId(const std::string& path);
        bool RequiresLoading();
        bool RequireInit();
        void InitModels();

        std::vector<Model> GetModels(const std::vector<uint>& reqIDs);

    private:
        TextureManager texMan;

        std::vector<Model> models;
        std::vector<uint> IDs;
        std::vector<std::string> paths;

        SafeQueue<std::pair<std::string, uint>> toLoad;
        SafeQueue<std::pair<const aiScene*, uint>> toInit;

        uint nUninit;
        friend class ModelLoader;
        ModelLoader& ml;
    };
}