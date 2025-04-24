#include "Database.h"

Database::Database() {
    options.create_if_missing = true;
    status = leveldb::DB::Open(options, "./world", &db);

    if (status.ok() != true) {
        std::cout << status.ToString();
    }
}

Database::~Database() {
    delete db;
}


void Database::deleteWorld() {
    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());

    for (it->SeekToLast(); it->Valid(); it->Prev()) {
        // only delete if it isn't protected
        if (protectedKeys.find(it->key().ToString()) == protectedKeys.end()) {
            std::string key = it->key().ToString();
            db->Delete(leveldb::WriteOptions(), key);
        }
    }
    assert(it->status().ok());  // Check for any errors found during the scan

    delete it;
}

void Database::saveChunks(std::unordered_map<std::string, Chunk> chunks) {
    for (auto& pair : chunks) {
        db->Put(leveldb::WriteOptions(), pair.first, pair.second.chunkData());
    }
}

std::unordered_map<std::string, Chunk> Database::loadChunks(std::set<std::string> chunksToLoad) {
    std::unordered_map<std::string, Chunk> loadedChunks;

    for (std::string chunkToLoad : chunksToLoad) {
        std::string chunkData = "";
        db->Get(leveldb::ReadOptions(), chunkToLoad, &chunkData);

        // only return chunks that exist
        if (chunkData != "") {
            Chunk loadedChunk(Grid::strToV2i(chunkToLoad), chunkData);
            loadedChunks.emplace(chunkToLoad, loadedChunk);
        }
    }

    return loadedChunks;
}