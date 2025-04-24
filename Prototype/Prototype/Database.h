#pragma once

#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "leveldb/db.h"

#include "Chunk.h"

class Database
{
	const std::set<std::string> protectedKeys = {
		"playerSettings"
	};

	leveldb::DB* db;
	leveldb::Options options;
	leveldb::Status status;

public:
	Database();
	~Database();
	void deleteWorld();
	std::unordered_map<std::string, Chunk> loadChunks(std::set<std::string>);
	void saveChunks(std::unordered_map<std::string, Chunk>);
};
