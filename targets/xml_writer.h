// $Id: xml_writer.h,v 1.19 2016/04/14 22:03:13 ist179027 Exp $ -*- c++ -*-
#ifndef __ZU_SEMANTICS_XMLWRITER_H__
#define __ZU_SEMANTICS_XMLWRITER_H__

#include <string>
#include <iostream>
#include <cdk/ast/basic_node.h>
#include <cdk/symbol_table.h>
#include <cdk/basic_type.h>
#include "targets/basic_ast_visitor.h"
#include "targets/symbol.h"

namespace zu {

  /**
   * Print nodes as XML elements to the output stream.
   */
  class xml_writer: public basic_ast_visitor {
    cdk::symbol_table<zu::symbol> &_symtab;

  public:
    xml_writer(std::shared_ptr<cdk::compiler> compiler, cdk::symbol_table<zu::symbol> &symtab) :
        basic_ast_visitor(compiler), _symtab(symtab) {
    }

  public:
    ~xml_writer() {
      os().flush();
    }

  private:
    inline void openTag(const std::string &tag, int lvl) {
      os() << std::string(lvl, ' ') + "<" + tag + ">" << std::endl;
    }
    inline void openTag(const cdk::basic_node *node, int lvl) {
      openTag(node->name(), lvl);
    }
    inline void closeTag(const std::string &tag, int lvl) {
      os() << std::string(lvl, ' ') + "</" + tag + ">" << std::endl;
    }
    inline void closeTag(const cdk::basic_node *node, int lvl) {
      closeTag(node->name(), lvl);
    }

  public:
    void do_sequence_node(cdk::sequence_node * const node, int lvl);

  protected:
    template<typename T>
    void processSimple(cdk::simple_value_node<T> * const node, int lvl) {
      os() << std::string(lvl, ' ') << "<" << node->name() << ">" << node->value() << "</" << node->name() << ">" << std::endl;
    }

    void processExpr(cdk::basic_node * const node, int lvl) {
      os() << std::string(lvl, ' ') << "<" << node->name() << "/>" << std::endl;
    }

    void processBool(bool value, const std::string &name, int lvl) {
      if (value)
        os() << std::string(lvl, ' ') << "<" << name << "/>" << std::endl;
    }

    void processName(const std::string &name, int lvl) {
      os() << std::string(lvl, ' ') << "<name>" << name << "</name>" << std::endl;
    }

    void processType(basic_type *t, int lvl) {
      os() << std::string(lvl, ' ') << "<type>" << getName(t) << "</type>" << std::endl;
    }

    const std::string getName(basic_type *t) const {
      switch(t->name()) {
        case basic_type::TYPE_VOID:
          return "void";
        case basic_type::TYPE_INT:
          return "int";
        case basic_type::TYPE_STRING:
          return "string";
        case basic_type::TYPE_DOUBLE:
          return "double";
        case basic_type::TYPE_POINTER:
          return getName(t->subtype())+'*';
        default:
          return "ERROR";
      }
    }

  public:
    void do_integer_node(cdk::integer_node * const node, int lvl);
    void do_double_node(cdk::double_node * const node, int lvl);
    void do_string_node(cdk::string_node * const node, int lvl);
    void do_identifier_node(cdk::identifier_node * const node, int lvl);

  protected:
    void processUnaryExpression(cdk::unary_expression_node * const node, int lvl);

  public:
    void do_identity_node(zu::identity_node * const node, int lvl);
    void do_neg_node(cdk::neg_node * const node, int lvl);
    void do_not_node(zu::not_node * const node, int lvl);
    void do_address_node(zu::address_node * const node, int lvl);
    void do_malloc_node(zu::malloc_node * const node, int lvl);

  protected:
    void processBinaryExpression(cdk::binary_expression_node * const node, int lvl);

  public:
    void do_add_node(cdk::add_node * const node, int lvl);
    void do_sub_node(cdk::sub_node * const node, int lvl);
    void do_mul_node(cdk::mul_node * const node, int lvl);
    void do_div_node(cdk::div_node * const node, int lvl);
    void do_mod_node(cdk::mod_node * const node, int lvl);
    void do_lt_node(cdk::lt_node * const node, int lvl);
    void do_le_node(cdk::le_node * const node, int lvl);
    void do_ge_node(cdk::ge_node * const node, int lvl);
    void do_gt_node(cdk::gt_node * const node, int lvl);
    void do_ne_node(cdk::ne_node * const node, int lvl);
    void do_eq_node(cdk::eq_node * const node, int lvl);
    void do_and_node(zu::and_node * const node, int lvl);
    void do_or_node(zu::or_node * const node, int lvl);

  public:
    void do_rvalue_node(zu::rvalue_node * const node, int lvl);

    void do_variable_node(zu::variable_node * const node, int lvl);
    void do_index_node(zu::index_node * const node, int lvl);

  public:
    void do_fundecl_node(zu::fundecl_node * const node, int lvl);
    void do_fundef_node(zu::fundef_node * const node, int lvl);
    void do_funcall_node(zu::funcall_node * const node, int lvl);
    void do_vardecl_node(zu::vardecl_node * const node, int lvl);
    void do_vardef_node(zu::vardef_node * const node, int lvl);

  public:
    void do_evaluation_node(zu::evaluation_node * const node, int lvl);
    void do_print_node(zu::print_node * const node, int lvl);
    void do_read_node(zu::read_node * const node, int lvl);
    void do_assignment_node(zu::assignment_node * const node, int lvl);

  public:

    void do_for_node(zu::for_node * const node, int lvl);
    void do_if_node(zu::if_node * const node, int lvl);
    void do_if_else_node(zu::if_else_node * const node, int lvl);
    void do_break_node(zu::break_node * const node, int lvl);
    void do_continue_node(zu::continue_node * const node, int lvl);
    void do_return_node(zu::return_node * const node, int lvl);
    void do_block_node(zu::block_node * const node, int lvl);

  };

} // zu

#endif
