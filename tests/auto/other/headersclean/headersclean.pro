CONFIG += testcase
TARGET = tst_headersclean
SOURCES  += tst_headersclean.cpp

# No need to link to all modules, only those actually used
QT = core testlib gui widgets

*-g++*: QMAKE_CXXFLAGS += -W -Wall -Wextra -Werror

# The flags here come from http://wiki.qt-project.org/Coding_Conventions#Conventions_for_public_header_files
# -Wold-style-cast cannot be used, /usr/include/bits/byteswap.h defines the macro bswap_16 using C style casts :(
# -Wfloat-equal cannot be used, qrect.h and qvector2d.h do exact comparisons in isNull and operator==. Would need #pragmas.
*-g++*: QMAKE_CXXFLAGS += -Woverloaded-virtual -Wshadow -Wundef

# Other nice flags
*-g++*: QMAKE_CXXFLAGS += -Wnon-virtual-dtor -ansi -Wcast-align -Wchar-subscripts -Wpointer-arith -Wformat-security

# Enable pedantic mode, but accept variadic macros and 'long long' usage.
*-g++*: QMAKE_CXXFLAGS += -Wno-long-long -Wno-variadic-macros -pedantic-errors

QMAKE_CXXFLAGS += -DQT_NO_CAST_TO_ASCII \
                  -DQT_NO_CAST_FROM_ASCII \
                  -DQT_STRICT_ITERATORS \
                  -DQT_NO_URL_CAST_FROM_STRING \
                  -DQT_NO_CAST_FROM_BYTEARRAY \
                  -DQT_NO_KEYWORDS \
                  -DQT_USE_FAST_CONCATENATION \
                  -DQT_USE_FAST_OPERATOR_PLUS
