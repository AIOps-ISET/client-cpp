#include "sidecar_handler.hpp"

#include "spdlog/spdlog.h"

#include <sstream>

using sidecar::SidecarInjectorPatcher;

std::string SidecarInjectorPatcher::sidecarInjectionAnnotation() { return injectPrefix + "/" + injectName; }

std::vector<std::string> SidecarInjectorPatcher::configmapSidecarNames(std::string namespace_, types::Pod pod) {
  std::string podName = pod.getName();
  if (podName.empty()) {
    podName = pod.getGenerateName();
  }
  std::unordered_map<std::string, std::string> annotations{};
  if (!pod.getAnnotations().empty()) {
    annotations = pod.getAnnotations();
  }
  if (annotations.count(sidecarInjectionAnnotation()) == 0) {
    spdlog::info("Skipping mutation for {}. No action required", pod.getName());
    return {};
  } else {
    std::string sidecars = annotations[sidecarInjectionAnnotation()];
    std::vector<std::string> parts{};
    // Here, we use stringstream to split the string
    // which makes our life easier.
    std::stringstream ss{sidecars};
    std::string temp{};
    while (getline(ss, temp, ',')) {
      parts.push_back(std::move(temp));
    }
    spdlog::info("Sidecar injection for {}/{}: sidecats: {}", namespace_, podName, sidecars);
    return parts;
  }
}

std::vector<types::PatchOperaion> SidecarInjectorPatcher::createObjectPatches(
    std::unordered_map<std::string, std::string> newMap,
    std::unordered_map<std::string, std::string> existingMap,
    std::string path,
    bool override) {
  // TODO: this operation needs admission PatchOperation.
  return {};
}

std::vector<types::PatchOperaion> SidecarInjectorPatcher::PatchPodCreate(std::string namespace_, types::Pod pod) {
  std::string podName = pod.getName();
  if (podName.empty()) {
    podName = pod.getGenerateName();
  }
  std::vector<types::PatchOperaion> patches{};
  std::vector<std::string> configmapNames = configmapSidecarNames(namespace_, pod);
  if (!configmapNames.empty()) {
    /*
     * In this process, we will need to get the configmap
     * and use `createObjectPatches`.
     */
    for (std::string &name : configmapNames) {
      // TODO: Here, we need the support of the client operation.
    }
  }
  return {};
}
