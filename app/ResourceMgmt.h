#ifndef RESOURCE_MGMT_H
#define RESOURCE_MGMT_H

// Standard includes.
#include <map>

// Project includes.
#include "os/OSWrapper.h"
#include "control/Control.h"

namespace app {
class ResourceMgmt {
public:
    // No copy is allowed
    ResourceMgmt(const ResourceMgmt& other) = delete;
    ResourceMgmt& operator=(const ResourceMgmt& other) = delete;

    static ResourceMgmt& getInstance();

    void setControl(std::shared_ptr<Control> control);
    std::shared_ptr<Control> getControl() const;

private:
    ResourceMgmt();

    std::shared_ptr<Control> m_control;

};
} // namespace app

using app::ResourceMgmt;

#endif // RESOURCE_MGMT_H
