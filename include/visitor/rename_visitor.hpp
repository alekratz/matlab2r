#ifndef VISITOR_RENAME_VISITOR
#define VISITOR_RENAME_VISITOR

#ifndef VISITOR_HPP
#error This file should not be included standalone. Please include visitor.hpp instead.
#endif

/**
 * This visitor is used to rename all identifiers with underscores in them to
 * be dots. Underscores are not valid in R variable names.
 */
class rename_visitor
    : public visitor
{
public:
    rename_visitor();
    virtual ~rename_visitor() = default;

public:
    virtual void visit(ast::qualified_id_item*);
    virtual void visit(ast::statement_list*);
};

#endif