// $Id: lvalue_node.h,v 1.4 2016/04/11 21:25:07 ist179027 Exp $
#ifndef __ZU_LVALUE_NODE_H__
#define __ZU_LVALUE_NODE_H__

#include <cdk/ast/simple_value_node.h>
#include <string>

namespace zu {

  /**
   * Class for describing syntactic tree leaves for holding lvalues.
   */
  class lvalue_node: public cdk::expression_node {
  public:
    inline lvalue_node(int lineno): cdk::expression_node(lineno) {}

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) = 0;

  };

} // zu

#endif
