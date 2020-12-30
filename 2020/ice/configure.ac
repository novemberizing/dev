dnl -----------------------------------------------
dnl INITIALIZE CONFIGURE
dnl -----------------------------------------------
AC_INIT([novemberizing-ice], [0.0.1], [novemberizing@gmail.com])

dnl -----------------------------------------------
dnl CREATE CONFIGURATION FILES
dnl -----------------------------------------------
AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/novemberizing/Makefile
    src/novemberizing/ds/Makefile
    src/novemberizing/net/Makefile
    src/novemberizing/ice/Makefile
])

dnl -----------------------------------------------
dnl CONFIGURATION HEADER FILES
dnl -----------------------------------------------
AC_CONFIG_HEADERS([config.h])

dnl -----------------------------------------------
dnl AUTOMAKE
dnl -----------------------------------------------
AM_INIT_AUTOMAKE
AC_PROG_RANLIB
AC_PROG_CC

dnl -----------------------------------------------
dnl TODO
dnl -----------------------------------------------
test=test
AC_SUBST(test)

dnl -----------------------------------------------
dnl OUTPUTING FILES
dnl -----------------------------------------------
AC_OUTPUT