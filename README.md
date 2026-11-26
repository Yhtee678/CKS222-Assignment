# TravelGo — C++ Hotel Review System

[![TravelGo CI](https://github.com/Yhtee678/CKS222-Assignment/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/Yhtee678/CKS222-Assignment/actions/workflows/ci.yml)

## 1. Project Overview

TravelGo is a console-based hotel review and traveler management system developed in C++. This repository extends an existing CKC112 Object-Oriented Programming university project as part of the CKS222 Software Process and Life Cycle assignment at Universiti Sains Malaysia (USM).

The extension focuses on improving software reliability, input validation, data persistence, maintainability and automated testing while retaining the original system functionalities.

## 2. System Features

- Property Deep-Dive
- Traveler Profile Management
- Top-Pick Matcher
- Top Reviewers
- Add New Review
- Add New Traveler
- Save and Exit

## 3. Quality Improvements

| Area | Improvement |
|---|---|
| Menu Input | Strict menu selection validation and invalid input handling. |
| Traveler Registration | Improved validation of traveler registration inputs. |
| Review Submission | Rating validation and capacity checks before review submission. |
| Loyalty Points | Points are awarded after successful review submission. |
| Startup Stability | Static storage allocation to reduce stack memory issues. |
| Data Persistence | Prevents data files from being overwritten when loading is incomplete. |
| Maintainability | Separates source code, header files, data, tests and documentation. |
| Automated Testing | Includes unit tests, persistence testing and capacity boundary testing. |
| Continuous Integration | Automated compilation and testing through GitHub Actions. |

## 4. Technology Stack

| Technology | Purpose |
|---|---|
| C++17 | Application development |
| GCC / G++ | C++ compilation |
| Python 3 | Automated integration and regression testing |
| Text Files (TSV) | Persistent data storage |
| Git | Version control |
| GitHub | Collaborative development and code review |
| GitHub Actions | Continuous integration |

## 5. Project Structure

```text
CKS222-Assignment/
├── .github/
│   └── workflows/
│       └── ci.yml
├── src/
│   └── main.cpp
├── include/
│   ├── Constants.h
│   ├── Feature.h
│   ├── Hotel.h
│   ├── MenuInput.h
│   ├── Person.h
│   ├── RatingValidation.h
│   ├── Review.h
│   ├── Traveler.h
│   └── TravelerValidation.h
├── data/
│   ├── users.txt
│   └── reviews.txt
├── tests/
│   ├── test_menu.cpp
│   ├── test_traveler.cpp
│   ├── test_rating.cpp
│   ├── test_persistence.py
│   ├── test_traveler_capacity.py
│   └── test_hotel_capacity.py
├── docs/
│   ├── baseline-audit.md
│   ├── pair-programming-log.md
│   └── evidence/
├── build/                  # Generated locally
├── .gitignore
└── README.md
```

| Directory | Description |
|---|---|
| `src/` | Main application source code |
| `include/` | Class definitions, constants and validation functions |
| `data/` | Persistent traveler and review records |
| `tests/` | Automated unit and integration tests |
| `docs/` | Development documentation and supporting evidence |
| `.github/workflows/` | Continuous integration configuration |
| `build/` | Generated executables excluded from version control |

## 6. Getting Started

### Prerequisites

- Git
- G++ compiler with C++17 support
- Python 3

### Clone the Repository

```bash
git clone https://github.com/Yhtee678/CKS222-Assignment.git
cd CKS222-Assignment
```

### Build and Run on Windows (CMD)

```cmd
mkdir build
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/main.cpp -o build/travelgo.exe
.\build\travelgo.exe
```

### Build and Run on Linux

```bash
mkdir -p build
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/main.cpp -o build/travelgo
./build/travelgo
```

Run the application from the repository root so that it can access the files in the `data/` directory.

## 7. Automated Testing

The project includes six automated test suites covering input validation, persistence and capacity boundaries.

| Test Suite | Coverage |
|---|---|
| Menu Validation | Valid and invalid menu selections |
| Traveler Validation | Traveler registration input validation |
| Rating Validation | Valid ratings, invalid ratings, retries and end-of-input handling |
| Persistence Smoke Test | Data preservation after Save and Exit |
| Traveler Capacity | Successful loading of 100 travelers and rejection of 101 travelers |
| Hotel Capacity | Successful loading of 50 hotels and rejection of 51 hotels |

### Windows (CMD)

Compile the unit tests:

```cmd
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude tests/test_menu.cpp -o build/test_menu.exe
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude tests/test_traveler.cpp -o build/test_traveler.exe
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude tests/test_rating.cpp -o build/test_rating.exe
```

Run the unit tests:

```cmd
.\build\test_menu.exe
.\build\test_traveler.exe
.\build\test_rating.exe
```

Run the integration tests:

```cmd
py tests/test_persistence.py .\build\travelgo.exe
py tests/test_traveler_capacity.py .\build\travelgo.exe
py tests/test_hotel_capacity.py .\build\travelgo.exe
```

### Linux

Compile and run the unit tests:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude tests/test_menu.cpp -o build/test_menu
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude tests/test_traveler.cpp -o build/test_traveler
g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude tests/test_rating.cpp -o build/test_rating

./build/test_menu
./build/test_traveler
./build/test_rating
```

Run the integration tests:

```bash
python3 tests/test_persistence.py ./build/travelgo
python3 tests/test_traveler_capacity.py ./build/travelgo
python3 tests/test_hotel_capacity.py ./build/travelgo
```

The Python tests use isolated temporary directories to avoid modifying the original project data. These directories are automatically removed after testing.

## 8. Continuous Integration

GitHub Actions is configured to run the build and test workflow automatically on pushes and pull requests.

The workflow performs the following activities:

1. Checks out the repository.
2. Compiles the TravelGo application.
3. Compiles and executes the three C++ unit test suites.
4. Executes the persistence smoke test.
5. Executes the traveler and hotel capacity tests.

The workflow reports a failure if any compilation or testing step fails.

[View GitHub Actions](https://github.com/Yhtee678/CKS222-Assignment/actions)

## 9. Development Practices

The project applies selected software development practices to support collaborative development and software quality.

| Practice | Application |
|---|---|
| Test-Driven Development (TDD) | Menu and rating validation improvements supported by test-first development. |
| Pair Programming | Collaborative development of rating validation with driver and navigator role switching. |
| Continuous Integration | Automated compilation and testing using GitHub Actions. |
| Code Review | Pull request reviews, change requests and corrective commits before integration. |
| Refactoring | Repository restructuring and test script improvements to improve maintainability. |
| Regression Testing | Re-execution of existing tests to verify behavior after changes. |
| Incremental Development | Integration of quality improvements through separate feature branches and pull requests. |

## 10. Team Members and Contributions

| Member | Name | Main Contributions |
|---|---|---|
| M1 | Tee Yu Heng | Project coordination, baseline audit, menu validation, code review and repository refactoring |
| M2 | Abdul Muaz | Traveler registration validation and pair programming |
| M3 | Wan Ahmad Aiman | Review rating validation, review submission consistency and pair programming |
| M4 | Ong Zhen Hang | Startup stability, data persistence protection and capacity testing |
| M5 | Muhammad Izzat | GitHub Actions continuous integration and automated build configuration |

## 11. Project Documentation

- [Baseline Audit](docs/baseline-audit.md)
- [Pair Programming Log](docs/pair-programming-log.md)
- [Development Evidence](docs/evidence/)
- [Pull Requests](https://github.com/Yhtee678/CKS222-Assignment/pulls?q=is%3Apr)
- [Continuous Integration History](https://github.com/Yhtee678/CKS222-Assignment/actions)

## 12. Academic Context

This project is developed for the CKS222 Software Process and Life Cycle assignment at the School of Computer Sciences, Universiti Sains Malaysia.

The project demonstrates the application of software process improvement and selected Extreme Programming (XP) practices through the quality improvement of an existing university software project.