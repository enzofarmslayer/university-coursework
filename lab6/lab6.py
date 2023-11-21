from calc import *


def exec_program(p, var_table={}):
    """Execute a program with a given variable table."""

    if not is_program(p):
        raise SyntaxError("Invalid program: " + str(p))
    statements = program_statements(p)
    new_var_table = exec_statements(statements, var_table)

    return new_var_table


def exec_statements(statements, var_table):
    """Execute a list of statements while updating the variable table."""

    if not is_statements(statements):
        raise SyntaxError("Invalid syntax: " + str(statements))
    new_var_table = exec_statement(first_statement(statements), var_table)
    if(len(statements) == 1):
        return new_var_table

    return exec_statements(rest_statements(statements), new_var_table)


def exec_statement(statement, var_table):
    """Execute a single statement and update the variable table."""

    if not is_statement(statement):
        raise SyntaxError("Invalid syntax: " + str(statement))

    if is_assignment(statement):
        return exec_assignment(statement, var_table)
    elif is_repetition(statement):
        return exec_repetition(statement, var_table)
    elif is_output(statement):
        exec_output(statement, var_table)
        return var_table
    elif is_input(statement):
        return exec_input(statement, var_table)
    elif is_selection(statement):
        return exec_selection(statement, var_table)
    else:
        raise SyntaxError("Invalid statement: " + str(statement))


def exec_assignment(assignment, var_table):
    """Execute an assignment statement and update the variable table."""

    assignment_var = assignment_variable(assignment)
    assignment_expr = eval_expression(
        assignment_expression(assignment), var_table)

    new_var_table = var_table.copy()
    new_var_table[assignment_var] = assignment_expr
    return new_var_table


def exec_repetition(statement, var_table):
    """Execute a while loop under given condition."""

    cond = repetition_condition(statement)
    statements = repetition_statements(statement)

    if not eval_condition(cond, var_table):
        return var_table
    new_var_table = exec_statements(statements, var_table)
    return exec_repetition(statement, new_var_table)


def exec_selection(selection, var_table):
    """Execute an if-statement and update the variable table."""

    cond = selection_condition(selection)

    if eval_condition(cond, var_table):
        return exec_statement(selection_true_branch(selection), var_table)
    elif selection_has_false_branch(selection):
        return exec_statement(selection_false_branch(selection), var_table)
    else:
        return var_table


def exec_input(expr, var_table):
    """Request an input and update the variable table."""

    new_var = input_variable(expr)
    value = int(input("Enter value for " + new_var + ": "))
    new_var_table = var_table.copy()
    new_var_table[new_var] = value
    return new_var_table


def exec_output(statement, var_table):
    """Evaluate and print given expression."""

    expr = output_expression(statement)
    value = eval_expression(expr, var_table)

    if is_variable(expr):
        print(expr + " = " + str(value))
    else:
        print(value)


def eval_expression(expr, var_table):
    """Evaluate an expression based on the current variable table."""

    if isinstance(expr, int):
        return expr
    if is_variable(expr):
        return var_table[expr]
    if is_binaryexpr(expr):
        return eval_binaryexpr(expr, var_table)
    raise SyntaxError("Invalid expression: " + str(expr))


def eval_binaryexpr(expr, var_table):
    """Evaluate a binary expression based on the current variable table."""

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
    """Evaluate a boolean condition based on the current variable table."""

    if not is_condition(cond):
        raise SyntaxError("Invalid condition: " + str(cond))
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
    """Return the binary operator as a string."""

    if not is_binaryoper(binary_oper):
        raise SyntaxError("Invalid binary operator: " + str(binary_oper))
    return binary_oper


# exec_program()

def eval_condoper(cond_oper):
    """Return the condition operator as a string."""

    if not is_condoper(cond_oper):
        raise SyntaxError("Invalid condition operator: " + str(cond_oper))
    return cond_oper


"""
Körexempel
"""

# Kvadrera givet tal
calc_test_1 = ['calc', ['read', 'x'], ['set', 'x2', ['x', '*', 'x']], ['print', 'x2']]

# Beräkna fakultet av givet tal
calc_test_2 = ['calc', ['read', 'n'], ['set', 'result', 'n'], ['while', ['n', '>', 1], ['set', 'n2', ['n', '-', 1]], ['set', 'result', ['result', '*', 'n2']], ['set', 'n', 'n2']], ['print', 'result']]

# Systembolaget check
calc_test_3 = ['calc', ['read', 'age'], ['if', ['age', '>', 19], ['print', 1], ['print', 0]]]

# Error checks
calc_test_4 = []
calc_test_5 = ['enzo']
calc_test_6 = ['calc', ['set', 'a', '*']]
