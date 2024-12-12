#ifndef  MY_API_MEMENTO_HPP
#define  MY_API_MEMENTO_HPP

#include "../../api/api_memento.hpp"

#include <cassert>

namespace psapi
{
    template <typename SnapshotType>
    class Mementable : public IMementable<SnapshotType>
    {
    public:
         Mementable()           = default;
        ~Mementable() override  = default;

        virtual std::unique_ptr<SnapshotType> save() override;
        virtual void restore(SnapshotType* snapshot) override;    
    };

    template <typename SnapshotType>
    std::unique_ptr<SnapshotType> psapi::Mementable<SnapshotType>::save()
    {
        assert(false && "ERROR!!! Function is not implemented in this release!\n");
    }

    template <typename SnapshotType>
    void psapi::Mementable<SnapshotType>::restore(SnapshotType* snapshot)
    {
        assert(false && "ERROR!!! Function is not implemented in this release!\n");
    }
}

#endif //MY_API_MEMENTO_HPP