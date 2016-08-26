
`ndjson` : Wicked-fast Streaming JSON ('ndjson') Reader

Rcpp/C++11 wrapper for <https://github.com/nlohmann/json>

The goal is to create a completely "flat" `data.frame`-like structure from ndjson records.

The following functions are implemented:

-   `stream_in`: Stream in ndjson from a file
-   `validate`: Validate JSON records in an ndjson file

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
tf <- tempfile()
sample_data <- readr::read_lines("http://httpbin.org/stream/100")
length(sample_data)
```

    ## [1] 100

``` r
readr::write_lines(sample_data, tf)

dplyr::glimpse(ndjson::stream_in(tf))
```

    ## Observations: 100
    ## Variables: 8
    ## $ args                    <int> NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA,...
    ## $ headers.Accept          <chr> "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*", "*/*",...
    ## $ headers.Accept-Encoding <chr> "gzip, deflate", "gzip, deflate", "gzip, deflate", "gzip, deflate", "gzip, deflate"...
    ## $ headers.Host            <chr> "httpbin.org", "httpbin.org", "httpbin.org", "httpbin.org", "httpbin.org", "httpbin...
    ## $ headers.User-Agent      <chr> "r/curl/jeroen", "r/curl/jeroen", "r/curl/jeroen", "r/curl/jeroen", "r/curl/jeroen"...
    ## $ id                      <dbl> 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 2...
    ## $ origin                  <chr> "50.252.233.22", "50.252.233.22", "50.252.233.22", "50.252.233.22", "50.252.233.22"...
    ## $ url                     <chr> "http://httpbin.org/stream/100", "http://httpbin.org/stream/100", "http://httpbin.o...

``` r
dplyr::glimpse(jsonlite::stream_in(file(tf), flatten=TRUE, verbose=FALSE))
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
  ndjson={ ndjson::stream_in(tf) },
  jsonlite={ jsonlite::stream_in(file(tf), flatten=TRUE, verbose=FALSE) }
)
```

    ## Unit: milliseconds
    ##      expr      min       lq     mean   median       uq       max neval cld
    ##    ndjson 2.456077 2.664881 2.782078 2.738882 2.830236  4.112322   100  a 
    ##  jsonlite 8.347527 8.633819 9.055792 8.797878 9.092505 13.744002   100   b

``` r
unlink(tf)
```

### Test Results

``` r
library(ndjson)
library(testthat)

date()
```

    ## [1] "Fri Aug 26 16:00:46 2016"

``` r
test_dir("tests/")
```

    ## testthat results ========================================================================================================
    ## OK: 0 SKIPPED: 0 FAILED: 0
    ## 
    ## DONE ===================================================================================================================

Please note that this project is released with a [Contributor Code of Conduct](CONDUCT.md). By participating in this project you agree to abide by its terms.
