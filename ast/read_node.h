// $Id: read_node.h,v 1.3 2016/03/30 14:56:31 ist178414 Exp $ -*- c++ -*-
#ifndef __ZU_READ_NODE_H__
#define __ZU_READ_NODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing read nodes.
   */
  class read_node: public cdk::expression_node {

  public:
    inline read_node(int lineno) :
        cdk::expression_node(lineno) {}

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_read_node(this, level);
    }

  };

} // zu

#endif
