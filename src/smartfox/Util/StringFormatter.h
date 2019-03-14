// ===================================================================
//
// Description
//        Contains the utility to format strings
//
// Revision history
//        Date            Description
//        30-Nov-2012        First version
//
// ===================================================================
#ifndef __StringFormatter__
#define __StringFormatter__

#include <cstdio>

#include <boost/shared_ptr.hpp> // Boost Asio shared pointer
#include <boost/make_shared.hpp>

#if defined(_MSC_VER)
#pragma warning(disable : 4786) // STL library: disable warning 4786; this
                                // warning is generated due to a Microsoft bug
#endif
#include <string> // STL library: string object

namespace Sfs2X {
namespace Util {

// -------------------------------------------------------------------
// StringFormatter
// -------------------------------------------------------------------
template <class... Args>
std::string StringFormatter(const std::string& stringFormat, Args&&... args) {
    auto size = static_cast<std::size_t>(
        std::snprintf(nullptr, 0, stringFormat.c_str(), args...) + 1);
    auto buffer = std::make_unique<char[]>(size);
    std::snprintf(buffer.get(), size, stringFormat.c_str(),
                  std::forward<Args>(args)...);
    return std::string(buffer.get(), size);
}

// -------------------------------------------------------------------
// Utf8toWStr
// -------------------------------------------------------------------
inline void Utf8toWStr(const boost::shared_ptr<std::string>& src,
                       const boost::shared_ptr<std::wstring>& dest) {
    dest->clear();
    wchar_t w = 0;
    int bytes = 0;
    wchar_t err = L'?';
    for (std::size_t i = 0; i < src->size(); i++) {
        unsigned char c = (unsigned char)(*src)[i];
        if (c <= 0x7f) {
            // first byte
            if (bytes) {
                dest->push_back(err);
                bytes = 0;
            }
            dest->push_back((wchar_t)c);
        } else if (c <= 0xbf) {
            // second/third/etc byte
            if (bytes) {
                w = ((w << 6) | (c & 0x3f));
                bytes--;
                if (bytes == 0) {
                    dest->push_back(w);
                }
            } else {
                dest->push_back(err);
            }
        } else if (c <= 0xdf) {
            // 2byte sequence start
            bytes = 1;
            w = c & 0x1f;
        } else if (c <= 0xef) {
            // 3byte sequence start
            bytes = 2;
            w = c & 0x0f;
        } else if (c <= 0xf7) {
            // 3byte sequence start
            bytes = 3;
            w = c & 0x07;
        } else {
            dest->push_back(err);
            bytes = 0;
        }
    }
    if (bytes) {
        dest->push_back(err);
    }
}

// -------------------------------------------------------------------
// WStrToUtf8
// -------------------------------------------------------------------
inline void WStrToUtf8(const boost::shared_ptr<std::wstring>& src,
                       const boost::shared_ptr<std::string>& dest) {
    dest->clear();
    for (std::size_t i = 0; i < src->size(); i++) {
        wchar_t w = (*src)[i];
        if (w <= 0x7f) {
            dest->push_back(static_cast<char>(w));
        } else if (w <= 0x7ff) {
            dest->push_back(static_cast<char>(0xc0 | ((w >> 6) & 0x1f)));
            dest->push_back(static_cast<char>(0x80 | (w & 0x3f)));
        } else if (w <= 0xffff) {
            dest->push_back(static_cast<char>(0xe0 | ((w >> 12) & 0x0f)));
            dest->push_back(static_cast<char>(0x80 | ((w >> 6) & 0x3f)));
            dest->push_back(static_cast<char>(0x80 | (w & 0x3f)));
        } else if (w <= 0x10ffff) {
            dest->push_back(static_cast<char>(0xf0 | (((unsigned long int)w >> 18) & 0x07)));
            dest->push_back(static_cast<char>(0x80 | ((w >> 12) & 0x3f)));
            dest->push_back(static_cast<char>(0x80 | ((w >> 6) & 0x3f)));
            dest->push_back(static_cast<char>(0x80 | (w & 0x3f)));
        } else {
            dest->push_back('?');
        }
    }
}
} // namespace Util
} // namespace Sfs2X

#endif
