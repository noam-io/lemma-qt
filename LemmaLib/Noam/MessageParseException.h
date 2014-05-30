//Copyright (c) 2014, IDEO 

#ifndef Noam_MESSAGEPARSEEXCEPTION_H
#define Noam_MESSAGEPARSEEXCEPTION_H

#include <stdexcept>

class QString;
class QByteArray;

namespace Noam {

    class MessageParseException
      : public std::runtime_error
    {
    public:
        MessageParseException( const QByteArray& );

        static QString generateErrorMessage( const QByteArray& );
    };
}

#endif
