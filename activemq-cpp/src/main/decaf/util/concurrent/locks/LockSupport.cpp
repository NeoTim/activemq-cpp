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

#include "LockSupport.h"

#include <decaf/lang/Exception.h>
#include <decaf/lang/Thread.h>
#include <decaf/lang/System.h>

using namespace decaf;
using namespace decaf::lang;
using namespace decaf::util;
using namespace decaf::util::concurrent;
using namespace decaf::util::concurrent::locks;

////////////////////////////////////////////////////////////////////////////////
LockSupport::LockSupport() {
}

////////////////////////////////////////////////////////////////////////////////
LockSupport::~LockSupport() {
}

////////////////////////////////////////////////////////////////////////////////
void LockSupport::unpark( decaf::lang::Thread* thread ) throw() {

    try{
        Thread::unpark( thread );
    } DECAF_CATCHALL_NOTHROW()
}

////////////////////////////////////////////////////////////////////////////////
void LockSupport::park() throw() {

    try{
        Thread::park( Thread::currentThread() );
    } DECAF_CATCHALL_NOTHROW()
}

////////////////////////////////////////////////////////////////////////////////
void LockSupport::parkNanos( long long nanos ) throw() {

    try{
        Thread::park( Thread::currentThread(), 0, nanos );
    } DECAF_CATCHALL_NOTHROW()
}

////////////////////////////////////////////////////////////////////////////////
void LockSupport::parkUntil( long long deadline ) throw() {

    try{

        long long now = System::currentTimeMillis();

        if( deadline < now ) {
            return;
        }

        Thread::park( Thread::currentThread(), ( deadline - now ), 0 );

    } DECAF_CATCHALL_NOTHROW()
}