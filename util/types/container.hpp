/**
 * @file container.hpp
 * @brief Container type
 */

#ifndef _UTIL_TYPES_CONTAINER_HPP_
#define _UTIL_TYPES_CONTAINER_HPP_

#include <string>

namespace types {
struct Container {
  std::string name;   // Name of the container (DNS)
  std::string image;  // Container image name
};
}  // namespace types

#endif
