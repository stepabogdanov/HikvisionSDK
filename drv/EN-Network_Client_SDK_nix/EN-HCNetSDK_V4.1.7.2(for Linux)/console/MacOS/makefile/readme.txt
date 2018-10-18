Note:
    1. Check the id of ".dylib" files. 
          $otool -L ../../lib/MacOS/libxxxxx.dylib
    If the output information is not like this:"@loader_path/../../lib/MacOS/", you must change the id of ".dylib" files before run "make".
    2. Change the id of ".dylib" files.
          $./change_lib_path.sh
    3. $make
  