## Test environments
* local OS X install, R 3.4.3 (clang)
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
- Removed included-json library #pragmas causing CRAN issues due to new 
  "show all warnings" policy
- Update core C++ library the pkg uses to 3.1.1
