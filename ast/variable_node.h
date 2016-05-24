// $Id: variable_node.h,v 1.6 2016/04/15 12:34:15 ist178414 Exp $
#ifndef __ZU_VARIABLE_NODE_H__
#define __ZU_VARIABLE_NODE_H__

#include "ast/lvalue_node.h"
#include <string>

namespace zu {

  /**
   * Class for describing syntactic tree leaves for holding variables.
   */
  class variable_node: public zu::lvalue_node {
    std::string _id;

  public:
    inline variable_node(int lineno, std::string *id) :
        zu::lvalue_node(lineno), _id(*id) {
    }

    const std::string &id() {
      return _id;
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) {
      sp->do_variable_node(this, level);
    }

  };

} // zu

#endif
