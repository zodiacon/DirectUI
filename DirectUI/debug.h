#pragma once

#ifdef _DEBUG
#include <windows.h>
#include <stdio.h>
#include <crtdbg.h>
#endif

#ifdef _DEBUG
#define ASSERT _ASSERTE
#define VERIFY ASSERT
#define VERIFY_(result, expression) ASSERT(result == expression)
#else
#define ASSERT __noop
#define VERIFY(expression) (expression)
#define VERIFY_(result, expression) (expression)
#endif

#ifdef _DEBUG
struct Tracer
{
    char const * m_filename;
    unsigned m_line;

    Tracer(char const * filename, unsigned const line) :
        m_filename { filename },
        m_line { line }
    {

    }

    template <typename... Args>
    auto operator()(wchar_t const * format, Args... args) const -> void
    {
        wchar_t buffer [400];

        auto count = swprintf_s(buffer,
                                L"%S(%d): ",
                                m_filename,
                                m_line);

        ASSERT(-1 != count);

        ASSERT(-1 != _snwprintf_s(buffer + count,
                                  _countof(buffer) - count,
                                  _countof(buffer) - count - 1,
                                  format,
                                  args...));

        OutputDebugString(buffer);
    }
};
#endif

#ifdef _DEBUG
#define TRACE Tracer(__FILE__, __LINE__)
#else
#define TRACE __noop
#endif
