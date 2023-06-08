#ifndef SYS_RES_MGMT_SINGLETON
#define SYS_RES_MGMT_SINGLETON

// Standard includes.
#include <map>

// Project includes.
#include "os/OSWrapper.h"
#include "control/Control.h"

namespace app {
class SysResMgmtSingleton {
public:
    // No copy is allowed
    SysResMgmtSingleton(const SysResMgmtSingleton& other) = delete;
    SysResMgmtSingleton& operator=(const SysResMgmtSingleton& other) = delete;

    static SysResMgmtSingleton& getInstance();

    void setControl(std::shared_ptr<Control> control);
    std::shared_ptr<Control> getControl() const;

private:
    SysResMgmtSingleton();

    std::shared_ptr<Control> m_control;

};
} // namespace app

using app::SysResMgmtSingleton;

#endif // SYS_RES_MGMT_SINGLETON