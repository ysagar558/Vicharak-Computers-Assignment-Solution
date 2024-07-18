#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

// Assuming Token and TokenType are defined as in the lexer example

struct ASTNode {
    TokenType type;
    std::string value;
    std::vector<ASTNode*> children;
};

class Parser {
public:
    Parser(const std::vector<Token>& tokens) : tokens(tokens), currentTokenIndex(0) {}
    
    ASTNode* parse() {
        return parseStatements();
    }
    
private:
    std::vector<Token> tokens;
    int currentTokenIndex;
    
    Token currentToken() {
        if (currentTokenIndex < tokens.size()) {
            return tokens[currentTokenIndex];
        } else {
            Token eofToken = { TOKEN_EOF, "" };
            return eofToken;
        }
    }
    
    void advance() {
        currentTokenIndex++;
    }
    
    ASTNode* parseStatements() {
        ASTNode* node = new ASTNode{ TOKEN_UNKNOWN, "", {} };
        while (currentToken().type != TOKEN_EOF) {
            node->children.push_back(parseStatement());
        }
        return node;
    }
    
    ASTNode* parseStatement() {
        Token token = currentToken();
        if (token.type == TOKEN_INT) {
            return parseVariableDeclaration();
        } else if (token.type == TOKEN_IDENTIFIER) {
            return parseAssignment();
        } else if (token.type == TOKEN_IF) {
            return parseConditional();
        } else {
            std::cerr << "Syntax error: Unexpected token " << token.text << std::endl;
            exit(1);
        }
    }
    
    ASTNode* parseVariableDeclaration() {
        advance(); // consume 'int'
        Token identifier = currentToken();
        advance(); // consume identifier
        ASTNode* node = new ASTNode{ TOKEN_INT, "int", {} };
        node->children.push_back(new ASTNode{ TOKEN_IDENTIFIER, identifier.text, {} });
        if (currentToken().type != TOKEN_SEMICOLON) {
            std::cerr << "Syntax error: Expected ';' after variable declaration" << std::endl;
            exit(1);
        }
        advance(); // consume ';'
        return node;
    }
    
    ASTNode* parseAssignment() {
        Token identifier = currentToken();
        advance(); // consume identifier
        if (currentToken().type != TOKEN_ASSIGN) {
            std::cerr << "Syntax error: Expected '=' after identifier" << std::endl;
            exit(1);
        }
        advance(); // consume '='
        ASTNode* expr = parseExpression();
        if (currentToken().type != TOKEN_SEMICOLON) {
            std::cerr << "Syntax error: Expected ';' after expression" << std::endl;
            exit(1);
        }
        advance(); // consume ';'
        ASTNode* node = new ASTNode{ TOKEN_ASSIGN, "=", {} };
        node->children.push_back(new ASTNode{ TOKEN_IDENTIFIER, identifier.text, {} });
        node->children.push_back(expr);
        return node;
    }
    
    ASTNode* parseConditional() {
        advance(); // consume 'if'
        if (currentToken().type != TOKEN_LBRACE) {
            std::cerr << "Syntax error: Expected '(' after 'if'" << std::endl;
            exit(1);
        }
        advance(); // consume '('
        ASTNode* condition = parseExpression();
        if (currentToken().type != TOKEN_RBRACE) {
            std::cerr << "Syntax error: Expected ')' after condition" << std::endl;
            exit(1);
        }
        advance(); // consume ')'
        if (currentToken().type != TOKEN_LBRACE) {
            std::cerr << "Syntax error: Expected '{' after condition" << std::endl;
            exit(1);
        }
        advance(); // consume '{'
        ASTNode* statements = parseStatements();
        if (currentToken().type != TOKEN_RBRACE) {
            std::cerr << "Syntax error: Expected '}' after statements" << std::endl;
            exit(1);
        }
        advance(); // consume '}'
        ASTNode* node = new ASTNode{ TOKEN_IF, "if", {} };
        node->children.push_back(condition);
        node->children.push_back(statements);
        return node;
    }
    
    ASTNode* parseExpression() {
        ASTNode* node = parseTerm();
        while (currentToken().type == TOKEN_PLUS || currentToken().type == TOKEN_MINUS) {
            Token op = currentToken();
            advance(); // consume operator
            ASTNode* right = parseTerm();
            ASTNode* newNode = new ASTNode{ op.type, op.text, {} };
            newNode->children.push_back(node);
            newNode->children.push_back(right);
            node = newNode;
        }
        return node;
    }
    
    ASTNode* parseTerm() {
        Token token = currentToken();
        if (token.type == TOKEN_NUMBER) {
            advance(); // consume number
            return new ASTNode{ TOKEN_NUMBER, token.text, {} };
        } else if (token.type == TOKEN_IDENTIFIER) {
            advance(); // consume identifier
            return new ASTNode{ TOKEN_IDENTIFIER, token.text, {} };
        } else {
            std::cerr << "Syntax error: Unexpected token " << token.text << std::endl;
            exit(1);
        }
    }
};

int main() {
    // Example usage with tokens
    std::vector<Token> tokens = {
        { TOKEN_INT, "int" }, { TOKEN_IDENTIFIER, "a" }, { TOKEN_SEMICOLON, ";" },
        { TOKEN_INT, "int" }, { TOKEN_IDENTIFIER, "b" }, { TOKEN_SEMICOLON, ";" },
        { TOKEN_INT, "int" }, { TOKEN_IDENTIFIER, "c" }, { TOKEN_SEMICOLON, ";" },
        { TOKEN_IDENTIFIER, "a" }, { TOKEN_ASSIGN, "=" }, { TOKEN_NUMBER, "10" }, { TOKEN_SEMICOLON, ";" },
        { TOKEN_IDENTIFIER, "b" }, { TOKEN_ASSIGN, "=" }, { TOKEN_NUMBER, "20" }, { TOKEN_SEMICOLON, ";" },
        { TOKEN_IDENTIFIER, "c" }, { TOKEN_ASSIGN, "=" }, { TOKEN_IDENTIFIER, "a" }, { TOKEN_PLUS, "+" }, { TOKEN_IDENTIFIER, "b" }, { TOKEN_SEMICOLON, ";" },
        { TOKEN_IF, "if" }, { TOKEN_LBRACE, "(" }, { TOKEN_IDENTIFIER, "c" }, { TOKEN_EQUAL, "==" }, { TOKEN_NUMBER, "30" }, { TOKEN_RBRACE, ")" },
        { TOKEN_LBRACE, "{" }, { TOKEN_IDENTIFIER, "c" }, { TOKEN_ASSIGN, "=" }, { TOKEN_IDENTIFIER, "c" }, { TOKEN_PLUS, "+" }, { TOKEN_NUMBER, "1" }, { TOKEN_SEMICOLON, ";" }, { TOKEN_RBRACE, "}" },
        { TOKEN_EOF, "" }
    };

    Parser parser(tokens);
    ASTNode* ast = parser.parse();
    // Further processing of the AST
    return 0;
}
