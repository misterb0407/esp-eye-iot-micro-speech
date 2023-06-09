// Standard includes.
#include <cassert>

// Project includes.
#include "ResourceMgmt.h"

ResourceMgmt::ResourceMgmt():
    m_control(nullptr)
{}

ResourceMgmt& ResourceMgmt::getInstance() {
    static ResourceMgmt s_instance;
    return s_instance;
}

void ResourceMgmt::setControl(std::shared_ptr<Control> control) {
    assert(control != nullptr);
    m_control = control;
}

std::shared_ptr<Control> ResourceMgmt::getControl() const {
    return m_control;
}
