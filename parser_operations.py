# Para poder hacer referencia a TreeNode dentro de su definicion,forward definition
from __future__ import annotations
from enum import Enum
import sys

class Token_type(Enum):
	DIGIT = 1
	MINUS = 2
	PLUS = 3
	MULTIPLICATION = 4
	DIVISION = 5
	LPARENTHESIS = 6
	RPARENTHESIS = 7
	BAD = 8

class	Token:
	def __init__(self, id : Token_type, attribute : str, index : int):
		self.id = id
		self.attribute = attribute
		self.index = index
     

class TreeNode:
    def __init__(self, data: Token):
        self.data = data
        self.children: list["TreeNode"] = [] #Se escribe dentro de  "" para que python no busque la definicion en otro lado

    def add_child(self, child: "TreeNode"):
        self.children.append(child)


#Preorder traversal (depth first exploration)
#For a given subtree we first traverse it's root, then to the left
# and then to the right.
# def preorder_traversal(node:TreeNode):

#     if node.children == False:
#         return
#     preorder_traversal(node.children[0])
#     preorder_traversal(node.children[1])
    
def get_token(original : str, start : int) -> Token:
	c = original[start]
	type_token : Token_type = Token_type.BAD
	match c:
		case '0':
			type_token = Token_type.DIGIT
		case '1':
			type_token = Token_type.DIGIT
		case '2':
			type_token = Token_type.DIGIT
		case '3':
			type_token = Token_type.DIGIT
		case '4':
			type_token = Token_type.DIGIT
		case '5':
			type_token = Token_type.DIGIT
		case '6':
			type_token = Token_type.DIGIT
		case '7':
			type_token = Token_type.DIGIT
		case '8':
			type_token = Token_type.DIGIT
		case '9':
			type_token = Token_type.DIGIT
		case '+':
			type_token = Token_type.PLUS
		case '-':
			type_token = Token_type.MINUS
		case '*':
			type_token = Token_type.MULTIPLICATION
		case '/':
			type_token = Token_type.DIVISION
		case '(':
			type_token = Token_type.LPARENTHESIS
		case ')':
			type_token = Token_type.RPARENTHESIS
		case _:
			type_token = Token_type.BAD
	token = Token(type_token, c, start)
	return  token

		
def is_operator(operator : Token_type) -> bool:
	match operator:
		case Token_type.PLUS:
			return True
		case Token_type.MINUS:
			return True
		case Token_type.MULTIPLICATION:
			return True
		case Token_type.DIVISION:
			return True
		case _:
			return False
		

def lexical_analizer(original : str):
	start :int = 0
	if len(original) == 0:
		return
	first_token : Token = get_token(original, start)
	if (first_token.id == Token_type.DIGIT):
		start += 1
		while start < len(original) and original[start] == ' ':
			start += 1
		if start < len(original):
			second_token : Token = get_token(original, start)
		else :
			print(original)
			return
	if is_operator(second_token.id):
		root = TreeNode(second_token)
		node = TreeNode(first_token)
		tree.add_child(node)

     
if __name__ == '__main__':
    original = sys.argv[1]
    lexical_analizer(original)
    
~                        