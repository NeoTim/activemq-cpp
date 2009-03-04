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

#include "FailoverTransportTest.h"

#include <activemq/transport/failover/FailoverTransportFactory.h>
#include <activemq/transport/failover/FailoverTransport.h>
#include <activemq/exceptions/ActiveMQException.h>
#include <decaf/lang/Pointer.h>

using namespace activemq;
using namespace activemq::transport;
using namespace activemq::transport::failover;
using namespace activemq::exceptions;
using namespace decaf::util;

////////////////////////////////////////////////////////////////////////////////
FailoverTransportTest::FailoverTransportTest() {
}

////////////////////////////////////////////////////////////////////////////////
FailoverTransportTest::~FailoverTransportTest() {
}

////////////////////////////////////////////////////////////////////////////////
void FailoverTransportTest::testTransportCreate() {

    std::string uri = "failover://(mock://localhost:61616)?randomize=false";

    FailoverTransportFactory factory;

    Pointer<Transport> transport( factory.create( uri ) );

    CPPUNIT_ASSERT( transport != NULL );

    FailoverTransport* failover = dynamic_cast<FailoverTransport*>(
        transport->narrow( typeid( FailoverTransport ) ) );

    CPPUNIT_ASSERT( failover != NULL );
    CPPUNIT_ASSERT( failover->isRandomize() == false );

    transport->close();
}
