0.6.0
=====================
* License change to MIT
* Updated to nlohmann/json.hpp v3.1.1 (Ref:
  <https://github.com/nlohmann/json/blob/develop/ChangeLog.md>)
* Removed nlohmann/json.hpp #pragma's causing CRAN issues vis-a-vis the new
  "Clutter up the console with unnecessary warnings" policy.
# Slightly modified tests

0.5.0
=====================
* Updated core ndjson file to take care of some buffer overflow vulns
* Optionally returns a `tbl_df` vs a `tbl_dt` (data.table is used for speed on list rbind)
* Fixed CRAN check errors

0.4.0
=====================
* Gracefully handles parsing errors when streaming in data

0.3.0
=====================
* PR from Dirk to remove unnecessary dependency on Rcpp11
* Added `flatten()` to work with vectors of JSON vs just files

0.2.0
=====================
* Initial release
