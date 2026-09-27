#pragma once

#ifdef GMFN_EXPORTS
#  define GMFN_API __declspec(dllexport)
#else // !GMFN_EXPORT
#  define GMFN_API __declspec(dllimport)
#  ifndef GMFN_NO_AUTO_LINK
#    pragma comment(lib, "GMFN.lib")
#  endif // GMFN_NO_AUTO_LINK
#endif   // GMFN_EXPORT

#include <expected>
#include <filesystem>

namespace GMFN {
inline namespace v1 {
using WIN_DWORD = unsigned long;

GMFN_API std::expected<std::filesystem::path, WIN_DWORD> K32GetModuleFileName(void *hModule = nullptr) noexcept;
GMFN_API std::expected<std::filesystem::path, WIN_DWORD> K32GetModuleFileNameEx(void *hModule = nullptr, void *process = nullptr) noexcept;
} // namespace v1
} // namespace GMFN