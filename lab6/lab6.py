'''
COMMA = ',' ;
PROGRAM = '[', "'calc'", COMMA, STATEMENTS, ']' ;
STATEMENTS = STATEMENT | STATEMENT, COMMA, STATEMENTS ;
STATEMENT = ASSIGNMENT | REPETITION | SELECTION | INPUT | OUTPUT ;
ASSIGNMENT = '[', "'set'", COMMA, VARIABLE, COMMA, EXPRESSION, ']' ;
REPETITION = '[', "'while'", COMMA, CONDITION, COMMA, STATEMENTS, ']' ;
SELECTION = '[', "'if'", COMMA, CONDITION, COMMA, STATEMENT, [COMMA, STATEMENT], ']' ;
INPUT = '[', "'read'", COMMA, VARIABLE, ']' ;
OUTPUT = '[', "'print'", COMMA, EXPRESSION, ']' ;
EXPRESSION = CONSTANT | VARIABLE | BINARYEXPR ;
BINARYEXPR = '[', EXPRESSION, COMMA, BINARYOPER, COMMA, EXPRESSION, ']' ;
CONDITION = '[', EXPRESSION, COMMA, CONDOPER, COMMA, EXPRESSION, ']' ;
BINARYOPER = "'+'" | "'-'" | "'*'" | "'/'" ;
CONDOPER = "'<'" | "'>'" | "'='" ;
VARIABLE = ? a Python string ? ;
CONSTANT = ? a Python number ? ;
'''

from calc import *


def exec_program(p, var_table = {}):
    if not is_program(p): raise SyntaxError("Invalid program: " + str(p))
    statements = program_statements(p)
    new_var_table = exec_statements(statements, var_table)

    return new_var_table

def exec_statements(statements, var_table):
    if not is_statements(statements): raise SyntaxError("Invalid syntax: " + str(statements))
    new_var_table = exec_statement(first_statement(statements), var_table)
    if(len(statements) == 1): return new_var_table
    
    return exec_statements(rest_statements(statements), new_var_table)
    
    
def exec_statement(statement, var_table):
    if not is_statement(statement): raise SyntaxError("Invalid syntax: " + str(statement))

    new_var_table = var_table.copy()
    if is_assignment(statement): 
        new_var_table = exec_assignment(statement, var_table)
    elif is_repetition(statement): 
        new_var_table = exec_repetition(statement, var_table)
    elif is_output(statement): 
        exec_output(statement, var_table)
    elif is_input(statement): 
        new_var_table = exec_input(statement, var_table)
    elif is_selection(statement): 
        new_var_table = exec_selection(statement, var_table)
    else:
        raise SyntaxError("Invalid statement: " + str(statement))
    
    return new_var_table

def exec_assignment(assignment, var_table):
    assignment_var = assignment_variable(assignment)
    assignment_expr = eval_expression(assignment_expression(assignment), var_table)

    new_var_table = var_table.copy()
    new_var_table[assignment_var] = assignment_expr
    return new_var_table

def exec_repetition(statement, var_table):
    cond = repetition_condition(statement)
    statements = repetition_statements(statement)

    if not eval_condition(cond, var_table): return var_table
    new_var_table = exec_statements(statements, var_table)
    return exec_repetition(statement, new_var_table)

def exec_selection(selection, var_table):
    cond = selection_condition(selection)

    if eval_condition(cond, var_table):
        return exec_statement(selection_true_branch(selection), var_table)
    elif selection_has_false_branch(selection):
        return exec_statement(selection_false_branch(selection), var_table)
    else:
        return var_table

def exec_input(expr, var_table):
    new_var = expr[1]
    value = int(input("Enter value for " + new_var + ": "))
    new_var_table = var_table.copy()
    new_var_table[new_var] = value
    return new_var_table
    
def exec_output(statement, var_table):
    expr = output_expression(statement)
    value = eval_expression(expr, var_table)

    if is_variable(expr):
        print(expr + " = " + str(value))
    else:
        print(value)

def eval_expression(expr, var_table):
    if isinstance(expr, int): return expr
    if is_variable(expr): return var_table[expr]                    
    if is_binaryexpr(expr): return eval_binaryexpr(expr, var_table)
    raise SyntaxError("Invalid expression: " + str(expr))

def eval_binaryexpr(expr, var_table):
    expr_left = eval_expression(binaryexpr_left(expr), var_table) 
    expr_right = eval_expression(binaryexpr_right(expr), var_table)
    binary_oper = eval_binaryoper(binaryexpr_operator(expr))

    if binary_oper == "+":
        return expr_left + expr_right
    
    if binary_oper == "-":
        return expr_left - expr_right

    if binary_oper == "*":
        return expr_left * expr_right
    
    if binary_oper == "/":
        return expr_left / expr_right


def eval_condition(cond, var_table):
    if not is_condition(cond): raise SyntaxError("Invalid condition: " + str(cond))
    expr_left = eval_expression(condition_left(cond), var_table)
    expr_right = eval_expression(condition_right(cond), var_table)
    cond_oper = eval_condoper(condition_operator(cond))

    if cond_oper == "=":
        return expr_left == expr_right

    if cond_oper == "<":
        return expr_left < expr_right

    if cond_oper == ">":
        return expr_left > expr_right
        
def eval_binaryoper(binary_oper):
    if not is_binaryoper(binary_oper): raise SyntaxError("Invalid binary operator: " + str(binary_oper))
    return binary_oper
    

def eval_condoper(cond_oper):
    if not is_condoper(cond_oper): raise SyntaxError("Invalid condition operator: " + str(cond_oper))
    return cond_oper
