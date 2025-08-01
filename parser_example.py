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
        while tokens and tokens[0].type == "OPERATOR" and tokens[0].value == "*":
            tokens.pop(0)
            node = ASTNode("MULTIPLY", left=node, right=parse_factor())
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
        node = ASTNode("ADD", left=node, right=parse_term())
    return node


def evaluate_ast(node: Optional[ASTNode]) -> Any:
    if node == None:
        return
    if node.type == "NUMBER":
        return node.value
    elif node.type == "ADD":
        return evaluate_ast(node.left) + evaluate_ast(node.right)
    elif node.type == "MULTIPLY":
        return evaluate_ast(node.left) * evaluate_ast(node.right)


if __name__ == "__main__":
    # Example usage
    expression = "3 + 4 * 2"
    tokens = tokenize(expression)
    ast = parse_expression(tokens)
    result = evaluate_ast(ast)
    print(f"The result of {expression} is {result}")
