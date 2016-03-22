#ifndef __ZU_FUNDEF_NODE_H__
#define __ZU_FUNDEF_NODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/sequence_node.h>
#include <cdk/basic_type.h>
#include "ast/variable_node.h"
#include "ast/block_node.h"
#include <string>

namespace zu {

  /**
   * Class for describing function definition nodes.
   */
  class fundef_node: public cdk::basic_node {
  	variable_node *_retval;
    cdk::sequence_node *_args;
    basic_type *_type;
    std::string _id;
    bool _ispublic;
    bool _isextern;
    block_node *_body;


  public:
    inline fundef_node(int lineno, cdk::sequence_node *args, basic_type *type, const std::string &id, 
      bool ispublic, bool isextern, block_node *body) :
        cdk::basic_node(lineno), _args(args), _type(type), _id(id),
        	_ispublic(ispublic), _isextern(isextern), _body(body) {
            _retval = new variable_node(lineno, type, id);
    }

  public:
    inline cdk::sequence_node *args() {
      return _args;
    }

    basic_type *type() {
      return _type;
    }

    void type(basic_type *type) {
      _type = type;
    }

    inline variable_node *retval() {
      return _retval;
    }

    inline const std::string &id() const {
      return _id;
    }
    inline const bool ispublic() const {
      return _ispublic;
    }
    inline const  bool isextern() const {
      return _isextern;
    }

    inline block_node *body() {
      return _body;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_fundef_node(this, level);
    }

  };

} // zu

#endif
