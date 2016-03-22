// $Id: index_node.h,v 1.4 2016/03/17 19:30:15 ist179027 Exp $
#ifndef __ZU_INDEX_NODE_H__
#define __ZU_INDEX_NODE_H__

#include "ast/lvalue_node.h"

namespace zu {

  /**
   * Class for describing syntactic tree leaves for holding indexes.
   */
  class index_node: public zu::lvalue_node {
    cdk::expression_node *_address;
    cdk::expression_node *_index;

  public:
    inline index_node(int lineno, expression_node *address, expression_node *index) :
        zu::lvalue_node(lineno), _address(address), _index(index) {}
        
    inline cdk::expression_node *address() {
      return _address;
    }
    inline cdk::expression_node *index() {
      return _index;
    }
    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) {
      sp->do_index_node(this, level);
    }

  };

} // zu

#endif
