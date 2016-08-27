context("basic functionality")
test_that("we can do something", {

  f <- system.file("extdata", "test.json", package="ndjson")
  expect_that(validate(f), equals(TRUE))
  expect_that(nrow(stream_in(f)), equals(100))

  gzf <- system.file("extdata", "testgz.json.gz", package="ndjson")
  expect_that(validate(gzf), equals(TRUE))
  expect_that(nrow(stream_in(gzf)), equals(100))

})
