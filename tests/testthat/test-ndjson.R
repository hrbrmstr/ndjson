context("basic functionality")
test_that("we can do something", {

  f <- system.file("extdata", "test.json", package="ndjson")
  expect_that(validate(f), equals(TRUE))
  expect_that(nrow(stream_in(f)), equals(100))
  expect_that(stream_in(f), is_a("tbl_dt"))
  expect_that(stream_in(f, "tbl"), is_a("tbl_df"))

  gzf <- system.file("extdata", "testgz.json.gz", package="ndjson")
  expect_that(validate(gzf), equals(TRUE))
  expect_that(nrow(stream_in(gzf)), equals(100))
  expect_that(stream_in(gzf), is_a("tbl_dt"))
  expect_that(stream_in(gzf, "tbl"), is_a("tbl_df"))

})
