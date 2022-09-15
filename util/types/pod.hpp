/**
 * @file pod.hpp
 * @brief Pod type
 */

#ifndef _UTIL_TYPES_POD_HPP_
#define _UTIL_TYPES_POD_HPP_

#include <string>
#include <unordered_map>

namespace types {
class Pod {
public:
  /**
   * @brief Get the Name object
   * @return std::string pod name
   */
  std::string getName() {
    // TODO: this part is hardcoded. Need to revise later
    return "pod";
  }
  /**
   * @brief Generate a random string for pod
   *
   * @return std::string generated pad name
   */
  std::string getGenerateName() {
    // TODO: this part is hardcoded. Need to revise later
    return "pod";
  }
  /**
   * @brief Get the annotations of pod
   *
   * @return std::unordered_map<std::string, std::string>
   */
  std::unordered_map<std::string, std::string> getAnnotations() {
    // TODO: this part is hardcoded. Need to revise later
    return {};
  }
};
}  // namespace types

#endif
