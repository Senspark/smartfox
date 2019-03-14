//
//  SFSDataConverter.cpp
//  smartfox
//
//  Created by eps on 1/24/18.
//

#include <cinttypes>
#include <vector>

#include "smartfox/Entities/Data/SFSDataConverter.hpp"
#include "smartfox/Util/StringFormatter.h"

#include <boost/make_shared.hpp>

namespace Sfs2X {
namespace Entities {
namespace Data {
using Self = DataConverter;

Self::DataConverter(const boost::shared_ptr<void>& wrapperData)
    : wrapperData_(wrapperData) {}

std::string Self::toBool() const {
    auto data = boost::static_pointer_cast<bool>(wrapperData_);
    return Util::StringFormatter("[%d]", *data);
}

std::string Self::toByte() const {
    auto data = boost::static_pointer_cast<std::uint8_t>(wrapperData_);
    return Util::StringFormatter("[" PRIu8 "]", *data);
}

std::string Self::toShort() const {
    auto data = boost::static_pointer_cast<std::int16_t>(wrapperData_);
    return Util::StringFormatter("[" PRId16 "]", *data);
}

std::string Self::toInt() const {
    auto data = boost::static_pointer_cast<std::int32_t>(wrapperData_);
    return Util::StringFormatter("[" PRId32 "]", *data);
}

std::string Self::toLong() const {
    auto data = boost::static_pointer_cast<std::int64_t>(wrapperData_);
    return Util::StringFormatter("[" PRId64 "]", *data);
}

std::string Self::toFloat() const {
    auto data = boost::static_pointer_cast<float>(wrapperData_);
    return Util::StringFormatter("[%f]", *data);
}

std::string Self::toDouble() const {
    auto data = boost::static_pointer_cast<double>(wrapperData_);
    return Util::StringFormatter("[%f]", *data);
}

std::string Self::toString() const {
    auto data = boost::static_pointer_cast<std::string>(wrapperData_);
    return Util::StringFormatter("[%s]", data->c_str());
}

std::string Self::toBoolArray() const {
    auto data =
        boost::static_pointer_cast<std::vector<boost::shared_ptr<bool>>>(
            wrapperData_);

    std::string strDump;
    strDump.append("[");
    for (auto&& item : *data) {
        strDump.append(Self(item).toBool());
    }
    strDump.append("]");
    return strDump;
}

std::string Self::toByteArray() const {
    auto data = boost::static_pointer_cast<
        std::vector<boost::shared_ptr<std::uint8_t>>>(wrapperData_);

    std::string strDump;
    strDump.append("[");
    for (auto&& item : *data) {
        strDump.append(Self(item).toByte());
    }
    strDump.append("]");
    return strDump;
}

std::string Self::toShortArray() const {
    auto data = boost::static_pointer_cast<
        std::vector<boost::shared_ptr<std::int16_t>>>(wrapperData_);

    std::string strDump;
    strDump.append("[");
    for (auto&& item : *data) {
        strDump.append(Self(item).toShort());
    }
    strDump.append("]");
    return strDump;
}

std::string Self::toIntArray() const {
    auto data = boost::static_pointer_cast<
        std::vector<boost::shared_ptr<std::int32_t>>>(wrapperData_);

    std::string strDump;
    strDump.append("[");
    for (auto&& item : *data) {
        strDump.append(Self(item).toInt());
    }
    strDump.append("]");
    return strDump;
}

std::string Self::toLongArray() const {
    auto data = boost::static_pointer_cast<
        std::vector<boost::shared_ptr<std::int64_t>>>(wrapperData_);

    std::string strDump;
    strDump.append("[");
    for (auto&& item : *data) {
        strDump.append(Self(item).toLong());
    }
    strDump.append("]");
    return strDump;
}

std::string Self::toFloatArray() const {
    auto data =
        boost::static_pointer_cast<std::vector<boost::shared_ptr<float>>>(
            wrapperData_);

    std::string strDump;
    strDump.append("[");
    for (auto&& item : *data) {
        strDump.append(Self(item).toFloat());
    }
    strDump.append("]");
    return strDump;
}

std::string Self::toDoubleArray() const {
    auto data =
        boost::static_pointer_cast<std::vector<boost::shared_ptr<double>>>(
            wrapperData_);

    std::string strDump;
    strDump.append("[");
    for (auto&& item : *data) {
        strDump.append(Self(item).toDouble());
    }
    strDump.append("]");
    return strDump;
}

std::string Self::toStringArray() const {
    auto data =
        boost::static_pointer_cast<std::vector<boost::shared_ptr<std::string>>>(
            wrapperData_);

    std::string strDump;
    strDump.append("[");
    for (auto&& item : *data) {
        strDump.append(Self(item).toString());
    }
    strDump.append("]");
    return strDump;
}
} // namespace Data
} // namespace Entities
} // namespace Sfs2X
