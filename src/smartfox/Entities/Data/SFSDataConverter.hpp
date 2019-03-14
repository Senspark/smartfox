//
//  SFSDataConverter.hpp
//  smartfox
//
//  Created by eps on 1/24/18.
//

#ifndef SFS_DATA_CONVERTER_HPP
#define SFS_DATA_CONVERTER_HPP

#include <boost/shared_ptr.hpp>

namespace Sfs2X {
namespace Entities {
namespace Data {
class DataConverter {
public:
    explicit DataConverter(const boost::shared_ptr<void>& wrapperData);

    std::string toBool() const;
    std::string toByte() const;
    std::string toShort() const;
    std::string toInt() const;
    std::string toLong() const;
    std::string toFloat() const;
    std::string toDouble() const;
    std::string toString() const;
    std::string toBoolArray() const;
    std::string toByteArray() const;
    std::string toShortArray() const;
    std::string toIntArray() const;
    std::string toLongArray() const;
    std::string toFloatArray() const;
    std::string toDoubleArray() const;
    std::string toStringArray() const;

private:
    boost::shared_ptr<void> wrapperData_;
};
} // namespace Data
} // namespace Entities
} // namespace Sfs2X

#endif /* SFS_DATA_CONVERTER_HPP */
