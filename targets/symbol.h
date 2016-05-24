// $Id: symbol.h,v 1.8 2016/05/20 00:53:14 ist179027 Exp $ -*- c++ -*-
#ifndef __ZU_SEMANTICS_SYMBOL_H__
#define __ZU_SEMANTICS_SYMBOL_H__

#include <string>
#include <cdk/basic_type.h>

namespace zu {

    class symbol {
      basic_type *_type;
      std::string _name;
      std::vector<basic_type *> _args;
      bool _isdeclared;
      int _offset;
      long _value; // hack!

    public:
      inline symbol(basic_type *type, const std::string &name, bool isdeclared, int offset, long value) :
          _type(type), _name(name), _isdeclared(isdeclared), _offset(offset), _value(value) {
      }

      virtual ~symbol() {
        delete _type;
        _args.clear();
      }

      inline basic_type *type() {
        return _type;
      }
      inline const std::string &name() const {
        return _name;
      }
      inline long value() const {
        return _value;
      }
      inline long value(long v) {
        return _value = v;
      }
      inline bool isdeclared() {
        return _isdeclared;
      }
      inline long isdeclared(bool d) {
        return _isdeclared = d;
      }
      inline int offset() {
        return _offset;
      }
      inline int offset(int o) {
        return _offset = o;
      }
      
      void add_arg(basic_type *t) {
        _args.push_back(t);
      }
      
      basic_type *get_arg(size_t i) {
        return _args.at(i);
      }

      size_t argsize() {
        return _args.size();
      }
      
    };

} // zu

#endif
