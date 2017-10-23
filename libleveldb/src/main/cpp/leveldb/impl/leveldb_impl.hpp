#pragma once

#include "leveldb.hpp"
#include "leveldb/db.h"

#define DB_NULL_RETURN(value) \
do { \
    if (db_ == nullptr) { \
        LOGW("WARN: db not opened!"); \
        status_ = status::NOT_OPENED; \
        return value; \
    } \
} while (0)

#define DB_NOT_NULL_RETURN(value) \
do { \
    if (db_ != nullptr) { \
        LOGW("WARN: db not closed!"); \
        status_ = status::NOT_CLOSED; \
        return value; \
    } \
} while (0)

namespace dd {

class LeveldbImpl : public Leveldb {
public:
    LeveldbImpl();
    ~LeveldbImpl();

    virtual status open(const std::string & name) override;

    virtual std::string get(const std::string & key) override;

    virtual std::string get_def(const std::string & key, const std::string & def) override;

    virtual status put(const std::string & key, const std::string & value) override;

    virtual status del(const std::string & key) override;

    virtual status write(const std::shared_ptr<WriteBatch> & batch) override;

    virtual status close() override;

    virtual status result() override;

private:
    status set_status(const leveldb::Status& status);

    enum status status_;
    std::unique_ptr<leveldb::DB> db_;
};

}  // namespace dd
