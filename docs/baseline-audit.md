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

**Observed result:** [Insert actual baseline execution result]

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

| Check | Result |
|---|---|
| Original project compilation | [Actual result] |
| Original project startup | [Actual result] |
| Mixed menu input `1abc` | [Actual result] |
| Existing data loading | [Actual result] |

## 5. Improvement Scope

The team will improve menu input validation, traveler input validation, review/rating validation, application stability and automated testing. GitHub Actions will be introduced to support continuous integration.

## 6. Limitations

This audit is based on the inspected source code and the tests actually performed. Potential defects identified through code inspection are not presented as experimentally reproduced failures unless supporting execution evidence exists.