/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "CheckedInputStream.h"

#include <decaf/lang/Math.h>

using namespace decaf;
using namespace decaf::io;
using namespace decaf::lang;
using namespace decaf::lang::exceptions;
using namespace decaf::util;
using namespace decaf::util::zip;

////////////////////////////////////////////////////////////////////////////////
CheckedInputStream::CheckedInputStream( InputStream* inputStream, Checksum* sum, bool own )
 :  FilterInputStream( inputStream, own ), sum( sum ) {

    if( sum == NULL ) {
        throw NullPointerException(
            __FILE__, __LINE__, "The Checksum instance cannot be NULL." );
    }
}

////////////////////////////////////////////////////////////////////////////////
CheckedInputStream::~CheckedInputStream() {
}

////////////////////////////////////////////////////////////////////////////////
std::size_t CheckedInputStream::skip( std::size_t num ) throw( decaf::io::IOException ) {

    try{

        if( num == 0 ) {
            return 0;
        }

        if( isClosed() ) {
            throw IOException(
                __FILE__, __LINE__, "Stream is Closed." );
        }

        // Perform smaller reads then the indicated amount
        std::size_t remaining = Math::min( (int)num, 2048 );
        std::size_t skipped = 0;

        std::vector<unsigned char> buffer( remaining );

        while( skipped < num ) {

            int result = this->inputStream->read( &buffer[0], remaining );

            if( isClosed() ) {
                throw IOException(
                    __FILE__, __LINE__, "Stream is Closed." );
            }

            if( result == -1 ) {
                return skipped;
            }

            this->sum->update( buffer, 0, remaining );

            skipped += result;
            remaining = ( num - skipped ) > buffer.size() ? buffer.size() : num - skipped;
        }

        return skipped;
    }
    DECAF_CATCH_RETHROW( IOException )
    DECAF_CATCHALL_THROW( IOException )
}

////////////////////////////////////////////////////////////////////////////////
int CheckedInputStream::doReadByte() throw ( decaf::io::IOException ) {

    try{

        if( isClosed() ) {
            throw IOException(
                __FILE__, __LINE__, "Stream is Closed." );
        }

        int result = this->inputStream->read();

        if( result != -1 ) {
            this->sum->update( result );
        }

        return result;
    }
    DECAF_CATCH_RETHROW( IOException )
    DECAF_CATCHALL_THROW( IOException )
}

////////////////////////////////////////////////////////////////////////////////
int CheckedInputStream::doReadArrayBounded( unsigned char* buffer, std::size_t size,
                                            std::size_t offset, std::size_t length )
    throw ( decaf::io::IOException,
            decaf::lang::exceptions::IndexOutOfBoundsException,
            decaf::lang::exceptions::NullPointerException ) {

    try{

        if( buffer == NULL ) {
            throw NullPointerException(
                __FILE__, __LINE__, "Buffer passed was NULL" );
        }

        if( ( offset + length ) > size ) {
            throw IndexOutOfBoundsException(
                __FILE__, __LINE__, "Offset + Length exceeds buffer size." );
        }

        if( length == 0 ) {
            return 0;
        }

        if( isClosed() ) {
            throw IOException(
                __FILE__, __LINE__, "Stream is Closed." );
        }

        int result = this->inputStream->read( buffer, size, offset, length );

        if( result != -1 ) {
            // Only add the amount of bytes actually read to the Checksum.
            this->sum->update( buffer, size, offset, result );
        }

        return result;
    }
    DECAF_CATCH_RETHROW( IOException )
    DECAF_CATCH_RETHROW( IndexOutOfBoundsException )
    DECAF_CATCH_RETHROW( NullPointerException )
    DECAF_CATCHALL_THROW( IOException )
}
