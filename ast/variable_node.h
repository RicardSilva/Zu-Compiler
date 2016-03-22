// $Id: variable_node.h,v 1.3 2016/03/16 23:30:11 ist179027 Exp $
#ifndef __ZU_VARIABLE_NODE_H__
#define __ZU_VARIABLE_NODE_H__

#include "ast/lvalue_node.h"
#include <cdk/basic_type.h>
#include <string>

namespace zu {

  /**
   * Class for describing syntactic tree leaves for holding variables.
   */
  class variable_node: public zu::lvalue_node {
    basic_type *_type;
    std::string _id;

  public:
    inline variable_node(int lineno, basic_type *type, const std::string &id) :
        zu::lvalue_node(lineno), _type(type), _id(id) {
    }

    basic_type *type() {
      return _type;
    }
    void type(basic_type *type) {
      _type = type;
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
