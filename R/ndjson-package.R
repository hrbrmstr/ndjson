#' Wicked-fast Streaming JSON ('ndjson) Reader
#'
#' Streaming 'JSON' ('ndjson') has one 'JSON' record per-line
#' and many modern 'ndjson' files contain large numbers of records.
#' These constructs may not be columnar in nature, but it is often
#' useful to read in these files and "flatten" the structure out to
#' enable working with the data in an R 'data.frame'-like context.
#' Functions are provided that make it possible to read in plain
#' ndjson' files or compressed ('gz') 'ndjson' files and either
#' validate the format of the records or create "flat" 'data.table'
#' structures from them.
#'
#' @name ndjson
#' @docType package
#' @author Bob Rudis (bob@@rud.is)
#' @useDynLib ndjson, .registration=TRUE
#' @importFrom Rcpp sourceCpp
NULL
