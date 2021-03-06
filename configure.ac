#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.63)
AC_INIT([nemu],[0.1],[dbaryshkov@gmail.com])
AC_CONFIG_SRCDIR([libir/ir.c])
AC_CONFIG_AUX_DIR([misc])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror gnu])
AM_MAINTAINER_MODE

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_AWK
AC_PROG_INSTALL
AC_PROG_RANLIB
AC_PROG_CPP
AC_PROG_MKDIR_P
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)
AC_PROG_YACC
AM_PROG_LEX

AC_ARG_ENABLE([werror],
	      [AS_HELP_STRING([--disable-werror],[compile without -Werror])],
	      [werror=$enableval], [werror=yes])
if test "$werror" = "yes" -o "$werror" = "enable"
then
#	AC_SUBST(COMMON_CFLAGS, "-Wall -Werror")
	CFLAGS="$CFLAGS -Wall -Werror"
else
#	AC_SUBST(COMMON_CFLAGS, "-Wall")
	CFLAGS="$CFLAGS -Wall"
fi

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h inttypes.h libintl.h stddef.h stdint.h stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile
		 libmdesc/Makefile
                 libir/Makefile
                 mmio/Makefile
                 drivers/Makefile
		 guest-i8080/Makefile])
AC_OUTPUT
