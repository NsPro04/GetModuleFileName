#define GMFN_EXPORTS
#include <GMFN/GMFN.h>

#include <windows.h>
#include <psapi.h>

#include <string>

GMFN_API std::expected<std::filesystem::path, GMFN::v1::WIN_DWORD> GMFN::v1::K32GetModuleFileName(void *hModule) noexcept {
  try {
    std::wstring path_wstr(MAX_PATH, L'\0');

    const DWORD old_error_code = ::GetLastError();

    while (true) {
      const DWORD path_size  = ::GetModuleFileNameW(reinterpret_cast<HMODULE>(hModule), path_wstr.data(), path_wstr.size());
      const DWORD error_code = ::GetLastError();
      ::SetLastError(old_error_code);

      if (!path_size) {
        return std::unexpected(error_code);
      }

      if (path_size < path_wstr.size()) {
        path_wstr.erase(path_size);
        break;
      }

      path_wstr.resize(path_wstr.size() + MAX_PATH, L'\0');
    }

    std::filesystem::path tmp = std::move(path_wstr);

    return std::move(tmp);
  } catch (...) {
    return std::unexpected(ERROR_NOT_ENOUGH_MEMORY);
  }
}

GMFN_API std::expected<std::filesystem::path, GMFN::v1::WIN_DWORD> GMFN::v1::K32GetModuleFileNameEx(void *hModule, void *process) noexcept {
  if (process == nullptr)
    process = ::GetCurrentProcess();

  try {
    std::wstring path_wstr(MAX_PATH, L'\0');

    const DWORD old_error_code = ::GetLastError();

    while (true) {
      const DWORD path_size  = ::K32GetModuleFileNameExW(reinterpret_cast<HANDLE>(process), reinterpret_cast<HMODULE>(hModule), path_wstr.data(), path_wstr.size());
      const DWORD error_code = ::GetLastError();
      ::SetLastError(old_error_code);

      if (!path_size) {
        return std::unexpected(error_code);
      }

      // https://learn.microsoft.com/en-us/windows/win32/api/psapi/nf-psapi-getmodulefilenameexw
      if ((path_size + /*(windows_version >= 10)*/ 1) < path_wstr.size()) {
        path_wstr.erase(path_size);
        break;
      }

      path_wstr.resize(path_wstr.size() + MAX_PATH, L'\0');
    }

    std::filesystem::path tmp = std::move(path_wstr);

    return std::move(tmp);
  } catch (...) {
    return std::unexpected(ERROR_NOT_ENOUGH_MEMORY);
  }
}