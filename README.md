# Movie App 🎬 — Beautiful, Buzzy, and Built with C++!

Welcome to Movie App — a polished desktop application with a friendly GUI where movie lovers and admins both feel at home. This project combines a responsive user interface for browsing, rating, and searching movies with a powerful admin interface for managing the catalogue, users, and content.

Built using C++ (core logic), CMake (build), and HTML (embedded UI pages or assets), Movie App is designed to be extended, themed, and deployed across platforms.

---

Table of Contents
- Features
- Usage (User & Admin)
- Configuration
- Contributing

---

Features ✨
- Two polished interfaces:
  - User interface: browse, search, view details, rate and favorite movies
  - Admin interface: add/remove/edit movies, manage users, moderate content
- Clean C++ core for performance and reliability
- Cross-platform build system using CMake
- HTML/CSS assets for flexible, themeable UI components
- Designed for easy testing and iteration

---

How to use — quick tour 🎟️

User interface (what the movie fan sees)
- Browse movies by category and popularity
- Click a movie to view details: synopsis, cast, poster, ratings
- Rate and favorite movies
- Search bar with instant suggestions

Admin interface (tools for content managers)
- Create / edit / delete movie entries (title, synopsis, poster, tags)

---

Troubleshooting
- Build errors:
  - Missing GUI libs? Install the framework dev packages (e.g., libqt5-dev) or set CMAKE_PREFIX_PATH.
  - Compiler warnings? Try building with -DCMAKE_BUILD_TYPE=Debug to see details.
- Runtime problems:
  - Assets not found? Check MOVIEAPP_ASSETS or relative paths in config.
  - Admin pages blank? Ensure your embedded HTML files are packaged/copied into the build output.

---

Contributing 🤝
We love help! To contribute:
1. Fork the repo
2. Create a feature branch: git checkout -b feat/cool-thing
3. Add code, tests, and docs
4. Open a Pull Request describing the change
