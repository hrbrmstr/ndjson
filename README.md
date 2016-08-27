
`ndjson` : Wicked-fast Streaming JSON ('ndjson') Reader

Rcpp/C++11 wrapper for <https://github.com/nlohmann/json>

The goal is to create a completely "flat" `data.frame`-like structure from ndjson records in plain text ndjson files or gzip'd ndjson files

The following functions are implemented:

-   `stream_in`: Stream in ndjson from a file (handles `.gz` files)
-   `validate`: Validate JSON records in an ndjson file (handles `.gz` files)

### Installation

``` r
devtools::install_git("https://gitlab.com/hrbrmstr/ndjson.git")
```

### Usage

``` r
library(ndjson)
library(microbenchmark)

# current verison
packageVersion("ndjson")
```

    ## [1] '0.1.0'

``` r
f <- system.file("extdata", "test.json", package="ndjson")
gzf <- system.file("extdata", "testgz.json.gz", package="ndjson")

dplyr::glimpse(ndjson::stream_in(f))
```

    ## Observations: 100
    ## Variables: 8
    ## $ args                    <int> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA,...
    ## $ headers.Accept          <chr> "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*",...
    ## $ headers.Accept-Encoding <chr> "identity", "identity", "identity", "identity", "identity", "identity", "identity",...
    ## $ headers.Host            <chr> "httpbin.org", "httpbin.org", "httpbin.org", "httpbin.org", "httpbin.org", "httpbin...
    ## $ headers.User-Agent      <chr> "Wget/1.18 (darwin15.5.0)", "Wget/1.18 (darwin15.5.0)", "Wget/1.18 (darwin15.5.0)",...
    ## $ id                      <dbl> 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 2...
    ## $ origin                  <chr> "50.252.233.22", "50.252.233.22", "50.252.233.22", "50.252.233.22", "50.252.233.22"...
    ## $ url                     <chr> "http://httpbin.org/stream/100", "http://httpbin.org/stream/100", "http://httpbin.o...

``` r
dplyr::glimpse(ndjson::stream_in(gzf))
```

    ## Observations: 100
    ## Variables: 8
    ## $ args                    <int> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA,...
    ## $ headers.Accept          <chr> "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*",...
    ## $ headers.Accept-Encoding <chr> "identity", "identity", "identity", "identity", "identity", "identity", "identity",...
    ## $ headers.Host            <chr> "httpbin.org", "httpbin.org", "httpbin.org", "httpbin.org", "httpbin.org", "httpbin...
    ## $ headers.User-Agent      <chr> "Wget/1.18 (darwin15.5.0)", "Wget/1.18 (darwin15.5.0)", "Wget/1.18 (darwin15.5.0)",...
    ## $ id                      <dbl> 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 2...
    ## $ origin                  <chr> "50.252.233.22", "50.252.233.22", "50.252.233.22", "50.252.233.22", "50.252.233.22"...
    ## $ url                     <chr> "http://httpbin.org/stream/100", "http://httpbin.org/stream/100", "http://httpbin.o...

``` r
dplyr::glimpse(jsonlite::stream_in(file(f), flatten=TRUE, verbose=FALSE))
```

    ## Observations: 100
    ## Variables: 5
    ## $ url     <chr> "http://httpbin.org/stream/100", "http://httpbin.org/stream/100", "http://httpbin.org/stream/100", ...
    ## $ headers <data.frame> c("httpbin.org", "httpbin.org", "httpbin.org", "httpbin.org", "httpbin.org", "httpbin.org", ...
    ## $ args    <data.frame> 
    ## $ id      <int> 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 2...
    ## $ origin  <chr> "50.252.233.22", "50.252.233.22", "50.252.233.22", "50.252.233.22", "50.252.233.22", "50.252.233.22...

``` r
dplyr::glimpse(jsonlite::stream_in(gzfile(gzf), flatten=TRUE, verbose=FALSE))
```

    ## Observations: 100
    ## Variables: 5
    ## $ url     <chr> "http://httpbin.org/stream/100", "http://httpbin.org/stream/100", "http://httpbin.org/stream/100", ...
    ## $ headers <data.frame> c("httpbin.org", "httpbin.org", "httpbin.org", "httpbin.org", "httpbin.org", "httpbin.org", ...
    ## $ args    <data.frame> 
    ## $ id      <int> 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 2...
    ## $ origin  <chr> "50.252.233.22", "50.252.233.22", "50.252.233.22", "50.252.233.22", "50.252.233.22", "50.252.233.22...

``` r
microbenchmark(
    ndjson={ ndjson::stream_in(f) },
  jsonlite={ jsonlite::stream_in(file(f), flatten=TRUE, verbose=FALSE) }
)
```

    ## Unit: milliseconds
    ##      expr     min       lq     mean   median       uq       max neval cld
    ##    ndjson 2.14295 2.272900 2.476348 2.360306 2.491099  4.647523   100  a 
    ##  jsonlite 7.09834 7.266711 7.892412 7.483522 8.023671 12.548351   100   b

``` r
microbenchmark(
    ndjson={ ndjson::stream_in(gzf) },
  jsonlite={ jsonlite::stream_in(gzfile(gzf), flatten=TRUE, verbose=FALSE) }
)
```

    ## Unit: milliseconds
    ##      expr      min       lq     mean   median       uq      max neval cld
    ##    ndjson 2.127702 2.243182 2.435168 2.311043 2.439949 4.424222   100  a 
    ##  jsonlite 6.119968 6.378245 6.784871 6.507773 6.888627 9.692935   100   b

### Test Results

``` r
library(ndjson)
library(testthat)

date()
```

    ## [1] "Fri Aug 26 23:01:36 2016"

``` r
test_dir("tests/")
```

    ## testthat results ========================================================================================================
    ## OK: 0 SKIPPED: 0 FAILED: 0
    ## 
    ## DONE ===================================================================================================================

Please note that this project is released with a [Contributor Code of Conduct](CONDUCT.md). By participating in this project you agree to abide by its terms.
