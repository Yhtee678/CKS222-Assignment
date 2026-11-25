# Pair Programming Session Log

**Project:** TravelGo Quality Improvement Extension

**Task:** Review Rating Input Validation

**Participants:** Muaz and Wan Aiman

**Date:** 23/11/2026 - 24/11/2026

**Start Time:** 23/11/2026, 11.30 PM 

**End Time:** 24/11/2026, 12.30 AM 

**Platform:** Discord 

## Session 1 — Test-First Development

**Driver:** Wan Aiman

**Navigator:** Muaz

Activities:
- Wrote tests to check whether the rating validation function accepts valid ratings from 1 to 5 and rejects invalid inputs.
- Tested invalid inputs such as abc, 6 and 3.5 to identify validation issues.
- Ran the tests before implementing the validation logic and recorded the RED result.

## Session 2 — Implementation and Verification

**Driver:** Muaz

**Navigator:** Wan Aiman

Activities:
- Implemented the rating validation logic to ensure that only integer ratings from 1 to 5 are accepted.
- The Navigator reviewed the implementation and provided feedback on the validation conditions and input handling.
- Ran the tests again to verify that invalid ratings were rejected and valid ratings were accepted. The tests passed, confirming the GREEN result.

## Refactoring and Discussion

Both members reviewed the rating validation implementation, including variable names, validation conditions, input handling and the rating range.

The implementation was retained because the code was clear and no unnecessary duplicate logic was identified. The rating validation tests were run again after the review to ensure that the functionality remained correct.

## Evidence

- RED Commit: [Red Commit](evidence/RED-commit.jpg)
- GREEN Commit: [Green Commit](evidence/GREEN-commit.jpg)
- Pull Request: [View Pull Request #4](https://github.com/Yhtee678/CKS222-Assignment/pull/4#issue-6564673055)
- Test Output: [Test Output](evidence/Test-Output1.jpg)
- Test Output Validation: [Test Output Validation](evidence/Test-Output2.jpg)

## Conclusion

The pair programming session helped us practise test-first development and improve our understanding of rating input validation. We successfully implemented and tested the validation logic to ensure that only valid ratings from 1 to 5 are accepted. Through collaboration and code review, we also improved our understanding of testing, debugging, and maintaining clean code.
