// $Id: continue_node.h,v 1.2 2016/03/17 19:24:28 ist179027 Exp $
#ifndef __ZU_CONTINUE_NODE_H__
#define __ZU_CONTINUE_NODE_H__

#include <cdk/ast/expression_node.h>

namespace zu {

  /**
   * Class for describing break node.
   */
  class continue_node: public cdk::basic_node {

  public:
    inline continue_node(int lineno) :
        cdk::basic_node(lineno) {
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_continue_node(this, level);
    }

  };

} // zu

#endif