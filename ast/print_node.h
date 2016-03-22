// $Id: print_node.h,v 1.3 2016/03/17 19:24:28 ist179027 Exp $ -*- c++ -*-
#ifndef __ZU_PRINT_NODE_H__
#define __ZU_PRINT_NODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing print nodes.
   */
  class print_node: public cdk::basic_node {
    cdk::expression_node *_argument;
    bool _println;

  public:
    inline print_node(int lineno, cdk::expression_node *argument, bool println) :
        cdk::basic_node(lineno), _argument(argument), _println(println) {
    }

  public:
    inline cdk::expression_node *argument() {
      return _argument;
    }

    inline const bool println() const {
    	return _println;
    }
    
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_print_node(this, level);
    }

  };

} // zu

#endif
