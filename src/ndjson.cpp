#include <Rcpp.h>
using namespace Rcpp;

#include "json.hpp"
using json = nlohmann::json;

// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]
List internal_stream_in(std::vector < std::string > lines) {

  List container(lines.size());

  for (R_xlen_t j=0; j<lines.size(); j++) {

    json o = json::parse(lines[j]).flatten();

    List lst(o.size());
    CharacterVector lst_nms(o.size());

    double d_val;
    std::string s_val;
    bool b_val;

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

    container[j] = lst;

  }

  return(container);

}
