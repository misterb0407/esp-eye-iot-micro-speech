// Standard includes.
#include <cassert>

// Project includes.
#include "SysResMgmtSingleton.h"

SysResMgmtSingleton::SysResMgmtSingleton():
    m_control(nullptr)
{}

SysResMgmtSingleton& SysResMgmtSingleton::getInstance() {
    static SysResMgmtSingleton s_instance;
    return s_instance;
}

void SysResMgmtSingleton::setControl(std::shared_ptr<Control> control) {
    assert(control != nullptr);
    m_control = control;
}

std::shared_ptr<Control> SysResMgmtSingleton::getControl() const {
    return m_control;
}