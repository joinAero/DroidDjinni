#include "write_batch_impl.hpp"

#include "log.hpp"

namespace dd {

std::shared_ptr<WriteBatch> WriteBatch::create() {
    return std::make_shared<WriteBatchImpl>();
}

WriteBatchImpl::WriteBatchImpl() : batch_(leveldb::WriteBatch()) {
    DBG_LOGV(__func__);
}

WriteBatchImpl::~WriteBatchImpl() {
    DBG_LOGV(__func__);
}

void WriteBatchImpl::put(const std::string & key, const std::string & value) {
    batch_.Put(key, value);
}

void WriteBatchImpl::del(const std::string & key) {
    batch_.Delete(key);
}

void WriteBatchImpl::clear() {
    batch_.Clear();
}

}  // namespace dd
