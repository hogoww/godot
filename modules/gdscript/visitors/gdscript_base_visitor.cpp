/**************************************************************************/
/*  gdscript_base_visitor.cpp                                             */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "gdscript_base_visitor.h"

void NodeWalkerVisitor::visit_annotation(const GDScriptASTNodes::AnnotationNode *p_annotation) {
	for (uint32_t i = 0; i < p_annotation->arguments.size(); ++i) {
		p_annotation->arguments[i]->accept_visitor(this);
	}
}

void NodeWalkerVisitor::visit_assignable(const GDScriptASTNodes::AssignableNode *p_assignable) {
}

void NodeWalkerVisitor::visit_array(const GDScriptASTNodes::ArrayNode *p_array) {
	for (uint32_t i = 0; i < p_array->elements.size(); i++) {
		p_array->elements[i]->accept_visitor(this);
	}
}

void NodeWalkerVisitor::visit_assert(const GDScriptASTNodes::AssertNode *p_assert) {
	p_assert->condition->accept_visitor(this);
}

void NodeWalkerVisitor::visit_assignment(const GDScriptASTNodes::AssignmentNode *p_assignment) {
	p_assignment->assignee->accept_visitor(this);
	p_assignment->assigned_value->accept_visitor(this);
}

void NodeWalkerVisitor::visit_await(const GDScriptASTNodes::AwaitNode *p_await) {
	p_await->to_await->accept_visitor(this);
}

void NodeWalkerVisitor::visit_binary_op(const GDScriptASTNodes::BinaryOpNode *p_binary_op) {
	p_binary_op->left_operand->accept_visitor(this);
	p_binary_op->right_operand->accept_visitor(this);
}

void NodeWalkerVisitor::visit_break(const GDScriptASTNodes::BreakNode *p_break) {
}

void NodeWalkerVisitor::visit_breakpoint(const GDScriptASTNodes::BreakpointNode *p_breakpoint) {
}

void NodeWalkerVisitor::visit_call(const GDScriptASTNodes::CallNode *p_call) {
	p_call->callee->accept_visitor(this);
	for (uint32_t i = 0; i < p_call->arguments.size(); i++) {
		p_call->arguments[i]->accept_visitor(this);
	}
}

void NodeWalkerVisitor::visit_cast(const GDScriptASTNodes::CastNode *p_cast) {
	p_cast->operand->accept_visitor(this);
	p_cast->cast_type->accept_visitor(this);
}

// TODO PMI visit members
void NodeWalkerVisitor::visit_class(const GDScriptASTNodes::ClassNode *p_class) {
	for (const GDScriptASTNodes::AnnotationNode *E : p_class->annotations) {
		E->accept_visitor(this);
	}
	if (p_class != nullptr) {
		p_class->identifier->accept_visitor(this);
	}
}

void NodeWalkerVisitor::visit_constant(const GDScriptASTNodes::ConstantNode *p_constant) {
	p_constant->identifier->accept_visitor(this);
	if (p_constant->initializer != nullptr) {
		p_constant->initializer->accept_visitor(this);
	}
}

void NodeWalkerVisitor::visit_continue(const GDScriptASTNodes::ContinueNode *p_continue) {
}

void NodeWalkerVisitor::visit_dictionary(const GDScriptASTNodes::DictionaryNode *p_dictionary) {
	for (const GDScriptASTNodes::DictionaryNode::Pair &element : p_dictionary->elements) {
		element.key->accept_visitor(this);
		element.value->accept_visitor(this);
	}
}

void NodeWalkerVisitor::visit_expression(const GDScriptASTNodes::ExpressionNode *p_expression) {
	if (p_expression != nullptr) {
		p_expression->accept_visitor(this);
	}
}

void NodeWalkerVisitor::visit_enum(const GDScriptASTNodes::EnumNode *p_enum) {
	if (p_enum->identifier != nullptr) {
		p_enum->identifier->accept_visitor(this);
	}
	for (const GDScriptASTNodes::EnumNode::Value &item : p_enum->values) {
		item.identifier->accept_visitor(this);
	}
}

void NodeWalkerVisitor::visit_for(const GDScriptASTNodes::ForNode *p_for) {
	p_for->variable->accept_visitor(this);
	p_for->list->accept_visitor(this);
	p_for->loop->accept_visitor(this);
}

void NodeWalkerVisitor::visit_function(const GDScriptASTNodes::FunctionNode *p_function) {
	for (const GDScriptASTNodes::AnnotationNode *E : p_function->annotations) {
		E->accept_visitor(this);
	}
	if (p_function->identifier) {
		p_function->identifier->accept_visitor(this);
	}
	for (uint32_t i = 0; i < p_function->parameters.size(); i++) {
		p_function->parameters[i]->accept_visitor(this);
	}
	p_function->body->accept_visitor(this);
}

void NodeWalkerVisitor::visit_get_node(const GDScriptASTNodes::GetNodeNode *p_get_node) {
}

void NodeWalkerVisitor::visit_if(const GDScriptASTNodes::IfNode *p_if) {
	p_if->condition->accept_visitor(this);
	p_if->true_block->accept_visitor(this);
	if (p_if->false_block != nullptr) {
		p_if->false_block->accept_visitor(this);
	}
}

void NodeWalkerVisitor::visit_identifier(const GDScriptASTNodes::IdentifierNode *p_identifier) {
}

void NodeWalkerVisitor::visit_lambda(const GDScriptASTNodes::LambdaNode *p_lambda) {
	p_lambda->function->accept_visitor(this);
}

void NodeWalkerVisitor::visit_literal(const GDScriptASTNodes::LiteralNode *p_literal) {
}

void NodeWalkerVisitor::visit_match(const GDScriptASTNodes::MatchNode *p_match) {
	p_match->test->accept_visitor(this);
	for (const GDScriptASTNodes::MatchBranchNode *branch : p_match->branches) {
		branch->accept_visitor(this);
	}
}

void NodeWalkerVisitor::visit_match_branch(const GDScriptASTNodes::MatchBranchNode *p_match_branch) {
	for (uint32_t i = 0; i < p_match_branch->patterns.size(); i++) {
		p_match_branch->patterns[i]->accept_visitor(this);
	}
	p_match_branch->block->accept_visitor(this);
}

void NodeWalkerVisitor::visit_match_pattern(const GDScriptASTNodes::PatternNode *p_match_pattern) {
}

void NodeWalkerVisitor::visit_node(const GDScriptASTNodes::Node *p_node) {
}

void NodeWalkerVisitor::visit_parameter(const GDScriptASTNodes::ParameterNode *p_parameter) {
	p_parameter->identifier->accept_visitor(this);
	if (p_parameter->datatype_specifier != nullptr) {
		p_parameter->datatype_specifier->accept_visitor(this);
	}
	if (p_parameter->initializer != nullptr) {
		p_parameter->initializer->accept_visitor(this);
	}
}

void NodeWalkerVisitor::visit_pass(const GDScriptASTNodes::PassNode *p_pass) {
}

void NodeWalkerVisitor::visit_pattern(const GDScriptASTNodes::PatternNode *p_pattern) {
}

void NodeWalkerVisitor::visit_preload(const GDScriptASTNodes::PreloadNode *p_preload) {
}

void NodeWalkerVisitor::visit_return(const GDScriptASTNodes::ReturnNode *p_return) {
	if (p_return->return_value != nullptr) {
		p_return->return_value->accept_visitor(this);
	}
}

void NodeWalkerVisitor::visit_self(const GDScriptASTNodes::SelfNode *p_self) {
}

void NodeWalkerVisitor::visit_signal(const GDScriptASTNodes::SignalNode *p_signal) {
	p_signal->identifier->accept_visitor(this);
	for (const GDScriptASTNodes::ParameterNode *param : p_signal->parameters) {
		param->accept_visitor(this);
	}
}

void NodeWalkerVisitor::visit_subscript(const GDScriptASTNodes::SubscriptNode *p_subscript) {
	// TODO PMI
	// p_subscript->base->accept_visitor(this);
	// if (p_subscript->is_attribute) {
	//         p_subscript->attribute->accept_visitor(this);
	// } else {
	// 	push_text("[ ");
	//         p_subscript->index->accept_visitor(this);
	// 	push_text(" ]");
	// }
}

void NodeWalkerVisitor::visit_suite(const GDScriptASTNodes::SuiteNode *p_suite) {
	for (const GDScriptASTNodes::Node *stmt : p_suite->statements) {
		stmt->accept_visitor(this);
	}
}

void NodeWalkerVisitor::visit_ternary_op(const GDScriptASTNodes::TernaryOpNode *p_ternary_op) {
	p_ternary_op->true_expr->accept_visitor(this);
	p_ternary_op->condition->accept_visitor(this);
	p_ternary_op->false_expr->accept_visitor(this);
}

void NodeWalkerVisitor::visit_type(const GDScriptASTNodes::TypeNode *p_type) {
	for (uint32_t i = 0; i < p_type->type_chain.size(); i++) {
		p_type->type_chain[i]->accept_visitor(this);
	}
}

void NodeWalkerVisitor::visit_type_test(const GDScriptASTNodes::TypeTestNode *p_type_test) {
	p_type_test->operand->accept_visitor(this);
	p_type_test->test_type->accept_visitor(this);
}

void NodeWalkerVisitor::visit_unary_op(const GDScriptASTNodes::UnaryOpNode *p_unary_op) {
	p_unary_op->operand->accept_visitor(this);
}

void NodeWalkerVisitor::visit_variable(const GDScriptASTNodes::VariableNode *p_variable) {
	for (const GDScriptASTNodes::AnnotationNode *E : p_variable->annotations) {
		E->accept_visitor(this);
	}
	p_variable->identifier->accept_visitor(this);
	if (p_variable->datatype_specifier != nullptr) {
		p_variable->datatype_specifier->accept_visitor(this);
	}
	if (p_variable->initializer != nullptr) {
		p_variable->initializer->accept_visitor(this);
	}

	if (p_variable->getter != nullptr) {
		if (p_variable->property == GDScriptASTNodes::VariableNode::PROP_INLINE) {
			p_variable->getter->body->accept_visitor(this);
		} else {
			p_variable->getter_pointer->accept_visitor(this);
		}
	}
	if (p_variable->setter != nullptr) {
		if (p_variable->property == GDScriptASTNodes::VariableNode::PROP_INLINE) {
			if (p_variable->setter_parameter != nullptr) {
				p_variable->setter_parameter->accept_visitor(this);
			}
			p_variable->setter->body->accept_visitor(this);
		} else {
			p_variable->setter_pointer->accept_visitor(this);
		}
	}
}

void NodeWalkerVisitor::visit_while(const GDScriptASTNodes::WhileNode *p_while) {
	p_while->condition->accept_visitor(this);
	p_while->loop->accept_visitor(this);
}
