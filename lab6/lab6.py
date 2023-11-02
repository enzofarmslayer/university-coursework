"""
PROGRAM = '[', "'calc'", COMMA, STATEMENTS, ']' ;
STATEMENTS = STATEMENT | STATEMENT, COMMA, STATEMENTS ;
STATEMENT = SELECTION | OUTPUT ;
SELECTION = '[', "'if'", COMMA, CONDITION, COMMA, STATEMENT, [COMMA, STATEMENT], ']' ;
OUTPUT = '[', "'print'", COMMA, EXPRESSION, ']' ;
EXPRESSION = CONSTANT | BINARYEXPR ;
BINARYEXPR = '[', EXPRESSION, COMMA, BINARYOPER, COMMA, EXPRESSION, ']' ;
CONDITION = '[', EXPRESSION, COMMA, CONDOPER, COMMA, EXPRESSION, ']' ;
BINARYOPER = "'+'" | "'-'" | "'*'" | "'/'" ;
CONDOPER = "'<'" | "'>'" | "'='" ;
CONSTANT = ? a Python number ? ;
"""

calc1 = ['calc', ['print', 2], ['print', 4]]

from calc import *


def exec_program(p):
    if not is_program(p): return False
    statements = program_statements(p)
    exec_statements(statements)

def exec_statements(statements):
    if not is_statements(statements): raise SyntaxError("Invalid syntax: " + str(statements))
    
    statement_len = len(statements)
    if statement_len == 1: 
        exec_statement(statements)
    elif statement_len == 3: 
        exec_statement(statements[0])
        exec_statements(statements[2])
    
def exec_statement(statement):
    if not is_statement(statement): raise SyntaxError("Invalid syntax: " + str(statement))

    if is_output(statement): exec_output(statement)
    else: exec_selection(statement)

def exec_selection(selection):
    if not is_selection(selection): raise SyntaxError("Invalid syntax: " + str(selection))
    cond = selection_condition(selection)
    if eval_condition(cond):
        exec_statement(selection_true_branch(selection))
    elif selection_has_false_branch(selection):
        exec_statement(selection_false_branch(selection))
    
def exec_output(statement):
    print(output_expression(statement))

exec_program(calc1)
    

        
