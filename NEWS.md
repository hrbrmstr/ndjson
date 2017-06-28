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
