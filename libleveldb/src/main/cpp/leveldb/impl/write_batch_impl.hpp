#pragma once

#include "write_batch.hpp"
#include "leveldb/write_batch.h"

namespace dd {

class WriteBatchImpl : public WriteBatch {
public:
    WriteBatchImpl();
    ~WriteBatchImpl();

    virtual void put(const std::string & key, const std::string & value) override;

    virtual void del(const std::string & key) override;

    virtual void clear() override;

protected:
    leveldb::WriteBatch batch_;

    friend class LeveldbImpl;
};

}  // namespace dd
