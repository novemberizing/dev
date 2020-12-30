AC_CONFIG_HEADERS (header ..., [cmds], [init-cmds])

This macro is one of the instantiating macros; see Configuration Actions. Make AC_OUTPUT create the file(s) in the blank-or-newline-separated list header containing C preprocessor #define statements, and replace ‘@DEFS@’ in generated files with -DHAVE_CONFIG_H instead of the value of DEFS. The usual name for header is config.h.

If header already exists and its contents are identical to what AC_OUTPUT would put in it, it is left alone. Doing this allows making some changes in the configuration without needlessly causing object files that depend on the header file to be recompiled.

Usually the input file is named header.in; however, you can override the input file name by appending to header a colon-separated list of input files. For example, you might need to make the input file name acceptable to DOS variants:

AC_CONFIG_HEADERS([config.h:config.hin])
