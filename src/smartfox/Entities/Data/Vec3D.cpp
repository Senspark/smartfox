// ===================================================================
//
// Description
//        Contains the implementation of Vec3D
//
// Revision history
//        Date            Description
//        30-Nov-2013        First version
//
// ===================================================================
#include "Vec3D.h"

#include <boost/system/error_code.hpp>
#include <boost/make_shared.hpp>

namespace Sfs2X {
namespace Entities {
namespace Data {
// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
Vec3D::Vec3D(int px, int py, int pz) {
    ix = px;
    iy = py;
    iz = pz;
    useFloat = false;
}

Vec3D::Vec3D(int px, int py) {
    ix = px;
    iy = py;
    iz = 0;
    useFloat = false;
}

Vec3D::Vec3D(float px, float py, float pz) {
    fx = px;
    fy = py;
    fz = pz;
    useFloat = true;
}

Vec3D::Vec3D(float px, float py) {
    fx = px;
    fy = py;
    fz = 0;
    useFloat = true;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
Vec3D::~Vec3D() {}

// -------------------------------------------------------------------
// IsFloat
// -------------------------------------------------------------------
bool Vec3D::IsFloat() const {
    return useFloat;
}

// -------------------------------------------------------------------
// FloatX
// -------------------------------------------------------------------
float Vec3D::FloatX() const {
    return fx;
}

// -------------------------------------------------------------------
// FloatY
// -------------------------------------------------------------------
float Vec3D::FloatY() const {
    return fy;
}

// -------------------------------------------------------------------
// FloatZ
// -------------------------------------------------------------------
float Vec3D::FloatZ() const {
    return fz;
}

// -------------------------------------------------------------------
// IntX
// -------------------------------------------------------------------
std::int32_t Vec3D::IntX() const {
    return ix;
}

// -------------------------------------------------------------------
// IntY
// -------------------------------------------------------------------
std::int32_t Vec3D::IntY() const {
    return iy;
}

// -------------------------------------------------------------------
// IntZ
// -------------------------------------------------------------------
std::int32_t Vec3D::IntZ() const {
    return iz;
}

// -------------------------------------------------------------------
// fromIntArray
// -------------------------------------------------------------------
boost::shared_ptr<Vec3D> Vec3D::fromIntArray(
    const boost::shared_ptr<std::vector<boost::int32_t>>& array) {
    if (array->size() != 3)
        boost::throw_exception(boost::enable_error_info(
            std::runtime_error("Wrong array size. Vec3D requires an array with "
                               "3 parameters (x,y,z)")));

    return boost::shared_ptr<Vec3D>(
        new Vec3D(array->at(0), array->at(1), array->at(2)));
}

// -------------------------------------------------------------------
// fromFloatArray
// -------------------------------------------------------------------
boost::shared_ptr<Vec3D>
Vec3D::fromFloatArray(const boost::shared_ptr<std::vector<float>>& array) {
    if (array->size() != 3)
        boost::throw_exception(boost::enable_error_info(
            std::runtime_error("Wrong array size. Vec3D requires an array with "
                               "3 parameters (x,y,z)")));

    return boost::shared_ptr<Vec3D>(
        new Vec3D(array->at(0), array->at(1), array->at(2)));
}

// -------------------------------------------------------------------
// ToIntArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<std::int32_t>> Vec3D::ToIntArray() const {
    auto returned = boost::make_shared<std::vector<std::int32_t>>();
    returned->push_back(ix);
    returned->push_back(iy);
    returned->push_back(iz);
    return returned;
}

// -------------------------------------------------------------------
// ToFloatArray
// -------------------------------------------------------------------
boost::shared_ptr<std::vector<float>> Vec3D::ToFloatArray() const {
    auto returned = boost::make_shared<std::vector<float>>();
    returned->push_back(fx);
    returned->push_back(fy);
    returned->push_back(fz);
    return returned;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<std::string> Vec3D::ToString() const {
    char buffer[512];

    if (IsFloat()) {
        std::sprintf(buffer, "(%f,%f,%f)\n", fx, fy, fz);
    } else {
        std::sprintf(buffer, "(%d,%d,%d)\n", ix, iy, iz);
    }

    boost::shared_ptr<std::string> str(new std::string(buffer));
    return str;
}

// -------------------------------------------------------------------
// fromArray
// -------------------------------------------------------------------
boost::shared_ptr<Vec3D>
Vec3D::fromArray(int tp, const boost::shared_ptr<void>& array) {
    if (tp == SFSDATATYPE_INT_ARRAY) {
        return fromIntArray(
            boost::static_pointer_cast<std::vector<std::int32_t>>(array));
    } else if (tp == SFSDATATYPE_FLOAT_ARRAY) {
        return fromFloatArray(
            boost::static_pointer_cast<std::vector<float>>(array));
    } else
        boost::throw_exception(boost::enable_error_info(std::runtime_error(
            "Invalid Array Type, cannot convert to Vec3D!")));
}
} // namespace Data
} // namespace Entities
} // namespace Sfs2X
