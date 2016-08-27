#' Wicked-fast Streaming JSON ('ndjson) Reader
#'
#' @name ndjson
#' @docType package
#' @author Bob Rudis (@@hrbrmstr)
#' @import purrr
#' @useDynLib ndjson
#' @import Rcpp11
#' @import BH
#' @importFrom Rcpp sourceCpp
#' @importFrom stringi stri_read_lines stri_enc_toutf8
#' @importFrom data.table rbindlist
#' @importFrom dtplyr tbl_dt
NULL
