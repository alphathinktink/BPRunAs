# BogProg RunAs

BogProg RunAs is a lightweight Windows utility for launching applications under different user credentials via a simple GUI. Built using classic Win32 API techniques and compiled with MinGW.

This project is **not open-source**. It is published **for reference and educational purposes only**. No reuse or modification is permitted without explicit written permission from the author.

---

## 📦 Project Contents

```
BogProg RunAs/
├── AnsiString.h         ← Lightweight ANSI-compatible string wrapper
├── BPIcon.ico           ← Application icon resource
├── BPRunAs.cpp          ← Main entry point and message loop
├── BPRunAs.sess         ← Notepad++ session file
├── build.bat            ← Build script using MinGW (adjust path as needed)
├── DispWindow.cpp       ← GUI logic and handlers
├── DispWindow.h         ← GUI declarations and global handles
├── LICENSE              ← Strict usage and no-modification license
├── resource.h           ← Resource ID defines
├── resource.rc          ← Dialog and icon resources
├── TansGLEM.cpp         ← Windows error code translator
├── TansGLEM.h           ← Error translator declaration
├── UniString.h          ← Custom Unicode string class
└── bin/                 ← Output folder for compiled EXE and object files
```

---

## 🛠 Build Requirements

To compile `BPRunAs.exe`:

### Option 1: Using MSYS2 (Recommended)

Install required packages:
```bash
pacman -S mingw-w64-i686-gcc mingw-w64-i686-binutils
```

Set `MINGW32_BIN` in `build.bat` to:
```batch
SET MINGW32_BIN=C:\msys64\mingw32\bin
```

Then run:
```batch
CALL build.bat
```

### Option 2: Standalone MinGW

If you're using a lightweight MinGW install (e.g., `C:\MinGW32\bin`), ensure it includes:
- `g++`, `gcc`, `windres`, `ld`, `as`, `ar`

Update `build.bat` accordingly:
```batch
SET MINGW32_BIN=C:\MinGW32\bin
```

---

## 🔒 License

```
Copyright (c) 2025
Leonard W. Bogard dba BogProg Software (thinktink / alphathinktink)

All rights reserved.

This source code is provided for reference and educational purposes only.
You may not copy, modify, publish, distribute, sublicense, or use this code
or any portion thereof in any software, whether open-source or proprietary,
without explicit written permission from the author.

No warranty is expressed or implied. Use at your own risk.

Contact the author to request permission for any usage beyond reading.
```

---

## 🧠 Author

- **Leonard W. Bogard**
- GitHub: [@alphathinktink](https://github.com/alphathinktink)
- Project: [BogProg Software](https://bogproghome.hopto.org/) *(link placeholder, update if public)*

---

## 💬 Notes

- This project is part of a broader toolset used internally for user process management.
- `UniString` and `AnsiString` headers are used both in VCL and non-VCL projects.
- Dialog UI is defined in `resource.rc` and constructed with pure WinAPI calls.

---

> For any questions or requests regarding this project, contact the author directly. Contributions, forks, or derivative works are not permitted without prior authorization.
> The compiled binary output is authorized for private use, but not republication or redistribution.
