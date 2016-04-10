#ifndef VISITOR_SANITY_CHECK_VISITOR_HPP
#define VISITOR_SANITY_CHECK_VISITOR_HPP

#ifndef VISITOR_HPP
#error This file should not be included standalone. Please include visitor.hpp instead.
#endif

enum class sanity_check_status
{
    NOT_STARTED,
    IN_PROGRESS,
    SUCCESS,
    ERROR,
};

/**
 * This visitor ensures that the MATLAB code plugged in is sane. This includes:
 *     * Matrix dimensions
 */
class sanity_check_visitor
    : protected visitor
{
public:
    sanity_check_visitor(std::ostream& out=std::cerr);
    virtual ~sanity_check_visitor() = default;

public:
    void start(ast::statement_list* ast);
    
    const sanity_check_status get_status() const { return status; }
    const bool is_successful() const 
        { return status == sanity_check_status::SUCCESS; }
    void reset() { status = sanity_check_status::NOT_STARTED; }
    
protected:
    virtual void visit(ast::primary_expression*);
    
private:
    sanity_check_status status;
    std::ostream& out;
    friend class ast::node;
};

#endif