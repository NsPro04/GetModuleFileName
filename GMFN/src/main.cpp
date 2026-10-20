#ifndef GMFN_EXPORTS
#  define GMFN_EXPORTS
#endif // GMFN_EXPORTS

#include <GMFN/GMFN.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <psapi.h>

#include <string>

GMFN_API std::expected<std::filesystem::path, GMFN::v1::WIN_DWORD> GMFN::v1::K32GetModuleFileName(void *hModule) noexcept {
  const DWORD old_error_code = ::GetLastError();

  try {
    std::wstring path_wstr(MAX_PATH, L'\0');

    while (true) {
      const DWORD path_size  = ::GetModuleFileNameW(static_cast<HMODULE>(hModule), path_wstr.data(), static_cast<DWORD>(path_wstr.size()));
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

    return path_wstr;
  } catch (...) {
    ::SetLastError(old_error_code);
    return std::unexpected(ERROR_NOT_ENOUGH_MEMORY);
  }
}

GMFN_API std::expected<std::filesystem::path, GMFN::v1::WIN_DWORD> GMFN::v1::K32GetModuleFileNameEx(void *hModule, void *process) noexcept {
  if (process == nullptr)
    process = ::GetCurrentProcess();

  const DWORD old_error_code = ::GetLastError();

  try {
    std::wstring path_wstr(MAX_PATH, L'\0');

    while (true) {
      const DWORD path_size  = ::K32GetModuleFileNameExW(reinterpret_cast<HANDLE>(process), static_cast<HMODULE>(hModule), path_wstr.data(), static_cast<DWORD>(path_wstr.size()));
      const DWORD error_code = ::GetLastError();
      ::SetLastError(old_error_code);

      if (!path_size) {
        return std::unexpected(error_code);
      }

      // https://github.com/MicrosoftDocs/sdk-api/blob/docs/sdk-api-src/content/psapi/nf-psapi-getmodulefilenameexw.md#-returns
      if ((path_size + /*(windows_version >= 10)*/ 1uz) < path_wstr.size()) {
        path_wstr.erase(path_size);
        break;
      }

      path_wstr.resize(path_wstr.size() + MAX_PATH, L'\0');
    }

    return path_wstr;
  } catch (...) {
    ::SetLastError(old_error_code);
    return std::unexpected(ERROR_NOT_ENOUGH_MEMORY);
  }
}