AC_OUTPUT

Generate config.status and launch it. Call this macro once, at the end of configure.ac.

config.status performs all the configuration actions: all the output files (see Configuration Files, macro AC_CONFIG_FILES), header files (see Configuration Headers, macro AC_CONFIG_HEADERS), commands (see Configuration Commands, macro AC_CONFIG_COMMANDS), links (see Configuration Links, macro AC_CONFIG_LINKS), subdirectories to configure (see Subdirectories, macro AC_CONFIG_SUBDIRS) are honored.

The location of your AC_OUTPUT invocation is the exact point where configuration actions are taken: any code afterwards is executed by configure once config.status was run. If you want to bind actions to config.status itself (independently of whether configure is being run), see Running Arbitrary Configuration Commands.

