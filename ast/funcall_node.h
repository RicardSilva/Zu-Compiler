#ifndef __ZU_FUNCALL_NODE_H__
#define __ZU_FUNCALL_NODE_H__

#include <cdk/ast/sequence_node.h>
#include <string>

namespace zu {

  /**
   * Class for describing function call nodes.
   */
  class funcall_node: public cdk::expression_node {
    std::string _id;
    cdk::sequence_node *_args;

  public:
    inline funcall_node(int lineno, const std::string &id, cdk::sequence_node *args) :
        cdk::expression_node(lineno), _id(id), _args(args) {
    }

  public:
    inline const std::string &id() const {
      return _id;
    }
    inline cdk::sequence_node *args() {
      return _args;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_funcall_node(this, level);
    }

  };

} // zu

#endif
