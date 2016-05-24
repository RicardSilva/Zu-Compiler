// $Id: type_checker.cpp,v 1.41 2016/05/20 09:49:29 ist179027 Exp $ -*- c++ -*-
#include <string>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }

//---------------------------------------------------------------------------
size_t _offset=0;
size_t _argpos=8;

void zu::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  /*if (node->value()==0)
    node->type(new basic_type(4, basic_type::TYPE_UNSPEC));
  else*/
    node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
}

void zu::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

void zu::type_checker::do_identifier_node(cdk::identifier_node * const node, int lvl) { }


//---------------------------------------------------------------------------

inline void zu::type_checker::processUnaryExpressionI(cdk::unary_expression_node * const node, int lvl) {
	ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in argument of unary expression");

  node->type(new basic_type(4, basic_type::TYPE_INT));
}

inline void zu::type_checker::processUnaryExpressionID(cdk::unary_expression_node * const node, int lvl) {
	ASSERT_UNSPEC;
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT && node->argument()->type()->name() != basic_type::TYPE_DOUBLE)
    throw std::string("wrong type in argument of unary expression");

  if(node->argument()->type()->name() == basic_type::TYPE_DOUBLE)
    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  else
	  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_identity_node(zu::identity_node * const node, int lvl) {
  processUnaryExpressionID(node, lvl);
}

void zu::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpressionID(node, lvl);
}

void zu::type_checker::do_not_node(zu::not_node * const node, int lvl) {
  processUnaryExpressionI(node, lvl);
}

void zu::type_checker::do_malloc_node(zu::malloc_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->counter()->accept(this, lvl);
  if (node->counter()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in counter");
  node->type(new basic_type(4, basic_type::TYPE_POINTER));
  node->type()->_subtype = new basic_type(4, basic_type::TYPE_UNSPEC);
}

//---------------------------------------------------------------------------

inline void zu::type_checker::processBinaryExpressionI(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT && node->left()->type()->name() != basic_type::TYPE_UNSPEC)
    throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT && node->right()->type()->name() != basic_type::TYPE_UNSPEC)
    throw std::string("wrong type in right argument of binary expression");


  node->type(new basic_type(4, basic_type::TYPE_INT));
  if (node->left()->type()->name() == basic_type::TYPE_UNSPEC)
    node->left()->type(node->type());
  if (node->right()->type()->name() == basic_type::TYPE_UNSPEC)
    node->right()->type(node->type());
}

inline void zu::type_checker::processBinaryExpressionID(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT && node->left()->type()->name() != basic_type::TYPE_DOUBLE &&
      node->left()->type()->name() != basic_type::TYPE_POINTER)
    throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT && node->right()->type()->name() != basic_type::TYPE_DOUBLE &&
      node->right()->type()->name() != basic_type::TYPE_POINTER)
    throw std::string("wrong type in right argument of binary expression");

  if(node->left()->type()->name() == basic_type::TYPE_UNSPEC && node->right()->type()->name() == basic_type::TYPE_UNSPEC) {
    node->type(new basic_type(4, basic_type::TYPE_INT));
    node->left()->type(node->type());
    node->right()->type(node->type());
  } else if (node->left()->type()->name() == basic_type::TYPE_UNSPEC) {
    node->type(node->left()->type());    
    node->right()->type(node->type());
  } else if (node->right()->type()->name() == basic_type::TYPE_UNSPEC) {
    node->type(node->right()->type());    
    node->left()->type(node->type());
  } else if(node->left()->type()->name() == basic_type::TYPE_DOUBLE || node->right()->type()->name() == basic_type::TYPE_DOUBLE)
    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));  
  else
	  node->type(new basic_type(4, basic_type::TYPE_INT));
}

inline void zu::type_checker::processBinaryExpressionIDP(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT && node->left()->type()->name() != basic_type::TYPE_DOUBLE &&
      node->left()->type()->name() != basic_type::TYPE_POINTER && node->left()->type()->name() != basic_type::TYPE_UNSPEC)
    throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT && node->right()->type()->name() != basic_type::TYPE_DOUBLE &&
      node->right()->type()->name() != basic_type::TYPE_POINTER && node->right()->type()->name() != basic_type::TYPE_UNSPEC)
    throw std::string("wrong type in right argument of binary expression");

  if(node->left()->type()->name() == basic_type::TYPE_UNSPEC && node->right()->type()->name() == basic_type::TYPE_UNSPEC) {
    node->type(new basic_type(4, basic_type::TYPE_INT));
    node->left()->type(node->type());
    node->right()->type(node->type());
  } else if (node->left()->type()->name() == basic_type::TYPE_UNSPEC) {
    node->type(node->left()->type());    
    node->right()->type(node->type());
  } else if (node->right()->type()->name() == basic_type::TYPE_UNSPEC) {
    node->type(node->right()->type());    
    node->left()->type(node->type());
  } else if(node->left()->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() == basic_type::TYPE_POINTER)
    node->type(new basic_type(4, basic_type::TYPE_POINTER));
	else if(node->left()->type()->name() == basic_type::TYPE_DOUBLE && node->right()->type()->name() == basic_type::TYPE_DOUBLE)
    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));
  else if(node->left()->type()->name() == basic_type::TYPE_INT && node->right()->type()->name() == basic_type::TYPE_INT)
	  node->type(new basic_type(4, basic_type::TYPE_INT));
	else
		throw std::string("incompatible types of binary expression");
  // FIXME compare INTs with DOUBLEs
}


void zu::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT && node->left()->type()->name() != basic_type::TYPE_DOUBLE &&
      node->left()->type()->name() != basic_type::TYPE_POINTER && node->left()->type()->name() != basic_type::TYPE_UNSPEC)
    throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT && node->right()->type()->name() != basic_type::TYPE_DOUBLE && 
      node->right()->type()->name() != basic_type::TYPE_POINTER && node->right()->type()->name() != basic_type::TYPE_UNSPEC)
    throw std::string("wrong type in right argument of binary expression");

	// when one argument is pointer the other must be an int
  if((node->left()->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() != basic_type::TYPE_POINTER && node->right()->type()->name() != basic_type::TYPE_INT) && 
	   (node->right()->type()->name() == basic_type::TYPE_POINTER && node->left()->type()->name() != basic_type::TYPE_INT && node->left()->type()->name() != basic_type::TYPE_POINTER))
		throw std::string("incompatible argument types of binary expression");
  
  if(node->left()->type()->name() == basic_type::TYPE_UNSPEC && node->right()->type()->name() == basic_type::TYPE_UNSPEC) {
    node->type(new basic_type(4, basic_type::TYPE_INT));
    node->left()->type(node->type());
    node->right()->type(node->type());
  } else if (node->left()->type()->name() == basic_type::TYPE_UNSPEC) {
    node->type(node->left()->type());    
    node->right()->type(node->type());
  } else if (node->right()->type()->name() == basic_type::TYPE_UNSPEC) {
    node->type(node->right()->type());    
    node->left()->type(node->type());
  } else if(node->left()->type()->name() == basic_type::TYPE_POINTER)
    node->type(node->left()->type());
  else if (node->right()->type()->name() == basic_type::TYPE_POINTER)
    node->type(node->right()->type());
  else if(node->left()->type()->name() == basic_type::TYPE_DOUBLE || node->right()->type()->name() == basic_type::TYPE_DOUBLE)
    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));  
  else 
    node->type(new basic_type(4, basic_type::TYPE_INT));
}
void zu::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT && node->left()->type()->name() != basic_type::TYPE_DOUBLE &&
      node->left()->type()->name() != basic_type::TYPE_POINTER && node->left()->type()->name() != basic_type::TYPE_UNSPEC)
    throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT && node->right()->type()->name() != basic_type::TYPE_DOUBLE && 
      node->right()->type()->name() != basic_type::TYPE_POINTER && node->right()->type()->name() != basic_type::TYPE_UNSPEC)
    throw std::string("wrong type in right argument of binary expression");

	// when both arguments are pointers they must have the same subtype
  // FIXME check types recursively
  if (node->left()->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() == basic_type::TYPE_POINTER) {
		if (node->left()->type()->subtype()->name() != node->right()->type()->subtype()->name())
			throw std::string("incompatible pointer types of binary expression");
		node->type(new basic_type(4, basic_type::TYPE_INT));
	}
	
	// when one argument is pointer the other must be an int
  if((node->left()->type()->name() == basic_type::TYPE_POINTER && node->right()->type()->name() != basic_type::TYPE_POINTER && node->right()->type()->name() != basic_type::TYPE_INT) && 
     (node->right()->type()->name() == basic_type::TYPE_POINTER && node->left()->type()->name() != basic_type::TYPE_INT && node->left()->type()->name() != basic_type::TYPE_POINTER))
    throw std::string("incompatible argument types of binary expression");
  
  if(node->left()->type()->name() == basic_type::TYPE_UNSPEC && node->right()->type()->name() == basic_type::TYPE_UNSPEC) {
    node->type(new basic_type(4, basic_type::TYPE_INT));
    node->left()->type(node->type());
    node->right()->type(node->type());
  } else if (node->left()->type()->name() == basic_type::TYPE_UNSPEC) {
    node->type(node->left()->type());    
    node->right()->type(node->type());
  } else if (node->right()->type()->name() == basic_type::TYPE_UNSPEC) {
    node->type(node->right()->type());    
    node->left()->type(node->type());
  } else if(node->left()->type()->name() == basic_type::TYPE_POINTER || node->right()->type()->name() == basic_type::TYPE_POINTER)
    node->type(new basic_type(4, basic_type::TYPE_POINTER));
  else if(node->left()->type()->name() == basic_type::TYPE_DOUBLE || node->right()->type()->name() == basic_type::TYPE_DOUBLE)
    node->type(new basic_type(8, basic_type::TYPE_DOUBLE));  
  else 
    node->type(new basic_type(4, basic_type::TYPE_INT));
}
void zu::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpressionID(node, lvl);
}
void zu::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpressionID(node, lvl);
}
void zu::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
	processBinaryExpressionI(node, lvl);
}
void zu::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpressionID(node, lvl);
}
void zu::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpressionID(node, lvl);
}
void zu::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpressionID(node, lvl);
}
void zu::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpressionID(node, lvl);
}
void zu::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpressionIDP(node, lvl);
}
void zu::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryExpressionIDP(node, lvl);
}
void zu::type_checker::do_and_node(zu::and_node * const node, int lvl) {
  processBinaryExpressionI(node, lvl);
}
void zu::type_checker::do_or_node(zu::or_node * const node, int lvl) {
  processBinaryExpressionI(node, lvl);
}

//---------------------------------------------------------------------------

void zu::type_checker::do_rvalue_node(zu::rvalue_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->lvalue()->accept(this, lvl);
  node->type(node->lvalue()->type());
}

void zu::type_checker::do_assignment_node(zu::assignment_node * const node, int lvl) {
  ASSERT_UNSPEC;

  node->lvalue()->accept(this, lvl);
  if (node->lvalue()->type()->name() != basic_type::TYPE_INT && 
      node->lvalue()->type()->name() != basic_type::TYPE_DOUBLE && 
      node->lvalue()->type()->name() != basic_type::TYPE_STRING && 
      node->lvalue()->type()->name() != basic_type::TYPE_POINTER)
    throw std::string("wrong type in left argument of assignment expression");

  node->rvalue()->accept(this, lvl);

  if (node->lvalue()->type()->name() == basic_type::TYPE_POINTER && node->rvalue()->type()->name() == basic_type::TYPE_POINTER) {
      /* FIXME implement check_pointers
      if (check_pointers(node->lvalue()->type(), node->rvalue()->type())
        node->type(node->lvalue()->type());*/
    //if (node->rvalue()->type()->subtype()->name() == basic_type::TYPE_UNSPEC)
      node->rvalue()->type(node->lvalue()->type());//->_subtype = node->lvalue()->type()->subtype();
      node->type(node->lvalue()->type());
  } else if (node->lvalue()->type()->name() == node->rvalue()->type()->name() ||
      (node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE && node->rvalue()->type()->name() == basic_type::TYPE_INT) ||
      node->rvalue()->type()->name() == basic_type::TYPE_UNSPEC)
    node->type(node->lvalue()->type());
  else
    throw std::string("wrong type in right argument of assignment expression");
}

//---------------------------------------------------------------------------

void zu::type_checker::do_variable_node(zu::variable_node * const node, int lvl) {
  ASSERT_UNSPEC;
  const std::string &id = node->id();
  std::shared_ptr<symbol> symbol = _symtab.find(id);
  if (!symbol) throw id + " undeclared [variable]";
  node->type(new basic_type(*symbol->type()));
}

void zu::type_checker::do_funcall_node(zu::funcall_node * const node, int lvl) {
  ASSERT_UNSPEC;
  const std::string &id = "." + node->id();
  
  std::shared_ptr<symbol> symbol = _symtab.find(id);
  if (symbol == nullptr) throw id + " undeclared [funcall]";
  //std::cout << "funcall id:" << id << std::endl;
  //std::cout << "funcall type: " << symbol->type()->name() << std::endl;
  // TODO check arguments
  /*if (node->args()) {
    node->args()->accept(this, lvl);
    if (node->args()->size() != symbol->argsize())
      throw std::string("argument mismatch in function call");
    for (size_t i=0; i<node->args()->size(); i++)
      if (symbol->get_arg(i)->name()!=basic_type::TYPE_DOUBLE &&
          ((cdk::expression_node *)(node->args()->node(i)))->type()->name()!= basic_type::TYPE_INT &&
          symbol->get_arg(i)->name()!=((cdk::expression_node *)(node->args()->node(i)))->type()->name())
        throw std::string("argument mismatch in function call");
  }*/
  node->type(new basic_type(*symbol->type()));
}

void zu::type_checker::do_address_node(zu::address_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->arg()->accept(this, lvl);
  node->type(new basic_type(4, basic_type::TYPE_POINTER));
  node->type()->_subtype=node->arg()->type();
}

void zu::type_checker::do_index_node(zu::index_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->address()->accept(this, lvl);
  if (node->address()->type()->name() != basic_type::TYPE_POINTER)
    throw std::string("wrong type in address");
  node->index()->accept(this, lvl);
  if (node->index()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in index");
  node->type(node->address()->type()->subtype());
  // TODO check subtype?
}

//---------------------------------------------------------------------------

void zu::type_checker::do_fundecl_node(zu::fundecl_node * const node, int lvl) {
  //ASSERT_UNSPEC;
  const std::string &id = "." + node->id();
  //std::cout << "fundecl id:" << id << std::endl;
  //std::cout << "fundecl type: " << node->type()->name() << std::endl;
  std::shared_ptr<symbol> s = std::make_shared<symbol>(new basic_type(*node->type()), id, false, 0, 0);
  // TODO handle repeated declarations
  if (!_symtab.insert(id, s))
    throw id + " redeclared";
  //std::cout << "fundecl symbol type: " << s->type()->name() << std::endl;
  if (node->args()) {
    size_t sz = node->args()->size();
    for (size_t i=0; i<sz; i++) {
      zu::vardecl_node *arg = (zu::vardecl_node *) (node->args()->node(sz-i-1));
      //std::cout << "tc fundecl arg " << (sz-i) << std::endl;
      //if (arg->type()==nullptr)
      //  std::cout << "null type for arg #" << i+1 << std::endl;
      s->add_arg(new basic_type(*arg->type()));
    }
  }
  // TODO check booleans?
}

//---------------------------------------------------------------------------

void zu::type_checker::do_fundef_node(zu::fundef_node * const node, int lvl) {
  //ASSERT_UNSPEC;
  const std::string &id = "." + node->id();
  //std::cout << "fundef id:" << id << std::endl;
  std::shared_ptr<symbol> s = _symtab.find(id);
  if (s == nullptr) {
    std::cout << "fundef type: " << node->type()->name() << std::endl;
    s = std::make_shared<symbol>(new basic_type(*node->type()), id, false, 0, 0);
    _symtab.insert(id, s);
    if (node->args()) {
      size_t sz = node->args()->size();
      for (size_t i=0; i<sz; i++) {
        zu::vardecl_node *arg = (zu::vardecl_node *) (node->args()->node(sz-i-1));
        //std::cout << "tc fundef arg " << (sz-i) << std::endl;
        //if (arg->type()==nullptr)
        //  std::cout << "null type for arg #" << i+1 << std::endl;
        s->add_arg(new basic_type(*arg->type()));
      }
    }
    //s = _symtab.find(id);
    //std::cout << "fundef symbol type: " << s->type()->name() << std::endl;
  } else if (node->args()) {
    if (node->args()->size() != s->argsize())
      throw std::string("argument mismatch in function definition");
    for (size_t i=0; i<node->args()->size(); i++)
      if (s->get_arg(i)->name()!=((zu::vardecl_node *)(node->args()->node(i)))->type()->name())
        throw id + " redefined";
  }
  _symtab.push();
  //s = _symtab.find(id);
  //std::cout << "fundef symbol type after push: " << s->type()->name() << std::endl;
  if (node->type()->name() != basic_type::TYPE_VOID) {
    _offset=-node->type()->size();
    if  (!_symtab.insert(node->id(), std::make_shared<symbol>(new basic_type(*node->type()), node->id(), false, _offset, 0)))
      throw std::string("function lvalue redeclared");
  } else
    _offset=0;
  if (node->retval()) {
    node->retval()->accept(this, lvl+2);
    if ((node->type()->name() == basic_type::TYPE_POINTER ||
        node->type()->name() == basic_type::TYPE_DOUBLE) &&
        node->type()->name() == basic_type::TYPE_INT)
    if (node->type()->name() != node->retval()->type()->name())
      if (node->retval()->type()->name() != basic_type::TYPE_INT &&
          (node->type()->name() == basic_type::TYPE_POINTER ||
          node->type()->name() == basic_type::TYPE_DOUBLE))
        throw std::string("wrong type for default value");
  }  
  if (node->args()) {
    _argpos = 8;
    for (size_t i=0; i<node->args()->size(); i++) {
        vardecl_node *arg = (zu::vardecl_node *)(node->args()->node(i));

        if (!_symtab.insert(arg->id(), std::make_shared<symbol>(new basic_type(*arg->type()), arg->id(), false, _argpos, 0)))
          throw std::string("function argument redeclared");
        _argpos+=arg->type()->size();
    } 
  }
  
  // TODO check booleans?
}

//---------------------------------------------------------------------------

void zu::type_checker::do_vardecl_node(zu::vardecl_node * const node, int lvl) {
  const std::string &id = node->id();
  _offset -= node->type()->size();
  if (!_symtab.insert(id, std::make_shared<symbol>(new basic_type(*node->type()), id, false, _offset, 0)))
    throw id + " redeclared";
  // TODO check booleans?
}

//---------------------------------------------------------------------------

void zu::type_checker::do_vardef_node(zu::vardef_node * const node, int lvl) {
  std::cout << "before vardef" << std::endl;
  const std::string &id = node->id();
  _offset -= node->type()->size();
  if (!_symtab.insert(id, std::make_shared<symbol>(new basic_type(*node->type()), id, false, _offset, 0)))
    throw id + " redeclared";
  node->value()->accept(this, lvl+2);
  if (node->value()->type()->name()==basic_type::TYPE_UNSPEC)
    node->value()->type(node->type());
  if (node->type()->name() == basic_type::TYPE_POINTER && node->value()->type()->name() == basic_type::TYPE_INT)
    node->value()->type(node->type());
  if (node->type()->name() != node->value()->type()->name() && 
      !(node->type()->name() == basic_type::TYPE_DOUBLE && node->value()->type()->name() == basic_type::TYPE_INT))
    throw std::string("wrong type for initial value");
  // TODO check booleans?
}

//---------------------------------------------------------------------------

void zu::type_checker::do_evaluation_node(zu::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

void zu::type_checker::do_print_node(zu::print_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() == basic_type::TYPE_UNSPEC)
    node->argument()->type(new basic_type(4, basic_type::TYPE_INT));
  else if (node->argument()->type()->name() != basic_type::TYPE_INT &&
      node->argument()->type()->name() != basic_type::TYPE_DOUBLE &&
      node->argument()->type()->name() != basic_type::TYPE_STRING)
    throw std::string("type cannot be printed");
}

//---------------------------------------------------------------------------

void zu::type_checker::do_read_node(zu::read_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_UNSPEC));
}

//---------------------------------------------------------------------------

void zu::type_checker::do_for_node(zu::for_node * const node, int lvl) {
  /*for (size_t i = 0; i < node->condition()->size(); i++) {
    node->condition()->node(i)->accept(this, lvl);
    if (node->condition()->node(i)->type()->name() != basic_type::TYPE_INT)
      throw std::string("wrong type in condition expression");
  }*/
}

//---------------------------------------------------------------------------

void zu::type_checker::do_if_node(zu::if_node * const node, int lvl) {
  // conditions must be integer
  /*node->condition()->accept(this, lvl + 4);
  if (node->condition()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in condition expression");*/
}

//---------------------------------------------------------------------------

void zu::type_checker::do_if_else_node(zu::if_else_node * const node, int lvl) {
  /*node->condition()->accept(this, lvl + 4);
  if (node->condition()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in condition expression");*/
}

//---------------------------------------------------------------------------

void zu::type_checker::do_break_node(zu::break_node * const node, int lvl) {
}

//---------------------------------------------------------------------------

void zu::type_checker::do_continue_node(zu::continue_node * const node, int lvl) {
}

//---------------------------------------------------------------------------

void zu::type_checker::do_return_node(zu::return_node * const node, int lvl) {
}

//---------------------------------------------------------------------------

void zu::type_checker::do_block_node(zu::block_node * const node, int lvl) {
}
