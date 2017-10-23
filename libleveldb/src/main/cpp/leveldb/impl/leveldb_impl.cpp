#include "leveldb_impl.hpp"
#include "status.hpp"
#include "write_batch_impl.hpp"

#include "log.hpp"

namespace dd {

std::shared_ptr<Leveldb> Leveldb::create() {
    return std::make_shared<LeveldbImpl>();
}

LeveldbImpl::LeveldbImpl() : status_(status::OK), db_(nullptr) {
    DBG_LOGV(__func__);
}

LeveldbImpl::~LeveldbImpl() {
    DBG_LOGV(__func__);
}

status LeveldbImpl::open(const std::string & name) {
    DB_NOT_NULL_RETURN(status::NOT_CLOSED);
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status s = leveldb::DB::Open(options, name, &db);
    db_.reset(db);
    return set_status(s);
}

std::string LeveldbImpl::get(const std::string & key) {
    return get_def(key, STR_NONE);
}

std::string LeveldbImpl::get_def(const std::string & key, const std::string & def) {
    DB_NULL_RETURN(def);
    std::string value;
    leveldb::Status s = db_->Get(leveldb::ReadOptions(), key, &value);
    set_status(s);
    return s.ok() ? value : def;
}

status LeveldbImpl::put(const std::string & key, const std::string & value) {
    DB_NULL_RETURN(status::NOT_OPENED);
    leveldb::Status s = db_->Put(leveldb::WriteOptions(), key, value);
    return set_status(s);
}

status LeveldbImpl::del(const std::string & key) {
    DB_NULL_RETURN(status::NOT_OPENED);
    leveldb::Status s = db_->Delete(leveldb::WriteOptions(), key);
    return set_status(s);
}

status LeveldbImpl::write(const std::shared_ptr<WriteBatch> & batch) {
    DB_NULL_RETURN(status::NOT_OPENED);
    leveldb::WriteBatch& batch_ = std::static_pointer_cast<WriteBatchImpl>(batch)->batch_;
    leveldb::Status s = db_->Write(leveldb::WriteOptions(), &batch_);
    return set_status(s);
}

status LeveldbImpl::close() {
    DB_NULL_RETURN(status::NOT_OPENED);
    db_.reset(nullptr);
    status_ = status::OK;
    return status_;
}

status LeveldbImpl::result() {
    return status_;
}

status LeveldbImpl::set_status(const leveldb::Status& s) {
    if (s.ok()) {
        status_ = status::OK;
    } else {
        //LOGW("leveldb status, %s", s.ToString());
        if (s.IsNotFound()) {
            status_ = status::NOT_FOUND;
        } else if (s.IsCorruption()) {
            status_ = status::CORRUPTION;
        } else if (s.IsNotSupportedError()) {
            status_ = status::NOT_SUPPORTED;
        } else if (s.IsInvalidArgument()) {
            status_ = status::INVALID_ARGUMENT;
        } else if (s.IsIOError()) {
            status_ = status::IO_ERROR;
        } else {
            status_ = status::UNKNOWN;
        }
    }
    return status_;
}

}  // namespace dd
