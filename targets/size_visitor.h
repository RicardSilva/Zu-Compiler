// $Id: size_visitor.h,v 1.4 2016/05/19 01:22:39 ist179027 Exp $ -*- c++ -*-
#ifndef __ZU_SEMANTICS_SIZE_VISITOR_H__
#define __ZU_SEMANTICS_SIZE_VISITOR_H__

#include <string>
#include <iostream>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"
#include "ast/all.h"

namespace zu {

  //!
  //! Traverse syntax tree and generate the corresponding assembly code.
  //!
  class size_visitor: public basic_ast_visitor {
    size_t _size=0;

  public:
    size_visitor(std::shared_ptr<cdk::compiler> compiler) :
        basic_ast_visitor(compiler) {
    }

  public:
    ~size_visitor() {
      os().flush();
    }

    size_t size() {
      return _size;
    }
    
  public:
    void do_sequence_node(cdk::sequence_node * const node, int lvl) {
      for (size_t i = 0; i < node->size(); i++) {
	      node->node(i)->accept(this, lvl);
      }
    }

  public:
    void do_integer_node(cdk::integer_node * const node, int lvl) { }
    void do_double_node(cdk::double_node * const node, int lvl) { }
    void do_string_node(cdk::string_node * const node, int lvl) { }
    void do_identifier_node(cdk::identifier_node * const node, int lvl) { }

  public:
    void do_identity_node(zu::identity_node * const node, int lvl) { }
    void do_neg_node(cdk::neg_node * const node, int lvl) { }
    void do_not_node(zu::not_node * const node, int lvl) { }
    void do_address_node(zu::address_node * const node, int lvl) { }
    void do_malloc_node(zu::malloc_node * const node, int lvl) {
      // FIXME 
    }

  public:
    void do_add_node(cdk::add_node * const node, int lvl) { }
    void do_sub_node(cdk::sub_node * const node, int lvl) { }
    void do_mul_node(cdk::mul_node * const node, int lvl) { }
    void do_div_node(cdk::div_node * const node, int lvl) { }
    void do_mod_node(cdk::mod_node * const node, int lvl) { }
    void do_lt_node(cdk::lt_node * const node, int lvl) { }
    void do_le_node(cdk::le_node * const node, int lvl) { }
    void do_ge_node(cdk::ge_node * const node, int lvl) { }
    void do_gt_node(cdk::gt_node * const node, int lvl) { }
    void do_ne_node(cdk::ne_node * const node, int lvl) { }
    void do_eq_node(cdk::eq_node * const node, int lvl) { }
    void do_and_node(zu::and_node * const node, int lvl) { }
    void do_or_node(zu::or_node * const node, int lvl) { }

  public:
    void do_rvalue_node(zu::rvalue_node * const node, int lvl) { }

    void do_variable_node(zu::variable_node * const node, int lvl) { }
    void do_index_node(zu::index_node * const node, int lvl) { }

  public:
    void do_fundecl_node(zu::fundecl_node * const node, int lvl) { }
    void do_fundef_node(zu::fundef_node * const node, int lvl) { 
      node->body()->accept(this, lvl);
    }
    void do_funcall_node(zu::funcall_node * const node, int lvl) { }
    void do_vardecl_node(zu::vardecl_node * const node, int lvl) {
      _size += node->type()->size();
    }
    void do_vardef_node(zu::vardef_node * const node, int lvl) {
      _size += node->type()->size();
    }

  public:
    void do_evaluation_node(zu::evaluation_node * const node, int lvl) { }
    void do_print_node(zu::print_node * const node, int lvl) { }
    void do_read_node(zu::read_node * const node, int lvl) { }
    void do_assignment_node(zu::assignment_node * const node, int lvl) { }

  public:

    void do_for_node(zu::for_node * const node, int lvl) {
      if (node->init())
        node->init()->accept(this, lvl);
      node->block()->accept(this, lvl);
    }
    void do_if_node(zu::if_node * const node, int lvl) {
      node->block()->accept(this, lvl);
    }
    void do_if_else_node(zu::if_else_node * const node, int lvl) {
      node->thenblock()->accept(this, lvl);
      node->elseblock()->accept(this, lvl);
    }
    void do_break_node(zu::break_node * const node, int lvl) { }
    void do_continue_node(zu::continue_node * const node, int lvl) { }
    void do_return_node(zu::return_node * const node, int lvl) { }
    void do_block_node(zu::block_node * const node, int lvl) {
      if (node->declarations())
        node->declarations()->accept(this, lvl);
      if (node->instructions())
        node->instructions()->accept(this, lvl);
    }

  };

} // zu

#endif
