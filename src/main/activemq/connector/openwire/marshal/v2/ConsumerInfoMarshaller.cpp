/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <activemq/connector/openwire/marshal/v2/ConsumerInfoMarshaller.h>

#include <activemq/connector/openwire/commands/ConsumerInfo.h>

//
//     NOTE!: This file is autogenerated - do not modify!
//            if you need to make a change, please see the Java Classes in the
//            activemq-core module
//

using namespace std;
using namespace activemq;
using namespace activemq::io;
using namespace activemq::connector;
using namespace activemq::connector::openwire;
using namespace activemq::connector::openwire::commands;
using namespace activemq::connector::openwire::marshal;
using namespace activemq::connector::openwire::util;
using namespace activemq::connector::openwire::marshal::v2;

///////////////////////////////////////////////////////////////////////////////
DataStructure* ConsumerInfoMarshaller::createObject() const {
    return new ConsumerInfo();
}

///////////////////////////////////////////////////////////////////////////////
unsigned char ConsumerInfoMarshaller::getDataStructureType() const {
    return ConsumerInfo::ID_CONSUMERINFO;
}

///////////////////////////////////////////////////////////////////////////////
void ConsumerInfoMarshaller::tightUnmarshal( OpenWireFormat* wireFormat, DataStructure* dataStructure, DataInputStream* dataIn, BooleanStream* bs ) {
   BaseCommandMarshaller::tightUnmarshal( wireFormat, dataStructure, dataIn, bs );

    ConsumerInfo* info =
        dynamic_cast<ConsumerInfo*>( dataStructure );
    info->setConsumerId( dynamic_cast< ConsumerId* >(
        tightUnmarsalCachedObject( wireFormat, dataIn, bs ) );
    info->setBrowser( bs->readBoolean() );
    info->setDestination( dynamic_cast< ActiveMQDestination* >(
        tightUnmarsalCachedObject( wireFormat, dataIn, bs ) );
    info->setPrefetchSize( dataIn->readInt() );
    info->setMaximumPendingMessageLimit( dataIn->readInt() );
    info->setDispatchAsync( bs->readBoolean() );
    info->setSelector( TightUnmarshalString( dataIn, bs ) );
    info->setSubscriptionName( TightUnmarshalString( dataIn, bs ) );
    info->setNoLocal( bs->readBoolean() );
    info->setExclusive( bs->readBoolean() );
    info->setRetroactive( bs->readBoolean() );
    info->setPriority( dataIn->readByte() );

    if( bs->readBoolean() ) {
        short size = dataIn->readShort();
        BrokerId* value = new BrokerId[size];
        for( int i = 0; i < size; i++ ) {
            value[i] = dynamic_cast< BrokerId* >(
                tightUnmarsalNestedObject( wireFormat, dataIn, bs ) );
        }
        info->setBrokerPath( value );
    }
    else {
        info->setBrokerPath( NULL );
    }
    info->setAdditionalPredicate( dynamic_cast< BooleanExpression* >(
        tightUnmarsalNestedObject( wireFormat, dataIn, bs ) );
    info->setNetworkSubscription( bs->readBoolean() );
    info->setOptimizedAcknowledge( bs->readBoolean() );
    info->setNoRangeAcks( bs->readBoolean() );
}

///////////////////////////////////////////////////////////////////////////////
int ConsumerInfoMarshaller::tightMarshal1( OpenWireFormat& wireFormat, DataStructure* dataStructure, BooleanStream& bs ) {

    ConsumerInfo* info =
        dynamic_cast<ConsumerInfo*>( dataStructure );

    int rc = BaseCommandMarshaller::tightMarshal1( wireFormat, dataStructure, bs );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getConsumerId() );

    rc += tightMarshalCachedObject1( wireFormat, data, bs );
    bs->writeBoolean( info->isBrowser() );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getDestination() );

    rc += tightMarshalCachedObject1( wireFormat, data, bs );
    bs->writeBoolean( info->isDispatchAsync() );
    rc += tightMarshalString1( info->getSelector(), bs );
    rc += tightMarshalString1( info->getSubscriptionName(), bs );
    bs->writeBoolean( info->isNoLocal() );
    bs->writeBoolean( info->isExclusive() );
    bs->writeBoolean( info->isRetroactive() );
    rc += tightMarshalObjectArray1( wireFormat, info->getBrokerPath(), bs );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getAdditionalPredicate() );

    rc += tightMarshalNestedObject1( wireFormat, data, bs );
    bs->writeBoolean( info->isNetworkSubscription() );
    bs->writeBoolean( info->isOptimizedAcknowledge() );
    bs->writeBoolean( info->isNoRangeAcks() );

    return rc + 9;
}

///////////////////////////////////////////////////////////////////////////////
void ConsumerInfoMarshaller::tightMarshal2( OpenWireFormat& wireFormat, DataStructure* dataStructure, DataOutputStream& dataOut, BooleanStream& bs ) {

    BaseCommandMarshaller::tightMarshal2( wireFormat, dataStructure, dataOut, bs );

    ConsumerInfo* info =
        dynamic_cast<ConsumerInfo*>( dataStructure );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getConsumerId() );

    tightMarshalCachedObject2( wireFormat, data, dataOut, bs );
    bs->readBoolean();
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getDestination() );

    tightMarshalCachedObject2( wireFormat, data, dataOut, bs );
    dataOut->write( info->getPrefetchSize() );
    dataOut->write( info->getMaximumPendingMessageLimit() );
    bs->readBoolean();
    tightMarshalString2( info->getSelector(), dataOut, bs );
    tightMarshalString2( info->getSubscriptionName(), dataOut, bs );
    bs->readBoolean();
    bs->readBoolean();
    bs->readBoolean();
    dataOut->write( info->getPriority() );
    tightMarshalObjectArray2( wireFormat, info->getBrokerPath(), dataOut, bs );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getAdditionalPredicate() );

    tightMarshalNestedObject2( wireFormat, data, dataOut, bs );
    bs->readBoolean();
    bs->readBoolean();
    bs->readBoolean();
}

///////////////////////////////////////////////////////////////////////////////
void ConsumerInfoMarshaller::looseUnmarshal( OpenWireFormat& wireFormat, DataStructure* dataStructure, DataInputStream& dataIn ) {
    BaseCommandMarshaller::looseUnmarshal( wireFormat, dataStructure, dataIn );
    ConsumerInfo* info = 
        dynamic_cast<ConsumerInfo*>( dataStructure );
   info->setConsumerId( dynamic_cast<ConsumerId* >( 
       looseUnmarshalCachedObject( wireFormat, dataIn ) ) );
    info->setBrowser( dataIn->readBoolean() );
   info->setDestination( dynamic_cast<ActiveMQDestination* >( 
       looseUnmarshalCachedObject( wireFormat, dataIn ) ) );
    info->setPrefetchSize( dataIn->readInt() );
    info->setMaximumPendingMessageLimit( dataIn->readInt() );
    info->setDispatchAsync( dataIn->readBoolean() );
    info->setSelector( looseUnmarshalString( dataIn ) );
    info->setSubscriptionName( looseUnmarshalString( dataIn ) );
    info->setNoLocal( dataIn->readBoolean() );
    info->setExclusive( dataIn->readBoolean() );
    info->setRetroactive( dataIn->readBoolean() );
    info->setPriority( dataIn->readByte() );

    if( dataIn->readBoolean() ) {
        short size = dataIn->readShort();
        BrokerId* value = new BrokerId[size];
        for( int i = 0; i < size; i++ ) {
            value[i] = dynamic_cast<BrokerId* >(
                looseUnmarshalNestedObject( wireFormat,dataIn ) );
        }
        info->setBrokerPath( value );
    }
    else {
        info->setBrokerPath( NULL );
    }
   info->setAdditionalPredicate( dynamic_cast<BooleanExpression* >( 
       looseUnmarshalNestedObject( wireFormat, dataIn ) ) );
    info->setNetworkSubscription( dataIn->readBoolean() );
    info->setOptimizedAcknowledge( dataIn->readBoolean() );
    info->setNoRangeAcks( dataIn->readBoolean() );
}

///////////////////////////////////////////////////////////////////////////////
void ConsumerInfoMarshaller::looseMarshal( OpenWireFormat& wireFormat, DataStructure* dataStructure, DataOutputStream& dataOut ) {
    ConsumerInfo* info =
        dynamic_cast<ConsumerInfo*>( dataStructure );
    BaseCommandMarshaller::looseMarshal( wireFormat, dataStructure, dataOut );

    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getConsumerId() );

    looseMarshalCachedObject( wireFormat, data, dataOut );
    dataOut->write( info->isBrowser() );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getDestination() );

    looseMarshalCachedObject( wireFormat, data, dataOut );
    dataOut->write( info->getPrefetchSize() );
    dataOut->write( info->getMaximumPendingMessageLimit() );
    dataOut->write( info->isDispatchAsync() );
    looseMarshalString( info->getSelector(), dataOut );
    looseMarshalString( info->getSubscriptionName(), dataOut );
    dataOut->write( info->isNoLocal() );
    dataOut->write( info->isExclusive() );
    dataOut->write( info->isRetroactive() );
    dataOut->write( info->getPriority() );
    looseMarshalObjectArray( wireFormat, info->getBrokerPath(), dataOut );
    DataStructure* data = 
        dynamic_cast< DataStructure* >( info->getAdditionalPredicate() );

    looseMarshalNestedObject( wireFormat, data, dataOut );
    dataOut->write( info->isNetworkSubscription() );
    dataOut->write( info->isOptimizedAcknowledge() );
    dataOut->write( info->isNoRangeAcks() );
}

