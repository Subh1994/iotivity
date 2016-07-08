//******************************************************************
//
// Copyright 2016 Samsung Electronics All Rights Reserved.
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

#include "NSConstants.h"
#include "NSConsumerCommon.h"
#include "NSConsumerInternalTaskController.h"
#include "NSStructs.h"

#include "oic_malloc.h"
#include "oic_string.h"

NSCacheList ** NSGetMessageCacheList()
{
    static NSCacheList * messageCache = NULL;
    return & messageCache;
}

void NSSetMessageCacheList(NSCacheList * cache)
{
    *(NSGetMessageCacheList()) = cache;
}

NSCacheList ** NSGetProviderCacheList()
{
    static NSCacheList * providerCache = NULL;
    return & providerCache;
}

void NSSetProviderCacheList(NSCacheList * cache)
{
    *(NSGetProviderCacheList()) = cache;
}

void NSDestroyMessageCacheList()
{
    NSCacheList * cache = *(NSGetMessageCacheList());
    if (cache)
    {
        NSStorageDestroy(cache);
    }
}

void NSDestroyProviderCacheList()
{
    NSCacheList * cache = *(NSGetProviderCacheList());
    if (cache)
    {
        NSStorageDestroy(cache);
    }
}

NSMessage_consumer * NSMessageCacheFind(const char * messageId)
{
    NS_VERIFY_NOT_NULL(messageId, NULL);

    NSCacheList * MessageCache = *(NSGetMessageCacheList());
    if (!MessageCache)
    {
        NS_LOG(DEBUG, "Message Cache Init");
        MessageCache = NSStorageCreate();
        NS_VERIFY_NOT_NULL(MessageCache, NULL);

        MessageCache->cacheType = NS_CONSUMER_CACHE_MESSAGE;
        NSSetMessageCacheList(MessageCache);
    }

    NSCacheElement * cacheElement = NSStorageRead(MessageCache, messageId);

    return (NSMessage_consumer *) cacheElement->data;
}

NSProvider_internal * NSProviderCacheFind(const char * providerId)
{
    NS_VERIFY_NOT_NULL(providerId, NULL);

    NSCacheList * ProviderCache = *(NSGetProviderCacheList());
    if (!ProviderCache)
    {
        NS_LOG(DEBUG, "Provider Cache Init");
        ProviderCache = NSStorageCreate();
        NS_VERIFY_NOT_NULL(ProviderCache, NULL);

        ProviderCache->cacheType = NS_CONSUMER_CACHE_PROVIDER;
        NSSetMessageCacheList(ProviderCache);
    }

    NSCacheElement * cacheElement = NSStorageRead(ProviderCache, providerId);

    return (NSProvider_internal *) cacheElement->data;
}


NSResult NSMessageCacheUpdate(NSMessage_consumer * msg, NSSyncType type)
{
    NSCacheList * MessageCache = *(NSGetMessageCacheList());
    if (!MessageCache)
    {
        NS_LOG(DEBUG, "Message Cache Init");
        MessageCache = NSStorageCreate();
        NS_VERIFY_NOT_NULL(MessageCache, NS_ERROR);

        MessageCache->cacheType = NS_CONSUMER_CACHE_MESSAGE;
        NSSetMessageCacheList(MessageCache);
    }

    NS_VERIFY_NOT_NULL(msg, NS_ERROR);

    msg->type = type;

    NSCacheElement * obj = (NSCacheElement *)OICMalloc(sizeof(NSCacheElement));
    NS_VERIFY_NOT_NULL(obj, NS_ERROR);

    obj->data = (NSCacheData *) msg;
    obj->next = NULL;

    NS_LOG(DEBUG, "try to write to storage");
    NSResult ret = NSStorageWrite(MessageCache, obj);
    NS_VERIFY_NOT_NULL_WITH_POST_CLEANING(ret == NS_OK ? (void *) 1 : NULL,
            NS_ERROR, NSRemoveMessage(msg));

    NSOICFree(obj);

    return NS_OK;
}

NSResult NSProviderCacheUpdate(NSProvider_internal * provider)
{
    NSCacheList * ProviderCache = *(NSGetProviderCacheList());
    if (!ProviderCache)
    {
        NS_LOG(DEBUG, "Provider Cache Init");
        ProviderCache = NSStorageCreate();
        NS_VERIFY_NOT_NULL(ProviderCache, NS_ERROR);

        ProviderCache->cacheType = NS_CONSUMER_CACHE_PROVIDER;
        NSSetProviderCacheList(ProviderCache);
    }

    NS_VERIFY_NOT_NULL(provider, NS_ERROR);

    NSCacheElement * obj = (NSCacheElement *)OICMalloc(sizeof(NSCacheElement));
    NS_VERIFY_NOT_NULL(obj, NS_ERROR);

    obj->data = (NSCacheData *) provider;
    obj->next = NULL;

    NS_LOG(DEBUG, "try to write to storage");
    NSResult ret = NSStorageWrite(ProviderCache, obj);
    NS_VERIFY_NOT_NULL_WITH_POST_CLEANING(ret == NS_OK ? (void *) 1 : NULL,
            NS_ERROR, NSRemoveProvider(provider));

    NSOICFree(obj);

    return NS_OK;
}

void NSConsumerHandleProviderDiscovered(NSProvider_internal * provider)
{
    NS_VERIFY_NOT_NULL_V(provider);

    NSProvider_internal * providerCacheData = NSProviderCacheFind(provider->providerId);
    NS_VERIFY_NOT_NULL_V(providerCacheData == NULL ? (void *)1 : NULL);

    NS_LOG (ERROR, "New provider is discovered");
    NSResult ret = NSProviderCacheUpdate(provider);
    NS_VERIFY_NOT_NULL_V(ret == NS_OK ? (void *) 1 : NULL);


    if (provider->accessPolicy == NS_ACCESS_DENY)
    {
        NS_LOG(DEBUG, "accepter is NS_ACCEPTER_CONSUMER, Callback to user");
        NSDiscoveredProvider((NSProvider *) provider);
    }
    else
    {
        NS_LOG(DEBUG, "accepter is NS_ACCEPTER_PROVIDER, request subscribe");
        NSTask * task = NSMakeTask(TASK_CONSUMER_REQ_SUBSCRIBE, (void *) provider);
        NS_VERIFY_NOT_NULL_V(task);

        NSConsumerPushEvent(task);
    }
}

void NSConsumerHandleRecvSubscriptionConfirmed(NSMessage_consumer * msg)
{
    NS_VERIFY_NOT_NULL_V(msg);

    NSProvider_internal * provider = NSProviderCacheFind(msg->providerId);
    NS_VERIFY_NOT_NULL_V(provider);

    NSSubscriptionAccepted((NSProvider *) provider);
}

void NSConsumerHandleRecvMessage(NSMessage_consumer * msg)
{
    NS_VERIFY_NOT_NULL_V(msg);

    NSResult ret = NSMessageCacheUpdate(msg, NS_SYNC_UNREAD);
    NS_VERIFY_NOT_NULL_V(ret == NS_OK ? (void *) 1 : NULL);

    NSMessagePost((NSMessage *) msg);
}

void NSConsumerHandleRecvSyncInfo(NSSyncInfo * sync)
{
    NS_VERIFY_NOT_NULL_V(sync);

    NSProvider_internal * provider = NSProviderCacheFind(sync->providerId);
    NS_VERIFY_NOT_NULL_V(provider);

    char msgId[NS_DEVICE_ID_LENGTH] = { 0, };
    snprintf(msgId, NS_DEVICE_ID_LENGTH, "%lu", sync->messageId);

    NSMessage_consumer * msg = NSMessageCacheFind(msgId);
    NS_VERIFY_NOT_NULL_V(msg);

    NSResult ret = NSMessageCacheUpdate(msg, sync->state);
    NS_VERIFY_NOT_NULL_V(ret == NS_OK ? (void *) 1 : NULL);

    NSNotificationSync(sync);
}

void NSConsumerHandleMakeSyncInfo(NSSyncInfo * sync)
{
    NS_VERIFY_NOT_NULL_V(sync);

    NSProvider_internal * provider = NSProviderCacheFind(sync->providerId);
    NS_VERIFY_NOT_NULL_V (provider);

    NSSyncInfo_internal * syncInfo = (NSSyncInfo_internal *)OICMalloc(sizeof(NSSyncInfo_internal));
    NS_VERIFY_NOT_NULL_V(syncInfo);

    OICStrcpy(syncInfo->providerId, sizeof(char) * NS_DEVICE_ID_LENGTH, sync->providerId);
    syncInfo->messageId = sync->messageId;
    syncInfo->state = sync->state;
    syncInfo->i_addr = (OCDevAddr *)OICMalloc(sizeof(OCDevAddr));
    NS_VERIFY_NOT_NULL_WITH_POST_CLEANING_V(syncInfo->i_addr, NSOICFree(syncInfo));
    memcpy(syncInfo->i_addr, provider->i_addr, sizeof(OCDevAddr));

    NSTask * syncTask = NSMakeTask(TASK_SEND_SYNCINFO, (void *) syncInfo);
    NS_VERIFY_NOT_NULL_WITH_POST_CLEANING_V(syncTask, NSOICFree(syncInfo));

    NSConsumerPushEvent(syncTask);

    NSOICFree(sync);
}

void NSConsumerInternalTaskProcessing(NSTask * task)
{
    NS_VERIFY_NOT_NULL_V(task);

    NS_LOG_V(DEBUG, "Receive Event : %d", (int)task->taskType);
    switch (task->taskType)
    {
        case TASK_CONSUMER_RECV_SUBSCRIBE_CONFIRMED:
        {
            NS_LOG(DEBUG, "Receive Subscribe confirm from provider.");
            NSConsumerHandleRecvSubscriptionConfirmed((NSMessage_consumer *)task->taskData);
            break;
        }
        case TASK_CONSUMER_RECV_MESSAGE:
        {
            NS_LOG(DEBUG, "Receive New Notification");
            NSConsumerHandleRecvMessage((NSMessage_consumer *)task->taskData);

            break;
        }
        case TASK_CONSUMER_PROVIDER_DISCOVERED:
        {
            NS_LOG(DEBUG, "Receive New Provider is discovered.");
            NSConsumerHandleProviderDiscovered((NSProvider_internal *)task->taskData);
            break;
        }
        case TASK_RECV_SYNCINFO:
        {
            NS_LOG(DEBUG, "Receive SyncInfo.");
            NSConsumerHandleRecvSyncInfo((NSSyncInfo *)task->taskData);
            break;
        }
        case TASK_MAKE_SYNCINFO:
        {
            NS_LOG(DEBUG, "Make SyncInfo, get Provider's Addr");
            NSConsumerHandleMakeSyncInfo((NSSyncInfo *)task->taskData);
            break;
        }
        default :
        {
            NS_LOG(ERROR, "Unknown TASK Type");
            return ;
        }
    }
}