// $Id: not_node.h,v 1.2 2016/03/17 19:30:16 ist179027 Exp $ -*- c++ -*-
#ifndef __ZU_NOT_NODE_H__
#define __ZU_NOT_NODE_H__

#include <cdk/ast/unary_expression_node.h>

namespace zu {

  /**
   * Class for describing the logic not ('~') operator
   */
  class not_node: public cdk::unary_expression_node {
  public:
    inline not_node(int lineno, cdk::expression_node *arg) :
        cdk::unary_expression_node(lineno, arg) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_not_node(this, level);
    }

  };

} // zu

#endif
