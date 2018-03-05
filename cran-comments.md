## Test environments
* local macOS (10.13.4 beta 3) install, R 3.4.3 (clang)
* local ubuntu 16.04, R 3.4.3 (g++-7)
* Travis-CI (linux) https://travis-ci.org/hrbrmstr/ndjson
* win-builder (devel and release)

## R CMD check results

0 errors | 0 warnings | 1 note (Maintainer)

* This is an update

## Reverse dependencies

None

## General notes

- License change to MIT
- Update core C++ library the pkg uses to 3.1.1
- Removed #pragmas from said C++ library that was causing
  CRAN issues due to the new "show all warnings" policy
