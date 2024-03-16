#include "kv_storage.h"

class KeyValueServiceImpl {
public:
    KeyValueServiceImpl(KeyValueStorage& storage)
        : storage_(storage)
    {}
private:
    KeyValueStorage& storage_;
};
