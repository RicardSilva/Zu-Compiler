// $Id: malloc_node.h,v 1.5 2016/04/13 18:40:26 ist178414 Exp $ -*- c++ -*-
#ifndef __ZU_MALLOC_NODE_H__
#define __ZU_MALLOC_NODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing memory allocation nodes
   */
  class malloc_node: public cdk::expression_node {
    cdk::expression_node *_counter;

  public:
   
    inline malloc_node(int lineno, cdk::expression_node *counter) :
        cdk::expression_node(lineno), _counter(counter) {
    }

    inline cdk::expression_node *counter() {
      return _counter;
    }
   

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_malloc_node(this, level);
    }

  };

} // zu

#endif
