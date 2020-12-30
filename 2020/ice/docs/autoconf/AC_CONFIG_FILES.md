AC_CONFIG_FILES (file..., [cmds], [init-cmds])

Make AC_OUTPUT create each file by copying an input file (by default file.in), substituting the output variable values. This macro is one of the instantiating macros; see Configuration Actions. See Makefile Substitutions, for more information on using output variables. See Setting Output Variables, for more information on creating them. This macro creates the directory that the file is in if it doesn't exist. Usually, makefiles are created this way, but other files, such as .gdbinit, can be specified as well.

Typical calls to AC_CONFIG_FILES look like this:

AC_CONFIG_FILES([Makefile src/Makefile man/Makefile X/Imakefile])
AC_CONFIG_FILES([autoconf], [chmod +x autoconf])

You can override an input file name by appending to file a colon-separated list of input files. Examples:

AC_CONFIG_FILES([Makefile:boiler/top.mk:boiler/bot.mk]
                [lib/Makefile:boiler/lib.mk])

Doing this allows you to keep your file names acceptable to DOS variants, or to prepend and/or append boilerplate to the file.