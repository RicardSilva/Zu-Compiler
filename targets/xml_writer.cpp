// $Id: xml_writer.cpp,v 1.26 2016/05/15 16:04:11 ist179027 Exp $ -*- c++ -*-
#include <string>
#include "targets/xml_writer.h"
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

//---------------------------------------------------------------------------

void zu::xml_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<sequence_node size='" << node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++)
    node->node(i)->accept(this, lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  processSimple(node, lvl);
}

void zu::xml_writer::do_double_node(cdk::double_node * const node, int lvl) {
  processSimple(node, lvl);
}

void zu::xml_writer::do_string_node(cdk::string_node * const node, int lvl) {
  processSimple(node, lvl);
}

void zu::xml_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  processSimple(node, lvl);
}

//---------------------------------------------------------------------------

inline void zu::xml_writer::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void zu::xml_writer::do_identity_node(zu::identity_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

void zu::xml_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

void zu::xml_writer::do_not_node(zu::not_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

void zu::xml_writer::do_address_node(zu::address_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->arg()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void zu::xml_writer::do_malloc_node(zu::malloc_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
	openTag("size", lvl + 2);
	node->counter()->accept(this, lvl + 4);
	closeTag("size", lvl + 2);
	closeTag(node, lvl);
}

//---------------------------------------------------------------------------

inline void zu::xml_writer::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void zu::xml_writer::do_add_node(cdk::add_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_and_node(zu::and_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_or_node(zu::or_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_rvalue_node(zu::rvalue_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_variable_node(zu::variable_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  processName(node->id(), lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_index_node(zu::index_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);

  openTag("address", lvl + 2);
  node->address()->accept(this, lvl + 4);
  closeTag("address", lvl + 2);

  openTag("index", lvl + 2);
  node->index()->accept(this, lvl + 4);
  closeTag("index", lvl + 2);

  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_fundecl_node(zu::fundecl_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);

  processType(node->type(), lvl + 2);
  processName(node->id(), lvl + 2);
  processBool(node->ispublic(), "public", lvl + 2);
  processBool(node->isextern(), "extern", lvl + 2);
	

	openTag("arguments", lvl + 2);
	node->args()->accept(this, lvl + 4);
	closeTag("arguments", lvl + 2);

  closeTag(node, lvl);

}

//---------------------------------------------------------------------------

void zu::xml_writer::do_fundef_node(zu::fundef_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);

  processType(node->type(), lvl + 2);
  processName(node->id(), lvl + 2);
  processBool(node->ispublic(), "public", lvl + 2);
  processBool(node->isextern(), "extern", lvl + 2);

	openTag("arguments", lvl + 2);
	node->args()->accept(this, lvl + 4);
	closeTag("arguments", lvl + 2);

  if (node->retval() != nullptr) {
    openTag("default_value", lvl + 2);
    node->retval()->accept(this, lvl + 4);
    closeTag("default_value", lvl + 2);
  }

  openTag("body", lvl + 2);
  node->body()->accept(this, lvl + 4);
  closeTag("body", lvl + 2);

  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_funcall_node(zu::funcall_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);

  processName(node->id(), lvl + 2);

	openTag("arguments", lvl + 2);
	node->args()->accept(this, lvl + 4);
	closeTag("arguments", lvl + 2);

  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_vardecl_node(zu::vardecl_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);

  processType(node->type(), lvl + 2);
  processName(node->id(), lvl + 2);
  processBool(node->ispublic(), "public", lvl + 2);
  processBool(node->isextern(), "extern", lvl + 2);

  closeTag(node, lvl);

}

//---------------------------------------------------------------------------

void zu::xml_writer::do_vardef_node(zu::vardef_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);

  processType(node->type(), lvl + 2);
  processName(node->id(), lvl + 2);
  processBool(node->ispublic(), "public", lvl + 2);
  processBool(node->isextern(), "extern", lvl + 2);

  openTag("value", lvl + 2);
  node->value()->accept(this, lvl + 4);
  closeTag("value", lvl + 2);

  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_assignment_node(zu::assignment_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 2);
  openTag("rvalue", lvl + 2);
  node->rvalue()->accept(this, lvl + 4);
  closeTag("rvalue", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

// void zu::xml_writer::do_program_node(zu::program_node * const node, int lvl) {
//   openTag(node, lvl);
//   node->statements()->accept(this, lvl + 4);
//   closeTag(node, lvl);
// }

//---------------------------------------------------------------------------

void zu::xml_writer::do_evaluation_node(zu::evaluation_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void zu::xml_writer::do_print_node(zu::print_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  processBool(node->println(), "newline", lvl+2);
  closeTag(node, lvl);
  
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_read_node(zu::read_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  processExpr(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_for_node(zu::for_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);

	openTag("initialization", lvl + 2);
	node->init()->accept(this, lvl + 4);
	closeTag("initialization", lvl + 2);
	
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  
	openTag("increment", lvl + 2);
	node->incr()->accept(this, lvl + 4);
	closeTag("increment", lvl + 2);
	
  openTag("block", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("block", lvl + 2);

  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_if_node(zu::if_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->block()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_if_else_node(zu::if_else_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  openTag("condition", lvl + 2);
  node->condition()->accept(this, lvl + 4);
  closeTag("condition", lvl + 2);
  openTag("then", lvl + 2);
  node->thenblock()->accept(this, lvl + 4);
  closeTag("then", lvl + 2);
  openTag("else", lvl + 2);
  node->elseblock()->accept(this, lvl + 4);
  closeTag("else", lvl + 2);
  closeTag(node, lvl);

}

//---------------------------------------------------------------------------

void zu::xml_writer::do_break_node(zu::break_node * const node, int lvl) {
  processExpr(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_continue_node(zu::continue_node * const node, int lvl) {
  processExpr(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_return_node(zu::return_node * const node, int lvl) {
  processExpr(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_block_node(zu::block_node * const node, int lvl) {
  openTag(node, lvl);

	openTag("declarations", lvl + 2);
	node->declarations()->accept(this, lvl + 4);
	closeTag("declarations", lvl + 2);
	
	openTag("instructions", lvl + 2);
	node->instructions()->accept(this, lvl + 4);
	closeTag("instructions", lvl + 2);
  
  closeTag(node, lvl);
}
