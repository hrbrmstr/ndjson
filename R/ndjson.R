#' Stream in & flatten an ndjson file into a \code{tbl_dt}
#'
#' Given a file of streaming JSON (ndjson) this function reads in the records
#' and creates a flat \code{data.table} / \code{tbl_dt} from it.
#'
#' @param path path to file (supports "\code{gz}" files)
#' @return \code{tbl_dt}
#' @export
#' @references \url{http://ndjson.org/}
#' @examples
#' f <- system.file("extdata", "test.json", package="ndjson")
#' nrow(stream_in(f))
#'
#' gzf <- system.file("extdata", "testgz.json.gz", package="ndjson")
#' nrow(stream_in(gzf))
stream_in <- function(path) {
  tmp <- .Call('ndjson_internal_stream_in', path.expand(path), PACKAGE='ndjson')
  dtplyr::tbl_dt(data.table::rbindlist(tmp, fill=TRUE))
}

#' Validate ndjson file
#'
#' Given a file of streaming JSON (ndjson) this function reads in the records
#' and validates that they are all legal JSON records. If the \code{verbose}
#' parameter is \code{TRUE} and errors are found, the line numbers of the
#' errant records will be displayed.
#'
#' @param path path to file (supports "\code{gz}" files)
#' @param verbose display verbose information (filename and line numbers with bad records)
#' @return logical
#' @export
#' @references \url{http://ndjson.org/}
#' @examples
#' f <- system.file("extdata", "test.json", package="ndjson")
#' validate(f)
#'
#' gzf <- system.file("extdata", "testgz.json.gz", package="ndjson")
#' validate(gzf)
validate <- function(path, verbose=FALSE) {
  .Call('ndjson_internal_validate', path.expand(path), verbose, PACKAGE='ndjson')
}

#' Flatten a character vector of individual JSON lines into a \code{tbl_dt}
#'
#' @param x character vector of individual JSON lines to flatten
#' @return \code{tbl_dt}
#' @export
#' @examples
#' flatten('{"top":{"next":{"final":1,"end":true},"another":"yes"},"more":"no"}')
flatten <- function(x) {
  tmp <- .Call('ndjson_internal_flatten', x, PACKAGE='ndjson')
  dtplyr::tbl_dt(data.table::rbindlist(tmp, fill=TRUE))
}
