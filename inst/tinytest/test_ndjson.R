library(ndjson)

f <- system.file("extdata", "test.json", package="ndjson")
expect_true(validate(f))
expect_equal(nrow(stream_in(f)), 100)
expect_true(inherits(stream_in(f), "data.table"))
expect_true(inherits(stream_in(f, "tbl"), "tbl_df"))

gzf <- system.file("extdata", "testgz.json.gz", package="ndjson")
expect_true(validate(gzf))
expect_equal(nrow(stream_in(gzf)), 100)
expect_true(inherits(stream_in(gzf), "data.table"))
expect_true(inherits(stream_in(gzf, "tbl"), "tbl_df"))
