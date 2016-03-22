// $Id: return_node.h,v 1.3 2016/03/17 19:24:28 ist179027 Exp $
#ifndef __ZU_RETURN_NODE_H__
#define __ZU_RETURN_NODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing return node.
   */
  class return_node: public cdk::basic_node {

  public:
    inline return_node(int lineno) :
        cdk::basic_node(lineno) {
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_return_node(this, level);
    }

  };

} // zu

#endif