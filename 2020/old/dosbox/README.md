

```
sudo apt install python
sudo apt install build-essential
```

https://www.dosbox.com/

https://sourceforge.net/projects/dosbox/files/dosbox/0.74-3/dosbox-0.74-3.tar.gz/download

```
emconfigure ./configure
```


```
checking SDL version only being 1.2.X... no
configure: error: Only libSDL 1.2.X supported
```

https://groups.google.com/forum/#!topic/emscripten-discuss/dY1FYteFzzY

```
cat confdefs.h - <<_ACEOF >conftest.$ac_ext
/* end confdefs.h.  */

#include "SDL.h"
void blah(){
#if SDL_MINOR_VERSION != 2
#error "Only SDL 1.2 supported"
#endif
;
}
```

```
#if SDL_MINOR_VERSION != 2
```

change to 2 > 3

```
emconfigure ./configure
emmake make
```

// NOT SUPPORt SDL_CD

```
./cdrom.h:86:2: error: unknown type name 'SDL_CD'
        SDL_CD* cd;
        ^
dos_programs.cpp:194:14: error: use of undeclared identifier 'SDL_CDNumDrives'
                        int num = SDL_CDNumDrives();
                                  ^
dos_programs.cpp:197:28: error: use of undeclared identifier 'SDL_CDName'
                                WriteOut("%2d. %s\n",i,SDL_CDName(i));
                                                       ^
3 errors generated.
em++: error: '/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/bin/clang++ -DEMSCRIPTEN -fignore-exceptions -mllvm -combiner-global-alias-analysis=false -mllvm -enable-emscripten-sjlj -mllvm -disable-lsr -Xclang -isystem/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/system/include/SDL -target wasm32-unknown-emscripten -D__EMSCRIPTEN_major__=2 -D__EMSCRIPTEN_minor__=0 -D__EMSCRIPTEN_tiny__=9 -D_LIBCPP_ABI_VERSION=2 -Dunix -D__unix -D__unix__ -Werror=implicit-function-declaration -Xclang -nostdsysteminc -Xclang -isystem/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/system/include/libcxx -Xclang -isystem/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/system/lib/libcxxabi/include -Xclang -isystem/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/system/include/compat -Xclang -isystem/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/system/include -Xclang -isystem/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/system/include/libc -Xclang -isystem/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/system/lib/libc/musl/arch/emscripten -Xclang -isystem/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/system/local/include -Xclang -isystem/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/system/include/SSE -Xclang -isystem/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/system/include/neon -Xclang -isystem/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/system/lib/compiler-rt/include -Xclang -isystem/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/system/lib/libunwind/include -Xclang -isystem/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/cache/wasm/include -DHAVE_CONFIG_H -I. -I../.. -I../../include -g -O2 -mno-ms-bitfields -c -o dos_programs.o dos_programs.cpp -c -o dos_programs.o' failed (1)
```


/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O2 -mno-ms-bitfields    -o dosbox dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL
wasm-ld: error: initial memory too small, 35325216 bytes needed


  596  
  597  emmake make
  598  ls
  599  find ./ -name *.js
  600  ls
  601  find ./ -name dosbox
  602  cd src/
  603  ls
  604  /home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O2 -mno-ms-bitfields   -s TOTAL_MEMORY=67108864 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -o dosbox.html dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL 
  605  ls
  606  docker run -it --rm --name dosbox -v ${PWD}:/usr/local/apache2/htdocs -p 80:80 httpd
  607  ls
  608  /home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O2 -mno-ms-bitfields   -s TOTAL_MEMORY=67108864 -o dosbox.html dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL 
  609  history
  610  cd ..
  611  ls
  612  cd ..
  613  ls
  614  history


   566  emmake make
  567  cd csr
  568  cd src/
  569  /home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O2 -mno-ms-bitfields   -s TOTAL_MEMORY=67108864 -o dosbox dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL
  570  /home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/emcc  -g -O2 -mno-ms-bitfields   -s TOTAL_MEMORY=67108864 -o dosbox dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL
  571  /home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O2 -mno-ms-bitfields   -s TOTAL_MEMORY=67108864 -s USE_WEBGL2=1 -o dosbox dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL
  572  cd ..
  573  emconfigure ./configure --help
  574  emmake make
  575  /home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O2 -mno-ms-bitfields   -s TOTAL_MEMORY=67108864 -o dosbox dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL
  576  cd src/
  577  /home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O2 -mno-ms-bitfields   -s TOTAL_MEMORY=67108864 -o dosbox dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL
  578  /home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O2 -mno-ms-bitfields   -s TOTAL_MEMORY=67108864 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -o dosbox dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL
  579  ls
  580  find ./ -name *.html
  581  find ./ -name *.js
  582  cd ..
  583  find ./ -name *.js
  584  find ./ -name *.h
  585  find ./ -name *.html
  586  find ./ -name '*.html'
  587  find ./ -name '*.js'
  588  emconfigure ./configure --help
  589  ls
  590  cd src/
  591  ls
  592  cd ..
  593  ls
  594  histroy
  595  history
  596  LDFLAGS="-s TOTAL_MEMORY=67108864 -s ERROR_ON_UNDEFINED_SYMBOLS=0" emconfigure ./configure
  597  emmake make
  598  ls
  599  find ./ -name *.js
  600  ls
  601  find ./ -name dosbox
  602  cd src/
  603  ls
  604  /home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O2 -mno-ms-bitfields   -s TOTAL_MEMORY=67108864 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -o dosbox.html dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL 
  605  ls
  606  docker run -it --rm --name dosbox -v ${PWD}:/usr/local/apache2/htdocs -p 80:80 httpd
  607  ls
  608  /home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O2 -mno-ms-bitfields   -s TOTAL_MEMORY=67108864 -o dosbox.html dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL 
  609  history
  610  cd ..
  611  ls
  612  cd ..
  613  ls
  614  history
  615  cd dosbox-0.74-3/
  616  ls
  617  emconfigure ./configure --help
  618  emconfigure ./configure --program-suffix=.html
  619  LDFLAGS="-s TOTAL_MEMORY=67108864 -s ERROR_ON_UNDEFINED_SYMBOLS=0" emconfigure ./configure --program-suffix=.html
  620  emmake make
  621  emmake make clean
  622  emmake make
  623  ls src/
  624  ls src/ -al
  625  emconfigure ./configure
  626* 
  627  LDFLAGS="-s TOTAL_MEMORY=67108864 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ASYNCIFY" CXXFLAGS="-g -O3" emconfigure ./configure --program-suffix=.html
  628  emmake clean
  629  emmake
  630  emmake make clean
  631  emmake make
  632  cd src/
  633  /home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O3 -mno-ms-bitfields   -s TOTAL_MEMORY=67108864 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ASYNCIFY -o dosbox.html dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL
  634  history
  635  docker run -it --rm --name dosbox -v ${PWD}:/usr/local/apache2/htdocs -p 80:80 httpd
  636  /home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O3 -mno-ms-bitfields   -s TOTAL_MEMORY=67108864 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ASYNCIFY -o dosbox.html dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL --enable-wasm
  637  ls
  638  vi gui/
  639  cd gui/
  640  ls
  641  vi sdlmain.cpp 
  642  cd ..
  643  emmake make
  644  cd src/
  645  /home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O3 -mno-ms-bitfields   -s TOTAL_MEMORY=67108864 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ASYNCIFY -o dosbox.html dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL
  646  history
  647  docker run -it --rm --name dosbox -v ${PWD}:/usr/local/apache2/htdocs -p 80:80 httpd
  648  grep Startup -nr ./
  649  vi ./gui/sdl_gui.cpp 
  650  grep Config -nr ./*
  651  vi ./misc/setup.cpp
  652  grep SetStartUp -nr ./*
  653  vi gui/sdlmain.cpp 
  654  cd ..
  655  emmake
  656  emmake make
  657  cd src
  658  /home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O3 -mno-ms-bitfields   -s TOTAL_MEMORY=67108864 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ASYNCIFY -o dosbox.html dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL
  659  history
  660  docker run -it --rm --name dosbox -v ${PWD}:/usr/local/apache2/htdocs -p 80:80 httpd
  661  grep SHELL_init -nr ./*
  662  grep SHELL_Init -nr ./*
  663  vi ./shell/dosbox.cpp
  664  vi ./shell/shell.cpp 
  665  cd ..
  666  emmake make
  667  cd src/
  668  /home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O3 -mno-ms-bitfields   -s TOTAL_MEMORY=67108864 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ASYNCIFY -o dosbox.html dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL
  669  docker run -it --rm --name dosbox -v ${PWD}:/usr/local/apache2/htdocs -p 80:80 httpd
  670  cd ..
  671  ls
  672  history


```
CXXFLAGS="-g -O3" LDFLAGS="-s TOTAL_MEMORY=67108864 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ASYNCIFY -s ASSERTIONS=1 -s DISABLE_EXCEPTION_CATCHING=0" emconfigure ./configure 

emmake make







/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O3 -mno-ms-bitfields -s USE_SDL=2  -s TOTAL_MEMORY=67108864 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ASYNCIFY -o dosbox.html dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL


docker run -it --rm --name dosbox -v ${PWD}:/usr/local/apache2/htdocs -p 80:80 httpd
```



/home/novemberizing/Workspace/novemberizing/dev/emscripten/emsdk/upstream/emscripten/em++  -g -O3 -mno-ms-bitfields   -s WASM=1 -s TOTAL_MEMORY=67108864 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s ASYNCIFY -s ALLOW_MEMORY_GROWTH=1 -o dosbox.html dosbox.o  cpu/libcpu.a debug/libdebug.a dos/libdos.a fpu/libfpu.a  hardware/libhardware.a gui/libgui.a ints/libints.a misc/libmisc.a shell/libshell.a hardware/mame/libmame.a hardware/serialport/libserial.a libs/gui_tk/libgui_tk.a -lX11 -lGL









