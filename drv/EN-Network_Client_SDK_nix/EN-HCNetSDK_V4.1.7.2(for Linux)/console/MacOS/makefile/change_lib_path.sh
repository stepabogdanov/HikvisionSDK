#!/bin/sh
echo "change hpr.lib..."
install_name_tool -id "@loader_path/../lib/libhpr.dylib"  ../lib/libhpr.dylib

echo "change hcnetsdk.lib..."
install_name_tool -id "@loader_path/../lib/libHCNetSDK.dylib" ../lib/libHCNetSDK.dylib


echo "Change the dependence between hpr and hcnetsdk."
#install_name_tool -change "/usr/local/lib/libhpr.dylib" "@loader_path/../lib/libhpr.dylib" ../lib/libHCNetSDK.dylib

echo "change the denpendenc between hpr and rtsp lib."
#install_name_tool -change "/usr/local/lib/libhpr.dylib" "@loader_path/../lib/libhpr.dylib" ../lib/libStreamTransClient.dylib
#install_name_tool -change "/usr/local/lib/libhpr.dylib" "@loader_path/../lib/libhpr.dylib" ./libStreamTransClient.dylib


echo "Compelte!"
