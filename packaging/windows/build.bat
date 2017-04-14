rem
rem Follow the instructions in 3rdparty/README.md to setup Qt and the 
rem build dirs and checkout krita
rem 

set PATH=c:\dev\i\bin\;c:\dev\i\lib;%PATH%
cd c:\dev\b
cmake ..\krita\3rdparty -DEXTERNALS_DOWNLOAD_DIR=/dev/d -DINSTALL_ROOT=/dev/i   -G "Visual Studio 14 Win64" 
cmake --build . --config RelWithDebInfo --target ext_patch
cmake --build . --config RelWithDebInfo --target ext_png2ico
cmake --build . --config RelWithDebInfo --target ext_pthreads
cmake --build . --config RelWithDebInfo --target ext_boost
cmake --build . --config RelWithDebInfo --target ext_eigen3
cmake --build . --config RelWithDebInfo --target ext_fftw3
cmake --build . --config RelWithDebInfo --target ext_ilmbase
cmake --build . --config RelWithDebInfo --target ext_jpeg
cmake --build . --config RelWithDebInfo --target ext_lcms2
cmake --build . --config RelWithDebInfo --target ext_png
cmake --build . --config RelWithDebInfo --target ext_tiff
cmake --build . --config RelWithDebInfo --target ext_gsl
cmake --build . --config RelWithDebInfo --target ext_vc
cmake --build . --config RelWithDebInfo --target ext_libraw
rem cmake --build . --config RelWithDebInfo --target ext_freetype
cmake --build . --config RelWithDebInfo --target ext_ocio
cmake --build . --config RelWithDebInfo --target ext_openexr
cmake --build . --config RelWithDebInfo --target ext_exiv2
cmake --build . --config RelWithDebInfo --target ext_kwindowsystem

REM cmake --build . --config RelWithDebInfo --target ext_poppler
cd c:\dev\build
cmake ..\krita -G"Visual Studio 14 Win64" -DBoost_DEBUG=OFF -DBOOST_INCLUDEDIR=c:\dev\i\include -DBOOST_DEBUG=ON -DBOOST_ROOT=c:\dev\i -DBOOST_LIBRARYDIR=c:\dev\i\lib -DCMAKE_INSTALL_PREFIX=c:\dev\i -DCMAKE_PREFIX_PATH=c:\dev\i -DCMAKE_BUILD_TYPE=RelWithDebInfo -DBUILD_TESTING=OFF -DKDE4_BUILD_TESTS=OFF -DHAVE_MEMORY_LEAK_TRACKER=OFF -Wno-dev -DDEFINE_NO_DEPRECATED=1

copy c:\dev\i\lib\*.dll c:\dev\i\bin
copy "C:\Program Files (x86)\Windows Kits\10\Redist\ucrt\DLLs\x64\*.dll" c:\dev\i\bin
