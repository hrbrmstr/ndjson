#' Stream in & flatten an ndjson file into a \code{data.table}
#'
#' Given a file of streaming JSON (ndjson) this function reads in the records
#' and creates a flat \code{data.table} / \code{tbl} from it.
#'
#' @md
#' @param path path to file (supports "\code{gz}" files)
#' @param cls the package uses \code{data.table::rbindlist} for speed but
#'        that's not always the best return type for everyone, so you have
#'        option of keeping it a `data.table` or converting it to a `tbl`
#' @return \code{data.table} or \code{tbl}
#' @export
#' @references \url{http://ndjson.org/}
#' @examples
#' f <- system.file("extdata", "test.json", package="ndjson")
#' nrow(stream_in(f))
#'
#' gzf <- system.file("extdata", "testgz.json.gz", package="ndjson")
#' nrow(stream_in(gzf))
stream_in <- function(path, cls = c("dt", "tbl")) {
  cls <- match.arg(cls, c("dt", "tbl"))
  tmp <- stream_in_int(path.expand(path))
  tmp <- data.table::rbindlist(tmp, fill=TRUE)
  if (cls == "tbl") tibble::as_tibble(tmp) else tmp
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
  validate_int(path.expand(path), verbose)
}

#' Flatten a character vector of individual JSON lines into a \code{data.table}
#'
#' @md
#' @param x character vector of individual JSON lines to flatten
#' @param cls the package uses \code{data.table::rbindlist} for speed but
#'        that's not always the best return type for everyone, so you have
#'        option of keeping it a `data.table` or converting it to a `tbl`
#' @return \code{data.table} or \code{tbl}
#' @export
#' @examples
#' flatten('{"top":{"next":{"final":1,"end":true},"another":"yes"},"more":"no"}')
flatten <- function(x, cls = c("dt", "tbl")) {
  cls <- match.arg(cls, c("dt", "tbl"))
  tmp <- flatten_int(x)
  tmp <- data.table::rbindlist(tmp, fill=TRUE)
  if (cls == "tbl") tibble::as_tibble(tmp) else tmp
}
