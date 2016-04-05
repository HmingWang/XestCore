//
// Created by whaim on 16-4-5.
//

#ifndef XESTCORE_CONFIG_H
#define XESTCORE_CONFIG_H

#include <string>
#include <list>
#include <mutex>
#include <boost/property_tree/ptree.hpp>
#include "Define.h"

class TC_COMMON_API ConfigMgr
{
    ConfigMgr() = default;
    ConfigMgr(ConfigMgr const&) = delete;
    ConfigMgr& operator=(ConfigMgr const&) = delete;
    ~ConfigMgr() = default;

public:
    /// Method used only for loading main configuration files
    bool LoadInitial(std::string const& file, std::string& error);

    static ConfigMgr* instance();

    bool Reload(std::string& error);
    std::string GetStringDefault(std::string const& name, const std::string& def) const;
    bool GetBoolDefault(std::string const& name, bool def) const;
    int GetIntDefault(std::string const& name, int def) const;
    float GetFloatDefault(std::string const& name, float def) const;

    std::string const& GetFilename();
    std::list<std::string> GetKeysByString(std::string const& name);

private:
    std::string _filename;
    boost::property_tree::ptree _config;
    std::mutex _configLock;

    template<class T>
    T GetValueDefault(std::string const& name, T def) const;
};

#define sConfigMgr ConfigMgr::instance()

#endif //XESTCORE_CONFIG_H
