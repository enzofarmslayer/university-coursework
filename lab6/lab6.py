from calc import *

def exec_program(p):
    if not is_program(p): raise SyntaxError("Invalid program: " + str(p))
    statements = program_statements(p)
    exec_statements(statements)

def exec_statements(statements):
    if not is_statements(statements): raise SyntaxError("Invalid syntax: " + str(statements))
    
    for statement in statements:
        exec_statement(statement)
    
def exec_statement(statement):
    if not is_statement(statement): raise SyntaxError("Invalid syntax: " + str(statement))

    if is_assignment(statement): exec_assignment(statement)
    #elif is_repetition(statement): exec_repetition(statement)
    elif is_output(statement): exec_output(statement)
    #elif is_input(statement): exec_input(statement)
    else: exec_selection(statement)

def exec_assignment(assignment):
    if not is_assignment(assignment): raise SyntaxError("Invalid syntax: " + str(assignment))
    assignment_var = assignment_variable(assignment)
    assignment_expr = eval_expression(assignment_expression(assignment))
    
def exec_selection(selection):
    if not is_selection(selection): raise SyntaxError("Invalid syntax: " + str(selection))
    cond = selection_condition(selection)

    if eval_condition(cond):
        exec_statement(selection_true_branch(selection))
    elif selection_has_false_branch(selection):
        exec_statement(selection_false_branch(selection))
    
def exec_output(statement):
    output = eval_expression(output_expression(statement))
    print(output)

def eval_expression(expr):
    if isinstance(expr, int): return expr   # Expression is constant
    return eval_binaryexpr(expr)            # Expression is binary

def eval_binaryexpr(expr):
    if not is_binaryexpr(expr): raise SyntaxError("Invalid binary expression: " + str(expr))
    expr_left = eval_expression(binaryexpr_left(expr))
    expr_right = eval_expression(binaryexpr_right(expr))
    binary_oper = eval_binaryoper(binaryexpr_operator(expr))

    if binary_oper == "+":
        return expr_left + expr_right
    
    if binary_oper == "-":
        return expr_left - expr_right

    if binary_oper == "*":
        return expr_left * expr_right
    
    if binary_oper == "/":
        return expr_left / expr_right


def eval_condition(cond):
    if not is_condition(cond): raise SyntaxError("Invalid condition: " + str(cond))
    expr_left = eval_expression(condition_left(cond))
    expr_right = eval_expression(condition_right(cond))
    cond_oper = eval_condoper(condition_operator(cond))

    if cond_oper == "=":
        if expr_left == expr_right: return True
        else: return False

    if cond_oper == "<":
        if expr_left < expr_right: return True
        else: return False

    if cond_oper == ">":
        if expr_left > expr_right: return True
        else: return False
        
def eval_binaryoper(binary_oper):
    if not is_binaryoper(binary_oper): raise SyntaxError("Invalid binary operator: " + str(binary_oper))
    return binary_oper
    

def eval_condoper(cond_oper):
    if not is_condoper(cond_oper): raise SyntaxError("Invalid condition operator: " + str(cond_oper))
    return cond_oper


calc1 = ['calc', ['set', 'a', 5], ['print', 'a']]
exec_program(calc1)
    

        
