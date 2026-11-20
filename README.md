# TravelGo — C++ Hotel Review System

## Project Overview

TravelGo is a console-based hotel review system developed in C++17. The application allows users to explore hotel information, manage traveler profiles, submit reviews and receive hotel recommendations.

This repository is used for the CKS222 Software Process and Life Cycle assignment to demonstrate software quality improvement practices and collaborative development using GitHub.

## Main Features

1. Property Deep-Dive
2. Traveler Profile Management
3. Top-Pick Matcher
4. Top Reviewers
5. Add New Review
6. Add New Traveler
7. Save and Exit

## Technology

- Language: C++17
- Compiler: GCC / G++
- Development Environment: Visual Studio Code
- Version Control: Git and GitHub
- Data Storage: Text files (`users.txt` and `reviews.txt`)

## Project Structure

- `main.cpp` — Application entry point and file persistence
- `Feature.h` — Main application features
- `Traveler.h` — Traveler model
- `Hotel.h` — Hotel model
- `Review.h` — Review model
- `MenuInput.h` — Menu input validation
- `tests/` — Automated test files
- `docs/` — Project documentation

## Build Instructions

### Windows (MSYS2 UCRT64 GCC)

Open a terminal in the repository root:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Wl,--stack,16777216 main.cpp -o travelgo.exe
```

Run the application:

```cmd
travelgo.exe
```

The increased stack size is a temporary workaround for the original application. The stability improvement is tracked separately.

## Menu Validation Test

Compile:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic tests/test_menu.cpp -o test_menu.exe
```

Run:

```cmd
test_menu.exe
```

Expected output when all tests pass:

```text
All menu validation tests passed!
```

## Development Workflow

Each team member works on a separate Git branch. Changes are committed with descriptive messages, pushed to GitHub and submitted through Pull Requests for review before merging.

The project applies software engineering practices including Test-Driven Development, code review, pair programming and continuous integration as these activities are implemented and verified.

## Known Baseline Issues

The initial application contains areas requiring improvement, including strict input validation, stack usage and file loading capacity checks.

See `docs/baseline-audit.md` for details.

## Team Responsibilities

- M1 — Menu Validation, Baseline Documentation and Integration
- M2 — Traveler Validation
- M3 — Review and Rating Validation
- M4 — Stability and Persistence
- M5 — GitHub Actions Continuous Integration

## Notes

This project is an academic software quality improvement exercise. The implementation and testing evidence should reflect the actual work performed by the team.