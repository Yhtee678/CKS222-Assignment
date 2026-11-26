# TravelGo Baseline Audit

## 1. Purpose

This audit records the initial condition of the TravelGo C++ hotel review application before the team's quality improvement work. The baseline is used to identify defects, plan corrective actions and compare the results after implementation.

## 2. Existing System

TravelGo is a console-based hotel review application written in C++17. It supports traveler profiles, hotel reviews, hotel recommendations and loyalty-related functions. Traveler and review records are stored in `users.txt` and `reviews.txt`.

## 3. Baseline Findings

### B01 — Menu Input Validation

The original menu used formatted integer extraction (`cin >> choice`). Although it handled some invalid non-numeric input, a mixed input such as `1abc` could be partially accepted as Option 1.

**Planned improvement:** Validate the entire input line before accepting a menu choice.

**Responsible member:** M1

### B02 — Startup Stack Usage

The original application declared fixed-size arrays of Traveler and Hotel objects inside `main()`. These arrays may exceed the default stack capacity in the Windows environment.

**Observed result:** The application compiled successfully but terminated during startup with exit code -1073741571 (0xC00000FD), indicating a stack overflow. After increasing the stack size to 16 MB, the application started successfully and displayed the main menu.

**Temporary diagnostic workaround:** Compile with `-Wl,--stack,16777216`.

**Responsible member:** M4

### B03 — Data Loading Capacity

The original data loading functions did not consistently check array capacity before inserting traveler or hotel records.

**Potential impact:** Out-of-bounds memory access when input exceeds the configured capacity.

**Responsible member:** M4

### B04 — Review Rating Parsing

The original review loader reads ratings using an integer variable, while the Review model supports a floating-point rating.

**Potential impact:** Incorrect parsing if the input file contains fractional ratings.

**Responsible members:** M3 and M4, subject to the agreed rating requirements.

## 4. Baseline Verification

## 4. Baseline Verification

| Check | Result |
|---|---|
| Original project compilation | Compiled successfully using G++ with C++17. |
| Original project startup | Failed with a stack overflow (0xC00000FD) under the default stack configuration. Started successfully after increasing the stack size to 16 MB. |
| Mixed menu input `1abc` | The original formatted integer extraction could accept the numeric prefix as Option 1. Identified through source code inspection. |
| Existing data loading | Successfully loaded 10 travelers and 12 hotels after applying the temporary stack size workaround. |

## 5. Improvement Scope

The team will improve menu input validation, traveler input validation, review/rating validation, application stability and automated testing. GitHub Actions will be introduced to support continuous integration.

## 6. Limitations

This audit is based on the inspected source code and the tests actually performed. Potential defects identified through code inspection are not presented as experimentally reproduced failures unless supporting execution evidence exists.

## 7. Baseline Context and Repository Refactoring

This baseline audit documents the original project structure and software quality issues identified before the quality improvement activities.

Following the integration of the quality improvements, the repository was reorganized to separate application source code, header files, persistent data, automated tests and development documentation.

The original file locations and diagnostic commands recorded in this audit are retained for historical reference. Updated compilation instructions, execution commands and testing procedures are available in the current [README](../README.md).

Regression testing was performed before and after the repository restructuring to verify that the existing validation, persistence and capacity tests continued to pass.