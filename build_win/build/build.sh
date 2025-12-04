x86_64-w64-mingw32-g++ -std=c++17 -Wall -O2 -I/Users/demi/raylib_editor_game/raylib-icon-maker/raylib-icon-maker-WINDOWS/raylib/include/ -c \
 ../ELC.cpp ../ELCAudio.cpp ../ELCGui.cpp ../ELCImage.cpp ../ELCMath.cpp ../ELCPopup.cpp ../ELCFilePicker.cpp

x86_64-w64-mingw32-ar rcs libELC-windows.a ELC.o ELCAudio.o ELCFilePicker.o ELCGui.o ELCImage.o ELCMath.o ELCPopup.o
