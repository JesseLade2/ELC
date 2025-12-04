'/Users/demi/raylib_editor_game/raylib-icon-maker/raylib-icon-maker-LINUX/x86_64-unknown-linux-gnu/bin/x86_64-linux-gnu-g++' -std=c++17 -Wall -O2 -I/usr/local/include -c \
 ../ELC.cpp ../ELCAudio.cpp ../ELCGui.cpp ../ELCImage.cpp ../ELCMath.cpp ../ELCPopup.cpp ../ELCFilePicker.cpp

'/Users/demi/raylib_editor_game/raylib-icon-maker/raylib-icon-maker-LINUX/x86_64-unknown-linux-gnu/bin/x86_64-linux-gnu-ar' rcs libELC.a ELC.o ELCAudio.o ELCFilePicker.o ELCGui.o ELCImage.o ELCMath.o ELCPopup.o

sudo cp libELC.a /usr/local/lib/
