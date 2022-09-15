/**
 * @file sidecar_handler.hpp
 * @brief Dynamic Admission Control admission webhooks
 */

#ifndef _SIDECAR_HANDLER_HPP_
#define _SIDECAR_HANDLER_HPP_

#include "istio.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace sidecar {

/**
 * @brief K8s sidecat injector schema
 */
struct Sidecar {
  std::string name;                                          // yaml: "name"
  std::vector<types::Container> initContainers;              // yaml: "initContainers"
  std::vector<types::Container> containers;                  // yaml: "containers"
  std::vector<types::Volume> volumes;                        // yaml: "volumes"
  std::unordered_map<std::string, std::string> annotations;  // yaml: "annotations"
  std::unordered_map<std::string, std::string> labels;       // yaml: "labels"
};

/**
 * @brief Sidecar injector patcher
 */
class SidecarInjectorPatcher {
private:
  std::string injectPrefix;
  std::string injectName;
  std::string sidecarDataKey;
  bool allowAnnotationOverrides;
  bool allowLabelOverrides;

public:
  /**
   * @brief Get annotation of the sidecar
   * @return std::string Annotation
   */
  std::string sidecarInjectionAnnotation();

  /**
   * @brief From pod to get the configmap for latter process
   *
   * @return std::vector<std::string> configmap configuration
   */
  std::vector<std::string> configmapSidecarNames(std::string namespace_, types::Pod pod);

  /**
   * @brief Create a Object Patches object
   *
   * @param newMap      the new configmap
   * @param existingMap the existing config
   * @param path
   * @param override
   * @return std::vector<types::PatchOperaion>
   */
  std::vector<types::PatchOperaion> createObjectPatches(std::unordered_map<std::string, std::string> newMap,
                                                        std::unordered_map<std::string, std::string> existingMap,
                                                        std::string path,
                                                        bool override);

  /**
   * @brief Handle pod create patch
   *
   * @param namespace_
   * @param pod
   * @return std::vector<types::PatchOperaion>
   */
  std::vector<types::PatchOperaion> PatchPodCreate(std::string namespace_, types::Pod pod);
};

}  // namespace sidecar

#endif  // _SIDECAR_HANDLER_HPP_
