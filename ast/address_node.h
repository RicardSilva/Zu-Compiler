// $Id: address_node.h,v 1.3 2016/05/19 17:48:40 ist179027 Exp $ -*- c++ -*-
#ifndef __ZU_ADDRESS_NODE_H__
#define __ZU_ADDRESS_NODE_H__

#include "ast/lvalue_node.h"

namespace zu {

  /**
   * Class for describing the address operator
   */
  class address_node: public cdk::expression_node {
	zu::lvalue_node *_arg;  
	public:
    inline address_node(int lineno, zu::lvalue_node *arg) :
        cdk::expression_node(lineno), _arg(arg) {
    }

		zu::lvalue_node * arg() {
			return _arg;
		}

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_address_node(this, level);
    }

  };

} // zu

#endif
