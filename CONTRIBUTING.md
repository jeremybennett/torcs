# Contributing to Open Racing Simulator

Thank you for your interest in contributing.  This guide covers how to set up
a development environment, what to work on, and how to submit changes.

---

## Getting the Code

```
git clone https://github.com/awest813/Open-Racing-Simulator-.git
cd "Open-Racing-Simulator-"
```

---

## Development Environment

### Linux (recommended)

Install the required libraries before building.  On Debian/Ubuntu:

```
sudo apt-get install \
  build-essential autoconf automake \
  libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev \
  libplib-dev libopenal-dev libalut-dev \
  libvorbis-dev zlib1g-dev libpng-dev libx11-dev libxrandr-dev
```

Build steps:

```
./configure
make
make install
make datainstall
```

To also build the API documentation (requires Doxygen):

```
make doc
```

The generated HTML lands in `doc/manual/api/`.

Useful configure flags:

- `--enable-debug` — enable debug symbols and assertions
- `--disable-xrandr` — disable XRandR if it causes issues on your system

### Windows

The repository ships Visual Studio project files for older toolchains.
Modern Windows toolchain support is still a roadmap item.  See the README
for the current Windows build steps.

---

## Running the Simulator

After installing:

```
torcs                       # interactive mode
torcs -r <race-config.xml>  # headless race from config file
```

Headless mode (`-r`) is the fastest way to iterate on robots, physics
changes, or race-manager configuration without the full rendering stack.

---

## Where to Start

- `ROADMAP.md` — full project plan and current priorities
- `src/doc/architecture.md` — overview of the three-tier architecture
- `src/interfaces/` — interface headers for all plugin types
- `src/libs/` — shared utility libraries used across the project
- `src/modules/` — runtime-loadable plugins (graphics, simulation, robots)
- `src/drivers/` — AI robot driver implementations
- `data/` — cars, tracks, race-manager XML, menus, and sounds
- `doc/tutorials/robot/` — browser-based robot development tutorial

---

## Code Conventions

The codebase is pre-C++11 C and C++.  Please match the style of the file
you are editing:

- Indentation follows the existing file — most C++ uses tabs.
- Keep line lengths reasonable (existing code is not strictly limited).
- Prefer `const` over magic numbers where practical.
- Avoid introducing new dependencies unless the ROADMAP already calls for
  the change.
- Do not introduce C++11 or later constructs unless explicitly coordinated
  on the roadmap; the build still needs to work on older toolchains.
- Prefer fixing one thing per commit to make history readable.

---

## Submitting Changes

1. Fork the repository and create a branch from `main` (or the active
   milestone branch).
2. Make your changes in small, focused commits with clear commit messages.
3. Verify the build succeeds: `./configure && make && make install && make datainstall`.
4. If your change affects AI or physics, run a headless race to confirm no
   obvious regressions.
5. Open a pull request against the target branch and describe what you
   changed and why.

---

## Reporting Bugs

Open a GitHub issue with:

- A short description of the problem.
- Steps to reproduce (including the race config if relevant).
- Build environment (OS, compiler version, hardware).
- Any relevant output from the terminal or a Valgrind run.

---

## Licensing

Code contributions are accepted under the project's existing GPL v2 license.
By submitting a pull request you confirm that you have the right to contribute
the code under those terms.

If you are contributing new assets (cars, tracks, sounds, textures), ensure
that the asset is clearly GPL-compatible or public domain, and include
licensing metadata alongside the asset.  Assets with trademark or
redistribution concerns will not be accepted.

---

## Questions

For questions about the codebase, open a GitHub issue or start a discussion
in the repository.  The architecture document and robot tutorial are the best
starting points for understanding how the simulator is structured.
