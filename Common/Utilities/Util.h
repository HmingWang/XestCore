//
// Created by whaim on 16-4-7.
//

#ifndef XESTCORE_UTIL_H
#define XESTCORE_UTIL_H

#include <vector>
#include <string>
#include "Define.h"

class TC_COMMON_API Tokenizer
{
public:
    typedef std::vector<char const*> StorageType;

    typedef StorageType::size_type size_type;

    typedef StorageType::const_iterator const_iterator;
    typedef StorageType::reference reference;
    typedef StorageType::const_reference const_reference;

public:
    Tokenizer(const std::string &src, char const sep, uint32 vectorReserve = 0);
    ~Tokenizer() { delete[] m_str; }

    const_iterator begin() const { return m_storage.begin(); }
    const_iterator end() const { return m_storage.end(); }

    size_type size() const { return m_storage.size(); }

    reference operator [] (size_type i) { return m_storage[i]; }
    const_reference operator [] (size_type i) const { return m_storage[i]; }

private:
    char* m_str;
    StorageType m_storage;
};

TC_COMMON_API bool utf8ToConsole(const std::string& utf8str, std::string& conStr);
TC_COMMON_API bool consoleToUtf8(const std::string& conStr, std::string& utf8str);
TC_COMMON_API bool Utf8FitTo(const std::string& str, std::wstring const& search);
TC_COMMON_API void utf8printf(FILE* out, const char *str, ...);
TC_COMMON_API void vutf8printf(FILE* out, const char *str, va_list* ap);
TC_COMMON_API bool Utf8ToUpperOnlyLatin(std::string& utf8String);

#endif //XESTCORE_UTIL_H
