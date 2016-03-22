// $Id: malloc_node.h,v 1.3 2016/03/17 19:30:16 ist179027 Exp $ -*- c++ -*-
#ifndef __ZU_MALLOC_NODE_H__
#define __ZU_MALLOC_NODE_H__

#include <cdk/ast/basic_node.h>

namespace zu {

  /**
   * Class for describing memory allocation nodes
   */
  class malloc_node: public cdk::basic_node {
    cdk::integer_node *_counter;

  public:
   
    inline malloc_node(int lineno, cdk::integer_node *counter) :
        cdk::basic_node(lineno), _counter(counter) {
    }

    inline cdk::integer_node *counter() {
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