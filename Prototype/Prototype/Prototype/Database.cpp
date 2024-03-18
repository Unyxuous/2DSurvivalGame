#include "Database.h"

Database::Database() {
    options.create_if_missing = true;
    status = leveldb::DB::Open(options, "./testdb", &db);
    //Make sure database was opened/made
    if (status.ok() == false)
    {
        std::cerr << "Unable to make/open database." << std::endl;
        std::cerr << status.ToString() << std::endl;
    }
}

Database::~Database() {
    //Close database
    delete db;
}

/****************************************************************************************************************************/
// Add 256 values to the database
//leveldb::WriteOptions writeOptions;
//for (unsigned int i = 0; i < 256; ++i)
//{
    //std::ostringstream keyStream;
    //keyStream << "Key" << i;

    //std::ostringstream valueStream;
    //valueStream << "Test data value: " << i;

    //db->Put(writeOptions, keyStream.str(), valueStream.str());
//}

//Iterate over each item in the database and print them
//leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());

//for (it->SeekToFirst(); it->Valid(); it->Next())
//{
    //std::cout << it->key().ToString() << " : " << it->value().ToString() << std::endl;
//}

//if (false == it->status().ok())
//{
    //std::cerr << "An error was found during the scan" << std::endl;
    //std::cerr << it->status().ToString() << std::endl;
//}

//delete it;
/****************************************************************************************************************************/