# GMFN

GMFN is a small C++23 library that provides exception-free wrappers for retrieving the file path of a loaded Windows module. It exposes two functions:

- `K32GetModuleFileName` — retrieves the path of a module in the current process.
- `K32GetModuleFileNameEx` — retrieves the path of a module from a specified process, or from the current process by default.

Both functions are marked `noexcept` and return `std::expected<std::filesystem::path, WIN_DWORD>`. On success, the module path is returned as a `std::filesystem::path`. WinAPI failures are reported through `std::unexpected` using the error code obtained from `GetLastError`.

The implementation does not propagate C++ exceptions. Allocation failures, which are the only expected source of exceptions, are caught and returned as `std::unexpected(ERROR_NOT_ENOUGH_MEMORY)`.

The previous thread-local last-error value is saved and restored before every return, so the functions do not alter the caller's WinAPI error state or leave observable side effects behind.

Module paths are collected using a dynamically growing buffer rather than a fixed-size `MAX_PATH` buffer. This allows the functions to handle paths longer than `MAX_PATH`, including Windows long paths.
