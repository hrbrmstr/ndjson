#include <pthread.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cerrno>

#include "gzstream.h"
#include "json.h"
using json = nlohmann::json;

#include <Rcpp.h>

using namespace Rcpp;
using namespace std;

using std::ifstream;

bool ends_with(const std::string &str, const std::string &suffix) {
  return((str.size() >= suffix.size()) &&
         (str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0));
}

List gz_stream_in(const std::string &path) {

  R_xlen_t num_lines = 0;
  std::string line;

  igzstream in;
  in.open(path.c_str());
  while(std::getline(in, line)) ++num_lines;
  in.close();

  List container(num_lines);
  R_xlen_t k=0;

  igzstream in2;
  in2.open(path.c_str());

  while(std::getline(in2, line)) {

    try {

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

      container[k++] = lst;

    } catch(...) {
      Rcpp::warning("Parsing error on line " + std::to_string(k));
    }

  }

  in2.close();

  return(container);

}

// [[Rcpp::export]]
List flatten_int(CharacterVector lines) {

  R_xlen_t num_lines = lines.size();
  List container(num_lines);
  R_xlen_t j=0, k=0;

  while(j < num_lines) {

    std::string line = as<std::string>(lines[j]);

    try {

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

      container[k++] = lst;

    } catch(...) {
      Rcpp::warning("Parsing error on line " + std::to_string(j));
    }

    j++;

  }

  return(container);

}

List j_stream_in(const std::string &path) {

  R_xlen_t num_lines = 0;
  ifstream in(path);
  std::string line;
  while (std::getline(in, line)) ++num_lines;
  in.close();

  List container(num_lines);
  R_xlen_t k=0;

  in.open(path);

  while(getline(in, line)) {

    try {

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

      container[k++] = lst;

    } catch(...) {
      Rcpp::warning("Parsing error on line " + std::to_string(k));
    }

  }

  in.close();

  return(container);

}

// [[Rcpp::export]]
List stream_in_int(const std::string &path) {

  if (ends_with(path, ".gz")) {
    return(gz_stream_in(path));
  } else {
    return(j_stream_in(path));
  }

}

// [[Rcpp::export]]
bool validate_int(std::string path, bool verbose) {

  bool ok = true;
  std::string line;
  R_xlen_t j=0;

  if (ends_with(path, ".gz")) {
    igzstream in;
    in.open(path.c_str());
    while(std::getline(in, line)) {
      j++;
      try {
        json o = json::parse(line);
      } catch(...) {
        ok = false;
        if (verbose) Rcout << "  - invalid JSON record on line " << j << std::endl;
      }
    }
    in.close();
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
