#' Stream in JSON from a file
#'
#' Given a file of streaming JSON (ndjson) this function uses \code{stringi::stri_read_lines()}
#' to read the data in quickly and create a flat \code{data.table} / \code{tbl_dt}
#' from it.
#'
#' @param x path
#' @export
stream_in_file <- function(x) {
  tmp <- .Call('ndjson_internal_stream_in', stringi::stri_read_lines(x), PACKAGE = 'ndjson' )
  dtplyr::tbl_dt(data.table::rbindlist(tmp, fill=TRUE))
}

#' Stream in JSON from a character vector
#'
#' Given a character vector of streaming JSON (ndjson) this function will
#' create a flat \code{data.table} / \code{tbl_dt} from it.
#'
#' @param x character vector
#' @export
stream_in <- function(x) {
  tmp <- .Call('ndjson_internal_stream_in', x, PACKAGE = 'ndjson')
  dtplyr::tbl_dt(data.table::rbindlist(tmp, fill=TRUE))
}