#' Stream in & flatten an ndjson file into a \code{tbl_dt}
#'
#' Given a file of streaming JSON (ndjson) this function reads in the records
#' and creates a flat \code{data.table} / \code{tbl_dt} from it.
#'
#' @param path path to file
#' @return \code{data.frame}
#' @export
stream_in <- function(path) {
  tmp <- .Call('ndjson_internal_stream_in', path.expand(path), PACKAGE='ndjson')
  dtplyr::tbl_dt(data.table::rbindlist(tmp, fill=TRUE))
}


#' Validate ndjson file
#'
#' Given a file of streaming JSON (ndjson) this function reads in the records
#' and validates that they are all legal JSON records
#'
#' @param path path to file
#' @param verbose display verbose information (filename and line numbers with bad records)
#' @return logical
#' @export
validate <- function(path, verbose=FALSE) {
  .Call('ndjson_internal_validate', path.expand(path), verbose, PACKAGE='ndjson')
}

