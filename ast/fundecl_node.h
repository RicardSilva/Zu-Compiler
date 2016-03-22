#ifndef __ZU_FUNDECL_LNODE_H__
#define __ZU_FUNDECL_NODE_H__

#include <cdk/ast/expression_node.h>
#include <cdk/ast/sequence_node.h>
#include <cdk/basic_type.h>
#include <string>

namespace zu {

  /**
   * Class for describing function  declaration nodes.
   */
  class fundecl_node: public cdk::basic_node {
    cdk::sequence_node *_args;
    basic_type *_type;
    std::string _id;
    bool _ispublic;
    bool _isextern;

  public:
    inline fundecl_node(int lineno, cdk::sequence_node *args, basic_type *type, const std::string &id, bool ispublic, bool isextern) :
        cdk::basic_node(lineno), _args(args), _type(type), _id(id), _ispublic(ispublic), _isextern(isextern) {
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

    inline const std::string &id() const {
      return _id;
    }
    inline const bool ispublic() const {
      return _ispublic;
    }
    inline const  bool isextern() const {
      return _isextern;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_fundecl_node(this, level);
    }

  };

} // zu

#endif
