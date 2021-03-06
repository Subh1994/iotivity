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

#include <mutex>
#include <condition_variable>

#include "RemoteSceneList.h"

#include "UnitTestHelper.h"
#include "SceneCommons.h"
#include "SceneList.h"
#include "RCSResourceObject.h"
#include "RCSRemoteResourceObject.h"
#include "OCPlatform.h"

using namespace std;
using namespace OIC::Service;
using namespace OC;

constexpr int DEFAULT_WAITTIME = 2000;

constexpr char RESOURCE_URI[]{ "/a/light" };
constexpr char RESOURCE_TYPE[]{ "core.light" };
constexpr char KEY[]{ "power" };
constexpr char VALUE[]{ "off" };

static int lightNum = 0;

class RemoteSceneTest : public TestWithMock
{
protected:
    void SetUp()
    {
        TestWithMock::SetUp();
        executionSucceeded = false;

        SceneList::getInstance()->getName();
        createListServer();

        RemoteSceneList::createInstance(pListResource, std::bind(
            &RemoteSceneTest::onRemoteSceneListCreated, this,
            placeholders::_1, placeholders::_2));

        waitForCallback();

        pSceneList->addNewSceneCollection(std::bind(
            &RemoteSceneTest::onRemoteSceneCollectionCreated, this,
            placeholders::_1, placeholders::_2));

        waitForCallback();

        pSceneCollection->addNewScene("Default", std::bind(
            &RemoteSceneTest::onRemoteSceneCreated, this,
            placeholders::_1, placeholders::_2));

        waitForCallback();
    }

    void createListServer()
    {
        std::vector< std::string > vecRT{ SCENE_LIST_RT };
        std::vector< std::string > vecIF{ OC_RSRVD_INTERFACE_DEFAULT, OC::BATCH_INTERFACE };

        pListResource = SceneUtils::createRCSResourceObject(
            "coap://" + SceneUtils::getNetAddress() + SCENE_LIST_URI,
            SCENE_CONNECTIVITY, vecRT, vecIF);
    }

    void createLightServer()
    {
        RCSResourceObject::Ptr pResource = RCSResourceObject::Builder(
            RESOURCE_URI, RESOURCE_TYPE, DEFAULT_INTERFACE).build();
        pResource->setAttribute(KEY, RCSResourceAttributes::Value(VALUE));

        pLightResource
            = SceneUtils::createRCSResourceObject(
            "coap://" + SceneUtils::getNetAddress() + RESOURCE_URI
            + "/" + std::to_string(lightNum++),
            SCENE_CONNECTIVITY, pResource->getTypes(), pResource->getInterfaces());
    }

    void waitForCallback(int waitingTime = DEFAULT_WAITTIME)
    {
        std::unique_lock< std::mutex > lock{ mutex };
        cond.wait_for(lock, std::chrono::milliseconds{ waitingTime });
    }

public:
    RCSRemoteResourceObject::Ptr pListResource;
    RemoteSceneList::Ptr pSceneList;
    RemoteSceneCollection::Ptr pSceneCollection;
    RemoteScene::Ptr pScene;
    RCSRemoteResourceObject::Ptr pLightResource;
    bool executionSucceeded;
    std::condition_variable cond;
    std::mutex mutex;

    void onRemoteSceneListCreated(RemoteSceneList::Ptr remoteSceneList, int)
    {
        pSceneList = std::move(remoteSceneList);
        cond.notify_all();
    }

    void onRemoteSceneCollectionCreated(RemoteSceneCollection::Ptr remoteSceneCol, int)
    {
        pSceneCollection = remoteSceneCol;
        cond.notify_all();
    }

    void onRemoteSceneCreated(RemoteScene::Ptr remoteScene, int)
    {
        pScene = remoteScene;
        cond.notify_all();
    }

    void onRemoteSceneActionCreated(RemoteSceneAction::Ptr, int)
    {
        cond.notify_all();
    }

    void onRemoteSceneExecuted(string, int)
    {
        executionSucceeded = true;
        cond.notify_all();
    }
};

TEST_F(RemoteSceneTest, addNewRemoteScene)
{
    pSceneCollection->addNewScene("Test Scene", std::bind(
        &RemoteSceneTest::onRemoteSceneCreated, this,
        placeholders::_1, placeholders::_2));

    waitForCallback();

    ASSERT_NE(nullptr, pScene);
    ASSERT_EQ("Test Scene", pScene->getName());
}

TEST_F(RemoteSceneTest, createNewRemoteSceneWithEmptyName)
{
    ASSERT_THROW(
        pSceneCollection->addNewScene("", std::bind(
        &RemoteSceneTest::onRemoteSceneCreated, this,
        placeholders::_1, placeholders::_2));, RCSInvalidParameterException);
}

TEST_F(RemoteSceneTest, getRemoteSceneBySceneName)
{
    pSceneCollection->addNewScene("Test Scene", std::bind(
        &RemoteSceneTest::onRemoteSceneCreated, this,
        placeholders::_1, placeholders::_2));

    waitForCallback();

    auto scene = pSceneCollection->getRemoteScene("Test Scene");

    EXPECT_NE(nullptr, scene);
    EXPECT_EQ("Test Scene", scene->getName());
}

TEST_F(RemoteSceneTest, getAllRemoteScenes)
{
    pSceneCollection->addNewScene("Test Scene", std::bind(
        &RemoteSceneTest::onRemoteSceneCreated, this,
        placeholders::_1, placeholders::_2));

    waitForCallback();

    auto scenes = pSceneCollection->getRemoteScenes();

    ASSERT_EQ((unsigned int)2, scenes.size());
    ASSERT_NE(scenes.end(), scenes.find("Test Scene"));
}

TEST_F(RemoteSceneTest, executeRemoteScene)
{
    createLightServer();

    pScene->addNewSceneAction(pLightResource, KEY, RCSResourceAttributes::Value(VALUE),
        std::bind(&RemoteSceneTest::onRemoteSceneActionCreated, this,
        placeholders::_1, placeholders::_2));

    waitForCallback();

    pScene->execute(std::bind(
        &RemoteSceneTest::onRemoteSceneExecuted, this, placeholders::_1, placeholders::_2));

    waitForCallback();

    ASSERT_TRUE(executionSucceeded);
}