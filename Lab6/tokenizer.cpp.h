//
// Created by Alex Hayden van Zuiden-Rylander on 2019-03-01.
//

#ifndef LAB6_TOKENIZER_CPP_H
#define LAB6_TOKENIZER_CPP_H
template <class NumericType>
bool Tokenizer<NumericType>::getChar( char &ch ) {
    char tmp;

    // skip blanks
    while ( in.get( tmp ) && tmp == ' ' );

    // read a char
    if ( in.good( ) && tmp != '\n'&& tmp != '\0' ) {
        ch = tmp;
        return true; // if it is not a delimiter
    }
    else
        return false; // if it's a delimitter
}

template <class NumericType>
Token<NumericType> Tokenizer<NumericType>::getToken( ) {

    char ch;
    NumericType theValue;

    if ( getChar( ch ) == true ) {
        switch( ch ) {
            case '|':
                if (getChar( ch ) == true){

                }
            case '^': return EXP;
            case '/': return DIV;
            case '*': return MULT;
            case '(': return OPAREN;
            case ')': return CPAREN;
            case '+': return PLUS;
            case '-': return MINUS;
            case '<':
                if(getChar(ch) == true){
                    switch(ch){
                        case '<': return (prevToken = SHIFT_L);
                        case '=':
                    }
                }
            default:
                in.putback( ch );
                if ( !( in >> theValue ) ) {
                    cerr << "Parse error" << endl;
                    return EOL;
                }
                return Token<NumericType>( VALUE, theValue );
        }
    }

    return EOL;
}
#endif //LAB6_TOKENIZER_CPP_H
