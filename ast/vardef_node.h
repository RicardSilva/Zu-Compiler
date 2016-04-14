#ifndef __ZU_VARDEF_NODE_H__
#define __ZU_VARDEF_NODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/basic_type.h>
#include <string>

namespace zu {

  /**
   * Class for describing variable definition nodes.
   */
  class vardef_node: public cdk::basic_node {
    basic_type *_type;
    std::string *_id;
    bool _ispublic;
    bool _isextern;
    cdk::expression_node *_value;

  public:
    inline vardef_node(int lineno, basic_type *type, std::string *id, bool ispublic, bool isextern, 
      cdk::expression_node *value) :
        cdk::basic_node(lineno), _type(type), _id(id), _ispublic(ispublic), _isextern(isextern), _value(value) {
    }

  public:
    basic_type *type() {
      return _type;
    }
    void type(basic_type *type) {
      _type = type;
    }

    inline const std::string *id() const {
      return _id;
    }
    inline const bool ispublic() const {
      return _ispublic;
    }
    inline const  bool isextern() const {
      return _isextern;
    }

    cdk::expression_node *value(){
      return _value;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_vardef_node(this, level);
    }

  };

} // zu

#endif
