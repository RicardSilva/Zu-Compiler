// $Id: postfix_writer.cpp,v 1.42 2016/05/20 09:49:29 ist179027 Exp $ -*- c++ -*-
#include <string>
#include <sstream>
#include "targets/type_checker.h"
#include "targets/postfix_writer.h"
#include "targets/size_visitor.h"
#include "ast/all.h"  // all.h is automatically generated

//---------------------------------------------------------------------------
//     THIS IS THE VISITOR'S DEFINITION
//---------------------------------------------------------------------------

void zu::postfix_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl);
  }
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
 
  CHECK_TYPES(_compiler, _symtab, node);
  if (_inside)
    _pf.INT(node->value());
  else 
    _pf.CONST(node->value());  
}

void zu::postfix_writer::do_double_node(cdk::double_node * const node, int lvl) {
  
  CHECK_TYPES(_compiler, _symtab, node);
  if (_inside) {
    int dlbl = ++_lbl;
    _pf.RODATA();
    _pf.ALIGN();
    _pf.LABEL(mklbl(dlbl));
    _pf.DOUBLE(node->value());
    _pf.TEXT();
    _pf.ALIGN();
    _pf.ADDR(mklbl(dlbl));
    _pf.DLOAD();
  }
  else 
    _pf.DOUBLE(node->value());
}

void zu::postfix_writer::do_string_node(cdk::string_node * const node, int lvl) {
 
  CHECK_TYPES(_compiler, _symtab, node);
  int strlbl = ++_lbl;
  _pf.RODATA();
  _pf.ALIGN();
  _pf.LABEL(mklbl(strlbl));
  _pf.STR(node->value());
  if (_inside) {    
    _pf.TEXT();
    _pf.ALIGN();
    _pf.ADDR(mklbl(strlbl));
  }
  else {
    _pf.DATA();
    _pf.ALIGN();    
    _pf.ID(mklbl(strlbl));
  }
}


void zu::postfix_writer::do_identifier_node(cdk::identifier_node * const node, int lvl) {
  //do nothing
}


//---------------------------------------------------------------------------

void zu::postfix_writer::do_identity_node(zu::identity_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); // determine the value
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_neg_node(cdk::neg_node * const node, int lvl) {

	CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); // determine the value
  if (node->type()->name() == basic_type::TYPE_INT)
    _pf.NEG();
  else if (node->type()->name() == basic_type::TYPE_DOUBLE)
    _pf.DNEG();
}

//---------------------------------------------------------------------------
void zu::postfix_writer::do_not_node(zu::not_node * const node, int lvl) {  
	CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); // determine the value
  _pf.NOT(); 
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_malloc_node(zu::malloc_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  
  node->counter()->accept(this, lvl);
  _pf.INT(node->type()->subtype()->size());
  _pf.MUL();
  _pf.ALLOC();
  _pf.SP();
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_add_node(cdk::add_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);	
	if(node->type()->name() == basic_type::TYPE_INT) {
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.ADD();
	}
	else if(node->type()->name() == basic_type::TYPE_DOUBLE) {
		node->left()->accept(this, lvl);
		if(node->left()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
			
		node->right()->accept(this, lvl);
		if(node->right()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
		_pf.DADD();
	}
	else if(node->type()->name() == basic_type::TYPE_POINTER) {
		node->left()->accept(this, lvl);
    if(node->left()->type()->name() == basic_type::TYPE_INT) {
      _pf.INT(node->right()->type()->subtype()->size());
      _pf.MUL();     
    }
    node->right()->accept(this, lvl);
    if(node->right()->type()->name() == basic_type::TYPE_INT) {
      _pf.INT(node->left()->type()->subtype()->size());
      _pf.MUL();
    }
    _pf.ADD();
	}

}

void zu::postfix_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  	CHECK_TYPES(_compiler, _symtab, node);	
	if(node->type()->name() == basic_type::TYPE_INT) {
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.SUB();
	}
	else if(node->type()->name() == basic_type::TYPE_DOUBLE) {
		node->left()->accept(this, lvl);
		if(node->left()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
			
		node->right()->accept(this, lvl);
		if(node->right()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
		_pf.DSUB();
	}
	else if(node->type()->name() == basic_type::TYPE_POINTER) {
		node->left()->accept(this, lvl);
    node->right()->accept(this, lvl);
    _pf.INT(node->right()->type()->subtype()->size());
    _pf.MUL();
    _pf.ADD();
	}
}

void zu::postfix_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  
  CHECK_TYPES(_compiler, _symtab, node);
	if(node->type()->name() == basic_type::TYPE_INT) {
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.MUL();
	}
	else if(node->type()->name() == basic_type::TYPE_DOUBLE) {
	  node->left()->accept(this, lvl);
		if(node->left()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
			
		node->right()->accept(this, lvl);
		if(node->right()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
		_pf.DMUL();
	}
	
}
void zu::postfix_writer::do_div_node(cdk::div_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
	if(node->type()->name() == basic_type::TYPE_INT) {
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.DIV();
	}
	else if(node->type()->name() == basic_type::TYPE_DOUBLE) {
	  node->left()->accept(this, lvl);
		if(node->left()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
			
		node->right()->accept(this, lvl);
		if(node->right()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
		_pf.DDIV();
	}
}
void zu::postfix_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  node->right()->accept(this, lvl);
  _pf.MOD();
}
void zu::postfix_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);	
	if(node->type()->name() == basic_type::TYPE_INT) {
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.LT();
	}
	else if(node->type()->name() == basic_type::TYPE_DOUBLE) {
		node->left()->accept(this, lvl);
		if(node->left()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
			
		node->right()->accept(this, lvl);
		if(node->right()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
			
		_pf.DCMP();
		_pf.INT(0);
		_pf.LT();
	}
}
void zu::postfix_writer::do_le_node(cdk::le_node * const node, int lvl) {
	CHECK_TYPES(_compiler, _symtab, node);	
	if(node->type()->name() == basic_type::TYPE_INT) {
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.LE();
	}
	else if(node->type()->name() == basic_type::TYPE_DOUBLE) {
		node->left()->accept(this, lvl);
		if(node->left()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
			
		node->right()->accept(this, lvl);
		if(node->right()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
			
		_pf.DCMP();
		_pf.INT(0);
		_pf.LE();
	}
}
void zu::postfix_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
 	CHECK_TYPES(_compiler, _symtab, node);	
	if(node->type()->name() == basic_type::TYPE_INT) {
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.GE();
	}
	else if(node->type()->name() == basic_type::TYPE_DOUBLE) {
		node->left()->accept(this, lvl);
		if(node->left()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
			
		node->right()->accept(this, lvl);
		if(node->right()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
			
		_pf.DCMP();
		_pf.INT(0);
		_pf.GE();
	}
}
void zu::postfix_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
 	CHECK_TYPES(_compiler, _symtab, node);	
	if(node->type()->name() == basic_type::TYPE_INT) {
		node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.GT();
	}
	else if(node->type()->name() == basic_type::TYPE_DOUBLE) {
		node->left()->accept(this, lvl);
		if(node->left()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
			
		node->right()->accept(this, lvl);
		if(node->right()->type()->name() == basic_type::TYPE_INT)
			_pf.I2D();
			
		_pf.DCMP();
		_pf.INT(0);
		_pf.GT();
	}
}
void zu::postfix_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
	
	if(node->type()->name() == basic_type::TYPE_INT || node->type()->name() == basic_type::TYPE_POINTER) {
	  node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.NE();
	}
	else if(node->type()->name() == basic_type::TYPE_DOUBLE) {		
		node->left()->accept(this, lvl);
    node->right()->accept(this, lvl);
		_pf.DCMP();
		_pf.INT(0);
		_pf.NE();
	}
}
void zu::postfix_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
	
  if(node->type()->name() == basic_type::TYPE_INT || node->type()->name() == basic_type::TYPE_POINTER) {
	  node->left()->accept(this, lvl);
		node->right()->accept(this, lvl);
		_pf.EQ();		
	}
	else if(node->type()->name() == basic_type::TYPE_DOUBLE) {
		node->left()->accept(this, lvl);
    node->right()->accept(this, lvl);
		_pf.DCMP();
		_pf.INT(0);
		_pf.EQ();
	}
}
void zu::postfix_writer::do_and_node(zu::and_node * const node, int lvl) {
  int endand = ++_lbl;
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  _pf.JZ(mklbl(endand));
  node->right()->accept(this, lvl);
  _pf.AND();
  _pf.LABEL(mklbl(endand));
}
void zu::postfix_writer::do_or_node(zu::or_node * const node, int lvl) {
  int endor = ++_lbl;
  CHECK_TYPES(_compiler, _symtab, node);
  node->left()->accept(this, lvl);
  _pf.JNZ(mklbl(endor));
  node->right()->accept(this, lvl);
  _pf.OR();
  _pf.LABEL(mklbl(endor));
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_rvalue_node(zu::rvalue_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->lvalue()->accept(this, lvl);
  if (node->type()->name() == basic_type::TYPE_DOUBLE)
    _pf.DLOAD();
  else
    _pf.LOAD();

}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_variable_node(zu::variable_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  std::cout << "enter postfix variable" << std::endl;
  std::shared_ptr<zu::symbol> symbol = _symtab.find_local(node->id());
  if (symbol != nullptr) {
    std::cout << symbol->name() << std::endl;
    _pf.LOCAL(symbol->offset());
  } else if (symbol=_symtab.find(node->id())) {
    _pf.ADDR(node->id());
  } else {
    std::cerr << "ERROR: CANNOT HAPPEN! [var]" << std::endl;
    exit(1);
  }
    
}

void zu::postfix_writer::do_index_node(zu::index_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->address()->accept(this, lvl);
  if (dynamic_cast<zu::lvalue_node *>(node->address())) {
    _pf.LOAD();
  }
  node->index()->accept(this, lvl);
  if (node->type()->name() == basic_type::TYPE_DOUBLE)
    _pf.INT(8);
  else if (node->type()->name() == basic_type::TYPE_INT ||
           node->type()->name() == basic_type::TYPE_STRING ||
           node->type()->name() == basic_type::TYPE_POINTER)
    _pf.INT(4);
  else {
    std::cerr << "ERROR: CANNOT HAPPEN! [index]" << std::endl;
    exit(1);
  }
  
  _pf.MUL();
  _pf.ADD();
}

void zu::postfix_writer::do_address_node(zu::address_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->arg()->accept(this, lvl);
}

void zu::postfix_writer::do_funcall_node(zu::funcall_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  if (node->args()) {
    // fetch function symbol do convert args according to declaration if needed
    std::shared_ptr<zu::symbol> symbol = _symtab.find("."+node->id());
    size_t sz = node->args()->size();
    for (size_t i=0; i<sz; i++) {
      
      node->args()->node(sz-i-1)->accept(this, lvl);
      if (symbol->get_arg(i)->name() == basic_type::TYPE_DOUBLE &&
          ((cdk::expression_node *)node->args()->node(sz-i-1))->type()->name() == basic_type::TYPE_INT)
        _pf.I2D();
    }
  }
  _pf.CALL(node->id());
  if (node->args()) {
    for (size_t i = 0; i<node->args()->size(); i++) {
      std::cout << "postfix funcall arg " << i+1 << std::endl;
      _pf.TRASH(((cdk::expression_node*)node->args()->node(i))->type()->size());
    }
  }
  if (node->type()->name()==basic_type::TYPE_DOUBLE)
    _pf.DPUSH();
  else if (node->type()->name() == basic_type::TYPE_INT ||
           node->type()->name() == basic_type::TYPE_STRING ||
           node->type()->name() == basic_type::TYPE_POINTER)
    _pf.PUSH();
  else if (node->type()->name() != basic_type::TYPE_VOID) {
    std::cerr << "ERROR: CANNOT HAPPEN! [funcall]" << std::endl;
    exit(1);
  }
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_fundecl_node(zu::fundecl_node * const node, int lvl) {  
  CHECK_TYPES(_compiler, _symtab, node);
  
  _externs[node->id()]=1;
 
  
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_fundef_node(zu::fundef_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);

  _pf.TEXT();
  _pf.ALIGN();
  std::string name = node->id(); 
  _externs.erase(name);
  if (name == "zu") name = "_main";
  else if (name == "_main") name = "__main";  
  if (node->ispublic()) _pf.GLOBAL(name, _pf.FUNC());
  _pf.LABEL(name);
  _retlbl = ++_lbl;
  size_t localsize = 0;
  size_t retsize = (node->type()->name() != basic_type::TYPE_VOID) ? node->type()->size() : 0;
  size_visitor sv(_compiler);
  node->accept(&sv, lvl);
  localsize = sv.size();           
  _pf.ENTER(localsize+retsize);
  _inside=true;
  if (node->retval() != nullptr) { 
    node->retval()->accept(this, lvl);
    if (node->type()->name() == basic_type::TYPE_DOUBLE &&
      node->retval()->type()->name() == basic_type::TYPE_INT)
      _pf.I2D();
    _pf.LOCAL(-retsize);
    if (node->type()->name() == basic_type::TYPE_DOUBLE)
      _pf.DSTORE();
    else
      _pf.STORE();
  } else if (node->type()->name() == basic_type::TYPE_POINTER ||
           node->type()->name() == basic_type::TYPE_INT) {
    _pf.INT(0);
    _pf.LOCA(-retsize); // initialize return value
  }
  node->body()->accept(this, lvl);
  _pf.LABEL(mklbl(_retlbl));
  if (node->type()->name() != basic_type::TYPE_VOID) {
    _pf.LOCAL(-retsize);
    if (node->type()->name() == basic_type::TYPE_DOUBLE) {
      _pf.DLOAD();
      _pf.DPOP();
    } else {
      _pf.LOAD();
      _pf.POP();
    }
  } 
  _pf.LEAVE();
  _pf.RET();
  _inside=false;
  _symtab.pop();
  _breaks.clear();
  _continues.clear();
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_vardecl_node(zu::vardecl_node * const node, int lvl) {
  std::cout << "enter postfix vardecl" << std::endl;
  CHECK_TYPES(_compiler, _symtab, node);
  //check_types inserts symbol
  std::shared_ptr<zu::symbol> symbol = _symtab.find_local(node->id());
  if (symbol == nullptr) {
    std::cerr << "ERROR: CANNOT HAPPEN! [vardecl]" << std::endl;
    exit(0);
  }
  if (_inside) {
    if (node->type()->name() == basic_type::TYPE_DOUBLE)
      _pf.DOUBLE(0.0);
    else if (node->type()->name() == basic_type::TYPE_INT ||
	     node->type()->name() == basic_type::TYPE_POINTER)
      _pf.INT(0);
    else if (node->type()->name() == basic_type::TYPE_STRING) {
      int strlabel = ++_lbl;
      _pf.RODATA();
      _pf.ALIGN();
      _pf.LABEL(mklbl(strlabel));
      _pf.STR("");
      _pf.TEXT();
      _pf.ALIGN();
      _pf.ADDR(mklbl(strlabel));
    }
    
    _pf.LOCAL(symbol->offset());
    if (symbol->type()->name() == basic_type::TYPE_DOUBLE)
      _pf.DSTORE();
    else
      _pf.STORE();
  } else { 
    _pf.DATA();
    _pf.ALIGN();
    if (node->ispublic()) 
      _pf.GLOBAL(node->id(), _pf.OBJ());
    _pf.LABEL(node->id());
    if (node->type()->name() == basic_type::TYPE_DOUBLE)
      _pf.DOUBLE(0.0);
    else if (node->type()->name() == basic_type::TYPE_INT ||
	     node->type()->name() == basic_type::TYPE_POINTER)
      _pf.CONST(0);
    else if (node->type()->name() == basic_type::TYPE_STRING) {
      int strlabel = ++_lbl;
      _pf.RODATA();
      _pf.ALIGN();
      _pf.LABEL(mklbl(strlabel));
      _pf.STR("");
      _pf.DATA();
      _pf.ALIGN();
      _pf.ID(mklbl(strlabel));
    }
  }
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_vardef_node(zu::vardef_node * const node, int lvl) {
  std::cout << "enter postfix vardef" << std::endl;
  CHECK_TYPES(_compiler, _symtab, node);
  //check_types inserts symbol
  std::shared_ptr<zu::symbol> symbol = _symtab.find_local(node->id());
  if (symbol == nullptr) {
    std::cerr << "ERROR: CANNOT HAPPEN! [vardef]" << std::endl;
    exit(0);
  }
  if (!_inside) {
    _pf.DATA();
    _pf.ALIGN();
    if (node->ispublic()) 
      _pf.GLOBAL(node->id(), _pf.OBJ());
    _pf.LABEL(node->id());
    if (node->type()->name() == basic_type::TYPE_DOUBLE &&
      node->value()->type()->name() == basic_type::TYPE_INT) {
      // convert integer to double expression without i2d
      // assumes expr is literal
      _pf.DOUBLE(((cdk::simple_value_node<int> *)node->value())->value());
    }
    else
      node->value()->accept(this, lvl);
  } else {
    node->value()->accept(this, lvl);
    if (node->type()->name() == basic_type::TYPE_DOUBLE &&
      node->value()->type()->name() == basic_type::TYPE_INT)
    _pf.I2D();
    _pf.LOCAL(symbol->offset());
    if (symbol->type()->name() == basic_type::TYPE_DOUBLE)
      _pf.DSTORE();
    else
      _pf.STORE();
  }
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_assignment_node(zu::assignment_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->rvalue()->accept(this, lvl); // determine the new value
  if (node->rvalue()->type()->name() == basic_type::TYPE_DOUBLE)
    _pf.DDUP();
  else
    _pf.DUP();
  if (node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE &&
      node->rvalue()->type()->name() == basic_type::TYPE_INT)
    _pf.I2D();
  node->lvalue()->accept(this, lvl); // where to store the value
  if (node->lvalue()->type()->name() == basic_type::TYPE_DOUBLE)
    _pf.DSTORE(); // store the value at address
  else
    _pf.STORE();
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_evaluation_node(zu::evaluation_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); // determine the value
  if (node->argument()->type()->name() == basic_type::TYPE_INT ||
      node->argument()->type()->name() == basic_type::TYPE_STRING ||
      node->argument()->type()->name() == basic_type::TYPE_POINTER) {
    _pf.TRASH(4); // delete the evaluated value
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.TRASH(8); // delete the evaluated value
  }
  else if (node->argument()->type()->name() != basic_type::TYPE_VOID) {
    std::cerr << "ERROR: CANNOT HAPPEN! [eval]" << std::endl;
    exit(1);
  }
}

void zu::postfix_writer::do_print_node(zu::print_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  node->argument()->accept(this, lvl); // determine the value to print
  if (node->argument()->type()->name() == basic_type::TYPE_INT ||
      node->argument()->type()->name() == basic_type::TYPE_POINTER) {
    _pf.CALL("printi");
    _pf.TRASH(4); // delete the printed value
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_STRING) {
    _pf.CALL("prints");
    _pf.TRASH(4); // delete the printed value's address
  }
  else if (node->argument()->type()->name() == basic_type::TYPE_DOUBLE) {
    _pf.CALL("printd");
    _pf.TRASH(8); // delete the printed value
  }
  else {
    std::cerr << "ERROR: CANNOT HAPPEN! [print]" << std::endl;
    exit(1);
  }
  if (node->println())
    _pf.CALL("println"); // print a newline
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_read_node(zu::read_node * const node, int lvl) {
  
  //TODO: NOT FINISHED
  CHECK_TYPES(_compiler, _symtab, node);
  _pf.CALL("readi");
  _pf.PUSH();
  _pf.STORE();
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_for_node(zu::for_node * const node, int lvl) {
  
  int fortest = ++_lbl; 
  int forincr = ++_lbl; 
  int endfor = ++_lbl;

  _continues.push_back(forincr);
  _breaks.push_back(endfor);
  if (node->init())
  node->init()->accept(this, lvl);
  _pf.LABEL(mklbl(fortest));
  if (node->condition()->size() > 1)
    for (size_t i = 0; i < node->condition()->size()-1; i++) {
      node->condition()->node(i)->accept(this, lvl);
      _pf.TRASH(((cdk::expression_node*)node->condition()->node(i))->type()->size());
    }
  node->condition()->node(node->condition()->size()-1)->accept(this, lvl);
  _pf.JZ(mklbl(endfor));
  node->block()->accept(this, lvl+2);
  _pf.LABEL(mklbl(forincr));
  if (node->incr()) {
    for (size_t i = 0; i < node->incr()->size(); i++) {
      node->incr()->node(i)->accept(this, lvl);
      _pf.TRASH(((cdk::expression_node*)node->incr()->node(i))->type()->size());
    }
  }
  _pf.JMP(mklbl(fortest));
  _pf.LABEL(mklbl(endfor));
  _continues.pop_back();
  _breaks.pop_back();
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_if_node(zu::if_node * const node, int lvl) {
  int lbl1;
  
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->block()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1));
  
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_if_else_node(zu::if_else_node * const node, int lvl) {
  int lbl1, lbl2;
  
  node->condition()->accept(this, lvl);
  _pf.JZ(mklbl(lbl1 = ++_lbl));
  node->thenblock()->accept(this, lvl + 2);
  _pf.JMP(mklbl(lbl2 = ++_lbl));
  _pf.LABEL(mklbl(lbl1));
  node->elseblock()->accept(this, lvl + 2);
  _pf.LABEL(mklbl(lbl1 = lbl2));
  
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_break_node(zu::break_node * const node, int lvl) {
  _pf.JMP(mklbl(_breaks.back()));
  _breaks.pop_back();
  _continues.pop_back();
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_continue_node(zu::continue_node * const node, int lvl) {
  _pf.JMP(mklbl(_continues.back()));
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_return_node(zu::return_node * const node, int lvl) {
  _pf.JMP(mklbl(_retlbl));
}

//---------------------------------------------------------------------------

void zu::postfix_writer::do_block_node(zu::block_node * const node, int lvl) {
  if (node->declarations())
    node->declarations()->accept(this, lvl+2);
  if (node->instructions())
    node->instructions()->accept(this, lvl+2);
}
