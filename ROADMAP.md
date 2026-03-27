# Open Racing Simulator Roadmap

This roadmap turns the historical TORCS backlog into a clearer plan for the Open
Racing Simulator fork. It is intended to communicate direction and priorities, not
to promise exact delivery dates.

The project has two parallel responsibilities:

1. keep the current 1.3.x line usable for players, modders, and researchers
2. prepare a healthier foundation for larger architectural changes later

---

## Guiding Priorities

These priorities apply across every release stream:

- protect the headless / automation workflows used for AI and research
- improve contributor documentation before expanding the feature surface
- modernize carefully without breaking existing cars, tracks, and robots
- reduce legal and licensing risk in bundled content
- replace fragile legacy dependencies only when a clear migration path exists

---

## Current Focus — Documentation, Stability, and Project Hygiene

These items should move first because they make every later release easier:

- [x] Refresh contributor documentation and setup guidance
- [x] Update the robot tutorial and race-manager documentation
- [x] Document important repository subsystems and extension points
- [ ] Review bundled assets for licensing, redistribution, and trademark issues
- [x] Tighten the fork identity where old TORCS naming is confusing

---

## 1.3.x Stabilization Track

Goal: keep the existing simulator practical while avoiding unnecessary API breaks.

### Simulation and Gameplay

- [ ] Finish car adjustments for tire wear and performance balance
- [ ] Improve ranking when damaged or stranded cars stay classified incorrectly
- [ ] Make brake balance adjustable during a session
- [ ] Add curb sound support
- [ ] Investigate dynamic track-surface effects
- [ ] Investigate wind and ambient-temperature effects

### Analysis and Race Operations

- [ ] Add a telemetry / data recorder
- [ ] Add a data-analysis workflow for lap comparison and filtering
- [ ] Expose more telemetry channels, including speed and suspension data
- [ ] Prototype a replay pipeline
- [ ] Add timed race formats
- [ ] Expand configurable rules and penalty handling without forcing a 1.4 break
- [ ] Fix repeated-violation edge cases when entering or exiting pit lanes

### Tooling and UX

- [ ] Update Visual Studio support to a more practical baseline
- [ ] Expose hidden or difficult-to-find settings in the GUI
- [ ] Add GUI support for event blacklisting

---

## 1.4 Preparation Track

Goal: prepare breaking changes only after the 1.3.x line is better documented and
more maintainable.

### Robot API

- [ ] Review optional callbacks such as `askfeatures`, `callonce`, `grid`, and `postprocess`
- [ ] Identify robots by stable names instead of integer slots where possible
- [ ] Remove the fixed 10-driver-per-module limit

### Graphics and Platform

- [ ] Replace GLUT-era assumptions with a more modern windowing layer
- [ ] Review and revive the SDL 2 path
- [ ] Rework skid marks, masking, shadows, and frame-rate-dependent rendering behavior
- [ ] Move graphics-engine state into an explicit context structure
- [ ] Reduce dynamic allocation inside rendering hot paths
- [ ] Review macOS support
- [ ] Review MorphOS support

### Audio

- [ ] Update OpenAL usage and remove deprecated ALUT dependencies
- [ ] Replace WAV-only assumptions with OGG Vorbis where appropriate
- [ ] Fix split-screen multiplayer audio issues

### Physics and Simulation

- [ ] Review simuv3 changes for selective merge into simuv2
- [ ] Review and merge the ABS work if it still applies cleanly
- [ ] Review and merge 4WD-related work if it still applies cleanly
- [ ] Add brake and engine wear with cooling effects
- [ ] Add configurable track-wall properties
- [ ] Extend track definitions for crossings, split/join segments, and variable width
- [ ] Consider differential adjustment during a session

### Content and Race Flow

- [ ] Add support for better starting / race modes, including multi-class ideas
- [ ] Add support vehicles such as pace cars or trucks for incident cleanup
- [ ] Deliver a replay feature that is robust enough for long-term support

---

## Content and Compliance Track

Goal: keep the project redistributable and easier to package.

- [ ] Replace or retire trademark-sensitive car content
- [ ] Rework buggy and baja-bug assets
- [ ] Replace rally-car content that cannot be safely shipped long-term
- [ ] Remove invalid geometry from bundled tracks
- [ ] Audit car, track, and UI assets for missing licensing metadata

Suggested replacements retained from the historical backlog:

- [ ] Replace `155-DTM`
- [ ] Replace `acura-nsx`
- [ ] Replace `mc-larenf1`
- [ ] Replace `p406`

---

## Engineering Debt Track

Goal: reduce maintenance cost without destabilizing the simulation.

- [x] Migrate away from pre-C++11 idioms where changes are low-risk
- [ ] Replace raw allocation patterns with RAII-based ownership
- [ ] Reduce C-style casts and narrow unsafe conversions
- [ ] Replace `printf`-style diagnostics with a structured logging approach
- [ ] Replace remaining fragile string handling with safer abstractions
- [x] Add an initial automated test suite for utility and parsing code
- [ ] Remove the circular dependency between `raceman.h` and `simu.h`
- [ ] Move reusable spline code into a shared math library
- [ ] Eliminate `glGet*` usage in simulation-time paths
- [ ] Refactor `trackgen` to reduce duplicated left/right logic
- [ ] Review whether PLIB usage can be isolated or retired incrementally
- [ ] Remove sound-property calculation from `wheel.cpp`
- [ ] Convert internal force-unit handling consistently from lbs to lbf

---

## 2.0 Networking Track

Goal: introduce multiplayer only after the simulation and APIs are easier to
evolve safely.

### Pre-release exploration

- [ ] Design the network architecture and simulation-loop integration points
- [ ] Build a networking proof of concept
- [ ] Evaluate race formats that work well online
- [ ] Add endianness-safe binary data infrastructure where needed

### Public 2.0 goals

- [ ] Ship an initial client/server multiplayer implementation
- [ ] Finalize replays as a supported feature, not just a prototype

---

## Long-Term Exploration

These items are valuable, but they sit behind the more practical work above:

- [ ] Modern rendering beyond the fixed-function OpenGL pipeline
- [ ] Dynamic sky, weather, and day/night systems
- [ ] Improved vegetation, shadows, and environment detail
- [ ] Procedural or in-game-assisted track creation
- [ ] In-game livery editing
- [ ] Animated driver and pit-crew support
- [ ] Dirt accumulation and broader visual wear systems
- [ ] Free camera and better spectating tools
- [ ] Force-feedback wheel support
- [ ] Story / career progression
- [ ] Traffic or free-roam modes
- [ ] Multi-core simulation work
- [ ] Benchmark / screensaver-style modes
- [ ] Better opponent-set presets for human players
- [ ] Seamless hand-off between human control and AI assistance

---

## Success Criteria

The roadmap is working if the project becomes easier to build, easier to
understand, safer to redistribute, and still useful for both players and
research-focused users.

*Last updated: 2026-03-27 (second pass)*
