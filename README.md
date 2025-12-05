<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<title>ELC Framework</title>
</head>
<body>

<h1>🚀 ELC — Easy Lightweight C++ Framework</h1>

<p><strong>ELC</strong> is a lightweight, modular C++ framework built on top of
<strong>raylib</strong>.  
It provides simple UI components, audio utilities, image helpers, popups, math tools,
and a consistent cross-platform file picker.</p>

<hr>

<h2>✨ What ELC Provides</h2>
<ul>
  <li>🎨 <strong>GUI system</strong> — buttons, labels, windows, popups, layout helpers</li>
  <li>🖼️ <strong>Image utilities</strong> — easy loading, safe wrapping, scaling, and pixel operations</li>
  <li>🔊 <strong>Audio helpers</strong> — quick playback, SFX handling, and simple interfaces</li>
  <li>📐 <strong>Math utilities</strong> — vectors, rectangles, interpolation, and helper math functions</li>
  <li>📁 <strong>Custom file picker</strong> — same interface and visuals on all platforms  
      (NOT native dialogs)</li>
  <li>📦 <strong>Static library</strong> — distributed as <code>libELC.a</code> for each platform</li>
</ul>

<hr>

<h2>📦 Library Files</h2>

<p>ELC is shipped as prebuilt static libraries for each OS:</p>

<ul>
  <li><code>libELC.a</code> — macOS</li>
  <li><code>libELC-linux.a</code> — Linux</li>
  <li><code>libELC-windows.a</code> — Windows</li>
</ul>

<p>You include the header <code>ELC.h</code> and link the proper library for your platform.</p>

<hr>

<h2>📁 File Picker</h2>

<p>ELC includes a unified custom file picker.  
It is <strong>not native</strong>, but an in-engine cross-platform UI component:</p>

<ul>
  <li>Works the same on macOS, Windows, and Linux</li>
  <li>Supports filters (PNG, JPG, etc)</li>
  <li>Supports selecting single or multiple files</li>
  <li>Built entirely inside your app with ELC GUI tools</li>
</ul>

<hr>

<h2>🧱 ELC Modules</h2>

<h3>🔹 ELC</h3>
<p>The core system, shared utilities, base types, safety helpers.</p>

<h3>🔹 ELCGui</h3>
<p>Buttons, windows, labels, popups, layout helpers, interaction tools.</p>

<h3>🔹 ELCImage</h3>
<p>Safe wrapper around raylib images and textures with helpful utilities.</p>

<h3>🔹 ELCAudio</h3>
<p>Simple SFX/music handling with minimal API.</p>

<h3>🔹 ELCMath</h3>
<p>Vector math, geometry helpers, random tools, small utilities.</p>

<h3>🔹 ELCPopup</h3>
<p>Popup windows, alerts, confirmations, in-UI messages.</p>

<h3>🔹 ELCFilePicker</h3>
<p>Your cross-platform, non-native file chooser widget.</p>

<hr>

<h2>🧪 Minimal Usage Example</h2>

<pre>
#include "ELC.h"

int main() {
    InitWindow(800, 600, "ELC Demo");

    ELC::Button b({50, 50}, {160, 40}, "Click Me!");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        b.Draw();
        EndDrawing();
    }
}
</pre>

<hr>

<h2>📄 License</h2>
<p>MIT License</p>

<hr>

<h2>❤️ Author</h2>
<p>Created by <strong>Coding Master Demi</strong></p>

</body>
</html>
