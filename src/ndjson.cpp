// [[Rcpp::depends(BH)]]

#include <Rcpp.h>
using namespace Rcpp;

#include <fstream>
#include <iostream>
using std::ifstream;

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include "json.hpp"
using json = nlohmann::json;

// [[Rcpp::plugins(cpp11)]]

bool ends_with(const std::string &str, const std::string &suffix) {
  return((str.size() >= suffix.size()) &&
         (str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0));
}

List gz_stream_in(const std::string &path) {

  R_xlen_t num_lines = 0;
  std::string line;

  std::ifstream file(path, std::ios_base::in | std::ios_base::binary);
  boost::iostreams::filtering_streambuf<boost::iostreams::input> inbuf;
  inbuf.push(boost::iostreams::gzip_decompressor());
  inbuf.push(file);
  std::istream instream(&inbuf);

  while(std::getline(instream, line)) ++num_lines;
  file.close();

  List container(num_lines);
  R_xlen_t j=0;

  std::ifstream file2(path, std::ios_base::in | std::ios_base::binary);
  boost::iostreams::filtering_streambuf<boost::iostreams::input> inbuf2;
  inbuf2.push(boost::iostreams::gzip_decompressor());
  inbuf2.push(file2);
  std::istream instream2(&inbuf2);

  while(getline(instream2, line)) {

    json o = json::parse(line).flatten();

    List lst(o.size());
    CharacterVector lst_nms(o.size());

    double      d_val;
    std::string s_val;
    bool        b_val;

    R_xlen_t i=0;
    for (json::iterator it = o.begin(); it != o.end(); ++it) {

      std::string key = it.key();
      std::replace(key.begin(), key.end(), '/', '.');
      key.erase(0, 1);

      lst_nms[i] = key;

      if (it.value().is_number()) {
        d_val = it.value();
        lst[i] = d_val;
      } else if (it.value().is_boolean()) {
        b_val = it.value();
        lst[i] = b_val;
      } else if (it.value().is_string()) {
        s_val = it.value();
        lst[i] = s_val;
      } else if (it.value().is_null()) {
        lst[i] = NA_LOGICAL;
      }

      i += 1;

    }

    lst.attr("names") = lst_nms;
    lst.attr("class") = "data.frame";
    lst.attr("row.names") = 1;

    container[j++] = lst;

  }

  file2.close();

  return(container);

}

List j_stream_in(const std::string &path) {

  R_xlen_t num_lines = 0;
  ifstream in(path);
  std::string line;
  while (std::getline(in, line)) ++num_lines;
  in.close();

  List container(num_lines);
  R_xlen_t j=0;

  in.open(path);

  while(getline(in, line)) {

    json o = json::parse(line).flatten();

    List lst(o.size());
    CharacterVector lst_nms(o.size());

    double      d_val;
    std::string s_val;
    bool        b_val;

    R_xlen_t i=0;
    for (json::iterator it = o.begin(); it != o.end(); ++it) {

      std::string key = it.key();
      std::replace(key.begin(), key.end(), '/', '.');
      key.erase(0, 1);

      lst_nms[i] = key;

      if (it.value().is_number()) {
        d_val = it.value();
        lst[i] = d_val;
      } else if (it.value().is_boolean()) {
        b_val = it.value();
        lst[i] = b_val;
      } else if (it.value().is_string()) {
        s_val = it.value();
        lst[i] = s_val;
      } else if (it.value().is_null()) {
        lst[i] = NA_LOGICAL;
      }

      i += 1;

    }

    lst.attr("names") = lst_nms;
    lst.attr("class") = "data.frame";
    lst.attr("row.names") = 1;

    container[j++] = lst;

  }

  in.close();

  return(container);

}

// [[Rcpp::export]]
List internal_stream_in(const std::string &path) {

  if (ends_with(path, ".gz")) {
    return(gz_stream_in(path));
  } else {
    return(j_stream_in(path));
  }

}
// [[Rcpp::export]]
bool internal_validate(std::string path, bool verbose) {

  bool ok = true;
  std::string line;
  R_xlen_t j=0;

  if (ends_with(path, ".gz")) {

    std::ifstream file(path, std::ios_base::in | std::ios_base::binary);
    boost::iostreams::filtering_streambuf<boost::iostreams::input> inbuf;
    inbuf.push(boost::iostreams::gzip_decompressor());
    inbuf.push(file);
    std::istream instream(&inbuf);

    while(std::getline(instream, line)) {

      j++;

      try {
        json o = json::parse(line);
      } catch(...) {
        ok = false;
        if (verbose) Rcout << "  - invalid JSON record on line " << j << std::endl;
      }

    }

    file.close();

  } else {

    ifstream f(path);

    if (verbose) Rcout << "File: " << path << std::endl;

    while(getline(f, line)) {

      j++;

      try {
        json o = json::parse(line);
      } catch(...) {
        ok = false;
        if (verbose) Rcout << "  - invalid JSON record on line " << j << std::endl;
      }

    }

    f.close();

  }

  return(ok);

}
