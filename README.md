
`ndjson` : Wicked-fast Streaming JSON ('ndjson') Reader

Rcpp/C++11 wrapper for <https://github.com/nlohmann/json>

The goal is to create a completely "flat" `data.frame`-like structure from ndjson records.

The following functions are implemented:

-   `stream_in`: Stream in JSON from a character vector
-   `stream_in_file`: Stream in JSON from a file

### Installation

``` r
devtools::install_github("hrbrmstr/ndjson")
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
sample_data <- readr::read_lines("http://httpbin.org/stream/100")
length(sample_data)
```

    ## [1] 100

``` r
dplyr::glimpse(ndjson::stream_in(sample_data))
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
dplyr::glimpse(jsonlite::stream_in(textConnection(sample_data), flatten=TRUE, verbose=FALSE))
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
  ndjson={ ndjson::stream_in(sample_data) },
  jsonlite={ jsonlite::stream_in(textConnection(sample_data), flatten=TRUE, verbose=FALSE) }
)
```

    ## Unit: milliseconds
    ##      expr      min       lq     mean   median       uq      max neval cld
    ##    ndjson 2.164029 2.260217 2.353497 2.309950 2.361279 3.637044   100  a 
    ##  jsonlite 6.690733 6.859965 7.200450 6.977782 7.117655 9.895136   100   b

### Test Results

``` r
library(ndjson)
library(testthat)

date()
```

    ## [1] "Thu Aug 25 17:49:56 2016"

``` r
test_dir("tests/")
```

    ## testthat results ========================================================================================================
    ## OK: 0 SKIPPED: 0 FAILED: 0
    ## 
    ## DONE ===================================================================================================================
