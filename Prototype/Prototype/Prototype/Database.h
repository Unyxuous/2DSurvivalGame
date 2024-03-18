#pragma once
#include "leveldb/db.h"

#include <iostream>

static class Database
{
private:
	leveldb::DB* db;
	leveldb::Options options;
	leveldb::Status status;

	~Database();

public:
	Database();
};

