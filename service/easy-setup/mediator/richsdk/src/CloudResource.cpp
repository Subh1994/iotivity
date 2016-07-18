//******************************************************************
//
// Copyright 2015 Samsung Electronics All Rights Reserved.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#include <functional>

#include "CloudResource.h"

#include "OCPlatform.h"
#include "ESException.h"
#include "OCResource.h"
#include "logger.h"

namespace OIC
{
    namespace Service
    {
        #define ES_CLOUD_RES_TAG "ES_CLOUD_RESOURCE"

        static const char ES_BASE_RES_URI[] = "/oic/res";

        CloudResource::CloudResource(std::shared_ptr< OC::OCResource > resource)
        {
            m_ocResource = resource;
        }

        void CloudResource::provisionEnrollee(const CloudProp& cloudProp)
        {
            OIC_LOG_V (DEBUG, ES_CLOUD_RES_TAG, "Enter provisionEnrollee.");

            OCRepresentation provisioningRepresentation;

            provisioningRepresentation.setValue(OC_RSRVD_ES_AUTHCODE, cloudProp.authCode);
            provisioningRepresentation.setValue(OC_RSRVD_ES_AUTHPROVIDER, cloudProp.authProvider);
            provisioningRepresentation.setValue(OC_RSRVD_ES_CISERVER, cloudProp.ciServer);

            OIC_LOG_V (DEBUG, ES_CLOUD_RES_TAG, "provisionEnrollee : authCode - %s",
                    (cloudProp.authCode).c_str());
            OIC_LOG_V (DEBUG, ES_CLOUD_RES_TAG, "provisionEnrollee : authProvider - %s",
                    (cloudProp.authProvider).c_str());
            OIC_LOG_V (DEBUG, ES_CLOUD_RES_TAG, "provisionEnrollee : ciServer - %s",
                    (cloudProp.ciServer).c_str());

            m_ocResource->post(OC_RSRVD_ES_RES_TYPE_PROV, BATCH_INTERFACE,
                        provisioningRepresentation, QueryParamsMap(),
                        std::function<
                                void(const HeaderOptions& headerOptions,
                                        const OCRepresentation& rep, const int eCode) >(
                        std::bind(&CloudResource::onCloudProvResponse, this,
                        std::placeholders::_1, std::placeholders::_2,
                        std::placeholders::_3)));
        }

        void CloudResource::onCloudProvResponse(const HeaderOptions& /*headerOptions*/,
                const OCRepresentation& rep, const int eCode)
        {
            OIC_LOG_V (DEBUG, ES_CLOUD_RES_TAG, "onCloudProvResponse : %s, eCode = %d",
                    rep.getUri().c_str(), eCode);

            if (eCode != 0)
            {
                ESResult result  = ESResult::ES_ERROR;

                OIC_LOG(DEBUG, ES_CLOUD_RES_TAG,"onCloudProvResponse : onCloudProvResponse is failed ");

                if (eCode == OCStackResult::OC_STACK_UNAUTHORIZED_REQ)
                {
                    OIC_LOG(DEBUG, ES_CLOUD_RES_TAG, "Mediator is unauthorized from Enrollee.");
                    result = ESResult::ES_UNAUTHORIZED;
                }

                std::shared_ptr< CloudPropProvisioningStatus > provStatus = std::make_shared<
                        CloudPropProvisioningStatus >(result, ESCloudProvState::ES_CLOUD_PROVISIONING_ERROR);
                m_cloudPropProvStatusCb(provStatus);
            }
            else
            {
                OIC_LOG(DEBUG, ES_CLOUD_RES_TAG,"onCloudProvResponse : onCloudProvResponse is success ");
                std::shared_ptr< CloudPropProvisioningStatus > provStatus = std::make_shared<
                        CloudPropProvisioningStatus >(ESResult::ES_OK, ESCloudProvState::ES_CLOUD_PROVISIONING_SUCCESS);
                m_cloudPropProvStatusCb(provStatus);
            }
        }

        void CloudResource::registerCloudPropProvisioningStatusCallback(CloudPropProvStatusCb callback)
        {
            OIC_LOG_V (DEBUG, ES_CLOUD_RES_TAG, "Enter registerCloudPropProvisioningStatusCallback.");
            m_cloudPropProvStatusCb = callback;
        }
    }
}