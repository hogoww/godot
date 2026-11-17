/**************************************************************************/
/*  gdscript_tree_printer.h                                               */
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

#pragma once

#include "../gdscript_ast.h"
#include "gdscript_base_visitor.h"

#include "core/string/string_builder.h"

class TreePrinter : public BaseVisitor {
	int indent_level = 0;
	String indent;
	StringBuilder printed;
	bool pending_indent = false;

	void increase_indent();
	void decrease_indent();
	void push_line(const String &p_line = String());
	void push_text(const String &p_text);

public:
	virtual void visit_annotation(const GDScriptASTNodes::AnnotationNode *p_annotation) override;
	virtual void visit_array(const GDScriptASTNodes::ArrayNode *p_array) override;
	virtual void visit_assert(const GDScriptASTNodes::AssertNode *p_assert) override;
	virtual void visit_assignment(const GDScriptASTNodes::AssignmentNode *p_assignment) override;
	virtual void visit_await(const GDScriptASTNodes::AwaitNode *p_await) override;
	virtual void visit_binary_op(const GDScriptASTNodes::BinaryOpNode *p_binary_op) override;
	virtual void visit_break(const GDScriptASTNodes::BreakNode *p_break) override;
	virtual void visit_breakpoint(const GDScriptASTNodes::BreakpointNode *p_breakpoint) override;
	virtual void visit_call(const GDScriptASTNodes::CallNode *p_call) override;
	virtual void visit_cast(const GDScriptASTNodes::CastNode *p_cast) override;
	virtual void visit_class(const GDScriptASTNodes::ClassNode *p_class) override;
	virtual void visit_constant(const GDScriptASTNodes::ConstantNode *p_constant) override;
	virtual void visit_continue(const GDScriptASTNodes::ContinueNode *p_continue) override;
	virtual void visit_dictionary(const GDScriptASTNodes::DictionaryNode *p_dictionary) override;
	virtual void visit_expression(const GDScriptASTNodes::ExpressionNode *p_expression) override;
	virtual void visit_enum(const GDScriptASTNodes::EnumNode *p_enum) override;
	virtual void visit_for(const GDScriptASTNodes::ForNode *p_for) override;
	virtual void visit_function(const GDScriptASTNodes::FunctionNode *p_function) override;
	virtual void visit_get_node(const GDScriptASTNodes::GetNodeNode *p_get_node) override;
	virtual void visit_if(const GDScriptASTNodes::IfNode *p_if) override;
	virtual void visit_identifier(const GDScriptASTNodes::IdentifierNode *p_identifier) override;
	virtual void visit_lambda(const GDScriptASTNodes::LambdaNode *p_lambda) override;
	virtual void visit_literal(const GDScriptASTNodes::LiteralNode *p_literal) override;
	virtual void visit_match(const GDScriptASTNodes::MatchNode *p_match) override;
	virtual void visit_match_branch(const GDScriptASTNodes::MatchBranchNode *p_match_branch) override;
	virtual void visit_match_pattern(const GDScriptASTNodes::PatternNode *p_match_pattern) override;
	virtual void visit_node(const GDScriptASTNodes::Node *p_node) override;
	virtual void visit_parameter(const GDScriptASTNodes::ParameterNode *p_parameter) override;
	virtual void visit_pass(const GDScriptASTNodes::PassNode *p_pass) override;
	virtual void visit_preload(const GDScriptASTNodes::PreloadNode *p_preload) override;
	virtual void visit_return(const GDScriptASTNodes::ReturnNode *p_return) override;
	virtual void visit_self(const GDScriptASTNodes::SelfNode *p_self) override;
	virtual void visit_signal(const GDScriptASTNodes::SignalNode *p_signal) override;
	virtual void visit_subscript(const GDScriptASTNodes::SubscriptNode *p_subscript) override;
	virtual void visit_suite(const GDScriptASTNodes::SuiteNode *p_suite) override;
	virtual void visit_ternary_op(const GDScriptASTNodes::TernaryOpNode *p_ternary_op) override;
	virtual void visit_type(const GDScriptASTNodes::TypeNode *p_type) override;
	virtual void visit_type_test(const GDScriptASTNodes::TypeTestNode *p_type_test) override;
	virtual void visit_unary_op(const GDScriptASTNodes::UnaryOpNode *p_unary_op) override;
	virtual void visit_variable(const GDScriptASTNodes::VariableNode *p_variable) override;
	virtual void visit_while(const GDScriptASTNodes::WhileNode *p_while) override;
	void print_tree(const GDScriptASTNodes::ClassNode *p_parser, const bool is_tool);
};
