#ifndef __S21_GETDIRECTORY_H__
#define __S21_GETDIRECTORY_H__

#include <cstring>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <shlwapi.h>  // Для PathRemoveFileSpec
#include <windows.h>
#pragma comment(lib, "Shlwapi.lib")

std::string getExecutableDirectory() {
  char buffer[MAX_PATH];
  GetModuleFileName(NULL, buffer, MAX_PATH);
  PathRemoveFileSpec(buffer);
  std::string path = std::string(buffer);
  std::string toRemove = "/install/";
  size_t pos = path.find(toRemove);
  if (pos != std::string::npos) path.erase(pos, toRemove.length());
  return path;
}

#elif __APPLE__
#include <mach-o/dyld.h>

std::string getExecutableDirectory() {
  uint32_t size = 0;
  _NSGetExecutablePath(NULL, &size);
  std::string path(size, '\0');
  if (_NSGetExecutablePath(&path[0], &size) == 0) {
    char* lastSlash = strrchr(&path[0], '/');
    if (lastSlash) {
      *lastSlash = '\0';
      std::string toRemove = "/install/";
      size_t pos = path.find(toRemove);
      if (pos != std::string::npos) path.erase(pos, toRemove.length());
      return path;
    }
  }
  return "";
}

#else
#include <limits.h>
#include <string.h>
#include <unistd.h>

std::string getExecutableDirectory() {
  char buffer[PATH_MAX];
  ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
  if (len != -1) {
    buffer[len] = '\0';
    char* lastSlash = strrchr(buffer, '/');
    if (lastSlash) {
      *lastSlash = '\0';
      std::string path = std::string(buffer);
      std::string toRemove = "/install";
      size_t pos = path.find(toRemove);
      if (pos != std::string::npos) path.erase(pos, toRemove.length());
      return path;
    }
  }
  return "";
}

#endif

#endif