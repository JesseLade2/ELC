clang++ -std=c++17 -Wall -O2 -I/usr/local/include -c ../ELC.cpp ../ELCAudio.cpp ../ELCGui.cpp ../ELCImage.cpp ../ELCMath.cpp ../ELCPopup.cpp ../ELCFilePicker.cpp
ar rcs libELC.a ELC.o ELCAudio.o ELCFilePicker.o ELCGui.o ELCImage.o ELCMath.o ELCPopup.o
cp libELC.a /usr/local/lib/