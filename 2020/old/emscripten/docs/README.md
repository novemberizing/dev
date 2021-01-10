__INTRODUCING EMSCRIPTEN__
==========================

> [INTRODUCING EMSCRIPTEN](https://emscripten.org/docs/introducing_emscripten/index.html)

This section explains what Emscripten does, why it is needed, its limitations and its licensing. After reading, you will understand whether Emscripten is the right tool for you, and where to go if you have [further questions](https://emscripten.org/docs/introducing_emscripten/community.html#community).

## __ABOUT EMSCRIPTEN__

> [ABOUT EMSCRIPTEN](https://emscripten.org/docs/introducing_emscripten/about_emscripten.html)

Emscripten is a complete [Open Source](https://emscripten.org/docs/introducing_emscripten/emscripten_license.html#emscripten-license) compiler toolchain to WebAssembly. Using Emscripten you can:

- Compile C and C++ code, or any other language that uses LLVM, into WebAssembly, and run it on the Web, Node.js, or other wasm runtimes.
- Compile the C/C++ runtimes of other languages into WebAssembly, and then run code in those other languages in an indirect way (for example, this has been done for Python and Lua).

Practically any portable C or C++ codebase can be compiled into WebAssembly using Emscripten, ranging from high-performance games that need to render graphics, play sounds, and load and process files, through to application frameworks like Qt. Emscripten has already been used to convert a very long list of real world codebases to WebAssembly, including commercial codbases like the Unreal Engine 4 and the Unity engine. For examples and demos, see [the community-maintained list on the wiki](https://github.com/emscripten-core/emscripten/wiki/Porting-Examples-and-Demos).

Emscripten generates small and fast code! Its default output format is [WebAssembly](https://webassembly.org/), a highly optimizable executable format, that runs almost as fast as native code, while being portable and safe. Emscripten does a lot of optimization work for you automatically, by careful integration with LLVM, Binaryen, Closure Compiler, and other tools.

### EMSCRIPTEN TOOLCHAIN

A high level view of the Emscripten toolchain is given below. The main tool is [the Emscripten Compiler Frontend (emcc)](https://emscripten.org/docs/tools_reference/emcc.html#emccdoc). This is a drop in replacement for a standard compiler like gcc or clang.

Emcc uses Clang and LLVM to compile to WebAssembly. Emcc also emits JavaScript that provides API support to the compiled code. That JavaScript can be executed by Node.js, or from within HTML in a browser.

The [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html#sdk-download-and-install) is used to install the entire toolchain, including emcc and LLVM and so forth. The [Emscripten SDK (emsdk)](https://emscripten.org/docs/tools_reference/emsdk.html#emsdk) can be used on Linux, Windows, or MacOS.

### PORTING CODE TO USE EMSCRIPTEN

Emscripten support for portable C/C++ code is fairly comprehensive. Support for the C standard library, C++ standard library, C++ exceptions, etc, is very good, as is SDL2 and other APIs. OpenGL support in Emscripten support is excellent for OpenGL ES 2.0 type code, and acceptable for other types.

There are differences between the native and [Emscripten Runtime Environment](https://emscripten.org/docs/porting/emscripten-runtime-environment.html#emscripten-runtime-environment), which mean some changes usually need to be made to the native code. That said, many applications will only need to change the way define their main loop, and also modify there [file handling](https://emscripten.org/docs/porting/files/file_systems_overview.html#file-system-overview) to adapt to the limitations of the browser/JavaScript.

There are also limitations that can make some code easier to port - read [Portability Guidelines](https://emscripten.org/docs/porting/guidelines/portability_guidelines.html#code-portability-guidelines) determine where you may need to spend more effort.

### COMMUNITY

> [COMMUNITY](https://emscripten.org/docs/introducing_emscripten/community.html)

Welcome to the Emscripten community!

#### GET IN TOUCH

The best ways contact the community are:

- THE GITHUB [ISSUE TRACKER](https://github.com/emscripten-core/emscripten/issues?q=is%3Aopen).
- MAILING LIST: [EMSCRIPTEN DISCUSS](https://groups.google.com/g/emscripten-discuss)
- REALTIME CHAT: [#EMSCRIPTEN ON DISCORD](https://discord.com/invite/53u3EKq) (there was also an IRC channel on Mozilla IRC, but they are shutting those servers down). We are also open to exploring other options than Discord. If you're interested to help out, let use know!

Feel free to ask questions, share your ideas, or just join the conversation!

Emscripten also has a presence on social media:

- [#emscripten](https://twitter.com/hashtag/emscripten) (Emscripten Hashtag on Twitter)
- [@kripken](https://twitter.com/kripken) (an Emscripten developer's account on Twitter, mentions Emscripten updates).

#### REPORT A BUG

[Bug reports](https://emscripten.org/docs/getting_started/bug_reports.html#bug-reports) can be posted in the Github [Issue Tracker](https://github.com/emscripten-core/emscripten/issues?q=is%3Aopen).

#### CONTIBUTE

Anyone can contribute to Emscripten. We've got some ideas to get you started on our [Contributing](https://emscripten.org/docs/contributing/contributing.html#contributing) page!

## OPEN SOURCE LICENSE

> [OPEN SOURCE LICENSE](https://emscripten.org/docs/introducing_emscripten/emscripten_license.html)

Emscripten is made available under two permissive open source licenses: the MIT license and the University of Illinois/NCSA Open Source License.

There is little, if any, protical difference between the licenses. They are both offered because the:

- MIT license is well known and understood.
- University of Illinois/NCSA Open Source License allows Emscripten's code to be integrated upstream into LLVM, should the opportunity arise.

The license for Emscripten 2.0.9 (Nov 30, 2020) is reproduces below. The [current full license](https://github.com/emscripten-core/emscripten/blob/master/LICENSE) can be found on Github (and is also present in the root of the SDK).

```
Emscripten is available under 2 li9censes, the MIT license and the University of Illinois/NCSA Open Source License.

Both are permissive open source licenses, with little if any practical difference between them.

The reason for offering both is that (1) the MIT license is well-know, while (2) the University of Illoinois/NCSA Open Source License allows Emscripten's code to be integrated upstream into LLVM, which uses that license, should the opportunity arise.

The full text of both licenses follows.

==============================================================================

Copyright (c) 2010-2014 Emscripten authors, see AUTHORS file.

Permission is hereby granted, free of charge, to any person obtaining c copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do son, subject to the following conditions:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimers.

    Redistributions in binrary form reproduce the above copyright notice, this list of conditions and the fllowing disclaimers in the documentation and/or other materials provided with the distribution.

    Neither the names of Mozilla, nor the names of is contributors may be used to endorse or promote products derived from this Software without specific prior written permission.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE CONTRIBUTORS OR COPY RIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS WITH THE SOFTWARE.

==============================================================================

This program uses portions of Node.js source code located in src/library_path.js, in accordance with the terms of the MIT license. Node's license follows"

        Copyright Joyent, Inc. and other Node contributors. All rights reserved.
        Permission is hereby granted, free of charge, to any person obtaining a copy
        of this software and associated documentation files (the "Software"), to
        deal in the Software without restriction, including without limitation the
        rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
        sell copies of the Software, and to permit persons to whom the Software is
        furnished to do so, subject to the following conditions:

        The above copyright notice and this permission notice shall be included in
        all copies or substantial portions of the Software.

        THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
        IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
        FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
        LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
        FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
        IN THE SOFTWARE.

The musl libc project is bundled in this repo, and it has the MIT license, see system/lib/libc/musl/COPYRIGHT

The third_party/ subdirectory contains code with other licenses. None of it is
used by default, but certain options use it (e.g., the optional closure compiler
flag will run closure compiler from third_party/).
```

- [RELEASE NOTES](https://emscripten.org/docs/introducing_emscripten/release_notes.html)
- [TALKS AND PUBLICATIONS](https://emscripten.org/docs/introducing_emscripten/Talks-and-Publications.html)

__GETTING STARTED__
===================

> [GETTING STARTED](https://emscripten.org/docs/getting_started/index.html)

Now you know why Emscripten is right for you, it's time to get started.

This section provides a walk-through of [downloading and installing the SDK](https://emscripten.org/docs/getting_started/downloads.html#sdk-download-and-install) and the basic of [using the Emscripten toolchain](https://emscripten.org/docs/getting_started/Tutorial.html#tutorial). The general [FAQ](https://emscripten.org/docs/getting_started/FAQ.html#faq) answers many common questions about setting up and using Emscripten.

We also explain where to [Report Bugs](https://emscripten.org/docs/getting_started/bug_reports.html#bug-reports) in the toolchain and the site. The [Emscripten Test Suite](https://emscripten.org/docs/getting_started/test-suite.html#emscripten-test-suite) is a great resource for finding examples of how to use Emscripten.

## DOWNLOAD AND INSTALL

> [DOWNLOAD AND INSTALL](https://emscripten.org/docs/getting_started/downloads.html)

> NOTE
> 
> You can also [build Emscripten from source](https://emscripten.org/docs/building_from_source/index.html#installing-from-source) if your prefer that to downloading binaries using the emsdk.
>
> There are additional ways to install Emscripten thatn the instructions below, for example using Homebrew on MacOS, the package manager on your linux distro. However, the emsdk is the only officially supported way to use Emscripten that is supported by the Emscripten project, and the only one that we constantly test (emsdk CI, Emscripten Github CI, Chromium CI). (While we don't offically support other ways of getting Emscripten, we definitely appreciate the efforts by third parties to package Emscripten for user's convenience, and we'd like to help out, please get in touch if your are such a packager!)

### INSTALLATION INSTRUCTIONS

First check the [Platform-specific notes](https://emscripten.org/docs/getting_started/downloads.html#platform-notes-installation-instructions-sdk) below and install any prerequisites.

The core Emscripten SDK (emsdk) driver is a Python script. You can get it for the first time with

```
# Get the emsdk repo
git clone https://github.com/emscripten-core/emsdk.git

# Enter that directory
cd emsdk
```

> NOTE
>
> You can also get the emsdk without git, by selecting "Clone or download => Download ZIP" on the [emsdk Github page](https://github.com/emscripten-core/emsdk).

Run the following emsdk commands to get the latest tools from Github and set them as archive:

```
# Fetch the latest version of the emsdk (not needed the first time you clone)
git clone

# Download and install the latest SDK tools.
./emsdk install latest

# Make the "latest" SDK "active" for the current user, (writes .emscripten file)
./emsdk activate latest

# Activate PATH and other environment variables in the current terminal.
source ./emsdk_env.sh
```

> NOTE
>
> On Windows, run emsdk instead of ./emsdk, and emsdk_env.bat instead of source ./emsdk_env.sh
>
> git pull will fetch the current list of tags, but very recent ones may not yet be present there. You can run ./emsdk update-tags to update the list of tags directly.

If you change the location of the SDK (e.g. take it to another computer on an USB), re-run the ./emsdk activate latest and source ./emsdk_env.sh commands.

### EMSDK INSTALL TARGETS

In the description above we asked the emsdk to install and activate latest, which is the latest tagged release. That is often what you want.

You can also install a specific version by specifying it, for example,

```
./emsdk install 1.38.45
```

> NOTE
> 
> When installing old versions from before the build infrastructure rewrite (anything before 1.38.33), you need to write something like ./emsdk install sdk-1.38.20-64bit (add sdk- and -64bit) as that was the naming convention at the time.

There are also "tip of tree builds", which are the very latest code that passes integration tests on Chromium CI. This is updated much more frequently than tagged releases, but may be less stable (we tag releases manually using a more careful procedure). Tip of tree builds may be useful for continuous integration that uses the emsdk (as Emscripten's Github CI does), and you may want to use it in your own CI as well, so that if you find a regression on your project you can report it and prevent it from reaching a tagged release. Tip-of-builds may also be useful if you want to test a feature that just landed but didn't reach a release yet. To use a tip-of-tree build, use to tot target, and note that you must specify the backend explicitly.

```
# Get a tip-of-tree
./emsdk install tot
```

(In the above examples we installed the various targets; remember to also activate them as in the full example from eariler.)

### PLATFORM SPECIFIC NOTES

WINDOWS

1. Install Python 2.7.12 or newer (older versions may not work due to a Github change with SSL)

> NOTE
>
> Instead of running emscripten on Windows directly, you can use the Windows Subsystem for Linux to run it in a Linux environment.

MACOS

If you use the Emscripten SDK it includes a bundled version of Python 3. Otherwise you will need to manually install and use Python 3.6 or newer.

These instructions explain how to install all the required tools. You can test whether some of these are already installed on the platform and skip those steps.

1. INSTALL THE XCODE COMMAND LINE TOOLS. These are a precodntion for git.

- Install Xcode from the macOS App Store.
- In Xcode | Preferences | Downloads, install command line tools.

2. Install git:

- Make sure the OS allows install git.




