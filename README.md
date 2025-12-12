
# 🎉 ELC Engine  
A small, modular game/utility framework built on top of **Raylib**, created by **Coding Master Demi** 😎🔥  

This README explains **EVERY MODULE** inside ELC:
- ✔ Core system  
- ✔ GUI widgets  
- ✔ Popup system  
- ✔ Math utilities  
- ✔ Image loader with GIF + ASEPRITE support  
- ✔ Audio system  
- ✔ File picker GUI (work-in-progress)

---

# 🚀 ELC Overview

ELC is a lightweight wrapper around Raylib that gives you:

- Simple UI elements (`Button`, `TextBox`)
- Modal popups (`Alert`, `Prompt`, `Input`)
- ASEprite + GIF animation support
- Audio (music + sound)
- A cross-platform graphical file picker

Perfect for editors, small games, or tools.

---

# 📦 Module Breakdown

---

## 🖥 **1. Core System (`ELC.h`, `ELC.cpp`)**

Provides:

- Window creation (`Core::Init`)
- Drawing control (`BeginDrawing`, `EndDrawing`)
- Input handling (mouse, keyboard)
- Basic drawing helpers (rectangles, text)
- Color type wrapper (`ELC_Color`)
- Vector type wrapper (`Vec2`)

Usage:

```cpp
ELC::Core::Init(800, 600, "My App");
while (!ELC::Core::ShouldClose()) {
    ELC::Core::BeginDrawing();
    ELC::Core::ClearBackground(ELC::ELC_BLACK);

    // draw stuff...

    ELC::Core::EndDrawing();
}
ELC::Core::Close();
````

---

## 🧮 **2. Math Utilities (`ELCMath.h/.cpp`)**

Small helpers:

* `Lerp(a, b, t)`
* `Clamp(v, min, max)`
* `Normalize(Vec2 v)`

---

## 🎨 **3. GUI Widgets (`ELCGui.h/.cpp`)**

Includes:

### ✔ Button

* Detects hover
* Detects click
* Runs callback

### ✔ TextBox

* Editable text input
* Cursor blinking
* Handles `OnChar`, `OnKeyDown`

### ✔ Gui Manager

* Holds all widgets
* `gui.Update()`
* `gui.Draw()`

---

## 🪟 **4. Popups (`ELCPopup.h/.cpp`)**

Fully modal popup windows:

### ✔ `Popup::Alert("Hello!")`

Shows a message and an OK button.

### ✔ `Popup::PromptAnswer("Delete file?", "Yes", "No")`

Returns `true`/`false`.

### ✔ `Popup::PromptText("Name:", "enter...", "OK")`

Returns a string.

All popups freeze the app until answered.

---

## 🖼 **5. Image Loader (`ELCImage.h/.cpp`)**

Supports:

### ✔ PNG / JPG

Loads normally with Raylib.

### ✔ GIF

Uses `stb_image` GIF loader.
Handles multi-frame animations.

### ✔ ASEPRITE `.ase` / `.aseprite`

Using **cute_aseprite**:

* Supports layers & blending (already blended by cute_aseprite)
* Loads each frame into a `Texture2D`
* Animation auto-updates in `UpdateAnimation(delta)`

Usage:

```cpp
ELC::Image img("sprite.ase");
while (...) {
    img.UpdateAnimation(GetFrameTime());
    img.Draw(100, 100);
}
```

---

## 🔊 **6. Audio (`ELCAudio.h/.cpp`)**

### ✔ Sound (one-shot effects)

```cpp
ELC::Sound click("click.wav");
click.Play();
```

### ✔ Music (streaming)

```cpp
ELC::Music bg("music.ogg");
bg.Play();
bg.Update(); // call each frame
```

---

## 📁 **7. File Picker GUI — WIP**

The graphical file picker:

* Displays folders + files as buttons
* Lets you navigate folders
* Supports filters (`png`, `gif`, `ase`)
* Uses scrolling
* Returns full path or empty string

---

# 📌 Still in Progress

* Proper clipping of scroll area
* Keyboard navigation
* Breadcrumb navigation (folder bar)
* Icons for folders/files

---

# 💙 Credits

* Raylib
* stb_image
* cute_aseprite
* obviously me!

Created by **JesseLade** 😎🔥🔥🔥

---

