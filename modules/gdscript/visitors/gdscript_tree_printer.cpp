/**************************************************************************/
/*  gdscript_tree_printer.cpp                                             */
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

#include "gdscript_tree_printer.h"

void TreePrinter::increase_indent() {
	indent_level++;
	indent = "";
	for (int i = 0; i < indent_level * 4; i++) {
		if (i % 4 == 0) {
			indent += "|";
		} else {
			indent += " ";
		}
	}
}

void TreePrinter::decrease_indent() {
	indent_level--;
	indent = "";
	for (int i = 0; i < indent_level * 4; i++) {
		if (i % 4 == 0) {
			indent += "|";
		} else {
			indent += " ";
		}
	}
}

void TreePrinter::push_line(const String &p_line) {
	if (!p_line.is_empty()) {
		push_text(p_line);
	}
	printed += "\n";
	pending_indent = true;
}

void TreePrinter::push_text(const String &p_text) {
	if (pending_indent) {
		printed += indent;
		pending_indent = false;
	}
	printed += p_text;
}

void TreePrinter::visit_annotation(const GDScriptASTNodes::AnnotationNode *p_annotation) {
	push_text(p_annotation->name);
	push_text(" (");
	for (uint32_t i = 0; i < p_annotation->arguments.size(); i++) {
		if (i > 0) {
			push_text(" , ");
		}
		p_annotation->arguments[i]->accept_visitor(this);
	}
	push_line(")");
}

void TreePrinter::visit_array(const GDScriptASTNodes::ArrayNode *p_array) {
	push_text("[ ");
	for (uint32_t i = 0; i < p_array->elements.size(); i++) {
		if (i > 0) {
			push_text(" , ");
		}
		p_array->elements[i]->accept_visitor(this);
	}
	push_text(" ]");
}

void TreePrinter::visit_assert(const GDScriptASTNodes::AssertNode *p_assert) {
	push_text("Assert ( ");
	p_assert->condition->accept_visitor(this);
	push_line(" )");
}

void TreePrinter::visit_assignment(const GDScriptASTNodes::AssignmentNode *p_assignment) {
	p_assignment->assignee->accept_visitor(this);

	push_text(" ");
	switch (p_assignment->operation) {
		case GDScriptASTNodes::AssignmentNode::OP_ADDITION:
			push_text("+");
			break;
		case GDScriptASTNodes::AssignmentNode::OP_SUBTRACTION:
			push_text("-");
			break;
		case GDScriptASTNodes::AssignmentNode::OP_MULTIPLICATION:
			push_text("*");
			break;
		case GDScriptASTNodes::AssignmentNode::OP_DIVISION:
			push_text("/");
			break;
		case GDScriptASTNodes::AssignmentNode::OP_MODULO:
			push_text("%");
			break;
		case GDScriptASTNodes::AssignmentNode::OP_POWER:
			push_text("**");
			break;
		case GDScriptASTNodes::AssignmentNode::OP_BIT_SHIFT_LEFT:
			push_text("<<");
			break;
		case GDScriptASTNodes::AssignmentNode::OP_BIT_SHIFT_RIGHT:
			push_text(">>");
			break;
		case GDScriptASTNodes::AssignmentNode::OP_BIT_AND:
			push_text("&");
			break;
		case GDScriptASTNodes::AssignmentNode::OP_BIT_OR:
			push_text("|");
			break;
		case GDScriptASTNodes::AssignmentNode::OP_BIT_XOR:
			push_text("^");
			break;
		case GDScriptASTNodes::AssignmentNode::OP_NONE:
			break;
	}
	push_text("= ");
	p_assignment->assigned_value->accept_visitor(this);
	push_line();
}

void TreePrinter::visit_await(const GDScriptASTNodes::AwaitNode *p_await) {
	push_text("Await ");
	p_await->to_await->accept_visitor(this);
}

void TreePrinter::visit_binary_op(const GDScriptASTNodes::BinaryOpNode *p_binary_op) {
	// Surround in parenthesis for disambiguation.
	push_text("(");
	p_binary_op->left_operand->accept_visitor(this);
	switch (p_binary_op->operation) {
		case GDScriptASTNodes::BinaryOpNode::OP_ADDITION:
			push_text(" + ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_SUBTRACTION:
			push_text(" - ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_MULTIPLICATION:
			push_text(" * ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_DIVISION:
			push_text(" / ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_MODULO:
			push_text(" % ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_POWER:
			push_text(" ** ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_BIT_LEFT_SHIFT:
			push_text(" << ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_BIT_RIGHT_SHIFT:
			push_text(" >> ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_BIT_AND:
			push_text(" & ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_BIT_OR:
			push_text(" | ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_BIT_XOR:
			push_text(" ^ ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_LOGIC_AND:
			push_text(" AND ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_LOGIC_OR:
			push_text(" OR ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_CONTENT_TEST:
			push_text(" IN ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_COMP_EQUAL:
			push_text(" == ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_COMP_NOT_EQUAL:
			push_text(" != ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_COMP_LESS:
			push_text(" < ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_COMP_LESS_EQUAL:
			push_text(" <= ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_COMP_GREATER:
			push_text(" > ");
			break;
		case GDScriptASTNodes::BinaryOpNode::OP_COMP_GREATER_EQUAL:
			push_text(" >= ");
			break;
	}
	p_binary_op->right_operand->accept_visitor(this);
	// Surround in parenthesis for disambiguation.
	push_text(")");
}

void TreePrinter::visit_break(const GDScriptASTNodes::BreakNode *p_break) {
	push_line("Break");
}

void TreePrinter::visit_breakpoint(const GDScriptASTNodes::BreakpointNode *p_breakpoint) {
	push_line("Breakpoint");
}

void TreePrinter::visit_call(const GDScriptASTNodes::CallNode *p_call) {
	if (p_call->is_super) {
		push_text("super");
		if (p_call->callee != nullptr) {
			push_text(".");
			p_call->callee->accept_visitor(this);
		}
	} else {
		p_call->callee->accept_visitor(this);
	}
	push_text("( ");
	for (uint32_t i = 0; i < p_call->arguments.size(); i++) {
		if (i > 0) {
			push_text(" , ");
		}
		p_call->arguments[i]->accept_visitor(this);
	}
	push_text(" )");
}

void TreePrinter::visit_cast(const GDScriptASTNodes::CastNode *p_cast) {
	p_cast->operand->accept_visitor(this);
	push_text(" AS ");
	p_cast->cast_type->accept_visitor(this);
}

void TreePrinter::visit_class(const GDScriptASTNodes::ClassNode *p_class) {
	for (const GDScriptASTNodes::AnnotationNode *E : p_class->annotations) {
		E->accept_visitor(this);
	}
	push_text("Class ");
	if (p_class->identifier == nullptr) {
		push_text("<unnamed>");
	} else {
		p_class->identifier->accept_visitor(this);
	}

	if (p_class->extends_used) {
		bool first = true;
		push_text(" Extends ");
		if (!p_class->extends_path.is_empty()) {
			push_text(vformat(R"("%s")", p_class->extends_path));
			first = false;
		}
		for (int i = 0; i < p_class->extends.size(); i++) {
			if (!first) {
				push_text(".");
			} else {
				first = false;
			}
			push_text(p_class->extends[i]->name);
		}
	}

	push_line(" :");

	increase_indent();

	for (const GDScriptASTNodes::ClassNode::Member &m : p_class->members) {
		switch (m.type) {
			case GDScriptASTNodes::ClassNode::Member::CLASS:
				visit_class(m.m_class);
				break;
			case GDScriptASTNodes::ClassNode::Member::VARIABLE:
				visit_variable(m.variable);
				break;
			case GDScriptASTNodes::ClassNode::Member::CONSTANT:
				visit_constant(m.constant);
				break;
			case GDScriptASTNodes::ClassNode::Member::SIGNAL:
				visit_signal(m.signal);
				break;
			case GDScriptASTNodes::ClassNode::Member::FUNCTION:
				visit_function(m.function);
				break;
			case GDScriptASTNodes::ClassNode::Member::ENUM:
				visit_enum(m.m_enum);
				break;
			case GDScriptASTNodes::ClassNode::Member::ENUM_VALUE:
				break; // Nothing. Will be printed by enum.
			case GDScriptASTNodes::ClassNode::Member::GROUP:
				break; // Nothing. Groups are only used by inspector.
			case GDScriptASTNodes::ClassNode::Member::UNDEFINED:
				push_line("<unknown member>");
				break;
		}
	}

	decrease_indent();
}

void TreePrinter::visit_constant(const GDScriptASTNodes::ConstantNode *p_constant) {
	push_text("Constant ");
	p_constant->identifier->accept_visitor(this);

	increase_indent();

	push_line();
	push_text("= ");
	if (p_constant->initializer == nullptr) {
		push_text("<missing value>");
	} else {
		p_constant->initializer->accept_visitor(this);
	}
	decrease_indent();
	push_line();
}

void TreePrinter::visit_continue(const GDScriptASTNodes::ContinueNode *p_continue) {
	push_line("Continue");
}

void TreePrinter::visit_dictionary(const GDScriptASTNodes::DictionaryNode *p_dictionary) {
	push_line("{");
	increase_indent();
	for (const GDScriptASTNodes::DictionaryNode::Pair &element : p_dictionary->elements) {
		element.key->accept_visitor(this);
		if (p_dictionary->style == GDScriptASTNodes::DictionaryNode::PYTHON_DICT) {
			push_text(" : ");
		} else {
			push_text(" = ");
		}
		element.value->accept_visitor(this);
		push_line(" ,");
	}
	decrease_indent();
	push_text("}");
}

void TreePrinter::visit_expression(const GDScriptASTNodes::ExpressionNode *p_expression) {
	if (p_expression == nullptr) {
		push_text("<invalid expression>");
		return;
	}
	p_expression->accept_visitor(this);
}

void TreePrinter::visit_enum(const GDScriptASTNodes::EnumNode *p_enum) {
	push_text("Enum ");
	if (p_enum->identifier != nullptr) {
		p_enum->identifier->accept_visitor(this);
	} else {
		push_text("<unnamed>");
	}

	push_line(" {");
	increase_indent();
	for (const GDScriptASTNodes::EnumNode::Value &item : p_enum->values) {
		item.identifier->accept_visitor(this);
		push_text(" = ");
		push_text(itos(item.value));
		push_line(" ,");
	}
	decrease_indent();
	push_line("}");
}

void TreePrinter::visit_for(const GDScriptASTNodes::ForNode *p_for) {
	push_text("For ");
	p_for->variable->accept_visitor(this);
	push_text(" IN ");
	p_for->list->accept_visitor(this);
	push_line(" :");

	increase_indent();

	p_for->loop->accept_visitor(this);

	decrease_indent();
}

void TreePrinter::visit_function(const GDScriptASTNodes::FunctionNode *p_function) {
	for (const GDScriptASTNodes::AnnotationNode *E : p_function->annotations) {
		E->accept_visitor(this);
	}
	if (p_function->is_static) {
		push_text("Static ");
	}
	push_text(" ");
	if (p_function->identifier) {
		p_function->identifier->accept_visitor(this);
	} else {
		push_text("<anonymous>");
	}
	push_text("( ");
	for (uint32_t i = 0; i < p_function->parameters.size(); i++) {
		if (i > 0) {
			push_text(" , ");
		}
		p_function->parameters[i]->accept_visitor(this);
	}
	push_line(" ) :");
	increase_indent();
	p_function->body->accept_visitor(this);
	decrease_indent();
}

void TreePrinter::visit_get_node(const GDScriptASTNodes::GetNodeNode *p_get_node) {
	if (p_get_node->use_dollar) {
		push_text("$");
	}
	push_text(p_get_node->full_path);
}

void TreePrinter::visit_identifier(const GDScriptASTNodes::IdentifierNode *p_identifier) {
	if (p_identifier != nullptr) {
		push_text(p_identifier->name);
	} else {
		push_text("<invalid identifier>");
	}
}

void TreePrinter::visit_if(const GDScriptASTNodes::IfNode *p_if) {
	push_text("If ");
	p_if->condition->accept_visitor(this);
	push_line(" :");

	increase_indent();
	p_if->true_block->accept_visitor(this);
	decrease_indent();

	// FIXME: Properly detect "elif" blocks.
	if (p_if->false_block != nullptr) {
		push_line("Else :");
		increase_indent();
		p_if->false_block->accept_visitor(this);
		decrease_indent();
	}
}

void TreePrinter::visit_lambda(const GDScriptASTNodes::LambdaNode *p_lambda) {
	push_text("Lambda");
	p_lambda->function->accept_visitor(this);
	push_text("| captures [ ");
	for (uint32_t i = 0; i < p_lambda->captures.size(); i++) {
		if (i > 0) {
			push_text(" , ");
		}
		push_text(p_lambda->captures[i]->name.string());
	}
	push_line(" ]");
}

void TreePrinter::visit_literal(const GDScriptASTNodes::LiteralNode *p_literal) {
	// Prefix for string types.
	switch (p_literal->value.get_type()) {
		case Variant::NODE_PATH:
			push_text("^\"");
			break;
		case Variant::STRING:
			push_text("\"");
			break;
		case Variant::STRING_NAME:
			push_text("&\"");
			break;
		default:
			break;
	}
	push_text(p_literal->value);
	// Suffix for string types.
	switch (p_literal->value.get_type()) {
		case Variant::NODE_PATH:
		case Variant::STRING:
		case Variant::STRING_NAME:
			push_text("\"");
			break;
		default:
			break;
	}
}

void TreePrinter::visit_match(const GDScriptASTNodes::MatchNode *p_match) {
	push_text("Match ");
	p_match->test->accept_visitor(this);
	push_line(" :");

	increase_indent();
	for (const GDScriptASTNodes::MatchBranchNode *branch : p_match->branches) {
		branch->accept_visitor(this);
	}
	decrease_indent();
}

void TreePrinter::visit_match_branch(const GDScriptASTNodes::MatchBranchNode *p_match_branch) {
	for (uint32_t i = 0; i < p_match_branch->patterns.size(); i++) {
		if (i > 0) {
			push_text(" , ");
		}
		p_match_branch->patterns[i]->accept_visitor(this);
	}

	push_line(" :");

	increase_indent();
	p_match_branch->block->accept_visitor(this);
	decrease_indent();
}

void TreePrinter::visit_match_pattern(const GDScriptASTNodes::PatternNode *p_match_pattern) {
	switch (p_match_pattern->pattern_type) {
		case GDScriptASTNodes::PatternNode::PT_LITERAL:
			p_match_pattern->literal->accept_visitor(this);
			break;
		case GDScriptASTNodes::PatternNode::PT_WILDCARD:
			push_text("_");
			break;
		case GDScriptASTNodes::PatternNode::PT_REST:
			push_text("..");
			break;
		case GDScriptASTNodes::PatternNode::PT_BIND:
			push_text("Var ");
			p_match_pattern->bind->accept_visitor(this);
			break;
		case GDScriptASTNodes::PatternNode::PT_EXPRESSION:
			p_match_pattern->expression->accept_visitor(this);
			break;
		case GDScriptASTNodes::PatternNode::PT_ARRAY:
			push_text("[ ");
			for (uint32_t i = 0; i < p_match_pattern->array.size(); i++) {
				if (i > 0) {
					push_text(" , ");
				}
				p_match_pattern->array[i]->accept_visitor(this);
			}
			push_text(" ]");
			break;
		case GDScriptASTNodes::PatternNode::PT_DICTIONARY:
			push_text("{ ");
			for (uint32_t i = 0; i < p_match_pattern->dictionary.size(); i++) {
				if (i > 0) {
					push_text(" , ");
				}
				if (p_match_pattern->dictionary[i].key != nullptr) {
					// Key can be null for rest pattern.
					p_match_pattern->dictionary[i].key->accept_visitor(this);
					if (p_match_pattern->dictionary[i].value_pattern != nullptr) {
						// Value can be null when only matching key.
						push_text(" : ");
						p_match_pattern->dictionary[i].value_pattern->accept_visitor(this);
					}
				}
			}
			push_text(" }");
			break;
	}
}

void TreePrinter::visit_node(const GDScriptASTNodes::Node *p_node) {
	push_line(vformat("<unknown expression or statement statement %d>", p_node->type));
}

void TreePrinter::visit_parameter(const GDScriptASTNodes::ParameterNode *p_parameter) {
	p_parameter->identifier->accept_visitor(this);
	if (p_parameter->datatype_specifier != nullptr) {
		push_text(" : ");
		p_parameter->datatype_specifier->accept_visitor(this);
	}
	if (p_parameter->initializer != nullptr) {
		push_text(" = ");
		p_parameter->initializer->accept_visitor(this);
	}
}

void TreePrinter::visit_pass(const GDScriptASTNodes::PassNode *p_pass) {
	push_line("Pass");
}

void TreePrinter::visit_preload(const GDScriptASTNodes::PreloadNode *p_preload) {
	push_text(R"(Preload ( ")");
	push_text(p_preload->resolved_path);
	push_text(R"(" )");
}

void TreePrinter::visit_return(const GDScriptASTNodes::ReturnNode *p_return) {
	push_text("Return");
	if (p_return->return_value != nullptr) {
		push_text(" ");
		p_return->return_value->accept_visitor(this);
	}
	push_line();
}

void TreePrinter::visit_self(const GDScriptASTNodes::SelfNode *p_self) {
	push_text("Self(");
	if (p_self->current_class->identifier != nullptr) {
		p_self->current_class->identifier->accept_visitor(this);
	} else {
		push_text("<main class>");
	}
	push_text(")");
}

void TreePrinter::visit_signal(const GDScriptASTNodes::SignalNode *p_signal) {
	push_text("Signal ");
	p_signal->identifier->accept_visitor(this);
	push_text("( ");
	for (const GDScriptASTNodes::ParameterNode *param : p_signal->parameters) {
		param->accept_visitor(this);
	}
	push_line(" )");
}

void TreePrinter::visit_subscript(const GDScriptASTNodes::SubscriptNode *p_subscript) {
	p_subscript->base->accept_visitor(this);
	if (p_subscript->is_attribute) {
		push_text(".");
		p_subscript->attribute->accept_visitor(this);
	} else {
		push_text("[ ");
		p_subscript->index->accept_visitor(this);
		push_text(" ]");
	}
}

void TreePrinter::visit_suite(const GDScriptASTNodes::SuiteNode *p_suite) {
	for (const GDScriptASTNodes::Node *stmt : p_suite->statements) {
		stmt->accept_visitor(this);
		if (stmt->is_expression()) {
			push_line();
		}
	}
}

void TreePrinter::visit_ternary_op(const GDScriptASTNodes::TernaryOpNode *p_ternary_op) {
	// Surround in parenthesis for disambiguation.
	push_text("(");
	p_ternary_op->true_expr->accept_visitor(this);
	push_text(") IF (");
	p_ternary_op->condition->accept_visitor(this);
	push_text(") ELSE (");
	p_ternary_op->false_expr->accept_visitor(this);
	push_text(")");
}

void TreePrinter::visit_type(const GDScriptASTNodes::TypeNode *p_type) {
	if (p_type->type_chain.is_empty()) {
		push_text("Void");
	} else {
		for (uint32_t i = 0; i < p_type->type_chain.size(); i++) {
			if (i > 0) {
				push_text(".");
			}
			p_type->type_chain[i]->accept_visitor(this);
		}
	}
}

void TreePrinter::visit_type_test(const GDScriptASTNodes::TypeTestNode *p_test) {
	p_test->operand->accept_visitor(this);
	push_text(" IS ");
	p_test->test_type->accept_visitor(this);
}

void TreePrinter::visit_unary_op(const GDScriptASTNodes::UnaryOpNode *p_unary_op) {
	// Surround in parenthesis for disambiguation.
	push_text("(");
	switch (p_unary_op->operation) {
		case GDScriptASTNodes::UnaryOpNode::OP_POSITIVE:
			push_text("+");
			break;
		case GDScriptASTNodes::UnaryOpNode::OP_NEGATIVE:
			push_text("-");
			break;
		case GDScriptASTNodes::UnaryOpNode::OP_LOGIC_NOT:
			push_text("NOT");
			break;
		case GDScriptASTNodes::UnaryOpNode::OP_COMPLEMENT:
			push_text("~");
			break;
	}
	p_unary_op->operand->accept_visitor(this);
	// Surround in parenthesis for disambiguation.
	push_text(")");
}

void TreePrinter::visit_variable(const GDScriptASTNodes::VariableNode *p_variable) {
	for (const GDScriptASTNodes::AnnotationNode *E : p_variable->annotations) {
		E->accept_visitor(this);
	}

	if (p_variable->is_static) {
		push_text("Static ");
	}
	push_text("Variable ");
	p_variable->identifier->accept_visitor(this);

	push_text(" : ");
	if (p_variable->datatype_specifier != nullptr) {
		p_variable->datatype_specifier->accept_visitor(this);
	} else if (p_variable->infer_datatype) {
		push_text("<inferred type>");
	} else {
		push_text("Variant");
	}

	increase_indent();

	push_line();
	push_text("= ");
	if (p_variable->initializer == nullptr) {
		push_text("<default value>");
	} else {
		p_variable->initializer->accept_visitor(this);
	}
	push_line();

	if (p_variable->property != GDScriptASTNodes::VariableNode::PROP_NONE) {
		if (p_variable->getter != nullptr) {
			push_text("Get");
			if (p_variable->property == GDScriptASTNodes::VariableNode::PROP_INLINE) {
				push_line(":");
				increase_indent();
				p_variable->getter->body->accept_visitor(this);
				decrease_indent();
			} else {
				push_line(" =");
				increase_indent();
				p_variable->getter_pointer->accept_visitor(this);
				push_line();
				decrease_indent();
			}
		}
		if (p_variable->setter != nullptr) {
			push_text("Set (");
			if (p_variable->property == GDScriptASTNodes::VariableNode::PROP_INLINE) {
				if (p_variable->setter_parameter != nullptr) {
					p_variable->setter_parameter->accept_visitor(this);
				} else {
					push_text("<missing>");
				}
				push_line("):");
				increase_indent();
				p_variable->setter->body->accept_visitor(this);
				decrease_indent();
			} else {
				push_line(" =");
				increase_indent();
				p_variable->setter_pointer->accept_visitor(this);
				push_line();
				decrease_indent();
			}
		}
	}

	decrease_indent();
	push_line();
}

void TreePrinter::visit_while(const GDScriptASTNodes::WhileNode *p_while) {
	push_text("While ");
	p_while->condition->accept_visitor(this);
	push_line(" :");

	increase_indent();
	p_while->loop->accept_visitor(this);
	decrease_indent();
}

void TreePrinter::print_tree(const GDScriptASTNodes::ClassNode *class_tree, const bool is_tool) {
	ERR_FAIL_NULL_MSG(class_tree, "Parse the code before printing the parse tree.");

	if (is_tool) {
		push_line("@tool");
	}
	if (!class_tree->icon_path.is_empty()) {
		push_text(R"(@icon (")");
		push_text(class_tree->icon_path);
		push_line("\")");
	}
	class_tree->accept_visitor(this);

	print_line(String(printed));
}
