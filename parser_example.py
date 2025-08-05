from __future__ import annotations
from typing import Optional, Any


class Token:
    def __init__(self, type: str, value: Any):
        self.type = type
        self.value = value


def tokenize(expression: str) -> list[Token]:
    tokens: list[Token] = []
    current = ""
    for char in expression:
        if char.isdigit():
            current += char
        elif char in ["+", "*"]:
            if current:
                tokens.append(Token("NUMBER", int(current)))
                current = ""
            tokens.append(Token("OPERATOR", char))
    if current:
        tokens.append(Token("NUMBER", int(current)))
    return tokens


class ASTNode:
    def __init__(
        self,
        type: str,
        value: Optional[str] = None,
        left: Optional[ASTNode] = None,
        right: Optional[ASTNode] = None,
    ):
        self.type = type
        self.value = value
        self.left = left
        self.right = right


def parse_expression(tokens: list[Token]):
    def parse_term():
        node = parse_factor()
        while tokens and tokens[0].type == "OPERATOR" and tokens[0].value == "*" :
            tokens.pop(0)
            node = ASTNode("MULTIPLY", '*', left=node, right=parse_factor())
        return node

    def parse_factor():
        token = tokens.pop(0)
        if token.type == "NUMBER":
            return ASTNode("NUMBER", value=token.value)
        else:
            raise ValueError("Expected number")

    node = parse_term()
    while tokens and tokens[0].type == "OPERATOR" and tokens[0].value == "+":
        tokens.pop(0)
        node = ASTNode("ADD", '+', left=node, right=parse_term())
    return node

def prefix_notation(node: Optional[ASTNode], first:bool, prefix: list[str])->list[str]:
	if (node == None):
		return prefix
	if (first == True):
		current = str(node.value)
		prefix.append(current)
	if (node.left == None):
		return prefix
	else:
		current = str(node.left.value)
		prefix.append(current)
		if (node.right != None):
			current = str(node.right.value)
			prefix.append(current)
		if (node.left.left != None):
			prefix_notation(node.left, False, prefix)
		if (node.right != None and node.right.left != None):
			prefix_notation(node.right, False, prefix)
		# else:
		return prefix
		# 	print(f"{level*blank} {tee} {node.left.value}")
			# if (node.left.left != None):
			# 	print_tree(node.left, False, level)
			# print(f"{level*blank} {elbow} {node.right.value}")
			# if (node.right.left != None):
			# 	prefix_notation(node.right, False, prefix)

def print_tree(node: Optional[ASTNode], first: bool , level: int):
	elbow = "└──"
#	pipe = "│  "
	tee = "├──"
	blank = "   "
	if (node == None):
		return
	if (first == True):
		print(f"{elbow} {node.value}")
	if (node.left == None):
		return
	else:
		level += 1
		if (node.right == None):
			print(f"{level*blank} {elbow} {node.left.value}")
			if (node.left.left != None):
				print_tree(node.left, False, level)
		else:
			print(f"{level*blank} {tee} {node.left.value}")
			if (node.left.left != None):
				print_tree(node.left, False, level)
			print(f"{level*blank} {elbow} {node.right.value}")
			if (node.right.left != None):
				print_tree(node.right, False, level)
		

def evaluate_ast(node: Optional[ASTNode]) -> Any:
    if node == None:
        return
    if node.type == "NUMBER":
        return node.value
    elif node.type == "ADD":
        print(f"node = {node.value} left = {node.left.value} right = {node.right.value}")
        return evaluate_ast(node.left) + evaluate_ast(node.right)
    elif node.type == "MULTIPLY":
        print(f"node = {node.value} left = {node.left.value} right = {node.right.value}")
        return evaluate_ast(node.left) * evaluate_ast(node.right)


if __name__ == "__main__":
    # Example usage
    prefix : list[str] = []
    expression = "7 + 3 + 8 * 2"
    tokens = tokenize(expression)
    ast = parse_expression(tokens)
    print_tree(ast, True, 0)
    prefix = prefix_notation(ast, True, prefix)
    result = evaluate_ast(ast)
    print(f"The result of {expression} {prefix} is {result}")
